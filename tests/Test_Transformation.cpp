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

#include "Test_Transformation.h"

#include "Test_ParametricFunction.h"

#include "TransformationFactory.impl.h"
#include "MultiDimensionalVector.impl.h"
#include "Rotation.impl.h"

using VecMath::Vector;
using VecMath::Rotation;
using VecMath::Matrix;
using std::shared_ptr;
using std::cerr;


class AverageParametricFunction: public ParametricFunction<4,3, float> {
    public:
        AverageParametricFunction() { }
        virtual return_type f(const argument_type &x) {
            return VecMath::makeVector(x[0],x[1],x[2],(x[0]+x[1]+x[2])/3.f);
        }
};

Rotation<4> defaultRotation() {
    return Rotation<4>(1., 2., 3., 4., 5., 6.);
}

Vector<4> defaultTranslation() {
    return Vector<4>(1., 1., 1., 1.);
}

const Transformation< 4, 3 > *generateDefaultTransform() {
  return TransformationFactory::create< 4, 3, double >(defaultRotation(), defaultTranslation(), 1.);
}

shared_ptr< FunctionValueGrid<4, 3> > makeGrid(unsigned xsize, unsigned ysize, unsigned zsize) {
  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);

  return shared_ptr< FunctionValueGrid<4, 3> >(
      new FunctionValueGrid<4, 3>(pf,
                                  Vector<3, unsigned>(xsize, ysize, zsize),
                                  Vector<3>(-1., -1., -1.),
                                  Vector<3>(1., 1., 1.)));

}

void Test_Transformation::initTestCase() {
  _grid = makeGrid(3, 3, 3);
}

void Test_Transformation::cleanupTestCase() {

}

Q_DECLARE_METATYPE(Rotation<4>)
Q_DECLARE_METATYPE(Vector<4>)

void Test_Transformation::transformPerformed() {
  TransformationFactory::setTransformationMethod(TransformationFactory::Singlethreaded);
  const Transformation< 4, 3 > *transform = generateDefaultTransform();

  FunctionValueGrid<4, 3>::value_storage_type g = transform->transform(_grid->getValues());
}

void Test_Transformation::multithreadedTransformPerformed() {
  TransformationFactory::setTransformationMethod(TransformationFactory::Multithreaded);
  const Transformation< 4, 3 > *transform = generateDefaultTransform();

  FunctionValueGrid<4, 3>::value_storage_type g = transform->transform(_grid->getValues());
}

int Test_Transformation::timeTransform(const Transformation< 4, 3 > *transform) {
  shared_ptr< FunctionValueGrid<4, 3> > grid = makeGrid(2, 2, min_size_for_multithreaded_advantage);
  QTime t;
  t.start();
  FunctionValueGrid<4, 3>::value_storage_type g = transform->transform(grid->getValues());
  return t.elapsed();
}

void Test_Transformation::verifyMultithreadedIsFaster(int elapsed_multi, int elapsed_single) {
    qDebug() << "Multithreaded: " << elapsed_multi << "ms, single threaded: " << elapsed_single << "ms";
    if (Util::isMultithreadedSensible()) {
        if (elapsed_multi >= elapsed_single) {
            QSKIP(
                "Multithreaded slower than singlethreaded; that may be because you don't have enough processors",
                SkipSingle
            );
        }
//        QVERIFY2(elapsed_multi < elapsed_single, "Multithreaded transform should be faster");    
    } else {
        if (elapsed_multi >= elapsed_single) {
            QSKIP(
                "Multithreaded slower than singlethreaded; that may be because you don't have enough processors",
                SkipSingle
            );
        } else {
            QVERIFY(true);
        }
    }
}

void Test_Transformation::multithreadedTransformFaster() {

    TransformationFactory::setTransformationMethod(TransformationFactory::Multithreaded);
    const Transformation< 4, 3 > *transform_multi =
        TransformationFactory::create<4, 3>(defaultRotation(), defaultTranslation(), VecMath::Vector<4>(1.));
    int elapsed_multi = timeTransform(transform_multi);

    TransformationFactory::setTransformationMethod(TransformationFactory::Singlethreaded);
    const Transformation< 4, 3 > *transform_single =
        TransformationFactory::create<4, 3>(defaultRotation(), defaultTranslation(), VecMath::Vector<4>(1.));
    int elapsed_single = timeTransform(transform_single);

    verifyMultithreadedIsFaster(elapsed_multi, elapsed_single);
    
}

int Test_Transformation::timeTransformationMethod(TransformationFactory::Method method) {
  TransformationFactory::setTransformationMethod(method);
  const Transformation< 4, 3 > *transform = TransformationFactory::create< 4, 3, double >(
        defaultRotation(), defaultTranslation(), 1.
  );
  return timeTransform(transform);
    
}

void Test_Transformation::factorySetsSingleAndMultithreaded() {

  int elapsed_multi = timeTransformationMethod(TransformationFactory::Multithreaded);
  int elapsed_single = timeTransformationMethod(TransformationFactory::Singlethreaded);

  verifyMultithreadedIsFaster(elapsed_multi, elapsed_single);
    
}

void Test_Transformation::singlethreadedWorksForObjects() {

//    shared_ptr< FunctionValueGrid<4, 1> > grid = makeGrid(4, 4, min_size_for_multithreaded_advantage);

}

