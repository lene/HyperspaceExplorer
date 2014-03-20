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

#include <iostream>

#include "Object.h"

#include "FunctionHolder.impl.h"
#include "MultiDimensionalVector.impl.h"

using std::cerr;
using std::endl;

using VecMath::Vector;
using VecMath::Matrix;

/** generic Object constructor; only allocates necessary arrays, children must
 *  fill them in their c'tor
 *  @param vertices number of vertices
 *  @param surfaces number of surfaces                                        */
Object::Object (unsigned vertices, unsigned surfaces):
        VertexHolder<4, 1, double>(ParameterMap()),
        Surface(surfaces) {
    for (unsigned i = 0; i < surfaces; i++) Surface[i].resize(4);
}

/// Actually create the Object, this method is overridden in child classes
/** Calibrates the color manager from the vertices of the object.
 *
 *  In child classes, this method should be reimplemented to set up the arrays
 *  \p X and \p Surface. When that is finished, the reimplementation should
 *  call \code Object::Initialize() \endcode at the end of its own Initialize()
 *  routine to calibrate the color manager.
 */
void Object::Initialize() {
    calibrateColors();
}

void Object::calibrateColors() {
    for (unsigned i = 0; i < X().size(); i++) {
        ColMgrMgr::Instance().calibrateColor(
            X()[i],
            Color((X()[i][0]+1)/2, (X()[i][1]+1)/2, (X()[i][2]+1)/2,
                  .75-(X()[i][3]+1)/4));
    }
}

/// Draw the projected Object (onto screen or into GL list, as it is)
void Object::Draw(UI::View *view) {
  for (unsigned i = 0; i < Surface.size(); ++i) {
    view->drawQuadrangle(X()[Surface[i][0]], X()[Surface[i][1]], X()[Surface[i][2]], X()[Surface[i][3]],
                         Xscr()[Surface[i][0]], Xscr()[Surface[i][1]], Xscr()[Surface[i][2]], Xscr()[Surface[i][3]]);
  }
  view->commitDraw();
}

/** Reinitialize an Object. This function is called when the initialization is
 *  done outside the constructor.
 *
 *  Currently it does not differ from Initialize(). In fact, it simply calls
 *  Initialize().
 */
void Object::ReInit (double, double, double,
                     double, double, double,
                     double, double, double) {
    SingletonLog::Instance() << "Object::ReInit()\n";
    Initialize();
}

void Object::clearAndResizeX(unsigned size) {
    setX(VertexGrid<4, 1, double>(VertexGrid<4,1,double>::grid_size_type(size)));
}

void Object::setX(unsigned i, const VecMath::Vector<4,double>& x) {
    MultiDimensionalVector< Vector<4>, 1 > &values = getGridNonConst().getValuesNonConst();
    values[i] = x;
}