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

#ifndef DEFINITIONRANGEOFDIMENSION_IMPL_H
#define DEFINITIONRANGEOFDIMENSION_IMPL_H

#include "DefinitionRangeOfDimension.h"

template<unsigned D>
double DefinitionRangeOfDimension<D>::getMinValue(unsigned i) const {
  assert(i < D);
  return range_[i].getMinValue();
}

template<unsigned D>
VecMath::Vector<D, double> DefinitionRangeOfDimension<D>::getMinValue() const {
  VecMath::Vector<D, double> minValue;
  for (unsigned i = 0; i < D; ++i) {
    minValue[i] = getMinValue(i);
  }
  return minValue;
}

template<unsigned D>
void DefinitionRangeOfDimension<D>::setMinValue(unsigned i, double minValue) {
  assert(i < D);
  range_[i].setMinValue(minValue);
}

template<unsigned D>
double DefinitionRangeOfDimension<D>::getMaxValue(unsigned i) const {
  assert(i < D);
  return range_[i].getMaxValue();
}

template<unsigned D>
VecMath::Vector<D, double> DefinitionRangeOfDimension<D>::getMaxValue() const {
  VecMath::Vector<D, double> maxValue;
  for (unsigned i = 0; i < D; ++i) {
    maxValue[i] = getMaxValue(i);
  }
  return maxValue;
}

template<unsigned D>
void DefinitionRangeOfDimension<D>::setMaxValue(unsigned i, double maxValue) {
  assert(i < D);
  range_[i].setMaxValue(maxValue);
}

template<unsigned D>
double DefinitionRangeOfDimension<D>::getStepsize(unsigned i) const {
  assert(i < D);
  return range_[i].getStepsize();
}

template<unsigned D>
void DefinitionRangeOfDimension<D>::setStepsize(unsigned i, double stepsize) {
  assert(i < D);
  range_[i].setStepsize(stepsize);
}

template<unsigned D>
unsigned DefinitionRangeOfDimension<D>::getNumSteps(unsigned i) const {
  assert(i < D);
  return range_[i].getNumSteps();
}

template<unsigned D>
VecMath::Vector<D, unsigned> DefinitionRangeOfDimension<D>::getNumSteps() const {
  VecMath::Vector<D, unsigned> numSteps;
  for (unsigned i = 0; i < D; ++i) {
    numSteps[i] = getNumSteps(i);
  }
  return numSteps;
}

template<unsigned D>
void DefinitionRangeOfDimension<D>::setNumSteps(unsigned i, unsigned numSteps) {
  assert(i < D);
  range_[i].setNumSteps(numSteps);
}

template<unsigned D>
void DefinitionRangeOfDimension<D>::setRange(unsigned i, const DefinitionSpaceRange &range) {
#ifdef DEBUG_NUM_STEPS
  std::cerr << "DefinitionRangeOfDimension<D>::setRange(" << i << range.toString() << ")\n";
#endif
  assert(i < D);
  range_[i] = range;
}

#endif
