#ifndef ROTOPE_BASE_H
#define ROTOPE_BASE_H

#include "uintvec.h"
#include "Realm.h"

using VecMath::uintvec;

/** \defgroup RotopeGroup N-dimensional Rotopes.
 *  For a definition of Rotopes, see http://teamikaria.com/wiki/Rotope.
 *  \ingroup ObjectGroup
 */

/// Interface implemented by all Rotope s
/** \ingroup RotopeGroup */
class RotopeBase {
    public:
        virtual void print() = 0;           ///< Output of all vertices

        /// The array of realms
        virtual Realm &realm() = 0;

    protected:

        /// three-dimensional array of unsigned, implemented as a nested vector
        typedef uintvec<3> uintvec3D;

        /// Add a surface to the array of surfaces
        virtual void addSurface(unsigned, unsigned, unsigned, unsigned) = 0;
        /// Add a surface to the array of surfaces
        virtual void addSurface(unsigned, unsigned, unsigned) = 0;

        /// Perform a \p D -dimensional transformation
        virtual void addTransform(unsigned, const VecMath::RotationBase *) = 0;

        /// Dimension of the object
        virtual unsigned &dimension() = 0;
        /// The array of surfaces
        virtual uintvec<2> &surface() = 0;
        /// The array of vertices, projected to four dimensions if necessary
        virtual std::vector<VecMath::Vector<4> > vertices() = 0;

    /// Allow Rotope (which is not a RotopeBase, but contains one) free access
    friend class Rotope;
};

#endif
