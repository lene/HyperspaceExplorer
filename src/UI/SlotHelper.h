///
/// C++ Interface: SlotHelper
///
/// Description:
///
///
/// @author: Lene Preuss <lene.preuss@gmail.com>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
/// \ingroup UIHelpers
///

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
