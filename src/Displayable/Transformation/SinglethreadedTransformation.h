/* 
 * File:   SinglethreadedTransformation.h
 * Author: lene
 *
 * Created on March 30, 2012, 5:52 PM
 */

#ifndef SINGLETHREADEDTRANSFORMATION_H
#define	SINGLETHREADEDTRANSFORMATION_H

#include "Transformation.h"

/// Class template to apply a geometrical transformation on a set of vertices.
/** 
 *  This is an implementation that applies a transformation on every element of
 *  a MultiDimensionalVector one element after the next, sequentially, in a
 *  single threaded way. The TransformationFactory uses it as the default method
 *  to do transformations.
 * 
 *  Recursively instantiates and performs transformations on VertexArray s of
 *  lower dimension.
 * 
 *  \tparam N Dimension of the vertices.
 *  \tparam P Dimension of the parameter space.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned P, typename NUM = double>
class SinglethreadedTransformation: public TransformationImpl< N, P, NUM > {

public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, P, NUM >::value_storage_type value_storage_type;
    
    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    SinglethreadedTransformation(const VecMath::Rotation<N, NUM> &rotation,
                                 const VecMath::Vector<N, NUM> &translation,
                                 const VecMath::Vector<N, NUM> &scale);
    
    /// Execute the transform on a set of vertices.
    /**
     * @param operand A (multi-dimensional) array of vertices on which the transformation is performed
     * @return A (multi-dimensional) array of transformed vertices
     */
    virtual value_storage_type transform(const value_storage_type &operand) const;

private:

    void perform_transformation(const VecMath::Vector<N, NUM>& x, const VecMath::Vector<N, NUM>& xtrans);
    
    friend class TransformationFactory;
    friend class SinglethreadedTransformation<N, P+1, NUM>;
};

/// Specialization for one-dimensional arrays to end recursion.
/** 
 *  This is the only class on which transformation are actually performed on 
 *  single vertices.
 * 
 *  \tparam N Dimension of the vertices.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, typename NUM>
class SinglethreadedTransformation<N, 1, NUM>: public TransformationImpl< N, 1, NUM > {

public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, 1, NUM >::value_storage_type value_storage_type;
    
    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    SinglethreadedTransformation(const VecMath::Rotation<N, NUM> &rotation,
                                 const VecMath::Vector<N, NUM> &translation,
                                 const VecMath::Vector<N, NUM> &scale);

    void perform_transformation(const VecMath::Vector<N, NUM>& x, const VecMath::Vector<N, NUM>& xtrans);
    
    /// Execute the transform on a set of vertices.
    /**
     * @param operand An array of vertices on which the transformation is performed
     * @return An array of transformed vertices
     */
    virtual value_storage_type transform(const value_storage_type &operand) const;

private:

    friend class TransformationFactory;
    friend class SinglethreadedTransformation<N, 2, NUM>;
};

#endif	/* SINGLETHREADEDTRANSFORMATION_H */

