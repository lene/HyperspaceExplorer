
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
SurfaceDialogImpl::SurfaceDialogImpl (QWidget *parent, Qt::WFlags f) :
	QDialog (parent, f) {
  setupUi(this);
  connect (okButton, SIGNAL(clicked()), this, SLOT(checkValidity()));
  connect (loadButton, SIGNAL(clicked()), this, SLOT(loadFunction()));
  show ();
}

QString SurfaceDialogImpl::libraryName () {
  return LibraryName;
}

bool SurfaceDialogImpl::loadFunction() {
    return PluginCreator::loadFunction("surface", this);
    /*
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
    */
}

bool SurfaceDialogImpl::doLoadFunction(const QString &libName) {
  void *handle;
  Vector<4> (*f)(double, double);
  char *error;

  handle = dlopen (libName.toStdString().c_str(), RTLD_LAZY);
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
  if ((nameEdit->text().isEmpty()) || (XEdit->text().isEmpty())
      || (YEdit->text().isEmpty()) || (ZEdit->text().isEmpty()) || (WEdit->text().isEmpty())) {
    QMessageBox::warning (this, "Missing fields",
			  "Please fill in all fields!");
    return false;
  }

  QString currentPath = QDir::currentPath ();
  QDir::setCurrent (*(Globals::Instance().rcdirs.begin())); // qApp->applicationDirPath ());

  if (!QDir::current ().exists ("plugins"))
    QDir::current ().mkdir ("plugins");
  if (!QDir::current ().exists ("plugins/surface"))
    QDir::current ().mkdir ("plugins/surface");
  QDir::setCurrent ("plugins/surface");

  writeSource ();

  if (!compile (nameEdit->text())) {    //  try to compile
    QDir::setCurrent (currentPath);
    return false;
  }

  if (!link (nameEdit->text())) {   //  try to link
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

void SurfaceDialogImpl::writeSource () {
    ofstream SourceFile ((nameEdit->text().toStdString()+".C").c_str());

    SourceFile << "#include \"Vector.H\"	\n\
\n\
using namespace VecMath;\n\
\n\
extern \"C\" Vector<4> f (double, double);\n\
extern \"C\" char *symbolic ();\n\
\n\
Vector<4> f (double u, double v) {\n\
    static Vector<4> F;\n\
    F[0] = " << XEdit->text().toStdString() << ";\n\
    F[1] = " << YEdit->text().toStdString() << ";\n\
    F[2] = " << ZEdit->text().toStdString() << ";\n\
    F[3] = " << WEdit->text().toStdString() << ";\n\
\n\
    return F;\n\
}\n\
\n\
char *symbolic () {\n\
    return \"("
    << XEdit->text().toStdString() << ", "
    << YEdit->text().toStdString() << ", "
    << ZEdit->text().toStdString() << ", "
    << WEdit->text().toStdString() << ")"
    << "\";\n\
}\n";

  SourceFile.close ();
}
