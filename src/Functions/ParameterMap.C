#include "ParameterMap.h"

#include <QString>

/** \throw NonexistentParameterAccessed if \p name is not a key. */
FunctionParameter::parameter_ptr_type ParameterMap::getParameter(const std::string &name) {
  ParameterMap::iterator it = findOrThrow(name);
  return it->second;
}

/** \throw NonexistentParameterAccessed if \p name is not a key. */
FunctionParameter::value_ptr_type ParameterMap::getValue(const std::string& name) {
  return getParameter(name)->value();
}

std::string ParameterMap::toString() const {
  std::ostringstream o;
  o << "[\n";
  for (map_type::const_iterator i = begin();
       i != end(); ++i) {
    o << "    " << i->first << ": \t"
      << i->second->getName() << " = ";
    // try casting to every known type, only print if cast succeeds
    try {
      o << "(double)" << i->second->toDouble() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(unsigned)" << i->second->toUnsigned() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(int)" << i->second->toInt() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(string)" << i->second->toString() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<5>)" << i->second->value()->toRotation5() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<6>)" << i->second->value()->toRotation6() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<7>)" << i->second->value()->toRotation7() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<8>)" << i->second->value()->toRotation8() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<9>)" << i->second->value()->toRotation9() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<10>)" << i->second->value()->toRotation10() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
  }
  o << "]" << std::endl << std::ends;

  return o.str();
}

/** \throw NonexistentParameterAccessed if \p name is not a key. */
ParameterMap::iterator ParameterMap::findOrThrow(const std::string& name) {
  map_type::iterator it = find(name);
  if (it != end()) return it;
  throw ParameterMap::NonexistentParameterAccessed(name, *this);
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
