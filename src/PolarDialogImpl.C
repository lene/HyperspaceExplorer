
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "PolarDialogImpl.H"

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

PolarDialogImpl::PolarDialogImpl (QWidget *parent, const char *name,
				  bool modal, WFlags f) :
	PolarDialog (parent, name, modal, f) {
  show ();
}


QString PolarDialogImpl::libraryName () {
  return LibraryName;
}

bool PolarDialogImpl::loadFunction() {
  QString libName;
  //  iterate through all resource directories until you find a plugin subdirectory
  for (QStringList::Iterator it = rcdirs.begin(); it != rcdirs.end(); ++it ) {
    QDir current (*it);
    if (current.exists ("plugins/polar")) {	//  plugin subdir present?
      libName = QFileDialog::getOpenFileName(current.absPath ()+"/plugins/polar",
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

bool PolarDialogImpl::loadFunction(const QString &libName) {
  void *handle;
  Vector (*f)(double, double, double);
  char *error;
      
  handle = dlopen (libName, RTLD_LAZY);
  if (!handle) {
    QMessageBox::warning (this, "Error opening library", dlerror());
    return false;
  }

  //  f = (Vector(*)(double, double, double))dlsym(handle, "f__Fddd");
  f = (Vector(*)(double, double, double))dlsym(handle, "f");
  if ((error = dlerror()) != NULL)  {
    QMessageBox::warning (this, "Error finding function", error);
    return false;
  }

  dlclose(handle); 
      
  return true;    
}


bool PolarDialogImpl::checkValidity() {
  if ((NameEdit->text().isEmpty()) || (FEdit->text().isEmpty())) {
    QMessageBox::warning (this, "Missing fields",
			  "Please fill in all fields!");
    return false;
  }

  QString currentPath = QDir::currentDirPath ();
  QDir::setCurrent (*(rcdirs.begin()));		//  qApp->applicationDirPath ());

  if (!QDir::current ().exists ("plugins"))
    QDir::current ().mkdir ("plugins");
  if (!QDir::current ().exists ("plugins/polar"))
    QDir::current ().mkdir ("plugins/polar");
  QDir::setCurrent ("plugins/polar");

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

void PolarDialogImpl::writeSource () {
  ofstream SourceFile (NameEdit->text()+".C");

  SourceFile << "#include \"numclass.H\"		\n\
                                                        \n\
    extern \"C\" Vector f (double, double, double);	\n\
    extern \"C\" char *symbolic ();			\n\
                                                        \n\
    Vector f (double t, double u, double v) {		\n\
      static Vector F (4);				\n\
      double sinphi = sin (pi*t), cosphi = cos (pi*t),	\n\
             sintht = sin (pi*u), costht = cos (pi*u),	\n\
             sinpsi = sin (pi*v), cospsi = cos (pi*v),	\n\
             Radius = " << FEdit->text() << ";		\n\
                                                        \n\
      F[0] = Radius*sinpsi*sintht*cosphi;		\n\
      F[1] = Radius*sinpsi*sintht*sinphi;		\n\
      F[2] = Radius*sinpsi*costht;			\n\
      F[3] = Radius*cospsi;				\n\
                                                        \n\
      return F; }					\n\
                                                        \n\
    char *symbolic () { return \"" << FEdit->text()<< "\"; }\n";
  
    SourceFile.close ();
}

bool PolarDialogImpl::compile () {
  bool Success = !system ("g++ -g -c -Wall -I.. -I../..  \""
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

bool PolarDialogImpl::link () {
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


