/* 
 * File:   Test_FacePolygon.cpp
 * Author: lene
 * 
 * Created on March 27, 2014, 4:07 PM
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
    UnitTests::test(face3_1 == face3_1, std::string("face equals itself"));
}
void Test_FacePolygon::rotatedFaceIsEqual() {    
    FacePolygon<3, 3> face3_1(container_, ZERO, X, Y);
    FacePolygon<3, 3> face3_2(container_, X, Y, ZERO);
    UnitTests::test(face3_1 == face3_2, std::string("faces with shifted vertex order are equal"));
}

void Test_FacePolygon::reversedFaceIsEqual() {    
    FacePolygon<3, 3> face3_1(container_, ZERO, X, Y);
    FacePolygon<3, 3> face3_2(container_, Y, X, ZERO);
    UnitTests::test(face3_1 == face3_2, std::string("faces with reversed vertex order are equal"));
}

void Test_FacePolygon::faceUnequalOther() {
    FacePolygon<3, 3> face3_1(container_, ZERO, X, Y);
    FacePolygon<3, 3> face3_2(container_, Z, X, Y);
    UnitTests::test(face3_1 != face3_2, std::string("faces containing different vertices are not equal"));
}

void Test_FacePolygon::rotatedFaceIsEqualWith4() {
    FacePolygon<3, 4> face4_1(container_, ZERO, X, Y, Z);
    FacePolygon<3, 4> face4_2(container_, X, Y, Z, ZERO);
    UnitTests::test(face4_1 == face4_2, std::string("faces with shifted vertex order are equal"));
}

void Test_FacePolygon::garbledFaceIsNotEqual() {
    FacePolygon<3, 4> face4_1(container_, ZERO, X, Y, Z);
    FacePolygon<3, 4> face4_2(container_, ZERO, Y, X, Z);
    UnitTests::test(face4_1 != face4_2, std::string("garbled faces are not equal"));
}

void Test_FacePolygon::iteratorConstructor() {
    Vector<3> data1[] = { ZERO, X, Y, Z, ONE };
    FacePolygon<3, 5> face5_1(container_, data1);
    face5_1.print();
    UnitTests::test(face5_1[0] == ZERO, std::string("first element not ZERO"));
    UnitTests::test(face5_1[1] == X, std::string("second element not X"));
    UnitTests::test(face5_1[2] == Y, std::string("third element not Y"));
    UnitTests::test(face5_1[3] == Z, std::string("fourth element not Z"));
    UnitTests::test(face5_1[4] == ONE, std::string("fifth element not ONE"));
}

void Test_FacePolygon::rotatedFaceIsEqualWith5() {
    Vector<3> data1[] = { ZERO, X, Y, Z, ONE };
    Vector<3> data2[] = { X, Y, Z, ONE, ZERO };
    FacePolygon<3, 5> face5_1(container_, data1);
    FacePolygon<3, 5> face5_2(container_, data2);
    face5_1.print(); face5_2.print();
    UnitTests::test(face5_1 == face5_2, std::string("faces with shifted vertex order are equal"));
}
