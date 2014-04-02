/* 
 * File:   Test_Projector.cpp
 * Author: lene
 * 
 * Created on March 31, 2014, 3:43 PM
 */

#include "Test_Projector.h"

#include "GlobalFunctions.h"
#include "Rotopes/Projector.h"
using namespace UnitTests;

void Test_Projector::testProject3Dto2D() {
    VecMath::Vector<3> original(1., 0., 0.);
    std::vector<VecMath::Vector<3>> originals(1, original);
    Projector<3, 2> projector;
    VecMath::Vector<2> projected = projector(originals, 2., 4.).front();
    test(projected == VecMath::Vector<2>(0.5, 0.), "projected value wrong");
}

void Test_Projector::testProject4Dto2D() {
    VecMath::Vector<4> original(1., 0., 0., 0.);
    std::vector<VecMath::Vector<4>> originals(1, original);
    Projector<4, 2> projector;
    VecMath::Vector<2> projected = projector(originals, 2., 4.).front();
    test(projected == VecMath::Vector<2>(0.25, 0.), "projected value wrong");
}

void Test_Projector::testProject2Dto2D() {
    VecMath::Vector<2> original(1., 0.);
    std::vector<VecMath::Vector<2>> originals(1, original);
    Projector<2, 2> projector;
    VecMath::Vector<2> projected = projector(originals, 2., 4.).front();
    test(projected == original, "projected value wrong");
}

void Test_Projector::testProjectSingleVertex() {
    VecMath::Vector<3> original(1., 0., 0.);
    Projector<3, 2> projector;
    VecMath::Vector<2> projected = projector(original, 2., 4.);
    test(projected == VecMath::Vector<2>(0.5, 0.), "projected value wrong");
}

