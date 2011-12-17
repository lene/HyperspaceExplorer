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
std::shared_ptr< const Transformation< N, P, NUM > > 
TransformationFactory< N, P, NUM >::pointerToImpl_ = NULL;

#endif	/* TRANSFORMATIONFACTORY_IMPL_H */

