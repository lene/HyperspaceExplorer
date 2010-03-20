//
// C++ Implementation: FunctionParameter
//
// Description: 
//
//
// Author: Lene Preuss <lene.preuss@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "FunctionParameter.h"


FunctionParameter::FunctionParameter(const std::string &_name,
                                     const std::string &_description):
    name(_name), description(_description), m_value(), m_defaultValue() { }

FunctionParameter::~FunctionParameter() { }

FunctionParameter::operator double() { return m_value->toDouble(); }
FunctionParameter::operator unsigned() { return m_value->toUnsigned(); }
FunctionParameter::operator int() { return m_value->toInt(); }
FunctionParameter::operator std::string() { return m_value->toString(); }

const std::string &FunctionParameter::getName() const { return name; }
void FunctionParameter::setName ( const std::string &_name ) { name = _name; }
const std::string &FunctionParameter::getDescription() const { return description; }
void FunctionParameter::setDescription (const std::string &_description) {
    description = _description;
}

FunctionParameterValueBase *FunctionParameter::value() const {
    return m_value.get();
}

FunctionParameterValueBase *FunctionParameter::defaultValue() const {
    return m_defaultValue.get();
}

void FunctionParameter::setValue(std::string _value) {
    if (value()) m_value->setValue(_value.c_str());
}

