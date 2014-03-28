/* 
 * File:   Test_FacePolygon.h
 * Author: lene
 *
 * Created on March 27, 2014, 4:07 PM
 */

#ifndef TEST_FACEPOLYGON_H
#define	TEST_FACEPOLYGON_H

#include <QtTest/QtTest>
#include "MultiDimensionalVector.h"
#include "Vector.h"

class Test_FacePolygon: public QObject {
  Q_OBJECT

  const VecMath::Vector<3> ZERO = VecMath::Vector<3>(0., 0., 0.);
  const VecMath::Vector<3> X = VecMath::Vector<3>(1., 0., 0.);
  const VecMath::Vector<3> Y = VecMath::Vector<3>(0., 1., 0.);
  const VecMath::Vector<3> Z = VecMath::Vector<3>(0., 0., 1.);
  const VecMath::Vector<3> ONE = VecMath::Vector<3>(1., 1., 1.);
  
private slots:
  
  void initTestCase();

  void faceEqualsItself();
  void rotatedFaceIsEqual();
  void reversedFaceIsEqual();
  void faceUnequalOther();
  void rotatedFaceIsEqualWith4();
  void garbledFaceIsNotEqual();
  void iteratorConstructor();
  void rotatedFaceIsEqualWith5();
  
private:
  VecMath::MultiDimensionalVector<VecMath::Vector<3>,1> container_;
};

#endif	/* TEST_FACEPOLYGON_H */

