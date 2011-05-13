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
#include <vector>

using std::vector;
using std::shared_ptr;

using VecMath::Vector;
using VecMath::makeVector;
using VecMath::Rotation;
using VecMath::makeRotation;


struct Composite::Impl {
  typedef vector< CompositeComponent > list_type;
  list_type sub_objects_;
};

Composite::Composite(): Displayable(), pImpl_(new Impl) { }

Composite::Composite(ParameterMap parameters): Displayable(parameters), pImpl_(new Impl) { }

Composite::~Composite() { }

void Composite::Transform(const VecMath::Rotation< 4 >& R, 
                          const VecMath::Vector< 4 >& T,
                          const VecMath::Vector< 4 >& scale) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin();
       i != pImpl_->sub_objects_.end(); ++i) {
    i->component_->Transform(i->rotation_+R, i->translation_+T, VecMath::scale(i->scale_, scale));
  }
}

void Composite::Project(double ScrW, double CamW, bool DepthCue4D) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin();
       i != pImpl_->sub_objects_.end(); ++i) {
    i->component_->Project(ScrW, CamW, DepthCue4D);
  }
}

void Composite::Draw(UI::View *view) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin();
       i != pImpl_->sub_objects_.end(); ++i) {
    i->component_->Draw(view);
  }
}

void Composite::addComponent(std::shared_ptr<Displayable> component,
                             const VecMath::Vector< 4 >& T,
                             const VecMath::Rotation< 4 >& R,
                             const VecMath::Vector<4> &scale) {
  pImpl_->sub_objects_.push_back(CompositeComponent(component, T, R, scale));
}

const CompositeComponent& Composite::getComponent(unsigned i) const {
    return pImpl_->sub_objects_[i];
}

unsigned int Composite::getNumComponents() {
  return pImpl_->sub_objects_.size();
}

void Composite::calibrateColors() const {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin();
       i != pImpl_->sub_objects_.end(); ++i) {
      i->component_->calibrateColors();
  }
}

VecMath::Vector< 4 >& Composite::operator()(double , double , double ) {
  throw NotYetImplementedException("Composite::operator()");
}

unsigned int Composite::getDefinitionSpaceDimensions() { return 0; }

void Composite::for_each_vertex(Displayable::function_on_fourspace_vertex apply) {
  for (Impl::list_type::iterator it = pImpl_->sub_objects_.begin();
          it != pImpl_->sub_objects_.end(); ++it) {
      it->component_->for_each_vertex(apply);
  }
}

void Composite::for_each_vertex_transformed(Displayable::function_on_fourspace_and_transformed_vertex apply) {
  for (Impl::list_type::iterator it = pImpl_->sub_objects_.begin();
          it != pImpl_->sub_objects_.end(); ++it) {
      it->component_->for_each_vertex_transformed(apply);
  }
}

void Composite::for_each_projected(Displayable::function_on_projected_vertex apply) {
  for (Impl::list_type::iterator it = pImpl_->sub_objects_.begin();
          it != pImpl_->sub_objects_.end(); ++it) {
      it->component_->for_each_projected(apply);
  }
}

void Composite::for_each_vertex_transformed_projected(Displayable::function_on_fourspace_transformed_and_projected_vertex apply) {
  for (Impl::list_type::iterator it = pImpl_->sub_objects_.begin();
          it != pImpl_->sub_objects_.end(); ++it) {
      it->component_->for_each_vertex_transformed_projected(apply);
  }
}
/*
void Composite::Initialize( ) {
  throw NotYetImplementedException("Composite::Initialize()");
}
*/
void Composite::ReInit(double _tmin, double _tmax, double _dt,
                       double _umin, double _umax, double _du,
                       double _vmin, double _vmax, double _dv) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin();
       i != pImpl_->sub_objects_.end(); ++i) {
      i->component_->ReInit(_tmin, _tmax, _dt,
                            _umin, _umax, _du,
                            _vmin, _vmax, _dv);
  }
  Initialize();
}

void Composite::clear() {
    pImpl_->sub_objects_.clear();
}
