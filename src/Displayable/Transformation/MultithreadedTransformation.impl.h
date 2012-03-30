/* 
 * File:   MultithreadedTransformation.impl.h
 * Author: lene
 *
 * Created on March 30, 2012, 6:00 PM
 */

#ifndef MULTITHREADEDTRANSFORMATION_IMPL_H
#define	MULTITHREADEDTRANSFORMATION_IMPL_H

#include "MultithreadedTransformation.h"

#include <QtConcurrentMap>

#if DEBUG_TRANSFORMATION
#include <QDebug>
#include <QThreadPool>
#include <typeinfo>
#endif

template<unsigned  N, typename NUM>
struct MultithreadedTransformation<N, 1, NUM>::MapFunctor {

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


template <unsigned N, unsigned P, typename NUM>
MultithreadedTransformation<N, P, NUM>::MultithreadedTransformation(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale): 
  TransformationImpl<N, P, NUM>(rotation, translation, scale) { }

template <unsigned N, typename NUM>
MultithreadedTransformation<N, 1, NUM>::MultithreadedTransformation(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale): 
  TransformationImpl<N, 1, NUM>(rotation, translation, scale), functor_(rotation, translation, scale) { }

template <unsigned N, unsigned P, typename NUM>
typename MultithreadedTransformation<N, P, NUM>::value_storage_type
MultithreadedTransformation<N, P, NUM>::transform(
  const value_storage_type &x) const {
    
    value_storage_type xtrans(x.size());
    
    MultithreadedTransformation<N, P-1, NUM> transformation(
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
typename MultithreadedTransformation<N, 1, NUM>::value_storage_type
MultithreadedTransformation<N, 1, NUM>::transform(
  const value_storage_type &operand) const {
  auto future = QtConcurrent::mapped(operand.begin(), operand.end(), functor_);
# if DEBUG_TRANSFORMATION
  qDebug() << "MultithreadedTransformationPolicy<" << N << ", " << 1 << ", " << typeid(NUM).name() << ">::transform("
           << operand.toString().c_str()
           << "): "
           << QThreadPool::globalInstance()->activeThreadCount() << " active Threads, "
           << QThreadPool::globalInstance()->maxThreadCount() << " max Threads";
# endif
  future.waitForFinished();

  value_storage_type v(operand.size());
  for (auto i = future.constBegin(); i != future.constEnd(); ++i) {
      v.push_back(*i);
  }

  return v;
}


#endif	/* MULTITHREADEDTRANSFORMATION_IMPL_H */

