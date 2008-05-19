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

#include "MouseHandler.H"
#include "Menu4D.H"

C4DView::MouseHandler4D::MouseHandler4D(C4DView *_parent): parent(_parent) {}

C4DView::MouseHandler4D::~MouseHandler4D() {}

/// Mouse move event handler
/** Awfully long, which is UGLY, but it does not seem to make much sense to
 *  break it up, so here we go
 *
 *  Particular mouse move/button/modifier key combinations documented in the
 *  code below
 *  @param e Qt's mouse event information structure                           */
void C4DView::MouseHandler4D::mouseMoveEvent (QMouseEvent *e) {
    SingletonLog::Instance() << "C4DView::mouseMoveEvent ("
                << (long)e->modifiers()<<")\n";
    QPoint point = e->pos ();
    Qt::KeyboardModifiers s = e->modifiers();
    Qt::MouseButtons b = e->buttons();

    bool LeftButtonDown  = b & Qt::LeftButton,
         MidButtonDown   = b & Qt::MidButton,
         RightButtonDown = b & Qt::RightButton,
         AltPressed = s & Qt::AltModifier,
         ControlPressed = s & Qt::ControlModifier,
         ShiftPressed = s & Qt::ShiftModifier;

    SingletonLog::Instance() << (LeftButtonDown? "LMB ": "")
             << (MidButtonDown? "MMB ": "")
             << (RightButtonDown? "RMB ": "")
             << (AltPressed? "+ Alt ": "")
             << (ControlPressed? "+ Ctrl ": "")
             << (ShiftPressed? "+ Shift ": "") << "\n";

    bool ViewChanged = false;

    double xsize = parent->width (),
           ysize = parent->height ();


    if (xsize == 0 || ysize == 0) return;       //  pathological case better taken care of

    if (AltPressed) parent->setTakingSpinValues(true);
    else            parent->setTakingSpinValues(false);

    if (ControlPressed) {                                   //  CONTROL pressed

        if (LeftButtonDown || MidButtonDown || RightButtonDown) {   //  CONTROL + any Button

            ViewChanged = true;                         //  mark 4D viewpoint as changed

            double size = parent->Size();                      //  reference size for the translations

            //    translate x / y with LMB
            if (LeftButtonDown && !MidButtonDown && !RightButtonDown) { //  CONTROL+LMB pressed

                QPoint translate = parent->m_LeftDownPos()-point;  //  store difference from button press position

               if (parent->TakingSpinValues()) {    } else {      //  no translation animation (yet?)
                   parent->setm_LeftDownPos(point);               //  reset start position for next mouse move

                   parent->setTx(parent->Tx() - translate.x ()*size/xsize);     //  add x translation
                   parent->setTy(parent->Ty() + translate.y ()*size/ysize);     //  add y translation

                   parent->UpdateStatus ("translate x/y");
               }               //    if (TakingSpinValues)

            }                 //    if (LeftButtonDown && !MidButtonDown && !RightButtonDown)

            //    translate z / w with MMB
            if (MidButtonDown && !LeftButtonDown && !RightButtonDown) { //  CTRL + MMB pressed

                QPoint translate = parent->m_MidDownPos()-point;   //  store difference from button press position

                if (parent->TakingSpinValues()) {    } else {      //  no translation animation (yet?)
                    parent->setm_MidDownPos(point);                //  reset start position for next mouse move

                    parent->setTz(parent->Tz() - translate.x ()*size/xsize);     //  add z translation
                    parent->setTw(parent->Tw() + translate.y ()*size/ysize);     //  add w translation

                    parent->UpdateStatus ("translate z/w");
	        }            //  if (TakingSpinValues)

            }                //  if (MidButtonDown && !LeftButtonDown && !RightButtonDown)

        }                 //    if (LeftButtonDown || MidButtonDown || RightButtonDown)

    }                     //    if (::GetKeyState (VK_CONTROL) < 0)

    if (ShiftPressed) {                     //  rotate 4D viewpoint with SHIFT pressed

        if (LeftButtonDown || MidButtonDown || RightButtonDown) {   //  SHIFT + any button

            ViewChanged = true;                            //  mark 4D viewpoint as changed

            //    rotate xy / xz with LMB
            if (LeftButtonDown && !MidButtonDown && !RightButtonDown) { //  SHIFT + LMB

                QPoint rotate = parent->m_LeftDownPos()-point;    //  store difference from button press position
                ViewChanged = false;                    //  takes only xy/xz values, which are
                                                        //  equivalent to z/y 3D rotation

                if (parent->TakingSpinValues()) {
                    parent->setdz(parent->dz() + rotate.x ()/xsize*5);
                    parent->setdy(parent->dy() + rotate.y ()/ysize*5);
                    parent->UpdateStatus ("taking xy/xz rotation speed");
                } else {                                //  immediate movement
                    parent->setm_LeftDownPos(point);              //  reset start position for next mouse move

                    parent->setm_rotZ(parent->m_rotZ() - rotate.x ()/xsize*180);    //  add xy rotation ( = z in 3D)
                    parent->setm_rotY(parent->m_rotY() - rotate.y ()/ysize*180);    //  add xz rotation ( = y in 3D)

                    parent->UpdateStatus ("rotate xy/xz");
                }        //    if (TakingSpinValues)
            }            //    if (LeftButtonDown && !MidButtonDown && !RightButtonDown)

            //    rotate xw / yz with MMB
            if (!LeftButtonDown && MidButtonDown && !RightButtonDown) { //  SHIFT + MMB

                QPoint rotate = parent->m_MidDownPos()-point;        //  store difference from button press position

                if (parent->TakingSpinValues()) {
                    parent->setdxw(parent->dxw() + rotate.x ()/xsize*5);
                    parent->setdx(parent->dx() + rotate.y ()/ysize*5);
                    if (parent->dxw() == 0.) ViewChanged = false;

                    parent->UpdateStatus ("taking xw / yz rotation speed");
                } else {                             		//    immediate movement
                    parent->setm_MidDownPos(point);     //    reset start position for next mouse move

                    parent->setRxw(parent->Rxw() - rotate.x ()/xsize*180);            		//    add xw rotation
                    parent->setm_rotX(parent->m_rotX() - rotate.y ()/ysize*180);            		//    add yz  ( = x in 3D) rotation
                    if (parent->Rxw() == 0.) ViewChanged = false;

                    parent->UpdateStatus ("rotate xw/yz");
	        }        	//    if (TakingSpinValues)

            }          	//    if (!LeftButtonDown && MidButtonDown && !RightButtonDown)

            //    rotate yw / zw with RMB
            if (!LeftButtonDown && !MidButtonDown && RightButtonDown) {    	//  SHIFT + RMB pressed

                QPoint rotate = parent->m_RightDownPos()-point;    		//    store difference from button press position

                if (parent->TakingSpinValues()) {                    		//
                    parent->setdyw(parent->dyw() + rotate.x ()/xsize*5);
                    parent->setdzw(parent->dzw() + rotate.y ()/ysize*5);                    	//
                    parent->UpdateStatus ("taking yw / zw rotation speed");
	        } else {                                    		//    immediate movement
                    parent->setm_RightDownPos(point);                		//    reset start position for next mouse move

                    parent->setRyw(parent->Ryw() - rotate.x ()/xsize*180);            		//    add yw rotation
                    parent->setRzw(parent->Ryw() - rotate.y ()/ysize*180);            		//    add zw rotation

                    parent->UpdateStatus ("rotate yw/zw");
	        }        	//    if (TakingSpinValues)

            }            	//    if (!LeftButtonDown && !MidButtonDown && RightButtonDown)

        }                	//    if (LeftButtonDown || MidButtonDown || RightButtonDown)

    }                     	//    if (::GetKeyState (VK_SHIFT) < 0)

    if (ViewChanged) {                                    	//    4D viewpoint has changed
        SingletonLog::Instance().log("C4DView::mouseMoveEvent: View changed ()");

        parent->Transform (parent->Rxy(), parent->Rxz(), parent->Rxw(),
                           parent->Ryz(), parent->Ryw(), parent->Rzw(),
                           parent->Tx(), parent->Ty(), parent->Tz(), parent->Tw());   //    apply the 4D transformation
        parent->Redraw ();
    } else {					//    4D viewpoint didn't change

        if (LeftButtonDown || MidButtonDown) {		//  LMB or MMB without modifier

            double size = parent->Size();            	//    reference size for the translations

            //    pan the view with MMB
            if (MidButtonDown && !LeftButtonDown) {		//  MMB

                QPoint translate = parent->m_MidDownPos()-point;    		//    store difference from button press position

                if (parent->TakingSpinValues()) {    } else {        		//    no translation animation (yet?)
                    parent->setm_MidDownPos(point);                			//    reset start position for next mouse move

                    parent->setm_transX(parent->m_transX() - translate.x ()*size/xsize);    //    add x translation
                    parent->setm_transY(parent->m_transY() + translate.y ()*size/ysize);    //    add y translation

                    parent->UpdateStatus ("translate x/y");
	        }            	//    if (TakingSpinValues)

            }                	//    if (MidButtonDown && !LeftButtonDown)

            //    rotate the view with LMB
            if (LeftButtonDown && !MidButtonDown) {				//  LMB

                QPoint rotate = parent->m_LeftDownPos()-point;        		//    store difference from button press position

                if (parent->TakingSpinValues()) {                    		//
                    parent->setdx(parent->dx() + rotate.x ()/xsize*5);
                    parent->setdy(parent->dy() + rotate.y ()/ysize*5);                    	//
                    parent->UpdateStatus ("taking x/y rotation speed");
	        } else {                                    		//    immediate movement
                    parent->setm_LeftDownPos(point);                		//    reset start position for next mouse move

                    parent->setm_rotX(parent->m_rotX() - rotate.y ()/ysize*180);        		//    add x rotation
                    parent->setm_rotY(parent->m_rotY() - rotate.x ()/xsize*180);        		//    add y rotation

                parent->UpdateStatus ("rotate x/y");
	        }            	//    if (TakingSpinValues)

            }                	//    if (LeftButtonDown && !MidButtonDown)

            //    zoom with LMB+RMB
            if (LeftButtonDown && MidButtonDown) {				//  LMB+RMB

                QPoint zoom = parent->m_LeftDownPos()-point;        		//    store difference from button press position

                if (parent->TakingSpinValues()) {                    		//
                    parent->setdz(parent->dz() + zoom.x ()/xsize*10);
                    parent->UpdateStatus ("taking z rotation speed");
	        } else {                                    		//    immediate movement
                    parent->setm_LeftDownPos(point);                		//    reset start position for next mouse move

                    if (zoom.x () != 0) {
                        parent->setm_camZ(parent->m_camZ() * (1+zoom.x ()/xsize));            //      scale camera z position
                        parent->SetupDepthCue (parent->DepthCue3D());
	            }
                    parent->setm_rotZ(parent->m_rotZ() - zoom.y ()/ysize*180);        		//    add z rotation

                parent->UpdateStatus ("translate/rotate z");
	        }            	//    if (TakingSpinValues)

            }                	//    if (LeftButtonDown && MidButtonDown)


        }                   //    if (LeftButtonDown || MidButtonDown)

    }                     //    if (ViewChanged)

    parent->OnPaint ();                					//    redraw the window
}

