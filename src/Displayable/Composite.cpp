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

#include <list>
#include <memory>
#include <algorithm>

using std::list;
using std::shared_ptr;

struct Composite::Impl {
  typedef list< shared_ptr< Displayable > > list_type;
  list_type sub_objects_;
};

Composite::Composite(): Displayable(), pImpl_(new Impl) { }

Composite::Composite(ParameterMap parameters): Displayable(parameters), pImpl_(new Impl) { }

Composite::~Composite() { }

void Composite::Transform(const VecMath::Rotation< 4 >& R, const VecMath::Vector< 4 >& T) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin(); 
       i != pImpl_->sub_objects_.end(); ++i) {
    (*i)->Transform(R, T);                    
  }
}

void Composite::Project(double ScrW, double CamW, bool DepthCue4D) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin(); 
       i != pImpl_->sub_objects_.end(); ++i) {
    (*i)->Project(ScrW, CamW, DepthCue4D);                    
  }
}

void Composite::Draw(UI::View* view) {
  for (Impl::list_type::iterator i = pImpl_->sub_objects_.begin(); 
       i != pImpl_->sub_objects_.end(); ++i) {
    (*i)->Draw(view);                    
  }
}

