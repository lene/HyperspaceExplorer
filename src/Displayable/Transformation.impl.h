/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef TRANSFORMATION_IMPL_H
#define TRANSFORMATION_IMPL_H

#include "Transformation.h"

#include "Matrix.impl.h"

template <unsigned N, unsigned P, typename NUM, typename TransformationPolicy>
Transformation<N, P, NUM, TransformationPolicy>::Transformation():
  _transform(), _translation() { }

template <unsigned N, unsigned P, typename NUM, typename TransformationPolicy>
Transformation<N, P, NUM, TransformationPolicy>::Transformation(const VecMath::Rotation<N, NUM> &rotation,
                                                           const VecMath::Vector<N, NUM> &translation,
                                                           const VecMath::Vector<N, NUM> &scale):
  _transform(rotation), _translation(translation) {
  _transform.scale(scale);
}

template <unsigned N, unsigned P, typename NUM, typename TransformationPolicy>
Transformation<N, P, NUM, TransformationPolicy>::Transformation(const VecMath::Matrix<N, NUM> &transform,
                                                           const VecMath::Vector<N, NUM> &translation):
  _transform(transform), _translation(translation) { }

template <unsigned N, unsigned P, typename NUM, typename TransformationPolicy>
typename Transformation<N, P, NUM, TransformationPolicy>::value_storage_type
Transformation<N, P, NUM, TransformationPolicy>::transform(
  const value_storage_type &operand) {
  TransformationPolicy p(_transform, _translation);

  return p.transform(operand);
}
#include <QDebug>

template <unsigned N, unsigned P, typename NUM>
typename SimpleTransformationPolicy<N, P, NUM>::value_storage_type
SimpleTransformationPolicy<N, P, NUM>::transform(
        const value_storage_type &operand
) {
  value_storage_type v(operand.size());
  Transformation<N, P-1, NUM, SimpleTransformationPolicy<N, P-1, NUM> > sub_transform(_transform, _translation);
# if 0
  qDebug() << "SimpleTransformationPolicy<" << N << ", " << P << ", NUM>::transform("
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
    v[i] = _transform*operand[i]+_translation;
  }
# if 0
  qDebug()
    << operand.toString().c_str() << " * " << _transform.toString().c_str() << " + " << _translation.toString().c_str()
    << " = " << v.toString().c_str();
# endif
  return v;
}


#endif // TRANSFORMATION_IMPL_H