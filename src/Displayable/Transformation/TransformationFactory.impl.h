/* 
 * File:   TransformationFactory.impl.h
 * Author: lene
 *
 * Created on December 17, 2011, 3:02 AM
 */

#ifndef TRANSFORMATIONFACTORY_IMPL_H
#define	TRANSFORMATIONFACTORY_IMPL_H

#include "TransformationFactory.h"
#include "MultithreadedTransformation.h"

#include "Transformation.impl.h"
#include "SinglethreadedTransformation.impl.h"

template <unsigned N, unsigned P, typename NUM> 
const Transformation< N, P, NUM > * 
TransformationFactory::create(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    ) {
    switch(getTransformationMethod()) {
        
        case Multithreaded:
            return new MultithreadedTransformation<N, P, NUM>(rotation, translation, scale);
            
        case Singlethreaded:
        default:
            return new SinglethreadedTransformation<N, P, NUM>(rotation, translation, scale);
    }
}

template <unsigned N, unsigned P, typename NUM> 
const Transformation< N, P, NUM > * 
TransformationFactory::create() {
    return create(VecMath::Rotation<N, NUM>(), VecMath::Vector<N, NUM>(), VecMath::Vector<N, NUM>(1.));
}
/*
template <unsigned N, unsigned P, typename NUM, typename Policy> 
const Transformation< N, P, NUM > * 
TransformationFactory::createWithPolicy(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    ) {
    return new TransformationWithPolicy< N, P, NUM, Policy >(
        rotation, translation, scale
    );
}
*/

#endif	/* TRANSFORMATIONFACTORY_IMPL_H */

