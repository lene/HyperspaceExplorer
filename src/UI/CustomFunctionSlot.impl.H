///
/// C++ Template Implementation: CustomFunctionSlot
///
/// Description: Implementation for createCustomFunction() and
///              createCustomSurface()
///
/// @author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
/// \ingroup UIHelpers
///

#ifndef CUSTOM_FUNCTION_SLOT_IMPL_H
#define CUSTOM_FUNCTION_SLOT_IMPL_H

#include "CustomFunction.H"

/// Factory method to create a new customized Function of type R^3->R
/** This function template is called by each slot with the correct function
 *  type as template parameter. \n
 *  Sets F to the newly created Function, checks the corresponding menu item,
 *  updates the ValuesDialog and redraws. Does some error handling in case the
 *  Function could not be loaded.                                             */
template<class function>
        void C4DView::CustomFunctionSlot<function>::createCustomFunction(
                 C4DView *view) {
            function *tmp = new function (
                view->Values()->tmin (), view->Values()->tmax (), view->Values()->dt (),
                view->Values()->umin (), view->Values()->umax (), view->Values()->du (),
                view->Values()->vmin (), view->Values()->vmax (), view->Values()->dv ());
            if (tmp->isValid()) {
                    view->setF(tmp);
                    QString sym (((function *)(view->F()).get ())->symbolic());

                view->AssignValues(view->F());
                view->Redraw ();
            } else {
                delete tmp;
                view->UpdateStatus("Failed to load custom function");
            }
        }

/// Factory method to create a new customized Function of type R^2->R^4
/** This function template is called by each slot with the correct function
 *  type as template parameter. \n
 *  Sets F to the newly created Function, checks the corresponding menu item,
 *  updates the ValuesDialog and redraws. Does some error handling in case the
 *  Function could not be loaded.                                             */
template<class function>
    void C4DView::CustomFunctionSlot<function>::createCustomSurface(
                C4DView *view) {
        function *tmp = new function (
            view->Values()->tmin (), view->Values()->tmax (), view->Values()->dt (),
            view->Values()->umin (), view->Values()->umax (), view->Values()->du ());
        if (tmp->isValid()) {
            view->setF(tmp);
            QString sym (((function *)(view->F()).get ())->symbolic());

            view->AssignValues(view->F());
            view->Redraw ();
        } else {
            delete tmp;
            view->UpdateStatus("Failed to load custom function");
        }
    }

#endif
