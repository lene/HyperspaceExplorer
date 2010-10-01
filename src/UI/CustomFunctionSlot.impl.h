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

/// \ingroup UIHelpers

#ifndef CUSTOM_FUNCTION_SLOT_IMPL_H
#define CUSTOM_FUNCTION_SLOT_IMPL_H

#include "CustomFunction.h"

    /// Factory method to create a new customized Function of type R^3->R
    /** This function template is called by each slot with the correct function
    *  type as template parameter.
    *
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
    *  type as template parameter.
    *
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
