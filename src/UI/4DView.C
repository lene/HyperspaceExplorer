
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:       helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)

#include <sstream>
#include <iomanip>

#include <QMouseEvent>
#include <QMainWindow>
#include <QStatusBar>

#include "4DView.H"
#include "Menu4D.H"
#include "AnimationDialogImpl.H"

#include "Globals.H"
#include "Log.H"

#include "Matrix.H"

#include "Function.H"
#include "Surface.H"
#include "ComplexFunction.H"
#include "Object.H"

using std::ostringstream;
using std::cerr;
using std::endl;
using std::ends;
using std::auto_ptr;
using std::vector;

using VecMath::Vector;
using VecMath::Matrix;

////////////////////////////////////////////////////////////////////////////////
// 	C4DView construction/destruction
////////////////////////////////////////////////////////////////////////////////

/// C4DView constructor
/** does a lot of initialization to (usually sensible)
 *  hardcoded default values, initializes the coordinate cross object (which
 *  could well be a class on its own), creates the necessary timers and menus,
 *  and finally creates a Hypercube as the default object to display
 *  @param parent	parent QWidget, defaults to NULL                      */
C4DView::C4DView(QWidget *parent):
    XQGLWidget (parent),

    ObjectList (0), CoordinateCross (0),

    Tx (0), Ty (0), Tz (0), Tw (0),
    Rxy (0), Rxz (0), Rxw (0), Ryz (0), Ryw (0), Rzw (0),

    m_rotX (15), m_rotY (15), m_rotZ (0.),
    m_transX (0), m_transY (0), m_camZ (-10.),

    m_LeftDownPos (0,0), m_MidDownPos (0,0), m_RightDownPos (0,0),

    AntiAlias (false), DisplayPolygons (false), Lighting (true),
    DepthCue3D (false), DepthCue4D (false),
    DisplayCoordinates (false),
    Animated (false), TakingSpinValues (false),

    RenderToPixmap (false), CurrentlyRendering (false),

    Values (new ValuesDialogImpl (this)),
    F(auto_ptr<Function>()),
    dxy (0), dxz (0), dxw (0), dyz (0), dyw (0), dzw (0),
    dx (0), dy (0), dz (0),
    animation_fps (50),
    CamW (-3.), ScrW (0.),
    animationMaxFrames((unsigned)-1), animationDirectory("/tmp"),
    animationPrefix("HyperspaceExplorer_Image") {

    InitCross();

    AnimationTimer = new QTimer (this);
    connect (AnimationTimer, SIGNAL(timeout()), this, SLOT(OnTimer()));

    AnimateRandomTimer = new QTimer (this);
    //  connect (AnimateRandomTimer, SIGNAL(timeout()), this, SLOT(RandomAnimation()));

    connect (Values, SIGNAL (ApplyChanges ()), this, SLOT (ApplyChanges ()));

    menu = new Menu4D(this);
    menu->addToMenuBar(Globals::Instance().getMainWindow()->menuBar());

    show ();

    ObjectHypercube ();

    Light ();

}

/// C4DView destructor
C4DView::~C4DView() { }

/// Initialize the structures to display a four-dimensional coordinate cross
void C4DView::InitCross() {
    Cross = vector<vector<Vector<4> > > (4);
    CrossTrans = vector<vector<Vector<4> > > (4);
    CrossScr = vector<vector<Vector<3> > > (4);;
    for (unsigned j = 0; j < 4; j++) {
        Cross[j].resize(2);
        CrossTrans[j].resize(2);
        CrossScr[j].resize(2);
        for (unsigned k = 0; k < 2; k++) {
            //  CrossTrans[j][k] = Vector (4, 0., 0., 0., 0.);
            CrossScr[j][k] = Vector<3> (0., 0., 0.);
        }
    }
    Cross[0][0] = Vector<4>(-5., 0., 0., 0.);
    Cross[0][1] = Vector<4>( 5., 0., 0., 0.);
    Cross[1][0] = Vector<4>(0., -5., 0., 0.);
    Cross[1][1] = Vector<4>(0.,  5., 0., 0.);
    Cross[2][0] = Vector<4>(0., 0., -5., 0.);
    Cross[2][1] = Vector<4>(0., 0.,  5., 0.);
    Cross[3][0] = Vector<4>(0., 0., 0., -5.);
    Cross[3][1] = Vector<4>(0., 0., 0.,  5.);
}

/// Application of translations and rotations
/** Calls F->Transform () and transforms the coordinate cross
 *  @param thetaxy rotation around xy plane (z axis); ignored because 3D rotation takes care of it
 *  @param thetaxz rotation around xz plane (y axis); ignored because 3D rotation takes care of it
 *  @param thetaxw rotation around xw plane
 *  @param thetayz rotation around xy plane (x axis); ignored because 3D rotation takes care of it
 *  @param thetayw rotation around yw plane
 *  @param thetazw rotation around zw plane
 *  @param tx translation in x direction
 *  @param ty translation in y direction
 *  @param tz translation in z direction
 *  @param tw translation in w direction                            */
void C4DView::Transform (double thetaxy, double thetaxz, double thetaxw,
                         double thetayz, double thetayw, double thetazw,
                         double tx, double ty, double tz, double tw) {
    SingletonLog::Instance() << "C4DView::Transform ("<< thetaxy << ", "
            << thetaxz << ", " << thetaxw << ", "
            << thetayz << ", " << thetayw << ", " << thetazw << ", \n"
            << "                    "
            << tx << ", " << ty << ", " << tz << ", " << tw <<")\n";

    if (F.get())
        F->Transform (thetaxy, thetaxz, thetaxw, thetayz, thetayw, thetazw,
                      tx, ty, tz, tw);
    else return;

    Matrix<4> Rxy = Matrix<4> (0, 1, thetaxy), Rxz = Matrix<4> (0, 2, thetaxz),
              Rxw = Matrix<4> (0, 3, thetaxw), Ryz = Matrix<4> (1, 2, thetayz),
              Ryw = Matrix<4> (1, 3, thetayw), Rzw = Matrix<4> (2, 3, thetazw),
              Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw,
              Rot = Rxyz*Rxwyz*Ryzw;
    Vector<4> trans = Vector<4>(tx, ty, tz, tw);

    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 2; j++)
            CrossTrans[i][j] = (Rot*Cross[i][j])+trans;
}


