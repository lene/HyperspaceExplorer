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

