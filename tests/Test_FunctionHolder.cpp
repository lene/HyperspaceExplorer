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

#include "Test_FunctionHolder.h"

#include "FunctionHolder.impl.h"
#include "MultiDimensionalVector.impl.h"

#include "Test_ParametricFunction.h"

class TestFunctionHolder: public FunctionHolder<4,3> {
  
  public:
    TestFunctionHolder(std::tr1::shared_ptr< function_type > f): FunctionHolder< 4, 3>(f) { }
    TestFunctionHolder(function_type *f): FunctionHolder< 4, 3>(std::tr1::shared_ptr< function_type > (f)) { }
    virtual void Transform (const VecMath::Rotation<4, double> &,
                            const VecMath::Vector<4, double> &) { }
    virtual void Project (double, double, bool) { }
    virtual void Draw (UI::View *) { }
    virtual void ReInit(double, double, double,
                        double, double, double,
                        double, double, double) { }
    virtual void calibrateColors() const { }
    virtual std::string getFunctionName() const { return ""; } 
    virtual void for_each(function_on_fourspace_vertex apply) { }
    virtual void for_each(function_on_projected_vertex apply) { }
    virtual VecMath::Vector<4> &operator () (double, double, double) { 
      static VecMath::Vector<4> v;
      return v;
    }
    virtual void Initialize (void) { }    

};

void Test_FunctionHolder::instantiate() {
  Test_ParametricFunction::ParametricFunctionTestImplementation function;
  TestFunctionHolder holder(new Test_ParametricFunction::ParametricFunctionTestImplementation);
  QVERIFY(holder.getNumParameters() == function.getNumParameters());
}

