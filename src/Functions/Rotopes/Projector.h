#ifndef PROJECTOR_H
#define PROJECTOR_H

/// A functor class to project a \p D -dimensional object to \p D-1 dimensions
/**
 *  \param D Original dimension of the object
 *  \param D_ Dimension to project onto
 *
 *  \todo make scrW and camW vectors for consecutive operations
 *  \todo add possibility to transform before projecting - or make a process
 *        separate from projection
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <lene.preuss@gmail.com>
 */
template <unsigned D, unsigned D_> class Projector: protected Projector<D-1, D_> {
    public:
        /// Project an array of vertices of dimension \p D to dimension \p D_ < \p D
        /** \param x The array of vertices to be projected
         *  \param scrW Distance of the "screen" to be projected onto from the
         *              origin
         *  \param camW Distance of the camera/eye onto from the origin
         *
         *  \return \p x projected to \p D_
         */
        std::vector<VecMath::Vector<D_> > operator()(
                const std::vector<VecMath::Vector<D> > &x,
                double scrW, double camW) {

            checkConsistency(scrW, camW);

            std::vector<VecMath::Vector<D-1> > x_proj = doProject(x, scrW, camW);
            return Projector<D-1, D_>::operator()(x_proj, scrW, camW);
        }

        /// Project an array of vertices of dimension \p D to dimension \p D_ < \p D
        /** \param x The array of vertices to be projected
         *  \param scrW Distances of the "screen" to be projected onto from the
         *              origin, one for every projection operation
         *  \param camW Distances of the camera/eye onto from the origin, one for
         *              every projection operation
         *
         *  \return \p x projected to \p D_
         *
         *  \todo implement this!
         */
        std::vector<VecMath::Vector<D_> > operator()(
                const std::vector<VecMath::Vector<D> > &x,
                const std::vector<double> &scrW, const std::vector<double> &camW) {
            throw NotYetImplementedException("std::vector<VecMath::Vector<D_> > \n"
                    "    Projector<D, D_>::operator()(\n"
                    "        vector<Vector<D> > &, vector<double> &, "
                    "vector<double> &)");
        }

    private:
        /// Check if a projection makes sense, throw if it doesn't
        /** \param scrW Distance of the "screen" to be projected onto from the
         *              origin
         *  \param camW Distance of the camera/eye onto from the origin
         */
        void checkConsistency(double scrW, double camW) {
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

        /// Perform the projection from dimension \p D to dimension \p D-1
        /** \param x The array of vertices to be projected
         *  \param scrW Distance of the "screen" to be projected onto from the
         *              origin
         *  \param camW Distance of the camera/eye onto from the origin
         *
         *  \return \p x projected one dimension down
         */
        std::vector<VecMath::Vector<D-1> > doProject(
                const std::vector<VecMath::Vector<D> > &x,
                double scrW, double camW) {
            std::vector<VecMath::Vector<D-1> > x_proj(x.size());

            for (unsigned i = 0; i < x.size(); i++) {
                double ProjectionFactor = (scrW-camW)/(x[i][D-1]-camW);

                for (unsigned j = 0; j < D-1; j++)
                    x_proj.at(i)[j] = ProjectionFactor*x[i][j];
            }
            return x_proj;
        }

};

/// Specialization for \p D_ == \p D
template <unsigned D> class Projector<D, D> {
    public:
        /// Projection from D dimensions to D dimensions is a no-op
        std::vector<VecMath::Vector<D> > operator()(
            const std::vector<VecMath::Vector<D> > &x, double, double) {
            return x;
        }
};

#endif
