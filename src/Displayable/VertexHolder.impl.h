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
#include "ColorManager.h"

#include "FunctionValueGrid.h"
#include "TransformationFactory.impl.h"
#include "Transformation.impl.h"
#include "Projection.impl.h"
#include "GridDrawer.impl.h"


using VecMath::Vector;
using VecMath::MultiDimensionalVector;

using std::shared_ptr;

namespace DepthCueUtil {
    void checkMinimum(const VecMath::Vector<4, double> &,
                       const VecMath::Vector<4, double> &xtrans);
    void resetMin();
    double getWmin();
    
    void checkMaximum(const VecMath::Vector<4, double> &,
                       const VecMath::Vector<4, double> &xtrans);
    void resetMax();
    double getWmax();

    void setDepthCueColor(const VecMath::Vector<4, double> &x,
                          const VecMath::Vector<4, double> &xtrans);
    
    void calibrateColor(const VecMath::Vector<4, double> &x);
    
}

template <unsigned N, unsigned P, typename NUM>
class VertexHolder<N, P, NUM>::Impl {

public:

    Impl(VertexHolder<N, P, NUM> *parent): parent_(parent) { }

    void applyDepthCue() {
        findMaximumW();
        findMinimumW();
        parent_->for_each_vertex_transformed(DepthCueUtil::setDepthCueColor);
    }
    
    double findMinimumW() {
        DepthCueUtil::resetMin();
        parent_->for_each_vertex_transformed(DepthCueUtil::checkMinimum);
        return DepthCueUtil::getWmin();
    }
    double findMaximumW() {
        DepthCueUtil::resetMax();
        parent_->for_each_vertex_transformed(DepthCueUtil::checkMaximum);
        return DepthCueUtil::getWmax();
    }

    /// Array of function values.
    VertexGrid<N, P, NUM> X_;
    /// Array of function values after transform.
    typename VertexGrid<N, P, NUM>::value_storage_type Xtrans_;
    /// Array of projected function values.
    MultiDimensionalVector< projected_vertex_type, P > Xscr_;

private: 
    
    VertexHolder<N, P, NUM> *parent_;
    
};

////////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned P, typename NUM>
VertexHolder<N, P, NUM>::VertexHolder(ParameterMap parms):
  Displayable(parms),
  pImpl_(new Impl(this)) { }

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
  if (DepthCue4D) pImpl_->applyDepthCue();
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::calibrateColors() {
    for_each_vertex(DepthCueUtil::calibrateColor);
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
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
VertexHolder<N, P, NUM>::X() const {
  return pImpl_->X_.getValues();
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::setX(const VertexGrid<N, P, NUM>& x) {
  pImpl_->X_ = x;
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
VertexHolder<N, P, NUM>::Xtrans() const {
  return pImpl_->Xtrans_;
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::setXtrans(const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P >& x) {
  pImpl_->Xtrans_ = x;
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<3, NUM>, P > &
VertexHolder<N, P, NUM>::Xscr() const {
  return pImpl_->Xscr_;
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::setXscr(const VecMath::MultiDimensionalVector< VecMath::Vector<3, NUM>, P >& x) {
  pImpl_->Xscr_ = x;
}

template <unsigned N, unsigned P, typename NUM>
const VertexGrid<N, P, NUM> &
VertexHolder<N, P, NUM>::getGrid() const {
  return pImpl_->X_;
}

template <unsigned N, unsigned P, typename NUM>
VertexGrid<N, P, NUM> &
VertexHolder<N, P, NUM>::getGridNonConst() {
  return pImpl_->X_;
}

#endif