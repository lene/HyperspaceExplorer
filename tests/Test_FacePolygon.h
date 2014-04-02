/*
 * Hyperspace Explorer - visualizing higher-dimensional geometry
 * Copyright (C) 2011  Lene Preuss <lene.preuss@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef TEST_FACEPOLYGON_H
#define	TEST_FACEPOLYGON_H

#include <QtTest/QtTest>
#include "MultiDimensionalVector.h"
#include "Vector.h"

class Test_FacePolygon: public QObject {
  Q_OBJECT

  const VecMath::Vector<3> ZERO = VecMath::Vector<3>(0., 0., 0.);
  const VecMath::Vector<3> X = VecMath::Vector<3>(1., 0., 0.);
  const VecMath::Vector<3> Y = VecMath::Vector<3>(0., 1., 0.);
  const VecMath::Vector<3> Z = VecMath::Vector<3>(0., 0., 1.);
  const VecMath::Vector<3> ONE = VecMath::Vector<3>(1., 1., 1.);
  
private slots:
  
  void initTestCase();

  void faceEqualsItself();
  void rotatedFaceIsEqual();
  void reversedFaceIsEqual();
  void faceUnequalOther();
  void rotatedFaceIsEqualWith4();
  void garbledFaceIsNotEqual();
  void iteratorConstructor();
  void rotatedFaceIsEqualWith5();
  
private:
  VecMath::MultiDimensionalVector<VecMath::Vector<3>,1> container_;
};

#endif	/* TEST_FACEPOLYGON_H */

