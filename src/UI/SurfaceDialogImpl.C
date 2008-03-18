
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
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

#include "SurfaceDialogImpl.H"
#include "Vector.H"
#include "Globals.H"

using std::ofstream;

using VecMath::Vector;

/** SurfaceDialogImpl c'tor taking parameters for the parent ComplexDialog,
 *  which in turn inherited them from QDialog
 *  displays the dialog
 *  @param parent parent widget (NULL)
 *  @param f window flags                                                     */
SurfaceDialogImpl::SurfaceDialogImpl (QWidget *parent, Qt::WFlags f) :
	QDialog (parent, f) {
  setupUi(this);
  connect (okButton, SIGNAL(clicked()), this, SLOT(checkValidity()));
  connect (loadButton, SIGNAL(clicked()), this, SLOT(loadFunction()));
  descriptionLabel->hide();
  descriptionTextEdit->hide();
  show ();
}

bool SurfaceDialogImpl::loadFunction() {
    return PluginCreator::loadFunction("surface", this);
}

bool SurfaceDialogImpl::functionPresent(const QString &libName) {
    return PluginCreator::
        LoadFunctionHelper<Vector<4> (double, double)>::
            functionPresent(libName, this);
}

bool SurfaceDialogImpl::checkValidity() {
    if ((nameEdit->text().isEmpty()) || (XEdit->text().isEmpty())
        || (YEdit->text().isEmpty()) || (ZEdit->text().isEmpty())
        || (WEdit->text().isEmpty())) {
        QMessageBox::warning (this, "Missing fields",
"Please fill in all fields: A name for the function and a function f:R²->R \
for all four components of the resulting vector!");
        return false;
    }
    return PluginCreator::checkValidity("surface", nameEdit->text(), this);
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
