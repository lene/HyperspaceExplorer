/*
Hyperspace Explorer - vizualizing higher-dimensional geometry
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
(Seriously, has anyone ever done this?)

*/
#ifndef GRID_DRAWER_H
#define GRID_DRAWER_H

/// define this if you want the GridDrawer do the drawing work
//#define USE_GRID_DRAWER

#include <View.h>

/// Draws a ParametricFunction projected to 3-space.
/** This class evaluates the parametric equation represented by a ParametricFunction
 *  on points throughout its definition space and stores the values of the function
 *  at those points in a \p P dimensional grid.
 *
 *  \tparam P The dimension of the parameter vector space.
 *  \tparam NUM The numeric type managed by the grid.
 *
 *  \ingroup FunctionGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>
 */
template <unsigned P>
class GridDrawer {
  public:

    GridDrawer(const VecMath::NestedVector< VecMath::Vector<3>, P > &x_scr, UI::View *view);

    void execute();

  private:

    const VecMath::NestedVector< VecMath::Vector<3>, P > &_x_scr;
    UI::View *_view;

};


template <unsigned P>
GridDrawer<P>::GridDrawer(const VecMath::NestedVector< VecMath::Vector<3>, P > &x_scr,
                          UI::View *view):
    _x_scr(x_scr), _view(view) { }

template <unsigned P> void GridDrawer<P>::execute() {
  std::cerr << "GridDrawer<" << P << ">::execute()\n";
  for (unsigned i = 0; i < _x_scr.size(); ++i) {
    GridDrawer<P-1> sub_drawer(_x_scr[i], _view);
    sub_drawer.execute();
  }
}

template<> class GridDrawer<1> {
  public:

    GridDrawer(const VecMath::NestedVector< VecMath::Vector<3>, 1 > &x_scr, UI::View *view):
    _x_scr(x_scr), _view(view) { }

    void execute() {
      std::cerr << "GridDrawer<1>::execute()\n";
    }

  private:

    const VecMath::NestedVector< VecMath::Vector<3>, 1 > &_x_scr;
    UI::View *_view;

};
/*
template<> GridDrawer<1>::GridDrawer(const VecMath::NestedVector< VecMath::Vector<3>, 1 > &x_scr,
                                     UI::View *view):
  _x_scr(x_scr), _view(view) { }

template<> void GridDrawer<1>::execute() {
  std::cerr << "GridDrawer<1>::execute()\n";
}
*/

#endif