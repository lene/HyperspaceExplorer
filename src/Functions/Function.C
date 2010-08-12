
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)

#include "Function.h"
#include "Log.h"
#include "ColorManager.h"

using std::cerr;
using std::endl;

using VecMath::Vector;


//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////


/** Zeroes everything       */
Function::Function (): _F () { }


/** \param parameters Parameters for the Function.
 */
Function::Function (ParameterMap parameters):
    _F (),
    _parameters(parameters) {
# if 0
    if (MemRequired() > Globals::Instance().getMaxMemory()) {
    }
# endif
}


/** \todo This function is only there to provide an interface, and it's
*  not abstract so that Function s which don't have Parameters don't
*  need to reimplement an unneeded method. But the present implementation
*  does not make sense.
*/
void Function::SetParameters(const ParameterMap& ) {
    std::cerr << "Function::SetParameters()" << std::endl;
}

/** \todo uses hardcoded and experimentally found value for memory per cell
*  \return approx. mem required                                              */
unsigned long Function::MemRequired (void) {
    return 0;
}

void Function::setVertex(const VecMath::Vector< 4 >& X, const VecMath::Vector< 3 >& Xscr) {
    ColMgrMgr::Instance().setColor(X);
    Globals::Instance().glVertex(Xscr);
}

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

    _F = operator () (tt+h, uu, vv);     //  derive after t
    DF[0] = (_F-F0)/h;

    _F = operator () (tt, uu+h, vv);     //  derive after u
    DF[1] = (_F-F0)/h;

    _F = operator () (tt, uu, vv+h);     //  derive after v
    DF[2] = (_F-F0)/h;

    return DF;
}
