
#include "Test_FunctionValueGrid.h"
#include "Test_ParametricFunction.h"

using std::tr1::shared_ptr;

void Test_FunctionValueGrid::initialize() {
  FunctionValueGrid<4, 3> grid1();
  
  Test_ParametricFunction::ParametricFunctionTestImplementation f;
  FunctionValueGrid<4, 3> grid2(shared_ptr<ParametricFunction<4, 3> >(&f));
  
  VecMath::Vector<3> xmin(-1., -1., -1.);
  VecMath::Vector<3> xmax(1., 1., 1.);
  VecMath::Vector<3, unsigned> grid_size(10, 10, 10);
  QSKIP("double free?", SkipSingle);
  FunctionValueGrid<4, 3> grid3(shared_ptr<ParametricFunction<4, 3> >(&f), xmin, xmax, grid_size);
  

}
