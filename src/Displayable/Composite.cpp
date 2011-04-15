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

#include "Composite.h"

#include "ParameterMap.h"

#include "Vector.impl.h"
#include "Rotation.impl.h"

#include <list>
#include <memory>
#include <algorithm>

using std::list;
using std::shared_ptr;

using VecMath::Vector;
using VecMath::makeVector;
using VecMath::Rotation;
using VecMath::makeRotation;

struct CompositeComponent {
  CompositeComponent(
    shared_ptr< Displayable > component,
    Vector< 4 > translation = makeVector(0., 0., 0., 0.),
    const VecMath::Rotation< 4 > rotation = makeRotation(0., 0., 0., 0., 0., 0.),
    const VecMath::Vector< 4 > scale = makeVector(1., 1., 1., 1.)
  ):
    component_(component), translation_(translation), rotation_(rotation), scale_(scale) { }

  shared_ptr< Displayable > component_;
  const VecMath::Vector< 4 > translation_;
  const VecMath::Rotation< 4 > rotation_;
  const VecMath::Vector< 4 > scale_;
};

struct Composite::Impl {
  typedef list< CompositeComponent > list_type;
  list_type sub_objects_;
};

Composite::Composite(): Displayable(), pImpl_(new Impl) { }

Composite::Composite(ParameterMap parameters): Displayable(parameters), pImpl_(new Impl) { }

Composite::~Composite() { }

void Composite::Transform(const VecMath::Rotation< 4 >& R, const VecMath::Vector< 4 >& T) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin();
       i != pImpl_->sub_objects_.end(); ++i) {
    i->component_->Transform(i->rotation_+R, i->translation_+T);
  }
}

void Composite::Project(double ScrW, double CamW, bool DepthCue4D) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin();
       i != pImpl_->sub_objects_.end(); ++i) {
    i->component_->Project(ScrW, CamW, DepthCue4D);
  }
}

void Composite::Draw(UI::View* view) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin();
       i != pImpl_->sub_objects_.end(); ++i) {
    i->component_->Draw(view);
  }
}

void Composite::addComponent(std::shared_ptr<Displayable> component,
                             const VecMath::Vector< 4 >& T,
                             const VecMath::Rotation< 4 >& R) {
  pImpl_->sub_objects_.push_back(CompositeComponent(component, T, R));
}

unsigned int Composite::getNumComponents() {
  return pImpl_->sub_objects_.size();
}

void Composite::calibrateColors() const {
  throw NotYetImplementedException("Composite::calibrateColors()");
}

VecMath::Vector< 4 >& Composite::operator()(double , double , double ) {
  throw NotYetImplementedException("Composite::operator()");
}

unsigned int Composite::getDefinitionSpaceDimensions() { return 0; }

void Composite::for_each_projected(Displayable::function_on_projected_vertex ) {
  throw NotYetImplementedException("Composite::getDefinitionSpaceDimensions()");

}

void Composite::for_each_vertex(Displayable::function_on_fourspace_vertex ) {
  throw NotYetImplementedException("Composite::for_each_vertex()");

}

void Composite::Initialize( )
{
  throw NotYetImplementedException("Composite::Initialize()");

}

void Composite::ReInit(double _tmin, double _tmax, double _dt,
                       double _umin, double _umax, double _du,
                       double _vmin, double _vmax, double _dv) {
  throw NotYetImplementedException("Composite::ReInit()");

}



