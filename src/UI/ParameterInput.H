#ifndef UI_DIALOGSPARAMETERINPUT_H
#define UI_DIALOGSPARAMETERINPUT_H

#include <QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>

#include "FunctionParameter.H"

namespace UI {

    namespace Dialogs {

        /// Widget with input controls for all types of FunctionParameter
        /**
                @author Helge Preuss <scout@hyperspace-travel.de>
        */
        class ParameterInput : public QWidget {
            public:

                ParameterInput(QWidget *parent = 0, Qt::WindowFlags f = 0);

                ~ParameterInput();

                virtual QString text() const = 0;
                virtual void setText(const QString &) = 0;
        };

        class ParameterLineEdit: public ParameterInput, public QLineEdit {
            public:

                ParameterLineEdit(QWidget *parent = 0, Qt::WindowFlags f = 0):
                        ParameterInput(parent, f) { }

                virtual QString text() const { return QLineEdit::text(); }
                virtual void setText(const QString &s) { QLineEdit::setText(s); }
        };

        class ParameterSpinBox: public ParameterInput, public QSpinBox {
            public:

                ParameterSpinBox(QWidget *parent = 0, Qt::WindowFlags f = 0):
                    ParameterInput(parent, f) { }

                virtual QString text() const { return QString::number(QSpinBox::value()); }
                virtual void setText(const QString &s) {
                    QSpinBox::setValue(s.toInt()); }
        };

        class ParameterInputFactory {
            public:
                static ParameterInput *create(const FunctionParameter &,
                                              QWidget * = 0);
        };

    }

}

#endif
