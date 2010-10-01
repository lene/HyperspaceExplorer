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

#ifndef NESTEDVECTORTEST_H_
#define NESTEDVECTORTEST_H_

#include <QtTest/QtTest>

#include "MultiDimensionalVector.h"

/// Unit tests for class VecMath::MultiDimensionalVector
class Test_MultiDimensionalVector: public QObject {

  Q_OBJECT

  typedef unsigned stored_type;
  typedef VecMath::MultiDimensionalVector<stored_type, 1> Vector1D;
  typedef VecMath::MultiDimensionalVector<stored_type, 2> Vector2D;

private slots:
  void push_back_1D();
  void push_back_2D();

  void testGenerate2DVector();

  void erase();
  void resize();

  void for_each();
  void for_each_const();
  void for_each_class();

private:
  Test_MultiDimensionalVector::Vector1D generate1DVector(
          Test_MultiDimensionalVector::stored_type start_value = 0, unsigned size = 3);
  Test_MultiDimensionalVector::Vector2D generate2DVector(
          Test_MultiDimensionalVector::stored_type start_value = 0, unsigned size = 3);
};


#endif /* NESTEDVECTORTEST_H_ */
