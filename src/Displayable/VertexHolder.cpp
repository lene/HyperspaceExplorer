
#include "VertexHolder.impl.h"

namespace DepthCueUtil {
    static double Wmin = 0.;
    void checkMinimumW(const VecMath::Vector<4, double> &,
                       const VecMath::Vector<4, double> &xtrans) {
        if (xtrans[3] < Wmin) Wmin = xtrans[3];
    }
    void resetWmin() { Wmin = 0.; }
    double getWmin() { return Wmin; }
    
    static double Wmax = 0.;
    void checkMaximumW(const VecMath::Vector<4, double> &,
                       const VecMath::Vector<4, double> &xtrans) {
        if (xtrans[3] > Wmax) Wmax = xtrans[3];
    }
    void resetWmax() { Wmin = 0.; }
    double getWmax() { return Wmin; }

    void setDepthCueColor(const VecMath::Vector<4, double> &x,
                          const VecMath::Vector<4, double> &xtrans) {
        ColMgrMgr::Instance().depthCueColor(Wmax, Wmin, xtrans[3], x);
    }
}

