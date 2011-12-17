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
#include "TransformationPolicy.h"

#include "Rotation.impl.h"

template <unsigned N, unsigned P, typename NUM, typename TransformationPolicy>
TransformationImpl<N, P, NUM, TransformationPolicy>::TransformationImpl():
  rotation_(), translation_(), scale_() { }

template <unsigned N, unsigned P, typename NUM, typename TransformationPolicy>
TransformationImpl<N, P, NUM, TransformationPolicy>::TransformationImpl(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale):
  rotation_(rotation), translation_(translation), scale_(scale) { }

template <unsigned N, unsigned P, typename NUM, typename TransformationPolicy>
typename TransformationImpl<N, P, NUM, TransformationPolicy>::value_storage_type
TransformationImpl<N, P, NUM, TransformationPolicy>::transform(
  const value_storage_type &operand) const {
  TransformationPolicy p(rotation_, translation_, scale_);

  return p.transform(operand);
}

#include "SimpleTransformationPolicy.impl.h"
#include "MultithreadedTransformationPolicy.impl.h"

template <unsigned N, unsigned P, typename NUM> 
std::shared_ptr< const Transformation< N, P, NUM > > 
TransformationFactory< N, P, NUM >::pointerToImpl_ = NULL;
#endif // TRANSFORMATION_IMPL_H
