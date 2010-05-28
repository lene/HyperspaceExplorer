/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
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

#include "Test_Transformation.h"

#include "Test_ParametricFunction.h"

using VecMath::Vector;
using VecMath::Rotation;
using VecMath::Matrix;
using std::tr1::shared_ptr;
using std::cerr;

void Test_Transformation::initTestCase() {

  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);

  _grid = shared_ptr< FunctionValueGrid<4, 3> >(
      new FunctionValueGrid<4, 3>(pf,
                                  Vector<3, unsigned>(3, 3, 3),
                                  Vector<3>(-1., -1., -1.),
                                  Vector<3>(1., 1., 1.)));

  Rotation<4> rot(1., 2., 3., 4., 5., 6.);
  Vector<4> trans(1., 1., 1., 1.);
  Transformation<4, 3> transform(rot, trans);

  FunctionValueGrid<4, 3>::value_storage_type g = transform.transform(_grid->getValues());

}

void Test_Transformation::cleanupTestCase() {

}

Q_DECLARE_METATYPE(Rotation<4>)
Q_DECLARE_METATYPE(Vector<4>)

void Test_Transformation::rotationPreservesNorm_data() {
  QTest::addColumn< Rotation<4> >("rotation");
  QTest::newRow("Zero rotation") << Rotation<4>(0., 0., 0., 0., 0., 0.);
  QTest::newRow("Random rotation") << Rotation<4>(1., 2., 3., 4., 5., 6.);
  QTest::newRow("90 degrees") << Rotation<4>(90., 0., 0., 0., 0., 0.);
  QTest::newRow("180 degrees") << Rotation<4>(180., 0., 0., 0., 0., 0.);
  QTest::newRow("Random negative rotation") << Rotation<4>(-1., -2., -3., -4., -5., -6.);
}

void Test_Transformation::rotationPreservesNorm() {

  QFETCH(Rotation<4>, rotation);

  Vector<4> trans(0.);
  Transformation<4, 3> transform(rotation, trans);

  FunctionValueGrid<4, 3>::value_storage_type g = transform.transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        QVERIFY2(fabs(g[i][j][k].sqnorm() - _grid->getValues()[i][j][k].sqnorm()) < 1e-8,
                 (QString::number(g[i][j][k].sqnorm()) + " != "+ QString::number(_grid->getValues()[i][j][k].sqnorm())).toAscii()
        );
      }
    }
  }
}


void Test_Transformation::rotate90DegreesIsOrthogonal_data() {
  QTest::addColumn< Rotation<4> >("rotation");
  QTest::newRow("xy") << Rotation<4>(90., 0., 0., 0., 0., 0.);
  QTest::newRow("xz") << Rotation<4>(0., 90., 0., 0., 0., 0.);
  QTest::newRow("xw") << Rotation<4>(0., 0., 90., 0., 0., 0.);
  QTest::newRow("yz") << Rotation<4>(0., 0., 0., 90., 0., 0.);
  QTest::newRow("yw") << Rotation<4>(0., 0., 0., 0., 90., 0.);
  QTest::newRow("zw") << Rotation<4>(0., 0., 0., 0., 0., 90.);
  QTest::newRow("what the hell, all axes at once ;-)") << Rotation<4>(90., 90., 90., 90., 90., 90.);
}

void Test_Transformation::rotate90DegreesIsOrthogonal() {
  QFETCH(Rotation<4>, rotation);

  Vector<4> trans(0.);
  Transformation<4, 3> transform(rotation, trans);

  FunctionValueGrid<4, 3>::value_storage_type g = transform.transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        if (g[i][j][k] != _grid->getValues()[i][j][k]) {
          QVERIFY(g[i][j][k] * _grid->getValues()[i][j][k]< 1e-8);
        }
      }
    }
  }
}

void Test_Transformation::rotate180DegreesIsNegative_data() {
  QTest::addColumn< Rotation<4> >("rotation");
  QTest::newRow("xy") << Rotation<4>(180., 0., 0., 0., 0., 0.);
  QTest::newRow("xz") << Rotation<4>(0., 180., 0., 0., 0., 0.);
  QTest::newRow("xw") << Rotation<4>(0., 0., 180., 0., 0., 0.);
  QTest::newRow("yz") << Rotation<4>(0., 0., 0., 180., 0., 0.);
  QTest::newRow("yw") << Rotation<4>(0., 0., 0., 0., 180., 0.);
  QTest::newRow("zw") << Rotation<4>(0., 0., 0., 0., 0., 180.);
  QTest::newRow("what the hell, all axes at once ;-)") << Rotation<4>(180., 180., 180., 180., 180., 180.);
}

void Test_Transformation::rotate180DegreesIsNegative() {
  QFETCH(Rotation<4>, rotation);

  Vector<4> trans(0.);
  Transformation<4, 3> transform(rotation, trans);

  FunctionValueGrid<4, 3>::value_storage_type g = transform.transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        if (g[i][j][k] != _grid->getValues()[i][j][k]) {
          QVERIFY((g[i][j][k] + _grid->getValues()[i][j][k]).sqnorm() < 1e-8);
        }
      }
    }
  }
}

void Test_Transformation::rotate360DegreesIsEqual_data() {
  QTest::addColumn< Rotation<4> >("rotation");
  QTest::newRow("xy") << Rotation<4>(360., 0., 0., 0., 0., 0.);
  QTest::newRow("xz") << Rotation<4>(0., 360., 0., 0., 0., 0.);
  QTest::newRow("xw") << Rotation<4>(0., 0., 360., 0., 0., 0.);
  QTest::newRow("yz") << Rotation<4>(0., 0., 0., 360., 0., 0.);
  QTest::newRow("yw") << Rotation<4>(0., 0., 0., 0., 360., 0.);
  QTest::newRow("zw") << Rotation<4>(0., 0., 0., 0., 0., 360.);
  QTest::newRow("what the hell, all axes at once ;-)") << Rotation<4>(360., 360., 360., 360., 360., 360.);
}