/// Projects F and coordinate cross into three-space
/** */
void C4DView::Project (void) {
    if (F.get()) F->Project (ScrW, CamW, DepthCue4D);
    else return;

    if (DisplayCoordinates) {
        for (unsigned i = 0; i < 2; i++)
            for (unsigned j = 0; j < 4; j++) {
                double ProjectionFactor = (ScrW-CamW)/(CrossTrans[j][i][3]-CamW);
                for (unsigned k = 0; k < CrossScr[j][i].dimension(); k++)
                    CrossScr[j][i][k] = CrossTrans[j][i][k]*ProjectionFactor;
            }
    }
}

/// Get size of displayed area
/** @return approximate diameter of definition space                          */
double C4DView::Size () {
  return sqrt ((Values->tmax ()-Values->tmin ())*(Values->tmax ()-Values->tmin ())
              +(Values->umax ()-Values->umin ())*(Values->umax ()-Values->umin ())
              +(Values->vmax ()-Values->vmin ())*(Values->vmax ()-Values->vmin ()));
}

/// draw the coordinate cross (on screen or int GL list)                      */
/** */
void C4DView::DrawCoordinates () {
    for (unsigned j = 0; j < 4; j++) {
        switch (j) {
        case 0:
            Globals::Instance().setColor (1., 0., 0.);
            break;
        case 1:
            Globals::Instance().setColor (0., 1., 0.);
            break;
        case 2:
            Globals::Instance().setColor (0., 0., 1.);
            break;
        case 3:
            Globals::Instance().setColor (1., 0., 1.);
            break;
        }
        glBegin (GL_LINES);
            for (unsigned i = 0; i < 2; i++)
                Globals::Instance().glVertex (CrossScr[j][i]);
        glEnd ();
    }
}

/// draw the projected Object (onto screen or into GL list, as it is)
/** */
void C4DView::Draw () {
  if (DisplayCoordinates) DrawCoordinates ();

  F->Draw ();
}

/// Mouse move event handler
/** Awfully long, which is UGLY, but it does not seem to make much sense to
 *  break it up, so here we go \n
 *  Particular mouse move/button/modifier key combinations documented in the
 *  code below
 *  @param e Qt's mouse event information structure                           */
