#ifndef TEST_PARAMETRICFUNCTION_H_
#define TEST_PARAMETRICFUNCTION_H_

#include <QtTest/QtTest>

#include "ParametricFunction.h"

class Test_ParametricFunction: public QObject {

  Q_OBJECT

  class ParametricFunctionTestImplementation: public ParametricFunction<4,3> {
  public:
    ParametricFunctionTestImplementation();

    VecMath::Vector<4> f(VecMath::Vector<3>) { return VecMath::Vector<4>(0.,0.,0.,1.); }
  };
  
public:
  ~Test_ParametricFunction();
    
private slots:

  void initTestCase();
  void cleanupTestCase();

private:
  ParametricFunction<4, 3> *_function;
  
};


#endif /* FUNCTIONTEST_H_ */
