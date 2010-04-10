/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
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
#ifndef ARRAYLIST_IMPL_H
#define ARRAYLIST_IMPL_H

#include "ArrayList.h"

#include <sstream>
#include <cstdarg>

template <unsigned size, typename T> ArrayList<size, T>::ArrayList(T x0) { 
  for (unsigned i = 0; i < size; ++i) {
    _elements[i] = x0;
  }
}

template <unsigned size, typename T> std::string ArrayList<size, T>::toString() const {
  std::ostringstream o;
  o << "[";
  for (unsigned i = 0; i < size-1; ++i) o << _elements[i] << ", ";
  o << _elements[size-1];
  o << "]";
  return o.str();
}

template <typename T> std::string ArrayList<1, T>::toString() const {
  std::ostringstream o;
  o << "[" << _elements[0] << "]";
  return o.str();
}

#endif