/*
Hyperspace Explorer - visualizing higher-dimensional geometry
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

#ifndef VertexHolder_IMPL_H
#define VertexHolder_IMPL_H

#include "VertexHolder.h"

#include "FunctionValueGrid.h"
#include "TransformationFactory.impl.h"
#include "Transformation.impl.h"
#include "Projection.impl.h"
#include "GridDrawer.impl.h"


using VecMath::Vector;
using VecMath::MultiDimensionalVector;

using std::shared_ptr;

template <unsigned N, unsigned P, typename NUM>
class VertexHolder<N, P, NUM>::Impl {

  public:

    Impl() { }
    Impl(shared_ptr< function_type > f): function_(f) { }


    unsigned getNumParameters() {
      assert(function_);
      return function_->getNumParameters();
    }

    void Initialize();

    const MultiDimensionalVector< vertex_type, P > &X() const {
      return _X.getValues();
    }
    void setX(const VertexGrid<N, P, NUM>& x) {
      _X = x;
    }

    const MultiDimensionalVector< vertex_type, P > &Xtrans() const {
      return _Xtrans;
    }
    void setXtrans(const VecMath::MultiDimensionalVector< vertex_type, P >& x) {
      _Xtrans = x;
    }

    const MultiDimensionalVector< projected_vertex_type, P > &Xscr() const {
      return _Xscr;
    }
    void setXscr(const VecMath::MultiDimensionalVector< projected_vertex_type, P >& x) {
      _Xscr = x;
    }

    /// Array of function values.
    VertexGrid<N, P, NUM> _X;

  private:

    /// Array of function values after transform.
    typename VertexGrid<N, P, NUM>::value_storage_type _Xtrans;
    /// Array of projected function values.
    MultiDimensionalVector< projected_vertex_type, P > _Xscr;

    /// Pointer to the actual ParametricFunction doing all the work.
    shared_ptr< function_type > function_;

};

////////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned P, typename NUM>
VertexHolder<N, P, NUM>::VertexHolder(shared_ptr< function_type > f):
  Displayable(ParameterMap()),
  pImpl_(new Impl(f)) { }

template <unsigned N, unsigned P, typename NUM>
VertexHolder<N, P, NUM>::VertexHolder(ParameterMap parms):
  Displayable(parms),
  pImpl_(new Impl()) { }

/** \param R rotation
 *  \param T translation                                                      */
template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::Transform (const VecMath::Rotation<N, NUM> &R,
                                           const vertex_type &T,
                                           const vertex_type &scale) {
  const Transformation<N, P, NUM> &xform = TransformationFactory<N, P, NUM>::create(R, T, scale);
  setXtrans(xform.transform(X()));
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::Project (double ScrW, double CamW, bool DepthCue4D) {
  Projection<N, 3, P, NUM> p(ScrW, CamW, DepthCue4D);
  setXscr(p.project(Xtrans()));
}

template <unsigned N, unsigned P, typename NUM>
unsigned int VertexHolder<N, P, NUM>::getDefinitionSpaceDimensions() {
  return P;
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::for_each_vertex(Displayable::function_on_fourspace_vertex apply) {
  X().for_each(apply);
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::for_each_vertex_transformed(Displayable::function_on_fourspace_and_transformed_vertex apply) {
  VecMath::for_each(X(), Xtrans(), apply);
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::for_each_vertex_transformed_projected(Displayable::function_on_fourspace_transformed_and_projected_vertex apply) {
  VecMath::for_each(X(), Xtrans(), Xscr(), apply);
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::for_each_projected(Displayable::function_on_projected_vertex apply) {
  Xscr().for_each(apply);
}

template <unsigned N, unsigned P, typename NUM>
unsigned int VertexHolder<N, P, NUM>::getNumParameters() {
  return pImpl_->getNumParameters();
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
VertexHolder<N, P, NUM>::X() const {
  return pImpl_->X();
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::setX(const VertexGrid<N, P, NUM>& x) {
  pImpl_->setX(x);
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
VertexHolder<N, P, NUM>::Xtrans() const {
  return pImpl_->Xtrans();
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::setXtrans(const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P >& x) {
  pImpl_->setXtrans(x);
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<3, NUM>, P > &
VertexHolder<N, P, NUM>::Xscr() const {
  return pImpl_->Xscr();
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::setXscr(const VecMath::MultiDimensionalVector< VecMath::Vector<3, NUM>, P >& x) {
  pImpl_->setXscr(x);
}

#endif