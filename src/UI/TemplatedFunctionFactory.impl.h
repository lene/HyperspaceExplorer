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

#ifndef TEMPLATED_FUNCTION_FACTORY_IMPL_H
#define TEMPLATED_FUNCTION_FACTORY_IMPL_H

/// Factory method to create a Function object
/** The type of the created Function is supplied as template parameter to the
 *  TemplatedFunctionFactory object owning this method.                       */
template<class function>
    RealFunction *C4DView::TemplatedRealFunctionFactory<function>::doCreateFunction(
        C4DView *view) {
        return new function(
            view->Values()->tmin (), view->Values()->tmax (), view->Values()->dt (),
            view->Values()->umin (), view->Values()->umax (), view->Values()->du (),
            view->Values()->vmin (), view->Values()->vmax (), view->Values()->dv ());
    }

template<class function>
    std::string C4DView::TemplatedRealFunctionFactory<function>::doGetFunctionName() {
      function* f(new function());
      return f->getFunctionName();
    }

/// Factory method to create a Surface object
/** The type of the created Surface is supplied as template parameter to the
 *  TemplatedSurfaceFactory object owning this method.                       */
template<class function>
    Surface *C4DView::TemplatedSurfaceFactory<function>::doCreateSurface(
        C4DView *view) {
        return new function (
            view->Values()->umin (), view->Values()->umax (), view->Values()->du (),
            view->Values()->vmin (), view->Values()->vmax (), view->Values()->dv ());
    }

template<class function>
    std::string C4DView::TemplatedSurfaceFactory<function>::doGetFunctionName() {
      function* f(new function());
      return f->getFunctionName();
    }

#endif