void C4DView::mouseMoveEvent (QMouseEvent *e) {
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

    double xsize = width (),
           ysize = height ();


    if (xsize == 0 || ysize == 0) return;       //  pathological case better taken care of

    if (AltPressed) TakingSpinValues = true;
    else            TakingSpinValues = false;

    if (ControlPressed) {                                   //  CONTROL pressed

        if (LeftButtonDown || MidButtonDown || RightButtonDown) {   //  CONTROL + any Button

            ViewChanged = true;                         //  mark 4D viewpoint as changed

            double size = Size ();                      //  reference size for the translations

            //    translate x / y with LMB
            if (LeftButtonDown && !MidButtonDown && !RightButtonDown) { //  CONTROL+LMB pressed

               QPoint translate = m_LeftDownPos-point;  //  store difference from button press position

               if (TakingSpinValues) {    } else {      //  no translation animation (yet?)
                   m_LeftDownPos = point;               //  reset start position for next mouse move

                   Tx -= translate.x ()*size/xsize;     //  add x translation
                   Ty += translate.y ()*size/ysize;     //  add y translation

                   UpdateStatus ("translate x/y");
               }               //    if (TakingSpinValues)

            }                 //    if (LeftButtonDown && !MidButtonDown && !RightButtonDown)

            //    translate z / w with MMB
            if (MidButtonDown && !LeftButtonDown && !RightButtonDown) { //  CTRL + MMB pressed

                QPoint translate = m_MidDownPos-point;   //  store difference from button press position

                if (TakingSpinValues) {    } else {      //  no translation animation (yet?)
                    m_MidDownPos = point;                //  reset start position for next mouse move

                    Tz -= translate.x ()*size/xsize;     //  add z translation
                    Tw += translate.y ()*size/ysize;     //  add w translation

                    UpdateStatus ("translate z/w");
	        }            //  if (TakingSpinValues)

            }                //  if (MidButtonDown && !LeftButtonDown && !RightButtonDown)

        }                 //    if (LeftButtonDown || MidButtonDown || RightButtonDown)

    }                     //    if (::GetKeyState (VK_CONTROL) < 0)

    if (ShiftPressed) {                     //  rotate 4D viewpoint with SHIFT pressed

        if (LeftButtonDown || MidButtonDown || RightButtonDown) {   //  SHIFT + any button

            ViewChanged = true;                            //  mark 4D viewpoint as changed

            //    rotate xy / xz with LMB
            if (LeftButtonDown && !MidButtonDown && !RightButtonDown) { //  SHIFT + LMB

                QPoint rotate = m_LeftDownPos-point;    //  store difference from button press position
                ViewChanged = false;                    //  takes only xy/xz values, which are
                                                        //  equivalent to z/y 3D rotation

                if (TakingSpinValues) {
                    dz += rotate.x ()/xsize*5;
                    dy += rotate.y ()/ysize*5;
                    UpdateStatus ("taking xy/xz rotation speed");
                } else {                                //  immediate movement
                    m_LeftDownPos = point;              //  reset start position for next mouse move

                    m_rotZ -= rotate.x ()/xsize*180;    //  add xy rotation ( = z in 3D)
                    m_rotY -= rotate.y ()/ysize*180;    //  add xz rotation ( = y in 3D)

                    UpdateStatus ("rotate xy/xz");
                }        //    if (TakingSpinValues)
            }            //    if (LeftButtonDown && !MidButtonDown && !RightButtonDown)

            //    rotate xw / yz with MMB
            if (!LeftButtonDown && MidButtonDown && !RightButtonDown) { //  SHIFT + MMB

                QPoint rotate = m_MidDownPos-point;        //  store difference from button press position

                if (TakingSpinValues) {
                    dxw += rotate.x ()/xsize*5;
                    dx += rotate.y ()/ysize*5;
                    if (dxw == 0.) ViewChanged = false;

                    UpdateStatus ("taking xw / yz rotation speed");
                } else {                             		//    immediate movement
                    m_MidDownPos = point;     //    reset start position for next mouse move

                    Rxw -= rotate.x ()/xsize*180;            		//    add xw rotation
                    m_rotX -= rotate.y ()/ysize*180;            		//    add yz  ( = x in 3D) rotation
                    if (Rxw == 0.) ViewChanged = false;

	            UpdateStatus ("rotate xw/yz");
	        }        	//    if (TakingSpinValues)

            }          	//    if (!LeftButtonDown && MidButtonDown && !RightButtonDown)

            //    rotate yw / zw with RMB
            if (!LeftButtonDown && !MidButtonDown && RightButtonDown) {    	//  SHIFT + RMB pressed

	        QPoint rotate = m_RightDownPos-point;    		//    store difference from button press position

	        if (TakingSpinValues) {                    		//
	            dyw += rotate.x ()/xsize*5;
	            dzw += rotate.y ()/ysize*5;                    	//
	            UpdateStatus ("taking yw / zw rotation speed");
	        } else {                                    		//    immediate movement
	            m_RightDownPos = point;                		//    reset start position for next mouse move

	            Ryw -= rotate.x ()/xsize*180;            		//    add yw rotation
	            Rzw -= rotate.y ()/ysize*180;            		//    add zw rotation

	            UpdateStatus ("rotate yw/zw");
	        }        	//    if (TakingSpinValues)

            }            	//    if (!LeftButtonDown && !MidButtonDown && RightButtonDown)

        }                	//    if (LeftButtonDown || MidButtonDown || RightButtonDown)

    }                     	//    if (::GetKeyState (VK_SHIFT) < 0)

    if (ViewChanged) {                                    	//    4D viewpoint has changed
        SingletonLog::Instance().log("C4DView::mouseMoveEvent: View changed ()");

        Transform (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw, Tx, Ty, Tz, Tw);   //    apply the 4D transformation
        Redraw ();
    } else {					//    4D viewpoint didn't change

        if (LeftButtonDown || MidButtonDown) {		//  LMB or MMB without modifier

            double size = Size ();            	//    reference size for the translations

            //    pan the view with MMB
            if (MidButtonDown && !LeftButtonDown) {		//  MMB

	        QPoint translate = m_MidDownPos-point;    		//    store difference from button press position

	        if (TakingSpinValues) {    } else {        		//    no translation animation (yet?)
	            m_MidDownPos = point;                			//    reset start position for next mouse move

	            m_transX -= translate.x ()*size/xsize; 		//    add x translation
	            m_transY += translate.y ()*size/ysize; 		//    add y translation

	            UpdateStatus ("translate x/y");
	        }            	//    if (TakingSpinValues)

            }                	//    if (MidButtonDown && !LeftButtonDown)

            //    rotate the view with LMB
            if (LeftButtonDown && !MidButtonDown) {				//  LMB

	        QPoint rotate = m_LeftDownPos-point;        		//    store difference from button press position

 	        if (TakingSpinValues) {                    		//
	            dx += rotate.x ()/xsize*5;
	            dy += rotate.y ()/ysize*5;                    	//
	            UpdateStatus ("taking x/y rotation speed");
	        } else {                                    		//    immediate movement
	            m_LeftDownPos = point;                		//    reset start position for next mouse move

	            m_rotX -= rotate.y ()/ysize*180;        		//    add x rotation
	            m_rotY -= rotate.x ()/xsize*180;        		//    add y rotation

	            UpdateStatus ("rotate x/y");
	        }            	//    if (TakingSpinValues)

            }                	//    if (LeftButtonDown && !MidButtonDown)

            //    zoom with LMB+RMB
            if (LeftButtonDown && MidButtonDown) {				//  LMB+RMB

                QPoint zoom = m_LeftDownPos-point;        		//    store difference from button press position

                if (TakingSpinValues) {                    		//
	            dz += zoom.x ()/xsize*10;
	            UpdateStatus ("taking z rotation speed");
	        } else {                                    		//    immediate movement
	            m_LeftDownPos = point;                		//    reset start position for next mouse move

                    if (zoom.x () != 0) {
                        m_camZ *= 1+zoom.x ()/xsize;            //      scale camera z position
                        SetupDepthCue (DepthCue3D);
	            }
	            m_rotZ -= zoom.y ()/ysize*180;        		//    add z rotation

	            UpdateStatus ("translate/rotate z");
	        }            	//    if (TakingSpinValues)

            }                	//    if (LeftButtonDown && MidButtonDown)


        }                   //    if (LeftButtonDown || MidButtonDown)

    }                     //    if (ViewChanged)

    OnPaint ();                					//    redraw the window
}

/// Mouse button event handler
/** Only sets flags which buttons are down
 *  @param e Qt's mouse event information structure                           */
void C4DView::mousePressEvent (QMouseEvent *e) {
    SingletonLog::Instance().log("C4DView::mousePressEvent ()");

    QPoint point = e->pos ();
    Qt::MouseButtons b = e->buttons();

    if ((b & Qt::LeftButton) != 0) {
        m_LeftDownPos = point;
    }
    if ((b & Qt::MidButton) != 0) {
        m_MidDownPos = point;
    }
    if ((b & Qt::RightButton) != 0) {
        m_RightDownPos = point;
        Qt::KeyboardModifiers s = e->modifiers();
        bool AltPressed = s & Qt::AltModifier,
             ControlPressed = s & Qt::ControlModifier,
             ShiftPressed = s & Qt::ShiftModifier;
        if (b == Qt::RightButton && !(AltPressed || ControlPressed || ShiftPressed))
            menu->exec (this->mapToGlobal(point));
//            XQGLWidget::mousePressEvent (e);
    }
}

/// Mouse button release event handler
/** If taking values for an animation, starts the animation
 *  @param e Qt's mouse event information structure                           */
void C4DView::mouseReleaseEvent ( QMouseEvent *e) {
    SingletonLog::Instance().log("C4DView::mouseReleaseEvent ()");

    Qt::MouseButtons b = e->buttons();

    if (TakingSpinValues) {
        StartAnimation ();
        TakingSpinValues = false;
    }

    UpdateStatus ("");
    if (b == Qt::RightButton) XQGLWidget::mouseReleaseEvent (e);
}

/// Double click event handler
/** Stops animation, if running, or resets transformation values to default
 *  @param e Qt's mouse event information structure                           */
