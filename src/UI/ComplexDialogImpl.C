
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include <QApplication>
#include <QMessageBox>
#include <QLineEdit>
#include <QFile>
#include <QFileDialog>
#include <QStringList>

#include <fstream>
#include <dlfcn.h>

#include "ComplexDialogImpl.H"
#include "Vector.H"
#include "Globals.H"

extern QStringList rcdirs;

using std::ofstream;

using VecMath::Vector;

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
ComplexDialogImpl::ComplexDialogImpl (QWidget *parent, Qt::WFlags f) :
	QDialog (parent, f) {
  setupUi(this);
  connect (okButton, SIGNAL(clicked()), this, SLOT(checkValidity()));
  connect (loadButton, SIGNAL(clicked()), this, SLOT(loadFunction()));
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
    return PluginCreator::loadFunction("complex", this);
/*
    QString libName;
  //  iterate through all resource directories until you find a plugin subdirectory
  for (QStringList::Iterator it = Globals::Instance().rcdirs.begin();
       it != Globals::Instance().rcdirs.end();
       ++it ) {
    QDir current (*it);
    if (current.exists ("plugins/complex")) {	//  plugin subdir present?
      libName = QFileDialog::getOpenFileName(current.absolutePath ()+"/plugins/complex",
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
    */
}


/*******************************************************************************
 *  loads the dynamic library given by libName, if it exists and can be loaded.
 *  then it checks whether a function named f () is present. if so, returns true.
 *  else borks with an error message.
 *  @param libName	filename for the selected DLL
 *  @return		success
 */
bool ComplexDialogImpl::doLoadFunction(const QString &libName) {
  void *handle;
  Vector<4> (*f)(double, double, double);
  char *error;

  handle = dlopen (libName.toStdString().c_str(), RTLD_LAZY);
  if (!handle) {
    QMessageBox::warning (this, "Error opening library", dlerror());
    return false;
  }

  f = (Vector<4>(*)(double, double, double))dlsym(handle, "f");
  if ((error = dlerror()) != NULL)  {
    QMessageBox::warning (this, "Error finding function", error);
    return false;
  }

  dlclose(handle);

  return true;
}


/** this function is called when the user clicks the OK button in the Function Dialog.
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
  if ((nameEdit->text().isEmpty()) || (WEdit->text().isEmpty())) {
    QMessageBox::warning (this, "Missing fields",
			  "Please fill in all fields!");
    return false;
  }

  QString currentPath = QDir::currentPath ();
  QDir::setCurrent (*(Globals::Instance().rcdirs.begin()));

  if (!QDir::current ().exists ("plugins"))
    QDir::current ().mkdir ("plugins");
  if (!QDir::current ().exists ("plugins/complex"))
    QDir::current ().mkdir ("plugins/complex");
  QDir::setCurrent ("plugins/complex");

  writeSource ();

  if (!compile (nameEdit->text())) {    //  try to compile
    QDir::setCurrent (currentPath);
    return false;
  }

  if (!link (nameEdit->text())) {					//  try to link
    QDir::setCurrent (currentPath);
    return false;
  }
  //  try to open the resulting dynamic library
  //  the name of the dynamic library must be given absolutely, because dlopen ()
  //  only checks LD_LIBRARY_PATH, which usually does not contain "."
  if (doLoadFunction (QDir::currentPath ()+"/"+nameEdit->text()+".so")) {
    LibraryName = QDir::currentPath ()+"/"+nameEdit->text()+".so";
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
  ofstream SourceFile ((nameEdit->text().toStdString()+".C").c_str());

  SourceFile << "#include \"Vector.H\"\n\
#include <complex>\n\
\n\
using namespace VecMath;\n\
using std::complex;\n\
\n\
extern \"C\" Vector<4> f (double, double);\n\
extern \"C\" char *symbolic ();\n\
\n\
Vector<4> f (double u, double v) {\n\
    static Vector<4> F;\n\
    complex<double> z (u, v), w = " << WEdit->text().toStdString() << ";\n\
    F[0] = u;\n\
    F[1] = v;\n\
    F[2] = w.real ();\n\
    F[3] = w.imag ();\n\
\n\
    return F;\n\
}\n\
\n\
char *symbolic () {\n\
    return \"" << WEdit->text().toStdString() << "\"; \n\
}\n";

    SourceFile.close ();
}

