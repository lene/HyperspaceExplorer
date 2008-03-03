
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

#include "PolarDialogImpl.H"
#include "Vector.H"
#include "Globals.H"

extern QStringList rcdirs;

using std::ofstream;

using VecMath::Vector;

//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  PolarDialogImpl c'tor taking parameters for the parent ComplexDialog,
 *  which in turn inherited them from QDialog
 *  displays the dialog
 *  @param parent	parent widget (NULL)
 *  @param name		name of the widget
 *  @param modal	modal dialog?
 *  @param f		window flags
 */
PolarDialogImpl::PolarDialogImpl (QWidget *parent, const char *name,
				  bool modal, Qt::WFlags f) :
	QDialog (parent, name, modal, f) {
  setupUi(this);
  show ();
}


/*******************************************************************************
 *  @return		the name of the selected DLL
 */
QString PolarDialogImpl::libraryName () {
  return LibraryName;
}


/*******************************************************************************
 *  display  and load the selected DLL into current address space
 *  loads a dynamic library, which can be selected by the user on a QFileDialog.
 *  calls loadFunction () below. see there.
 *  @return	success (?)
 */
bool PolarDialogImpl::loadFunction() {
  QString libName;
  //  iterate through all resource directories until you find a plugin subdirectory
  for (QStringList::Iterator it = Globals::Instance().rcdirs.begin(); 
       it != Globals::Instance().rcdirs.end(); 
       ++it ) {
    QDir current (*it);
    if (current.exists ("plugins/polar")) {	//  plugin subdir present?
      libName = Q3FileDialog::getOpenFileName(current.absPath ()+"/plugins/polar",
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


/*******************************************************************************
 *  loads the dynamic library given by libName, if it exists and can be loaded.
 *  then it checks whether a function named f () is present. if so, returns true.
 *  else borks with an error message.
 *  i'm sorry loadFunction () is a misnomer, it should be called checkFunction (),
 *  but as this name is distributed about three dozen .C, .H and .ui files, it is
 *  too much bother to change that now.
 *  @param libName	filename for the selected DLL
 *  @return		success
 */
bool PolarDialogImpl::loadFunction(const QString &libName) {
  void *handle;
  Vector<4> (*f)(double, double, double);
  char *error;
      
  handle = dlopen (libName, RTLD_LAZY);
  if (!handle) {
    QMessageBox::warning (this, "Error opening library", dlerror());
    return false;
  }

  //  f = (Vector(*)(double, double, double))dlsym(handle, "f__Fddd");
  f = (Vector<4>(*)(double, double, double))dlsym(handle, "f");
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
bool PolarDialogImpl::checkValidity() {
  if ((NameEdit->text().isEmpty()) || (FEdit->text().isEmpty())) {
    QMessageBox::warning (this, "Missing fields",
			  "Please fill in all fields!");
    return false;
  }

  QString currentPath = QDir::currentDirPath ();
  QDir::setCurrent (*(Globals::Instance().rcdirs.begin()));

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


/*******************************************************************************
 *  write a C++ source file, containing the given function and some framework to
 *  make it compilable by g++ (there is currently no support for other compilers).
 *  the resulting file "<function-name>.C" defines the function f () and the
 *  function symbolic (), which returns the function in symbolic terms, not in
 *  C++ syntax.
 */
void PolarDialogImpl::writeSource () {
  ofstream SourceFile (NameEdit->text()+".C");

  SourceFile << "#include \"Vector.H\"		\n\
                                                        \n\
    extern \"C\" Vector f (double, double, double);	\n\
    extern \"C\" char *symbolic ();			\n\
                                                        \n\
    Vector f (double t, double u, double v) {		\n\
      static Vector F (4);				\n\
      double sinphi = sin (pi*t), cosphi = cos (pi*t),	\n\
             sintht = sin (pi*u), costht = cos (pi*u),	\n\
             sinpsi = sin (pi*v), cospsi = cos (pi*v),	\n\
             Radius = " << FEdit->text().toStdString() << ";		\n\
                                                        \n\
      F[0] = Radius*sinpsi*sintht*cosphi;		\n\
      F[1] = Radius*sinpsi*sintht*sinphi;		\n\
      F[2] = Radius*sinpsi*costht;			\n\
      F[3] = Radius*cospsi;				\n\
                                                        \n\
      return F; }					\n\
                                                        \n\
    char *symbolic () { return \"" << FEdit->text().toStdString() << "\"; }\n";
  
    SourceFile.close ();
}


/*******************************************************************************
 *  compile the C++ source code written by writeSource (), displaying errors and
 *  warnings, if they come up.
 *  needs "Vector.H" in the current directory or in the C++ include path.
 *  might tweak the compilation flags a little, or make them variable
 *  I think this could be done in the parent...?
 *  @return 	success
 */
bool PolarDialogImpl::compile () {
  bool Success = !system ("g++ -g -c -Wall -I.. -I../..  \""
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
 *  needs "Vector.o" in the current directory.
 *  I think this could be done in the parent...?
 *  @return 	success
 */
bool PolarDialogImpl::link () {
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


