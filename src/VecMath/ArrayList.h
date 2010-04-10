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

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <string>

template <unsigned size, typename T> class ArrayList {
  public:
    ArrayList(): _elements() { }
    ArrayList(T x0);
    
    T head() const { return _elements[0]; }
    ArrayList<size-1, T> tail();

    T &operator[](unsigned i) { return _elements[i]; }
    const T &operator[](unsigned i) const { return _elements[i]; }
    
    std::string toString() const;
    
  private:
    ArrayList(T *elements): _elements(elements) { }
    T _elements[size];
};

template <typename T> class ArrayList<1, T> {
  public:
    ArrayList(): _elements() { }
    ArrayList(T x0) { _elements[0] = x0; }
    
    T head() const { return _elements[0]; }
    
    T &operator[](unsigned i) { return _elements[i]; }
    const T &operator[](unsigned i) const { return _elements[i]; }

    std::string toString() const;

  private:
    ArrayList(T *elements): _elements(elements) { }
    T _elements[1];
};

#include "ArrayList.impl.h"

#endif // ARRAYLIST_H
