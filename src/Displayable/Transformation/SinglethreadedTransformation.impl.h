/* 
 * File:   SinglethreadedTransformation.impl.h
 * Author: lene
 *
 * Created on March 30, 2012, 5:52 PM
 */

#ifndef SINGLETHREADEDTRANSFORMATION_IMPL_H
#define	SINGLETHREADEDTRANSFORMATION_IMPL_H

#include "SinglethreadedTransformation.h"

template <unsigned N, unsigned P, typename NUM>
SinglethreadedTransformation<N, P, NUM>::SinglethreadedTransformation(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale): 
  TransformationImpl<N, P, NUM>(rotation, translation, scale) { }

template <unsigned N, typename NUM>
SinglethreadedTransformation<N, 1, NUM>::SinglethreadedTransformation(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale): 
  TransformationImpl<N, 1, NUM>(rotation, translation, scale) { }

template <unsigned N, unsigned P, typename NUM>
typename SinglethreadedTransformation<N, P, NUM>::value_storage_type
SinglethreadedTransformation<N, P, NUM>::transform(
  const value_storage_type &x) const {
    
    value_storage_type xtrans(x.size());
    
    SinglethreadedTransformation<N, P-1, NUM> transformation(
        TransformationImpl<N, P, NUM>::rotation_, 
        TransformationImpl<N, P, NUM>::translation_, 
        TransformationImpl<N, P, NUM>::scale_
    );

    for(unsigned i = 0; i != x.size(); ++i) {
        xtrans[i] = transformation.transform(x[i]);
    }
    
    return xtrans;
}

template <unsigned N, typename NUM>
typename SinglethreadedTransformation<N, 1, NUM>::value_storage_type
SinglethreadedTransformation<N, 1, NUM>::transform(
  const value_storage_type &x) const {
    value_storage_type xtrans(x.size());

    for(unsigned i = 0; i != x.size(); ++i) {
        xtrans[i] = perform(
                x[i],
                TransformationImpl<N, 1, NUM>::rotation_, 
                TransformationImpl<N, 1, NUM>::translation_, 
                TransformationImpl<N, 1, NUM>::scale_                
        );
    }
    return xtrans;
}

#endif	/* SINGLETHREADEDTRANSFORMATION_IMPL_H */

