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

#include "CustomFunction.h"

#include <iostream>

#include <qmessagebox.h>
#include <qdialog.h>

#include "FunctionDialogImpl.h"
#include "PolarDialogImpl.h"
#include "ComplexDialogImpl.h"
#include "SurfaceDialogImpl.h"

#include "Vector.impl.h"

using std::complex;
using std::cerr;
using std::endl;

using VecMath::Vector;
using namespace UI::Dialogs;

template <class function_type>
template <class Dialog, class Lambda>
void CustomFunctionBase<function_type>::initializeFromDialog(Lambda code_snippet) {
    Dialog *dialog = new Dialog;
    if (dialog->exec() == QDialog::Accepted && loadFunction(dialog->libraryName())) {
        code_snippet();
        setValid();
    } else setInvalid();
}

/** CustomFunction c'tor given a definition set in \f$ R^3 \f$ (as parameter space) and a
 *  flag indicatin whether this is a test construction or a real one
 *  \param _tmin minimal value in t
 *  \param _tmax maximal value in t
 *  \param _dt stepsize in t
 *  \param _umin minimal value in u
 *  \param _umax maximal value in u
 *  \param _du stepsize in u
 *  \param _vmin minimal value in v
 *  \param _vmax maximal value in v
 *  \param _dv stepsize in v
 *  \param final real construction or test                                   */
CustomFunction::CustomFunction (double _tmin, double _tmax, double _dt,
                                double _umin, double _umax, double _du,
                                double _vmin, double _vmax, double _dv,
                                bool final):
    RealFunction (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
    if (final) {
        initializeFromDialog<FunctionDialogImpl>([&](){
                _function = std::shared_ptr<ParametricFunction<4, 3>>(new DefiningFunction(this));
                Initialize();        
        });
    }
}

std::string CustomFunction::getFunctionName() const {
    return symbolic().toStdString();
}

/** CustomFunction defining function; calls loaded function
 *  @param x x value
 *  @param y y value
 *  @param z z value
 *  @return custom function of (x, y, z)                                      */
Vector<4> &CustomFunction::f (double x, double y, double z) {
    static Vector<4> T;
    T = func(x, y, z);
    return T;
}

ParametricFunction< 4, 3 >::return_type CustomFunction::DefiningFunction::f(
  const ParametricFunction< 4, 3 >::argument_type& x) {
  return _parent->f(x[0], x[1], x[2]);
}

////////////////////////////////////////////////////////////////////////////////

/** CustomPolarFunction c'tor given a definition set in \f$ R^3 \f$ (as parameter space)
 *  and a flag indicating whether this is a test construction or a real one
 *  @param _tmin minimal value in t
 *  @param _tmax maximal value in t
 *  @param _dt stepsize in t
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
CustomPolarFunction::CustomPolarFunction (double _tmin, double _tmax, double _dt,
                                          double _umin, double _umax, double _du,
                                          double _vmin, double _vmax, double _dv):
    CustomFunction (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv, false) {
    initializeFromDialog<PolarDialogImpl>([&](){
                _function = std::shared_ptr<ParametricFunction<4, 3>>(new DefiningFunction(this));
                Initialize();        
        });
}

std::string CustomPolarFunction::getFunctionName() const {
    return CustomFunction::getFunctionName();
}


/** CustomPolarFunction defining function; calls loaded function
 *  @param x x value (these would really be phi, theta, psi)
 *  @param y y value
 *  @param z z value
 *  @return custom function of (x, y, z)                                      */
Vector<4> &CustomPolarFunction::f (double x, double y, double z) {
    static Vector<4> T;
    T = CustomFunction::func(x, y, z);
    return T;
}

ParametricFunction< 4, 3 >::return_type CustomPolarFunction::DefiningFunction::f(
  const ParametricFunction< 4, 3 >::argument_type& x) {
  return _parent->f(x[0], x[1], x[2]);
}

/** CustomComplexFunction c'tor given a definition set in \f$ C \f$ (as parameter space) and a
 *  flag indicatin whether this is a test construction or a real one
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                             
 */
CustomComplexFunction::CustomComplexFunction (double _umin, double _umax, double _du,
                                              double _vmin, double _vmax, double _dv):
        ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv) {
#if 1
    initializeFromDialog<ComplexDialogImpl>([&](){
                _function = std::shared_ptr<ParametricFunction<4, 2>>(new DefiningFunction(this));
                Initialize();        
        });
#else
    ComplexDialogImpl *Dlg = new ComplexDialogImpl ();
    if (Dlg->exec () == QDialog::Accepted && loadFunction(Dlg->libraryName())) {
        _function = std::shared_ptr<ParametricFunction<4,2>>(new DefiningFunction(this));
        Initialize ();
        setValid();
    } else setInvalid();
#endif    
}

std::string CustomComplexFunction::getFunctionName() const {
    return symbolic().toStdString();
}

/** CustomComplexFunction defining function; calls loaded function
 *  @param z (complex) z value
 *  @return custom function of z                                              */
complex<double> CustomComplexFunction::g (complex<double> z) {
    static complex<double> T;
    T = func(z);
    return T;
}

ParametricFunction< 4, 2 >::return_type CustomComplexFunction::DefiningFunction::f(
  const ParametricFunction< 4, 2 >::argument_type& x) {
  ParametricFunction< 4, 2 >::return_type F;
  complex< double > g = _parent->g(std::complex<double>(x[0], x[1]));
  F[0] = x[0];
  F[1] = x[1];
  F[2] = g.real();
  F[3] = g.imag();
  return F;
}

/** CustomSurface c'tor given a definition set in \f$ R^3 \f$ (as parameter space) and a
 *  flag indicatin whether this is a test construction or a real one
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
CustomSurface::CustomSurface (double _umin, double _umax, double _du,
                              double _vmin, double _vmax, double _dv):
        Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
    initializeFromDialog<SurfaceDialogImpl>([&](){
                _function = std::shared_ptr<ParametricFunction<4, 2>>(new DefiningFunction(this));
                Initialize();        
        });
}

std::string CustomSurface::getFunctionName() const {
    return symbolic().toStdString();
}


/** CustomFunction defining function; calls loaded function
 *  @param u u value
 *  @param v v value
 *  @return custom function of (u, v)                                         */
Vector<4> &CustomSurface::f (double u, double v) {
    static Vector<4> T;
    T = func(u, v);
    return T;
}

ParametricFunction< 4, 2 >::return_type CustomSurface::DefiningFunction::f(
  const ParametricFunction< 4, 2 >::argument_type& x) {
  return _parent->f(x[0], x[1]);
}
