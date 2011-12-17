/* 
 * File:   SimpleTransformationPolicy.h
 * Author: lene
 *
 * Created on December 16, 2011, 9:21 PM
 */

#ifndef SIMPLETRANSFORMATIONPOLICY_H
#define	SIMPLETRANSFORMATIONPOLICY_H

#include "TransformationPolicy.h"

/// Policy class template that contains the actual implementation of the transformation algorithm for Transformation.
/** This class implements a single-threaded transformation algorithm without
 *  any optimizations.
 *  \tparam N Dimension of the vertices.
 *  \tparam P Dimension of the parameter space.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned P, typename NUM>
class SimpleTransformationPolicy: public TransformationPolicy<N, P, NUM> {

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
    TransformationPolicy<N, P, NUM>(rotation, translation, scale) { }

    /// Execute the transform on a set of vertices.
    value_storage_type transform(const value_storage_type &operand);

};

/// Specialization to end recursion - transform a one-dimensional vector of Vector s.
/** \tparam N Dimension of the vertices.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, typename NUM>
class SimpleTransformationPolicy< N, 1, NUM >: public TransformationPolicy<N, 1, NUM> {

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
    TransformationPolicy<N, 1, NUM>(rotation, translation, scale) { }

    /// Execute the transform on a set of vertices.
    value_storage_type transform(const value_storage_type &operand);
    
};

#endif	/* SIMPLETRANSFORMATIONPOLICY_H */

