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
#include <stdexcept>

/** \param x The value all elements of \c this are initialized to.
 */
template <unsigned size, typename T> ArrayList<size, T>::ArrayList(const T &x): _elements() {
  _elements.first = x;
  _elements.second = ArrayList<size-1, T>(x);
}

/** \param i Index of the element accessed. No boundary checking is performed.
 */
template <unsigned size, typename T> T &ArrayList<size, T>::operator[](unsigned i) {
    if (i == 0) return head();
    return tail()[i-1];
}

/** \param i Index of the element accessed. No boundary checking is performed.
 */
template <unsigned size, typename T> T ArrayList<size, T>::operator[](unsigned i) const {
    if (i == 0) return head();
    return tail()[i-1];
}

template <unsigned size, typename T> std::string ArrayList<size, T>::toString() const {
  std::ostringstream o;
  o << _elements.first << ", " << _elements.second.toString();
  return o.str();
}

template <typename T> std::string ArrayList<0, T>::toString() const {
  return "";
}

#endif