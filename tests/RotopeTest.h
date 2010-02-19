#ifndef ROTOPETEST_H_
#define ROTOPETEST_H_

#include "Rotopes/Realm.h"

#include <QtTest/QtTest>

class RotopeBase;

class RotopeTest: public QObject {

  Q_OBJECT

public:
  static const unsigned _numSegments = 4;
  static const double EPSILON = 1.e-8;

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
  void cubeVertices();
  void prismRealm();
  void prismVertices();
  void cylinder1Realm();
  void cylinder1Vertices();
  void cylinder2Realm();
  void cylinder2Vertices();

private:
  void setRotope(const std::string &generator);
  void setRealm();
  void setVertices();

  bool isInVertices(const VecMath::Vector<4> &vertex) const;

  RotopeBase *_rotope;

  Realm _realm;
  std::vector<VecMath::Vector<4> > _vertices;
};


#endif /* ROTOPETEST_H_ */
