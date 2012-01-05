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
const Transformation< N, P, NUM > & 
TransformationFactory::create(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    ) {
    if (getTransformationMethod() == Multithreaded) {
        return createWithPolicy< N, P, NUM, MultithreadedTransformationPolicy< N, P, NUM > >(rotation, translation, scale);
    }
    return createWithPolicy< N, P, NUM, SimpleTransformationPolicy< N, P, NUM > >(rotation, translation, scale);
}

template <unsigned N, unsigned P, typename NUM> 
const Transformation< N, P, NUM > & 
TransformationFactory::create() {
    return create(VecMath::Rotation<N, NUM>(), VecMath::Vector<N, NUM>(), VecMath::Vector<N, NUM>(1.));
}

namespace TransformationFactoryUtil {
    template <unsigned N, unsigned P, typename NUM>
    std::shared_ptr< const Transformation< N, P, NUM > > &pointerToImpl() {
        static std::shared_ptr< const Transformation< N, P, NUM > > pImpl;
        return pImpl;
    }
}
template <unsigned N, unsigned P, typename NUM, typename Policy> 
const Transformation< N, P, NUM > & 
TransformationFactory::createWithPolicy(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    ) {
    TransformationFactoryUtil::pointerToImpl<N, P, NUM>() = std::shared_ptr< const Transformation< N, P, NUM > >(
                new TransformationImpl< N, P, NUM, Policy >(
                        rotation, translation, scale
                )
    );
    return *TransformationFactoryUtil::pointerToImpl<N, P, NUM>();
}


#endif	/* TRANSFORMATIONFACTORY_IMPL_H */

