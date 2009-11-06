///
/// C++ Implementation: ColorManager
///
/// Description:
///
///
/// \author Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#include <QMouseEvent>

#include "MouseHandler.h"
#include "Menu4D.h"

using VecMath::Vector;
using VecMath::Rotation;

C4DView::MouseHandler4D::MouseHandler4D(C4DView *_parent): parent(_parent),
    m_LeftDownPos (0,0), m_MidDownPos (0,0), m_RightDownPos (0,0),
    m_TakingSpinValues (false) {}

C4DView::MouseHandler4D::~MouseHandler4D() {}

/** Awfully long, which is UGLY, but it does not seem to make much sense to
 *  break it up, so here we go
 *
 *  Particular mouse move/button/modifier key combinations documented in the
 *  code below
 *  \param e Qt's mouse event information structure                           */
void C4DView::MouseHandler4D::mouseMoveEvent (QMouseEvent *e) {
    QPoint point = e->pos ();
    Qt::KeyboardModifiers s = e->modifiers();
    Qt::MouseButtons b = e->buttons();

    bool LeftButtonDown  = b & Qt::LeftButton,
         MidButtonDown   = b & Qt::MidButton,
         RightButtonDown = b & Qt::RightButton,
         AltPressed = s & Qt::AltModifier,
         ControlPressed = s & Qt::ControlModifier,
         ShiftPressed = s & Qt::ShiftModifier;

    bool ViewChanged = false;

    double xsize = parent->width (),
           ysize = parent->height ();


    if (xsize == 0 || ysize == 0) return;           //  pathological case better taken care of

    if (AltPressed) setTakingSpinValues(true);
    else            setTakingSpinValues(false);

    if (ControlPressed) {                           //  CONTROL pressed

        if (LeftButtonDown || MidButtonDown || RightButtonDown) {   //  CONTROL + any Button

            ViewChanged = true;                     //  mark 4D viewpoint as changed

            double size = parent->Size();           //  reference size for the translations

            //    translate x / y with LMB
            if (LeftButtonDown && !MidButtonDown && !RightButtonDown) { //  CONTROL+LMB pressed

                QPoint translate = LeftDownPos()-point; // store difference from button press position

               if (TakingSpinValues()) {    } else {    //  no translation animation (yet?)
                   setm_LeftDownPos(point);         //  reset start position for next mouse move

                    //  add x/y translation
                   parent->addT(Vector<4>(-translate.x ()*size/xsize,
                                           translate.y ()*size/ysize, 0.,0.));

                   parent->UpdateStatus ("translate x/y");
               }                //    if (TakingSpinValues)

            }                   //    if (LeftButtonDown && !MidButtonDown && !RightButtonDown)

            //    translate z / w with MMB
            if (MidButtonDown && !LeftButtonDown && !RightButtonDown) { //  CTRL + MMB pressed

                QPoint translate = MidDownPos()-point;  //  store difference from button press position

                if (TakingSpinValues()) {    } else {   //  no translation animation (yet?)
                    setm_MidDownPos(point);         //  reset start position for next mouse move

                    //  add z/w translation
                    parent->addT(Vector<4>(0.,0.,
                                           -translate.x ()*size/xsize, translate.y ()*size/ysize));

                    parent->UpdateStatus ("translate z/w");
                }               //  if (TakingSpinValues)

            }                   //  if (MidButtonDown && !LeftButtonDown && !RightButtonDown)

        }                       //    if (LeftButtonDown || MidButtonDown || RightButtonDown)

    }                           //    if (::GetKeyState (VK_CONTROL) < 0)

    if (ShiftPressed) {                             //  rotate 4D viewpoint with SHIFT pressed

        if (LeftButtonDown || MidButtonDown || RightButtonDown) {   //  SHIFT + any button

            ViewChanged = true;                     //  mark 4D viewpoint as changed

            //    rotate xy / xz with LMB
            if (LeftButtonDown && !MidButtonDown && !RightButtonDown) { //  SHIFT + LMB

                QPoint rotate = LeftDownPos()-point;    //  store difference from button press position
                ViewChanged = false;                //  takes only xy/xz values, which are
                                                    //  equivalent to z/y 3D rotation

                if (TakingSpinValues()) {
                    parent->adddR(Rotation<4>(0.,rotate.y()/xsize*2,rotate.x ()/xsize*2,0.,0.,0.));
                    parent->UpdateStatus ("taking xy/xz rotation speed");
                } else {                            //  immediate movement
                    setm_LeftDownPos(point);        //  reset start position for next mouse move
                    //  add xy (= z in 3D) and xz rotation (= y in 3D)
                    parent->addm_rot(Rotation<3>(0., -rotate.y()/ysize*180, -rotate.x()/xsize*180));

                    parent->UpdateStatus ("rotate xy/xz");
                }               //    if (TakingSpinValues)
            }                   //    if (LeftButtonDown && !MidButtonDown && !RightButtonDown)

            //    rotate xw / yz with MMB
            if (!LeftButtonDown && MidButtonDown && !RightButtonDown) { //  SHIFT + MMB

                QPoint rotate = MidDownPos()-point; //  store difference from button press position

                if (TakingSpinValues()) {
                    parent->adddR(Rotation<4>(rotate.y()/xsize*2,0.,rotate.x()/xsize*2,0.,0.,0.));
                    if (parent->getdR()[3] == 0.) ViewChanged = false;

                    parent->UpdateStatus ("taking xw / yz rotation speed");
                } else {                            //    immediate movement
                    setm_MidDownPos(point);         //    reset start position for next mouse move

                    //    add xw rotation
                    parent->addR(Rotation<4>(0.,0., -rotate.x()/xsize*180., 0.,0.,0.));
                    //  add yz  ( = x in 3D) rotation
                    parent->addm_rot(Rotation<3>(-rotate.y()/ysize*180.,0.,0.));
                    if (parent->R()[2] == 0.) ViewChanged = false;

                    parent->UpdateStatus ("rotate xw/yz");
                }               //    if (TakingSpinValues)

            }                   //    if (!LeftButtonDown && MidButtonDown && !RightButtonDown)

            //    rotate yw / zw with RMB
            if (!LeftButtonDown && !MidButtonDown && RightButtonDown) { //  SHIFT + RMB pressed

                QPoint rotate = RightDownPos()-point;   // store difference from button press position

                if (TakingSpinValues()) {
                    parent->adddR(Rotation<4>(0.,0.,0.,0.,rotate.x()/xsize*2,rotate.y()/ysize*2));
                    parent->UpdateStatus ("taking yw / zw rotation speed");
	        } else {                            //    immediate movement
                    setm_RightDownPos(point);       //    reset start position for next mouse move
                    //    add yw/zw rotation
                    parent->addR(Rotation<4>(0.,0.,0.,
                                           -rotate.x()/xsize*180, 0.,-rotate.y()/ysize*180));
                    parent->UpdateStatus ("rotate yw/zw");
                }               //    if (TakingSpinValues)

            }                   //    if (!LeftButtonDown && !MidButtonDown && RightButtonDown)

        }                       //    if (LeftButtonDown || MidButtonDown || RightButtonDown)

    }                           //    if (::GetKeyState (VK_SHIFT) < 0)

    if (ViewChanged) {                              //    4D viewpoint has changed
        parent->Transform (parent->R(), parent->T());            //    apply the 4D transformation
        parent->Redraw ();
    } else {                                        //    4D viewpoint didn't change

        if (LeftButtonDown || MidButtonDown) {      //  LMB or MMB without modifier

            double size = parent->Size();           //    reference size for the translations

            //    pan the view with MMB
            if (MidButtonDown && !LeftButtonDown) { //  MMB

                QPoint translate = MidDownPos()-point;  //  store difference from button press position

                if (TakingSpinValues()) {    } else {   //  no translation animation (yet?)
                    setm_MidDownPos(point);         //  reset start position for next mouse move
                    //    add y translation
                    parent->addm_trans(Vector<3, GLdouble>(-translate.x ()*size/xsize,
                                                            translate.y ()*size/ysize, 0.));

                    parent->UpdateStatus ("translate x/y");
                }               //    if (TakingSpinValues)

            }                   //    if (MidButtonDown && !LeftButtonDown)

            //    rotate the view with LMB
            if (LeftButtonDown && !MidButtonDown) { //  LMB

                QPoint rotate = LeftDownPos()-point;//    store difference from button press position

                if (TakingSpinValues()) {
                    parent->adddR(Rotation<4>(rotate.x ()/xsize*5, rotate.y ()/ysize*5, 0.,0.,0.,0.));
                    parent->UpdateStatus ("taking x/y rotation speed");
	        } else {                            //    immediate movement
                    setm_LeftDownPos(point);        //    reset start position for next mouse move
                    // add x/y rotation
                    parent->addm_rot(Rotation<3>(-rotate.y ()/ysize*180, -rotate.x ()/xsize*180, 0.));

                parent->UpdateStatus ("rotate x/y");
                }               //    if (TakingSpinValues)

            }                   //    if (LeftButtonDown && !MidButtonDown)

            //    zoom with LMB+RMB
            if (LeftButtonDown && MidButtonDown) {  //  LMB+RMB

                QPoint zoom = LeftDownPos()-point;  //    store difference from button press position

                if (TakingSpinValues()) {
                    parent->adddR(Rotation<4>(0.,0., zoom.x ()/xsize*10,0.,0.,0));
                    parent->UpdateStatus ("taking z rotation speed");
	        } else {                            //  immediate movement
                    setm_LeftDownPos(point);        //  reset start position for next mouse move

                    if (zoom.x () != 0) {           //  scale camera z position
                        parent->setm_trans(
                            Vector<3, GLdouble>(parent->m_trans()[0],
                                                parent->m_trans()[1],
                                                parent->m_trans()[2]*(1+zoom.x ()/xsize)));
                        parent->SetupDepthCue (parent->getFog());
                    }
                    parent->addm_rot(Rotation<3>(0.,0.,-zoom.y ()/ysize*180));    //    add z rotation

                parent->UpdateStatus ("translate/rotate z");
                }               //    if (TakingSpinValues)

            }                   //    if (LeftButtonDown && MidButtonDown)


        }                       //    if (LeftButtonDown || MidButtonDown)

    }                           //    if (ViewChanged)

    parent->paintEvent ();                             //    redraw the window
}

