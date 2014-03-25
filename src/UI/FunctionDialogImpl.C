/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include <fstream>
#include <dlfcn.h>

#include <QApplication>
#include <QMessageBox>
#include <QLineEdit>
#include <QFile>
#include <QFileDialog>
#include <QStringList>

#include "Vector.h"
#include "Globals.h"
#include "FunctionDialogImpl.h"

using std::cerr;
using std::endl;
using std::ofstream;

using VecMath::Vector;

namespace UI {
    namespace Dialogs {
        //////////////////////////////////////////////////////////////////////
        // construction / destruction
        //////////////////////////////////////////////////////////////////////

        /// FunctionDialogImpl c'tor - displays the dialog
        /** @param parent parent widget (NULL)
        *  @param f window flags                                                     */
        FunctionDialogImpl::FunctionDialogImpl (QWidget *parent):
            QDialog (parent) {
            setupUi(this);
            connect (okButton, SIGNAL(clicked()), this, SLOT(checkValidity()));
            connect (loadButton, SIGNAL(clicked()), this, SLOT(loadFunction()));
            descriptionLabel->hide();
            descriptionTextEdit->hide();
            if (layout()) layout()->setSizeConstraint(QLayout::SetFixedSize);
            show ();
        }


        /// Display  and load the selected DLL into current address space
        /** Loads a dynamic library, which can be selected by the user on a QFileDialog.
        *  calls loadFunction () below. see there.
        *  @return success (?)                                                       */
        bool FunctionDialogImpl::loadFunction() {
            return PluginCreator::loadFunction("real", this);
        }


        /// Loads the dynamic library given by libName, if it exists and can be loaded.
        /** Then checks whether a function named f() is present. if so, returns
        *  true. else borks with an error message.
        *  @param libName filename for the selected DLL
        *  @return success                                                           */
        bool FunctionDialogImpl::functionPresent(const QString &libName) {
            return PluginCreator::
                LoadFunctionHelper<Vector<4> (double, double, double)>::
                    functionPresent(libName, this);
        }


        /// Called when the user clicks the OK button in the Function Dialog.
        /** Checks whether all fields are filled in, whether the given function
        *  is valid C++ syntax, ie. whether it compiles, and whether the compiled code
        *  links into a dynamic library.
        *
        *  As a side effect, it generates this library.
        *
        *  Finally, it checks whether the library can be loaded. if so, it accepts the
        *  input.
        *
        *  Also, this function creates a directory structure "plugins/real" under the
        *  resource directory and changes the CWD to that folder for the duration of
        *  checkValidity ().
        *
        *  The name for this function is chosen rather unfortunately, i admit.
        *
        *  @return success                                                           */
        bool FunctionDialogImpl::checkValidity() {
            if ((nameEdit->text().isEmpty()) || (functionEdit->text().isEmpty())) {
                QMessageBox::warning (this, "Missing fields",
                                    "Please fill in all fields!");
                return false;
            }
            return PluginCreator::checkValidity("real", nameEdit->text(), this);
        }


        /// Write a C++ source file containing the given function
        /** Also written is a little framework to make the source file compilable by g++
        *  (there is currently no support for other compilers).
        *
        *  The resulting file "<function-name>.C" defines the function \em f() and the
        *  function \em symbolic(), which returns the function in symbolic terms, not
        *  in C++ syntax.                                                               */
        void FunctionDialogImpl::writeSource () {
            ofstream SourceFile ((nameEdit->text().toStdString()+".C").c_str());

            SourceFile << "#include \"" << vector_include_file.toStdString() << "\"\n\
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
    }
}
