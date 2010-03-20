/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "FunctionParameterValue.h"

/// Specialization for type double
template<> FunctionParameterValue<double>::FunctionParameterValue(const double &_value):
        value(_value) {}

/// Specialization for type unsigned
template<> FunctionParameterValue<unsigned>::FunctionParameterValue(const unsigned &_value):
        value(_value) {}

/// Specialization for type int
template<> FunctionParameterValue<int>::FunctionParameterValue(const int &_value):
        value(_value) {}

/// Specialization for type string
template<> FunctionParameterValue<std::string>::FunctionParameterValue(const std::string &_value):
        value(_value) {}

/// Specialization for type VecMath::Rotation<5>
template<> FunctionParameterValue<VecMath::Rotation<5> >::FunctionParameterValue(
    const VecMath::Rotation<5> &_value):
        value(_value) {}

/// Specialization for type VecMath::Rotation<6>
template<> FunctionParameterValue<VecMath::Rotation<6> >::FunctionParameterValue(
    const VecMath::Rotation<6> &_value):
        value(_value) {}

/// Specialization for type VecMath::Rotation<7>
template<> FunctionParameterValue<VecMath::Rotation<7> >::FunctionParameterValue(
    const VecMath::Rotation<7> &_value):
        value(_value) {}

/// Specialization for type VecMath::Rotation<8>
template<> FunctionParameterValue<VecMath::Rotation<8> >::FunctionParameterValue(
    const VecMath::Rotation<8> &_value):
        value(_value) {}

/// Specialization for type VecMath::Rotation<9>
template<> FunctionParameterValue<VecMath::Rotation<9> >::FunctionParameterValue(
    const VecMath::Rotation<9> &_value):
        value(_value) {}

/// Specialization for type VecMath::Rotation<10>
template<> FunctionParameterValue<VecMath::Rotation<10> >::FunctionParameterValue(
    const VecMath::Rotation<10> &_value):
        value(_value) {}


/// Specialization for type double
template<> double FunctionParameterValue<double>::toDouble() { return value; }
/// Specialization for type unsigned
template<> unsigned FunctionParameterValue<unsigned>::toUnsigned() { return value; }
/// Specialization for type int
template<> int FunctionParameterValue<int>::toInt() { return value; }

/// Specialization for type VecMath::Rotation<5>
template<> FunctionParameterValue<VecMath::Rotation<5> >::operator VecMath::Rotation<5>() {
    return (VecMath::Rotation<5>)value;
}
/// Specialization for type VecMath::Rotation<5>
template<> FunctionParameterValue<VecMath::Rotation<5> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<5>)value;
}
/// Specialization for type VecMath::Rotation<6>
template<> FunctionParameterValue<VecMath::Rotation<6> >::operator VecMath::Rotation<6>() {
    return (VecMath::Rotation<6>)value;
}
/// Specialization for type VecMath::Rotation<6>
template<> FunctionParameterValue<VecMath::Rotation<6> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<6>)value;
}
/// Specialization for type VecMath::Rotation<7>
template<> FunctionParameterValue<VecMath::Rotation<7> >::operator VecMath::Rotation<7>() {
    return (VecMath::Rotation<7>)value;
}
/// Specialization for type VecMath::Rotation<7>
template<> FunctionParameterValue<VecMath::Rotation<7> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<7>)value;
}
/// Specialization for type VecMath::Rotation<8>
template<> FunctionParameterValue<VecMath::Rotation<8> >::operator VecMath::Rotation<8>() {
    return (VecMath::Rotation<8>)value;
}
/// Specialization for type VecMath::Rotation<8>
template<> FunctionParameterValue<VecMath::Rotation<8> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<8>)value;
}
/// Specialization for type VecMath::Rotation<9>
template<> FunctionParameterValue<VecMath::Rotation<9> >::operator VecMath::Rotation<9>() {
    return (VecMath::Rotation<9>)value;
}
/// Specialization for type VecMath::Rotation<9>
template<> FunctionParameterValue<VecMath::Rotation<9> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<9>)value;
}
/// Specialization for type VecMath::Rotation<10>
template<> FunctionParameterValue<VecMath::Rotation<10> >::operator VecMath::Rotation<10>() {
    return (VecMath::Rotation<10>)value;
}
/// Specialization for type VecMath::Rotation<10>
template<> FunctionParameterValue<VecMath::Rotation<10> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<10>)value;
}

/// Specialization for type double
template<>
    void FunctionParameterValue<double>::setValue(const char * _value) {
    value = atof(_value);
}

/// Specialization for type unsigned
template<>
    void FunctionParameterValue<unsigned>::setValue(const char * _value) {
    value = atoi(_value);
}

/// Specialization for type int
template<>
    void FunctionParameterValue<int>::setValue(const char * _value) {
    value = atoi(_value);
}

/// Specialization for type std::string
template<>
    void FunctionParameterValue<std::string>::setValue(const char * _value) {
    value = _value;
}

std::string rotationInputString(const char *_value) {
    std::string s(_value);
    if (!s.find('<') == s.npos) s = '<'+s;
    return s;
}

/// Specialization for type VecMath::Rotation<5>
template<>
    void FunctionParameterValue<VecMath::Rotation<5> >::setValue(
        const char * _value) {
    std::istringstream s(rotationInputString(_value));
    s >> value;
}

/// Specialization for type VecMath::Rotation<6>
template<>
    void FunctionParameterValue<VecMath::Rotation<6> >::setValue(
        const char * _value) {
    std::istringstream s(rotationInputString(_value));
    s >> value;
}

/// Specialization for type VecMath::Rotation<7>
template<>
    void FunctionParameterValue<VecMath::Rotation<7> >::setValue(
        const char * _value) {
    std::istringstream s(rotationInputString(_value));
    s >> value;
}

/// Specialization for type VecMath::Rotation<8>
template<>
    void FunctionParameterValue<VecMath::Rotation<8> >::setValue(
        const char * _value) {
    std::istringstream s(rotationInputString(_value));
    s >> value;
}

/// Specialization for type VecMath::Rotation<9>
template<>
    void FunctionParameterValue<VecMath::Rotation<9> >::setValue(
        const char * _value) {
    std::istringstream s(rotationInputString(_value));
    s >> value;
}

/// Specialization for type VecMath::Rotation<10>
template<>
    void FunctionParameterValue<VecMath::Rotation<10> >::setValue(
        const char * _value) {
    std::istringstream s(rotationInputString(_value));
    s >> value;
}
