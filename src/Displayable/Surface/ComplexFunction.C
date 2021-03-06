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

#include "Globals.h"

#include "ComplexFunction.h"

#include "Vector.impl.h"

#include <QString>

using std::complex;
using std::shared_ptr;

using VecMath::Vector;

const QString ComplexFunction::sup2 = QString(QChar(0x00B2));
const QString ComplexFunction::sup3 = QString(QChar(0x00B3));

///////////////////////////////////////////////////////////////////////////////

/** ComplexFunction c'tor given a definition set in \f$ R^2 \f$ (as parameter
 *  space)
 *  \param _umin minimal value in u
 *  \param _umax maximal value in u
 *  \param _du stepsize in u
 *  \param _vmin minimal value in v
 *  \param _vmax maximal value in v
 *  \param _dv stepsize in v
 */
ComplexFunction::ComplexFunction (double _umin, double _umax, double _du,
                                  double _vmin, double _vmax, double _dv):
  Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
    _function = shared_ptr< ParametricFunction<4, 2> >(new DefiningFunction(this));
}

/** ComplexFunction destructor                                                */
ComplexFunction::~ComplexFunction () { }


ParametricFunction< 4, 2 >::return_type ComplexFunction::DefiningFunction::f(const ParametricFunction< 4, 2 >::argument_type& x) {

  complex<double> z(x[0], x[1]), w = _complex_function->g(z);

  Vector<4> F;
  F[0] = x[0];
  F[1] = x[1];
  F[2] = w.real();
  F[3] = w.imag();

  return F;

}

///////////////////////////////////////////////////////////////////////////////

/** \f$ z^2 \f$ c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)                                        */
z2::z2 (double _umin, double _umax, double _du,
        double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
    Initialize ();
}

/** \f$ z^2 \f$ defining function
 *  @param z operand
 *  @return \f$ z^2 \f$                                                            */
complex<double> z2::g (complex<double> z) {
    return z*z;
}

///////////////////////////////////////////////////////////////////////////////


/** \f$ z^3 \f$ c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)                                        */
z3::z3 (double _umin, double _umax, double _du,
        double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
    Initialize ();
}

/** \f$ z^3 \f$ defining function
 *  @param z operand
 *  @return \f$ z^3 \f$                                                            */
complex<double> z3::g (complex<double> z) {
    return z*z*z;
}

///////////////////////////////////////////////////////////////////////////////


/** z^a c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)
 *  @param _alpha	exponent                                                  */
zA::zA (double _umin, double _umax, double _du,
        double _vmin, double _vmax, double _dv,
        double _alpha):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
    alpha (_alpha) {
    Initialize ();
    declareParameter("a", 2.0);
    }

/** z^a defining function
 *  @param z		operand
 *  @return		z^alpha                                                      */
complex<double> zA::g (complex<double> z) {
    return pow (z, alpha);
}

///////////////////////////////////////////////////////////////////////////////


/** e^z c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)
 *  @param alpha	exponent multiplicator                                    */
ez::ez (double _umin, double _umax, double _du,
        double _vmin, double _vmax, double _dv,
        double alpha):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
    _alpha (alpha) {
    Initialize ();
    declareParameter("a", 2.0);
}

/** e^z defining function
 *  @param z		operand
 *  @return		e^(alpha*z)                                                   */
complex<double> ez::g (complex<double> z) {
    return exp (_alpha*z);
}

///////////////////////////////////////////////////////////////////////////////


/** c'tor for \f$ e^{- z^2} \f$ given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)
 *  @param alpha	exponent multiplicator
 */
emz2::emz2 (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv,
            double alpha):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
  _alpha (alpha) {
  Initialize ();
  declareParameter("a", 1.0);
}

/** e^-\f$ z^2 \f$ defining function
 *  @param z operand
 *  @return \f$ e^{-\alpha*z^2} \f$
 */
