/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "Test_Projection.h"

#include "Vector.h"

using VecMath::Vector;
using VecMath::NestedVector;

typedef NestedVector< Vector<4>, 1 > storage1D;
typedef NestedVector< Vector<3>, 1 > projected1D;
typedef NestedVector< Vector<5>, 1 > storage1D5;
typedef NestedVector< Vector<4>, 2 > storage2D;
typedef NestedVector< Vector<3>, 2 > projected2D;


void Test_Projection::initTestCase() { }

void Test_Projection::cleanupTestCase() { }

Q_DECLARE_METATYPE(storage1D)
Q_DECLARE_METATYPE(projected1D)

projected1D expected(double x, double y, double z) {
  projected1D temp;
  temp.push_back(Vector<3>(x, y, z));
  return temp;
}

storage1D given(double x, double y, double z, double w) {
  storage1D temp;
  temp.push_back(Vector<4>(x, y, z, w));
  return temp;
}

void Test_Projection::project1D_data() {
  QTest::addColumn< storage1D >("vertex_data");
  QTest::addColumn< double >("screen_w");
  QTest::addColumn< double >("camera_w");
  QTest::addColumn< projected1D >("projected_data");

  QTest::newRow("x") << given(1., 0., 0., 0.) << 1. << 3. << expected(2./3., 0., 0.);
  QTest::newRow("y") << given(0., 1., 0., 0.) << 1. << 3. << expected(0., 2./3., 0.);
  QTest::newRow("z") << given(0., 0., 1., 0.) << 1. << 3. << expected(0., 0., 2./3.);
  QTest::newRow("w") << given(0., 0., 0., 1.) << 1. << 3. << expected(0., 0., 0.);
}

void Test_Projection::project1D() {

  QFETCH(storage1D, vertex_data);
  QFETCH(double, screen_w);
  QFETCH(double, camera_w);
  QFETCH(projected1D, projected_data);
  
  Projection<4, 3, 1> p(screen_w, camera_w, false);
  
  projected1D target = p.project(vertex_data);
  
  for (unsigned i = 0; i < target.size(); ++i) {
    QVERIFY2((target[i]-projected_data[i]).sqnorm() < EPSILON,
             (target[i].toString()+" != expected "+projected_data[i].toString()).c_str());
  }
}

Q_DECLARE_METATYPE(storage1D5)

storage1D5 given(double x, double y, double z, double w, double v) {
  storage1D5 temp;
  temp.push_back(Vector<5>(x, y, z, w, v));
  return temp;
}

void Test_Projection::project5to3_data() {
  QTest::addColumn< storage1D5 >("vertex_data");
  QTest::addColumn< double >("screen_w");
  QTest::addColumn< double >("camera_w");
  QTest::addColumn< projected1D >("projected_data");

  QTest::newRow("x") << given(1., 0., 0., 0., 0.) << 1. << 3. << expected(4./9., 0., 0.);
  QTest::newRow("y") << given(0., 1., 0., 0., 0.) << 1. << 3. << expected(0., 4./9., 0.);
  QTest::newRow("z") << given(0., 0., 1., 0., 0.) << 1. << 3. << expected(0., 0., 4./9.);
  QTest::newRow("w") << given(0., 0., 0., 1., 0.) << 1. << 3. << expected(0., 0., 0.);
  QTest::newRow("v") << given(0., 0., 0., 0., 1.) << 1. << 3. << expected(0., 0., 0.);

}

void Test_Projection::project5to3() {
  QFETCH(storage1D5, vertex_data);
  QFETCH(double, screen_w);
  QFETCH(double, camera_w);
  QFETCH(projected1D, projected_data);
  
  Projection<5, 3, 1> p(screen_w, camera_w, false);
  
  projected1D target = p.project(vertex_data);

  for (unsigned i = 0; i < target.size(); ++i) {
    QVERIFY2((target[i]-projected_data[i]).sqnorm() < EPSILON,
             (target[i].toString()+" != expected "+projected_data[i].toString()).c_str());
  }
}

