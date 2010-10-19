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

#include "Tree.h"

#define WTFISWRONGWITHYOU

template < class Node >
Tree<Node>::Tree(): current_node_(), sub_trees_() { }

template < class Node >
Tree<Node>::Tree(const Node &node): current_node_(node), sub_trees_() { }

template < class Node >
const Node &Tree<Node>::getNode() const { return current_node_; }

template < class Node >
Node &Tree<Node>::getNode() { return current_node_; }

template < class Node >
void Tree<Node>::addNode(const Node &new_node) {
  addTree(Tree(new_node));
}

template < class Node >
#ifdef WTFISWRONGWITHYOU
const std::list< Tree<Node> > &
#else
const Tree<Node>::sub_tree_type &
#endif
Tree<Node>::getSubTrees() const {
  return sub_trees_;
}

template < class Node >
#ifdef WTFISWRONGWITHYOU
std::list< Tree<Node> > &
#else
Tree<Node>::sub_tree_type &
#endif
Tree<Node>::getSubTrees() {
  return sub_trees_;
}

template < class Node >
void Tree<Node>::addTree(const Tree<Node> &new_tree) {
  sub_trees_.push_back(new_tree);
}

