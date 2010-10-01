/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef ROTOPETEST_H_
#define ROTOPETEST_H_

#include "Rotopes/Realm.h"

#include <QtTest/QtTest>

class RotopeInterface;

/// Unit tests for Rotopes
class Test_Rotope: public QObject {

  Q_OBJECT

public:
  static const double EPSILON = 1.e-8;
  static unsigned numberOfVerticesForCircle();

private slots:
  void initTestCase();
  void cleanupTestCase();

  void oneDimensionalRotope();

  void squareRealm();
  void squareVertices();
  void triangleRealm();
  void triangleVertices();
  void circleVertices();
  void circleRealm();

  void cubeRealm();
  void cubeVertices();
  void prismRealm();
  void prismVertices();
  void cylinder1Realm();
  void cylinder1Vertices();
  void cylinder2Realm();
  void cylinder2Vertices();
  // I'm leaving out pyramid and tetrahedron, otherwise the number of tests would
  // explode combinatorically. from here on, i'm only testing interesting objects.
  void coneRealm();
  void coneVertices();
  void sphereRealm();
  void sphereRealmFull();
  void sphereVertices();

  void rotateTaper();
  void rotateExtrudedTaper();

  void tesseractRealm();
  void tesseractVertices();

  void penteract();

private:
  void setRotope(const std::string &generator);
  void setRealm();
  void setVertices();

  bool isInVertices(const VecMath::Vector<4> &vertex) const;
  void printVertices();

  RotopeInterface *_rotope;

  Realm _realm;
  std::vector<VecMath::Vector<4> > _vertices;
};


#endif /* ROTOPETEST_H_ */
