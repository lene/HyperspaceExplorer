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
  QVERIFY(parameters.find("rotation parameter") != parameters.end());
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

  QVERIFY(parameters.find("rotation parameter")->second->value()->operator VecMath::Rotation<5>() == Test_ParametricFunction::ROTATION_PARAMETER_VALUE);
  parameter = _function->getParameter("rotation parameter");
  QVERIFY(parameter->value()->operator VecMath::Rotation<5>() == Test_ParametricFunction::ROTATION_PARAMETER_VALUE);
  
}

void Test_ParametricFunction::getParameterValueWorks() {
  
  QSKIP("segfaultsblearghlatorzbabe", SkipSingle);

  std::cerr << _function->getParameters().toString() << endl;
  FunctionParameterValueBase *b = _function->getParameters().getParameter("double parameter")->value();
  FunctionParameterValueBase *b2 = _function->getParameterValue("double parameter").get();
  std::cerr << b << " " << b2 << std::endl;
  double d = b->toDouble();

  QVERIFY(d == Test_ParametricFunction::DOUBLE_PARAMETER_VALUE);
  QVERIFY(unsigned(*(_function->getParameterValue("unsigned parameter"))) == Test_ParametricFunction::UNSIGNED_PARAMETER_VALUE);
  QVERIFY(int(*(_function->getParameterValue("int parameter"))) == Test_ParametricFunction::INT_PARAMETER_VALUE);
  QVERIFY(std::string(*(_function->getParameterValue("string parameter"))) == Test_ParametricFunction::STRING_PARAMETER_VALUE);
  
}

void Test_ParametricFunction::settingParameters() {

  QSKIP("segfaultsblearghlatorzbabe", SkipSingle);
  
  _function->getParameters().set("double parameter", 4.0);
  QVERIFY(double(*(_function->getParameters().getValue("double parameter"))) == 4.0);
  _function->getParameters().set("unsigned parameter", 4);
  QVERIFY(unsigned(*(_function->getParameters().getValue("unsigned parameter"))) == 4);
  _function->getParameters().set("int parameter", -4);
  QVERIFY(int(*(_function->getParameters().getValue("int parameter"))) == -4);
  _function->getParameters().set("string parameter", std::string("yet another string"));
  QVERIFY(std::string(*(_function->getParameters().getValue("string parameter"))) == "yet another string");
  
  _function->getParameters().set("rotation parameter", VecMath::Rotation<5>(1., 2., 3., 4., 5., 6., 7., 8., 9., 10.));
  VecMath::Rotation<5> rot = _function->getParameters().getValue("rotation parameter")->operator VecMath::Rotation<5>();
  
  for (unsigned i = 0; i < VecMath::NumAxes<5>::num; ++i) {
    QVERIFY(rot[i] == i+1);
  }
  
}

void Test_ParametricFunction::parameterWithoutCast() {
  
  ParameterMap parameters = _function->getParameters();
  
  QSKIP("segfaultsblearghlatorzbabe", SkipSingle);
  
  try {
    unsigned u = *(parameters.find("looks like unsigned, but is int")->second->value());
    u++; // avoid compile warning
  } catch (FunctionParameterValueBase::WrongParameterTypeException &e) {
    return;
  }
  QFAIL("FunctionParameterValueBase::WrongParameterTypeException expected!");
}

void Test_ParametricFunction::accessedNonexistentParameter() {

  QSKIP("segfaultsblearghlatorzbabe", SkipSingle);
  
  try {
    shared_ptr<FunctionParameter> parameter = _function->getParameter("nonexistent parameter");
  } catch (ParameterMap::NonexistentParameterAccessed &e) {
    return;
  }
  
  QFAIL("ParameterMap::NonexistentParameterAccessed exception expected");
}

void Test_ParametricFunction::setParameters() {
  
  ParameterMap newParameters = _function->getParameters();

  std::string parameterName = "double parameter";
  ParameterMap::iterator it = newParameters.find(parameterName);
  QSKIP("segfaultsblearghlatorzbabe", SkipSingle);
  
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
