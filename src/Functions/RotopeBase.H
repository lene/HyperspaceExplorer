#ifndef ROTOPE_BASE_H
#define ROTOPE_BASE_H

/** \defgroup RotopeGroup N-dimensional Rotopes.
 *  For a definition of Rotopes, see http://teamikaria.com/wiki/Rotope
 *  \ingroup ObjectGroup
 */

/// Interface implemented by all Rotope s
class RotopeBase {
    public:
        virtual void print() = 0;           ///< Output of all vertices

    protected:

        /// one-dimensional array of unsigned, implemented as a std::vector
        typedef std::vector<unsigned> uintvec1D;
        /// two-dimensional array of unsigned, implemented as a nested vector
        typedef std::vector<uintvec1D> uintvec2D;

        /// Add a surface to the array of surfaces
        virtual void addSurface(unsigned, unsigned, unsigned, unsigned) = 0;
        /// Add a surface to the array of surfaces
        virtual void addSurface(unsigned, unsigned, unsigned) = 0;

        /// Dimension of the object
        virtual unsigned &dimension() = 0;
        /// The array of surfaces
        virtual uintvec2D &surface() = 0;
        /// The array of vertices, projected to four dimensions if necessary
        virtual std::vector<VecMath::Vector<4> > vertices() = 0;

    friend class Rotope;
};

#endif
