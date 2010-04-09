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

template <unsigned N, unsigned P, typename TransformationPolicy>
Transformation<N, P, TransformationPolicy>::Transformation():
  _transform(), _translation() { }

template <unsigned N, unsigned P, typename TransformationPolicy>
Transformation<N, P, TransformationPolicy>::Transformation(const VecMath::Rotation<N> &rotation, 
                                                           const VecMath::Vector<N> &translation,
                                                           const VecMath::Vector<N> &scale):
  _transform(rotation), _translation(translation) { 
  _transform.scale(scale);
}

template <unsigned N, unsigned P, typename TransformationPolicy>
Transformation<N, P, TransformationPolicy>::Transformation(const VecMath::Matrix<N> &transform, 
                                                           const VecMath::Vector<N> &translation):
  _transform(transform), _translation(translation) { }

template <unsigned N, unsigned P, typename TransformationPolicy>
typename Transformation<N, P, TransformationPolicy>::value_storage_type Transformation<N, P, TransformationPolicy>::transform(
  const value_storage_type &operand) {
  TransformationPolicy p(_transform, _translation);
  
  return p.transform(operand);
}

template <unsigned N, unsigned P>
typename SimpleTransformationPolicy<N, P>::value_storage_type 
SimpleTransformationPolicy<N, P>::transform(
        const value_storage_type &operand
) {
  value_storage_type v(operand.size());  
    
  for (unsigned i = 0; i < operand.size(); ++i) {
    Transformation<N, P-1, SimpleTransformationPolicy<N, P-1> > sub_transform(_transform, _translation);
    v[i] = sub_transform.transform(operand[i]);
  }
  
  return v;
}

template <unsigned N>
typename SimpleTransformationPolicy<N, 1>::value_storage_type 
SimpleTransformationPolicy<N, 1>::transform(
        const value_storage_type &operand
) {
  value_storage_type v(operand.size());

  for (unsigned i = 0; i < operand.size(); ++i) {
    v[i] = _transform*operand[i]+_translation;
  }
  
  return v;
}


#endif // TRANSFORMATION_IMPL_H
