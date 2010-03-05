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

using std::cerr;
using std::endl;

const QString Test_Function::TEST_FUNCTION_NAME = "FunctionTestImplementation";

Test_Function::FunctionTestImplementation::FunctionTestImplementation(): 
    Function(Test_Function::TEST_FUNCTION_NAME) {
  declareParameter("double parameter", 1.0);
  declareParameter("unsigned parameter", (unsigned)1);
  declareParameter("int parameter", -1);
  declareParameter("string parameter", std::string("a string"));
//  declareParameter("rotation parameter", VecMath::Rotation<4>());
}

void Test_Function::FunctionTestImplementation::SetParameters(const ParameterMap& parms) {
  Function::SetParameters(parms);
}


VecMath::Vector< 4 >& Test_Function::FunctionTestImplementation::operator()(double x, double y, double z) {
  static VecMath::Vector<4> F;
  F = VecMath::Vector<4>(x, y, z, 1.0);
  return F;
}

unsigned int Test_Function::FunctionTestImplementation::getDefinitionSpaceDimensions() {
  return Test_Function::TEST_FUNCTION_DIMENSIONS;
}

void Test_Function::FunctionTestImplementation::Initialize(void) { }
void Test_Function::FunctionTestImplementation::ReInit(double, double, double, double, double, double, double, double, double) { }
void Test_Function::FunctionTestImplementation::calibrateColors() const { }
void Test_Function::FunctionTestImplementation::Transform(const VecMath::Rotation< 4 >&, const VecMath::Vector< 4 >&) { }
void Test_Function::FunctionTestImplementation::Project(double, double, bool) { }
void Test_Function::FunctionTestImplementation::Draw(void ) { }

Test_Function::ParameterTestImplementation::ParameterTestImplementation() {
  declareParameter("looks like unsigned, but is int", 1);
}

Test_Function::~Test_Function() { }

void Test_Function::initTestCase() { }

void Test_Function::cleanupTestCase() { }

void Test_Function::instantiate() {
    _function = new FunctionTestImplementation();
    QVERIFY2(_function->getDefinitionSpaceDimensions() == TEST_FUNCTION_DIMENSIONS, 
             QString::number(_function->getDefinitionSpaceDimensions()).toAscii());
    QVERIFY2(_function->getFunctionName() == TEST_FUNCTION_NAME, 
             _function->getFunctionName().toAscii());
}

void Test_Function::parameters() {
  QVERIFY2(_function->getNumParameters() == TEST_FUNCTION_NUM_PARAMETERS,
           QString::number(_function->getNumParameters()).toAscii());
           
  ParameterMap parameters = _function->getParameters();

  QVERIFY(parameters.find("double parameter") != parameters.end());
  QVERIFY(parameters.find("unsigned parameter") != parameters.end());
  QVERIFY(parameters.find("int parameter") != parameters.end());
  QVERIFY(parameters.find("string parameter") != parameters.end());
  
  QVERIFY(double(*(parameters.find("double parameter")->second->value())) == 1.0);
  QVERIFY(unsigned(*(parameters.find("unsigned parameter")->second->value())) == 1);
  QVERIFY(int(*(parameters.find("int parameter")->second->value())) == -1);
  QVERIFY(std::string(*(parameters.find("string parameter")->second->value())) == "a string");
}

void Test_Function::parameterWithoutCast() {
  ParameterTestImplementation function;
  ParameterMap parameters = function.getParameters();
  try {
    unsigned u = *(parameters.find("looks like unsigned, but is int")->second->value());
  } catch (FunctionParameterValueBase::WrongParameterTypeException &e) {
    return;
  }
  QFAIL("FunctionParameterValueBase::WrongParameterTypeException expected!");
}

void Test_Function::setParameters() {
  QFAIL("NYI");
}

void Test_Function::accessedNonexistentParameter() {
  QFAIL("NYI");
}
