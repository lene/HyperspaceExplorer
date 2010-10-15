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

#include "View.h"
#include "MultiDimensionalVector.h"

/// Draws a ParametricFunction projected to 3-space.
/** This class evaluates the parametric equation represented by a ParametricFunction
 *  on points throughout its definition space and stores the values of the function
 *  at those points in a \p P dimensional grid.
 *
 *  \tparam P The dimension of the parameter vector space.
 *  \tparam NUM The numeric type managed by the grid.
 *  \tparam D Dimension of the projected vertices - if you find a reason for
 *            \p D being anything other than 3, I'd be interested to hear it ;-)
 *
 *  \ingroup FunctionGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>
 */
template <unsigned P, typename NUM = double, unsigned D = 3>
class GridDrawer {
  public:

    GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, P > &x_scr, UI::View *view);

    void execute();

  private:

    const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, P > &_x_scr;
    UI::View *_view;

};

template<typename NUM, unsigned D> class GridDrawer<3, NUM, D> {
  public:

    GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<4, NUM>, 3 > &x,
               const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, 3 > &x_scr,
               UI::View *view);

    void execute();

  private:

    void drawPlane (unsigned t);
    void drawStrip (unsigned t, unsigned u);
    void drawCube (unsigned t, unsigned u, unsigned v);

    const VecMath::MultiDimensionalVector< VecMath::Vector<4, NUM>, 3 > &x_;
    const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, 3 > &x_scr_;
    UI::View *view_;

};

template<typename NUM, unsigned D> class GridDrawer<1, NUM, D> {
  public:

    GridDrawer(const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, 1 > &x_scr, UI::View *view);

    void execute();

  private:

    void DrawCube (unsigned t, unsigned u, unsigned v);

    const VecMath::MultiDimensionalVector< VecMath::Vector<D, NUM>, 1 > &_x_scr;
    UI::View *_view;

};

#endif