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

#include "DefinitionSpaceRange.h"

double DefinitionSpaceRange::defaultMin = -1.;
double DefinitionSpaceRange::defaultMax =  1.;
double DefinitionSpaceRange::defaultStep = 0.1;

struct DefinitionSpaceRange::Impl {

  Impl(): minValue_(0), maxValue_(0), stepsize_(0), numSteps_(1) { }

  Impl(double minValue, double maxValue, double stepsize):
    minValue_(minValue), maxValue_(maxValue), stepsize_(stepsize) {
    recalibrateNumSteps();
  }

  Impl(double minValue, double maxValue, unsigned int numSteps):
    minValue_(minValue), maxValue_(maxValue), numSteps_(numSteps) {
    recalibrateStepsize();
  }

  void recalibrate();
  void recalibrateStepsize();
  void recalibrateNumSteps();

  double minValue_;
  double maxValue_;
  double stepsize_;
  unsigned numSteps_;

};

void DefinitionSpaceRange::Impl::recalibrate() {
  if (numSteps_) {
    recalibrateStepsize();
  } else {
    recalibrateNumSteps();
  }
}

void DefinitionSpaceRange::Impl::recalibrateStepsize() {
    stepsize_ = (maxValue_-minValue_)/(numSteps_-1);
}

void DefinitionSpaceRange::Impl::recalibrateNumSteps() {
    numSteps_ = (unsigned)((maxValue_-minValue_)/stepsize_)+1;
}

DefinitionSpaceRange::DefinitionSpaceRange(): pImpl_(new Impl()) { }

DefinitionSpaceRange::DefinitionSpaceRange(double minValue, double maxValue, double stepsize):
  pImpl_(new Impl(minValue, maxValue, stepsize)) { }

DefinitionSpaceRange::DefinitionSpaceRange(double minValue, double maxValue, unsigned int numSteps):
  pImpl_(new Impl(minValue, maxValue, numSteps)) { }

DefinitionSpaceRange::~DefinitionSpaceRange() { }

double DefinitionSpaceRange::getMaxValue() const { return pImpl_->maxValue_; }
void DefinitionSpaceRange::setMaxValue(double maxValue) {
  pImpl_->maxValue_ = maxValue;
  pImpl_->recalibrate();
}

double DefinitionSpaceRange::getMinValue() const { return pImpl_->minValue_; }
void DefinitionSpaceRange::setMinValue(double minValue) {
  pImpl_->minValue_ = minValue;
  pImpl_->recalibrate();
}

double DefinitionSpaceRange::getStepsize() const { return pImpl_->stepsize_; }
void DefinitionSpaceRange::setStepsize(double stepsize) {
  pImpl_->stepsize_ = stepsize;
  pImpl_->recalibrateNumSteps();
}

unsigned int DefinitionSpaceRange::getNumSteps() const { return pImpl_->numSteps_; }
void DefinitionSpaceRange::setNumSteps(unsigned int numSteps) {
  pImpl_->numSteps_ = numSteps;
  pImpl_->recalibrateStepsize();
}

