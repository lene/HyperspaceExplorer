
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "ComplexDialogImpl.H"
#include <qapplication.h>
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qstringlist.h>

#include <fstream>
#include <dlfcn.h>
#include "numclass.H"

extern QStringList rcdirs;


ComplexDialogImpl::ComplexDialogImpl (QWidget *parent, const char *name,
					bool modal, WFlags f) :
	ComplexDialog (parent, name, modal, f) {
  show ();
}

QString ComplexDialogImpl::libraryName () {
  return LibraryName;
}
bool ComplexDialogImpl::loadFunction() {
  QString libName;
  //  iterate through all resource directories until you find a plugin subdirectory
  for (QStringList::Iterator it = rcdirs.begin(); it != rcdirs.end(); ++it ) {
    QDir current (*it);
    if (current.exists ("plugins/complex")) {	//  plugin subdir present?
      libName = QFileDialog::getOpenFileName(current.absPath ()+"/plugins/complex",
					     "Libraries (*.so*)",
					     this,
					     "Open a function"
					     "Choose a dynamic library");
      if (!libName.isNull ()) break;		//  if user pressed "Cancel", try next dir
    }
  }

  if (libName.isNull ()) return false;		//  nothing found or selected

  if (loadFunction (libName)) {
    LibraryName = libName;
    accept();
  }
  
  return false;
}

bool ComplexDialogImpl::loadFunction(const QString &libName) {
  void *handle;
  Vector (*f)(double, double, double);
  char *error;
      
  handle = dlopen (libName, RTLD_LAZY);
  if (!handle) {
    QMessageBox::warning (this, "Error opening library", dlerror());
    return false;
  }

  f = (Vector(*)(double, double, double))dlsym(handle, "f");
  if ((error = dlerror()) != NULL)  {
    QMessageBox::warning (this, "Error finding function", error);
    return false;
  }

  dlclose(handle); 
      
  return true;    
}

bool ComplexDialogImpl::checkValidity() {
  if ((NameEdit->text().isEmpty()) || (WEdit->text().isEmpty())) {
    QMessageBox::warning (this, "Missing fields",
			  "Please fill in all fields!");
    return false;
  }

  QString currentPath = QDir::currentDirPath ();
  //  QDir::setCurrent (qApp->applicationDirPath ());
  QDir::setCurrent (*(rcdirs.begin()));		//  qApp->applicationDirPath ());

  if (!QDir::current ().exists ("plugins"))
    QDir::current ().mkdir ("plugins");
  if (!QDir::current ().exists ("plugins/complex"))
    QDir::current ().mkdir ("plugins/complex");
  QDir::setCurrent ("plugins/complex");

  writeSource ();

  if (!compile ()) {					//  try to compile
    QDir::setCurrent (currentPath);  
    return false;
  }
  
  if (!link ()) {					//  try to link
    QDir::setCurrent (currentPath);     
    return false;
  }
  //  try to open the resulting dynamic library
  //  the name of the dynamic library must be given absolutely, because dlopen ()
  //  only checks LD_LIBRARY_PATH, which usually does not contain "."
  if (loadFunction (QDir::currentDirPath ()+"/"+NameEdit->text()+".so")) {
    LibraryName = QDir::currentDirPath ()+"/"+NameEdit->text()+".so";
    accept();
  }

  QDir::setCurrent (currentPath);
  
  return true;
}

void ComplexDialogImpl::writeSource () {
  ofstream SourceFile (NameEdit->text()+".C");

  SourceFile << "#include \"numclass.H\"			\n\
#include <complex>						\n\
                                                                \n\
    extern \"C\" Vector f (double, double);			\n\
    extern \"C\" char *symbolic ();			        \n\
                                                                \n\
    Vector f (double u, double v) {				\n\
      static Vector F (4);					\n\
      complex<double> z (u, v), w = " <<WEdit->text() << ";	\n\
      F[0] = u; 						\n\
      F[1] = v;							\n\
      F[2] = w.real ();						\n\
      F[3] = w.imag ();						\n\
                                                                \n\
      return F; }						\n\
                                                                \n\
    char *symbolic () { return \"" << WEdit->text()<< "\"; }	\n";
  
    SourceFile.close ();
}

bool ComplexDialogImpl::compile () {
  bool Success = !system ("g++ -g -c -Wall -I.. -I../.. \""
			  +NameEdit->text()
			  +".C\" > /tmp/HyperspaceExplorer.compile.errors 2>&1");
    
  if (!Success) {
    QFile Errs ("/tmp/HyperspaceExplorer.compile.errors");
    Errs.open (IO_ReadOnly);
    QString ErrString (Errs.readAll ());
    QMessageBox::warning (this, "Compilation Errors", ErrString);
  }    
  return Success;
}

bool ComplexDialogImpl::link () {
  bool Success = !system ("g++ -shared -Wl,-export-dynamic -Wl,-soname,\""
			  +NameEdit->text()+".so\" -o \""
			  +NameEdit->text()+".so\" \""
			  +NameEdit->text()+".o\" ../numclass.o"
			  +"> /tmp/HyperspaceExplorer.link.errors 2>&1");
    
  if (!Success) {
    QFile Errs ("/tmp/HyperspaceExplorer.link.errors");
    Errs.open (IO_ReadOnly);
    QString ErrString (Errs.readAll ());
    QMessageBox::warning (this, "Compilation Errors", ErrString);
  }
  return Success;
}
