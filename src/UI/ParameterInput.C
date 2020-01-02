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
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            try {
                unsigned temp = parameter.value()->toUnsigned();
                ParameterSpinBox *input = new ParameterSpinBox(parent);
                input->setMinimum(0);
                QString s;
                s.setNum(temp);
                input->setValue(s);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            try {
                int temp = parameter.value()->toInt();
                ParameterSpinBox *input = new ParameterSpinBox(parent);
                QString s;
                s.setNum(temp);
                input->setValue(s);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            try {
                std::string temp = parameter.value()->toString();
                ParameterLineEdit *input = new ParameterLineEdit(parent);
                input->setValue(temp.c_str());
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            try {
                /// return a ParameterInput which controls a Rotation<5>
                VecMath::Rotation<5> temp = parameter.toRotation5();
                ParameterRotationControl *input =
                        new ParameterRotationControl(&temp, parent);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            try {
                /// return a ParameterInput which controls a Rotation<6>
                VecMath::Rotation<6> temp = parameter.toRotation6();
                ParameterRotationControl *input =
                        new ParameterRotationControl(&temp, parent);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            try {
                /// return a ParameterInput which controls a Rotation<7>
                VecMath::Rotation<7> temp = parameter.toRotation7();
                ParameterRotationControl *input =
                        new ParameterRotationControl(&temp, parent);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            try {
                /// return a ParameterInput which controls a Rotation<8>
                VecMath::Rotation<8> temp = parameter.toRotation8();
                ParameterRotationControl *input =
                        new ParameterRotationControl(&temp, parent);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            try {
                /// return a ParameterInput which controls a Rotation<9>
                VecMath::Rotation<9> temp = parameter.toRotation9();
                ParameterRotationControl *input =
                        new ParameterRotationControl(&temp, parent);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            try {
                /// return a ParameterInput which controls a Rotation<10>
                VecMath::Rotation<10> temp = parameter.toRotation10();
                ParameterRotationControl *input =
                        new ParameterRotationControl(&temp, parent);
                return input;
            } catch (FunctionParameterValueBase::WrongParameterTypeException&) { }
            return 0;
        }

    }

}
