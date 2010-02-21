#ifndef NESTEDVECTORTEST_H_
#define NESTEDVECTORTEST_H_

#include <QtTest/QtTest>

#include "NestedVector.h"

class NestedVectorTest: public QObject {

  Q_OBJECT

  typedef unsigned stored_type;
  typedef VecMath::NestedVector<stored_type, 1> Vector1D;
  typedef VecMath::NestedVector<stored_type, 2> Vector2D;

private slots:
  void push_back_1D();
  void push_back_2D();

  void testGenerate2DVector();

  void erase();
  void resize();

private:
  NestedVectorTest::Vector1D generate1DVector(
          NestedVectorTest::stored_type start_value = 0, unsigned size = 3);
  NestedVectorTest::Vector2D generate2DVector(
          NestedVectorTest::stored_type start_value = 0, unsigned size = 3);
};


#endif /* NESTEDVECTORTEST_H_ */
