/* 
 * File:   SimpleTransformationPolicy.impl.h
 * Author: lene
 *
 * Created on December 16, 2011, 9:22 PM
 */

#ifndef SIMPLETRANSFORMATIONPOLICY_IMPL_H
#define	SIMPLETRANSFORMATIONPOLICY_IMPL_H

#include "SimpleTransformationPolicy.h"

#if DEBUG_TRANSFORMATION
#include <QDebug>
#include <typeinfo>
#endif

template <unsigned N, unsigned P, typename NUM>
typename SimpleTransformationPolicy<N, P, NUM>::value_storage_type
SimpleTransformationPolicy<N, P, NUM>::transform(
        const value_storage_type &operand
) {
  value_storage_type v(operand.size());
  Transformation<N, P-1, NUM, SimpleTransformationPolicy<N, P-1, NUM> > sub_transform(
    this->rotation_, this->translation_, this->scale_
  );
# if DEBUG_TRANSFORMATION && 0
  qDebug() << "SimpleTransformationPolicy<" << N << ", " << P << ", " << typeid(NUM).name() << ">::transform("
           << operand.toString().c_str()
           << ")";
# endif
  for (unsigned i = 0; i < operand.size(); ++i) {
    v[i] = sub_transform.transform(operand[i]);
  }

  return v;
}

template <unsigned N, typename NUM>
typename SimpleTransformationPolicy<N, 1, NUM>::value_storage_type
SimpleTransformationPolicy<N, 1, NUM>::transform(
        const value_storage_type &operand
) {
  value_storage_type v(operand.size());

  for (unsigned i = 0; i < operand.size(); ++i) {
    VecMath::Matrix<N, NUM> matrix(this->rotation_);
    v[i] = Transformation<N, 1, NUM>::perform(operand[i], matrix, this->translation_, this->scale_);
  }
# if DEBUG_TRANSFORMATION && 0
  qDebug()
    << operand.toString().c_str() << " * " << this->rotation_.toString().c_str() << " + " << this->translation_.toString().c_str()
    << " = " << v.toString().c_str();
# endif
  return v;
}

#endif	/* SIMPLETRANSFORMATIONPOLICY_IMPL_H */

