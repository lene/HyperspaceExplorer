#ifndef TEST_PARAMETRICFUNCTION_H_
#define TEST_PARAMETRICFUNCTION_H_

#include "ParametricFunction.h"

#include <QtTest/QtTest>

#include <tr1/memory>

class Test_ParametricFunction: public QObject {

  Q_OBJECT

  class ParametricFunctionTestImplementation: public ParametricFunction<4,3> {
  public:
    ParametricFunctionTestImplementation();
    
    virtual return_type f(const argument_type &x) { return VecMath::Vector<4>(0.,0.,0.,1.); }
  };
  
public:
  ~Test_ParametricFunction();
    
private slots:

  void initTestCase();
  void cleanupTestCase();

  void definedParametersArePresent();
  void definedParametersHaveCorrectValues();
  void getParameterValueWorks();
  
private:
  std::tr1::shared_ptr< ParametricFunction<4, 3> > _function;
  
  const static unsigned TEST_FUNCTION_NUM_PARAMETERS = 4;
  const static double DOUBLE_PARAMETER_VALUE;
  const static unsigned UNSIGNED_PARAMETER_VALUE;
  const static int INT_PARAMETER_VALUE;
  const static std::string STRING_PARAMETER_VALUE;
  
};


#endif /* FUNCTIONTEST_H_ */
