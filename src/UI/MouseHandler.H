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

    private:
        void setm_LeftDownPos(QPoint b) { m_LeftDownPos = b; }
        QPoint LeftDownPos() const { return m_LeftDownPos; }
        void setm_MidDownPos(QPoint b) { m_MidDownPos = b; }
        QPoint MidDownPos() const { return m_MidDownPos; }
        void setm_RightDownPos(QPoint b) { m_RightDownPos = b; }
        QPoint RightDownPos() const { return m_RightDownPos; }
        void setTakingSpinValues(bool b) { m_TakingSpinValues = b; }
        bool TakingSpinValues() const { return m_TakingSpinValues; }

        C4DView *parent;        ///< the C4DView containing this mouse handler

        QPoint m_LeftDownPos,       ///< position where the LMB press started
               m_MidDownPos,        ///< position where the MMB press started
               m_RightDownPos;      ///< position where the RMB press started
        /// true while mouse button pressed & mouse moved to take movement speed
        bool m_TakingSpinValues;

};

#endif