void C4DView::mouseDoubleClickEvent (QMouseEvent *e) {
    SingletonLog::Instance().log("C4DView::mouseDoubleClickEvent ()");

    if (Animated) StopAnimation ();
    else {
      Tx = Ty = Tz = Tw = 0;
      Rxy = Rxz = Rxw = Ryz = Ryw = Rzw = 0;

      m_rotX = m_rotY = 15.;
      m_transX = m_transY = m_rotZ = 0.;
      m_camZ = -10.;

      Transform (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw, Tx, Ty, Tz, Tw); //    transform
      Redraw ();                                    		//    implicit OnPaint ()
    }

    UpdateStatus ("DoubleClick");

    XQGLWidget::mouseDoubleClickEvent (e);
}

/** Err well.. just that!
 *  starts AnimationTimer, too...                                             */
void C4DView::StartAnimation () {
    SingletonLog::Instance().log("C4DView::StartAnimation ()");

    Animated = true;
    animationFrame = 0;
    AnimationTimer->start (1000/animation_fps);               //  go for 50 fps

    UpdateStatus ("Double-click LMB to stop animation");
}

/** you guessed it */
void C4DView::StopAnimation () {
    SingletonLog::Instance().log("C4DView::StopAnimation ()");

    Animated = false;
    dxy = dxz = dxw = dyz = dyw = dzw = dx = dy = dz = 0.;
    AnimationTimer->stop ();
    AnimateRandomTimer->stop ();
    CurrentlyRendering = false;
}

/// Starts a random animation
/** xw/yw/zw rotation speed changes every 10 seconds
 *  @todo make hardcoded duration of rotation change frequency adjustable
 *  @todo a menu entry for this                                               */
void C4DView::RandomAnimation() {
    AnimationTimer->stop ();
    AnimateRandomTimer->stop ();

    dxw = float (rand ())/RAND_MAX;
    dyw = float (rand ())/RAND_MAX;
    dzw = float (rand ())/RAND_MAX;
    StartAnimation ();

    AnimateRandomTimer->start (10000);
}

/// Make a pixmap to to be rendered by the GL widget, and render it.
/** this is an embarrassing workaround to make rendering to files work.
 *  QGLWidget's renderPixmap() method only produces black frames. Works with
 *  QPixmap::grabWindow() instead.                                            */
QPixmap C4DView::makePixmap() {

    this->activateWindow();
    this->raise();

    QPixmap pm = QPixmap::grabWindow(this->winId());

    if ( pm.isNull() ) {
      SingletonLog::Instance() << "Failed to render Pixmap.\n";
    }

    return pm;
}


/// Timer event handler
/** Updates values if in the middle of an animation, and renders an image. \n
 *  Writes image to file too, if wanted.                                      */
void C4DView::OnTimer() {
    m_rotX += dx; m_rotY += dy; m_rotZ += dz;   //  update 3D viewpoint values

    SingletonLog::Instance() << "C4DView::OnTimer()\n"
            << "  dx = " <<  dx << "  dy = " <<  dy << "  dz = " <<  dz << "\n"
            << " dxy = " << dxy << " dxz = " << dxz << " dxw = " << dxw
            << " dyz = " << dyz << " dyw = " << dyw << " dzw = " << dzw
            << "\n";

    if (dxy != 0 || dxz != 0 || dxw != 0 ||     //  4D viewpoint animated?
        dyz != 0 || dyw != 0 || dzw != 0 ) {

        Rxy += dxy;    Rxz += dxz;    Rxw += dxw;   //  update values
        Ryz += dyz;    Ryw += dyw;    Rzw += dzw;

        Transform (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw, Tx, Ty, Tz, Tw);   // transform
        Redraw ();                                                  // implicit OnPaint()
    } else OnPaint ();                                              // explicit OnPaint()

    writeFrame();   //  if render to pixmap is selected, do it

    UpdateStatus (QString("Animation: Frame %1").arg(animationFrame)
            +(animationMaxFrames > 0 && animationMaxFrames < (unsigned)(-1)?
                QString("/%1").arg(animationMaxFrames):
                QString(""))
            +" - Double-click LMB to stop");
}

/** writes a snapshot of the current frame of an animation or interactive
 *  display to disk \n
 *  updates animationFrame                                                    */
void C4DView::writeFrame() {
    if (RenderToPixmap && (animationFrame <= animationMaxFrames)) {

        CurrentlyRendering = true;

        PreRedraw ();

        QPixmap tmpPixmap = makePixmap();

        unsigned animationCiphers = animationMaxFrames > 0?
                (unsigned)(log((double)animationMaxFrames)/log(10.))+1: 6;
        QString imageFilename =
                QString (animationDirectory+"/"+animationPrefix+"%1.png")
                .arg (animationFrame, animationCiphers)
                .replace (" ", "0");
        if (tmpPixmap.save (imageFilename, "PNG")) {
            cerr << "writing "
                    << imageFilename.toStdString() << " successful! ("
                    << (long)animationFrame << "/" << (long)animationMaxFrames
                    << ")\n";
        } else {
            SingletonLog::Instance() << "writing "
                    << imageFilename.toStdString() << " failed!\n";
        }
    }
    ++animationFrame;
}

/// display some info about current object and its transformations
/** In the status bar.
 *  Side effect: checks rotation values for overflow and resets them to the
 *  interval [-360, 360]. \todo Is this wise?
 *  @param status string to be displayed                                      */
void C4DView::UpdateStatus (QString status) {
    if (m_rotX > 360) m_rotX -= 360;
    if (m_rotX <-360) m_rotX += 360;
    if (fabs (m_rotX) < 1e-3) m_rotX = 0;
    if (m_rotY > 360) m_rotY -= 360;
    if (m_rotY <-360) m_rotY += 360;
    if (fabs (m_rotY) < 1e-3) m_rotY = 0;
    if (m_rotZ > 360) m_rotZ -= 360;
    if (m_rotZ <-360) m_rotZ += 360;
    if (fabs (m_rotZ) < 1e-3) m_rotZ = 0;
    if (Rxw > 360) Rxw -= 360;
    if (Rxw <-360) Rxw += 360;
    if (Ryw > 360) Ryw -= 360;
    if (Ryw <-360) Ryw += 360;
    if (Rzw > 360) Rzw -= 360;
    if (Rzw <-360) Rzw += 360;

    if (!status.isEmpty ()) {
        for (unsigned i = status.length (); i <= 24; i++) status = " "+status;
        status = " - "+status;
    }

    Globals::Instance().getMainWindow()->statusBar()->showMessage (ObjectName+status);

    setWindowTitle(ObjectName+status);
}

