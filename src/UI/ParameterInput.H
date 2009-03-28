#ifndef UI_DIALOGSPARAMETERINPUT_H
#define UI_DIALOGSPARAMETERINPUT_H

#include <QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>

#include "FunctionParameter.H"
#include "RotationControl.H"
#include "Rotation.H"

namespace UI {

    namespace Dialogs {

        /// Widget with input controls for all types of FunctionParameter
        /**
                @author Helge Preuss <scout@hyperspace-travel.de>
        */
        class ParameterInput {
            public:
                virtual QString value() const = 0;
                virtual void setValue(const QString &) = 0;
        };

        class ParameterLineEdit: public ParameterInput, public QLineEdit {
            public:

                ParameterLineEdit(QWidget *parent = 0): QLineEdit(parent) { }

                virtual QString value() const { return QLineEdit::text(); }
                virtual void setValue(const QString &s) { QLineEdit::setText(s); }
        };

        class ParameterSpinBox: public ParameterInput, public QSpinBox {
            public:

                ParameterSpinBox(QWidget *parent = 0): QSpinBox(parent) { }

                virtual QString value() const {
                    return QString::number(QSpinBox::value());
                }
                virtual void setValue(const QString &s) {
                    QSpinBox::setValue(s.toInt());
                }
        };

        class ParameterDoubleSpinBox: public ParameterInput, public QDoubleSpinBox {
            public:

                ParameterDoubleSpinBox(QWidget *parent = 0): QDoubleSpinBox(parent) { }

                virtual QString value() const {
                    return QString::number(QDoubleSpinBox::value());
                }
                virtual void setValue(const QString &s) {
                    QDoubleSpinBox::setValue(s.toDouble());
                }
        };

        class ParameterRotationControl: public ParameterInput, public RotationControl {
            public:

                ParameterRotationControl(VecMath::RotationBase *rot,
                                         QWidget *parent = 0):
                    RotationControl(rot, parent) { }

                virtual QString value() const {
                    throw NotYetImplementedException(
                            "ParameterRotationControl::value()");
                    return QString();
//                    return QString::number(RotationControl::value());
                }
                virtual void setValue(const QString &) {
                    throw NotYetImplementedException(
                            "ParameterRotationControl::setValue()");
//                    RotationControl::setValue(s.toDouble());
                }
        };

        class ParameterInputFactory {
            public:
                static ParameterInput *create(const FunctionParameter &,
                                              QWidget * = 0);
        };

    }

}

#endif
