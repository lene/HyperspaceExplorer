
#ifndef GRID_DRAWER_IMPL_H
#define GRID_DRAWER_IMPL_H

#include "GridDrawer.h"

template <unsigned P, typename NUM, unsigned D>
GridDrawer<P, NUM, D>::GridDrawer(const VecMath::NestedVector< VecMath::Vector<D, NUM>, P > &x_scr,
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
GridDrawer<1, NUM, D>::GridDrawer(const VecMath::NestedVector< VecMath::Vector<D, NUM>, 1 > &x_scr,
                                  UI::View *view):
  _x_scr(x_scr), _view(view) { }

template<typename NUM, unsigned D>
void GridDrawer<1, NUM, D>::execute() {
  std::cerr << "GridDrawer<1>::execute()\n";
  for (unsigned i = 0; i < _x_scr.size(); ++i) {

  }

}

/// Draw the current cube or cell of the projected Function
/** \param t current t value
*  \param u current u value
*  \param v current v value                                                  */
#if false
void RealFunction::DrawCube (unsigned t, unsigned u, unsigned v) {
  /// \todo don't use a malloc'ed pointer
  static Vector<3> *V = new Vector<3> [8];

  V[0] = Xscr()[t][u][v];     V[1] = Xscr()[t][u][v+1];
  V[2] = Xscr()[t][u+1][v];   V[3] = Xscr()[t][u+1][v+1];
  V[4] = Xscr()[t+1][u][v];   V[5] = Xscr()[t+1][u][v+1];
  V[6] = Xscr()[t+1][u+1][v]; V[7] = Xscr()[t+1][u+1][v+1];

  glBegin (GL_QUAD_STRIP);
  if (t == 0) {
    setVertex(X()[t][u][v], V[0]);
    setVertex(X()[t][u][v+1], V[1]);
    addVertices(2);
  }
  setVertex(X()[t][u+1][v], V[2]);
  setVertex(X()[t][u+1][v+1], V[3]);
  setVertex(X()[t+1][u+1][v], V[6]);
  setVertex(X()[t+1][u+1][v+1], V[7]);
  setVertex(X()[t+1][u][v], V[4]);
  setVertex(X()[t+1][u][v+1], V[5]);
  addVertices(6);
  if (u == 0) {
    setVertex(X()[t][u][v], V[0]);
    setVertex(X()[t][u][v+1], V[1]);
    addVertices(2);
  }
  glEnd ();

  glBegin (GL_QUADS);
  if (v == 0) {
    setVertex(X()[t][u][v], V[0]);
    setVertex(X()[t][u+1][v], V[2]);
    setVertex(X()[t+1][u+1][v], V[6]);
    setVertex(X()[t+1][u][v], V[4]);
    addVertices(4);
  }
  setVertex(X()[t][u][v+1], V[1]);
  setVertex(X()[t][u+1][v+1], V[3]);
  setVertex(X()[t+1][u+1][v+1], V[7]);
  setVertex(X()[t+1][u][v+1], V[5]);
  addVertices(4);
  glEnd ();
}

#endif

#endif