/// Switch 3D depth cue on and off
/** @param on whether to use fog                                              */
void C4DView::SetupDepthCue (bool on) {
    float size = Size ();
    DepthCue3D = on;
    if (on) {
        XQGLWidget::SetupDepthCue(fabs(m_camZ)-size/2.,
                                  fabs (m_camZ)+size/2.*Globals::Instance().SR3);
        glEnable (GL_FOG);
    }
    else glDisable (GL_FOG);
}

/// Called whenever an object or the parameters have changed
/** Changes the display on the status bar and the number and names of the
 *  parameters and grid parameters on the ValuesDialog
 *  @param F the Function object for which the ValuesDialog is changed        */
void C4DView::AssignValues (const std::auto_ptr<Function> &F) {
    QString Parameter1 = F->getParameterName(0);
    QString Parameter2 = F->getParameterName(1);
    QString Parameter3 = F->getParameterName(2);
    QString Parameter4 = F->getParameterName(3);

    if (!F->getFunctionName().isEmpty()) {
        ObjectName = F->getFunctionName();
        setWindowTitle(ObjectName);
        Values->setFunction(ObjectName);
    }

    if (dynamic_cast<Object *>(F.get())) {
        Values->gridLabel->hide();
        Values->TLabel->hide();
        Values->TSlider->hide();
        Values->TSteps->hide();
        Values->TMinLabel->hide();
        Values->TMin->hide();
        Values->TMaxLabel->hide();
        Values->TMax->hide();
        Values->ULabel->hide();
        Values->USlider->hide();
        Values->USteps->hide();
        Values->UMinLabel->hide();
        Values->UMin->hide();
        Values->UMaxLabel->hide();
        Values->UMax->hide();
        Values->VLabel->hide();
        Values->VSlider->hide();
        Values->VSteps->hide();
        Values->VMinLabel->hide();
        Values->VMin->hide();
        Values->VMaxLabel->hide();
        Values->VMax->hide();
    } else {
        Values->gridLabel->show();
        Values->TLabel->show();
        Values->TSlider->show();
        Values->TSteps->show();
        Values->TMinLabel->show();
        Values->TMin->show();
        Values->TMaxLabel->show();
        Values->TMax->show();
        Values->ULabel->show();
        Values->USlider->show();
        Values->USteps->show();
        Values->UMinLabel->show();
        Values->UMin->show();
        Values->UMaxLabel->show();
        Values->UMax->show();
        if (dynamic_cast<Surface *>(F.get())) {
            Values->VLabel->hide();
            Values->VSlider->hide();
            Values->VSteps->hide();
            Values->VMinLabel->hide();
            Values->VMin->hide();
            Values->VMaxLabel->hide();
            Values->VMax->hide();
        } else {
            Values->VLabel->show();
            Values->VSlider->show();
            Values->VSteps->show();
            Values->VMinLabel->show();
            Values->VMin->show();
            Values->VMaxLabel->show();
            Values->VMax->show();
        }
    }

    if (F->getNumParameters() == 0) Values->functionLabel->hide();
    else Values->functionLabel->show();

    if (!Parameter1.isEmpty()) {
        Values->aText (Parameter1);
        Values->A->show();
        Values->ALabel->show();
    } else {
        Values->aText ("");
        Values->A->hide();
        Values->ALabel->hide();
    }
    if (!Parameter2.isEmpty()) {
        Values->bText (Parameter2);
        Values->B->show();
        Values->BLabel->show();
    } else {
        Values->bText ("");
        Values->B->hide();
        Values->BLabel->hide();
    }
    if (!Parameter3.isEmpty()) {
        Values->cText (Parameter3);
        Values->C->show();
        Values->CLabel->show();
    } else {
        Values->cText ("");
        Values->C->hide();
        Values->CLabel->hide();
    }
    if (!Parameter4.isEmpty()) {
        Values->dText (Parameter4);
        Values->D->show();
        Values->DLabel->show();
    } else {
        Values->dText ("");
        Values->D->hide();
        Values->DLabel->hide();
    }

    Transform ();

    UpdateStatus("");
}

/// Called whenever an object or the parameters have changed
/** Sets the parameters, applies the changed parameters to the function object
 *  and redraws it                                                            */
void C4DView::ApplyChanges (void) {
    F->SetParameters (Values->a (), Values->b (), Values->c (), Values->d ());

    SingletonLog::Instance() << "C4DView::ApplyChanges ():\n"
          << "Parameter A: " << Values->a () << "\t"
          << "Parameter B: " << Values->b () << "\n"
          << "Parameter C: " << Values->c () << "\t"
          << "Parameter D: " << Values->d () << "\n"
          << "Tmin: " << Values->tmin () << "\t"
          << "Tmax: " << Values->tmax () << "\t"
          << "dT  : " << Values->dt () << "\n"
          << "Umin: " << Values->umin () << "\t"
          << "Umax: " << Values->umax () << "\t"
          << "dU  : " << Values->du () << "\n"
          << "Vmin: " << Values->vmin () << "\t"
          << "Vmax: " << Values->vmax () << "\t"
          << "dV  : " << Values->dv () << "\n";

    F->ReInit (Values->tmin (), Values->tmax (), Values->dt (),
               Values->umin (), Values->umax (), Values->du (),
               Values->vmin (), Values->vmax (), Values->dv ());

    Transform ();
    Redraw ();
}

/** called whenever an object or the parameters have changed; this is the most
 *  generalized version, which is great, but sadly it doesn't exist  yet      */
void C4DView::ParametersChanged(double, double, unsigned,
                                double, double, unsigned,
                                double, double, unsigned,
                                double a, double b, double c, double d,
                                QString &) {
    F->SetParameters(a, b, c, d);
//    QMessageBox::information (this, "C4DView::ParametersChanged",
//                              "... is not yet implemented");
}


