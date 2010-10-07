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
#include "DefinitionRangeOfDimension.impl.h"


using VecMath::Vector;
using VecMath::MultiDimensionalVector;

using std::tr1::shared_ptr;

template <unsigned N, unsigned P, typename NUM>
class FunctionHolder<N, P, NUM>::Impl {

  public:

    Impl(double tmin, double tmax, double dt,
         double umin, double umax, double du,
         double vmin, double vmax, double dv);
    Impl(shared_ptr< function_type > f,
         double tmin, double tmax, double dt,
         double umin, double umax, double du,
         double vmin, double vmax, double dv);


    unsigned getNumParameters() { return function_->getNumParameters(); }

    void Initialize();

    const DefinitionRangeOfDimension<P> &getDefinitionRange() const {
      return definitionRange_;
    }

    const MultiDimensionalVector< vertex_type, P > &X() const {
      return _X.getValues();
    }
    void setX(const FunctionValueGrid<N, P, NUM>& x) {
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

    void setDefinitionRange(double tmin, double tmax, double dt,
                            double umin, double umax, double du,
                            double vmin, double vmax, double dv);

    DefinitionRangeOfDimension<P> definitionRange_;

    /// Array of function values.
    FunctionValueGrid<N, P, NUM> _X;

  private:

    /// Array of function values after transform.
    typename FunctionValueGrid<N, P, NUM>::value_storage_type _Xtrans;
    /// Array of projected function values.
    MultiDimensionalVector< projected_vertex_type, P > _Xscr;

    /// Pointer to the actual ParametricFunction doing all the work.
    shared_ptr< function_type > function_;

    void addSafetyMargin(Vector<3, unsigned> &steps) { steps += 2; }

};

template <unsigned N, unsigned P, typename NUM>
FunctionHolder<N, P, NUM>::Impl::Impl(
    double tmin, double tmax, double dt,
    double umin, double umax, double du,
    double vmin, double vmax, double dv):
  definitionRange_() {
  setDefinitionRange(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
}

template <unsigned N, unsigned P, typename NUM>
FunctionHolder<N, P, NUM>::Impl::Impl(
    shared_ptr< function_type > f,
    double tmin, double tmax, double dt,
    double umin, double umax, double du,
    double vmin, double vmax, double dv):
  definitionRange_(), function_(f) {
  setDefinitionRange(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
}

template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::Impl::setDefinitionRange(double tmin, double tmax, double dt,
                                                         double umin, double umax, double du,
                                                         double vmin, double vmax, double dv) {
#ifdef DEBUG_NUM_STEPS
  std::cerr << "FunctionHolder<N, P, NUM>::Impl::setDefinitionRange(" << tmin<< ", " << tmax<< ", " << dt
            << ", " << umin<< ", " << umax<< ", " << du<< ", "
            << vmin<< ", " << vmax<< ", " << dv << ")\n";
#endif
  if (P > 0) definitionRange_.setRange(0, DefinitionSpaceRange(tmin, tmax, dt));
  if (P > 1) definitionRange_.setRange(1, DefinitionSpaceRange(umin, umax, du));
  if (P > 2) definitionRange_.setRange(2, DefinitionSpaceRange(vmin, vmax, dv));
}

template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::Impl::Initialize () {

  Vector<P, NUM> min = definitionRange_.getMinValue();
  Vector<P, NUM> max = definitionRange_.getMaxValue();
  Vector<P, unsigned> numSteps = definitionRange_.getNumSteps();
  addSafetyMargin(numSteps);

  _X = FunctionValueGrid<N, P, NUM>(function_, numSteps, min, max);

}

////////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned P, typename NUM>
FunctionHolder<N, P, NUM>::FunctionHolder(shared_ptr< function_type > f):
  Function(ParameterMap()),
  pImpl_(new Impl(
      f,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep)) { }

template <unsigned N, unsigned P, typename NUM>
FunctionHolder<N, P, NUM>::FunctionHolder(ParameterMap parms):
  Function(parms),
  pImpl_(new Impl(
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep,
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep)) { }

template <unsigned N, unsigned P, typename NUM>
unsigned int FunctionHolder<N, P, NUM>::getDefinitionSpaceDimensions() {
  return P;
}

template <unsigned N, unsigned P, typename NUM>
unsigned int FunctionHolder<N, P, NUM>::getNumParameters() {
  return pImpl_->getNumParameters();
}

template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::setDefinitionRange(double tmin, double tmax, double dt,
                                                   double umin, double umax, double du,
                                                   double vmin, double vmax, double dv) {
#ifdef DEBUG_NUM_STEPS
  std::cerr << "FunctionHolder<N, P, NUM>::setDefinitionRange(" << tmin<< ", " << tmax<< ", " << dt
            << ", " << umin<< ", " << umax<< ", " << du<< ", "
            << vmin<< ", " << vmax<< ", " << dv << ")\n";
#endif
  pImpl_->setDefinitionRange(tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
}
template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::Initialize () {
  pImpl_->Initialize();
  calibrateColors();
}

template <unsigned N, unsigned P, typename NUM>
const DefinitionRangeOfDimension<P> &FunctionHolder<N, P, NUM>::getDefinitionRange() const {
  return pImpl_->getDefinitionRange();
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
FunctionHolder<N, P, NUM>::X() const {
  return pImpl_->X();
}

template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::setX(const FunctionValueGrid<N, P, NUM>& x) {
  pImpl_->setX(x);
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
FunctionHolder<N, P, NUM>::Xtrans() const {
  return pImpl_->Xtrans();
}

template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::setXtrans(const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P >& x) {
  pImpl_->setXtrans(x);
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<3, NUM>, P > &
FunctionHolder<N, P, NUM>::Xscr() const {
  return pImpl_->Xscr();
}

template <unsigned N, unsigned P, typename NUM>
void FunctionHolder<N, P, NUM>::setXscr(const VecMath::MultiDimensionalVector< VecMath::Vector<3, NUM>, P >& x) {
  pImpl_->setXscr(x);
}

#endif