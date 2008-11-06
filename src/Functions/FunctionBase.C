
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "Function.H"
#include "Log.H"

using std::cerr;
using std::endl;

using VecMath::Vector;


//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////


/// Function default c'tor
/** Zeroes everything       */
Function::Function ():
    tmin (0),       tmax (0),       dt (0),
    umin (0),       umax (0),       du (0),
    vmin (0),       vmax (0),       dv (0),
    tsteps (0), usteps (0), vsteps (0),
    F (),
    functionName(""), parameterNames()
{ }


/** Function c'tor given a definition set in R³ (as parameter space)
 *  @param name a name for the function
 *  @param _tmin minimal value in t
 *  @param _tmax maximal value in t
 *  @param _dt stepsize in t
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Function::Function (const QString &name,
                    double _tmin, double _tmax, double _dt,
                    double _umin, double _umax, double _du,
                    double _vmin, double _vmax, double _dv):
    tmin (_tmin), tmax (_tmax), dt (_dt),
    umin (_umin), umax (_umax), du (_du),
    vmin (_vmin), vmax (_vmax), dv (_dv),
    tsteps (unsigned ((tmax-tmin)/dt+1)),
    usteps (unsigned ((umax-umin)/du+1)),
    vsteps (unsigned ((vmax-vmin)/dv+1)),
    F (),
    functionName(name), parameterNames() {
    if (MemRequired () > Globals::Instance().getMaxMemory()) {
        cerr << "Using a " << tsteps << "x" << usteps << "x" << vsteps
             << " grid would require approx. " << MemRequired () << " MB of memory.\n";
        while (MemRequired () > Globals::Instance().getMaxMemory()) {
            tsteps--; usteps--; vsteps--;
        }
        cerr << "Using a " << tsteps << "x" << usteps << "x" << vsteps
             << " grid instead." << endl;
        dt = (tmax-tmin)/tsteps;
        du = (umax-umin)/usteps;
        dv = (vmax-vmin)/vsteps;
    }
}



/// Placeholder for function to set parameters in descendants
/** Empty because a generic function has no parameters                        */
void Function::SetParameters (double, double, double, double) { }

/// Return the approximate amount of memory needed to display a Function of
/// current definition set
/** \todo uses hardcoded and experimentally found value for memory per cell
 *  @return approx. mem required                                              */
unsigned long Function::MemRequired (void) {
  return ((tsteps+2)*(usteps+2)*(vsteps+2)*4)/1024+8;
}



/// Numerical calculation of the derivatives in t, u and v
/** \f[
        \frac{df}{dt} = \lim_{h \rightarrow 0}
            \frac{f(t+h, u, v) - f(t, u, v)}{h},
        \frac{df}{du},\frac{df}{dv}\mbox{analogously}
    \f]
 *  @todo The h value is fixed and hardcoded. better approach, please!
 *  @todo I don't think calling operator() is right. Call f()!
 *  @param tt t value
 *  @param uu u value
 *  @param vv v value
 *  @return gradient in t, u and v as array                                   */
Function::vec4vec1D Function::df (double tt, double uu, double vv) {

    static Vector<4> F0;                //  f (u, v)
    static double h = 1e-5;
    static Function::vec4vec1D DF(3);

    F0 = operator () (tt, uu, vv);

    F = operator () (tt+h, uu, vv);     //  derive after t
    DF[0] = (F-F0)/h;

    F = operator () (tt, uu+h, vv);     //  derive after u
    DF[1] = (F-F0)/h;

    F = operator () (tt, uu, vv+h);     //  derive after v
    DF[2] = (F-F0)/h;

    return DF;
}
