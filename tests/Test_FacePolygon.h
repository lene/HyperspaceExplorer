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

private slots:
  
  void initTestCase();

  void faceEqualsItself();
  void faceEqualsOther();
  void faceUnequalOther();

private:  
  VecMath::MultiDimensionalVector<VecMath::Vector<3>,1> container_;
};

#endif	/* TEST_FACEPOLYGON_H */

