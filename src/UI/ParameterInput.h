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

#ifndef UI_DIALOGSPARAMETERINPUT_H
#define UI_DIALOGSPARAMETERINPUT_H

#include <QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

#include "FunctionParameter.h"
#include "RotationControl.h"
#include "Rotation.h"

namespace UI {

    namespace Dialogs {

        /// Input controls for all types of FunctionParameter.
        /** This class defines the interface that all input controls for
         *  FunctionParameter must follow.
         *
         *  @author Helge Preuss <lene.preuss@gmail.com>
         */
        class ParameterInput {
            public:
                /// Returns the value of the FunctionParameter as entered in the Widget.
                virtual QString value() const = 0;
                /// Sets the value displayed in the widget.
                /** \param newValue The value of the FunctionParameter to display
                 *      converted to a QString, with the help of the toString() method.
                 */
                virtual void setValue(const QString &newValue) = 0;
        };

        /// Widget to edit a FunctionParameter of type \c string.
        class ParameterLineEdit: public ParameterInput, public QLineEdit {
            public:

                /// Constructs a ParameterLineEdit
                ParameterLineEdit(QWidget *parent = 0): QLineEdit(parent) { }

                virtual QString value() const { return QLineEdit::text(); }
                virtual void setValue(const QString &s) { QLineEdit::setText(s); }
        };

        /// Widget to edit a FunctionParameter of type \c int.
        class ParameterSpinBox: public ParameterInput, public QSpinBox {
            public:

                /// Constructs a ParameterSpinBox
                ParameterSpinBox(QWidget *parent = 0): QSpinBox(parent) { }

                virtual QString value() const {
                    return QString::number(QSpinBox::value());
                }
                virtual void setValue(const QString &s) {
                    QSpinBox::setValue(s.toInt());
                }
        };

        /// Widget to edit a FunctionParameter of type \c double.
        class ParameterDoubleSpinBox: public ParameterInput, public QDoubleSpinBox {
            public:

                /// Constructs a ParameterDoubleSpinBox
                ParameterDoubleSpinBox(QWidget *parent = 0): QDoubleSpinBox(parent) { }

                virtual QString value() const {
                    return QString::number(QDoubleSpinBox::value());
                }
                virtual void setValue(const QString &s) {
                    QDoubleSpinBox::setValue(s.toDouble());
                }
        };

        /// Widget to edit a FunctionParameter of type \c Rotation.
        class ParameterRotationControl: public ParameterInput, public RotationControl {
            public:

                /// Constructs a ParameterRotationControl from a given Rotation
                ParameterRotationControl(VecMath::RotationBase *rot,
                                         QWidget *parent = 0):
                    RotationControl(rot, parent) { }

                /** \todo Implement! */
                virtual QString value() const {
                    throw NotYetImplementedException(
                            "ParameterRotationControl::value()");
                    return QString();
//                    return QString::number(RotationControl::value());
                }

                /** \todo Implement! */
                virtual void setValue(const QString &) {
                    throw NotYetImplementedException(
                            "ParameterRotationControl::setValue()");
//                    RotationControl::setValue(s.toDouble());
                }
        };

        /// Factory class to create a ParameterInput based on the type of a FunctionParameter.
        class ParameterInputFactory {
            public:
                static ParameterInput *create(const FunctionParameter &,
                                              QWidget * = 0);
        };

    }

}

#endif
