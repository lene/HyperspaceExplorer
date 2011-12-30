/* 
 * File:   DepthCueUtil.h
 * Author: lene
 *
 * Created on December 30, 2011, 4:20 PM
 */

#ifndef DEPTHCUEUTIL_H
#define	DEPTHCUEUTIL_H

#include "Displayable.h"

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
    
    /// Scans all vertices of the object, setting the upper and lower boundaries
    /// in all dimensions.
    void determineExtrema(Displayable *object);
    
    /// The lower boundary of the transformed object in all dimensions.
    VecMath::Vector<4> getMin();
    
    /// The upper boundary of the transformed object in all dimensions.
    VecMath::Vector<4> getMax();

    /// Sets the 4D depth cue for a single transformed vertex \p xtrans.
    void setDepthCueColor(const VecMath::Vector<4, double> &x,
                          const VecMath::Vector<4, double> &xtrans);
    
    /// Default calibration of the ColorManager for a single vertex \p x.
    /** Each component of the color (r, g, b, a) is calculated by how far the 
     *  corresponding component of the vector (x, y, z, w) lies between the min
     *  and max values for that dimension.
     */
    void calibrateColor3D(const VecMath::Vector<4, double> &x);

    /// A value between 0 and 1, how far component \p i of vector \p x lies
    /// between the extrema in the \p i th dimension.
    float getColorComponent(unsigned i, const VecMath::Vector<4,double>& x);
    
}


#endif	/* DEPTHCUEUTIL_H */