////////////////////////////////////////////////////////////////////////////////
//
//    from here on it gets pretty boring OpenGL management stuff
//
/// 4D projection stuff
/** Separated from the 3D OpenGL handling into this function                  */
void C4DView::PreRedraw () {
    SingletonLog::Instance().log("C4DView::PreRedraw ()");

    // this does seem very ineffective to me, deleting and reassigning the GL Lists,
    // but it does not seem to work any other way...?

    if (DisplayCoordinates) {
        if (CoordinateCross) glDeleteLists (CoordinateCross,1);
        CoordinateCross = Globals::Instance().GetGLList ();
        glNewList (CoordinateCross, GL_COMPILE);
        DrawCoordinates ();
        glEndList ();
    }

    if (ObjectList) glDeleteLists (ObjectList,1);
    ObjectList = Globals::Instance().GetGLList ();
    glNewList (ObjectList, GL_COMPILE_AND_EXECUTE);
        /*
        glBegin (GL_POINTS);
            setColor (0., 0., 0.);
            for (unsigned i = 0; i < 160; i++) glVertex3d (0., 0., i/100.);
        glEnd ();
        */
        Project ();
        Draw ();

    glEndList ();

    SingletonLog::Instance().log("C4DView::PreRedraw () done");
}

/// Redraw handler
void C4DView::Redraw () {
  PreRedraw ();
  OnPaint ();
}

/// Wrapper for redraw handler
/** With an error reporting routine and exit strategy */
void C4DView::RenderScene (unsigned /* Frame */) {  //  draw (frame of animation)
    usleep (16000);
    while (!glIsList (ObjectList)) {
#       ifdef DEBUG
            switch (
                QMessageBox::warning (
                    NULL, "C4DView::RenderScene",
                    ("ObjectList No. "+Globals::Instance().itoa (ObjectList)+
                     " is not a GL list!").c_str (),
                    "Retry", "Die", 0, 0, 1)) {
                case 0: PreRedraw ();
                        break;
                case 1: exit (1);
                        break;
            }
            sleep (1);
#       else
            cerr << "C4DView::RenderScene ():  "
                 << "ObjectList No. " << Globals::Instance().itoa(ObjectList)
                 << " is not a GL list!" << endl;
            sleep (1);
            PreRedraw ();
#       endif
    }

    glCallList (ObjectList);                                //  draw the object
    if (DisplayCoordinates) glCallList (CoordinateCross);
}

/// Should be called whenever the object is rotated or translated
/** */
void C4DView::OnPaint() {                           //  object drawing routine
    SingletonLog::Instance().log("C4DView::OnPaint ()");

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //  clear the window

    if (DisplayPolygons)                            //  this might move to a special
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //  routine "SwitchWireframe ()"
    else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPushMatrix();                                 //  save transformation Matrix
    // glTranslated(0.0, /*Size ()*.75*/0., 0);     //  set the camera position

    glTranslated (m_transX, m_transY, m_camZ);      //  apply object translation
    glRotated(m_rotX, 1.0, 0.0, 0.0);               //   -"-    -"-     rotation
    glRotated(m_rotY, 0.0, 1.0, 0.0);
    glRotated(m_rotZ, 0.0, 0.0, 1.0);

    RenderScene (0);                                //  draw current frame

    glPopMatrix();                                  //  restore transformation Matrix

    swapBuffers ();                                 //  swap the buffers

    writeFrame();
}

/// Resizing routine
/** Also, the definition of the GL viewport is done here                      */
void C4DView::resizeEvent (QResizeEvent *e) {
    unsigned cx = e->size ().width (),
             cy = e->size ().height ();
    if (cx == 0 && cy == 0) return;             //  zero size window taken care of

    XQGLWidget::resizeEvent (e);                //  window resizing

    GLsizei width = cx, height = cy;
    GLdouble aspect = GLdouble (width > 0? width: 1);   //  calculate aspect ratio
    if (height != 0) aspect /= GLdouble (height);

    glViewport (0, 0, width, height);           //  define the viewport
    glMatrixMode (GL_PROJECTION);               //  perspective view
    glLoadIdentity ();                          //  reset any transforms
    gluPerspective (45, aspect,                 //  set FOV, aspect,
                    .01*Size (),                //  front clipping plane
                    100.*Size ());              //  & back clipping plane

    glMatrixMode (GL_MODELVIEW);                //  return to model view
    glLoadIdentity ();                          //  reset

    glDrawBuffer (GL_BACK);                     //  dump the buffer
}

/** paintEvent() */
void C4DView::paintEvent (QPaintEvent *) {
  OnPaint ();
}

/// OpenGL initialization
/** Now this is not as boring as it seems, because further work has to be done
 *  here: \n
 *  \todo trying to check for rendering to file, but this doesn't work yet.
 *
 *  the rest of interesting inits is done in XQGLWidget::initializeGL (), btw.*/
void C4DView::initializeGL (void) {

    SingletonLog::Instance().log("C4DView::initializeGL ()");
    XQGLWidget::initializeGL ();

    glDisable (GL_CULL_FACE);                           //  disable face culling

    float *background = Globals::Instance().BackgroundColor();
    //  set background color
    glClearColor (background[0], background[1], background[2], background[3]);

    if (RenderToPixmap /* && CurrentlyRendering */ ) {
        SingletonLog::Instance().log("  render to pixmap = true");

        PreRedraw ();

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //  clear the window

        if (DisplayPolygons)                            //  this might move to a
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //  special routine "SwitchWireframe()"
        else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glPushMatrix();                                 //  save the transformation Matrix
        // glTranslated(0.0, /*Size ()*.75*/0., 0);     //  set the camera position

        glTranslated (m_transX, m_transY, m_camZ);      //  apply object translation
        glRotated(m_rotX, 1.0, 0.0, 0.0);               //   -"-    -"-     rotation
        glRotated(m_rotY, 0.0, 1.0, 0.0);
        glRotated(m_rotZ, 0.0, 0.0, 1.0);


        SingletonLog::Instance().log("  RenderScene");
        RenderScene (0);                                //  draw current frame

        glPopMatrix();                                  //  restore transformation Matrix
    }
    SingletonLog::Instance().log("C4DView::initializeGL() done");
}

/*******************************************************************************
 *  menu callback functions
 */

