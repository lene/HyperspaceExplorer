#ifndef ROTOPETEST_H_
#define ROTOPETEST_H_

#include <QtTest/QtTest>

class RotopeBase;

class RotopeTest: public QObject {

  Q_OBJECT

public:
  static const unsigned _numSegments = 4;

private slots:
  void initTestCase();
  void cleanupTestCase();

  void oneDimensionalRotope();
  void squareRealm();
  void squareVertices();
  void triangleRealm();
  void triangleVertices();
  void circleRealm();
  void circleVertices();

  void cubeRealm();
  void prismRealm();

private:
  RotopeBase *_rotope;

};


#endif /* ROTOPETEST_H_ */
