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

#include "Tree.h"

#include <stdexcept>
#include <string>
#include <vector>
#include <map>

class Displayable;

/// Carries a description of a Displayable class, including its relation to other Displayables.
/** Displayable classes belong to several categories - for instance, RealFunction,
 *  Surface or Object. Each of these classes contains subclasses, such as Torus1,
 *  Horizon or Hypersponge. These classes are arranged in a tree-like structure,
 *  mirroring the inheritance diagram of the classes. DisplayableClass represents
 *  one node in that inheritance tree.
 *
 *  The information stored in DisplayableClass nodes and the entire tree can be
 *  used to print a tree of the inheritance diagram, or to generate a menu
 *  structure of these classes.
 *
 *  Subclasses of Displayable must use the FunctionFactory::registerFunction()
 *  method on declaration (in the header file), such as this:
 *  \code
 *  class MyNewDisplayableSubclass: public Displayable {
 *    // ...
 *  };
 *
 *  namespace {
 *    Displayable *createMyNewDisplayableSubclass() { return new MyNewDisplayableSubclass(); }
 *    const bool registeredXYZ =    // you must use a variable name that is unique in the anonymous namespace
 *            TheFunctionFactory::Instance().registerFunction(createMyNewDisplayableSubclass, "Displayable");
 *  }
 *  \endcode
 */
class DisplayableClass {

public:

  /// Thrown when a DisplayableClass object is requested that has not been registered.
  struct DisplayableClassException: public std::logic_error {
    DisplayableClassException(const std::string &message): std::logic_error(message) { }
  };

  DisplayableClass(const std::string &name, const std::string &description, const std::string &parent_name);

  std::string getName() const;
  std::string getDescription() const;

  /// Adds a subclass to the current node.
  void addDisplayable(const std::string &displayable_name);
  /// Returns the names of the Displayable classes inheriting from the class described in this node.
  std::vector<std::string> getDisplayableNames() const;
  /// Not yet implemented. What was this about, again?
  /** Damn, I must remember to comment functions as soon as I write them. */
  std::vector<Displayable*> getDisplayables() const;

  /// Returns the classes which inherit from the class described in the current node.
  std::vector<DisplayableClass> getSubClasses() const;

  /// Retrieves the info stored for the class with the name \p class_name.
  static DisplayableClass &findClass(const std::string &class_name);

  /// Generate the root node of the inheritance hierarchy.
  /** This function must be called in the header file Displayable.h. It must be
   *  called before any subclasses of Displayable are declared.
   */
  static const DisplayableClass &makeRootNode(const std::string &class_name,
                                              const std::string &description);
  /// The root node of the inheritance hierarchy.
  /** If this does not point to the class Displayable, shoot me. */
  static DisplayableClass &getRootNode();

  /// Print the list of classes inheriting from the current node.
  void printSubclasses() const;
//  void print() const;

private:

  typedef std::map<std::string, DisplayableClass *> subclass_container_type;
  typedef std::vector<std::string> displayable_container_type;
  typedef subclass_container_type::iterator subclass_iterator;
  typedef subclass_container_type::const_iterator subclass_const_iterator;

  /// Create a DisplayableClass without a parent node. This may happen only once and creates the root node.
  DisplayableClass(const std::string & name, const std::string &description);

  void addSubClass(DisplayableClass &child);

  DisplayableClass &findSubClass(const std::string &class_name);

  std::string class_name_;
  std::string class_description_;

  subclass_container_type subclasses_;
  displayable_container_type displayables_;

  static DisplayableClass *root_node_;

  static Tree<DisplayableClass> class_tree_;

};

#endif // DISPLAYABLECLASS_H
