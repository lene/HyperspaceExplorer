
//      project:      hyperspace explorer
//      module:       FunctionDialogImpl.C
//      contains:     routines needed for the handling of user-generated R^3->R functions
//      compile with: make
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include <fstream>
#include <dlfcn.h>

#include <QApplication>
#include <QMessageBox>
#include <QLineEdit>
#include <QFile>
#include <QFileDialog>
#include <QStringList>

#include "Vector.H"
#include "Globals.H"
#include "FunctionDialogImpl.H"

using std::cerr;
using std::endl;
using std::ofstream;

using VecMath::Vector;

//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////

/** FunctionDialogImpl c'tor taking parameters for the parent ComplexDialog,
 *  which in turn inherited them from QDialog
 *  displays the dialog
 *  @param parent parent widget (NULL)
 *  @param name name of the widget
 *  @param modal modal dialog?
 *  @param f window flags                                                     */
FunctionDialogImpl::FunctionDialogImpl (QWidget *parent, Qt::WFlags f) :
    QDialog (parent, f) {
    setupUi(this);
    connect (okButton, SIGNAL(clicked()), this, SLOT(checkValidity()));
    connect (loadButton, SIGNAL(clicked()), this, SLOT(loadFunction()));
    show ();
}


/** @return the name of the selected DLL */
QString FunctionDialogImpl::libraryName () { return LibraryName; }

/** display  and load the selected DLL into current address space
 *  loads a dynamic library, which can be selected by the user on a QFileDialog.
 *  calls loadFunction () below. see there.
 *  @return success (?)                                                       */
bool FunctionDialogImpl::loadFunction() {
    return PluginCreator::loadFunction("real", this);
}


/** loads the dynamic library given by libName, if it exists and can be loaded.
 *  then it checks whether a function named f () is present. if so, returns
 *  true. else borks with an error message.
 *  i'm sorry doLoadFunction () is a misnomer, it should be called
 *  checkFunction (), but as this name is distributed about three dozen .C, .H
 *  and .ui files, it is too much bother to change that now.
 *  @param libName filename for the selected DLL
 *  @return success
 */
bool FunctionDialogImpl::doLoadFunction(const QString &libName) {
    void *handle;
    Vector<4> (*f)(double, double, double);
    char *error;

    if (!QFile::exists (libName)) {
        QMessageBox::warning (this, "Error opening library",
                              "Library does not exist: "+libName);
        cerr << "Library does not exist: "+libName.toStdString() << endl;
        return false;
    }

    handle = dlopen (libName.toStdString().c_str(), RTLD_LAZY);
    if (!handle) {
        QMessageBox::warning (this, "Error opening library", dlerror());
        return false;
    }

    f = (Vector<4>(*)(double, double, double))dlsym(handle, "f");

    if (f == NULL) {
        if ((error = dlerror()) != NULL)  {
            QMessageBox::warning (this, "Error finding function", error);
            abort ();
            return false;
        }
    }

    dlclose(handle);

    return true;
}


/** this function is called when the user clicks the OK button in the Function
 *  Dialog. Checks whether all fields are filled in, whether the given function
 *  is valid C++ syntax, ie. whether it compiles, and whether the compiled code
 *  links into a dynamic library.
 *  as a side effect, it generates this library.
 *  finally, it checks whether the library can be loaded. if so, it accepts the
 *  input.
 *  also, this function creates a directory structure "plugins/real" under the
 *  resource directory and changes the CWD to that folder for the duration of
 *  checkValidity ().
 *  the name for this function is chosen rather unfortunately, i guess.
 *
 *  @return success                                                           */
bool FunctionDialogImpl::checkValidity() {
    if ((nameEdit->text().isEmpty()) || (functionEdit->text().isEmpty())) {
        QMessageBox::warning (this, "Missing fields",
                              "Please fill in all fields!");
        return false;
    }

    QString currentPath = QDir::currentPath();
    QDir::setCurrent (*(Globals::Instance().rcdirs.begin()));

    if (!QDir::current ().exists ("plugins"))
        QDir::current ().mkdir ("plugins");
    if (!QDir::current ().exists ("plugins/real"))
        QDir::current ().mkdir ("plugins/real");
    QDir::setCurrent ("plugins/real");
    //  we are now in the subdirectory plugins/real under the first entry of the rcdirs list
    cerr << QDir::currentPath().toStdString() << endl;
    writeSource();                      //  generate C++ source code

    if (!compile(nameEdit->text())) {                  //  try to compile
        QDir::setCurrent (currentPath);
        return false;
    }

    if (!link (nameEdit->text())) {                     //  try to link
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
void FunctionDialogImpl::writeSource () {
    ofstream SourceFile ((nameEdit->text().toStdString()+".C").c_str());

  SourceFile << "#include \"Vector.H\"\n\
\n\
using namespace VecMath;\n\
\n\
extern \"C\" Vector<4> f (double, double, double);	\n\
extern \"C\" char *symbolic ();\n\
\n\
Vector<4> f (double x, double y, double z) {\n\
    static Vector<4> F;\n\
    F[0] = x;\n\
    F[1] = y;\n\
    F[2] = z;\n\
    F[3] = " << functionEdit->text().toStdString() << ";\n\
\n\
    return F; }\n\
\n\
char *symbolic () {\n\
    return \"" << functionEdit->text().toStdString() << "\";\n\
}\n";

    SourceFile.close ();
}


