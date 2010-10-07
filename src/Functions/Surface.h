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

#include "Function.h"

#include "ParametricFunction.h"
#include "MultiDimensionalVector.h"

#include <tr1/memory>

////////////////////////////////////////////////////////////////////////////////



/// Parametrized surface in four-space defined by \f$ f: R^2 \rightarrow R^4 \f$
/** \ingroup FunctionGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>
 */
class Surface: public Function {

  public:

    /** type of the function used to generate values, optimized with a
     *  reference as return value                                         */
    typedef VecMath::Vector<4> &function_type(double, double);
    /// the real, raw type of the function used to generate values
    typedef VecMath::Vector<4> raw_function_type (double, double);

    Surface();
    Surface (double _umin, double _umax, double _du,
             double _vmin, double _vmax, double _dv,
             ParameterMap _parms = ParameterMap());
    virtual ~Surface();

    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T);
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    virtual void Draw (UI::View *view);

    virtual void ReInit(double _tmin, double _tmax, double _dt,
                        double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv);

    /// Called by the ColorManager after setting the Function on the CM
    virtual void calibrateColors() const;

    /// \see Function::getDefinitionSpaceDimensions()
    virtual unsigned getDefinitionSpaceDimensions();

    /// Function evaluation operator for three parameters
    VecMath::Vector<4> &operator () (double u, double v, double = 0);

    virtual void for_each_vertex(function_on_fourspace_vertex apply);
    virtual void for_each_vertex_transformed(function_on_fourspace_and_transformed_vertex apply);
    virtual void for_each_vertex_transformed_projected(function_on_fourspace_transformed_and_projected_vertex apply);
    virtual void for_each_projected(function_on_projected_vertex apply);

  protected:
    virtual vec4vec1D df (double, double);
    virtual function_type normal;

    void Initialize (void);

    /// Pointer to the actual ParametricFunction doing all the work.
    std::tr1::shared_ptr< ParametricFunction<4, 2> > _function;

    unsigned getTsteps() const;
    unsigned getUsteps() const;

    /// Array of function values.
    const VecMath::MultiDimensionalVector< VecMath::Vector<4>, 2 > &X() const;
    /// Array of function values after transform.
    const VecMath::MultiDimensionalVector< VecMath::Vector<4>, 2 > &Xtrans() const;
    /// Array of projected function values.
    const VecMath::MultiDimensionalVector< VecMath::Vector<3>, 2 > &Xscr() const;

  private:

    class Impl;
    Impl *pImpl_;

};

#endif
