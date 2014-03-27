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

void Test_FacePolygon::initTestCase() {
    container_.push_back(VecMath::Vector<3>(0., 0., 0.));
    container_.push_back(VecMath::Vector<3>(1., 0., 0.));
    container_.push_back(VecMath::Vector<3>(0., 1., 0.));
    container_.push_back(VecMath::Vector<3>(0., 0., 1.));
}

void Test_FacePolygon::faceEqualsItself() {    
    FacePolygon<3, 3> face3_1(container_, VecMath::Vector<3>(0., 0., 0.), VecMath::Vector<3>(1., 0., 0.), VecMath::Vector<3>(0., 1., 0.));
    UnitTests::test(face3_1 == face3_1, std::string("face equals itself"));
}
void Test_FacePolygon::faceEqualsOther() {    
    FacePolygon<3, 3> face3_1(container_, VecMath::Vector<3>(0., 0., 0.), VecMath::Vector<3>(1., 0., 0.), VecMath::Vector<3>(0., 1., 0.));
    FacePolygon<3, 3> face3_2(container_, VecMath::Vector<3>(1., 0., 0.), VecMath::Vector<3>(0., 1., 0.), VecMath::Vector<3>(0., 0., 0.));
    face3_1.print();
    face3_2.print();
    UnitTests::test(face3_1 == face3_2, std::string("faces are equal"));
}

void Test_FacePolygon::faceUnequalOther() {
    FacePolygon<3, 3> face3_1(container_, VecMath::Vector<3>(0., 0., 0.), VecMath::Vector<3>(1., 0., 0.), VecMath::Vector<3>(0., 1., 0.));
    FacePolygon<3, 3> face3_3(container_, VecMath::Vector<3>(0., 0., 1.), VecMath::Vector<3>(1., 0., 0.), VecMath::Vector<3>(0., 1., 0.));
    UnitTests::test(face3_1 != face3_3, std::string("faces are not equal"));
}