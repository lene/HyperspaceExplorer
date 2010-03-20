///
/// C++ Implementation: ColorManager
///
/// Description:
///
///
/// \author Helge Preuss <lene.preuss@gmail.com>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#include <string>

#include "ParameterInput.h"
#include "Rotation.h"

namespace UI {

    namespace Dialogs {

        ParameterInput *ParameterInputFactory::create(const FunctionParameter &parameter,
                                                      QWidget *parent) {
            try {
                double temp = parameter.value()->toDouble();
                ParameterDoubleSpinBox *input = new ParameterDoubleSpinBox(parent);
                QString s;
                s.setNum(temp);
                input->setValue(s);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                unsigned temp = parameter.value()->toUnsigned();
                ParameterSpinBox *input = new ParameterSpinBox(parent);
                input->setMinimum(0);
                QString s;
                s.setNum(temp);
                input->setValue(s);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                int temp = parameter.value()->toInt();
                ParameterSpinBox *input = new ParameterSpinBox(parent);
                QString s;
                s.setNum(temp);
                input->setValue(s);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                std::string temp = parameter.value()->toString();
                ParameterLineEdit *input = new ParameterLineEdit(parent);
                input->setValue(temp.c_str());
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<5>
                VecMath::Rotation<5> temp = parameter.toRotation5();
                ParameterRotationControl *input =
                        new ParameterRotationControl(&temp, parent);
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<6>
                VecMath::Rotation<6> temp = parameter.toRotation6();
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<7>
                VecMath::Rotation<7> temp = parameter.toRotation7();
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<8>
                VecMath::Rotation<8> temp = parameter.toRotation8();
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<9>
                VecMath::Rotation<9> temp = parameter.toRotation9();
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<10>
                VecMath::Rotation<10> temp = parameter.toRotation10();
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }

        }

    }

}
