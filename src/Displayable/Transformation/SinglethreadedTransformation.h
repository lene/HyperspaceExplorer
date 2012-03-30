/* 
 * File:   SinglethreadedTransformation.h
 * Author: lene
 *
 * Created on March 30, 2012, 5:52 PM
 */

#ifndef SINGLETHREADEDTRANSFORMATION_H
#define	SINGLETHREADEDTRANSFORMATION_H

#include "Transformation.h"

template <unsigned N, unsigned P, typename NUM = double>
class SinglethreadedTransformation: public TransformationImpl< N, P, NUM > {

public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, P, NUM >::value_storage_type value_storage_type;
    
    virtual value_storage_type transform(const value_storage_type &operand) const;

private:

    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    SinglethreadedTransformation(const VecMath::Rotation<N, NUM> &rotation,
                                 const VecMath::Vector<N, NUM> &translation,
                                 const VecMath::Vector<N, NUM> &scale);
    
    void perform_transformation(const VecMath::Vector<N, NUM>& x, const VecMath::Vector<N, NUM>& xtrans);
    
    friend class TransformationFactory;
    friend class SinglethreadedTransformation<N, P+1, NUM>;
};

template <unsigned N, typename NUM>
class SinglethreadedTransformation<N, 1, NUM>: public TransformationImpl< N, 1, NUM > {

public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, 1, NUM >::value_storage_type value_storage_type;
    
    virtual value_storage_type transform(const value_storage_type &operand) const;

private:

    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    SinglethreadedTransformation(const VecMath::Rotation<N, NUM> &rotation,
                                 const VecMath::Vector<N, NUM> &translation,
                                 const VecMath::Vector<N, NUM> &scale);

    void perform_transformation(const VecMath::Vector<N, NUM>& x, const VecMath::Vector<N, NUM>& xtrans);
    
    friend class TransformationFactory;
    friend class SinglethreadedTransformation<N, 2, NUM>;
};

#endif	/* SINGLETHREADEDTRANSFORMATION_H */

