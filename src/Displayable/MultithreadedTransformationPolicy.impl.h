/* 
 * File:   MultithreadedTransformationPolicy.impl.h
 * Author: lene
 *
 * Created on December 16, 2011, 9:22 PM
 */

#ifndef MULTITHREADEDTRANSFORMATIONPOLICY_IMPL_H
#define	MULTITHREADEDTRANSFORMATIONPOLICY_IMPL_H

#include "MultithreadedTransformationPolicy.h"

#include <QtConcurrentMap>

#if DEBUG_TRANSFORMATION
#include <QDebug>
#include <QThreadPool>
#include <typeinfo>
#endif

template <unsigned N, unsigned P, typename NUM>
typename MultithreadedTransformationPolicy<N, P, NUM>::value_storage_type
MultithreadedTransformationPolicy<N, P, NUM>::transform(
        const value_storage_type &operand
) {
  value_storage_type v(operand.size());
  Transformation<N, P-1, NUM, MultithreadedTransformationPolicy<N, P-1, NUM> > sub_transform(
    this->rotation_, this->translation_, this->scale_
  );
  for (unsigned i = 0; i < operand.size(); ++i) {
    v[i] = sub_transform.transform(operand[i]);
  }

  return v;
}

template<unsigned  N, typename NUM>
struct MultithreadedTransformationPolicy<N, 1, NUM>::MapFunctor {

    typedef VecMath::Vector<N, NUM> result_type;

    MapFunctor(const VecMath::Rotation<N, NUM> &rotation,
               const VecMath::Vector<N, NUM> &translation,
               const VecMath::Vector<N, NUM> &scale):
    matrix_(rotation), translation_(translation), scale_(scale) { }

    VecMath::Vector<N, NUM> operator() (const VecMath::Vector<N, NUM> &arg) {
        return Transformation<N, 1, NUM>::perform(arg, matrix_, translation_, scale_);
    }

    VecMath::Matrix<N, NUM> matrix_;        ///< Rotation part of the Transformation.
    VecMath::Vector<N, NUM> translation_;   ///< Translation part of the Transformation.
    VecMath::Vector<N, NUM> scale_;         ///< Scaling part of the Transformation.

};

template <unsigned N, typename NUM>
typename MultithreadedTransformationPolicy<N, 1, NUM>::value_storage_type
MultithreadedTransformationPolicy<N, 1, NUM>::transform(
        const value_storage_type &operand
) {
  auto future = QtConcurrent::mapped(operand.begin(), operand.end(), functor_);
# if DEBUG_TRANSFORMATION
  qDebug() << "MultithreadedTransformationPolicy<" << N << ", " << 1 << ", " << typeid(NUM).name() << ">::transform("
           << operand.toString().c_str()
           << "): "
           << QThreadPool::globalInstance()->activeThreadCount() << " active Threads, "
           << QThreadPool::globalInstance()->maxThreadCount() << " max Threads";
# endif
  future.waitForFinished();
//  return operand;
  value_storage_type v(operand.size());
  for (auto i = future.constBegin(); i != future.constEnd(); ++i) {
      v.push_back(*i);
  }

  return v;
}

#endif	/* MULTITHREADEDTRANSFORMATIONPOLICY_IMPL_H */

