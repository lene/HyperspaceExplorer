
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

#include "PolarDialogImpl.H"
#include "Vector.H"
#include "Globals.H"

using std::ofstream;

using VecMath::Vector;

namespace UI {
    namespace Dialogs {
        /** PolarDialogImpl c'tor taking parameters for the parent ComplexDialog,
        *  which in turn inherited them from QDialog
        *  displays the dialog
        *  @param parent parent widget (NULL)
        *  @param f window flags                                                     */
        PolarDialogImpl::PolarDialogImpl (QWidget *parent, Qt::WFlags f) :
                QDialog (parent, f) {
        setupUi(this);
        connect (okButton, SIGNAL(clicked()), this, SLOT(checkValidity()));
        connect (loadButton, SIGNAL(clicked()), this, SLOT(loadFunction()));
        descriptionLabel->hide();
        descriptionTextEdit->hide();
        if (layout()) layout()->setSizeConstraint(QLayout::SetFixedSize);
        show ();
        }

        /** display  and load the selected DLL into current address space
        *  loads a dynamic library, which can be selected by the user on a QFileDialog.
        *  calls loadFunction () below. see there.
        *  @return	success (?)
        */
        bool PolarDialogImpl::loadFunction() {
            return PluginCreator::loadFunction("polar", this);
        }

        /** loads the dynamic library given by libName, if it exists and can be loaded.
        *  then it checks whether a function named f () is present. if so, returns true.
        *  else borks with an error message.
        *  @param libName filename for the selected DLL
        *  @return success                                                           */
        bool PolarDialogImpl::functionPresent(const QString &libName) {
            return PluginCreator::
                LoadFunctionHelper<Vector<4> (double, double, double)>::
                    functionPresent(libName, this);
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
        bool PolarDialogImpl::checkValidity() {
            if ((nameEdit->text().isEmpty()) || (FEdit->text().isEmpty())) {
                QMessageBox::warning (this, "Missing fields",
                                    "Please fill in all fields!");
                return false;
            }
            return PluginCreator::checkValidity("polar", nameEdit->text(), this);
        }

        /** write a C++ source file, containing the given function and some framework to
        *  make it compilable by g++ (there is currently no support for other compilers).
        *  the resulting file "<function-name>.C" defines the function f () and the
        *  function symbolic (), which returns the function in symbolic terms, not in
        *  C++ syntax.
        */
        void PolarDialogImpl::writeSource () {
            ofstream SourceFile ((nameEdit->text().toStdString()+".C").c_str());

            SourceFile << "#include \"Vector.H\"\n\
        \n\
        using namespace VecMath;\n\
        \n\
        extern \"C\" Vector<4> f (double, double, double);\n\
        extern \"C\" char *symbolic ();\n\
        \n\
        Vector<4> f (double t, double u, double v) {\n\
            static Vector<4> F;\n\
            double sinphi = sin (pi*t), cosphi = cos (pi*t),\n\
                sintht = sin (pi*u), costht = cos (pi*u),\n\
                sinpsi = sin (pi*v), cospsi = cos (pi*v),\n\
                Radius = " << FEdit->text().toStdString() << ";\n\
        \n\
            F[0] = Radius*sinpsi*sintht*cosphi;\n\
            F[1] = Radius*sinpsi*sintht*sinphi;\n\
            F[2] = Radius*sinpsi*costht;\n\
            F[3] = Radius*cospsi;\n\
        \n\
            return F;\n\
        }\n\
        \n\
        char *symbolic () {\n\
            return \"" << FEdit->text().toStdString() << "\";\n\
        }\n";

            SourceFile.close ();
        }
    }
}
