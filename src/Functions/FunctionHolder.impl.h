/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "FunctionHolder.h"

#include "FunctionValueGrid.h"
#include "DefinitionRangeOfDimension.impl.h"


using VecMath::Vector;
using VecMath::MultiDimensionalVector;

template <unsigned N, unsigned P, typename NUM>
class FunctionHolder<N, P, NUM>::Impl {

  public:

    Impl(double tmin, double tmax, double dt,
         double umin, double umax, double du,
         double vmin, double vmax, double dv);

    const MultiDimensionalVector< Vector<N, NUM>, P > &X() const { 
      return _X.getValues(); 
    }
    const MultiDimensionalVector< Vector<N, NUM>, P > &Xtrans() const { 
      return _Xtrans; 
    }
    const MultiDimensionalVector< Vector<3, NUM>, P > &Xscr() const { 
      return _Xscr; 
    }
    
  private:
    
    DefinitionRangeOfDimension<P> definitionRange_;

    /// Array of function values.
    FunctionValueGrid<N, P, NUM> _X;
    /// Array of function values after transform.
    typename FunctionValueGrid<N, P, NUM>::value_storage_type _Xtrans;
    /// Array of projected function values.
    MultiDimensionalVector< Vector<3, NUM>, P > _Xscr;

};

template <unsigned N, unsigned P, typename NUM>
FunctionHolder<N, P, NUM>::Impl::Impl(double tmin, double tmax, double dt, 
                                      double umin, double umax, double du, 
                                      double vmin, double vmax, double dv):
  definitionRange_() { 
  if (P > 0) definitionRange_.setRange(0, DefinitionSpaceRange(tmin, tmax, dt));
  if (P > 1) definitionRange_.setRange(1, DefinitionSpaceRange(umin, umax, du));
  if (P > 2) definitionRange_.setRange(2, DefinitionSpaceRange(vmin, vmax, dv));
}

template <unsigned N, unsigned P, typename NUM>
FunctionHolder<N, P, NUM>::FunctionHolder(): 
  Function(ParameterMap()), 
  pImpl_(new Impl(
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep, 
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep, 
      DefinitionSpaceRange::defaultMin, DefinitionSpaceRange::defaultMax, DefinitionSpaceRange::defaultStep)) { }

template <unsigned N, unsigned P, typename NUM>
unsigned int FunctionHolder<N, P, NUM>::getDefinitionSpaceDimensions() {
  return P;
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
FunctionHolder<N, P, NUM>::X() const {
  return pImpl_->X();
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &
FunctionHolder<N, P, NUM>::Xtrans() const {
  return pImpl_->Xtrans();
}

template <unsigned N, unsigned P, typename NUM>
const VecMath::MultiDimensionalVector< VecMath::Vector<3, NUM>, P > &
FunctionHolder<N, P, NUM>::Xscr() const {
  return pImpl_->Xscr();
}
