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

#include "Menu4D.h"

#include "SlotHelper.h"
#include "4DView.h"
#include "CustomFunctionSlot.impl.h"
#include "TemplatedFunctionFactory.impl.h"

/// Generalized slot. Sets C4DView::F to Function associated with this SlotHelper
void FunctionSlotHelper::slot() {
    view->setF(functionFactory->createFunction(view));

    view->Menu()->updateFunctionMenu(view->F()->getFunctionName().c_str());
    view->AssignValues(view->F());

    view->Redraw();
}

/// Generalized slot. Sets C4DView::F to Surface associated with this SlotHelper
void SurfaceSlotHelper::slot() {
    view->setF(surfaceFactory->createSurface(view));

    view->Menu()->updateFunctionMenu(view->F()->getFunctionName().c_str());
    view->AssignValues(view->F());
    view->Redraw();
}
