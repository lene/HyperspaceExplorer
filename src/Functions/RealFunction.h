/*
    Hyperspace Explorer - visualizing higher-dimensional geometry
    Copyright (C) 2008-2010 Lene Preuss <lene.preuss@gmail.com>

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
    (Seriously, has anyone ever done this?)

*/
#ifndef REAL_FUNCTION_H
#define REAL_FUNCTION_H

#include "FunctionHolder.h"

#include "ParametricFunction.h"
#include "MultiDimensionalVector.h"

#include <memory>

/// A RealFunction is a mathematical function  \f$ f: R^3 \rightarrow R \f$ .
/** The function \em f is evaluated on a 3-dimensional cartesian grid. The
 *  function value constitutes the fourth dimension of the Function object:
 *  \f$ \vec{x} = ( x, y, z, f(x, y, z) ) \f$.
 *
 *  The parent class Function provides the evaluation on the grid, together
 *  with methods to rotate and translate the grid in 4-space,  to project the
 *  transformed grid onto 3-space, and to draw the projected grid into an OpenGL
 *  display list.
 *
 *  \ingroup RealGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>                         */
class RealFunction: public FunctionHolder<4, 3, double> {

  public:

    /** type of the function used to generate values, optimized with a
     *  reference as return value
     */
    typedef VecMath::Vector<4> &function_type(double, double, double);
    /// the real, raw type of the function used to generate values
    typedef VecMath::Vector<4> raw_function_type (double, double, double);

    RealFunction();
    RealFunction(ParametricFunction<4, 3> *function);
    RealFunction(double tmin, double tmax, double dt,
                 double umin, double umax, double du,
                 double vmin, double vmax, double dv,
                 ParameterMap _parms = ParameterMap());
    virtual ~RealFunction();

    virtual void Project (double ScrW, double CamW, bool DepthCue4D);

    virtual void ReInit(double tmin, double tmax, double dt,
                        double umin, double umax, double du,
                        double vmin, double vmax, double dv);

    /// Called by the ColorManager after setting the Function on the CM
    virtual void calibrateColors() const;

    /** \return The name of the function in cleartext                     */
    virtual std::string getFunctionName() const;
    
    /// \see Function::getDefinitionSpaceDimensions()
    virtual unsigned getDefinitionSpaceDimensions();

    /// Function evaluation operator for three parameters
    VecMath::Vector<4> &operator () (double t, double u, double v);

    /** \return number of parameters for the function */
    virtual unsigned getNumParameters();

  protected:

    VecMath::Vector<4> &normal(double t, double u, double v);

    /// Allocate and initialize X[][][] with values of f().
    virtual void Initialize (void);

    /// Pointer to the actual ParametricFunction doing all the work.
    std::tr1::shared_ptr< ParametricFunction<4, 3> > _function;

  private:

    class Impl;
    std::unique_ptr<Impl> pImpl_;

};

namespace {
  DisplayableClass displayable_class_real_function(
    "RealFunction", "Functions R³ -> R", "FunctionHolder"
  );
}
#endif
