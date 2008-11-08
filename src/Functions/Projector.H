#ifndef PROJECTOR_H
#define PROJECTOR_H

/** \todo make scrW and camW vectors for consecutive operations
 *  \todo add possibility to transform before projecting
 */
template <unsigned D, unsigned D_> class Projector: protected Projector<D-1, D_> {
    public:
        /// Project an array of vertices of dimension \p D to dimension \p D_ < \p D
        std::vector<VecMath::Vector<D_> > operator()(
                const std::vector<VecMath::Vector<D> > &x,
                double scrW, double camW) {
            if (D_ > D) {
                throw std::logic_error("Tried to project to a higher dimension");
            }
            if (D_ == D) {
                throw std::logic_error("Explicit specialization should be called");
            }
            if (camW <= scrW) {
                throw std::logic_error("Screen must be closer to object than eye");
            }

            std::vector<VecMath::Vector<D-1> > x_proj(x.size());

            for (unsigned i = 0; i < x.size(); i++) {
                double ProjectionFactor = (scrW-camW)/(x[i][D-1]-camW);

                for (unsigned j = 0; j < D-1; j++)
                    x_proj.at(i)[j] = ProjectionFactor*x[i][j];
            }
            return Projector<D-1, D_>::operator()(x_proj, scrW, camW);
        }
};

/// Specialization for \p D_ == \p D
template <unsigned D> class Projector<D, D> {
    public:
        std::vector<VecMath::Vector<D> > operator()(
            const std::vector<VecMath::Vector<D> > &x, double, double) {
            return x;
        }
};

#endif
