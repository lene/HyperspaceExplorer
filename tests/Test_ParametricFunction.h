#ifndef TEST_PARAMETRICFUNCTION_H_
#define TEST_PARAMETRICFUNCTION_H_

#include "ParametricFunction.h"

#include "Rotation.h"

#include <QtTest/QtTest>

#include <tr1/memory>

/// Unit tests for class ParametricFunction
class Test_ParametricFunction: public QObject {

  Q_OBJECT

public:

  class ParametricFunctionTestImplementation: public ParametricFunction<4,3> {
    public:
      ParametricFunctionTestImplementation();

      virtual return_type f(const argument_type &) { return VecMath::Vector<4>(0.,0.,0.,CONST_FUNCTION_W); }
      
      const static double CONST_FUNCTION_W = 1.;
  };

  ~Test_ParametricFunction();

private slots:

  void initTestCase();
  void cleanupTestCase();

  void definedParametersArePresent();
  void definedParametersHaveCorrectValues();
  void getParameterValueWorks();
  void settingParameters();
  void accessedNonexistentParameter();
  void setParameters();
  void functionValue();

private:

  void initializeFunction();

  std::tr1::shared_ptr< ParametricFunction<4, 3> > _function;

  const static unsigned TEST_FUNCTION_NUM_PARAMETERS = 5;
  const static double DOUBLE_PARAMETER_VALUE;
  const static unsigned UNSIGNED_PARAMETER_VALUE;
  const static int INT_PARAMETER_VALUE;
  const static std::string STRING_PARAMETER_VALUE;
  const static VecMath::Rotation<5> ROTATION_PARAMETER_VALUE;

};


#endif /* FUNCTIONTEST_H_ */