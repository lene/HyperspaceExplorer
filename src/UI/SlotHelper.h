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

#include <QObject>

#include "4DView.h"

class RealFunctionFactory;
class SurfaceFactory;

/// Single-stop slot for menu QActions generating Function objects
/** Your mission, should you choose to accept it, is to have a single function
 *  to serve as slot for all menu Actions which generate a new Function. After
 *  all, this could be done with a template.
 *
 *  In fact, it's not quite so easy and we need an indirection. Also, one
 *  function is not enough because Surface objects have a constructor different
 *  from RealFunction objects.
 *
 *  Because moc can't compile class templates, we need another class to stand
 *  between the QAction triggered by (e.g.) menu item selection and the creation
 *  of a Function object.
 *
 *  This class provides a single slot, which calls the factory method of the
 *  factory object that was passed to the SlotHelper object during construction.
 *  That factory object is of type C4DView::TemplatedFunctionFactory <Function *>.
 *
 *  This way, a single slot function can create all Function objects. The
 *  drawback is that now many SlotHelper objects exist, one for every type of
 *  Function that is present in the menus.
 *  \ingroup UIHelpers                                                        */
class FunctionSlotHelper: public QObject {
    Q_OBJECT
    public:
        FunctionSlotHelper(C4DView *_view, RealFunctionFactory *ff):
            view(_view),functionFactory(ff) {}              ///< Construction
        ~FunctionSlotHelper() { delete functionFactory; }   ///< Cleanup
    public slots:
        void slot();
    private:
        /// The C4DView which wants to instantiate Function's
        C4DView* view;
        /// The factory object creating Function's in createFunction()
        RealFunctionFactory *functionFactory;
};

/// Single-stop slot for menu QActions generating Surface objects
/** Because the constructors for classes derived from Surface differ from the
 *  c'tors for Function objects, we need a different slot() function.
 *  \see FunctionSlotHelper
 *  \ingroup UIHelpers                                                        */
class SurfaceSlotHelper: public QObject {
    Q_OBJECT
    public:
        SurfaceSlotHelper(C4DView *_view, SurfaceFactory *sf):
            view(_view), surfaceFactory(sf) {}              ///< Construction
        ~SurfaceSlotHelper() { delete surfaceFactory; }   ///< Cleanup
    public slots:
        void slot();
    private:
        /// The C4DView which wants to instantiate Surface's
        C4DView* view;
        /// The factory object creating Surface's in createSurface()
        SurfaceFactory *surfaceFactory;
};
