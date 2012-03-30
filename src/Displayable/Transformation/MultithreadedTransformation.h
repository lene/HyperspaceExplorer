/* 
 * File:   MultithreadedTransformation.h
 * Author: lene
 *
 * Created on March 30, 2012, 5:59 PM
 */

#ifndef MULTITHREADEDTRANSFORMATION_H
#define	MULTITHREADEDTRANSFORMATION_H

#include "Transformation.h"

template <unsigned N, unsigned P, typename NUM = double>
class MultithreadedTransformation: public TransformationImpl< N, P, NUM > {

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
    MultithreadedTransformation(const VecMath::Rotation<N, NUM> &rotation,
                                const VecMath::Vector<N, NUM> &translation,
                                const VecMath::Vector<N, NUM> &scale);
    
    void perform_transformation(const VecMath::Vector<N, NUM>& x, const VecMath::Vector<N, NUM>& xtrans);
    
    friend class TransformationFactory;
    friend class MultithreadedTransformation<N, P+1, NUM>;
};

template <unsigned N, typename NUM>
class MultithreadedTransformation<N, 1, NUM>: public TransformationImpl< N, 1, NUM > {

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
    MultithreadedTransformation(const VecMath::Rotation<N, NUM> &rotation,
                                const VecMath::Vector<N, NUM> &translation,
                                const VecMath::Vector<N, NUM> &scale);

    void perform_transformation(const VecMath::Vector<N, NUM>& x, const VecMath::Vector<N, NUM>& xtrans);
    
    friend class TransformationFactory;
    friend class MultithreadedTransformation<N, 2, NUM>;

    class MapFunctor;
    MapFunctor functor_;

};

#endif	/* MULTITHREADEDTRANSFORMATION_H */

