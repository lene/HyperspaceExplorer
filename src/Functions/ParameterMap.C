#include "ParameterMap.h"

#include <QString>

FunctionParameter *ParameterMap::getParameter(const std::string &name) {
  ParameterMap::iterator it = findOrThrow(name);
  return it->second;
}

FunctionParameterValueBase* ParameterMap::getValue(const std::string& name) {
  return getParameter(name)->value();
}

template<> void ParameterMap::set(const std::string &name, const double &value) {
  getParameter(name)->setValue(QString::number(value).toStdString()); 
}

template<> void ParameterMap::set(const std::string &name, const unsigned &value) {
  getParameter(name)->setValue(QString::number(value).toStdString()); 
}

template<> void ParameterMap::set(const std::string &name, const int &value) {
  getParameter(name)->setValue(QString::number(value).toStdString()); 
}

template<> void ParameterMap::set(const std::string &name, const std::string &value) {
  getParameter(name)->setValue(value);
}

std::string ParameterMap::print() const {    
  std::ostringstream o;
  o << "[\n";
  for (std::map<std::string, FunctionParameter *>::const_iterator i = begin();
       i != end(); ++i) {
    o << "    " << i->first << ": \t"
      << i->second->getName() << " = ";
    // try casting to every known type, only print if cast succeeds
    try {
      o << "(double)" << double(*(i->second)) << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(unsigned)" << unsigned(*(i->second)) << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(int)" << int(*(i->second)) << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(string)" << std::string(*(i->second)) << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<5>)" << i->second->value()->operator VecMath::Rotation<5>();
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<6>)" << i->second->value()->operator VecMath::Rotation<6>();
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<7>)" << i->second->value()->operator VecMath::Rotation<7>();
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<8>)" << i->second->value()->operator VecMath::Rotation<8>();
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<9>)" << i->second->value()->operator VecMath::Rotation<9>();
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<10>)" << i->second->value()->operator VecMath::Rotation<10>();
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
  }
  o << "]" << std::endl << std::ends;

  return o.str();
}

ParameterMap::iterator ParameterMap::findOrThrow(const std::string& name) {
  std::map<std::string, FunctionParameter *>::iterator it = find(name);
  if (it != end()) return it;
  throw ParameterMap::NonexistentParameterAccessed(name, *this);
}