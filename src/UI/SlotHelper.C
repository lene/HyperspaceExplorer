//
// C++ Implementation: SlotHelper
//
// Description:
//
//
// Author: Helge Preuss <lene.preuss@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "Menu4D.h"

#include "SlotHelper.h"
#include "4DView.h"

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
