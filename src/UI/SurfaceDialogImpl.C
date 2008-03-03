
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include <qapplication.h>
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qfile.h>
#include <q3filedialog.h>
#include <qstringlist.h>

#include <fstream>
#include <dlfcn.h>

#include "SurfaceDialogImpl.H"
#include "Vector.H"
#include "Globals.H"

extern QStringList rcdirs;

using std::ofstream;

using VecMath::Vector;

//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  SurfaceDialogImpl c'tor taking parameters for the parent ComplexDialog,
 *  which in turn inherited them from QDialog
 *  displays the dialog
 *  @param parent	parent widget (NULL)
 *  @param name		name of the widget
 *  @param modal	modal dialog?
 *  @param f		window flags
 */
SurfaceDialogImpl::SurfaceDialogImpl (QWidget *parent, const char *name,
					bool modal, Qt::WFlags f) :
	QDialog (parent, name, modal, f) {
  setupUi(this);
  show ();
}

QString SurfaceDialogImpl::libraryName () {
  return LibraryName;
}

bool SurfaceDialogImpl::loadFunction() {
  QString libName;
  //  iterate through all resource directories until you find a plugin subdirectory
  for (QStringList::Iterator it = Globals::Instance().rcdirs.begin(); 
       it != Globals::Instance().rcdirs.end(); 
       ++it ) {
    QDir current (*it);

    if (current.exists ("plugins/surface")) {	//  plugin subdir present?
      libName = Q3FileDialog::getOpenFileName(current.absPath ()+"/plugins/surface",
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

bool SurfaceDialogImpl::loadFunction(const QString &libName) {
  void *handle;
  Vector<4> (*f)(double, double);
  char *error;
      
  handle = dlopen (libName, RTLD_LAZY);
  if (!handle) {
    QMessageBox::warning (this, "Error opening library", dlerror());
    return false;
  }

  f = (Vector<4>(*)(double, double))dlsym(handle, "f");
  if ((error = dlerror()) != NULL)  {
    QMessageBox::warning (this, "Error finding function", error);
    return false;
  }

  dlclose(handle); 
      
  return true;    
}


bool SurfaceDialogImpl::checkValidity() {
  if ((NameEdit->text().isEmpty()) || (XEdit->text().isEmpty())
      || (YEdit->text().isEmpty()) || (ZEdit->text().isEmpty()) || (WEdit->text().isEmpty())) {
    QMessageBox::warning (this, "Missing fields",
			  "Please fill in all fields!");
    return false;
  }

  QString currentPath = QDir::currentDirPath ();
  QDir::setCurrent (*(Globals::Instance().rcdirs.begin())); // qApp->applicationDirPath ());

  if (!QDir::current ().exists ("plugins"))
    QDir::current ().mkdir ("plugins");
  if (!QDir::current ().exists ("plugins/surface"))
    QDir::current ().mkdir ("plugins/surface");
  QDir::setCurrent ("plugins/surface");

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

void SurfaceDialogImpl::writeSource () {
  ofstream SourceFile (NameEdit->text()+".C");

  SourceFile << "#include \"Vector.H\"	\n\
                                                \n\
    extern \"C\" Vector f (double, double);	\n\
    extern \"C\" char *symbolic ();		\n\
                                                \n\
    Vector f (double u, double v) {		\n\
      static Vector F (4);			\n\
      F[0] = " << XEdit->text().toStdString() << ";		\n\
      F[1] = " << YEdit->text().toStdString() << ";		\n\
      F[2] = " << ZEdit->text().toStdString() << ";		\n\
      F[3] = " << WEdit->text().toStdString() << ";		\n\
                                                \n\
    return F; 					\n\
}						\n\
                                                \n\
    char *symbolic () { return \"("	
	     << XEdit->text().toStdString() << ", "
	     << YEdit->text().toStdString() << ", "
	     << ZEdit->text().toStdString() << ", "
	     << WEdit->text().toStdString() << ")"
	     << "\"; }\n";

  SourceFile.close ();
}

bool SurfaceDialogImpl::compile () {
  bool Success = !system ("g++ -g -c -Wall -I.. -I../.. \""
			  +NameEdit->text()
			  +".C\" > /tmp/HyperspaceExplorer.compile.errors 2>&1");
    
  if (!Success) {
    QFile Errs ("/tmp/HyperspaceExplorer.compile.errors");
    Errs.open (QIODevice::ReadOnly);
    QString ErrString (Errs.readAll ());
    QMessageBox::warning (this, "Compilation Errors", ErrString);
  }    
  return Success;
}

bool SurfaceDialogImpl::link () {
  bool Success = !system ("g++ -shared -Wl,-export-dynamic -Wl,-soname,\""
			  +NameEdit->text()+".so\" -o \""
			  +NameEdit->text()+".so\" \""
          +NameEdit->text()+".o\" ../Vector.o"
			  +"> /tmp/HyperspaceExplorer.link.errors 2>&1");
    
  if (!Success) {
    QFile Errs ("/tmp/HyperspaceExplorer.link.errors");
    Errs.open (QIODevice::ReadOnly);
    QString ErrString (Errs.readAll ());
    QMessageBox::warning (this, "Compilation Errors", ErrString);
  }
  return Success;
}
