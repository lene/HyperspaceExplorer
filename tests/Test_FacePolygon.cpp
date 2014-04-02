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

#include "Test_FacePolygon.h"
#include "FacePolygon.impl.h"
#include "MultiDimensionalVector.impl.h"
#include "Vector.h"
#include "GlobalFunctions.h"

using VecMath::Vector;

void Test_FacePolygon::initTestCase() {
    container_.push_back(ZERO);
    container_.push_back(X);
    container_.push_back(Y);
    container_.push_back(Z);
    container_.push_back(ONE);
}

void Test_FacePolygon::faceEqualsItself() {    
    FacePolygon<3, 3> face3_1(container_, ZERO, X, Y);
    UnitTests::test(face3_1 == face3_1, "face equals itself");
}
void Test_FacePolygon::rotatedFaceIsEqual() {    
    FacePolygon<3, 3> face3_1(container_, ZERO, X, Y);
    FacePolygon<3, 3> face3_2(container_, X, Y, ZERO);
    face3_1.print(); face3_2.print();
    UnitTests::test(face3_1 == face3_2, "faces with shifted vertex order are equal");
}

void Test_FacePolygon::reversedFaceIsEqual() {    
    FacePolygon<3, 3> face3_1(container_, ZERO, X, Y);
    FacePolygon<3, 3> face3_2(container_, Y, X, ZERO);
    UnitTests::test(face3_1 == face3_2, "faces with reversed vertex order are equal");
}

void Test_FacePolygon::faceUnequalOther() {
    FacePolygon<3, 3> face3_1(container_, ZERO, X, Y);
    FacePolygon<3, 3> face3_2(container_, Z, X, Y);
    UnitTests::test(face3_1 != face3_2, "faces containing different vertices are not equal");
}

void Test_FacePolygon::rotatedFaceIsEqualWith4() {
    FacePolygon<3, 4> face4_1(container_, ZERO, X, Y, Z);
    FacePolygon<3, 4> face4_2(container_, X, Y, Z, ZERO);
    UnitTests::test(face4_1 == face4_2, "faces with shifted vertex order are equal");
}

void Test_FacePolygon::garbledFaceIsNotEqual() {
    FacePolygon<3, 4> face4_1(container_, ZERO, X, Y, Z);
    FacePolygon<3, 4> face4_2(container_, ZERO, Y, X, Z);
    UnitTests::test(face4_1 != face4_2, "garbled faces are not equal");
}

void Test_FacePolygon::iteratorConstructor() {
    Vector<3> data1[] = { ZERO, X, Y, Z, ONE };
    FacePolygon<3, 5> face5_1(container_, data1);
    face5_1.print();
    UnitTests::test(face5_1[0] == ZERO, "first element not ZERO");
    UnitTests::test(face5_1[1] == X, "second element not X");
    UnitTests::test(face5_1[2] == Y, "third element not Y");
    UnitTests::test(face5_1[3] == Z, "fourth element not Z");
    UnitTests::test(face5_1[4] == ONE, "fifth element not ONE");
}

void Test_FacePolygon::rotatedFaceIsEqualWith5() {
    Vector<3> data1[] = { ZERO, X, Y, Z, ONE };
    Vector<3> data2[] = { X, Y, Z, ONE, ZERO };
    FacePolygon<3, 5> face5_1(container_, data1);
    FacePolygon<3, 5> face5_2(container_, data2);
    face5_1.print(); face5_2.print();
    UnitTests::test(face5_1 == face5_2, "faces with shifted vertex order are equal");
}
