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
#if 1
  for (ParameterMap::const_iterator i = parms.begin(); i != parms.end(); ++i) {
    if (i->second->getName() == "double parameter") _doubleParm = double(*i->second);
    if (i->second->getName() == "unsigned parameter") _unsignedParm = unsigned(*i->second);
    if (i->second->getName() == "int parameter") _intParm = int(*i->second);
    if (i->second->getName() == "string parameter") _stringParm = std::string(*i->second);
  }
#else
    setParameter(parms, this->_radius, "Radius");
#endif
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
  FunctionParameter *parameter = _function->getParameter("double parameter");
  QVERIFY(double(*(parameter->value())) == 1.0);
  
  QVERIFY(unsigned(*(parameters.find("unsigned parameter")->second->value())) == 1);
  parameter = _function->getParameter("unsigned parameter");
  QVERIFY(unsigned(*(parameter->value())) == 1);

  QVERIFY(int(*(parameters.find("int parameter")->second->value())) == -1);
  parameter = _function->getParameter("int parameter");
  QVERIFY(int(*(parameter->value())) == -1);  

  QVERIFY(std::string(*(parameters.find("string parameter")->second->value())) == "a string");
  parameter = _function->getParameter("string parameter");
  QVERIFY(std::string(*(parameter->value())) == "a string");
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
  
  ParameterMap newParameters = _function->getParameters();
  std::string parameterName = "double parameter";
  ParameterMap::iterator it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue("2.0");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.print()).c_str());
  }
  QVERIFY(double(*(newParameters.find("double parameter")->second->value())) == 2.0);

  parameterName = "unsigned parameter";
  it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue("2");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.print()).c_str());
  }
  QVERIFY(unsigned(*(newParameters.find("unsigned parameter")->second->value())) == 2);

  parameterName = "int parameter";
  it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue("-2");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.print()).c_str());
  }
  QVERIFY(int(*(newParameters.find("int parameter")->second->value())) == -2);
  
  parameterName = "string parameter";
  it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue("another string");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.print()).c_str());
  }
  QVERIFY(std::string(*(newParameters.find("string parameter")->second->value())) == "another string");
  
}

void Test_Function::accessedNonexistentParameter() {
  try {
    FunctionParameter *parameter = _function->getParameter("nonexistent parameter");
  } catch (ParameterMap::NonexistentParameterAccessed &e) {
    return;
  }
  
  QFAIL("ParameterMap::NonexistentParameterAccessed exception expected");
}
