/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "FunctionValueGrid.h"

#include "Rotation.h"

namespace TransformationUtil {
    template <unsigned N, typename NUM = double>
    inline VecMath::Vector<N, NUM> perform(
        const VecMath::Vector<N, NUM> &x,
        const VecMath::Matrix<N, NUM> &rot,
        const VecMath::Vector<N, NUM> &trans,
        const VecMath::Vector<N, NUM> &scale
    ) {
        return VecMath::scale(rot*(x+trans), scale);
    }
    
}

/// Interface for applying a geometrical transformation on a set of vertices.
/** 
 *  This class defines the interface to which all implementations conform. The
 *  interface basically consists of the constructor, which should only be used 
 *  by the TransformationFactory class, and the transform() method.
 * 
 *  \tparam N Dimension of the vertices.
 *  \tparam P Dimension of the parameter space.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned P, typename NUM = double>
class Transformation {

public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, P, NUM >::value_storage_type value_storage_type;

    static inline VecMath::Vector<N, NUM> perform(
        const VecMath::Vector<N, NUM> &x,
        const VecMath::Matrix<N, NUM> &rot,
        const VecMath::Vector<N, NUM> &trans,
        const VecMath::Vector<N, NUM> &scale
    ) {
        return TransformationUtil::perform(x, rot, trans, scale);
    }

    /// Execute the transform on a set of vertices.
    /**
     * @param operand A (multi-dimensional) array of vertices on which the transformation is performed
     * @return A (multi-dimensional) array of transformed vertices
     */
    virtual value_storage_type transform(const value_storage_type &operand) const = 0;

    virtual ~Transformation() { }

protected:

    Transformation() { }

    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    Transformation(const VecMath::Rotation<N, NUM> &rotation,
                   const VecMath::Vector<N, NUM> &translation,
                   const VecMath::Vector<N, NUM> &scale);

};

class TransformationFactory;

/// Class template to apply a geometrical transformation on a set of vertices.
/** 
 *  This is the parent class from which implementations of the transformation
 *  classes should inherit. It stores the parameters to a transformation, i.e.
 *  the rotation, translation and scaling that are applied.
 * 
 *  \tparam N Dimension of the vertices.
 *  \tparam P Dimension of the parameter space.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned P, typename NUM = double>
class TransformationImpl: public Transformation< N, P, NUM > {

public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, P, NUM >::value_storage_type value_storage_type;

protected:

    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    TransformationImpl(const VecMath::Rotation<N, NUM> &rotation,
                       const VecMath::Vector<N, NUM> &translation,
                       const VecMath::Vector<N, NUM> &scale);

    VecMath::Rotation<N, NUM> rotation_;      ///< Rotation part of the Transformation.
    VecMath::Vector<N, NUM> translation_;   ///< Translation part of the Transformation.
    VecMath::Vector<N, NUM> scale_;         ///< Scaling part of the Transformation.

    friend class TransformationFactory;
};

#endif // TRANSFORMATION_H
