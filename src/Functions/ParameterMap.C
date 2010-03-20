#include "ParameterMap.h"

#include <QString>

/** \throw NonexistentParameterAccessed if \p name is not a key. */
FunctionParameter *ParameterMap::getParameter(const std::string &name) {
  ParameterMap::iterator it = findOrThrow(name);
  std::cerr << "getParameter(" << name << ")";
//  if (name == "string parameter") {
    std::string v = it->second->toString();
    std::cerr << v;
    for(unsigned i = 0; i < v.length();++i) std::cerr << ", " << int(v[i]);
//  }
  std::cerr  << std::endl;
  return it->second;
}

/** \throw NonexistentParameterAccessed if \p name is not a key. */
FunctionParameterValueBase* ParameterMap::getValue(const std::string& name) {
  std::cerr << "getValue(" << name << ")";
  if (name == "string parameter") {
    std::string v = getParameter(name)->value()->toString();
    std::cerr << v;
    for(unsigned i = 0; i < v.length();++i) std::cerr << ". " << int(v[i]);
  }
  std::cerr  << std::endl;
  return getParameter(name)->value();
}

std::string ParameterMap::toString() const {
  std::ostringstream o;
  o << "[\n";
  for (std::map<std::string, FunctionParameter *>::const_iterator i = begin();
       i != end(); ++i) {
//    std::cerr << "[" << i->first << "]: " << typeid(i->second).name() << " " << i->second << std::endl;
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
      std::string value = std::string(*(i->second));
      o << "(string)" << value;
      {
        o << " (";
        for(unsigned i = 0; i < value.length();++i) o << int(value[i]) << " ";
        o << ")";
      }
      o << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<5>)" << i->second->value()->operator VecMath::Rotation<5>() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<6>)" << i->second->value()->operator VecMath::Rotation<6>() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<7>)" << i->second->value()->operator VecMath::Rotation<7>() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<8>)" << i->second->value()->operator VecMath::Rotation<8>() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<9>)" << i->second->value()->operator VecMath::Rotation<9>() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(Rotation<10>)" << i->second->value()->operator VecMath::Rotation<10>() << std::endl;
      continue;
    } catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
  }
  o << "]" << std::endl << std::ends;

  return o.str();
}

/** \throw NonexistentParameterAccessed if \p name is not a key. */
ParameterMap::iterator ParameterMap::findOrThrow(const std::string& name) {
  std::map<std::string, FunctionParameter *>::iterator it = find(name);
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
