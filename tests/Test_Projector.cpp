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
    VecMath::Vector<3> original(1, 0, 0);
    std::vector<VecMath::Vector<3>> originals(1, original);
    Projector<3, 2> projector;
    std::vector<VecMath::Vector<2>> projected = projector.operator ()(originals, 2., 4.);
    
    for(auto v: projected) std::cerr << v << std::endl;
    test(false, std::string("fail"));
}


