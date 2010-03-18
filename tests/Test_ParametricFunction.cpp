/*
 * FunctionTest.cpp
 *
 *  Created on: Feb 19, 2010
 *      Author: helge
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
  
Test_ParametricFunction::ParametricFunctionTestImplementation::ParametricFunctionTestImplementation() {
  declareParameter("double parameter", Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
  declareParameter("unsigned parameter", Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);
  declareParameter("int parameter", Test_ParametricFunction::INT_PARAMETER_VALUE);
  declareParameter("string parameter", Test_ParametricFunction::STRING_PARAMETER_VALUE);
}

void Test_ParametricFunction::initTestCase()
{
  _function = shared_ptr< ParametricFunction<4, 3> >(new ParametricFunctionTestImplementation());
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
           
  ParameterMap parameters = _function->getParameters();

  QVERIFY(parameters.find("double parameter") != parameters.end());
  QVERIFY(parameters.find("unsigned parameter") != parameters.end());
  QVERIFY(parameters.find("int parameter") != parameters.end());
  QVERIFY(parameters.find("string parameter") != parameters.end());
  
}

void Test_ParametricFunction::definedParametersHaveCorrectValues() {
  
  ParameterMap parameters = _function->getParameters();
  
  QVERIFY(double(*(parameters.find("double parameter")->second->value())) == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
  shared_ptr<FunctionParameter> parameter = _function->getParameter("double parameter");
  QVERIFY(double(*(parameter->value())) == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
  
  QVERIFY(unsigned(*(parameters.find("unsigned parameter")->second->value())) == Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);
  parameter = _function->getParameter("unsigned parameter");
  QVERIFY(unsigned(*(parameter->value())) == Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);
  
  QVERIFY(int(*(parameters.find("int parameter")->second->value())) == Test_ParametricFunction::INT_PARAMETER_VALUE);
  parameter = _function->getParameter("int parameter");
  QVERIFY(int(*(parameter->value())) == Test_ParametricFunction::INT_PARAMETER_VALUE);
  
  QVERIFY(std::string(*(parameters.find("string parameter")->second->value())) == Test_ParametricFunction::STRING_PARAMETER_VALUE);
  parameter = _function->getParameter("string parameter");
  QVERIFY(std::string(*(parameter->value())) == Test_ParametricFunction::STRING_PARAMETER_VALUE);
    
}

void Test_ParametricFunction::getParameterValueWorks() {

  QVERIFY(_function->getParameterValue("double parameter")->toDouble() == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
  
}

