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

/// Forward declaration needed to make the SimpleTransformationPolicy a default template parameter for Transformation.
template <unsigned N, unsigned P, typename NUM = double> class SimpleTransformationPolicy;

/// Policy-based class template to apply a geometrical transformation on a set of vertices.
/** \tparam N Dimension of the vertices.
 *  \tparam P Dimension of the parameter space.
 *  \tparam NUM The numeric type of the \c Vector s.
 *  \tparam TransformationPolicy The class executing the actual transform on the set of vertices.
 *
 *  \todo typedefs for translation and rotation types
 */
template <unsigned N, unsigned P, typename NUM = double,
          typename TransformationPolicy = SimpleTransformationPolicy <N, P, NUM> >
class Transformation {

  public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, P, NUM >::value_storage_type value_storage_type;

    /// Initialize an identity Transformation.
    Transformation();

    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    Transformation(const VecMath::Rotation<N, NUM> &rotation,
                   const VecMath::Vector<N, NUM> &translation,
                   const VecMath::Vector<N, NUM> &scale);

    /// Execute the transform on a set of vertices.
    value_storage_type transform(const value_storage_type &operand);

  private:

    VecMath::Rotation<N, NUM> rotation_;      ///< Rotation part of the Transformation.
    VecMath::Vector<N, NUM> translation_;   ///< Translation part of the Transformation.
    VecMath::Vector<N, NUM> scale_;         ///< Scaling part of the Transformation.

};

/// Policy class template that contains the actual implementation of the transformation algorithm for Transformation.
/** This class implements a single-threaded transformation algorithm without
 *  any optimizations.
 *  \tparam N Dimension of the vertices.
 *  \tparam P Dimension of the parameter space.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned P, typename NUM>
class SimpleTransformationPolicy {

  public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, P, NUM >::value_storage_type value_storage_type;

    /// Initialize a SimpleTransformationPolicy with a transformation matrix and a translation vector.
    /** \param transform The \p N x \p N Rotation to apply to all vertices.
     *  \param translation The translation Vector to add to all vertices.
     */
    SimpleTransformationPolicy(const VecMath::Rotation<N, NUM> &rotation,
                               const VecMath::Vector<N, NUM> &translation,
                               const VecMath::Vector<N, NUM> &scale):
    rotation_(rotation), translation_(translation), scale_(scale) { }

    /// Execute the transform on a set of vertices.
    value_storage_type transform(const value_storage_type &operand);

  private:

    VecMath::Rotation<N, NUM> rotation_;      ///< Rotation part of the Transformation.
    VecMath::Vector<N, NUM> translation_;   ///< Translation part of the Transformation.
    VecMath::Vector<N, NUM> scale_;         ///< Scaling part of the Transformation.

};

/// Specialization to end recursion - transform a one-dimensional vector of Vector s.
/** \tparam N Dimension of the vertices.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, typename NUM> class SimpleTransformationPolicy< N, 1, NUM > {

  public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, 1, NUM >::value_storage_type value_storage_type;

    /// Initialize a SimpleTransformationPolicy with a transformation matrix and a translation vector.
    /** \param transform The \p N x \p N Rotation to apply to all vertices.
     *  \param translation The translation Vector to add to all vertices.
     */
    SimpleTransformationPolicy(const VecMath::Rotation<N, NUM> &rotation,
                               const VecMath::Vector<N, NUM> &translation,
                               const VecMath::Vector<N, NUM> &scale):
    rotation_(rotation), translation_(translation), scale_(scale) { }

    /// Execute the transform on a set of vertices.
    value_storage_type transform(const value_storage_type &operand);

  private:

    VecMath::Rotation<N, NUM> rotation_;      ///< Rotation part of the Transformation.
    VecMath::Vector<N, NUM> translation_;   ///< Translation part of the Transformation.
    VecMath::Vector<N, NUM> scale_;         ///< Scaling part of the Transformation.

};

#endif // TRANSFORMATION_H
