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

#ifndef TREE_H
#define TREE_H

#include <list>

template < typename Node >
class Tree {

public:

  typedef std::list< Tree<Node> > sub_tree_type;

  Tree();
  explicit Tree(const Node &node);

  const Node &getNode() const;
  Node &getNode();
  void addNode(const Node &new_node);
  void removeNode(const Node &old_node);

  const sub_tree_type &getSubTrees() const;
  sub_tree_type &getSubTrees();
  void addTree(const Tree<Node> &new_tree);
  void removeTree(const Tree<Node> &new_tree);

  const Tree &findByNode(const Node &node) const;
  Tree &findByNode(const Node &node);

private:

  Node current_node_;
  sub_tree_type sub_trees_;

};

#endif // TREE_H
