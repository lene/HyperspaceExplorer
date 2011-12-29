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

#if(!defined SURFACE_H)
#define SURFACE_H

#include "FunctionHolder.h"

#include "ParametricFunction.h"
#include "MultiDimensionalVector.h"

#include <memory>

////////////////////////////////////////////////////////////////////////////////



/// Parametrized surface in four-space defined by \f$ f: R^2 \rightarrow R^4 \f$
/** \ingroup FunctionGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>
 */
class Surface: public FunctionHolder<4, 2, double> {

  public:

    /** type of the function used to generate values, optimized with a
     *  reference as return value                                         */
    typedef VecMath::Vector<4> &function_type(double, double);
    /// the real, raw type of the function used to generate values
    typedef VecMath::Vector<4> raw_function_type (double, double);

    Surface();
    Surface (double umin, double umax, double du,
             double vmin, double vmax, double dv,
             ParameterMap parms = ParameterMap());
    virtual ~Surface();

    virtual void Project (double ScrW, double CamW, bool DepthCue4D);

    virtual void ReInit(double _tmin, double _tmax, double _dt,
                        double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv);

    /// Called by the ColorManager after setting the Function on the CM
    virtual void calibrateColors() const;

    /// Function evaluation operator for three parameters
    VecMath::Vector<4> &operator () (double u, double v, double = 0);

    /** \return number of parameters for the function */
    virtual unsigned getNumParameters();

  protected:
    virtual VecMath::MultiDimensionalVector< VecMath::Vector<4>, 1 > df (double, double);
    virtual function_type normal;

    void Initialize (void);

    /// Pointer to the actual ParametricFunction doing all the work.
    std::shared_ptr< ParametricFunction<4, 2> > _function;

  private:

    class Impl;
    Impl *pImpl_;

};

namespace {
  static DisplayableClass displayable_class_surface(
    "Surface", "Surfaces in R^4", "Displayable"
  );
}

#endif
