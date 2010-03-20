
#include "Test_FunctionValueGrid.h"
#include "Test_ParametricFunction.h"

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
  
  _grid = shared_ptr< FunctionValueGrid<4, 3> >(new FunctionValueGrid<4, 3>(pf, DEFAULT_XMIN, DEFAULT_XMAX, DEFAULT_GRID));

}

void Test_FunctionValueGrid::initializeGrid() {
  FunctionValueGrid<4, 3> grid1();
  
  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);
  FunctionValueGrid<4, 3> grid2(pf);
  
  FunctionValueGrid<4, 3> grid3(pf, DEFAULT_XMIN, DEFAULT_XMAX, DEFAULT_GRID);
 
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
  FunctionValueGrid<4, 3> grid(pf, DEFAULT_XMIN, DEFAULT_XMAX, DEFAULT_GRID);
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
