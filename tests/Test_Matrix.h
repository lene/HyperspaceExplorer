#ifndef MATRIXTEST_H_
#define MATRIXTEST_H_

#include <QtTest/QtTest>


class Test_Matrix: public QObject {

  Q_OBJECT

  static const double EPSILON = 1e-8;

private slots:
  void defaultConstructor();
  void rotationAboutAxisConstructor();
  void matrixMultiplication();
  void vectorMultiplication();
  void toString();

};


#endif /* MATRIXTEST_H_ */