/// Toggle fog/depth cue
/** menu callback function */
void C4DView::Fog () {
  fog = !fog;
  menu->getAction("Depth Cue")->setChecked(fog);
  InitFog ();
  repaint (); }

/// toggle object transparency
/** menu callback function */
void C4DView::Transparent () {
  transparent = !transparent;
  menu->getAction("Transparence")->setChecked(transparent);
  InitTransparence ();
  repaint (); }

/// toggle shading
/** menu callback function */
void C4DView::Shade () {
  shade = !shade;
  menu->getAction("Shading")->setChecked(shade);
  InitShade ();
  repaint (); }

/// toggle colors
/** menu callback function */
void C4DView::Colors () {
  colors = !colors;
  menu->getAction("Colors")->setChecked(colors);
  initializeGL ();
  repaint (); }

/// Switch between wireframe and solid display
/** Account for antialiasing only in wireframe mode \n
 *  Change menu items accordingly \n
 *  Menu callback function                                                    */
void C4DView::Wireframe() {
    if (DisplayPolygons) {
        menu->getAction("Wireframe")->setText("Solid");
        menu->getAction("Transparence")->setText("Line Antialiasing");
    } else {
        transparent = true;;
        Transparent ();
        menu->getAction("Wireframe")->setText("Wireframe");
        menu->getAction("Transparence")->setText("Transparence");
        glDisable (GL_CULL_FACE);
    }
    menu->getAction("Wireframe")->setChecked (DisplayPolygons);
    SetWireframe (DisplayPolygons);

    OnPaint ();
}

/// switch coordinate cross on or off
/** change menu items accordingly \n
 *  menu callback function */
void C4DView::Coordinates() {
    DisplayCoordinates = !DisplayCoordinates;
    menu->getAction("Coordinate Cross")->setChecked (DisplayCoordinates);

    Redraw ();
}

/// switch 4D depth cue on or off
/** change menu items accordingly \n
 *  menu callback function */
void C4DView::HyperFog() {
    DepthCue4D = !DepthCue4D;
    menu->getAction("4D Depth Cue")->setChecked (DepthCue4D);

    Redraw ();
}

/// switch lighting on or off
/** change menu items accordingly \n
 *  menu callback function */
void C4DView::Light() {
    Lighting = !Lighting;
    if (Lighting) {
        glEnable(GL_LIGHTING);                  //  turn on the light

        static GLfloat LightAmbient[]  = { 0.3f, 0.3f, 0.3f, 1.0f }, //  HARDCODED VALUES
                       LightDiffuse[]  = { 0.9f, 0.9f, 0.9f, 1.0f },
	               LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f },
	               LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //  light properties

        glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); // set the light properties
        glLightfv (GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
        glLightfv (GL_LIGHT0, GL_SPECULAR, LightSpecular);
        glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
        glEnable  (GL_LIGHT0);   // turn on the light
    } else {
        static GLfloat LightAmbient[]  = { 1.0f, 1.0f, 1.0f, 0.0f },
                       LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //      light properties

        glEnable  (GL_LIGHTING);
        glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); // set the light properties
        glLightfv (GL_LIGHT0, GL_DIFFUSE, LightAmbient);
        glLightfv (GL_LIGHT0, GL_SPECULAR, LightAmbient);
        glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
        glEnable  (GL_LIGHT0);    //      turn on the light
    }

    OnPaint ();
}

/// switch rendering to files on or off
/** change menu items accordingly        \n
 *  menu callback function */
void C4DView::RenderToImages() {
  RenderToPixmap = !RenderToPixmap;
  menu->getAction("Render to Images")->setChecked(RenderToPixmap);
}

/// show a dialog to adjust animation settings
/** Where to write image files and how many files to write \n
 *  menu callback function */
void C4DView::AnimationSettings() {
    AnimationDialogImpl *Dlg = new AnimationDialogImpl;
    if (Dlg->exec () == QDialog::Accepted) {
        animationMaxFrames = Dlg->getFrames();
        animationDirectory = Dlg->getDir();
        animationPrefix = Dlg->getPrefix();
        SingletonLog::Instance()
                << "animationMaxFrames: " << (long)animationMaxFrames
                << ", animationDirectory: " << animationDirectory.toStdString()
                << ", animationPrefix: "<< animationPrefix.toStdString() << "\n";
    }
}

/// run a benchmark test
/** menu callback function */
void C4DView::Benchmark() {
  ostringstream Time;

  double time_4d = Benchmark4D (360, 1., 0., 0.);

  Time << "4D viewpoint rotation: " << time_4d << " sec."
       << " (" << 360/1./time_4d << " fps)" << endl;

  float time_3d = Benchmark3D (360, 1., 0., 0.);

  Time << "3D viewpoint rotation: " << time_3d << " sec."
       << " (" << 360/1./time_3d << " fps)" << ends;

  QMessageBox::information (NULL, "Benchmark results", Time.str ().c_str ());
  UpdateStatus ();
}


/// rotate in 4D 360 degrees
double C4DView::Benchmark4D (int num_steps,
                             double step_xw, double step_yw, double step_zw,
                             bool display) {
  clock_t stime = clock ();                     //  record start time

  double Rxw = 0., Ryw = 0., Rzw = 0.;

  for (int step = 0; step < num_steps; step++) {
    Rxw += step_xw; Ryw += step_yw; Rzw += step_zw;
    Transform (0., 0. ,Rxw, 0. , Ryw, Rzw, 0., 0., 0., 0.);
    if (display) {
      Redraw ();
      UpdateStatus (QString::number ((100*step)/num_steps)+"% done");
    }
  }

  return double (clock ()-stime)/CLOCKS_PER_SEC;
}


/// rotate in 3D 360 degrees
double C4DView::Benchmark3D (int num_steps,
                             double step_x, double step_y, double step_z,
                             bool display) {
  clock_t stime = clock ();                     //  record start time

  double Rx = m_rotX, Ry = m_rotY, Rz = m_rotZ;

  for (int step = 0; step < num_steps; step++) {
    m_rotX += step_x; m_rotY += step_y; m_rotZ += step_z;
    if (display) {
      OnPaint ();
      UpdateStatus (QString::number ((100*step)/num_steps)+"% done");
    }
  }
  m_rotX = Rx; m_rotY = Ry;  m_rotZ = Rz;

  return double (clock ()-stime)/CLOCKS_PER_SEC;
}


