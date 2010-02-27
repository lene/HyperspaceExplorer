#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include "4DView.h"

/// Inner class to C4DView which handles the mouse events
/** \author Lene Preuss <lene.preuss@gmail.com> */
class C4DView::MouseHandler4D {
    public:
        /// Create a MouseHandler4D for a C4DView
        MouseHandler4D(C4DView *);
        ~MouseHandler4D();

        /// Mouse move event handler
        void mouseMoveEvent(QMouseEvent *);
        /// Mouse button event handler
        void mousePressEvent(QMouseEvent *);
        /// Mouse button release event handler
        void mouseReleaseEvent( QMouseEvent *);
        /// Double click event handler
        void mouseDoubleClickEvent( QMouseEvent *);

    private:
        /// \param b position where the LMB press started
        void setm_LeftDownPos(QPoint b) { m_LeftDownPos = b; }
        /// \return position where the LMB press started
        QPoint LeftDownPos() const { return m_LeftDownPos; }
        /// \param b position where the MMB press started
        void setm_MidDownPos(QPoint b) { m_MidDownPos = b; }
        /// \return position where the MMB press started
        QPoint MidDownPos() const { return m_MidDownPos; }
        /// \param b position where the RMB press started
        void setm_RightDownPos(QPoint b) { m_RightDownPos = b; }
        /// \return position where the RMB press started
        QPoint RightDownPos() const { return m_RightDownPos; }

        /// Set whether mouse button pressed & mouse moved to take movement speed
        void setTakingSpinValues(bool b) { m_TakingSpinValues = b; }
        /// \return Mouse button pressed & mouse moved to take movement speed?
        bool TakingSpinValues() const { return m_TakingSpinValues; }

        C4DView *parent;        ///< the C4DView containing this mouse handler

        QPoint m_LeftDownPos;       ///< position where the LMB press started
        QPoint m_MidDownPos;        ///< position where the MMB press started
        QPoint m_RightDownPos;      ///< position where the RMB press started

        /// true while mouse button pressed & mouse moved to take movement speed
        bool m_TakingSpinValues;

};

#endif
