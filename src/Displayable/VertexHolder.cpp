
#include "VertexHolder.impl.h"

namespace DepthCueUtil {
    static Vector<4> min;
    void checkMinimum(const VecMath::Vector<4, double> &,
                      const VecMath::Vector<4, double> &xtrans) {
        for (unsigned i = 0; i < 4; ++i) {
            if (xtrans[i] < min[i]) min[i] = xtrans[i];
        }
    }
    void resetMin() { 
        for (unsigned i = 0; i < 4; ++i) min[i] = 0.;
    }
    double getWmin() { return min[3]; }
    
    static Vector<4> max;
    void checkMaximum(const VecMath::Vector<4, double> &,
                       const VecMath::Vector<4, double> &xtrans) {
        for (unsigned i = 0; i < 4; ++i) {
            if (xtrans[i] > max[i]) max[i] = xtrans[i];
        }
    }
    void resetMax() { 
        for (unsigned i = 0; i < 4; ++i) max[i] = 0.;
    }
    double getWmax() { return max[3]; }

    void setDepthCueColor(const VecMath::Vector<4, double> &x,
                          const VecMath::Vector<4, double> &xtrans) {
        ColMgrMgr::Instance().depthCueColor(getWmax(), getWmin(), xtrans[3], x);
    }
    
    float getColorComponent(unsigned i, const VecMath::Vector<4,double>& x) {
        return float((x[0]-min[0])/(max[0]-min[0]));
    }
    
    void calibrateColor(const VecMath::Vector<4,double>& x) {
        ColMgrMgr::Instance().calibrateColor(
            x,
            Color(getColorComponent(0, x),
                  getColorComponent(1, x),
                  getColorComponent(2, x),
                  getColorComponent(3, x))
        );
    }
}