////////////////////////////////////////////////////////////////////////////////

/// display a Fr3r object
/** menu callback function */
void C4DView::FunctionFr3r() { FunctionSlot<Fr3r>::createFunction(this); }

/// display a Hypersphere object
/** menu callback function */
void C4DView::FunctionHypersphere() { FunctionSlot<Hypersphere>::createFunction(this); }

/// display a Torus1 object
/** menu callback function */
void C4DView::FunctionTorus1() { FunctionSlot<Torus1>::createFunction(this); }

/// display a Torus2 object
/** menu callback function */
void C4DView::FunctionTorus2() { FunctionSlot<Torus2>::createFunction(this); }

///  display a Fr3r object
/** menu callback function */
void C4DView::FR3R(){ FunctionSlot<Fr3r>::createFunction(this); }

/// display a GravPotential object
/** menu callback function */
void C4DView::GravPotential(){ FunctionSlot<GravitationPotential>::createFunction(this); }

/// display a SinR object
/** menu callback function */
void C4DView::SinR(){ FunctionSlot<Fr3rSin>::createFunction(this); }

/// display a ExpR object
/** menu callback function */
void C4DView::ExpR(){ FunctionSlot<Fr3rExp>::createFunction(this); }

/// display a Sin object
/** menu callback function */
void C4DView::Sin(){ FunctionSlot<PolarSin>::createFunction(this); }

/// display a Sin2 object
/** menu callback function */
void C4DView::Sin2(){ FunctionSlot<PolarSin2>::createFunction(this); }

/// display a FunctionR object
/** menu callback function */
void C4DView::FunctionR(){ FunctionSlot<PolarR>::createFunction(this); }

/// display a ObjectHypercube object
/** menu callback function */
void C4DView::ObjectHypercube() {
    menu->updateFunctionMenu("Hypercube");

    F.reset(new Hypercube (Values->a ()));

    AssignValues(F);
    Redraw ();
}

/// display a ObjectHyperpyramid object
/** menu callback function */
void C4DView::ObjectHyperpyramid() {
    menu->updateFunctionMenu("Hyperpyramid");

    F.reset(new Pyramid (2.*Values->a ()));

    AssignValues(F);
    Redraw ();
}

/// display a ObjectHypersponge object
/** menu callback function */
void C4DView::ObjectHypersponge() {
    menu->updateFunctionMenu("Menger Sponge");

    F.reset(new Sponge (
//                unsigned (Values->a ()), int (Values->b ()), Values->c ())
                1, 2, 0.8)
    );

    AssignValues(F);
    Redraw ();
}

/// display a ObjectGasket object
/** menu callback function */
void C4DView::ObjectGasket() {
    menu->updateFunctionMenu("Sierpinski Gasket");

        F.reset(new Gasket (unsigned (Values->a ()), 2.*Values->b ()));

    AssignValues(F);
    Redraw ();
}

/// display a Surface object
/** menu callback function */
void C4DView::Surface_1() { FunctionSlot<Surface1>::createSurface(this); }

/// display a SurfaceHorizon object
/** menu callback function */
void C4DView::SurfaceHorizon() { FunctionSlot<Horizon>::createSurface(this); }

/// display a SurfaceTorus3 object
/** menu callback function */
void C4DView::SurfaceTorus3() { FunctionSlot<Torus3>::createSurface(this); }

/// display a ComplexZ2 object
/** menu callback function */
void C4DView::ComplexZ2() { FunctionSlot<z2>::createSurface(this); }

/// display a ComplexZ3 object
/** menu callback function */
void C4DView::ComplexZ3() { FunctionSlot<z3>::createSurface(this); }

/// display a ComplexZA object
/** menu callback function */
void C4DView::ComplexZA() { FunctionSlot<zA>::createSurface(this); }

/// display a ComplexEZ object
/** menu callback function */
void C4DView::ComplexEZ() { FunctionSlot<ez>::createSurface(this); }

/// display a ComplexEMZ2 object
/** menu callback function */
void C4DView::ComplexEMZ2() { FunctionSlot<emz2>::createSurface(this); }

/// display a ComplexZM1 object
/** menu callback function */
void C4DView::ComplexZM1() { FunctionSlot<zm1>::createSurface(this); }

/// display a ComplexZM2 object
/** menu callback function */
void C4DView::ComplexZM2() {FunctionSlot<zm2>::createSurface(this); }

/// display a ComplexSqrtZ object
/** menu callback function */
void C4DView::ComplexSqrtZ() {FunctionSlot<sqrtz>::createSurface(this); }

/// display a ComplexLnZ object
/** menu callback function */
void C4DView::ComplexLnZ() {FunctionSlot<lnz>::createSurface(this); }

/// display a ComplexSinZ object
/** menu callback function */
void C4DView::ComplexSinZ() {FunctionSlot<sinz>::createSurface(this); }

/// display a ComplexCosZ object
/** menu callback function */
void C4DView::ComplexCosZ() {FunctionSlot<cosz>::createSurface(this); }

/// display a ComplexSinhZ object
/** menu callback function */
void C4DView::ComplexSinhZ() {FunctionSlot<sinhz>::createSurface(this); }

/// display a ComplexCoshZ object
/** menu callback function */
void C4DView::ComplexCoshZ() {FunctionSlot<coshz>::createSurface(this); }

/// display a ComplexTanZ object
/** menu callback function */
void C4DView::ComplexTanZ() {FunctionSlot<tanz>::createSurface(this); }

/// display a customFunction object
/** menu callback function */
void C4DView::customFunction() {
    CustomFunctionSlot<CustomFunction>::createCustomFunction(this);
}

/// display a customPolarFunction object
/** menu callback function */
void C4DView::customPolarFunction() {
    CustomFunctionSlot<CustomPolarFunction>::createCustomFunction(this);
}

/// display a customComplexFunction object
/** menu callback function */
void C4DView::customComplexFunction() {
    CustomFunctionSlot<CustomComplexFunction>::createCustomSurface(this);
}

/// display a customSurface object
/** menu callback function */
void C4DView::customSurface() {
    CustomFunctionSlot<CustomSurface>::createCustomSurface(this);
}
