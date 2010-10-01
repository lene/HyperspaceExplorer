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

#include "Test_FunctionValueGrid.h"
#include "Test_ParametricFunction.h"

#include "MultiDimensionalVector.impl.h"

using std::tr1::shared_ptr;
using VecMath::Vector;

const Vector<3> Test_FunctionValueGrid::DEFAULT_XMIN(
  Test_FunctionValueGrid::DEFAULT_X_MIN, Test_FunctionValueGrid::DEFAULT_X_MIN, Test_FunctionValueGrid::DEFAULT_X_MIN
);
const Vector<3> Test_FunctionValueGrid::DEFAULT_XMAX(
  Test_FunctionValueGrid::DEFAULT_X_MAX, Test_FunctionValueGrid::DEFAULT_X_MAX, Test_FunctionValueGrid::DEFAULT_X_MAX
);
const Vector<3, unsigned> Test_FunctionValueGrid::DEFAULT_GRID(
  Test_FunctionValueGrid::DEFAULT_GRID_SIZE, Test_FunctionValueGrid::DEFAULT_GRID_SIZE, Test_FunctionValueGrid::DEFAULT_GRID_SIZE
);

class SummedArgsTestImplementation: public ParametricFunction<4,3> {
  public:
    SummedArgsTestImplementation(): min_w(1e8), max_w(-1e8) { }

    virtual return_type f(const argument_type &x) {
      double sum = 0;
      for (unsigned i = 0; i < argument_type::dimension(); ++i) sum += x[i];
      if (sum < min_w) min_w = sum;
      if (sum > max_w) max_w = sum;
      return Vector<4>(x[0], x[1], x[2], sum);
    }

    double min_w, max_w;
};

void Test_FunctionValueGrid::initTestCase() {

  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);

  _grid = shared_ptr< FunctionValueGrid<4, 3> >(new FunctionValueGrid<4, 3>(pf, DEFAULT_GRID, DEFAULT_XMIN, DEFAULT_XMAX));

}

void Test_FunctionValueGrid::initializeGrid() {
  FunctionValueGrid<4, 3> grid1();

  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);
  FunctionValueGrid<4, 3> grid2(pf);

  FunctionValueGrid<4, 3> grid3(pf, DEFAULT_GRID);

  FunctionValueGrid<4, 3> grid4(pf, DEFAULT_GRID, DEFAULT_XMIN, DEFAULT_XMAX);

}

void Test_FunctionValueGrid::functionValues() {
  FunctionValueGrid<4, 3>::value_storage_type values = _grid->getValues();
  for (unsigned i = 0; i < DEFAULT_GRID_SIZE; ++i) {
    for (unsigned j = 0; j < DEFAULT_GRID_SIZE; ++j) {
      for (unsigned k = 0; k < DEFAULT_GRID_SIZE; ++k) {
        QVERIFY(values[i][j][k] == Vector<4>(0., 0., 0., Test_ParametricFunction::ParametricFunctionTestImplementation::CONST_FUNCTION_W));
      }
    }
  }
}

void Test_FunctionValueGrid::changeGridSize() {
  const unsigned newGridSize = 5;
  FunctionValueGrid<4, 3>::grid_size_type newGrid(newGridSize, newGridSize, newGridSize);

  _grid->setGridSize(newGrid);

  FunctionValueGrid<4, 3>::value_storage_type values = _grid->getValues();
  QVERIFY(values.size() == newGridSize);
  QVERIFY(values[0].size() == newGridSize);
  QVERIFY(values[0][0].size() == newGridSize);

  resetGridSize();
}

void Test_FunctionValueGrid::inhomogenousGridSize() {
  FunctionValueGrid<4, 3>::grid_size_type newGrid(5, 10, 15);

  _grid->setGridSize(newGrid);

  FunctionValueGrid<4, 3>::value_storage_type values = _grid->getValues();
  QVERIFY(values.size() == 15);
  QVERIFY(values[0].size() == 10);
  QVERIFY(values[0][0].size() == 5);

  for (unsigned i = 0; i < values.size(); ++i) {
    for (unsigned j = 0; j < values[0].size(); ++j) {
      for (unsigned k = 0; k < values[0][0].size(); ++k) {
        QVERIFY(values[i][j][k] == VecMath::Vector<4>(0., 0., 0., Test_ParametricFunction::ParametricFunctionTestImplementation::CONST_FUNCTION_W));
      }
    }
  }

  resetGridSize();
}

