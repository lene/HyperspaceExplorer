/* 
 * File:   MultithreadedTransformationPolicy.h
 * Author: lene
 *
 * Created on December 16, 2011, 9:22 PM
 */

#ifndef MULTITHREADEDTRANSFORMATIONPOLICY_H
#define	MULTITHREADEDTRANSFORMATIONPOLICY_H

#include "TransformationPolicy.h"

/// Policy class template that contains an actual implementation of the transformation algorithm for Transformation.
/** This class implements a multithreaded transformation algorithm.
 *  \tparam N Dimension of the vertices.
 *  \tparam P Dimension of the parameter space.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned P, typename NUM>
class MultithreadedTransformationPolicy: public TransformationPolicy<N, P, NUM> {

  public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, P, NUM >::value_storage_type value_storage_type;

    /// Initialize a MultithreadedTransformationPolicy with a transformation matrix and a translation vector.
    /** \param transform The \p N x \p N Rotation to apply to all vertices.
     *  \param translation The translation Vector to add to all vertices.
     */
    MultithreadedTransformationPolicy(const VecMath::Rotation<N, NUM> &rotation,
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
class MultithreadedTransformationPolicy< N, 1, NUM >: public TransformationPolicy<N, 1, NUM> {

  public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, 1, NUM >::value_storage_type value_storage_type;

    /// Initialize a SimpleTransformationPolicy with a transformation matrix and a translation vector.
    /** \param transform The \p N x \p N Rotation to apply to all vertices.
     *  \param translation The translation Vector to add to all vertices.
     */
    MultithreadedTransformationPolicy(const VecMath::Rotation<N, NUM> &rotation,
                                      const VecMath::Vector<N, NUM> &translation,
                                      const VecMath::Vector<N, NUM> &scale):
    TransformationPolicy<N, 1, NUM>(rotation, translation, scale) { }

    /// Execute the transform on a set of vertices.
    value_storage_type transform(const value_storage_type &operand);

    VecMath::Vector<N, NUM> mapFunction(const VecMath::Vector<N, NUM> &arg);
};


#endif	/* MULTITHREADEDTRANSFORMATIONPOLICY_H */

