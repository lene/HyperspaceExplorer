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

class TestFunctionHolder: public FunctionHolder<4,3> {
  
  public:
    
    virtual void Transform (const VecMath::Rotation<4, double> &R,
                                const VecMath::Vector<4, double> &T) { }
    virtual void Project (double ScrW, double CamW, bool DepthCue4D) { }
    virtual void Draw (UI::View *) { }

    virtual void ReInit(double _tmin, double _tmax, double _dt,
                        double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv) { }

        /// Called by the ColorManager after setting the Function on the CM
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
  TestFunctionHolder f;
}
