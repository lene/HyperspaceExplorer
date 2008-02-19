
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
#include <q3filedialog.h>
#include <qstringlist.h>

#include <fstream>
#include <dlfcn.h>
#include "numclass.H"

extern QStringList rcdirs;
                                                     

//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  ComplexDialogImpl c'tor taking parameters for the parent ComplexDialog,
 *  which in turn inherited them from QDialog
 *  displays the dialog
 *  @param parent	parent widget (NULL)
 *  @param name		name of the widget
 *  @param modal	modal dialog?
 *  @param f		window flags
 */
//ComplexDialogImpl::ComplexDialogImpl (QWidget *parent, const char *name,
//					bool modal, Qt::WFlags f) :
//	ComplexDialog (parent, name, modal, f) {
ComplexDialogImpl::ComplexDialogImpl (QWidget *parent, const char *name,
					bool modal, Qt::WFlags f) :
	QDialog (parent, name, modal, f) {
  setupUi(this);
  show ();
}


/*******************************************************************************
 *  @return		the name of the selected DLL
 */
QString ComplexDialogImpl::libraryName () {
  return LibraryName;
}


/*******************************************************************************
 *  display  and load the selected DLL into current address space
 *  loads a dynamic library, which can be selected by the user on a QFileDialog.
 *  calls loadFunction () below. see there.
 *  @return	success (?)
 */
bool ComplexDialogImpl::loadFunction() {
  QString libName;
  //  iterate through all resource directories until you find a plugin subdirectory
  for (QStringList::Iterator it = rcdirs.begin(); it != rcdirs.end(); ++it ) {
    QDir current (*it);
    if (current.exists ("plugins/complex")) {	//  plugin subdir present?
      libName = Q3FileDialog::getOpenFileName(current.absPath ()+"/plugins/complex",
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
    accept();				        //  WHAT GOES ON HERE? forgot to check <blush>
  }
  
  return false;
}


/*******************************************************************************
 *  loads the dynamic library given by libName, if it exists and can be loaded.
 *  then it checks whether a function named f () is present. if so, returns true.
 *  else borks with an error message.
 *  @param libName	filename for the selected DLL
 *  @return		success
 */
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


/*******************************************************************************
 *  this function is called when the user clicks the OK button in the Function Dialog.
 *  checks whether all fields are filled in, whether the given function is valid C++ 
 *  syntax, ie. whether it compiles, and whether the compiled code links into a dynamic
 *  library.
 *  as a side effect, it generates this library.
 *  finally, it checks whether the library can be loaded. if so, it accepts the input.
 *  also, this function creates a directory structure "plugins/real" under the resource
 *  directory and changes the CWD to that folder for the duration of checkValidity ().
 *  the name for this function is chosen rather unfortunately, i guess.
 *  @return		success
 */
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


/*******************************************************************************
 *  write a C++ source file, containing the given function and some framework to
 *  make it compilable by g++ (there is currently no support for other compilers).
 *  the resulting file "<function-name>.C" defines the function f () and the
 *  function symbolic (), which returns the function in symbolic terms, not in
 *  C++ syntax.
 */
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
      complex<double> z (u, v), w = " << WEdit->text().toStdString() << ";	\n\
      F[0] = u; 						\n\
      F[1] = v;							\n\
      F[2] = w.real ();						\n\
      F[3] = w.imag ();						\n\
                                                                \n\
      return F; }						\n\
                                                                \n\
    char *symbolic () { return \"" << WEdit->text().toStdString() << "\"; }	\n";
  
    SourceFile.close ();
}


/*******************************************************************************
 *  compile the C++ source code written by writeSource (), displaying errors and
 *  warnings, if they come up.
 *  needs "numclass.H" in the current directory or in the C++ include path.
 *  might tweak the compilation flags a little, or make them variable
 *  I think this could be done in the parent...?
 *  @return 	success
 */
bool ComplexDialogImpl::compile () {
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


/*******************************************************************************
 *  link the object file generated by compile () into a dynamic library.
 *  needs "numclass.o" in the current directory.
 *  I think this could be done in the parent...?
 *  @return 	success
 */
bool ComplexDialogImpl::link () {
  bool Success = !system ("g++ -shared -Wl,-export-dynamic -Wl,-soname,\""
			  +NameEdit->text()+".so\" -o \""
			  +NameEdit->text()+".so\" \""
			  +NameEdit->text()+".o\" ../numclass.o"
			  +"> /tmp/HyperspaceExplorer.link.errors 2>&1");
    
  if (!Success) {
    QFile Errs ("/tmp/HyperspaceExplorer.link.errors");
    Errs.open (QIODevice::ReadOnly);
    QString ErrString (Errs.readAll ());
    QMessageBox::warning (this, "Compilation Errors", ErrString);
  }
  return Success;
}
