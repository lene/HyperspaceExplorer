
#ifndef GRID_DRAWER_IMPL_H
#define GRID_DRAWER_IMPL_H

#include "GridDrawer.h"

#include "ScopedTimer.h"
#include "Globals.h"

template <unsigned P, typename NUM, unsigned D>
GridDrawer<P, NUM, D>::GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, P > &x_scr,
                                  UI::View *view):
    _x_scr(x_scr), _view(view) { }

template <unsigned P, typename NUM, unsigned D>
void GridDrawer<P, NUM, D>::execute() {
  std::cerr << "GridDrawer<" << P << ">::execute()\n";
  for (unsigned i = 0; i < _x_scr.size(); ++i) {
    GridDrawer<P-1, NUM, D> sub_drawer(_x_scr[i], _view);
    sub_drawer.execute();
  }
}

template<typename NUM, unsigned D>
GridDrawer<3, NUM, D>::GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<4, NUM>, 3 > &x,
                                  const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, 3 > &x_scr,
                                  UI::View *view):
  x_(x), x_scr_(x_scr), view_(view) { }

template<typename NUM, unsigned D>
void GridDrawer<3, NUM, D>::execute() {
  unsigned size_t = x_scr_.size()-1;
//  ScopedTimer timer("GridDrawer<3, NUM, D>::execute() "+Util::itoa(size_t));

  for (unsigned t = 0; t < size_t; t++)
    drawPlane (t);

}

template<typename NUM, unsigned D>
void GridDrawer<3, NUM, D>::drawPlane(unsigned t) {
  unsigned size_u = x_scr_[0].size()-1;
//  ScopedTimer timer("GridDrawer<3, NUM, D>::drawPlane(" + Util::itoa(t)+ ") "+Util::itoa(size_u));
  for (unsigned u = 0; u < size_u; u++)
    drawStrip (t, u);
}

template<typename NUM, unsigned D>
void GridDrawer<3, NUM, D>::drawStrip(unsigned t, unsigned u) {
  unsigned size_v = x_scr_[0][0].size()-1;
  for (unsigned v= 0; v < size_v; v++)
    drawCube (t, u, v);
}

static VecMath::Vector<3> V[8];

template<typename NUM, unsigned D>
inline void GridDrawer<3, NUM, D>::drawCube (unsigned t, unsigned u, unsigned v) {
  /*
  V[0] = x_scr_[t][u][v];     V[1] = x_scr_[t][u][v+1];
  V[2] = x_scr_[t][u+1][v];   V[3] = x_scr_[t][u+1][v+1];
  V[4] = x_scr_[t+1][u][v];   V[5] = x_scr_[t+1][u][v+1];
  V[6] = x_scr_[t+1][u+1][v]; V[7] = x_scr_[t+1][u+1][v+1];

  view_->drawCube(x_, t, u, v,
                  V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
*/
  view_->drawCube(x_, t, u, v,
                  x_scr_[t][u][v], x_scr_[t][u][v+1], x_scr_[t][u+1][v], x_scr_[t][u+1][v+1],
                  x_scr_[t+1][u][v], x_scr_[t+1][u][v+1], x_scr_[t+1][u+1][v], x_scr_[t+1][u+1][v+1]);

}

template<typename NUM, unsigned D>
GridDrawer<1, NUM, D>::GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, 1 > &x_scr,
                                  UI::View *view):
  _x_scr(x_scr), _view(view) { }

template<typename NUM, unsigned D>
void GridDrawer<1, NUM, D>::execute() {
  std::cerr << "GridDrawer<1>::execute()\n";
  for (unsigned i = 0; i < _x_scr.size(); ++i) {

  }

}

#endif