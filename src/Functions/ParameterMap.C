#include "ParameterMap.h"

FunctionParameter *ParameterMap::operator[](const std::string &_name) {
  if (find(_name) == end()) {
    throw ParameterMap::NonexistentParameterAccessed(_name);
  }
  return std::map<std::string, FunctionParameter *>::operator[](_name);
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
    }  catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(unsigned)" << unsigned(*(i->second)) << std::endl;
    }  catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(int)" << int(*(i->second)) << std::endl;
    }  catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
    try {
      o << "(string)" << std::string(*(i->second)) << std::endl;
    }  catch (FunctionParameterValueBase::WrongParameterTypeException &e) { }
  }
  o << "]" << std::endl << std::ends;

  return o.str();
}
