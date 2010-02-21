/*
 * FunctionTest.cpp
 *
 *  Created on: Feb 19, 2010
 *      Author: helge
 */

#include "FunctionTest.h"

#include "RealFunction.h"
#include "Surface.h"
#include "ComplexFunction.h"
#include "Sponge.h"
#include "ColorManager.h"

#include <cstdlib>


FunctionTest::~FunctionTest() { }

void FunctionTest::initTestCase() {
    ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void FunctionTest::cleanupTestCase() {

}

void FunctionTest::surfaceFunction() {
    _function = new Horizon();
    QVERIFY(_function->getDefinitionSpaceDimensions() == 2);
    qDebug() << _function->getNumParameters()
            << _function->getFunctionName();
}

void FunctionTest::complexFunction() {
    _function = new z3();
    QVERIFY(_function->getDefinitionSpaceDimensions() == 2);
    qDebug() << _function->getNumParameters()
            << _function->getFunctionName();
}

void FunctionTest::objectFunction() {
//    _function = new Hypercube();
}

