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

#include "Rotation.impl.h"
#include "TransformationFactory.h"

template <unsigned N, unsigned P, typename NUM>
TransformationImpl<N, P, NUM>::TransformationImpl(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale): 
  rotation_(rotation), translation_(translation), scale_(scale) { }

#if 0
template <unsigned N, unsigned P, typename NUM, typename TransformationPolicy>
TransformationWithPolicy<N, P, NUM, TransformationPolicy>::TransformationWithPolicy(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale): 
  TransformationImpl<N, P, NUM>(rotation, translation, scale) { }

template <unsigned N, unsigned P, typename NUM, typename TransformationPolicy>
typename TransformationWithPolicy<N, P, NUM, TransformationPolicy>::value_storage_type
TransformationWithPolicy<N, P, NUM, TransformationPolicy>::transform(
  const value_storage_type &operand) const {
    TransformationPolicy p(
        TransformationImpl<N, P, NUM>::rotation_, 
        TransformationImpl<N, P, NUM>::translation_, 
        TransformationImpl<N, P, NUM>::scale_
    );

    return p.transform(operand);
}
#endif
#endif // TRANSFORMATION_IMPL_H
