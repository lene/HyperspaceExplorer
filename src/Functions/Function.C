
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "Function.H"
#include "Log.H"
#include "ColorManager.H"

using std::cerr;
using std::endl;

using VecMath::Vector;


//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////


/// Function default c'tor
/** Zeroes everything       */
Function::Function ():
    F (),
    functionName("")//, parameterNames()
{ }


/** Function c'tor given a definition set in R³ (as parameter space)
 *  \param name a name for the function
 *  \param _parameters
 */
Function::Function (const QString &name, ParameterMap _parameters):
    F (),
    functionName(name),// parameterNames(),
    parameters(_parameters) {
    if (MemRequired () > Globals::Instance().getMaxMemory()) {
    }
}

/// Return the approximate amount of memory needed to display a Function of
/// current definition set
/** \todo uses hardcoded and experimentally found value for memory per cell
 *  \return approx. mem required                                              */
unsigned long Function::MemRequired (void) {
  return 0;
}

void Function::setVertex(const VecMath::Vector<4> &X, VecMath::Vector<3> &Xscr) {
    ColMgrMgr::Instance().setColor(X);
    Globals::Instance().glVertex(Xscr);
}

/// Numerical calculation of the derivatives in t, u and v
/** \f[
        \frac{df}{dt} = \lim_{h \rightarrow 0}
            \frac{f(t+h, u, v) - f(t, u, v)}{h},
        \frac{df}{du},\frac{df}{dv}\mbox{analogously}
    \f]
 *  \todo The h value is fixed and hardcoded. better approach, please!
 *  \todo I don't think calling operator() is right. Call f()!
 *  \param tt t value
 *  \param uu u value
 *  \param vv v value
 *  \return gradient in t, u and v as array                                   */
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
