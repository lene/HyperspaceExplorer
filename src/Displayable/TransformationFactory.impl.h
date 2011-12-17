/* 
 * File:   TransformationFactory.impl.h
 * Author: lene
 *
 * Created on December 17, 2011, 3:02 AM
 */

#ifndef TRANSFORMATIONFACTORY_IMPL_H
#define	TRANSFORMATIONFACTORY_IMPL_H

#include "TransformationFactory.h"

#include "Transformation.impl.h"
#include "SimpleTransformationPolicy.impl.h"
#include "MultithreadedTransformationPolicy.impl.h"

template <unsigned N, unsigned P, typename NUM> 
typename TransformationFactory< N, P, NUM >::Method
TransformationFactory< N, P, NUM >::method_ = TransformationFactory< N, P, NUM >::Singlethreaded;

template <unsigned N, unsigned P, typename NUM> 
std::shared_ptr< const Transformation< N, P, NUM > > 
TransformationFactory< N, P, NUM >::pointerToImpl_ = NULL;

template <unsigned N, unsigned P, typename NUM> 
void 
TransformationFactory< N, P, NUM >::setTransformationMethod(
        const TransformationFactory< N, P, NUM >::Method &method
) {
    method_ = method;
}

template <unsigned N, unsigned P, typename NUM> 
typename TransformationFactory< N, P, NUM >::Method
TransformationFactory< N, P, NUM >::getTransformationMethod() {
    return method_;
}

template <unsigned N, unsigned P, typename NUM> 
const Transformation< N, P, NUM > & 
TransformationFactory< N, P, NUM >::create(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    ) {
    if (getTransformationMethod() == Multithreaded) {
        return createWithPolicy< MultithreadedTransformationPolicy< N, P, NUM > >(rotation, translation, scale);
    }
    return createWithPolicy< SimpleTransformationPolicy< N, P, NUM > >(rotation, translation, scale);
}

template <unsigned N, unsigned P, typename NUM> 
const Transformation< N, P, NUM > & 
TransformationFactory< N, P, NUM >::create() {
    return create(VecMath::Rotation<N, NUM>(), VecMath::Vector<N, NUM>(), VecMath::Vector<N, NUM>(1.));
}

template <unsigned N, unsigned P, typename NUM> 
template <typename Policy> 
const Transformation< N, P, NUM > & 
TransformationFactory< N, P, NUM >::createWithPolicy(
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


#endif	/* TRANSFORMATIONFACTORY_IMPL_H */

