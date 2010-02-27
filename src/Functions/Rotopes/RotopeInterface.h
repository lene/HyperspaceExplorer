#ifndef ROTOPE_BASE_H
#define ROTOPE_BASE_H

#include "Realm.h"

/** \defgroup RotopeGroup N-dimensional Rotopes.
 *  For a definition of Rotopes, see http://teamikaria.com/wiki/Rotope.
 *  \ingroup ObjectGroup
 */

/// Interface implemented by all Rotope s
/** \ingroup RotopeGroup 
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
class RotopeInterface {

public:

    /// The array of realms
    virtual Realm &realm() = 0;
    virtual const Realm &realm() const = 0;

    /// The array of vertices, projected to four dimensions if necessary
    virtual std::vector<VecMath::Vector<4> > vertices() = 0;

    /// Dimension of the object
    virtual unsigned dimension() const = 0;
    /// Direct access to the dimension member instead of setter for convenience
    /** This way, implementing classes can simply use
     *  \code
     *    VertexData<D>::dimension()++;
     *  \endcode
     *  instead of the more cumbersome
     *  \code
     *  VertexData<D>::setDimension(VertexData<D>::dimension()+1);
     *  \endcode
     *  Because Rotope operations (extrusion, tapering etc.) are all about
     *  increasing the dimension, I'll let this stand.
     */
    virtual unsigned &dimension() = 0;

    virtual std::string toString() = 0;
    operator std::string() { return toString(); }
    
    /// Output of all vertices
    void print() { std::cout << toString(); }

protected:

    /// Perform a \p D -dimensional transformation
    virtual void addTransform(unsigned, const VecMath::RotationBase *) = 0;

/// Allow Rotope (which is not a RotopeBase, but contains one) free access
friend class Rotope;
};

#endif
