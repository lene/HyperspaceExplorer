///
/// C++ Template Implementation: TemplatedFunctionFactory, TemplatedSurfaceFactory
///
/// Description: Implementation for creatFunction() resp. createSurface()
///
/// @author: Helge Preuss <lene.preuss@gmail.com>, (C) 2008
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
    RealFunction *C4DView::TemplatedRealFunctionFactory<function>::doCreateFunction(
        C4DView *view) {
        return new function(
            view->Values()->tmin (), view->Values()->tmax (), view->Values()->dt (),
            view->Values()->umin (), view->Values()->umax (), view->Values()->du (),
            view->Values()->vmin (), view->Values()->vmax (), view->Values()->dv ());
    }

template<class function>
    QString C4DView::TemplatedRealFunctionFactory<function>::doGetFunctionName() {
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
    QString C4DView::TemplatedSurfaceFactory<function>::doGetFunctionName() {
      function* f(new function());
      return f->getFunctionName();
    }

#endif
