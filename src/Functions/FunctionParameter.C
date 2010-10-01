/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2008-2010  Lene Preuss <lene.preuss@gmail.com>

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

#include "FunctionParameter.h"


FunctionParameter::FunctionParameter(const std::string &name,
                                     const std::string &description):
    _name(name), _description(description), _value(), _defaultValue() { }

double FunctionParameter::toDouble() const { return _value->toDouble(); }

unsigned int FunctionParameter::toUnsigned() const { return _value->toUnsigned(); }

int FunctionParameter::toInt() const { return _value->toInt(); }

std::string FunctionParameter::toString() const { return _value->toString(); }

VecMath::Rotation< 5 > FunctionParameter::toRotation5() const { return _value->toRotation5(); }

VecMath::Rotation< 6 > FunctionParameter::toRotation6() const { return _value->toRotation6(); }

VecMath::Rotation< 7 > FunctionParameter::toRotation7() const { return _value->toRotation7(); }

VecMath::Rotation< 8 > FunctionParameter::toRotation8() const { return _value->toRotation8(); }

VecMath::Rotation< 9 > FunctionParameter::toRotation9() const { return _value->toRotation9(); }

VecMath::Rotation< 10 > FunctionParameter::toRotation10() const { return _value->toRotation10(); }

const std::string &FunctionParameter::getName() const { return _name; }

void FunctionParameter::setName ( const std::string &name ) { _name = name; }

const std::string &FunctionParameter::getDescription() const { return _description; }

void FunctionParameter::setDescription (const std::string &description) {
    _description = description;
}

/** Requires a pointer created by FunctionParameterFactory::createParameterWithValue().
 *  \todo Can't I call createParameterWithValue() from inside
 *        setValue()?
 */
void FunctionParameter::setValue(FunctionParameter::value_ptr_type value) {
  _value = value;
}

void FunctionParameter::setValue(const std::string &newValue) {
    if (value()) _value->setValue(newValue.c_str());
}

/** Requires a pointer created by FunctionParameterFactory::createParameterWithDefault().
 *  \todo Can't I call createParameterWithDefault() from inside
 *        setDefaultValue()?
 */
void FunctionParameter::setDefaultValue(FunctionParameter::value_ptr_type defaultValue) {
  _defaultValue = defaultValue;
}

FunctionParameter::value_ptr_type FunctionParameter::value() const {
    return _value;
}

FunctionParameter::value_ptr_type FunctionParameter::defaultValue() const {
    return _defaultValue;
}
