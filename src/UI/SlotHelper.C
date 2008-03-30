//
// C++ Implementation: SlotHelper
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "SlotHelper.H"
#include "4DView.H"

/// Generalized slot. Sets C4DView::F to Function associated with this SlotHelper
void FunctionSlotHelper::slot() {
    view->F.reset(functionFactory->createFunction(view));

    view->menu->updateFunctionMenu (view->F->getFunctionName());
    view->AssignValues (view->F);
    view->Redraw ();
}

/// Generalized slot. Sets C4DView::F to Surface associated with this SlotHelper
void SurfaceSlotHelper::slot() {
    view->F.reset(surfaceFactory->createSurface(view));

    view->menu->updateFunctionMenu (view->F->getFunctionName());
    view->AssignValues (view->F);
    view->Redraw ();
}
