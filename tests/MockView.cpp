#include "MockView.h"

#include "NestedVector.h"

using std::vector;
using VecMath::Vector;

struct MockView::Impl {
  Impl(bool verbose): verbose_(verbose), drawnVertices_() { }

  bool verbose_;
  vector< Vector<4> > originalVertices_;
  vector< Vector<3> > drawnVertices_;

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
    if ((element-*i).sqnorm() < EPSILON) return true;
  }
  return false;
}

template <class COLL, class ELEM>
void add_if_not(COLL &collection, const ELEM &element) {
  if (!is_in(collection, element)) {
    collection.push_back(element);
  }
}

MockView::MockView(bool verbose): pImpl_(new Impl(verbose)) { }

void MockView::drawVertex(const VecMath::Vector< 4 >&, const VecMath::Vector< 3 >&) {
  throw NotYetImplementedException("MockView::drawVertex");
}

void MockView::drawLine(const VecMath::Vector< 4 >&, const VecMath::Vector< 4 >&, 
                        const VecMath::Vector< 3 >&, const VecMath::Vector< 3 >&) {
  throw NotYetImplementedException("MockView::drawLine");
}

void MockView::drawQuadrangle(const VecMath::Vector< 4 >&, const VecMath::Vector< 4 >&, 
                              const VecMath::Vector< 4 >&, const VecMath::Vector< 4 >&, 
                              const VecMath::Vector< 3 >&, const VecMath::Vector< 3 >&, 
                              const VecMath::Vector< 3 >&, const VecMath::Vector< 3 >&) {
  throw NotYetImplementedException("MockView::drawQuadrangle");
}

void MockView::drawCube(const VecMath::NestedVector< VecMath::Vector<4>, 3 > &X,
                        unsigned t, unsigned u, unsigned v,
                        const VecMath::Vector< 3 >& v0, const VecMath::Vector< 3 >& v1,
                        const VecMath::Vector< 3 >& v2, const VecMath::Vector< 3 >& v3,
                        const VecMath::Vector< 3 >& v4, const VecMath::Vector< 3 >& v5,
                        const VecMath::Vector< 3 >& v6, const VecMath::Vector< 3 >& v7) {
  if (pImpl_->verbose_) {
    std::cerr << "drawCube(" << v0 << ", " << v1 << ", " << v2 << ", " << v3 << ", "
                             << v4 << ", " << v5 << ", " << v6 << ", " << v7 << ")" << std::endl;
  }

  add_if_not(pImpl_->drawnVertices_, v0);
  add_if_not(pImpl_->drawnVertices_, v1);
  add_if_not(pImpl_->drawnVertices_, v2);
  add_if_not(pImpl_->drawnVertices_, v3);
  add_if_not(pImpl_->drawnVertices_, v4);
  add_if_not(pImpl_->drawnVertices_, v5);
  add_if_not(pImpl_->drawnVertices_, v6);
  add_if_not(pImpl_->drawnVertices_, v7);

  add_if_not(pImpl_->originalVertices_, X[t][u][v]);
  add_if_not(pImpl_->originalVertices_, X[t][u][v+1]);
  add_if_not(pImpl_->originalVertices_, X[t][u+1][v]);
  add_if_not(pImpl_->originalVertices_, X[t][u+1][v+1]);
  add_if_not(pImpl_->originalVertices_, X[t+1][u][v]);
  add_if_not(pImpl_->originalVertices_, X[t+1][u][v+1]);
  add_if_not(pImpl_->originalVertices_, X[t+1][u+1][v]);
  add_if_not(pImpl_->originalVertices_, X[t+1][u+1][v+1]);
}

bool MockView::isVertexDrawn(const VecMath::Vector<3>& vertex) const {
  return is_in(pImpl_->drawnVertices_, vertex);
}

bool MockView::isVertexPresent(const VecMath::Vector<4>& vertex) const {
  return is_in(pImpl_->originalVertices_, vertex);
}

unsigned MockView::numVerticesDrawn() const {
  return pImpl_->drawnVertices_.size();
}


template <unsigned D> void printVertex(const VecMath::Vector<D> &vertex) {
  std::cerr << vertex << " ";
}

void MockView::printVertices() const {
  std::cerr << "MockView::printVertices(): " << numVerticesDrawn() << " vertices\n";
  std::for_each(pImpl_->drawnVertices_.begin(), pImpl_->drawnVertices_.end(), printVertex<3>);
  std::cerr << "\n";
  std::for_each(pImpl_->originalVertices_.begin(), pImpl_->originalVertices_.end(), printVertex<4>);
  std::cerr << "\n";
}


