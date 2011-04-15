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

#include "SurfaceImplementations.h"

#include "Vector.impl.h"

using VecMath::Vector;
using std::tr1::shared_ptr;

/** Surface1 c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Surface1::Surface1 (double _umin, double _umax, double _du,
                    double _vmin, double _vmax, double _dv):
        Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {

    _function = shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction(this));
    Initialize();
}

Vector<4> Surface1::DefiningFunction::f (const Vector<2> &x) {
  double uu = x[0], vv = x[1];
  double sintht = sin (pi*uu), costht = cos (pi*uu),
         sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
         Radius = 1;
  Vector<4> F;
  F[0] = Radius*sintht*sinpsi;
  F[1] = Radius*costht*sinpsi;
  F[2] = Radius*costht;
  F[3] = Radius*cospsi;

  return F;
}



///////////////////////////////////////////////////////////////////////////////


/** Horizon c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Horizon::Horizon (double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv):
    Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
    _function = shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction(this));
    Initialize ();
}

Vector<4> Horizon::DefiningFunction::f (const Vector<2> &x) {
  double t = x[0]*pi, phi = x[1]*pi/2.;

  Vector<4> F;
  F[0] = (1-sin (t))*cos (phi);
  F[1] = (1-sin (t))*sin (phi);
  F[2] = (1+sin (t))*cos (phi);
  F[3] = (1+sin (t))*sin (phi);
  F *= 1./sqrt (2.)*cos (t);

  return F;
}

////////////////////////////////////////////////////////////////////////////////


/** Torus3 c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Torus3::Torus3 (double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv):
        Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
    _function = shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction(this));
    Initialize ();
}

/** Torus3 defining function
 *  @param theta u value
 *  @param phi v value
 *  @return (costht, sintht, cosphi, sinphi)                                  */
Vector<4> Torus3::DefiningFunction::f (const Vector<2> &x) {
  double theta = x[0]*pi, phi = x[1]*pi;

  Vector<4> F;
  F[0] = cos (theta);
  F[1] = sin (theta);
  F[2] = cos (phi);
  F[3] = sin (phi);

  return F;
}
