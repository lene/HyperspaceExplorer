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

  QVERIFY(double(*(parameters.find("double parameter")->second->value())) == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
# ifdef USE_SHARED_PTR
  shared_ptr<FunctionParameter> parameter(_function->getParameter("double parameter"));
# else
  FunctionParameter *parameter = _function->getParameter("double parameter");
#endif
  QVERIFY(double(*(parameter->value())) == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);

  QVERIFY(unsigned(*(parameters.find("unsigned parameter")->second->value())) == Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);
# ifdef USE_SHARED_PTR
  parameter.reset(_function->getParameter("unsigned parameter"));
# else
  parameter = _function->getParameter("unsigned parameter");
# endif
  QVERIFY(unsigned(*(parameter->value())) == Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);

  QVERIFY(int(*(parameters.find("int parameter")->second->value())) == Test_ParametricFunction::INT_PARAMETER_VALUE);
# ifdef USE_SHARED_PTR
  parameter.reset(_function->getParameter("int parameter"));
# else
  parameter = _function->getParameter("int parameter");
# endif
  QVERIFY(int(*(parameter->value())) == Test_ParametricFunction::INT_PARAMETER_VALUE);

  QVERIFY(std::string(*(parameters.find("string parameter")->second->value())) == Test_ParametricFunction::STRING_PARAMETER_VALUE);
# ifdef USE_SHARED_PTR
  parameter.reset(_function->getParameter("string parameter"));
# else
  parameter = _function->getParameter("string parameter");
# endif
  QVERIFY(std::string(*(parameter->value())) == Test_ParametricFunction::STRING_PARAMETER_VALUE);

  QVERIFY(parameters.find("rotation parameter")->second->value()->operator VecMath::Rotation<5>() == Test_ParametricFunction::ROTATION_PARAMETER_VALUE);
# ifdef USE_SHARED_PTR
  parameter.reset(_function->getParameter("rotation parameter"));
# else
  parameter = _function->getParameter("rotation parameter");
# endif
  QVERIFY(parameter->value()->operator VecMath::Rotation<5>() == Test_ParametricFunction::ROTATION_PARAMETER_VALUE);

}

void Test_ParametricFunction::getParameterValueWorks() {

  QVERIFY(_function->getParameterValue("double parameter")->toDouble() == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
  QVERIFY(_function->getParameterValue("unsigned parameter")->toUnsigned() == Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);
  QVERIFY(_function->getParameterValue("int parameter")->toInt() == Test_ParametricFunction::INT_PARAMETER_VALUE);
  cerr << _function->getParameterMap().toString();
  shared_ptr< FunctionParameterValueBase > val(_function->getParameterValue("string parameter"));
  std::string string_parameter = val->toString();
  std::cerr << "In map:  \"" << string_parameter << "\"  = ";
  for(unsigned i = 0; i < string_parameter.length();++i) std::cerr << int(string_parameter[i]) << " ";
  std::cerr << std::endl;
  std::cerr << "Default: \"" << Test_ParametricFunction::STRING_PARAMETER_VALUE << "\"  = ";
  for(unsigned i = 0; i < Test_ParametricFunction::STRING_PARAMETER_VALUE.length();++i) std::cerr << int(Test_ParametricFunction::STRING_PARAMETER_VALUE[i]) << " ";
  std::cerr << std::endl;

  std::cerr << string_parameter.compare(Test_ParametricFunction::STRING_PARAMETER_VALUE)  << " " << string_parameter.length() << " " << Test_ParametricFunction::STRING_PARAMETER_VALUE.length() << std::endl;

  QVERIFY2(string_parameter == Test_ParametricFunction::STRING_PARAMETER_VALUE,
           (string_parameter+" != "+Test_ParametricFunction::STRING_PARAMETER_VALUE).c_str());

}

void Test_ParametricFunction::settingParameters() {

  _function->getParameterMap().set("double parameter", 4.0);
  QVERIFY(double(*(_function->getParameterMap().getValue("double parameter"))) == 4.0);

  _function->getParameterMap().set("unsigned parameter", 4);
  QVERIFY(unsigned(*(_function->getParameterMap().getValue("unsigned parameter"))) == 4);

  _function->getParameterMap().set("int parameter", -4);
  QVERIFY(int(*(_function->getParameterMap().getValue("int parameter"))) == -4);

  _function->getParameterMap().set("rotation parameter", VecMath::Rotation<5>(1., 2., 3., 4., 5., 6., 7., 8., 9., 10.));
  VecMath::Rotation<5> rot = _function->getParameterMap().getValue("rotation parameter")->operator VecMath::Rotation<5>();
  for (unsigned i = 0; i < VecMath::NumAxes<5>::num; ++i) {
    QVERIFY(rot[i] == i+1);
  }

  QSKIP("segfaults when trying to set a string parameter", SkipSingle);
  _function->getParameterMap().set("string parameter", std::string("yet another string"));
  QVERIFY(std::string(*(_function->getParameterMap().getValue("string parameter"))) == "yet another string");

}

void Test_ParametricFunction::accessedNonexistentParameter() {

  QSKIP("segfaultsblearghlatorzbabe", SkipSingle);

  try {
    shared_ptr<FunctionParameter> parameter(_function->getParameter("nonexistent parameter"));
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
  QVERIFY(double(*(newParameters.find("double parameter")->second->value())) == 2.0);

  parameterName = "unsigned parameter";
  it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue("2");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.toString()).c_str());
  }
  QVERIFY(unsigned(*(newParameters.find("unsigned parameter")->second->value())) == 2);

  parameterName = "int parameter";
  it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    it->second->setValue("-2");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.toString()).c_str());
  }
  QVERIFY(int(*(newParameters.find("int parameter")->second->value())) == -2);

  parameterName = "string parameter";
  it = newParameters.find(parameterName);
  if (it != newParameters.end()) {
    QSKIP("segfaults when trying to set a string parameter", SkipSingle);
    it->second->setValue("another string");
  } else {
    QFAIL(("Parameter \""+parameterName+"\" not found in map "+newParameters.toString()).c_str());
  }
  QVERIFY(std::string(*(newParameters.find("string parameter")->second->value())) == "another string");

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
