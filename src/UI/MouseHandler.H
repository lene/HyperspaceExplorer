#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include "4DView.H"

/**
	@author Helge Preuss <scout@hyperspace-travel.de>
*/
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
