/* 
 * File:   Projector.impl.h
 * Author: lene
 *
 * Created on March 31, 2014, 4:40 PM
 */

#ifndef PROJECTOR_IMPL_H
#define	PROJECTOR_IMPL_H

#include "Projector.h"

template <unsigned D, unsigned D_>
std::vector<VecMath::Vector<D_> > Projector< D, D_>::operator () (
    const std::vector<VecMath::Vector<D> > &x, double scrW, double camW
) {
    checkConsistency(scrW, camW);

    std::vector<VecMath::Vector<D-1> > x_proj = doProject(x, scrW, camW);
    return Projector<D-1, D_>::operator()(x_proj, scrW, camW);
}


template <unsigned D, unsigned D_>
std::vector<VecMath::Vector<D_> > Projector< D, D_>::operator () (
    const std::vector<VecMath::Vector<D> > &x, 
    const std::vector<double> &scrW, const std::vector<double> &camW
)  {
    throw NotYetImplementedException("std::vector<VecMath::Vector<D_> > \n"
        "    Projector<D, D_>::operator()(\n"
        "        vector<Vector<D> > &, vector<double> &, "
        "vector<double> &)");
}

template <unsigned D, unsigned D_>
void Projector< D, D_>::checkConsistency(double scrW, double camW) {
    if (D_ > D) {
        throw std::logic_error("Tried to project to a higher dimension");
    }
    if (D_ == D) {
        throw std::logic_error("Explicit specialization should be called");
    }
    if (camW <= scrW) {
        throw std::logic_error("Screen must be closer to object than eye");
    }
}

template <unsigned D, unsigned D_>
std::vector<VecMath::Vector<D-1> > Projector< D, D_>::doProject(
    const std::vector<VecMath::Vector<D> > &x, double scrW, double camW
) {
    std::vector<VecMath::Vector<D-1> > x_proj(x.size());

    for (unsigned i = 0; i < x.size(); i++) {
        double ProjectionFactor = (scrW-camW)/(x[i][D-1]-camW);

        for (unsigned j = 0; j < D-1; j++)
            x_proj.at(i)[j] = ProjectionFactor*x[i][j];
    }
    return x_proj;
}

#endif	/* PROJECTOR_IMPL_H */