complex<double> emz2::g (complex<double> z) {
  return exp (-_alpha*z*z);
}


///////////////////////////////////////////////////////////////////////////////


/** z^-1 c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)
 */
zm1::zm1 (double _umin, double _umax, double _du,
	  double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** z^-1 defining function
 *  @param z		operand
 *  @return		1/z
 */
complex<double> zm1::g (complex<double> z) {
  return 1./z;
}


///////////////////////////////////////////////////////////////////////////////


/** z^-2 c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)
 */
zm2::zm2 (double _umin, double _umax, double _du,
	  double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** z^-2 defining function
 *  @param z		operand
 *  @return		1/z�
 */
complex<double> zm2::g (complex<double> z) {
  return 1./(z*z);
}


///////////////////////////////////////////////////////////////////////////////


/** sqrt(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)
 */
sqrtz::sqrtz (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** sqrt (z) defining function
 *  @param z        operand
 *  @return         sqrt(z)
 */
complex<double> sqrtz::g (complex<double> z) {
  return sqrt (z);
}


///////////////////////////////////////////////////////////////////////////////


/** ln(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)
 */
lnz::lnz (double _umin, double _umax, double _du,
	  double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** ln(z) defining function
 *  @param z		operand
 *  @return		ln(z)
 */
complex<double> lnz::g (complex<double> z) {
  return log (z);
}


///////////////////////////////////////////////////////////////////////////////


/** sin(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)
 */
sinz::sinz (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** sin(z) defining function
 *  @param z		operand
 *  @return		sin(pi*z)
 */
complex<double> sinz::g (complex<double> z) {
  return sin (pi*z);
}


///////////////////////////////////////////////////////////////////////////////


/** cos(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)
 */
cosz::cosz (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** cos(z) defining function
 *  @param z operand
 *  @return cos (pi*z) */
complex<double> cosz::g (complex<double> z) {
  return cos (pi*z);
}


///////////////////////////////////////////////////////////////////////////////


/** sinh(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin minimal value in Re (z)
 *  @param _umax maximal value in Re (z)
 *  @param _du stepsize in Re (z)
 *  @param _vmin minimal value in Im (z)
 *  @param _vmax maximal value in Im (z)
 *  @param _dv stepsize in Im (z)                                             */
sinhz::sinhz (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** sinh(z) defining function
 *  @param z operand
 *  @return sinh(pi*z)       */
complex<double> sinhz::g (complex<double> z) {
  return sinh (pi*z);
}


///////////////////////////////////////////////////////////////////////////////


/** cosh(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)                                    */
coshz::coshz (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** cosh(z) defining function
 *  @param z		operand
 *  @return		cosh(pi*z)  */
complex<double> coshz::g (complex<double> z) {
  return cosh (pi*z);
}


///////////////////////////////////////////////////////////////////////////////


/** tan(z) c'tor given a definition set in C (as parameter space)
 *  @param _umin	minimal value in Re (z)
 *  @param _umax	maximal value in Re (z)
 *  @param _du		stepsize in Re (z)
 *  @param _vmin	minimal value in Im (z)
 *  @param _vmax	maximal value in Im (z)
 *  @param _dv		stepsize in Im (z)                                    */
tanz::tanz (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}

/** tan(z) defining function
 *  @param z operand
 *  @return tan (pi*z)      */
complex<double> tanz::g (complex<double> z) {
  return sin (pi*z)/cos (pi*z);
}


///////////////////////////////////////////////////////////////////////////////

/// constructor
Polynomial::Polynomial (double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv,
                        double _a1, double _a2, double _a3, double _a4):
  ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
  a[0] = 0; a[1] = _a1; a[2] = _a2; a[3] = _a3; a[4] = _a4;
  Initialize ();
}

complex<double> Polynomial::g (complex<double> z) {
  return ((((a[4]*z)+a[3])*z+a[2])*z+a[1])*z;
}
