
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:       helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)


#include <qmessagebox.h>
#include <qslider.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "ValuesDialogImpl.H"
#include "Function.H"
#include "Log.H"

namespace UI {
    namespace Dialogs {

        /// Set up the components of the dialog and displays it
        ValuesDialogImpl::ValuesDialogImpl(QWidget *parent, Qt::WFlags f) :
            QDialog (parent, f) {
            setupUi(this);

            Steps[0]->setText (QString::number (Slider[0]->value ()));
            Steps[1]->setText (QString::number (Slider[1]->value ()));
            Steps[2]->setText (QString::number (Slider[2]->value ()));

            if (layout()) layout()->setSizeConstraint(QLayout::SetFixedSize);

            show ();
        }

        /// Adjust the display according to the Function whose Parameters are controlled
        /** \li Sets the internal map of parameters to the parameters the Function
        *      expects and adjusts input elements accordingly
        *  \li Shows as many sliders to adjust the size of the grid the function is
        *      evaluated on, as the definition space of the function has dimensions
        *  \li Only displays labels for the parts of the dialog which are shown      */
        void ValuesDialogImpl::setFunction(const std::auto_ptr<Function> &F) {
            setParameters(F->getParameters());

            for (unsigned i = 0; i < F->getDefinitionSpaceDimensions(); ++i) {
                if (Label[i]) Label[i]->show();
                if (Slider[i]) Slider[i]->show();
                if (Steps[i]) Steps[i]->show();
                if (MinLabel[i]) MinLabel[i]->show();
                if (Min[i]) Min[i]->show();
                if (MaxLabel[i]) MaxLabel[i]->show();
                if (Max[i]) Max[i]->show();
            }
            for (unsigned i = F->getDefinitionSpaceDimensions();
                i < maxNumDimensions; ++i) {
                if (Label[i]) Label[i]->hide();
                if (Slider[i]) Slider[i]->hide();
                if (Steps[i]) Steps[i]->hide();
                if (MinLabel[i]) MinLabel[i]->hide();
                if (Min[i]) Min[i]->hide();
                if (MaxLabel[i]) MaxLabel[i]->hide();
                if (Max[i]) Max[i]->hide();
            }

            gridLabel->setVisible(F->getDefinitionSpaceDimensions() > 0);
            functionLabel->setVisible(F->getNumParameters() > 0);
        }

        /// Adjust the displayed parameter fields to the parameters the function needs
        /** \li Sets the internal map of parameters to the parameters the Function
         *      expects
         *  \li Shows input fields for as many parameters as necessary
         *  \li Sets the text on these fields to the parameter's name, the tool tip to
         *      its optional description and the value to its value
         */
        void ValuesDialogImpl::setParameters(const ParameterMap &parms) {
            parameters = parms;

            for (unsigned i = 0; i < maxNumParameters; i++) {
                ParameterLabel[i]->hide();
                Parameter[i]->hide();
            }

            unsigned j = 0;
            for (ParameterMap::const_iterator it = parms.begin();
                it != parms.end(); ++it, ++j) {

                //  check whether the current parameter is a Rotation - just for kicks
                try {
                    VecMath::RotationBase dummy = *(it->second->value());
                    SingletonLog::Instance() << __PRETTY_FUNCTION__ << ": "
                            << it->second->getName() << " is a Rotation\n";
                } catch (FunctionParameterValueBase::WrongParameterTypeException e) {
                    SingletonLog::Instance() << __PRETTY_FUNCTION__ << ": "
                            << it->second->getName() << " is NOT a Rotation\n";
                }

#               ifdef USE_PARAMETER_INPUT
                Parameter[j] = ParameterInputFactory::create(*it->second, this);
#               endif

                std::string name = it->second->getName();
                ParameterLabel[j]->setText(name.c_str());
                std::string description = it->second->getDescription();
                if (!description.empty()) {
                    ParameterLabel[j]->setToolTip(description.c_str());
                    Parameter[j]->setToolTip(description.c_str());
                } else {
                    ParameterLabel[j]->setToolTip("");
                    Parameter[j]->setToolTip("");
                }
                std::string value = it->second->value()->toString();
                if (!value.empty()) {
                    Parameter[j]->setText(value.c_str());
                } else {
                    std::string defaultValue = it->second->defaultValue()->toString();
                    if (!defaultValue.empty()) {
                        Parameter[j]->setText(defaultValue.c_str());
                    }
                }
                Parameter[j]->show();
                ParameterLabel[j]->show();
            }
        }

        /// This function is called when the user clicks the "Apply" button
        void ValuesDialogImpl::accept () {
            for (unsigned i = 0; i < maxNumParameters; ++i) {
                std::string parameterName = ParameterLabel[i]->text().toStdString();
                ParameterMap::iterator it = parameters.find(parameterName);
                if (it != parameters.end()) {
                    it->second->setValue(Parameter[i]->text().toStdString());
                }
            }
            emit ApplyChanges(parameters);
        }

        /// output for debugging purposes
        std::string ValuesDialogImpl::print () {
            std::ostringstream o;
            o << "ValuesDialogImpl::print():\n";
            for (unsigned i = 0; i < maxNumParameters; ++i)
                o << "Parameter[" << i << "]: " << Parameter[i]->text ().toStdString() << "\t";
            o << std::endl;
            for (unsigned i = 0; i < maxNumDimensions; ++i)
                o << (char)('T'+i) << "min: " << Min[i]->text ().toStdString() << "\t"
                << (char)('T'+i) << "max: " << Max[i]->text ().toStdString() << "\t"
                << "d"<< (char)('T'+i) <<"  : " << dt () << "\n"; // !!! nyi!
            o << std::ends;

            return o.str();
        }
    }
}
