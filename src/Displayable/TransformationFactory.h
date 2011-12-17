/* 
 * File:   TransformationFactory.h
 * Author: lene
 *
 * Created on December 17, 2011, 2:59 AM
 */

#ifndef TRANSFORMATIONFACTORY_H
#define	TRANSFORMATIONFACTORY_H

#include "SimpleTransformationPolicy.h"
#include "MultithreadedTransformationPolicy.h"

#include <memory>

template < unsigned N, unsigned P, typename NUM >
class TransformationFactory {
    
public:
    
    /// Initialize an identity Transformation.
    static const Transformation< N, P, NUM > &create() {
        return TransformationImpl< N, P, NUM, SimpleTransformationPolicy< N, P, NUM > >();
    }

    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    static const Transformation< N, P, NUM > &create(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    ) {
        return createWithPolicy< SimpleTransformationPolicy< N, P, NUM > >(rotation, translation, scale);
    }
    
    template <typename Policy> static const Transformation< N, P, NUM > &createWithPolicy(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    ) {
        pointerToImpl_ = std::shared_ptr< const Transformation< N, P, NUM > >(
                new TransformationImpl< N, P, NUM, Policy >(
                        rotation, translation, scale
                )
        );
        return *pointerToImpl_;
    }
    
    static std::shared_ptr< const Transformation< N, P, NUM > > pointerToImpl_;
    
};


#endif	/* TRANSFORMATIONFACTORY_H */

