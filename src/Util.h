/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>

namespace VecMath {
  template <unsigned D, typename N> class Vector;
}
class QString;

/** for an explanation why this two-stage macro expansion generates string
 *  literals from #defines, see
 * http://groups.google.de/group/comp.lang.c/browse_thread/thread/2016d4664fdae3c1/f2873d4f6ef769b9#f2873d4f6ef769b9
 */
#define stringify(X) #X
#define make_str(X) stringify(X)

/** __PRETTY_FUNCTION__ is a gcc extension. For other compilers, redefine it
 *  to print filename and line instead of the function signature.
 */
//#ifndef __PRETTY_FUNCTION__
//#   define __PRETTY_FUNCTION__ (std::string(__FILE__)+std::string(" line //")+Globals::Instance().itoa(__LINE__)).c_str()
//#endif

///  Utility functions
namespace Util {

  /// Print a std::vector on a std::ostream
  /** \param s The ostream to which \p v is sent
  *  \param v The vector to print
  *  \return \p s
  */
  template<typename T> std::ostream& operator<<(std::ostream& s,
                                                std::vector<T> const& v);

  /// Find an element in a vector
  /** \param find_me The element to find in the vector \p v
  *  \param v The vector to search for element \p find_me
  *  \return The \p vector<T>::iterator pointing to the element or \p v.end() if
  *          it is not in \p v
  */
  template <typename T> typename std::vector<T>::iterator find(T find_me, std::vector<T> &v) {
    typename std::vector<T>::iterator i = v.begin();
    while(*i != find_me && i != v.end()) ++i;
    return i;
  }

  int GetGLList();

  void CheckGLErrors (const char *op = 0);

  /** define a GL Vertex from a Vector<3>
  *  @param V the vertex to be defined                                 */
  void glVertex (const VecMath::Vector<3, double> &V);

  VecMath::Vector<3, double> vnormalize (double xx, double yy, double zz);

  std::string itoa (int x);
  /// Convert a QString to double
  /** \return The double precision value of the argument */
  double atod (QString);
  /// Convert a string to unsigned
  /** \return The double precision value of the argument */
  double atod (const std::string &);
  /// Convert a string to signed int
  /** \return The integer value of the argument */
  int atoi(const std::string &);
  /// Convert a string to unsigned
  /** \return The unsigned value of the argument */
  unsigned atou(const std::string &);

  std::string ftoa (double x);

  /// A (I hope) Editor-independent repersentation of "²"
  std::string sup2();

  /// A (I hope) Editor-independent repersentation of "³"
  std::string sup3();

}

#endif // UTIL_H