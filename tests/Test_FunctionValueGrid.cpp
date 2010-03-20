
#include "Test_FunctionValueGrid.h"
#include "Test_ParametricFunction.h"

using std::tr1::shared_ptr;

void Test_FunctionValueGrid::initTestCase() {

  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);
  
  VecMath::Vector<3> xmin(DEFAULT_X_MIN, DEFAULT_X_MIN, DEFAULT_X_MIN);
  VecMath::Vector<3> xmax(DEFAULT_X_MAX, DEFAULT_X_MAX, DEFAULT_X_MAX);
  VecMath::Vector<3, unsigned> grid_size(DEFAULT_GRID_SIZE, DEFAULT_GRID_SIZE, DEFAULT_GRID_SIZE);
  
  _grid = shared_ptr< FunctionValueGrid<4, 3> >(new FunctionValueGrid<4, 3>(pf, xmin, xmax, grid_size));

}

void Test_FunctionValueGrid::initializeGrid() {
  FunctionValueGrid<4, 3> grid1();
  
  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);
  FunctionValueGrid<4, 3> grid2(pf);
  
  VecMath::Vector<3> xmin(DEFAULT_X_MIN, DEFAULT_X_MIN, DEFAULT_X_MIN);
  VecMath::Vector<3> xmax(DEFAULT_X_MAX, DEFAULT_X_MAX, DEFAULT_X_MAX);
  VecMath::Vector<3, unsigned> grid_size(DEFAULT_GRID_SIZE, DEFAULT_GRID_SIZE, DEFAULT_GRID_SIZE);
  FunctionValueGrid<4, 3> grid3(pf, xmin, xmax, grid_size);
 
}

void Test_FunctionValueGrid::functionValues() {
  FunctionValueGrid<4, 3>::value_storage_type values = _grid->getValues();
  for (unsigned i = 0; i < DEFAULT_GRID_SIZE; ++i) {
    for (unsigned j = 0; j < DEFAULT_GRID_SIZE; ++j) {
      for (unsigned k = 0; k < DEFAULT_GRID_SIZE; ++k) {
        QVERIFY(values[i][j][k] == VecMath::Vector<4>(0., 0., 0., Test_ParametricFunction::ParametricFunctionTestImplementation::CONST_FUNCTION_W));
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

void Test_FunctionValueGrid::resetGridSize() {
  FunctionValueGrid<4, 3>::grid_size_type oldGrid(DEFAULT_GRID_SIZE, DEFAULT_GRID_SIZE, DEFAULT_GRID_SIZE);
  _grid->setGridSize(oldGrid);
}
