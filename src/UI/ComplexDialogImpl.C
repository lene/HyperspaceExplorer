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

#include <QApplication>
#include <QMessageBox>
#include <QLineEdit>
#include <QFile>
#include <QFileDialog>
#include <QStringList>

#include <fstream>
#include <dlfcn.h>

#include "ComplexDialogImpl.h"
#include "Vector.h"
#include "Globals.h"

using std::ofstream;

using VecMath::Vector;

namespace UI {
  namespace Dialogs {
    /** ComplexDialogImpl c'tor taking parameters for the parent ComplexDialog,
     *  which in turn inherited them from QDialog
     *  displays the dialog
     *  @param parent parent widget (NULL)
     *  @param f window flags                                                     
     */
    ComplexDialogImpl::ComplexDialogImpl (QWidget *parent): QDialog (parent) {
        setupUi(this);
        connect (okButton, SIGNAL(clicked()), this, SLOT(checkValidity()));
        connect (loadButton, SIGNAL(clicked()), this, SLOT(loadFunction()));
        descriptionLabel->hide();
        descriptionTextEdit->hide();
        if (layout()) layout()->setSizeConstraint(QLayout::SetFixedSize);
        show ();
    }

    /** Display  and load the selected DLL into current address space.
     * 
     *  Loads a dynamic library, which can be selected by the user on a QFileDialog.
     *  Calls PluginCreator::loadFunction(). See there.
     *  @return	success
     */
    bool ComplexDialogImpl::loadFunction() {
      return PluginCreator::loadFunction("complex", this);
    }


    /** Loads the dynamic library given by \p lib_name, if it exists and can be loaded.
     *  Then it checks whether a function named \c f() is present. If so, returns true.
     *  else borks with an error message.
     *  @param libName	filename for the selected DLL
     *  @return		success
     */
    bool ComplexDialogImpl::functionPresent(const QString &lib_name) {
      return PluginCreator::LoadFunctionHelper<Vector<4> (double, double)>::functionPresent(lib_name, this);
    }


    /** This function is called when the user clicks the OK button in the Function Dialog. Checks 
     *  whether all fields are filled in, whether the given function is valid C++ syntax, ie. 
     *  whether it compiles, and whether the compiled code links into a dynamic library.
     *  
     *  As a side effect, it generates this library.
     * 
     *  Finally, it checks whether the library can be loaded. If so, it accepts the input.
     * 
     *  Also, this function creates a directory structure "plugins/real" under the resource
     *  directory and changes the CWD to that folder for the duration of checkValidity ().
     * 
     *  The name for this function is chosen rather unfortunately, i guess.
     *  @return		success
     */
    bool ComplexDialogImpl::checkValidity() {
      if ((nameEdit->text().isEmpty()) || (WEdit->text().isEmpty())) {
        QMessageBox::warning (this, "Missing fields", "Please fill in all fields!");
        return false;
      }
      return PluginCreator::checkValidity("complex", nameEdit->text(), this);
    }


    /** write a C++ source file, containing the given function and some framework to
     *  make it compilable by g++ (there is currently no support for other compilers).
     *  the resulting file "<function-name>.C" defines the function f () and the
     *  function symbolic (), which returns the function in symbolic terms, not in
     *  C++ syntax.                                                               
     */
    void ComplexDialogImpl::writeSource () {
      ofstream SourceFile ((nameEdit->text().toStdString()+".C").c_str());

      SourceFile << "\
#include \"" << vector_include_file.toStdString() << "\"\n\
#include <complex>\n\
\n\
using namespace VecMath;\n\
using std::complex;\n\
\n\
extern \"C\" Vector<4> f (double, double);\n\
extern \"C\" const char *symbolic ();\n\
\n\
Vector<4> f (double u, double v) {\n\
    static Vector<4> F;\n\
    complex<double> z(u, v), w = " << WEdit->text().toStdString() << ";\n\
    F[0] = u;\n\
    F[1] = v;\n\
    F[2] = w.real();\n\
    F[3] = w.imag();\n\
\n\
    return F;\n\
}\n\
\n\
const char *symbolic () {\n\
    return \"" << WEdit->text().toStdString() << "\"; \n\
}\n";

      SourceFile.close ();
    }
  }
}