/** Only sets flags which buttons are down
 *  \param e Qt's mouse event information structure                           */
void C4DView::MouseHandler4D::mousePressEvent (QMouseEvent *e) {
    QPoint point = e->pos ();
    Qt::MouseButtons b = e->buttons();

    if ((b & Qt::LeftButton) != 0) {
        setm_LeftDownPos(point);
    }
    if ((b & Qt::MidButton) != 0) {
        setm_MidDownPos(point);
    }
    if ((b & Qt::RightButton) != 0) {
        setm_RightDownPos(point);
        Qt::KeyboardModifiers s = e->modifiers();
        bool AltPressed = s & Qt::AltModifier,
             ControlPressed = s & Qt::ControlModifier,
             ShiftPressed = s & Qt::ShiftModifier;
        if (b == Qt::RightButton && !(AltPressed || ControlPressed || ShiftPressed))
            parent->Menu()->exec (parent->mapToGlobal(point));
    }
}

/// If taking values for an animation, starts the animation
void C4DView::MouseHandler4D::mouseReleaseEvent (QMouseEvent *) {
    if (TakingSpinValues()) {
        parent->StartAnimation ();
        setTakingSpinValues(false);
    }

    parent->UpdateStatus ("");
}

/// Stops animation, if running, or resets transformation values to default
void C4DView::MouseHandler4D::mouseDoubleClickEvent (QMouseEvent *) {
    if (parent->Animated()) parent->StopAnimation ();
    else {
        parent->Transform();
        parent->Redraw ();                              //  implicit paintEvent ()
    }

    parent->UpdateStatus ("DoubleClick");
}
