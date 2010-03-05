/*
 * FunctionTest.cpp
 *
 *  Created on: Feb 19, 2010
 *      Author: helge
 */

#include "Test_Function.h"

#include "RealFunction.h"
#include "Surface.h"
#include "ComplexFunction.h"
#include "Sponge.h"
#include "ColorManager.h"

#include <cstdlib>


Test_Function::~Test_Function() { }

void Test_Function::initTestCase() {
    ColMgrMgr::Instance().setColorManager("XYZ to RGB");
}

void Test_Function::cleanupTestCase() {

}

void Test_Function::surfaceFunction() {
    _function = new Horizon();
    QVERIFY(_function->getDefinitionSpaceDimensions() == 2);
    qDebug() << _function->getNumParameters()
            << _function->getFunctionName();
    QSKIP("Tests for Surface objects not done yet.", SkipSingle);
}

void Test_Function::complexFunction() {
    _function = new z3();
    QVERIFY(_function->getDefinitionSpaceDimensions() == 2);
    qDebug() << _function->getNumParameters()
            << _function->getFunctionName();
    QSKIP("Tests for ComplexFunction objects not done yet.", SkipSingle);
}

void Test_Function::objectFunction() {
//    _function = new Hypercube();
    QSKIP("Tests for Object objects not done yet.", SkipSingle);

}

