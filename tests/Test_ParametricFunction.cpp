/*
 * FunctionTest.cpp
 *
 *  Created on: Feb 19, 2010
 *  Author: lene.preuss@gmail.com
 *  License: GPL V2 (see COPYING)
 */

#include "Test_ParametricFunction.h"

#include <cstdlib>

using std::cerr;
using std::endl;
using std::tr1::shared_ptr;

const double Test_ParametricFunction::DOUBLE_PARAMETER_VALUE = 1.0;
const unsigned Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE = 1;
const int Test_ParametricFunction::INT_PARAMETER_VALUE = -1;
const std::string Test_ParametricFunction::STRING_PARAMETER_VALUE = "a string";
const VecMath::Rotation<5> Test_ParametricFunction::ROTATION_PARAMETER_VALUE = VecMath::Rotation<5>(1., 2., 3., 4., 5., 6., 7., 8., 9., 10.);

Test_ParametricFunction::ParametricFunctionTestImplementation::ParametricFunctionTestImplementation() {
  declareParameter("double parameter", Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
  declareParameter("unsigned parameter", Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);
  declareParameter("int parameter", Test_ParametricFunction::INT_PARAMETER_VALUE);
  declareParameter("string parameter", Test_ParametricFunction::STRING_PARAMETER_VALUE);
  declareParameter("rotation parameter", Test_ParametricFunction::ROTATION_PARAMETER_VALUE);
}

void Test_ParametricFunction::initializeFunction() {
  _function = shared_ptr< ParametricFunction<4, 3> >(new ParametricFunctionTestImplementation());
}

void Test_ParametricFunction::initTestCase() {
  initializeFunction();
}

void Test_ParametricFunction::cleanupTestCase()
{

}
Test_ParametricFunction::~Test_ParametricFunction()
{

}

void Test_ParametricFunction::definedParametersArePresent() {

  QVERIFY2(_function->getNumParameters() == TEST_FUNCTION_NUM_PARAMETERS,
           QString::number(_function->getNumParameters()).toAscii());

  ParameterMap parameters = _function->getParameterMap();

  QVERIFY(parameters.find("double parameter") != parameters.end());
  QVERIFY(parameters.find("unsigned parameter") != parameters.end());
  QVERIFY(parameters.find("int parameter") != parameters.end());
  QVERIFY(parameters.find("string parameter") != parameters.end());
  QVERIFY(parameters.find("rotation parameter") != parameters.end());
}

void Test_ParametricFunction::definedParametersHaveCorrectValues() {

  ParameterMap parameters = _function->getParameterMap();

  QVERIFY(parameters.find("double parameter")->second->value()->toDouble() == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
  FunctionParameter::parameter_ptr_type parameter(_function->getParameter("double parameter"));
  QVERIFY(parameter->value()->toDouble() == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);

  QVERIFY(parameters.find("unsigned parameter")->second->value()->toUnsigned() == Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);
  parameter = _function->getParameter("unsigned parameter");
  QVERIFY(parameter->value()->toUnsigned() == Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);

  QVERIFY(parameters.find("int parameter")->second->value()->toInt() == Test_ParametricFunction::INT_PARAMETER_VALUE);
  parameter = _function->getParameter("int parameter");
  QVERIFY(parameter->value()->toInt() == Test_ParametricFunction::INT_PARAMETER_VALUE);

  QVERIFY(parameters.find("string parameter")->second->value()->toString() == Test_ParametricFunction::STRING_PARAMETER_VALUE);
  parameter = _function->getParameter("string parameter");
  QVERIFY(parameter->value()->toString() == Test_ParametricFunction::STRING_PARAMETER_VALUE);

  QVERIFY(parameters.find("rotation parameter")->second->value()->toRotation5() == Test_ParametricFunction::ROTATION_PARAMETER_VALUE);
  parameter = _function->getParameter("rotation parameter");
  QVERIFY(parameter->value()->toRotation5() == Test_ParametricFunction::ROTATION_PARAMETER_VALUE);

}

void Test_ParametricFunction::getParameterValueWorks() {

  QVERIFY(_function->getParameterValue("double parameter")->toDouble() == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
  QVERIFY(_function->getParameterValue("unsigned parameter")->toUnsigned() == Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);
  QVERIFY2(_function->getParameterValue("int parameter")->toInt() == Test_ParametricFunction::INT_PARAMETER_VALUE,
	   QString::number(_function->getParameterValue("int parameter")->toInt()).toAscii());
  QVERIFY2(_function->getParameterValue("string parameter")->toString() == Test_ParametricFunction::STRING_PARAMETER_VALUE,
           _function->getParameterValue("string parameter")->toString().c_str());
}

void Test_ParametricFunction::settingParameters() {

  _function->getParameterMap().set("double parameter", 4.0);
  QVERIFY(_function->getParameterMap().getValue("double parameter")->toDouble() == 4.0);

  _function->getParameterMap().set("unsigned parameter", 4);
  QVERIFY(_function->getParameterMap().getValue("unsigned parameter")->toUnsigned() == 4);

  _function->getParameterMap().set("int parameter", -4);
  QVERIFY(_function->getParameterMap().getValue("int parameter")->toInt() == -4);

  _function->getParameterMap().set("rotation parameter", VecMath::Rotation<5>(1., 2., 3., 4., 5., 6., 7., 8., 9., 10.));
  VecMath::Rotation<5> rot = _function->getParameterMap().getValue("rotation parameter")->toRotation5();
  for (unsigned i = 0; i < VecMath::NumAxes<5>::num; ++i) {
    QVERIFY(rot[i] == i+1);
  }

  _function->getParameterMap().set("string parameter", std::string("yet another string"));
  QVERIFY(_function->getParameterMap().getValue("string parameter")->toString() == "yet another string");

}

void Test_ParametricFunction::accessedNonexistentParameter() {

  try {
   FunctionParameter::parameter_ptr_type parameter(_function->getParameter("nonexistent parameter"));
  } catch (ParameterMap::NonexistentParameterAccessed &e) {
    return;
  }

  QFAIL("ParameterMap::NonexistentParameterAccessed exception expected");
}

void Test_ParametricFunction::setParameters() {

  ParameterMap newParameters = _function->getParameterMap();

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

void Test_ParametricFunction::functionValue() {

  for (double x = -5; x < 5.; ++x) {
    for (double y = -5; y < 5.; ++y) {
      for (double z = -5; z < 5.; ++z) {
        VecMath::Vector<4> f = _function->f(VecMath::Vector<3>(x, y, z));
        QVERIFY2((f - VecMath::Vector<4>(0., 0., 0., 1.)).sqnorm() < 1e-8, f.toString().c_str());
      }
    }
  }
}
