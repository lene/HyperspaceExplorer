
#include "Test_FunctionValueGrid.h"
#include "Test_ParametricFunction.h"

using std::tr1::shared_ptr;

void Test_FunctionValueGrid::initTestCase() {

  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);
  
  VecMath::Vector<3> xmin(-1., -1., -1.);
  VecMath::Vector<3> xmax(1., 1., 1.);
  VecMath::Vector<3, unsigned> grid_size(10, 10, 10);
  
  _grid = shared_ptr< FunctionValueGrid<4, 3> >(new FunctionValueGrid<4, 3>(pf, xmin, xmax, grid_size));

}

void Test_FunctionValueGrid::initializeGrid() {
  FunctionValueGrid<4, 3> grid1();
  
  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);
  FunctionValueGrid<4, 3> grid2(pf);
  
  VecMath::Vector<3> xmin(-1., -1., -1.);
  VecMath::Vector<3> xmax(1., 1., 1.);
  VecMath::Vector<3, unsigned> grid_size(10, 10, 10);
  FunctionValueGrid<4, 3> grid3(pf, xmin, xmax, grid_size);
 
}

void Test_FunctionValueGrid::functionValues() {

}
