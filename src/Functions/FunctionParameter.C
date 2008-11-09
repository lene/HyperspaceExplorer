//
// C++ Implementation: FunctionParameter
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "FunctionParameter.H"

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
template<> FunctionParameterValue<double>::operator double() {
    return (double)value;
}
/// Specialization for type unsigned
template<> FunctionParameterValue<unsigned>::operator unsigned() {
    return (unsigned)value;
}
/// Specialization for type int
template<> FunctionParameterValue<int>::operator int() {
    return (int)value;
}
/// Specialization for type std::string
template<> FunctionParameterValue<std::string>::operator std::string() {
    return (std::string)value;
}

/// Specialization for type VecMath::Rotation<5>
template<> FunctionParameterValue<VecMath::Rotation<5> >::operator VecMath::Rotation<5>() {
    return (VecMath::Rotation<5>)value;
}
template<> FunctionParameterValue<VecMath::Rotation<5> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<5>)value;
}
/// Specialization for type VecMath::Rotation<6>
template<> FunctionParameterValue<VecMath::Rotation<6> >::operator VecMath::Rotation<6>() {
    return (VecMath::Rotation<6>)value;
}
template<> FunctionParameterValue<VecMath::Rotation<6> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<6>)value;
}
/// Specialization for type VecMath::Rotation<7>
template<> FunctionParameterValue<VecMath::Rotation<7> >::operator VecMath::Rotation<7>() {
    return (VecMath::Rotation<7>)value;
}
template<> FunctionParameterValue<VecMath::Rotation<7> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<7>)value;
}
/// Specialization for type VecMath::Rotation<8>
template<> FunctionParameterValue<VecMath::Rotation<8> >::operator VecMath::Rotation<8>() {
    return (VecMath::Rotation<8>)value;
}
template<> FunctionParameterValue<VecMath::Rotation<8> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<8>)value;
}
/// Specialization for type VecMath::Rotation<9>
template<> FunctionParameterValue<VecMath::Rotation<9> >::operator VecMath::Rotation<9>() {
    return (VecMath::Rotation<9>)value;
}
template<> FunctionParameterValue<VecMath::Rotation<9> >::operator VecMath::RotationBase() {
    return (VecMath::Rotation<9>)value;
}
/// Specialization for type VecMath::Rotation<10>
template<> FunctionParameterValue<VecMath::Rotation<10> >::operator VecMath::Rotation<10>() {
    return (VecMath::Rotation<10>)value;
}
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

/// Specialization for type VecMath::Rotation<5>
template<>
    void FunctionParameterValue<VecMath::Rotation<5> >::setValue(
        const char * _value) {
    std::string s(_value);
    if (!s.find('<') == s.npos) s = '<'+s;
    std::istringstream i(s);
    i >> value;
}

/// Specialization for type VecMath::Rotation<6>
template<>
    void FunctionParameterValue<VecMath::Rotation<6> >::setValue(
        const char * _value) {
    std::string s(_value);
    if (!s.find('<') == s.npos) s = '<'+s;
    std::istringstream i(s);
    i >> value;
}

/// Specialization for type VecMath::Rotation<7>
template<>
    void FunctionParameterValue<VecMath::Rotation<7> >::setValue(
        const char * _value) {
    std::string s(_value);
    if (!s.find('<') == s.npos) s = '<'+s;
    std::istringstream i(s);
    i >> value;
}

/// Specialization for type VecMath::Rotation<8>
template<>
    void FunctionParameterValue<VecMath::Rotation<8> >::setValue(
        const char * _value) {
    std::string s(_value);
    if (!s.find('<') == s.npos) s = '<'+s;
    std::istringstream i(s);
    i >> value;
}

/// Specialization for type VecMath::Rotation<9>
template<>
    void FunctionParameterValue<VecMath::Rotation<9> >::setValue(
        const char * _value) {
    std::string s(_value);
    if (!s.find('<') == s.npos) s = '<'+s;
    std::istringstream i(s);
    i >> value;
}

/// Specialization for type VecMath::Rotation<10>
template<>
    void FunctionParameterValue<VecMath::Rotation<10> >::setValue(
        const char * _value) {
    std::string s(_value);
    if (!s.find('<') == s.npos) s = '<'+s;
    std::istringstream i(s);
    i >> value;
}

FunctionParameter::FunctionParameter(const std::string &_name,
                                     const std::string &_description):
    pImpl(new Impl( _name, _description )) {}

FunctionParameter::~FunctionParameter() { delete pImpl; }

FunctionParameter::operator double() { return double(*(pImpl->value)); }
FunctionParameter::operator unsigned() { return (unsigned)(*(pImpl->value)); }
FunctionParameter::operator int() { return (int)(*(pImpl->value)); }
FunctionParameter::operator std::string() { return (std::string)(*(pImpl->value)); }

const std::string &FunctionParameter::getName() const { return pImpl->name; }
void FunctionParameter::setName ( const std::string &_name ) { pImpl->name = _name; }
const std::string &FunctionParameter::getDescription() const { return pImpl->description; }
void FunctionParameter::setDescription (const std::string &_description) {
    pImpl->description = _description;
}

FunctionParameterValueBase *FunctionParameter::value() const {
    return pImpl->value.get();
}

FunctionParameterValueBase *FunctionParameter::defaultValue() const {
    return pImpl->defaultValue.get();
}

void FunctionParameter::setValue(std::string _value) {
    if (!pImpl->value.get()) {
#       if 0
            pImpl->value = std::auto_ptr<FunctionParameterValueBase>(
            new FunctionParameterValueBase(*pImpl->defaultValue));
#       endif
    } else {
        pImpl->value->setValue(_value.c_str());
    }
}