void Test_FunctionValueGrid::nonconstantFunctionAndBoundaries() {
  SummedArgsTestImplementation *f = new SummedArgsTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);
  FunctionValueGrid<4, 3> grid(pf, DEFAULT_GRID, DEFAULT_XMIN, DEFAULT_XMAX);
  QVERIFY(f->max_w > f->min_w);

  FunctionValueGrid<4, 3>::value_storage_type values = grid.getValues();
  for (unsigned i = 0; i < DEFAULT_GRID_SIZE; ++i) {
    for (unsigned j = 0; j < DEFAULT_GRID_SIZE; ++j) {
      for (unsigned k = 0; k < DEFAULT_GRID_SIZE; ++k) {
        QVERIFY2(values[i][j][k][3] <= f->max_w, values[i][j][k].toString().c_str());
        QVERIFY2(values[i][j][k][3] >= f->min_w, values[i][j][k].toString().c_str());
      }
    }
  }

  grid.setBoundaries(Vector<3>(-2., -2., -2.), Vector<3>(2., 2., 2.));
  QVERIFY2(f->min_w == -6, QString::number(f->min_w).toAscii());
  QVERIFY2(f->max_w == 6, QString::number(f->max_w).toAscii());
}


void Test_FunctionValueGrid::resetGridSize() {
  FunctionValueGrid<4, 3>::grid_size_type oldGrid(DEFAULT_GRID_SIZE, DEFAULT_GRID_SIZE, DEFAULT_GRID_SIZE);
  _grid->setGridSize(oldGrid);
}


class AverageParametricFunction: public ParametricFunction<4,3, float> {
    public:
        AverageParametricFunction() { }
        virtual return_type f(const argument_type &x) {
            return VecMath::makeVector(x[0],x[1],x[2],(x[0]+x[1]+x[2])/3.f);
        }
};
const Vector<3, float> DEFAULT_FLOAT_XMIN = VecMath::makeVector(-1.f, -1.f, -1.f);
const Vector<3, float> DEFAULT_FLOAT_XMAX = VecMath::makeVector(-1.f, -1.f, -1.f);

void Test_FunctionValueGrid::floatValues() {

    shared_ptr< ParametricFunction<4, 3, float> > pf(new AverageParametricFunction());

    shared_ptr< FunctionValueGrid<4, 3, float> > float_grid = shared_ptr< FunctionValueGrid<4, 3, float> > (new FunctionValueGrid<4, 3, float>(pf, DEFAULT_GRID, DEFAULT_FLOAT_XMIN, DEFAULT_FLOAT_XMAX));

    FunctionValueGrid<4, 3, float>::value_storage_type values = float_grid->getValues();
    for (unsigned i = 0; i < DEFAULT_GRID_SIZE; ++i) {
        for (unsigned j = 0; j < DEFAULT_GRID_SIZE; ++j) {
            for (unsigned k = 0; k < DEFAULT_GRID_SIZE; ++k) {
                if (fabs(values[i][j][k][3] - (values[i][j][k][0]+values[i][j][k][1]+values[i][j][k][2])/3.) > 1e-6) {
                    QFAIL(values[i][j][k].toString().c_str());
                }

            }
        }
    }

}


#include <complex>
using std::complex;

class AverageComplexParametricFunction: public ParametricFunction< 4,3, complex<double> > {
    public:
        AverageComplexParametricFunction() { }
        virtual return_type f(const argument_type &x) {
            return VecMath::makeVector(x[0],x[1],x[2],(x[0]+x[1]+x[2])/complex<double>(3.));
        }
};
const Vector< 3, complex<double> > DEFAULT_COMPLEX_XMIN = VecMath::makeVector(complex<double>(-1.), complex<double>(-1.), complex<double>(-1.));
const Vector< 3, complex<double> > DEFAULT_COMPLEX_XMAX = VecMath::makeVector(complex<double>(-1.), complex<double>(-1.), complex<double>(-1.));

void Test_FunctionValueGrid::complexValues() {
    shared_ptr< ParametricFunction< 4, 3, complex<double> > > pf(new AverageComplexParametricFunction());

    shared_ptr< FunctionValueGrid< 4, 3, complex<double> > > complex_grid =
        shared_ptr< FunctionValueGrid< 4, 3, complex<double> > > (
            new FunctionValueGrid< 4, 3, complex<double> >(pf, DEFAULT_GRID, DEFAULT_COMPLEX_XMIN, DEFAULT_COMPLEX_XMAX)
        );

    FunctionValueGrid<4, 3, complex<double> >::value_storage_type values = complex_grid->getValues();
    for (unsigned i = 0; i < DEFAULT_GRID_SIZE; ++i) {
        for (unsigned j = 0; j < DEFAULT_GRID_SIZE; ++j) {
            for (unsigned k = 0; k < DEFAULT_GRID_SIZE; ++k) {
                if (abs(values[i][j][k][3] - (values[i][j][k][0]+values[i][j][k][1]+values[i][j][k][2])/3.) > 1e-6) {
                    QFAIL(values[i][j][k].toString().c_str());
                }

            }
        }
    }
}
