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

#include "FunctionFactory.h"
#include "Tree.impl.h"

#include <cassert>
#include <iostream>

DisplayableClass * DisplayableClass::root_node_ = NULL;


DisplayableClass::DisplayableClass(const std::string& name, const std::string &description,
                                   const std::string& parent_name):
  class_name_(name), class_description_(description),
  subclasses_(), displayables_() {
  findClass(parent_name).addSubClass(*this);
}


std::string DisplayableClass::getName() const {
  return class_name_;
}


std::string DisplayableClass::getDescription() const {
  return class_description_;
}


void DisplayableClass::addDisplayable(const std::string& displayable_name) {
  displayables_.push_back(displayable_name);
}


std::vector< std::string > DisplayableClass::getDisplayableNames() const {
  return displayables_;
}


std::vector< Displayable* > DisplayableClass::getDisplayables() const {
  std::vector<Displayable*> displayables;
//  for (displayable_container_type::const_iterator i = getDisplayableNames().begin();
//       i != getDisplayableNames().end(); ++i) {
//    std::cerr << *i << std::endl;
//    displayables.push_back(TheFunctionFactory::Instance().createFunction(*i));
//  }
  return displayables;
}


std::vector< DisplayableClass > DisplayableClass::getSubClasses() const {
  std::vector< DisplayableClass > subclasses;
  for (subclass_const_iterator i = subclasses_.begin(); i != subclasses_.end(); ++i) {
    subclasses.push_back(*(i->second));
  }
  return subclasses;
}


DisplayableClass& DisplayableClass::findClass(const std::string& class_name) {
  return getRootNode().findSubClass(class_name);
}


DisplayableClass& DisplayableClass::getRootNode() {
  assert(root_node_ != NULL);
  return *root_node_;
}


const DisplayableClass& DisplayableClass::makeRootNode(const std::string& class_name, const std::string &description) {
  if (root_node_ == NULL) {
    root_node_ = new DisplayableClass(class_name, description);
  }
  return getRootNode();
}


void DisplayableClass::printSubclasses() const {
  std::cerr << getName()<< ": ";
  for (subclass_const_iterator i = subclasses_.begin(); i != subclasses_.end(); ++i) {
    const DisplayableClass *subclass = i->second;
    std::cerr << subclass->getName() << ": " << subclass->getDescription() << "   ";
  }
  std::cerr << std::endl;
}


DisplayableClass::DisplayableClass(const std::string& name, const std::string &description):
  class_name_(name), class_description_(description),
  subclasses_(), displayables_() { }


void DisplayableClass::addSubClass(DisplayableClass& child) {
  subclasses_.insert(std::make_pair(child.getName(), &child));
}


DisplayableClass& DisplayableClass::findSubClass(const std::string& class_name) {
  if (getName() == class_name) return *this;
  for (subclass_iterator i = subclasses_.begin(); i != subclasses_.end(); ++i) {
    try {
      DisplayableClass &subclass = i->second->findSubClass(class_name);
      return subclass;
    } catch (const DisplayableClassException &e) { }
  }
  throw DisplayableClassException("Class \"" + class_name + "\" not found");
}
