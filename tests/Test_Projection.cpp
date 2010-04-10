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

void Test_Projection::project5to3_data()
{

}

void Test_Projection::project5to3()
{

}

void Test_Projection::project2D_data()
{

}

void Test_Projection::project2D()
{

}
