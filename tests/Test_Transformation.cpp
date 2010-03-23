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
using std::tr1::shared_ptr;

void Test_Transformation::initTestCase() {
  
  Test_ParametricFunction::ParametricFunctionTestImplementation *f = new Test_ParametricFunction::ParametricFunctionTestImplementation();
  shared_ptr<ParametricFunction<4, 3> > pf(f);
  
  _grid = shared_ptr< FunctionValueGrid<4, 3> >(
      new FunctionValueGrid<4, 3>(pf, 
                                  Vector<3, unsigned>(5, 5, 5), 
                                  Vector<3>(-1., -1., -1.), 
                                  Vector<3>(1., 1., 1.)));

  Rotation<4> rot(1., 2., 3., 4., 5., 6.);
  Vector<4> trans(1., 1., 1., 1.);
  Transformation<4, 3> transform(rot, trans);
  
  FunctionValueGrid<4, 3>::value_storage_type g = transform.transform(_grid->getValues());
  
  _grid->getValues().print();
  g.print();
}

void Test_Transformation::cleanupTestCase() {

}
