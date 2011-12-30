
#include "DepthCueUtil.h"

#include "ColorManager.h"

#include "Vector.impl.h"
using VecMath::Vector;

namespace DepthCueUtil {

    static Vector<4> min;

    /** Tests whether \p xtrans is inside the lower boundary of the transformed
     *  object and resets any component of the lower boundary if not.
     *  @param xtrans the vertex to check
     */
    void checkMinimum(const VecMath::Vector<4, double> &,
                      const VecMath::Vector<4, double> &xtrans) {
        for (unsigned i = 0; i < 4; ++i) {
            if (xtrans[i] < min[i]) min[i] = xtrans[i];
        }
    }
    
    /** Reset the lower boundary of the transformed object before running a full
     *  scan to determine it.
     */ 
    void resetMin() { 
        for (unsigned i = 0; i < 4; ++i) min[i] = 1.e8;
    }

    /** Find the lower boundary of the space the transformed \p object occupies.
     * @param object Object whose lower boundary is found
     */
    void findMinimumW(Displayable *object) {
        resetMin();
        object->for_each_vertex_transformed(checkMinimum);
    }
    
    static Vector<4> max;
    
    /** Tests whether \p xtrans is inside the upper boundary of the transformed
     *  object and resets any component of the upper boundary if not.
     */
    void checkMaximum(const VecMath::Vector<4, double> &,
                       const VecMath::Vector<4, double> &xtrans) {
        for (unsigned i = 0; i < 4; ++i) {
            if (xtrans[i] > max[i]) max[i] = xtrans[i];
        }
    }

    /** Reset the upper boundary of the transformed object before running a full
     *  scan to determine it.
     */ 
    void resetMax() { 
        for (unsigned i = 0; i < 4; ++i) max[i] = -1.e8;
    }

    /** Find the upper boundary of the space the transformed \p object occupies.
     * @param object Object whose upper boundary is found
     */
    void findMaximumW(Displayable *object) {
        resetMax();
        object->for_each_vertex_transformed(checkMaximum);
    }

    /**
     * @param object Object whose boundaries are found
     */
    void determineExtrema(Displayable *object) {
        findMaximumW(object);
        findMinimumW(object);
    }

    VecMath::Vector<4> getMax() { return max; }

    VecMath::Vector<4> getMin() { return min; }
    
    void setDepthCueColor(const VecMath::Vector<4, double> &x,
                          const VecMath::Vector<4, double> &xtrans) {
        ColMgrMgr::Instance().depthCueColor(getMax()[3], getMin()[3], xtrans[3], x);
    }
    
    float getColorComponent(unsigned i, const VecMath::Vector<4,double>& x) {
        return float((x[i]-min[i])/(max[i]-min[i]));
    }
    
    void calibrateColor3D(const VecMath::Vector<4,double>& x) {
        ColMgrMgr::Instance().calibrateColor(
            x,
            Color(getColorComponent(0, x),
                  getColorComponent(1, x),
                  getColorComponent(2, x),
                  getColorComponent(3, x))
        );
    }
}

