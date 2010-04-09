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

#include "Matrix.h"

/// Forward declaration needed to make the SimpleTransformationPolicy a default template parameter for Transformation.
template <unsigned N, unsigned P> class SimpleTransformationPolicy;

/// Policy-based class template to apply a geometrical transformation on a set of vertices.
/** \param N Dimension of the vertices.
 *  \param P Dimension of the parameter space.
 *  \param TransformationPolicy The class executing the actual transform on the set of vertices.
 */
template <unsigned N, unsigned P, typename TransformationPolicy = SimpleTransformationPolicy <N, P> >
class Transformation {
  
  public:

    typedef typename FunctionValueGrid< N, P >::value_storage_type value_storage_type;

    Transformation();
    Transformation(const VecMath::Rotation<N> &rotation, 
                   const VecMath::Vector<N> &translation, 
                   const VecMath::Vector<N> &scale);
    /// Initialize a Transformation with a transformation matrix and a translation vector.
    /** NB There is an implicit cast from class Rotation to Matrix, so you can use a
     *  Rotation instead.
     *  \param transform The \p N x \p N Matrix to apply to all vertices.
     *  \param translation The translation Vector to add to all vertices.
     */
    Transformation(const VecMath::Matrix<N> &transform, const VecMath::Vector<N> &translation);
    
    /// Execute the transform on a set of vertices.
    value_storage_type transform(const value_storage_type &operand);
    
  private:

    VecMath::Matrix<N> _transform;
    VecMath::Vector<N> _translation;
    
};

/// Policy class template that contains the actual implementation of the transformation algorithm for Transformation.
/** \param N Dimension of the vertices.
 *  \param P Dimension of the parameter space.
 */
template <unsigned N, unsigned P>
class SimpleTransformationPolicy {
  
  public:
  
    typedef typename FunctionValueGrid< N, P >::value_storage_type value_storage_type;

    SimpleTransformationPolicy(const VecMath::Matrix<N> &transform, 
                               const VecMath::Vector<N> &translation): _transform(transform), _translation(translation) { }
    value_storage_type transform(const value_storage_type &operand);
    
  private:
    
    VecMath::Matrix<N> _transform;
    VecMath::Vector<N> _translation;
    
};

template <unsigned N> class SimpleTransformationPolicy< N, 1 > {
  
  public:

    typedef typename FunctionValueGrid< N, 1 >::value_storage_type value_storage_type;

    SimpleTransformationPolicy(const VecMath::Matrix<N> &transform, 
                               const VecMath::Vector<N> &translation): _transform(transform), _translation(translation) { }
    value_storage_type transform(const value_storage_type &operand);
    
  private:
    
    VecMath::Matrix<N> _transform;
    VecMath::Vector<N> _translation;
    
};

#include "Transformation.impl.h"

#endif // TRANSFORMATION_H
