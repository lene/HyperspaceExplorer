
//      project:      hyperspace explorer
//      module:       CustomFunction.C
//      contains:     classes for dynamically loadable functions
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include <iostream>

#include <qmessagebox.h>

#include "CustomFunction.h"

#include "FunctionDialogImpl.h"
#include "PolarDialogImpl.h"
#include "ComplexDialogImpl.h"
#include "SurfaceDialogImpl.h"

using std::complex;
using std::cerr;
using std::endl;

using VecMath::Vector;
using namespace UI::Dialogs;

/** CustomFunction c'tor given a definition set in R� (as parameter space) and a
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
    RealFunction ("Custom function yet without a name", _tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
    if (final) {
        FunctionDialogImpl *Dlg = new FunctionDialogImpl ();

        if (Dlg->exec () == QDialog::Accepted &&
            loadFunction (Dlg->libraryName())) {
            Initialize ();
            setValid();
        } else setInvalid();
    }
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


////////////////////////////////////////////////////////////////////////////////


/** CustomPolarFunction c'tor given a definition set in R� (as parameter space)
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
    PolarDialogImpl *Dlg = new PolarDialogImpl ();

    if (Dlg->exec () == QDialog::Accepted &&
        loadFunction (Dlg->libraryName())) {
        Initialize ();
        setValid();
    } else setInvalid();
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


/** CustomComplexFunction c'tor given a definition set in C (as parameter space) and a
 *  flag indicatin whether this is a test construction or a real one
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                             */
CustomComplexFunction::CustomComplexFunction (double _umin, double _umax, double _du,
                                              double _vmin, double _vmax, double _dv):
        ComplexFunction ("Custom complex function yet without a name", _umin, _umax, _du, _vmin, _vmax, _dv) {
    ComplexDialogImpl *Dlg = new ComplexDialogImpl ();

    if (Dlg->exec () == QDialog::Accepted &&
        loadFunction(Dlg->libraryName())) {
        Initialize ();
        setValid();
    } else setInvalid();
}

/** CustomComplexFunction defining function; calls loaded function
 *  @param z (complex) z value
 *  @return custom function of z                                              */
complex<double> CustomComplexFunction::g (complex<double> z) {
    static complex<double> T;
    T = func(z);
    return T;
}

/** CustomSurface c'tor given a definition set in R� (as parameter space) and a
 *  flag indicatin whether this is a test construction or a real one
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
CustomSurface::CustomSurface (double _umin, double _umax, double _du,
                              double _vmin, double _vmax, double _dv):
        Surface ("Custom surface yet without a name", _umin, _umax, _du, _vmin, _vmax, _dv) {
    SurfaceDialogImpl *Dlg = new SurfaceDialogImpl ();

    if (Dlg->exec () == QDialog::Accepted) {
        loadFunction (Dlg->libraryName());
        Initialize ();
        setValid();
    } else setInvalid();
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
