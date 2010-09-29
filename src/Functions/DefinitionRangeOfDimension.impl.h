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
  assert(i < D);
  range_[i] = range;
}

#endif
