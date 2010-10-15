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

#ifndef SURFACEIMPLEMENTATIONS_H
#define SURFACEIMPLEMENTATIONS_H

#include "Surface.h"

/// An example surface.
/** \f{eqnarray*}{
        F_0 & = & Radius*\sin \theta*\sin \psi   \\
        F_1 & = & Radius*\cos \theta*\sin \psi   \\
        F_2 & = & Radius*\cos \theta             \\
        F_3 & = & Radius*\cos \psi
    \f}
 *  \ingroup SurfaceGroup                                                    */
class Surface1: public Surface {
public:
    Surface1(): Surface() {
      _function = std::tr1::shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction);
    }
    Surface1 (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
    virtual ~Surface1() { }

    virtual std::string getFunctionName() const { return "Surface1"; }

private:

  /// ParametricFunction that defines Surface1
  struct DefiningFunction: public ParametricFunction<4, 2> {
    virtual return_type f(const argument_type &x);
  };

};

namespace {
    Displayable *createSurface1() { return new Surface1(); }
    const bool registeredS1 =
            TheFunctionFactory::Instance().registerFunction(createSurface1, "Surface");
}

/// A four-dimensional surface described by Thomas Banchoff.
/** \f{eqnarray*}{
        t & = & \theta*\pi                  \\
        p & = & \phi*frac{\pi}{2}           \\
        F_0 & = (1-\sin{t})*\cos{p}         \\
        F_1 & = (1-\sin{t})*\sin{p}         \\
        F_2 & = (1+\sin{t})*\cos{p}         \\
        F_3 & = (1+\sin{t})*\sin{p}         \\
        F & = & F*\frac{1}{\sqrt{2}}*\cos{t}
    \f}
 *  \ingroup SurfaceGroup                                                    */
class Horizon: public Surface {
public:
    Horizon(): Surface() {
      _function = std::tr1::shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction);
    }
    Horizon (double _umin, double _umax, double _du,
             double _vmin, double _vmax, double _dv);
    virtual ~Horizon () { }

    virtual std::string getFunctionName() const { return "Horizon"; }

private:

    /// ParametricFunction that defines Horizon
  struct DefiningFunction: public ParametricFunction<4, 2> {
    virtual return_type f(const argument_type &x);
  };

};

namespace {
    Displayable *createHorizon() { return new Horizon(); }
    const bool registeredS2 =
            TheFunctionFactory::Instance().registerFunction(createHorizon, "Surface");
}

/// Another torus version, this one as a two-dimensional surface in four-space.
/** \ingroup SurfaceGroup                                                    */
class Torus3: public Surface {
public:
    Torus3(): Surface() {
      _function = std::tr1::shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction);
    }
    Torus3 (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv);
    virtual ~Torus3 () { }

    virtual std::string getFunctionName() const { return "Torus3"; }

private:

    /// ParametricFunction that defines Torus3
  struct DefiningFunction: public ParametricFunction<4, 2> {
    virtual return_type f(const argument_type &x);
  };

};

namespace {
    Displayable *createTorus3() { return new Torus3(); }
    const bool registeredS3 =
            TheFunctionFactory::Instance().registerFunction(createTorus3, "Surface");
}

#endif // SURFACEIMPLEMENTATIONS_H
