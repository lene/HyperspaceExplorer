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

#include "DisplayableClass.h"

#include <cassert>

const DisplayableClass * DisplayableClass::root_node_ = NULL;

DisplayableClass::DisplayableClass(const std::string& name, const std::string &description):
  class_name_(name), subclasses_(), displayables_() { }

DisplayableClass::DisplayableClass(const std::string& name, const std::string &description,
                                   const std::string& parent_name):
  class_name_(name), subclasses_(), displayables_() {
  DisplayableClass parent_temporary = findClass(parent_name);
  parent_temporary.addSubClass(*this);
}

std::string DisplayableClass::getName() const { return class_name_; }

const DisplayableClass& DisplayableClass::findSubClass(const std::string& class_name) const {
  if (getName() == class_name) return *this;
  for (subclass_container_type::const_iterator i = subclasses_.begin(); i != subclasses_.end(); ++i) {
    (*i)->findSubClass(class_name);
  }

}

const DisplayableClass& DisplayableClass::findClass(const std::string& class_name) {
  return getRootNode().findSubClass(class_name);
}

std::vector< DisplayableClass > DisplayableClass::getSubClasses() const {
  std::vector< DisplayableClass > subclasses;
  for (subclass_container_type::const_iterator i = subclasses_.begin(); i != subclasses_.end(); ++i) {
    subclasses.push_back(**i);
  }
  return subclasses;
}

std::vector< Displayable > DisplayableClass::getChildDisplayables() const {

}

const DisplayableClass& DisplayableClass::getRootNode() {
  assert(root_node_ != NULL);
  return *root_node_;
}

const DisplayableClass& DisplayableClass::makeRootNode(const std::string& class_name, const std::string &description) {
//  assert(root_node_ == NULL);
  root_node_ = new DisplayableClass(class_name, description);
  return getRootNode();
}

void DisplayableClass::addSubClass(const DisplayableClass& child) {
  subclasses_.push_back(&child);
}