/// Mouse button event handler
/** Only sets flags which buttons are down
 *  @param e Qt's mouse event information structure                           */
void C4DView::MouseHandler4D::mousePressEvent (QMouseEvent *e) {
    SingletonLog::Instance().log("C4DView::mousePressEvent ()");

    QPoint point = e->pos ();
    Qt::MouseButtons b = e->buttons();

    if ((b & Qt::LeftButton) != 0) {
        parent->setm_LeftDownPos(point);
    }
    if ((b & Qt::MidButton) != 0) {
        parent->setm_MidDownPos(point);
    }
    if ((b & Qt::RightButton) != 0) {
        parent->setm_RightDownPos(point);
        Qt::KeyboardModifiers s = e->modifiers();
        bool AltPressed = s & Qt::AltModifier,
             ControlPressed = s & Qt::ControlModifier,
             ShiftPressed = s & Qt::ShiftModifier;
        if (b == Qt::RightButton && !(AltPressed || ControlPressed || ShiftPressed))
            parent->Menu()->exec (parent->mapToGlobal(point));
//            XQGLWidget::mousePressEvent (e);
    }
}

/// Mouse button release event handler
/** If taking values for an animation, starts the animation
 *  @param e Qt's mouse event information structure                           */
void C4DView::MouseHandler4D::mouseReleaseEvent (QMouseEvent *) {
    SingletonLog::Instance().log("C4DView::mouseReleaseEvent ()");

//    Qt::MouseButtons b = e->buttons();

    if (parent->TakingSpinValues()) {
        parent->StartAnimation ();
        parent->setTakingSpinValues(false);
    }

    parent->UpdateStatus ("");
//    if (b == Qt::RightButton) QGLWidget::mouseReleaseEvent (e);
}

/// Double click event handler
/** Stops animation, if running, or resets transformation values to default
 *  @param e Qt's mouse event information structure                           */
void C4DView::MouseHandler4D::mouseDoubleClickEvent (QMouseEvent *) {
    SingletonLog::Instance().log("C4DView::mouseDoubleClickEvent ()");

    if (parent->Animated()) parent->StopAnimation ();
    else {
        parent->setTx(0); parent->setTy(0); parent->setTz(0); parent->setTw(0);
        parent->setRxy(0); parent->setRxz(0); parent->setRxw(0);
        parent->setRyz(0); parent->setRyw(0); parent->setRzw(0);

        parent->setm_rotX(15); parent->setm_rotY(15); parent->setm_rotZ(0);
        parent->setm_transX(0); parent->setm_transY(0);
        parent->setm_camZ(-10);

        parent->Transform (parent->Rxy(), parent->Rxz(), parent->Rxw(), parent->Ryz(),
                           parent->Ryw(), parent->Rzw(),
                           parent->Tx(), parent->Ty(), parent->Tz(), parent->Tw());
        parent->Redraw ();                                    		//    implicit OnPaint ()
    }

    parent->UpdateStatus ("DoubleClick");

//    parent->mouseDoubleClickEvent (e);
}

