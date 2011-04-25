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

#ifndef GRID_DRAWER_IMPL_H
#define GRID_DRAWER_IMPL_H

#undef PERFORM_TIMING

#include "GridDrawer.h"

#include "Globals.h"

#include "Vector.impl.h"

#ifdef PERFORM_TIMING
# include "ScopedTimer.h"
#endif

// template <unsigned P, typename NUM, unsigned D>
// GridDrawer<P, NUM, D>::GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, P > &x_scr,
//                                   UI::View *view):
//     _x(), _x_scr(x_scr), _view(view) { }

template <unsigned P, typename NUM, unsigned D>
GridDrawer<P, NUM, D>::GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<4, NUM>, P > &x,
				  const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, P > &x_scr,
                                  std::shared_ptr< UI::View > view):
    _x(x), _x_scr(x_scr), _view(view) { }

template <unsigned P, typename NUM, unsigned D>
void GridDrawer<P, NUM, D>::execute() {
  for (unsigned i = 0; i < _x_scr.size(); ++i) {
    GridDrawer<P-1, NUM, D> sub_drawer(_x[i], _x_scr[i], _view);
    sub_drawer.execute();
  }
  _view->commitDraw();
}

template<typename NUM, unsigned D>
GridDrawer<3, NUM, D>::GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<4, NUM>, 3 > &x,
                                  const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, 3 > &x_scr,
                                  std::shared_ptr< UI::View > view):
  x_(x), x_scr_(x_scr), view_(view) { }

template<typename NUM, unsigned D>
void GridDrawer<3, NUM, D>::execute() {
  unsigned size_t = x_scr_.size()-1;
# ifdef PERFORM_TIMING
    ScopedTimer timer("GridDrawer<3, NUM, "+Util::itoa(D)+">::execute() "+Util::itoa(size_t));
# endif

  for (unsigned t = 0; t < size_t; t++) {
    drawPlane (t);
  }

  view_->commitDraw();

}

template<typename NUM, unsigned D>
void GridDrawer<3, NUM, D>::drawPlane(unsigned t) {
  unsigned size_u = x_scr_[0].size()-1;
# ifdef PERFORM_TIMING
    ScopedTimer timer("GridDrawer<3, NUM, "+Util::itoa(D)+">::drawPlane(" + Util::itoa(t)+ ") "+Util::itoa(size_u));
# endif
  for (unsigned u = 0; u < size_u; u++)
    drawStrip (t, u);
}

template<typename NUM, unsigned D>
void GridDrawer<3, NUM, D>::drawStrip(unsigned t, unsigned u) {
  unsigned size_v = x_scr_[0][0].size()-1;
  for (unsigned v= 0; v < size_v; v++)
    drawCube (t, u, v);
}

template<typename NUM, unsigned D>
inline void GridDrawer<3, NUM, D>::drawCube (unsigned t, unsigned u, unsigned v) {
  view_->drawCube(x_, t, u, v,
                  x_scr_[t][u][v], x_scr_[t][u][v+1], x_scr_[t][u+1][v], x_scr_[t][u+1][v+1],
                  x_scr_[t+1][u][v], x_scr_[t+1][u][v+1], x_scr_[t+1][u+1][v], x_scr_[t+1][u+1][v+1]);

}


template<typename NUM, unsigned D>
GridDrawer<2, NUM, D>::GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<4, NUM>, 2 > &x,
                                  const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, 2 > &x_scr,
                                  std::shared_ptr< UI::View > view):
  x_(x), x_scr_(x_scr), view_(view) { }

template<typename NUM, unsigned D>
void GridDrawer<2, NUM, D>::execute() {
# ifdef PERFORM_TIMING
    ScopedTimer timer("GridDrawer<2, NUM, "+Util::itoa(D)+">::execute() "+Util::itoa(size_t));
# endif
  for (unsigned t = 0; t < x_scr_.size()-1; ++t) {
    drawStrip(t);
  }

}

template<typename NUM, unsigned D>
void GridDrawer<2, NUM, D>::drawStrip(unsigned t) {
  for (unsigned u = 0; u < x_scr_[0].size()-1; ++u) {
    view_->drawQuadrangle(x_[t][u], x_[t+1][u], x_[t+1][u+1], x_[t][u+1],
                          x_scr_[t][u], x_scr_[t+1][u], x_scr_[t+1][u+1], x_scr_[t][u+1]);
   }
}


template<typename NUM, unsigned D>
GridDrawer<1, NUM, D>::GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<4, NUM>, 1 > &x,
                                  const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, 1 > &x_scr,
                                  std::shared_ptr< UI::View > view):
  x_(x), x_scr_(x_scr), view_(view) { }

template<typename NUM, unsigned D>
void GridDrawer<1, NUM, D>::execute() {
# ifdef PERFORM_TIMING
    ScopedTimer timer("GridDrawer<1, NUM, "+Util::itoa(D)+">::execute() "+Util::itoa(size_t));
# endif
  for (unsigned i = 0; i < x_scr_.size(); ++i) {
    view_->drawLine(
      x_[i], x_[i+1],
      x_scr_[i], x_scr_[i+1]);
  }

}

#endif