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

#ifndef DISPLAYABLECLASS_H
#define DISPLAYABLECLASS_H

#include <stdexcept>
#include <string>
#include <vector>
#include <map>

class Displayable;

class DisplayableClass {

public:

  struct DisplayableClassException: public std::logic_error {
    DisplayableClassException(const std::string &message): std::logic_error(message) { }
  };

  DisplayableClass(const std::string &name, const std::string &description, const std::string &parent_name);

  std::string getName() const;
  std::string getDescription() const;

  std::vector<Displayable> getDisplayables() const;
  std::vector<DisplayableClass> getSubClasses() const;

  static DisplayableClass &findClass(const std::string &class_name);

  static const DisplayableClass &makeRootNode(const std::string &class_name,
                                              const std::string &description);
  static DisplayableClass &getRootNode();

  void printSubclasses() const;
  
private:

  /// Create a DisplayableClass without a parent node. This may happen only once and creates the root node.
  DisplayableClass(const std::string & name, const std::string &description);

  void addSubClass(DisplayableClass &child);

  DisplayableClass &findSubClass(const std::string &class_name);

  typedef std::map<std::string, DisplayableClass *> subclass_container_type;
  typedef std::vector<std::string> displayable_container_type;

  std::string class_name_;
  std::string class_description_;

  subclass_container_type subclasses_;
  displayable_container_type displayables_;

  static DisplayableClass *root_node_;

};

#endif // DISPLAYABLECLASS_H
