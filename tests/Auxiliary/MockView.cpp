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

#include "MockView.h"

#include "MultiDimensionalVector.h"
#include "Vector.impl.h"

using std::vector;
using VecMath::Vector;

struct MockView::Impl {
  Impl(bool verbose): verbose_(verbose), drawnVertices_() { }

  bool verbose_;
  vector< Vector<4> > originalVertices_;
  vector< Vector<3> > drawnVertices_;
  vector< Face<3> > drawnFaces_;

};

template <class COLL, class ELEM>
bool is_in(COLL &collection, const ELEM &element) {
  return std::find(collection.begin(), collection.end(), element) != collection.end();
}

const double EPSILON = 1e-3;

template <unsigned D, typename NUM>
bool is_in(vector< Vector<D, NUM> > &collection, const Vector<D, NUM> &element) {
  typedef typename vector< Vector<D, NUM> >::const_iterator collection_iterator;
  for (collection_iterator i = collection.begin(); i != collection.end(); ++i) {
    if (VecMath::sqnorm(element-*i) < EPSILON) return true;
  }
  return false;
}

template <class COLL, class ELEM>
void add_if_not(COLL &collection, const ELEM &element) {
  if (!is_in(collection, element)) {
    collection.push_back(element);
  }
}

template <unsigned D>
MockView::Face<D>::Face(const VecMath::Vector< D >& v0, const VecMath::Vector< D >& v1,
                     const VecMath::Vector< D >& v2, const VecMath::Vector< D >& v3): vertex_() {
  vertex_.push_back(v0);
  vertex_.push_back(v1);
  vertex_.push_back(v2);
  vertex_.push_back(v3);
}

template <unsigned D>
bool MockView::Face<D>::operator==(const Face< D >& other) const {
  if (vertex_.size() != other.vertex_.size()) return false;

  for (size_t i = 0; i < vertex_.size(); ++i) {
    if (VecMath::sqnorm(vertex_[i]-other.vertex_[i]) > EPSILON) return false;
  }

  return true;
}

MockView::MockView(bool verbose): pImpl_(new Impl(verbose)) { }

void MockView::drawVertex(const VecMath::Vector< 4 >&, const VecMath::Vector< 3 >&) {
  throw NotYetImplementedException("MockView::drawVertex");
}

void MockView::drawLine(const VecMath::Vector< 4 >&, const VecMath::Vector< 4 >&,
                        const VecMath::Vector< 3 >&, const VecMath::Vector< 3 >&) {
  throw NotYetImplementedException("MockView::drawLine");
}

void MockView::drawQuadrangle(const VecMath::Vector< 4 > &x0, const VecMath::Vector< 4 > &x1,
                              const VecMath::Vector< 4 > &x2, const VecMath::Vector< 4 > &x3,
                              const VecMath::Vector< 3 > &xscr0, const VecMath::Vector< 3 > &xscr1,
                              const VecMath::Vector< 3 > &xscr2, const VecMath::Vector< 3 > &xscr3) {
  if (pImpl_->verbose_) {
    std::cerr << "drawQuadrangle(" << x0 << ", " << x1 << ", " << x2 << ", " << x3 << ", \n"
              << "               " << xscr0 << ", " << xscr1 << ", " << xscr2 << ", " << xscr3 << ")" << std::endl;
  }

  add_if_not(pImpl_->drawnVertices_, xscr0);
  add_if_not(pImpl_->drawnVertices_, xscr1);
  add_if_not(pImpl_->drawnVertices_, xscr2);
  add_if_not(pImpl_->drawnVertices_, xscr3);

  add_if_not(pImpl_->originalVertices_, x0);
  add_if_not(pImpl_->originalVertices_, x1);
  add_if_not(pImpl_->originalVertices_, x2);
  add_if_not(pImpl_->originalVertices_, x3);

  add_if_not(pImpl_->drawnFaces_, Face<3>(xscr0, xscr1, xscr2, xscr3));
}

bool MockView::isVertexDrawn(const VecMath::Vector<3>& vertex) const {
  return is_in(pImpl_->drawnVertices_, vertex);
}

bool MockView::isVertexPresent(const VecMath::Vector<4>& vertex) const {
  return is_in(pImpl_->originalVertices_, vertex);
}

bool MockView::isTransformedVertexPresent(const VecMath::Vector<4>& vertex) const {
    throw NotYetImplementedException(
      "MockView::isTransformedVertexPresent("+vertex.toString()+std::string(")")
    );
}

unsigned MockView::numVerticesDrawn() const {
  return pImpl_->drawnVertices_.size();
}

template <unsigned D>
bool MockView::isFaceDrawn(const Face<D>& face) const {
  return is_in(pImpl_->drawnFaces_, face);
}

std::ostringstream o;

template <unsigned D> void printVertex(const VecMath::Vector<D> &vertex) {
  static unsigned numPrinted = 0;
  o << vertex << " ";
  if (++numPrinted % 4 == 0) o << std::endl;
}

void MockView::printVertices() const {
  std::cerr << toString();
}

std::string MockView::toString() const {
  o << "\nMockView::printVertices(): " << numVerticesDrawn() << " vertices\n"
    << "Drawn: =========================================================================\n";
  std::for_each(pImpl_->drawnVertices_.begin(), pImpl_->drawnVertices_.end(), printVertex<3>);

  o << "\nOriginal: ======================================================================\n";
  std::for_each(pImpl_->originalVertices_.begin(), pImpl_->originalVertices_.end(), printVertex<4>);
  o << "\n";
  return o.str();
}
