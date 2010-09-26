#ifndef NESTEDVECTORTEST_H_
#define NESTEDVECTORTEST_H_

#include <QtTest/QtTest>

#include "MultiDimensionalVector.h"

/// Unit tests for class VecMath::MultiDimensionalVector
class Test_MultiDimensionalVector: public QObject {

  Q_OBJECT

  typedef unsigned stored_type;
  typedef VecMath::MultiDimensionalVector<stored_type, 1> Vector1D;
  typedef VecMath::MultiDimensionalVector<stored_type, 2> Vector2D;

private slots:
  void push_back_1D();
  void push_back_2D();

  void testGenerate2DVector();

  void erase();
  void resize();

  void for_each();
  void for_each_const();
  
private:
  Test_MultiDimensionalVector::Vector1D generate1DVector(
          Test_MultiDimensionalVector::stored_type start_value = 0, unsigned size = 3);
  Test_MultiDimensionalVector::Vector2D generate2DVector(
          Test_MultiDimensionalVector::stored_type start_value = 0, unsigned size = 3);
};


#endif /* NESTEDVECTORTEST_H_ */
