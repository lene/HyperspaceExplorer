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

double FunctionParameter::toDouble() const { return m_value->toDouble(); }

unsigned int FunctionParameter::toUnsigned() const { return m_value->toUnsigned(); }

int FunctionParameter::toInt() const { return m_value->toInt(); }

std::string FunctionParameter::toString() const { return m_value->toString(); }

VecMath::Rotation< 5 > FunctionParameter::toRotation5() const { return m_value->toRotation5(); } 

VecMath::Rotation< 6 > FunctionParameter::toRotation6() const { return m_value->toRotation6(); } 

VecMath::Rotation< 7 > FunctionParameter::toRotation7() const { return m_value->toRotation7(); } 

VecMath::Rotation< 8 > FunctionParameter::toRotation8() const { return m_value->toRotation8(); } 

VecMath::Rotation< 9 > FunctionParameter::toRotation9() const { return m_value->toRotation9(); } 

VecMath::Rotation< 10 > FunctionParameter::toRotation10() const { return m_value->toRotation10(); } 

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

