/* 
 * File:   TransformationPolicy.impl.h
 * Author: lene
 *
 * Created on December 15, 2011, 11:43 PM
 */

#ifndef TRANSFORMATIONPOLICY_IMPL_H
#define	TRANSFORMATIONPOLICY_IMPL_H

#define DEBUG_TRANSFORMATION 1

#include "TransformationPolicy.h"

#if DEBUG_TRANSFORMATION
#include <QDebug>
#include <QThreadPool>
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

////////////////////////////////////////////////////////////////////////////////

#include <QtConcurrentMap>

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

template<unsigned  N, typename NUM> struct MapFunctor {

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
  auto future = QtConcurrent::mapped(
          operand.begin(), operand.end(),
          MapFunctor<N, NUM>(this->rotation_, this->translation_, this->scale_)
  );
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


#endif	/* TRANSFORMATIONPOLICY_IMPL_H */

