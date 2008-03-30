///
/// C++ Template Implementation: TemplatedFunctionFactory, TemplatedSurfaceFactory
///
/// Description: Implementation for creatFunction() resp. createSurface()
///
/// @author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
/// \ingroup UIHelpers
///

#ifndef TEMPLATED_FUNCTION_FACTORY_IMPL_H
#define TEMPLATED_FUNCTION_FACTORY_IMPL_H

/// Factory method to create a Function object
/** The type of the created Function is supplied as template parameter to the
 *  TemplatedFunctionFactory object owning this method.                       */
template<class function>
    Function *C4DView::TemplatedFunctionFactory<function>::createFunction(
        C4DView *view) {
        return new function (
            view->Values->tmin (), view->Values->tmax (), view->Values->dt (),
            view->Values->umin (), view->Values->umax (), view->Values->du (),
            view->Values->vmin (), view->Values->vmax (), view->Values->dv ());
    }

/// Factory method to create a Surface object
/** The type of the created Surface is supplied as template parameter to the
 *  TemplatedSurfaceFactory object owning this method.                       */
template<class function>
    Surface *C4DView::TemplatedSurfaceFactory<function>::createSurface(
        C4DView *view) {
        return new function (
            view->Values->umin (), view->Values->umax (), view->Values->du (),
            view->Values->vmin (), view->Values->vmax (), view->Values->dv ());
    }

#endif
