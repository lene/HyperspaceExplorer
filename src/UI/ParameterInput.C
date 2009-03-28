///
/// C++ Implementation: ColorManager
///
/// Description:
///
///
/// \author Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#include <string>

#include "ParameterInput.H"
#include "Rotation.H"

namespace UI {

    namespace Dialogs {

        ParameterInput *ParameterInputFactory::create(const FunctionParameter &parameter,
                                                      QWidget *parent) {
            try {
                double temp = *(parameter.value());
                ParameterDoubleSpinBox *input = new ParameterDoubleSpinBox(parent);
                QString s;
                s.setNum(temp);
                input->setValue(s);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                unsigned temp = *(parameter.value());
                ParameterSpinBox *input = new ParameterSpinBox(parent);
                input->setMinimum(0);
                QString s;
                s.setNum(temp);
                input->setValue(s);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                int temp = *(parameter.value());
                ParameterSpinBox *input = new ParameterSpinBox(parent);
                QString s;
                s.setNum(temp);
                input->setValue(s);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                std::string temp = *(parameter.value());
                ParameterLineEdit *input = new ParameterLineEdit(parent);
                input->setValue(temp.c_str());
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<5>
                VecMath::Rotation<5> temp = *(parameter.value());
                ParameterRotationControl *input =
                        new ParameterRotationControl(&temp, parent);
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<5>
                VecMath::Rotation<6> temp = *(parameter.value());
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<5>
                VecMath::Rotation<7> temp = *(parameter.value());
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<5>
                VecMath::Rotation<8> temp = *(parameter.value());
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<5>
                VecMath::Rotation<9> temp = *(parameter.value());
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }
            try {
                /// return a ParameterInput which controls a Rotation<5>
                VecMath::Rotation<10> temp = *(parameter.value());
            } catch (FunctionParameterValueBase::WrongParameterTypeException e) { }


        }

    }

}
