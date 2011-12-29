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

#ifndef FUNCTIONHOLDER_IMPL_H
#define FUNCTIONHOLDER_IMPL_H

#include "FunctionHolder.h"

#include "FunctionValueGrid.h"
#include "VertexHolder.impl.h"
#include "TransformationFactory.impl.h"
#include "Transformation.impl.h"
#include "Projection.impl.h"
#include "GridDrawer.impl.h"
#include "DefinitionRangeOfDimension.impl.h"


using VecMath::Vector;
using VecMath::MultiDimensionalVector;

using std::shared_ptr;

template <unsigned N, unsigned P, typename NUM>
class FunctionHolder<N, P, NUM>::Impl {

  public:

    Impl(double tmin, double tmax, double dt,
         double umin, double umax, double du,
         double vmin, double vmax, double dv):
        definitionRange_() {
        setDefinitionRange(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
    }
  
    Impl(shared_ptr< function_type > f,
         double tmin, double tmax, double dt,
         double umin, double umax, double du,
         double vmin, double vmax, double dv):
        definitionRange_(), function_(f) {
        setDefinitionRange(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
    }


    unsigned getNumParameters() {
      assert(function_);
      return function_->getNumParameters();
    }

    const DefinitionRangeOfDimension<P> &getDefinitionRange() const {
      return definitionRange_;
    }

    void setDefinitionRange(double tmin, double tmax, double dt,
                            double umin, double umax, double du,
                            double vmin, double vmax, double dv) {
        if (P > 0) definitionRange_.setRange(0, DefinitionSpaceRange(tmin, tmax, dt));
        if (P > 1) definitionRange_.setRange(1, DefinitionSpaceRange(umin, umax, du));
        if (P > 2) definitionRange_.setRange(2, DefinitionSpaceRange(vmin, vmax, dv));
    }

    Vector<P, unsigned> getNumSteps() {
        Vector<P, unsigned> numSteps = definitionRange_.getNumSteps();
        addSafetyMargin(numSteps);
        return numSteps;
    }

    Vector<P, NUM> min() { return definitionRange_.getMinValue(); }
    Vector<P, NUM> max() { return definitionRange_.getMaxValue(); }
    
    DefinitionRangeOfDimension<P> definitionRange_;

    /// Pointer to the actual ParametricFunction doing all the work.
    shared_ptr< function_type > function_;

    void addSafetyMargin(Vector<P, unsigned> &steps) { steps += 2; }

};

////////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned P, typename NUM>
FunctionHolder<N, P, NUM>::FunctionHolder(shared_ptr< function_type > f):
  VertexHolder<N, P, NUM>(f),
  pImpl_(new Impl(
      f,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep)) { }

template <unsigned N, unsigned P, typename NUM>
FunctionHolder<N, P, NUM>::FunctionHolder(ParameterMap parms):
  VertexHolder<N, P, NUM>(parms),
  pImpl_(new Impl(
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep)) { }

template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::Draw(UI::View *view) {
  GridDrawer<P, NUM, 3> draw(this->X(), this->Xscr(), view);
  draw.execute();
}

template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::setDefinitionRange(double tmin, double tmax, double dt,
                                                   double umin, double umax, double du,
                                                   double vmin, double vmax, double dv) {
  pImpl_->setDefinitionRange(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
}

template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::Initialize () {
  this->setX(
      FunctionValueGrid<N, P, NUM>(
          pImpl_->function_, pImpl_->getNumSteps(), pImpl_->min(), pImpl_->max()
      )
  );
  this->calibrateColors();
}

template <unsigned N, unsigned P, typename NUM>
const DefinitionRangeOfDimension<P> &FunctionHolder<N, P, NUM>::getDefinitionRange() const {
  return pImpl_->getDefinitionRange();
}


#endif