#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include "4DView.H"

/** Inner class to C4DView which handles the mouse events
 *  @author Helge Preuss <scout@hyperspace-travel.de>
 *  \todo move all state variables concerning mouse handling from C4DView into
 *  this class and adjust the accessors accordingly
 * \todo can I get rid of parent? It's annoying to prefix every call to C4DView
 * member functions with parent->                                             */
class C4DView::MouseHandler4D {
    public:
        MouseHandler4D(C4DView *);
        ~MouseHandler4D();

        void mouseMoveEvent(QMouseEvent *);
        void mousePressEvent(QMouseEvent *);
        void mouseReleaseEvent( QMouseEvent *);
        void mouseDoubleClickEvent( QMouseEvent *);

        C4DView *parent;        ///< the C4DView containing this mouse handler

};

#endif
