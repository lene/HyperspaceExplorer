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
#include <stdexcept>
#include <cstdarg>
#include <cassert>

template <unsigned size, typename T> 
ArrayList<size, T>::ArrayList(): 
  _elements() { }
/** \param x The value all elements of \c this are initialized to.
 */
template <unsigned size, typename T> 
ArrayList<size, T>::ArrayList(const T &x): 
  _elements(std::make_pair(x, ArrayList<size-1, T>(x))) { }
/** \param head Value of the first element
 *  \param tail The rest of the elements
 */
template <unsigned size, typename T> 
ArrayList<size, T>::ArrayList(const T &head, const ArrayList<size-1, T> &tail): 
  _elements(std::make_pair(head, tail)) { }

template<unsigned size, typename T> 
ArrayList<size, T>::ArrayList(const T *vec):  
  _elements(std::make_pair(vec[0], ArrayList<size-1, T>(vec+1))) { }

template <unsigned size, typename T> 
const T &ArrayList<size, T>::head() const { 
  return _elements.first; 
}

template <unsigned size, typename T> 
T &ArrayList<size, T>::head() { 
  return _elements.first; 
}
     
template <unsigned size, typename T> 
const ArrayList<size-1, T> &ArrayList<size, T>::tail() const { 
  return _elements.second; 
}

template <unsigned size, typename T> 
ArrayList<size-1, T> &ArrayList<size, T>::tail() { 
  return _elements.second; 
}

/** \param i Index of the element accessed.
 */
template <unsigned size, typename T> 
T &ArrayList<size, T>::operator[](unsigned i) {
  assert(i < size);
  if (i == 0) return head();
  ArrayList<size-1, T> _tail = tail();
  return _tail.operator[](i-1);
}

/** \param i Index of the element accessed.
 */
template <unsigned size, typename T> 
const T &ArrayList<size, T>::operator[](unsigned i) const {
  assert(i < size); 
  if (i == 0) return head();
  return tail()[i-1];
}

template <unsigned size, typename T> 
ArrayList<size-1, T> ArrayList<size, T>::minusElement(unsigned i) const { 
  assert(i < size);
  if (i == 0) return tail();
  return ArrayList<size-1, T>(head(), tail().minusElement(i-1));
}

template <unsigned size, typename T> 
bool ArrayList<size, T>::contains (const T &x) const {
  if (head() == x) return true;
  return tail().contains(x);
}

template <unsigned size, typename T> 
std::string ArrayList<size, T>::toString() const {
  std::ostringstream o;
  o << _elements.first << ", " << _elements.second.toString();
  return o.str();
}

////////////////////////////////////////////////////////////////////////////////

template <typename T> 
ArrayList<1, T>::ArrayList() { }

template <typename T> 
ArrayList<1, T>::ArrayList(const T &x): element_(x) { }

template <typename T> 
ArrayList<1, T>::ArrayList(T x, ArrayList<0, T>): element_(x) { }

template<typename T> 
ArrayList<1, T>::ArrayList(const T *vec): element_(*vec) { }

template <typename T> 
const T &ArrayList<1, T>::head() const { 
  return element_;
}

template <typename T> 
T &ArrayList<1, T>::head() { 
  return element_;
}
     
template <typename T> 
ArrayList<0, T> ArrayList<1, T>::tail() const { 
  return ArrayList<0, T>();
}

/** \param i Index of the element accessed.
 */
template <typename T> 
T &ArrayList<1, T>::operator[](unsigned) {
  return head();
}

/** \param i Index of the element accessed.
 */
template <typename T> 
const T &ArrayList<1, T>::operator[](unsigned) const {
  return head();
}

template <typename T> 
ArrayList<0, T> ArrayList<1, T>::minusElement(unsigned) const {
  return tail();
}

template <typename T> 
bool ArrayList<1, T>::contains (const T &x) const {
  return head() == x;
}

template <typename T> 
std::string ArrayList<1, T>::toString() const {
  std::ostringstream o;
  o << element_;
  return o.str();
}

////////////////////////////////////////////////////////////////////////////////

template <typename T> 
ArrayList<0, T>::ArrayList() { }

template <typename T> 
ArrayList<0, T>::ArrayList(const T &) { }

template <typename T> 
std::string ArrayList<0, T>::toString() const {
  return "";
}

////////////////////////////////////////////////////////////////////////////////

template<unsigned size, typename T>
bool isPermutation(const ArrayList<size, T> &list1, const ArrayList<size, T> &list2) {
  for (unsigned i = 0; i < size; ++i) {
    if (list1.head() == list2[i] && 
        isPermutation(list1.tail(), list2.minusElement(i))) return true;
  }
  return false;
}

template<typename T>
bool isPermutation(const ArrayList<1, T> &list1, const ArrayList<1, T> &list2) {
  return list1.head() == list2.head();
}

////////////////////////////////////////////////////////////////////////////////

template<typename T> 
ArrayList<1, T> makeArrayList(const T &x0) {
  return ArrayList<1, T>(x0);
}
template<typename T> 
ArrayList<2, T> makeArrayList(const T &x0, const T &x1) {
  return ArrayList<2, T>(x0, makeArrayList(x1));
}
template<typename T> 
ArrayList<3, T> makeArrayList(const T &x0, const T &x1, const T &x2) {
  return ArrayList<3, T>(x0, makeArrayList(x1, x2));
}
template<typename T> 
ArrayList<4, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3) {
  return ArrayList<4, T>(x0, makeArrayList(x1, x2, x3));
}
template<typename T> 
ArrayList<5, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4) {
  return ArrayList<5, T>(x0, makeArrayList(x1, x2, x3, x4));
}
template<typename T> 
ArrayList<6, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                              const T &x5) {
  return ArrayList<6, T>(x0, makeArrayList(x1, x2, x3, x4, x5));
}
template<typename T> 
ArrayList<7, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                              const T &x5, const T &x6) {
  return ArrayList<7, T>(x0, makeArrayList(x1, x2, x3, x4, x5, x6));
}
template<typename T> 
ArrayList<8, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                              const T &x5, const T &x6, const T &x7) {
  return ArrayList<8, T>(x0, makeArrayList(x1, x2, x3, x4, x5, x6, x7));
}
template<typename T> 
ArrayList<9, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                              const T &x5, const T &x6, const T &x7, const T &x8) {
  return ArrayList<9, T>(x0, makeArrayList(x1, x2, x3, x4, x5, x6, x7, x8));
}
template<typename T> 
ArrayList<10, T> makeArrayList(const T &x0, const T &x1, const T &x2, const T &x3, const T &x4,
                               const T &x5, const T &x6, const T &x7, const T &x8, const T &x9) {
  return ArrayList<10, T>(x0, makeArrayList(x1, x2, x3, x4, x5, x6, x7, x8, x9));
}

#endif