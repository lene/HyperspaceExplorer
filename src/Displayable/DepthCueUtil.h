/* 
 * File:   DepthCueUtil.h
 * Author: lene
 *
 * Created on December 30, 2011, 4:20 PM
 */

#ifndef DEPTHCUEUTIL_H
#define	DEPTHCUEUTIL_H

/// Functions used for calculating four-dimensional depth cue
/** Because these functions are parameters to Displayable::for_each_vertex(),
 *  they need to be global to fit the signature.
 * 
 *  namespace DepthCueUtil can and will be added to in other source files to
 *  define functions supplied to VertexHolder<N,P,NUM>::calibrateColor().
 *  Example:
 *  \code
 *  namespace DepthCueUtil {
 *
 *    void calibrateColorForSomething(const VecMath::Vector<4, double> &x) {
 *      // ...
 *      ColMgrMgr::Instance().calibrateColor(x, Color(r, g, b));
 *    }
 *   
 *  }
 *  Something::Something():
 *    VertexHolder<4, 2, double>(ParameterMap()) {
 *    setColorCalibrationFunction(DepthCueUtil::calibrateColorForSomething);
 *  }
 *  \endcode
 */
namespace DepthCueUtil {
    
    void checkMinimum(const VecMath::Vector<4, double> &,
                       const VecMath::Vector<4, double> &xtrans);
    void resetMin();
    double getWmin();
    
    void checkMaximum(const VecMath::Vector<4, double> &,
                       const VecMath::Vector<4, double> &xtrans);
    void resetMax();
    double getWmax();

    void setDepthCueColor(const VecMath::Vector<4, double> &x,
                          const VecMath::Vector<4, double> &xtrans);
    
    void calibrateColor3D(const VecMath::Vector<4, double> &x);

    float getColorComponent(unsigned i, const VecMath::Vector<4,double>& x);
    
}


#endif	/* DEPTHCUEUTIL_H */