void Test_Transformation::rotate360DegreesIsEqual() {
  QFETCH(Rotation<4>, rotation);

  Vector<4> trans(0.);
  Transformation<4, 3> transform(rotation, trans);

  FunctionValueGrid<4, 3>::value_storage_type g = transform.transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        QVERIFY((g[i][j][k] - _grid->getValues()[i][j][k]).sqnorm() < 1e-8);
      }
    }
  }
}

void Test_Transformation::translationAddsVector_data() {
  QTest::addColumn< Vector<4> >("translation");

  QTest::newRow("x+1") << Vector<4>(1., 0., 0., 0.);
  QTest::newRow("x-1") << Vector<4>(-1., 0., 0., 0.);
  QTest::newRow("0") << Vector<4>(0., 0., 0., 0.);
}

void Test_Transformation::translationAddsVector() {
  Rotation<4> rotation(0., 0., 0., 0., 0., 0.);
  QFETCH(Vector<4>, translation);

  Transformation<4, 3> transform(rotation, translation);

  FunctionValueGrid<4, 3>::value_storage_type g = transform.transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        QVERIFY((g[i][j][k] - _grid->getValues()[i][j][k]-translation).sqnorm() < 1e-8);
      }
    }
  }
}

void Test_Transformation::scaleScales_data() {
  QTest::addColumn< Vector<4> >("scale");

  QTest::newRow("x*2") << Vector<4>(2., 1., 1., 1.);
  QTest::newRow("y*2") << Vector<4>(2., 1., 1., 1.);
  QTest::newRow("1") << Vector<4>(1., 1., 1., 1.);
  QTest::newRow("negative") << Vector<4>(-1., -1., -1., -1.);
  QTest::newRow("0") << Vector<4>(1., 1., 1., 1.);

}

void Test_Transformation::scaleScales(){

  Rotation<4> rotation(0., 0., 0., 0., 0., 0.);
  Vector<4> translation(0.);
  QFETCH(Vector<4>, scale);

  Transformation<4, 3> transform(rotation, translation, scale);

  FunctionValueGrid<4, 3>::value_storage_type g = transform.transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        for (unsigned n = 0; n < g[i][j][k].dimension(); ++n) {
          double difference = g[i][j][k][n] - scale[n]*_grid->getValues()[i][j][k][n];
          QVERIFY2(fabs(difference) < 1e-8, QString::number(difference).toAscii());
        }
      }
    }
  }

}


class ParametricFunctionTestImplementation: public ParametricFunction<4,3, float> {
    public:
        ParametricFunctionTestImplementation();

        virtual return_type f(const argument_type &) { return VecMath::makeVector(0.f, 0.f, 0.f, 1.f); }
};


ParametricFunctionTestImplementation::ParametricFunctionTestImplementation() {
    declareParameter("double parameter", 1.0);
    declareParameter("unsigned parameter", (unsigned)1);
    declareParameter("int parameter", -1);
}

using VecMath::makeRotation;
using VecMath::makeVector;

typedef Rotation< 4, float > floatrot;
typedef Vector< 4, float > floatvec;

Q_DECLARE_METATYPE(floatrot)
Q_DECLARE_METATYPE(floatvec)

void Test_Transformation::rotateFloats_data() {

    QTest::addColumn< Rotation< 4, float > >("rotation");
    QTest::newRow("Zero rotation") << makeRotation<float>(0., 0., 0., 0., 0., 0.);
    QTest::newRow("Random rotation") << makeRotation<float>(1., 2., 3., 4., 5., 6.);
    QTest::newRow("90 degrees") << makeRotation<float>(90., 0., 0., 0., 0., 0.);
    QTest::newRow("180 degrees") << makeRotation<float>(180., 0., 0., 0., 0., 0.);
//    QTest::newRow("Random negative rotation") << makeRotation<float>(-1., -2., -3., -4., -5., -6.);
}

void Test_Transformation::rotateFloats() {

    ParametricFunctionTestImplementation *f = new ParametricFunctionTestImplementation();
    shared_ptr<ParametricFunction<4, 3, float> > pf(f);

    std::tr1::shared_ptr< FunctionValueGrid<4, 3, float> > grid(
        new FunctionValueGrid<4, 3, float>(pf,
                                makeVector<unsigned>(3, 3, 3),
                                makeVector<float>(-1., -1., -1.),
                                makeVector<float>(1., 1., 1.)));

    QFETCH(floatrot, rotation);

    Vector<4, float> trans(0.);
    Transformation<4, 3, float> transform(rotation, trans);

    FunctionValueGrid<4, 3, float>::value_storage_type g = transform.transform(grid->getValues());

    for (unsigned i = 0; i < g.size(); ++i) {
        for (unsigned j = 0; j < g.size(); ++j) {
            for (unsigned k = 0; k < g.size(); ++k) {
                QVERIFY2(fabs(g[i][j][k].sqnorm() - grid->getValues()[i][j][k].sqnorm()) < 1e-8,
                         (QString::number(g[i][j][k].sqnorm()) + " != "+ QString::number(grid->getValues()[i][j][k].sqnorm())).toAscii()
                         );
            }
        }
    }
}