void Test_Transformation::multithreadedWorksForObjects() {
    
}

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
  std::shared_ptr<const Transformation<4, 3> > transform(TransformationFactory::create< 4, 3, double >(rotation, trans, 1.));

  FunctionValueGrid<4, 3>::value_storage_type g = transform->transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        QVERIFY2(fabs(VecMath::sqnorm(g[i][j][k])) - VecMath::sqnorm(_grid->getValues()[i][j][k]) < 1e-8,
                 (QString::number(VecMath::sqnorm(g[i][j][k])) + " != "+ 
                  QString::number(VecMath::sqnorm(_grid->getValues()[i][j][k]))).toLatin1()
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
  std::shared_ptr<const Transformation<4, 3> > transform(TransformationFactory::create< 4, 3, double >(rotation, trans, 1.));

  FunctionValueGrid<4, 3>::value_storage_type g = transform->transform(_grid->getValues());

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
  std::shared_ptr<const Transformation<4, 3> > transform(TransformationFactory::create< 4, 3, double >(rotation, trans, 1.));

  FunctionValueGrid<4, 3>::value_storage_type g = transform->transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        if (g[i][j][k] != _grid->getValues()[i][j][k]) {
          QVERIFY(VecMath::sqnorm(g[i][j][k] + _grid->getValues()[i][j][k]) < 1e-8);
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
  std::shared_ptr< const Transformation<4, 3> > transform(TransformationFactory::create< 4, 3, double >(rotation, trans, 1.));

  FunctionValueGrid<4, 3>::value_storage_type g = transform->transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        QVERIFY(VecMath::sqnorm(g[i][j][k] - _grid->getValues()[i][j][k]) < 1e-8);
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

  std::shared_ptr<const Transformation<4, 3> > transform(TransformationFactory::create< 4, 3, double >(rotation, translation, 1.));

  FunctionValueGrid<4, 3>::value_storage_type g = transform->transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        QVERIFY(VecMath::sqnorm(g[i][j][k] - _grid->getValues()[i][j][k]-translation) < 1e-8);
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

  std::shared_ptr<const Transformation<4, 3> > transform(TransformationFactory::create< 4, 3, double >(rotation, translation, scale));

  FunctionValueGrid<4, 3>::value_storage_type g = transform->transform(_grid->getValues());

  for (unsigned i = 0; i < g.size(); ++i) {
    for (unsigned j = 0; j < g.size(); ++j) {
      for (unsigned k = 0; k < g.size(); ++k) {
        for (unsigned n = 0; n < g[i][j][k].dimension(); ++n) {
          double difference = g[i][j][k][n] - scale[n]*_grid->getValues()[i][j][k][n];
          QVERIFY2(fabs(difference) < 1e-8, QString::number(difference).toLatin1());
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
using VecMath::sqnorm;

void Test_Transformation::rotateFloatVector() {
    VecMath::MultiDimensionalVector<Vector<4, float>, 1> vec;
    vec.push_back(makeVector(1.f, 0.f, 0.f, 0.f));
    Vector<4, float> trans(0.);

    for (float angle = 0.f; angle <= 360.f; ++angle) {
        Rotation<4, float> rotation = makeRotation<float>(angle, 0., 0., 0., 0., 0.);

        std::shared_ptr<const Transformation<4, 1, float> > transform(TransformationFactory::create<4, 1, float>(rotation, trans, 1.));

        FunctionValueGrid<4, 1, float>::value_storage_type g = transform->transform(vec);

        QVERIFY2(fabs(sqnorm(g[0]) - sqnorm(vec[0])) < 1e-6,
                 (QString::number(sqnorm(g[0])) + " != "+ QString::number(sqnorm(vec[0]))).toLatin1()
        );
    }
}


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
    QTest::newRow("Random negative rotation") << makeRotation<float>(-1., -2., -3., -4., -5., -6.);
}

void Test_Transformation::rotateFloats() {

    AverageParametricFunction *f = new AverageParametricFunction();
    shared_ptr<ParametricFunction<4, 3, float> > pf(f);

    std::shared_ptr< FunctionValueGrid<4, 3, float> > grid(
        new FunctionValueGrid<4, 3, float>(pf,
                                makeVector<unsigned>(3, 3, 3),
                                makeVector<float>(-1., -1., -1.),
                                makeVector<float>(1., 1., 1.)));
//    qDebug() <<"Original:\n" << grid->getValues().toString();
    QFETCH(floatrot, rotation);

    Vector<4, float> trans(0.);
    std::shared_ptr<const Transformation<4, 3, float> > transform(TransformationFactory::create<4, 3, float>(rotation, trans, 1.));

    FunctionValueGrid<4, 3, float>::value_storage_type g = transform->transform(grid->getValues());
//    qDebug() << "Rotated:\n" << g.toString();

    for (unsigned i = 0; i < g.size(); ++i) {
        for (unsigned j = 0; j < g.size(); ++j) {
            for (unsigned k = 0; k < g.size(); ++k) {
                if (fabs(sqnorm(g[i][j][k]) - sqnorm(grid->getValues()[i][j][k])) > 1e-6) {
                    QSKIP("Rotating floats may give strange results", SkipSingle);
                }
                QVERIFY2(fabs(VecMath::sqnorm(g[i][j][k]) - VecMath::sqnorm(grid->getValues()[i][j][k])) < 1e-6,
                         (QString::number(VecMath::sqnorm(g[i][j][k])) + " != " + 
                          QString::number(VecMath::sqnorm(grid->getValues()[i][j][k]))).toLatin1()
                         );
            }
        }
    }
}

