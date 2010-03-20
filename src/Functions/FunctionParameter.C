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


FunctionParameter::FunctionParameter(const std::string &name,
                                     const std::string &description):
    _name(name), _description(description), _value(), _defaultValue() { }

FunctionParameter::~FunctionParameter() { }

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

FunctionParameterValueBase *FunctionParameter::value() const {
    return _value.get();
}

FunctionParameterValueBase *FunctionParameter::defaultValue() const {
    return _defaultValue.get();
}

void FunctionParameter::setValue(const std::string &newValue) {
    if (value()) _value->setValue(newValue.c_str());
}

