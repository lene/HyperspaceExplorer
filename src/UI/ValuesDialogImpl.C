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

#include <qmessagebox.h>
#include <qslider.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "ValuesDialogImpl.h"
#include "Displayable.h"
#include "Log.h"

namespace UI {
    namespace Dialogs {

        /// Set up the components of the dialog and displays it
        ValuesDialogImpl::ValuesDialogImpl(QWidget *parent):
            QDialog (parent) {
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
        void ValuesDialogImpl::setFunction(const std::shared_ptr< Displayable >&F) {
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
                dynamic_cast<QWidget *>(Parameter[i])->hide();
            }

            unsigned j = 0;
            for (ParameterMap::const_iterator it = parms.begin();
                it != parms.end(); ++it, ++j) {

                //  check whether the current parameter is a Rotation - just for kicks
                try {
                    VecMath::RotationBase dummy = it->second->value()->toRotationBase();
                    SingletonLog::Instance() << __PRETTY_FUNCTION__ << ": "
                            << it->second->getName() << " is a Rotation\n";
                } catch (FunctionParameterValueBase::WrongParameterTypeException e) {
                    SingletonLog::Instance() << __PRETTY_FUNCTION__ << ": "
                            << it->second->getName() << " is NOT a Rotation\n";
                }

                Parameter[j] = ParameterInputFactory::create(*it->second, this);
                //  Store the pointer to QWidget to avoid calling dynamic_cast<> over and over
                QWidget *ParameterInputAsWidget = dynamic_cast<QWidget *>(Parameter[j]);

                ParameterLayout[j]->addWidget(ParameterInputAsWidget);

                std::string name = it->second->getName();
                ParameterLabel[j]->setText(name.c_str());
                std::string description = it->second->getDescription();
                if (!description.empty()) {
                    ParameterLabel[j]->setToolTip(description.c_str());
                    ParameterInputAsWidget->setToolTip(description.c_str());
                } else {
                    ParameterLabel[j]->setToolTip("");
                    ParameterInputAsWidget->setToolTip("");
                }
                std::string value = it->second->value()->toString();
                if (!value.empty()) {
                    Parameter[j]->setValue(value.c_str());
                } else {
                    std::string defaultValue = it->second->defaultValue()->toString();
                    if (!defaultValue.empty()) {
                        Parameter[j]->setValue(defaultValue.c_str());
                    }
                }
                dynamic_cast<QWidget *>(Parameter[j])->show();
                ParameterLabel[j]->show();
            }
        }

        /// This function is called when the user clicks the "Apply" button
        void ValuesDialogImpl::accept () {
            for (unsigned i = 0; i < maxNumParameters; ++i) {
                std::string parameterName = ParameterLabel[i]->text().toStdString();
                try {
                  FunctionParameter::parameter_ptr_type parameter(parameters.getParameter(parameterName));
                  parameter->setValue(Parameter[i]->value().toStdString());
                } catch (const ParameterMap::NonexistentParameterAccessed &e) {
                  /// default parameter names in hidden fields of the dialog
                  /// \todo remove those fields instead of catching the exception
                }
            }
            emit ApplyChanges(parameters);
        }

        /// output for debugging purposes
        std::string ValuesDialogImpl::print () {
            std::ostringstream o;
            o << "ValuesDialogImpl::print():\n";
            for (unsigned i = 0; i < maxNumParameters; ++i)
                o << "Parameter[" << i << "]: " << Parameter[i]->value().toStdString() << "\t";
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
