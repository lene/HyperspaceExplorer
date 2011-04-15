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

#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

#include <bits/stringfwd.h>
#include "GridDrawer.impl.h"

class QString;

class MockView;

namespace VecMath {
  template <unsigned D, typename NUM> class Vector;
}

namespace UnitTests {

  void test(bool condition, const QString &message);
  void test(bool condition, const std::string &message);

  void fail(const std::string &message);

  void testEqual(double checked, double precondition);
  void testEqual(const std::string &checked, const std::string &precondition);
  template <unsigned D, typename NUM>
  void testEqual(const VecMath::Vector<D, NUM> &checked,
                 const VecMath::Vector<D, NUM> &precondition);

  void testGreaterEqual(double checked, double precondition);

  template <unsigned D, typename NUM>
  void testNotEqual(const VecMath::Vector<D, NUM> &checked,
                    const VecMath::Vector<D, NUM> &precondition);

  /// Overload to feed into Displayable::for_each(), which cannot take template functions
  void testVerticesEqual(const VecMath::Vector<4> &v1, const VecMath::Vector<4> &v2);
  /// Overload to feed into Displayable::for_each(), which cannot take template functions
  void testVerticesNotEqual(const VecMath::Vector<4> &v1, const VecMath::Vector<4> &v2);

  template <typename Value, class Container>
  void testContains(const Container &container, const Value &value);
  template <class Container>
  void testContains(const Container &container, const std::string &value);

  /// Stores a pointer to the view used by Test_RealFunction for global functions used by Function::for_each
  void setGlobalView(MockView *v);

  void checkVertexPresent(const VecMath::Vector<4> &v);

  void checkVertexDrawn(const VecMath::Vector<3> &v);


  static const double EPSILON = 1e-8;

}

#endif // GLOBALFUNCTIONS_H
