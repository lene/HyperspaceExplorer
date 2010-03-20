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
}

void Test_Function::FunctionTestImplementation::SetParameters(const ParameterMap& parms) {
#if 1
  for (ParameterMap::const_iterator i = parms.begin(); i != parms.end(); ++i) {
    if (i->second->getName() == "double parameter") _doubleParm = i->second->toDouble();
    if (i->second->getName() == "unsigned parameter") _unsignedParm = i->second->toUnsigned();
    if (i->second->getName() == "int parameter") _intParm = i->second->toInt();
    if (i->second->getName() == "string parameter") _stringParm = i->second->toString();
  }
#else
    setParameter(parms, this->_radius, "Radius");
#endif
}


VecMath::Vector< 4 >& Test_Function::FunctionTestImplementation::operator()(double x, double y, double z) {
  static VecMath::Vector<4> F;
  F = VecMath::Vector<4>(x, y, z, _doubleParm);
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

Test_Function::RotationParameterTestImplementation::RotationParameterTestImplementation() {
  declareParameter("rotation parameter", VecMath::Rotation<5>());
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

void Test_Function::functionValue() {
  FunctionTestImplementation function;
  ParameterMap newParameters = function.getParameters();
  std::string parameterName = "double parameter";
  ParameterMap::iterator it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue(QString::number(sqrt(2.)).toStdString());
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.toString()).c_str());
  }
    function.SetParameters(newParameters);
    
    VecMath::Vector<4> f = function.f();
    
    QVERIFY2((f - VecMath::Vector<4>(0., 0., 0., sqrt(2.))).sqnorm() < 1e-8, f.toString().c_str());
}

void Test_Function::parameters() {
  QVERIFY2(_function->getNumParameters() == TEST_FUNCTION_NUM_PARAMETERS,
           QString::number(_function->getNumParameters()).toAscii());
           
  ParameterMap parameters = _function->getParameters();

  QVERIFY(parameters.find("double parameter") != parameters.end());
  QVERIFY(parameters.find("unsigned parameter") != parameters.end());
  QVERIFY(parameters.find("int parameter") != parameters.end());
  QVERIFY(parameters.find("string parameter") != parameters.end());
  
  QVERIFY(parameters.find("double parameter")->second->value()->toDouble() == 1.0);
  FunctionParameter *parameter = _function->getParameter("double parameter");
  QVERIFY(parameter->value()->toDouble() == 1.0);
  
  QVERIFY(parameters.find("unsigned parameter")->second->value()->toUnsigned() == 1);
  parameter = _function->getParameter("unsigned parameter");
  QVERIFY(parameter->value()->toUnsigned() == 1);

  QVERIFY(parameters.find("int parameter")->second->value()->toInt() == -1);
  parameter = _function->getParameter("int parameter");
  QVERIFY(parameter->value()->toInt() == -1);  

  QVERIFY(parameters.find("string parameter")->second->value()->toString() == "a string");
  parameter = _function->getParameter("string parameter");
  QVERIFY(parameter->value()->toString() == "a string");
  
}

void Test_Function::parameter_get() {
  QVERIFY(_function->getParameters().getValue("double parameter")->toDouble() == 1.0);
  QVERIFY(_function->getParameters().getValue("unsigned parameter")->toUnsigned() == 1);
  QVERIFY(_function->getParameters().getValue("int parameter")->toInt() == -1);
  QVERIFY(_function->getParameters().getValue("string parameter")->toString() == "a string");
  
  RotationParameterTestImplementation f;
  QVERIFY(f.getParameters().getValue("rotation parameter")->operator VecMath::Rotation<5>()[0] == 0.);
}

void Test_Function::parameter_set() {
  _function->getParameters().set("double parameter", 4.0);
  QVERIFY(_function->getParameters().getValue("double parameter")->toDouble() == 4.0);
  _function->getParameters().set("unsigned parameter", 4);
  QVERIFY(_function->getParameters().getValue("unsigned parameter")->toUnsigned() == 4);
  _function->getParameters().set("int parameter", -4);
  QVERIFY(_function->getParameters().getValue("int parameter")->toInt() == -4);
  _function->getParameters().set("string parameter", std::string("yet another string"));
  QVERIFY(_function->getParameters().getValue("string parameter")->toString() == "yet another string");
  
  RotationParameterTestImplementation f;
  f.getParameters().set("rotation parameter", VecMath::Rotation<5>(0., 1., 2., 3., 4., 5., 6., 7., 8., 9.));
  VecMath::Rotation<5> rot = f.getParameters().getValue("rotation parameter")->operator VecMath::Rotation<5>();
  
  for (unsigned i = 0; i < VecMath::NumAxes<5>::num; ++i) {
    QVERIFY(rot[i] == i);
  }
}

void Test_Function::parameterWithoutCast() {
  ParameterTestImplementation function;
  ParameterMap parameters = function.getParameters();
  try {
    unsigned u = parameters.find("looks like unsigned, but is int")->second->value()->toUnsigned();
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
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.toString()).c_str());
  }
  QVERIFY(newParameters.find("double parameter")->second->value()->toDouble() == 2.0);

  parameterName = "unsigned parameter";
  it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue("2");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.toString()).c_str());
  }
  QVERIFY(newParameters.find("unsigned parameter")->second->value()->toUnsigned() == 2);

  parameterName = "int parameter";
  it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue("-2");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.toString()).c_str());
  }
  QVERIFY(newParameters.find("int parameter")->second->value()->toInt() == -2);
  
  parameterName = "string parameter";
  it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue("another string");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.toString()).c_str());
  }
  QVERIFY(newParameters.find("string parameter")->second->value()->toString() == "another string");
  
}

void Test_Function::accessedNonexistentParameter() {
  try {
    FunctionParameter *parameter = _function->getParameter("nonexistent parameter");
  } catch (ParameterMap::NonexistentParameterAccessed &e) {
    return;
  }
  
  QFAIL("ParameterMap::NonexistentParameterAccessed exception expected");
}

void Test_Function::rotationAsParameter() {
  RotationParameterTestImplementation f;
  FunctionParameter *parameter = f.getParameter("rotation parameter");
  VecMath::Rotation<5> rot = parameter->value()->operator VecMath::Rotation<5>();
  
  QVERIFY2(rot == VecMath::Rotation<5>(), rot.toString().c_str());
  
  ParameterMap newParameters = f.getParameters();
  std::string parameterName = "rotation parameter";
  ParameterMap::iterator it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    parameter = it->second;
    parameter->setValue(VecMath::Rotation<5>(0., 1., 2., 3., 4., 5., 6., 7., 8., 9.).toString());
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.toString()).c_str());
  }
  f.SetParameters(newParameters);
  
  parameter = f.getParameter("rotation parameter");
  rot = parameter->value()->operator VecMath::Rotation<5>();
  
  for (unsigned i = 0; i < VecMath::NumAxes<5>::num; ++i) {
    QVERIFY(rot[i] == i);
  }
  
  std::string parameterAsString = f.getParameters().toString();
  for (char c = '0'; c <= '9'; ++c) {
    QVERIFY2(parameterAsString.find(c) != std::string::npos, parameterAsString.c_str());
  }
}

