/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2009-2010  Lene Preuss <lene.preuss@gmail.com>

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

#include "MultiDimensionalVector.h"

#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>

namespace VecMath {

template <typename T, unsigned D>
MultiDimensionalVector<T, D>::MultiDimensionalVector(): _data() { }

template <typename T, unsigned D>
MultiDimensionalVector<T, D>::MultiDimensionalVector(unsigned n): _data(n) { }

template <typename T, unsigned D>
MultiDimensionalVector<T, D>::MultiDimensionalVector(
    typename std::vector<MultiDimensionalVector<T, D-1> >::iterator first,
    typename std::vector<MultiDimensionalVector<T, D-1> >::iterator last):
  MultiDimensionalVector<T, D-1>(),
  _data(first, last) { }

template <typename T, unsigned D>
MultiDimensionalVector<T, D>::MultiDimensionalVector(const MultiDimensionalVector<T, D> &v):
  MultiDimensionalVector<T, D-1>(),
  _data(v.data()) { }

template <typename T, unsigned D>
typename MultiDimensionalVector<T, D>::iterator
MultiDimensionalVector<T, D>::begin() {
  return data().begin();
}

template <typename T, unsigned D>
typename MultiDimensionalVector<T, D>::iterator
MultiDimensionalVector<T, D>::end() {
  return data().end();
}

template <typename T, unsigned D>
typename MultiDimensionalVector<T, D>::const_iterator
MultiDimensionalVector<T, D>::begin() const {
  return data().begin();
}

template <typename T, unsigned D>
typename MultiDimensionalVector<T, D>::const_iterator
MultiDimensionalVector<T, D>::end() const {
  return data().end();
}

/** \param x Data to be added */
template <typename T, unsigned D>
void MultiDimensionalVector<T, D>::push_back(const MultiDimensionalVector<T, D-1> &x) {
  data().push_back(x);
}

template <typename T, unsigned D>
MultiDimensionalVector<T, D-1> &MultiDimensionalVector<T, D>::back() {
    return data().back();
}
      
template <typename T, unsigned D>
const MultiDimensionalVector<T, D-1> &MultiDimensionalVector<T, D>::back() const {
    return data().back();
}

/** \param position Iterator pointing to element to be erased
 *  \return An iterator pointing to the next element (or end())
 */
template <typename T, unsigned D>
typename MultiDimensionalVector<T, D>::iterator
MultiDimensionalVector<T, D>::erase(iterator position) {
  return data().erase(position);
}

/** \param first Iterator pointing to first element to be erased
 *  \param last Iterator pointing to one past the last element to be erased.
 *  \return An iterator pointing to the next element (or end())
 */
template <typename T, unsigned D>
typename MultiDimensionalVector<T, D>::iterator
MultiDimensionalVector<T, D>::erase(iterator first, iterator last) {
  return data().erase(first, last);
}

/** \param i The index of the element for which data should be accessed
 *  \return Read/write reference to data.
 */
template <typename T, unsigned D>
MultiDimensionalVector<T, D-1> &MultiDimensionalVector<T, D>::operator [] (unsigned i) {
  return data()[i];
}

/** \param i The index of the element for which data should be accessed
 *  \return Read-only (constant) reference to data.
 */
template <typename T, unsigned D>
const MultiDimensionalVector<T, D-1> &MultiDimensionalVector<T, D>::operator [] (unsigned i) const {
  return data()[i];
}

template <typename T, unsigned D>
unsigned MultiDimensionalVector<T, D>::size() const {
  return data().size();
}

template <typename T, unsigned D>
unsigned MultiDimensionalVector<T, D>::empty() const {
  return data().empty();
}

template <typename T, unsigned D> void MultiDimensionalVector<T, D>::clear() {
  for (typename MultiDimensionalVector<T, D>::iterator i = data().begin(); i != data().end(); ++i) {
    i->clear();
  }
  data().clear();
}

/** \param new_size Number of elements the vector should contain */
template <typename T, unsigned D>
void MultiDimensionalVector<T, D>::resize(unsigned new_size) {
  data().resize(new_size);
}

/** \param new_size Number of elements the vector should contain
 *  \param x Data with which new elements should be populated
 */
template <typename T, unsigned D>
void MultiDimensionalVector<T, D>::resize(unsigned new_size, MultiDimensionalVector<T, D-1> x) {
  data().resize(new_size, x);
}

/** \param other NestedVector<T, D> to compare to */
template <typename T, unsigned D>
bool MultiDimensionalVector<T, D>::operator == (const MultiDimensionalVector<T, D> &other) const {
  return data() == other.data();
}

/** \param other NestedVector<T, D> to compare to */
template <typename T, unsigned D>
bool MultiDimensionalVector<T, D>::operator != (const MultiDimensionalVector<T, D> &other) const {
  return data() != other.data();
}

/** \tparam Function A unary function object or function taking a \p T,
 *      \c const \p T& or \p T& as argument type.
 */
template <typename T, unsigned D>
template <typename Function>
Function MultiDimensionalVector<T, D>::for_each(Function f) {
  for (iterator i = begin(); i != end(); ++i) {
    f = i->for_each(f);
  }
  return f;
}

template <typename T, unsigned D>
template <typename Function>
Function MultiDimensionalVector<T, D>::for_each(Function f) const {
  for (const_iterator i = begin(); i != end(); ++i) {
    f = i->for_each(f);
  }
  return f;
}

template <typename T, unsigned D>
std::string MultiDimensionalVector<T, D>::toString() const {
  std::ostringstream o;
  o << *this;
  return o.str();
}

template <typename T, unsigned D>
void MultiDimensionalVector<T, D>::print() const {
  std::cerr << data().size() << " elements: " << "< ";
  for (typename std::vector<MultiDimensionalVector<T, D-1> >::const_iterator
       i = data().begin();
       i != data().end(); ++i) {
    i->print();
  }
  std::cerr << " >" << std::endl;
}

template <typename T, unsigned D>
std::vector<MultiDimensionalVector<T, D-1> > &MultiDimensionalVector<T, D>::data() {
  return _data;
}

template <typename T, unsigned D>
const std::vector<MultiDimensionalVector<T, D-1> > &MultiDimensionalVector<T, D>::data() const {
  return _data;
}

/** \param s The ostream to which \p v is sent
 *  \param v The vector to print
 *  \return \p s
 *  \ingroup VecMath
 */
template<typename T, unsigned D>
std::ostream& operator<<(std::ostream& s, MultiDimensionalVector<T, D> const& v) {

  if (MultiDimensionalVector<T, 1>::print_num_elements()) s << v.size() << " elements: ";

  for (unsigned i = MultiDimensionalVector<T, 1>::max_dimension(); i > D; --i) s << "  ";

  s << "(\n";

  copy(v.begin(), v.end(), std::ostream_iterator<MultiDimensionalVector<T, D-1> >(s, "\n"));

  for (unsigned i = MultiDimensionalVector<T, 1>::max_dimension(); i > D; --i) s << "  ";

  s << ")";

  return s;
}

/** \param find_me The element to find in the vector \p v
 *  \param v The vector to search for element \p find_me
 *  \return The \p MultiDimensionalVector<T,D>::iterator pointing to the element or
 *          \p v.end() if it is not in \p v
 *
 *  \ingroup VecMath
 */
template <typename T, unsigned D>
typename MultiDimensionalVector<T, D>::iterator find(MultiDimensionalVector<T, D-1> const &find_me,
                                                     MultiDimensionalVector<T, D> &v) {
  typename MultiDimensionalVector<T, D>::iterator i = v.begin();
  while(*i != find_me && i != v.end()) ++i;
  return i;
}

/** \param v1 The MultiDimensionalVector containing the first arguments going into \p f.
 *  \param v2 The MultiDimensionalVector containing the second arguments going into \p f.
 *  \param f The function that is applied on every element of \p v1 and \p v2.
 *  \tparam T1 Type of the elements in the first MultiDimensionalVector; type of
 *    the first argument to \p f.
 *  \tparam T2 Type of the elements in the second MultiDimensionalVector; type of
 *    the second argument to \p f.
 *  \tparam D Dimensionality (nesting depth) of both MultiDimensionalVector s.
 *  \tparam Function A binary function object or function taking a \p T1,
 *      \c const \p T1& or \p T1& as first argument, and  a \p T2, \c const \p T2&
 *      or \p T2& as second argument.
 */
template<typename T1, typename T2, unsigned D, typename Function>
Function for_each(MultiDimensionalVector<T1, D> &v1,
                  MultiDimensionalVector<T2, D> &v2,
                  Function f) {
  size_t max_element = std::min(v1.size(), v2.size());
  for (size_t i = 0; i < max_element; ++i) {
    f = for_each(v1[i], v2[i], f);
  }
  return f;
}

/** \param v1 The MultiDimensionalVector containing the first arguments going into \p f.
 *  \param v2 The MultiDimensionalVector containing the second arguments going into \p f.
 *  \param f The function that is applied on every element of \p v1 and \p v2.
 *  \tparam T1 Type of the elements in the first MultiDimensionalVector; type of
 *    the first argument to \p f.
 *  \tparam T2 Type of the elements in the second MultiDimensionalVector; type of
 *    the second argument to \p f.
 *  \tparam D Dimensionality (nesting depth) of both MultiDimensionalVector s.
 *  \tparam Function A binary function object or function taking a \p T1 or
 *      \c const \p T1& as first argument, and  a \p T2 or \c const \p T2&
 *      as second argument.
 */
template<typename T1, typename T2, unsigned D, typename Function>
Function for_each(const MultiDimensionalVector<T1, D> &v1,
                  const MultiDimensionalVector<T2, D> &v2,
                  Function f) {
  size_t max_element = std::min(v1.size(), v2.size());
  for (size_t i = 0; i < max_element; ++i) {
    f = for_each(v1[i], v2[i], f);
  }
  return f;
}

/** \param v1 The MultiDimensionalVector containing the first arguments going into \p f.
 *  \param v2 The MultiDimensionalVector containing the second arguments going into \p f.
 *  \param v3 The MultiDimensionalVector containing the third arguments going into \p f.
 *  \param f The function that is applied on every element of \p v1, \p v2 \p v2 and \p v3.
 *  \tparam T1 Type of the elements in the first MultiDimensionalVector; type of
 *    the first argument to \p f.
 *  \tparam T2 Type of the elements in the second MultiDimensionalVector; type of
 *    the second argument to \p f.
 *  \tparam T3 Type of the elements in the third MultiDimensionalVector; type of
 *    the third argument to \p f.
 *  \tparam D Dimensionality (nesting depth) of both MultiDimensionalVector s.
 *  \tparam Function A ternary function object or function taking a \p T1,
 *      \c const \p T1& or \p T1& as first argument,  a \p T2, \c const \p T2&
 *      or \p T2& as second argument, and a \p T2, \c const \p T2& or \p T3& as
 *      third argument.
 */
template<typename T1, typename T2, typename T3, unsigned D, typename Function>
Function for_each(MultiDimensionalVector<T1, D> &v1,
                  MultiDimensionalVector<T2, D> &v2,
                  MultiDimensionalVector<T3, D> &v3,
                  Function f) {
  size_t max_element = std::min(std::min(v1.size(), v2.size()), v3.size());
  for (size_t i = 0; i < max_element; ++i) {
    f = for_each(v1[i], v2[i], v3[i], f);
  }
  return f;
}

/** \param v1 The MultiDimensionalVector containing the first arguments going into \p f.
 *  \param v2 The MultiDimensionalVector containing the second arguments going into \p f.
 *  \param v3 The MultiDimensionalVector containing the third arguments going into \p f.
 *  \param f The function that is applied on every element of \p v1, \p v2 \p v2 and \p v3.
 *  \tparam T1 Type of the elements in the first MultiDimensionalVector; type of
 *    the first argument to \p f.
 *  \tparam T2 Type of the elements in the second MultiDimensionalVector; type of
 *    the second argument to \p f.
 *  \tparam T3 Type of the elements in the third MultiDimensionalVector; type of
 *    the third argument to \p f.
 *  \tparam D Dimensionality (nesting depth) of both MultiDimensionalVector s.
 *  \tparam Function A ternary function object or function taking a \p T1,
 *      \c const \p T1& or \p T1& as first argument,  a \p T2, \c const \p T2&
 *      or \p T2& as second argument, and a \p T2, \c const \p T2& or \p T3& as
 *      third argument.
 */
template<typename T1, typename T2, typename T3, unsigned D, typename Function>
Function for_each(const MultiDimensionalVector<T1, D> &v1,
                  const MultiDimensionalVector<T2, D> &v2,
                  const MultiDimensionalVector<T3, D> &v3,
                  Function f) {
  size_t max_element = std::min(std::min(v1.size(), v2.size()), v3.size());
  for (size_t i = 0; i < max_element; ++i) {
    f = for_each(v1[i], v2[i], v3[i], f);
  }
  return f;
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
MultiDimensionalVector<T, 1>::MultiDimensionalVector(): _data() { }

template <typename T>
MultiDimensionalVector<T, 1>::MultiDimensionalVector(unsigned n): _data(n) { }

template <typename T>
MultiDimensionalVector<T, 1>::MultiDimensionalVector(std::vector<T> data): _data(data) { }

template <typename T>
typename MultiDimensionalVector<T, 1>::iterator
MultiDimensionalVector<T, 1>::begin() {
  return data().begin();
}

template <typename T>
typename MultiDimensionalVector<T, 1>::iterator
MultiDimensionalVector<T, 1>::end() {
  return data().end();
}

template <typename T>
typename MultiDimensionalVector<T, 1>::const_iterator
MultiDimensionalVector<T, 1>::begin() const {
  return data().begin();
}

template <typename T>
typename MultiDimensionalVector<T, 1>::const_iterator
MultiDimensionalVector<T, 1>::end() const {
  return data().end();
}

/** \param x Data to be added */
template <typename T>
void MultiDimensionalVector<T, 1>::push_back(const T &x) {
  data().push_back(x);
}

template <typename T>
T &MultiDimensionalVector<T, 1>::back() {
    return data().back();
}
      
template <typename T>
const T &MultiDimensionalVector<T, 1>::back() const {
    return data().back();
}

/** \param position Iterator pointing to element to be erased
 *  \return An iterator pointing to the next element (or end())
 */
template <typename T>
typename MultiDimensionalVector<T, 1>::iterator
MultiDimensionalVector<T, 1>::erase(iterator position) {
  return data().erase(position);
}

/** \param first Iterator pointing to first element to be erased
 *  \param last Iterator pointing to one past the last element to be erased.
 *  \return An iterator pointing to the next element (or end())
 */
template <typename T>
typename MultiDimensionalVector<T, 1>::iterator
MultiDimensionalVector<T, 1>::erase(iterator first, iterator last) {
  return data().erase(first, last);
}

/** \param i The index of the element for which data should be accessed
 *  \return Read/write reference to data.
 */
template <typename T>
T &MultiDimensionalVector<T, 1>::operator [] (unsigned i) {
  return data()[i];
}

/** \param i The index of the element for which data should be accessed
 *  \return Read-only (constant) reference to data.
 */
template <typename T>
const T &MultiDimensionalVector<T, 1>::operator [] (unsigned i) const {
  return data()[i];
}

template <typename T>
unsigned MultiDimensionalVector<T, 1>::size() const {
  return data().size();
}

template <typename T>
unsigned MultiDimensionalVector<T, 1>::empty() const {
  return data().empty();
}

template <typename T>
void MultiDimensionalVector<T, 1>::clear() {
  data().clear();
}

/** \param new_size Number of elements the vector should contain */
template <typename T>
void MultiDimensionalVector<T, 1>::resize(unsigned new_size) {
  data().resize(new_size);
}

/** \param new_size Number of elements the vector should contain
 *  \param x Data with which new elements should be populated
 */
template <typename T>
void MultiDimensionalVector<T, 1>::resize(unsigned new_size, T x) {
  data().resize(new_size, x);
}

/** \param other NestedVector<T, 1> to compare to */
template <typename T>
bool MultiDimensionalVector<T, 1>::operator == (const MultiDimensionalVector<T, 1> &other) const {
  return data() == other.data();
}

/** \param other NestedVector<T, 1> to compare to */
template <typename T>
bool MultiDimensionalVector<T, 1>::operator != (const MultiDimensionalVector<T, 1> &other) const {
  return data() != other.data();
}

template <typename T>
template <typename Function>
Function MultiDimensionalVector<T, 1>::for_each(Function f) {
  return std::for_each(begin(), end(), f);
}

template <typename T>
template <typename Function>
Function MultiDimensionalVector<T, 1>::for_each(Function f) const {
  return std::for_each(begin(), end(), f);
}

template <typename T>
std::string MultiDimensionalVector<T, 1>::toString() const {
  std::ostringstream o;
  o << *this;
  return o.str();
}

template <typename T>
void MultiDimensionalVector<T, 1>::print() const {
  std::cerr << "< ";
  for (typename std::vector<T>::const_iterator i = data().begin();
       i != data().end(); ++i) {
    std::cerr << *i << " ";
  }
  std::cerr << "> ";
}

template <typename T>
bool MultiDimensionalVector<T, 1>::print_num_elements() {
  return PRINT_NUM_ELEMENTS;
}

template <typename T>
unsigned MultiDimensionalVector<T, 1>::max_dimension() {
  return MAX_DIMENSION;
}

template <typename T>
std::vector<T> &MultiDimensionalVector<T, 1>::data() {
  return _data;
}

template <typename T>
const std::vector<T> &MultiDimensionalVector<T, 1>::data() const {
  return _data;
}

/// Print a MultiDimensionalVector<T, 1> on a std::ostream
/** \param s The ostream to which \p v is sent
 *  \param v The vector to print
 *  \return \p s
 *  \ingroup VecMath
 */
template<typename T>
std::ostream& operator<<(std::ostream& s, MultiDimensionalVector<T, 1> const& v) {

  if (MultiDimensionalVector<T, 1>::print_num_elements()) s << v.size() << " elements: ";
  for (unsigned i = MultiDimensionalVector<T, 1>::max_dimension(); i > 1; --i) s << "  ";
  s << "(";
  copy(v.begin(), v.end(), std::ostream_iterator<T>(s, " "));
  for (unsigned i = MultiDimensionalVector<T, 1>::max_dimension(); i > 1; --i) s << "  ";
  s << ")";
  return s;

}


/** \param v1 The MultiDimensionalVector containing the first arguments going into \p f.
 *  \param v2 The MultiDimensionalVector containing the second arguments going into \p f.
 *  \param f The function that is applied on every element of \p v1 and \p v2.
 *  \tparam T1 Type of the elements in the first MultiDimensionalVector; type of
 *    the first argument to \p f.
 *  \tparam T2 Type of the elements in the second MultiDimensionalVector; type of
 *    the second argument to \p f.
 *  \tparam Function A binary function object or function taking a \p T1,
 *      \c const \p T1& or \p T1& as first argument, and  a \p T2, \c const \p T2&
 *      or \p T2& as second argument.
 */
template<typename T1, typename T2, typename Function>
Function for_each(MultiDimensionalVector<T1, 1> &v1,
                  MultiDimensionalVector<T2, 1> &v2,
                  Function f) {
  size_t max_element = std::min(v1.size(), v2.size());
  for (size_t i = 0; i < max_element; ++i) {
    f(v1[i], v2[i]);
  }
  return f;
}

/** \param v1 The MultiDimensionalVector containing the first arguments going into \p f.
 *  \param v2 The MultiDimensionalVector containing the second arguments going into \p f.
 *  \param f The function that is applied on every element of \p v1 and \p v2.
 *  \tparam T1 Type of the elements in the first MultiDimensionalVector; type of
 *    the first argument to \p f.
 *  \tparam T2 Type of the elements in the second MultiDimensionalVector; type of
 *    the second argument to \p f.
 *  \tparam Function A binary function object or function taking a \p T1 or
 *      \c const \p T1& as first argument, and  a \p T2 or \c const \p T2&
 *      as second argument.
 */
template<typename T1, typename T2, typename Function>
Function for_each(const MultiDimensionalVector<T1, 1> &v1,
                  const MultiDimensionalVector<T2, 1> &v2,
                  Function f) {
  size_t max_element = std::min(v1.size(), v2.size());
  for (size_t i = 0; i < max_element; ++i) {
    f(v1[i], v2[i]);
  }
  return f;
}

/** \param v1 The MultiDimensionalVector containing the first arguments going into \p f.
 *  \param v2 The MultiDimensionalVector containing the second arguments going into \p f.
 *  \param v3 The MultiDimensionalVector containing the third arguments going into \p f.
 *  \param f The function that is applied on every element of \p v1, \p v2 \p v2 and \p v3.
 *  \tparam T1 Type of the elements in the first MultiDimensionalVector; type of
 *    the first argument to \p f.
 *  \tparam T2 Type of the elements in the second MultiDimensionalVector; type of
 *    the second argument to \p f.
 *  \tparam T3 Type of the elements in the third MultiDimensionalVector; type of
 *    the third argument to \p f.
 *  \tparam Function A ternary function object or function taking a \p T1,
 *      \c const \p T1& or \p T1& as first argument,  a \p T2, \c const \p T2&
 *      or \p T2& as second argument, and a \p T2, \c const \p T2& or \p T3& as
 *      third argument.
 */
template<typename T1, typename T2, typename T3, typename Function>
Function for_each(MultiDimensionalVector<T1, 1> &v1,
                  MultiDimensionalVector<T2, 1> &v2,
                  MultiDimensionalVector<T3, 1> &v3,
                  Function f) {
  size_t max_element = std::min(std::min(v1.size(), v2.size()), v3.size());
  for (size_t i = 0; i < max_element; ++i) {
    f(v1[i], v2[i], v3[i]);
  }
  return f;
}

/** \param v1 The MultiDimensionalVector containing the first arguments going into \p f.
 *  \param v2 The MultiDimensionalVector containing the second arguments going into \p f.
 *  \param v3 The MultiDimensionalVector containing the third arguments going into \p f.
 *  \param f The function that is applied on every element of \p v1, \p v2 \p v2 and \p v3.
 *  \tparam T1 Type of the elements in the first MultiDimensionalVector; type of
 *    the first argument to \p f.
 *  \tparam T2 Type of the elements in the second MultiDimensionalVector; type of
 *    the second argument to \p f.
 *  \tparam T3 Type of the elements in the third MultiDimensionalVector; type of
 *    the third argument to \p f.
 *  \tparam Function A ternary function object or function taking a \p T1,
 *      \c const \p T1& or \p T1& as first argument,  a \p T2, \c const \p T2&
 *      or \p T2& as second argument, and a \p T2, \c const \p T2& or \p T3& as
 *      third argument.
 */
template<typename T1, typename T2, typename T3, typename Function>
Function for_each(const MultiDimensionalVector<T1, 1> &v1,
                  const MultiDimensionalVector<T2, 1> &v2,
                  const MultiDimensionalVector<T3, 1> &v3,
                  Function f) {
  size_t max_element = std::min(std::min(v1.size(), v2.size()), v3.size());
  for (size_t i = 0; i < max_element; ++i) {
    f(v1[i], v2[i], v3[i]);
  }
  return f;
}


}