Q_DECLARE_METATYPE(storage2D)
Q_DECLARE_METATYPE(projected2D)

template <unsigned D> NestedVector<Vector<D>, 2> given(
    Vector<D> v00, Vector<D> v01, Vector<D> v10, Vector<D> v11) {
  NestedVector<Vector<D>, 1> v0;
  v0.push_back(v00);
  v0.push_back(v01);
  
  NestedVector<Vector<D>, 1> v1;
  v1.push_back(v10);
  v1.push_back(v11);

  NestedVector<Vector<D>, 2> temp;
  temp.push_back(v0);
  temp.push_back(v1);
  
  return temp;
}

void Test_Projection::project2D_data() {
  QTest::addColumn< storage2D >("vertex_data");
  QTest::addColumn< double >("screen_w");
  QTest::addColumn< double >("camera_w");
  QTest::addColumn< projected2D >("projected_data");

  QTest::newRow("xy") 
    << given(Vector<4>(-1., 0., 0., 0.), Vector<4>( 1., 0., 0., 0.), Vector<4>(0., -1., 0., 0.), Vector<4>(0., 1., 0., 0.))
    << 1. << 3. 
    << given(Vector<3>(-2./3., 0., 0.), Vector<3>( 2./3., 0., 0.), Vector<3>(0., -2./3., 0.), Vector<3>(0., 2./3., 0.));

  QTest::newRow("xz") 
    << given(Vector<4>(-1., 0., 0., 0.), Vector<4>( 1., 0., 0., 0.), Vector<4>(0., 0., -1., 0.), Vector<4>(0., 0., 1., 0.))
    << 1. << 3. 
    << given(Vector<3>(-2./3., 0., 0.), Vector<3>( 2./3., 0., 0.), Vector<3>(0., 0., -2./3.), Vector<3>(0., 0., 2./3.));
    
  QTest::newRow("xw") 
    << given(Vector<4>(-1., 0., 0., 0.), Vector<4>( 1., 0., 0., 0.), Vector<4>(0., 0., 0., -1.), Vector<4>(0., 0., 0., 1.))
    << 1. << 3. 
    << given(Vector<3>(-2./3., 0., 0.), Vector<3>( 2./3., 0., 0.), Vector<3>(0., 0., 0.), Vector<3>(0., 0., 0.));

  QTest::newRow("xyzw") 
    << given(Vector<4>(-1., -1., 0., 0.), Vector<4>( 1., 1., 0., 0.), Vector<4>(0., 0., -1., -1.), Vector<4>(0., 0., 1., 1.))
    << 1. << 3. 
    << given(Vector<3>(-2./3., -2./3., 0.), Vector<3>( 2./3., 2./3., 0.), Vector<3>(0., 0., -1./2.), Vector<3>(0., 0., 1.));
}

void Test_Projection::project2D() {
  QFETCH(storage2D, vertex_data);
  QFETCH(double, screen_w);
  QFETCH(double, camera_w);
  QFETCH(projected2D, projected_data);
  
  Projection<4, 3, 2> p(screen_w, camera_w, false);
  
  projected2D target = p.project(vertex_data);

  for (unsigned i = 0; i < target.size(); ++i) {
    for (unsigned j = 0; j < target[i].size(); ++j) {
      QVERIFY2((target[i][j]-projected_data[i][j]).sqnorm() < EPSILON,
               (target[i][j].toString()+" != expected "+projected_data[i][j].toString()).c_str());
    }
  }

}

void Test_Projection::projectWithViewpoints() {
/*  
  Projection<4, 3, 1> p(ArrayList<1, Vector<4> >(Vector<4>(0., 0., 0., 0.)),
                        ArrayList<1, Vector<4> >(Vector<4>(0., 0., 0., 3.)),
                        ArrayList<1, double>(1.),
                        ArrayList<1, bool>(false));
 */
} 
