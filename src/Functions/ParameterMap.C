/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#include "ParameterMap.h"

#include "Rotation.impl.h"

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
