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
#include "DepthCueUtil.h"

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

    Impl(VertexHolder<N, P, NUM> *parent): 
    X_(), Xtrans_(), Xscr_(), calibration_function(NULL),
    parent_(parent) { }

    void applyDepthCue() {
        DepthCueUtil::determineExtrema(parent_);
        parent_->for_each_vertex_transformed(DepthCueUtil::setDepthCueColor);
    }
    
    function_on_fourspace_vertex getCalibrationFunction() {
        if (calibration_function == NULL) return DepthCueUtil::calibrateColor3D;
        return calibration_function;
    }
    /// Array of function values.
    VertexGrid<N, P, NUM> X_;
    /// Array of function values after transform.
    typename VertexGrid<N, P, NUM>::value_storage_type Xtrans_;
    /// Array of projected function values.
    MultiDimensionalVector< projected_vertex_type, P > Xscr_;

    function_on_fourspace_vertex calibration_function;
    
private: 
    
    VertexHolder<N, P, NUM> *parent_;
    
};

////////////////////////////////////////////////////////////////////////////////

/** \param parms Parameters for the Displayable                               */
template <unsigned N, unsigned P, typename NUM>
VertexHolder<N, P, NUM>::VertexHolder(ParameterMap parms):
  Displayable(parms),
  pImpl_(new Impl(this)) { }

/** \param R rotation
 *  \param T translation                       
 *  \param scale scaling                                                      */
template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::Transform (const VecMath::Rotation<N, NUM> &R,
                                           const vertex_type &T,
                                           const vertex_type &scale) {
  std::shared_ptr<const Transformation<N, P, NUM> > xform(TransformationFactory::create<N, P, NUM>(R, T, scale));
  setXtrans(xform->transform(X()));
}

/**
 * @param ScrW \em w coordinate of the screen projected onto
 * @param CamW \em w coordinate of the camera
 * @param DepthCue4D whether to apply four-dimensional depth cue
 */
template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::Project (double ScrW, double CamW, bool DepthCue4D) {
  Projection<N, 3, P, NUM> p(ScrW, CamW, DepthCue4D);
  setXscr(p.project(Xtrans()));
  if (DepthCue4D) pImpl_->applyDepthCue();
}

template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::calibrateColors() {
    for_each_vertex(pImpl_->getCalibrationFunction());
}

template <unsigned N, unsigned P, typename NUM>
unsigned int VertexHolder<N, P, NUM>::getDefinitionSpaceDimensions() {
  return P;
}

/**
 * @param apply the function called for every vertex
 */
template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::for_each_vertex(Displayable::function_on_fourspace_vertex apply) {
  X().for_each(apply);
}

/**
 * @param apply the function called for every vertex and transformed vertex
 */
template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::for_each_vertex_transformed(Displayable::function_on_fourspace_and_transformed_vertex apply) {
  VecMath::for_each(X(), Xtrans(), apply);
}

/**
 * @param apply the function called for every vertex, transformed and projected vertex 
 */
template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::for_each_vertex_transformed_projected(Displayable::function_on_fourspace_transformed_and_projected_vertex apply) {
  VecMath::for_each(X(), Xtrans(), Xscr(), apply);
}

/**
 * @param apply the function called for every projected vertex
 */
template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::for_each_projected(Displayable::function_on_projected_vertex apply) {
  Xscr().for_each(apply);
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
VertexHolder<N, P, NUM>::X() const {
  return pImpl_->X_.getValues();
}

/**
 * @param x the new values for the vertices
 */
template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::setX(const VertexGrid<N, P, NUM>& x) {
  pImpl_->X_ = x;
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
VertexHolder<N, P, NUM>::Xtrans() const {
  return pImpl_->Xtrans_;
}

/**
 * @param x the new values for the transformed vertices
 */
template <unsigned N, unsigned P, typename NUM>
void VertexHolder<N, P, NUM>::setXtrans(const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P >& x) {
  pImpl_->Xtrans_ = x;
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<3, NUM>, P > &
VertexHolder<N, P, NUM>::Xscr() const {
  return pImpl_->Xscr_;
}

/**
 * @param x the new values for the projected vertices
 */
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

/**
 * @param calibrate The function called on every vertex to calibrate the ColorManager
 */
template <unsigned N, unsigned P, typename NUM>
void
VertexHolder<N, P, NUM>::setColorCalibrationFunction(function_on_fourspace_vertex calibrate) {
    pImpl_->calibration_function = calibrate;
}
#endif