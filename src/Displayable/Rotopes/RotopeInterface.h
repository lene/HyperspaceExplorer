/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2009-2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef ROTOPE_BASE_H
#define ROTOPE_BASE_H

#include "Realm.h"
#include "Rotation.h"

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
    virtual ~RotopeInterface() { }

    /// How many segments a rotation operation has by default.
    const static unsigned DEFAULT_NUM_SEGMENTS = 8;

    /// The array of realms
    virtual Realm &realm() = 0;
    /// The array of realms
    virtual const Realm &realm() const = 0;

    /// The array of vertices, projected to four dimensions if necessary
    virtual std::vector<VecMath::Vector<4> > projected_vertices() = 0;

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

    /// For rotated objects, set the level of detail of the rendering
    static void setRotationSegments(unsigned numSegments) {
        _numSegments = numSegments;
    }

    /// String representation
    virtual std::string toString() = 0;
    /// String representation
    operator std::string() { return toString(); }

    /// Output of all vertices
    void print() { std::cout << toString(); }

protected:

    /// Perform a \p D -dimensional transformation
    virtual void addTransform(unsigned, const VecMath::RotationBase *) = 0;

    /// How many segments to use to approximate a circle
    static unsigned _numSegments;

/// Allow Rotope (which is not a RotopeBase, but contains one) free access
friend class Rotope;
};

#endif
