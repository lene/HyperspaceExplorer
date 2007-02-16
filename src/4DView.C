
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "Globals.H"
#include "4DView.H"

#include "Matrix.H"

#include <sstream>
#include <iomanip>
//#include <unistd.h>			//  usleep (), 

#include "Function.H"
#include "Surface.H"
#include "ComplexFunction.H"
#include "Object.H"

#include <qlabel.h>
#include <qimage.h>

////////////////////////////////////////////////////////////////////////////////
// 	C4DView construction/destruction
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  C4DView constructor; does a lot of initialization to (usually sensible) hard-
 *  coded default values, initializes the coordinate cross object (which could
 *  well be a class on its own), creates the necessary timers and menus, and
 *  finally creates a Hypercube as the default object to display
 *  @param parent	parent QWidget, defaults to NULL
 *  @param name		name, defaulting to ""
 */
C4DView::C4DView(QWidget *parent, const char *name): 
    XQGLWidget (parent, name),

    ObjectList (0), CoordinateCross (0),
        
    Tx (0), Ty (0), Tz (0), Tw (0), 
    Rxy (0), Rxz (0), Rxw (0), Ryz (0), Ryw (0), Rzw (0),

    m_rotX (15), m_rotY (15), m_transX (0), m_transY (0), 
    m_camZ (-10.), m_rotZ (0.),
    
    m_LeftDownPos (0,0), m_MidDownPos (0,0), m_RightDownPos (0,0), 
 
    AntiAlias (false), DisplayPolygons (false), Lighting (true),
    DepthCue3D (false), DepthCue4D (false), 
    DisplayCoordinates (false),
    Animated (false), TakingSpinValues (false),

    RenderToPixmap (false), CurrentlyRendering (false),

    Values (new ValuesDialogImpl (this)),
    F (NULL), 

    dxy (0), dxz (0), dxw (0), dyz (0), dyw (0), dzw (0), 
    dx (0), dy (0), dz (0),
    animation_fps (50),
    CamW (-3.), ScrW (0.) {

  Cross = new Vector * [4]; CrossTrans = new Vector * [4]; CrossScr = new Vector * [4];
  for (unsigned j = 0; j < 4; j++) {
    Cross[j] = new Vector [2]; CrossTrans[j] = new Vector [2]; CrossScr[j] = new Vector [2];
    for (unsigned k = 0; k < 2; k++) {
      //      CrossTrans[j][k] = Vector (4, 0., 0., 0., 0.);
      CrossScr[j][k] = Vector (4, 0., 0., 0., 0.);
    }
  }
  Cross[0][0] = Vector (4, -5., 0., 0., 0.);	Cross[0][1] = Vector (4, 5., 0., 0., 0.);
  Cross[1][0] = Vector (4, 0., -5., 0., 0.);	Cross[1][1] = Vector (4, 0., 5., 0., 0.);
  Cross[2][0] = Vector (4, 0., 0., -5., 0.);	Cross[2][1] = Vector (4, 0., 0., 5., 0.);
  Cross[3][0] = Vector (4, 0., 0., 0., -5.);	Cross[3][1] = Vector (4, 0., 0., 0., 5.);

  AnimationTimer = new QTimer (this);
  connect (AnimationTimer, SIGNAL(timeout()), this, SLOT(OnTimer()));

  AnimateRandomTimer = new QTimer (this);
  //  connect (AnimateRandomTimer, SIGNAL(timeout()), this, SLOT(RandomAnimation()));

  connect (Values, SIGNAL (ApplyChanges ()), this, SLOT (ApplyChanges ()));
  
  menu = SetupMenu ();
  //  StatusBar = new QStatusBar (this);			//  this does not work well with QGLWidgets. left out for now.

  show ();
  
    ObjectHypercube ();

  Light ();

  //  in about half of all cases the call to ObjectHypercube () above produces a mutilated
  //  object, with vertices missing and generally wrong. i don't know why. all i can say
  //  is that a second call to ObjectHypercube () always seems to give a correct result.
  //  so:
  //ObjectHypercube ();
}

/*******************************************************************************
 *  C4DView destructor; frees arrays
 */
C4DView::~C4DView() {
  for (unsigned j = 0; j < 4; j++) {
    delete [] Cross[j]; delete [] CrossTrans[j]; delete [] CrossScr[j];
  }
  delete [] Cross; delete [] CrossTrans; delete [] CrossScr;
}


/*******************************************************************************
 *  application of translations and rotations
 *  calls F->Transform () and transforms the coordinate cross
 *  @param thetaxy	rotation around xy plane (z axis); ignored because 3D rotation takes care of it
 *  @param thetaxz	rotation around xz plane (y axis); ignored because 3D rotation takes care of it
 *  @param thetaxw	rotation around xw plane
 *  @param thetayz	rotation around xy plane (x axis); ignored because 3D rotation takes care of it
 *  @param thetayw	rotation around yw plane
 *  @param thetazw	rotation around zw plane
 *  @param tx		translation in x direction
 *  @param ty		translation in y direction
 *  @param tz		translation in z direction
 *  @param tw		translation in w direction
 */
void C4DView::Transform (double thetaxy, double thetaxz, double thetaxw, double thetayz, double thetayw, double thetazw,
			 double tx, double ty, double tz, double tw) {

# ifdef USE_AUTO_PTR 
    if (F.get ()) 
# else
    if (F)
# endif
      F->Transform (thetaxy, thetaxz, thetaxw, thetayz, thetayw, thetazw, 
		    tx, ty, tz, tw);
  else return;

  matrix<4> Rxy = matrix<4> (0, 1, thetaxy), Rxz = matrix<4> (0, 2, thetaxz), Rxw = matrix<4> (0, 3, thetaxw),
            Ryz = matrix<4> (1, 2, thetayz), Ryw = matrix<4> (1, 3, thetayw), Rzw = matrix<4> (2, 3, thetazw),
            Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw,
            Rot = Rxyz*Rxwyz*Ryzw;
  Vector trans = Vector (4, tx, ty, tz, tw);

  for (unsigned i = 0; i < 4; i++)
    for (unsigned j = 0; j < 2; j++) 
      CrossTrans[i][j] = (Rot*Cross[i][j])+trans;
}


/*******************************************************************************
 *  projects F and coordinate cross into three-space
 */
void C4DView::Project (void) {
# ifdef USE_AUTO_PTR 
    if (F.get ())
# else    
    if (F)
#endif
      F->Project (ScrW, CamW, DepthCue4D);
  else return;

  if (DisplayCoordinates) {
    for (unsigned i = 0; i < 2; i++)
      for (unsigned j = 0; j < 4; j++) {
#	if 0
	cerr << "i = " << i << " j = " << j << "CrossScr[j][i]" << CrossScr[j][i] << endl;
#	endif	
	double ProjectionFactor = (ScrW-CamW)/(CrossTrans[j][i][3]-CamW);
	CrossScr[j][i] = CrossTrans[j][i]*ProjectionFactor;
      }
  }
}


/*******************************************************************************
 *  @return approximate diameter of definition space
 */
double C4DView::Size () {
  return sqrt ((Values->tmax ()-Values->tmin ())*(Values->tmax ()-Values->tmin ())
	      +(Values->umax ()-Values->umin ())*(Values->umax ()-Values->umin ())
	      +(Values->vmax ()-Values->vmin ())*(Values->vmax ()-Values->vmin ()));
}   


/*******************************************************************************
 *  draw the coordinate cross (on screen or int GL list)
 */
void C4DView::DrawCoordinates () {
  for (unsigned j = 0; j < 4; j++) {
    switch (j) {
    case 0:
      SetColor (1., 0., 0.);
      break;
    case 1:
      SetColor (0., 1., 0.);
      break;
    case 2:
      SetColor (0., 0., 1.);
      break;
    case 3:
      SetColor (1., 0., 1.);
      break;
    }
    glBegin (GL_LINES);
    for (unsigned i = 0; i < 2; i++)
      glVertex (CrossScr[j][i]);
    glEnd ();
  }
}


/*******************************************************************************
 *  draw the projected Object (onto screen or into GL list, as it is)
 */
void C4DView::Draw () {
  if (DisplayCoordinates) DrawCoordinates ();

  F->Draw ();
}


/*******************************************************************************
 *  mouse move event handler; awfully long, which is UGLY, but it does not seem
 *  to make much sense to break it up, so here we go
 *  particular mouse move/button/modifier key combinations documented below
 *  @param e	Qt's mouse event information structure
 */
void C4DView::mouseMoveEvent (QMouseEvent *e) {
  QPoint point = e->pos ();
  ButtonState s = e->stateAfter ();

  bool LeftButtonDown  = s & LeftButton,
       MidButtonDown   = s & MidButton,
       RightButtonDown = s & RightButton;

  bool ViewChanged = false;

  double xsize = width (),
         ysize = height ();
  

  if (xsize == 0 || ysize == 0) return;         		//    pathological case better taken care of

  if ((s & AltButton) != 0) TakingSpinValues = true;
  else                      TakingSpinValues = false;

  if ((s & ControlButton) != 0) {						//  CONTROL pressed
										
    if (LeftButtonDown || MidButtonDown || RightButtonDown) {			//  CONTROL + any Button

      ViewChanged = true;                                       //    mark 4D viewpoint as changed

      double size = Size ();                                    //    reference size for the translations

      //    translate x / y with LMB
      if (LeftButtonDown && !MidButtonDown && !RightButtonDown) {         //  CONTROL+LMB pressed

	QPoint translate = m_LeftDownPos-point;                 //    store difference from button press position

	if (TakingSpinValues) {    } else {                     //    no translation animation (yet?)
	  m_LeftDownPos = point;                                //    reset start position for next mouse move

	  Tx -= translate.x ()*size/xsize;                      //    add x translation
	  Ty += translate.y ()*size/ysize;                      //    add y translation

	  UpdateStatus ("translate x/y");
	}               //    if (TakingSpinValues) 

      }                 //    if (LeftButtonDown && !MidButtonDown && !RightButtonDown) 

      //    translate z / w with MMB
      if (MidButtonDown && !LeftButtonDown && !RightButtonDown) {    	//  CTRL + MMB pressed

	QPoint translate = m_MidDownPos-point;    		//    store difference from button press position
                
	if (TakingSpinValues) {    } else {        		//    no translation animation (yet?)    
	  m_MidDownPos = point;                			//    reset start position for next mouse move

	  Tz -= translate.x ()*size/xsize;        		//    add z translation
	  Tw += translate.y ()*size/ysize;        		//    add w translation
                
	  UpdateStatus ("translate z/w");
	}            	//    if (TakingSpinValues) 
	
      }                	//    if (MidButtonDown && !LeftButtonDown && !RightButtonDown) 
      
    }                 	//    if (LeftButtonDown || MidButtonDown || RightButtonDown)

  }                     //    if (::GetKeyState (VK_CONTROL) < 0)

  if ((s & ShiftButton) != 0) {                    		//    rotate 4D viewpoint with SHIFT pressed	

    if (LeftButtonDown || MidButtonDown || RightButtonDown) {		//  SHIFT + any button

      ViewChanged = true;                            		//    mark 4D viewpoint as changed

      //    rotate xy / xz with LMB
      if (LeftButtonDown && !MidButtonDown && !RightButtonDown) {		//  SHIFT + LMB
                
	QPoint rotate = m_LeftDownPos-point;        		//    store difference from button press position
        ViewChanged = false;                                    //    takes only xy/xz values, which are 
                                                                //    equivalent to z/y 3D rotation
              
	if (TakingSpinValues) {                    		//
	  dz += rotate.x ()/xsize*5; 
	  dy += rotate.y ()/ysize*5;                    	//
	  UpdateStatus ("taking xy/xz rotation speed");
	}
	else {                                    		//    immediate movement
	  m_LeftDownPos = point;                		//    reset start position for next mouse move

	  m_rotZ -= rotate.x ()/xsize*180;            		//    add xy rotation ( = z in 3D)
	  m_rotY -= rotate.y ()/ysize*180;            		//    add xz rotation ( = y in 3D)

	  UpdateStatus ("rotate xy/xz");
	}        	//    if (TakingSpinValues) 
      }            	//    if (LeftButtonDown && !MidButtonDown && !RightButtonDown) 

      //    rotate xw / yz with MMB
      if (!LeftButtonDown && MidButtonDown && !RightButtonDown) {		//  SHIFT + MMB

	QPoint rotate = m_MidDownPos-point;        		//    store difference from button press position
                
	if (TakingSpinValues) {                    		//
	  dxw += rotate.x ()/xsize*5; 
	  dx += rotate.y ()/ysize*5;                    	//
          if (dxw == 0.) ViewChanged = false;

	  UpdateStatus ("taking xw / yz rotation speed");
	}
	else {                                    		//    immediate movement
	  m_MidDownPos = point;                			//    reset start position for next mouse move
	  
	  Rxw -= rotate.x ()/xsize*180;            		//    add xw rotation
	  m_rotX -= rotate.y ()/ysize*180;            		//    add yz  ( = x in 3D) rotation
          if (Rxw == 0.) ViewChanged = false;
  
	  UpdateStatus ("rotate xw/yz");
	}        	//    if (TakingSpinValues) 

      }            	//    if (!LeftButtonDown && MidButtonDown && !RightButtonDown) 

      //    rotate yw / zw with RMB
      if (!LeftButtonDown && !MidButtonDown && RightButtonDown) {    	//  SHIFT + RMB pressed

	QPoint rotate = m_RightDownPos-point;    		//    store difference from button press position
                
	if (TakingSpinValues) {                    		//
	  dyw += rotate.x ()/xsize*5; 
	  dzw += rotate.y ()/ysize*5;                    	//
	  UpdateStatus ("taking yw / zw rotation speed");
	}
	else {                                    		//    immediate movement
	  m_RightDownPos = point;                		//    reset start position for next mouse move

	  Ryw -= rotate.x ()/xsize*180;            		//    add yw rotation
	  Rzw -= rotate.y ()/ysize*180;            		//    add zw rotation
    
	  UpdateStatus ("rotate yw/zw");
	}        	//    if (TakingSpinValues) 
	
      }            	//    if (!LeftButtonDown && !MidButtonDown && RightButtonDown) 
      
    }                	//    if (LeftButtonDown || MidButtonDown || RightButtonDown)
    
  }                    	//    if (::GetKeyState (VK_SHIFT) < 0)

  if (ViewChanged) {                                    	//    4D viewpoint has changed
    Transform (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw, Tx, Ty, Tz, Tw);   //    apply the 4D transformation
    Redraw ();
  }
  else {							//    4D viewpoint didn't change

    if (LeftButtonDown || MidButtonDown) {					//  LMB or MMB without modifier

      double size = Size ();            			//    reference size for the translations

      //    pan the view with MMB
      if (MidButtonDown && !LeftButtonDown) {				//  MMB
	
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
	}
                
	else {                                    		//    immediate movement
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
	}
	
	else {                                    		//    immediate movement
	  m_LeftDownPos = point;                		//    reset start position for next mouse move

          if (zoom.x () != 0) {
            m_camZ *= 1+zoom.x ()/xsize;              		//      scale camera z position
            SetupDepthCue (DepthCue3D);
	  }
	  m_rotZ -= zoom.y ()/ysize*180;        		//    add z rotation

	  UpdateStatus ("translate/rotate z");
	}            	//    if (TakingSpinValues) 
	
      }                	//    if (LeftButtonDown && MidButtonDown)
      
      
    }                   //    if (LeftButtonDown || MidButtonDown) 
    
  }                     //    if (ViewChanged)
  
  OnPaint ();                					//    redraw the window

  //  XQGLWidget::mouseMoveEvent (e);
}


/*******************************************************************************
 *  mouse button event handler
 *  only sets flags which buttons are down
 *  @param e	Qt's mouse event information structure
 */
void C4DView::mousePressEvent (QMouseEvent *e) {
  QPoint point = e->pos ();
  ButtonState s = e->stateAfter ();

  if ((s & LeftButton) != 0) {
    m_LeftDownPos = point;
  }
  if ((s & MidButton) != 0) {
    m_MidDownPos = point;
  }
  if ((s & RightButton) != 0) {
    m_RightDownPos = point;
    if (s == RightButton)
      XQGLWidget::mousePressEvent (e);	
  }  
}


/*******************************************************************************
 *  mouse button release event handler
 *  if taking values for an animation, starts the animation
 *  @param e	Qt's mouse event information structure
 */
void C4DView::mouseReleaseEvent ( QMouseEvent *e) {
  ButtonState s = e->stateAfter ();
  
  if (TakingSpinValues) {
    StartAnimation ();
    TakingSpinValues = false;
  }   

  UpdateStatus ("");
  if (s == RightButton)
    XQGLWidget::mouseReleaseEvent (e);				// this fucks up all the location data!

}


/*******************************************************************************
 *  double click event handler
 *  stops animation, if running, or resets transformation values to default
 *  @param e	Qt's mouse event information structure
 */
void C4DView::mouseDoubleClickEvent (QMouseEvent *e) {
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


/*******************************************************************************
 *  err well.. just that!
 *  starts AnimationTimer, too...
 */
void C4DView::StartAnimation () {
# if 0
  cerr << "C4DView::StartAnimation ()\n";
# endif

  Animated = true;
  AnimationTimer->start (1000/animation_fps);                                 //    go for 50 fps
  
  UpdateStatus ("Double-click LMB to stop animation");
}


/*******************************************************************************
 *  you guessed it
 */
void C4DView::StopAnimation () {
# if 0
  cerr << "C4DView::StopAnimation ()\n";
# endif

  Animated = false;
  dxy = dxz = dxw = dyz = dyw = dzw = dx = dy = dz = 0.;
  AnimationTimer->stop ();
  AnimateRandomTimer->stop ();
  CurrentlyRendering = false;
}


/*******************************************************************************
 *  starts a random animation, whose xw/yw/zw rotation speed changes every HARDCODED - EEEEYUARGH!
 *  10 seconds
 */
void C4DView::RandomAnimation() {
  AnimationTimer->stop ();
  AnimateRandomTimer->stop ();

  dxw = float (rand ())/RAND_MAX;
  dyw = float (rand ())/RAND_MAX; 
  dzw = float (rand ())/RAND_MAX;
  StartAnimation ();

  AnimateRandomTimer->start (10000);
}


/*******************************************************************************
 *  make a pixmap to to be rendered by the gl widget, and render it.
 *  this is an embarrassing workaround to make rendering to files work.
 *  especially embarrassing is that it doesn't work either.
 */
QPixmap C4DView::makePixmap() {
    QPixmap pm;

    // Render the pixmap, with either c1's size or the fixed size pmSz
    pm = renderPixmap();

    if ( pm.isNull() ) {
      cerr << "Failed to render Pixmap.\n";
    }
    return pm;
}


/*******************************************************************************
 *  timer event handler
 *  updates values if in the middle of an animation, and renders an image
 *  tries to write image to file too, if wanted, but fails miserably.
 */
void C4DView::OnTimer() {
  m_rotX += dx; m_rotY += dy; m_rotZ += dz;        		//    update 3D viewpoint values

# ifdef DEBUG
  cerr << "C4DView::OnTimer()\n"
       << "  dx = " <<  dx << "  dy = " <<  dy << "  dz = " <<  dz << endl
       << " dxy = " << dxy << " dxz = " << dxz << " dxw = " << dxw
       << " dyz = " << dyz << " dyw = " << dyw << " dzw = " << dzw  << endl;
# endif
  
  if (dxy != 0 || dxz != 0 || dxw != 0 ||            		//    4D viewpoint animated?
      dyz != 0 || dyw != 0 || dzw != 0 ) {

    Rxy += dxy;    Rxz += dxz;    Rxw += dxw;            	//    update values
    Ryz += dyz;    Ryw += dyw;    Rzw += dzw;

    Transform (Rxy, Rxz, Rxw, Ryz, Ryw, Rzw, Tx, Ty, Tz, Tw);   //    transform
    Redraw ();                                			//    implicit OnPaint ()
  } 	 
  else OnPaint ();                                		//    explicit OnPaint ()
  
  if (1 && RenderToPixmap) {
    CurrentlyRendering = true;
    static unsigned long frame = 0;


    PreRedraw ();
#   ifdef DEBUG
      cerr << "  C4DView::OnTimer() \n";
#   endif
    QPixmap tmpPixmap = makePixmap ();

#   ifdef DEBUG
      cerr << "    renderPixmap ("<<width ()<<", "<<height()<< ")\n";
      cerr << "    " << tmpPixmap.width () << " " << tmpPixmap.height () << endl;
#   endif

    QString imageFilename = QString ("/tmp/HyperspaceExplorer_Image.%1.png")
                                     .arg (frame++, 6)
                                     .replace (" ", "0");
    if (tmpPixmap.save (imageFilename, "PNG"))
#   ifdef DEBUG
      //      cerr << "writing " << iio.fileName () << " successful!";
      cerr << "writing " << imageFilename << " successful!\n";
#   endif
    ;
    else
#   ifdef DEBUG
      //      cerr << "writing " << iio.fileName () << " failed!";
      cerr << "writing " << imageFilename << " failed!\n";
#   endif
    ;
  }
    
  UpdateStatus ("Double-click LMB to stop animation");
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    from here on it gets pretty boring OpenGL management stuff
//
/*******************************************************************************
 *  separated the 4d projection stuff from the 3d opengl handling into this function
 */
void C4DView::PreRedraw () {
  // this does seem very ineffective to me, deleting and reassigning the GL Lists,
  // but it does not seem to work any other way...?
# ifdef DEBUG
    cerr << "  PreRedraw ()\n";
# endif
  
  if (DisplayCoordinates) {
    if (CoordinateCross) glDeleteLists (CoordinateCross,1);
    CoordinateCross = GetGLList ();
    glNewList (CoordinateCross, GL_COMPILE);
      DrawCoordinates ();
    glEndList ();
  }

  if (ObjectList) glDeleteLists (ObjectList,1); 
  ObjectList = GetGLList ();
  glNewList (ObjectList, GL_COMPILE_AND_EXECUTE);
    /*
    glBegin (GL_POINTS);
      SetColor (0., 0., 0.);
      for (unsigned i = 0; i < 160; i++) glVertex3d (0., 0., i/100.);
    glEnd ();
    */
    Project ();
    Draw (); 

  glEndList ();

# ifdef DEBUG
    cerr << "  PreRedraw () done\n";
# endif
}


/*******************************************************************************
 *  redraw handler
 */
void C4DView::Redraw () {
  PreRedraw ();
  OnPaint ();
}


/*******************************************************************************
 *  wrapper for redraw handler, with an exit strategy
 */
void C4DView::RenderScene (unsigned Frame) {			//	draw (frame of animation)
  usleep (16000);
  while (!glIsList (ObjectList)) {
#   ifdef DEBUG
      switch (QMessageBox::warning (NULL, 
				    "C4DView::RenderScene", 
				    ("ObjectList No. "+itoa (ObjectList)+
				     " is not a GL list!").c_str (),
				    "Retry", "Die", 0,
				    0, 1)) {
      case 0: PreRedraw ();
	      break;
      case 1: exit (1);
              break;
      }
      sleep (1);
#   else
      cerr << "C4DView::RenderScene ():  "
	   << "ObjectList No. " << itoa (ObjectList) <<" is not a GL list!" << endl;
      sleep (1);
      PreRedraw ();
#   endif
  }

  glCallList (ObjectList);					//	draw the object
  if (DisplayCoordinates)
    glCallList (CoordinateCross);
}


/*******************************************************************************
 *  should be called whenever the object is rotaded or translated
 */
void C4DView::OnPaint() {                                	//    object drawing routine
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);    		//    clear the window

  if (DisplayPolygons)                                	//    this might move to a special routine
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);        	//    "SwitchWireframe ()"
  else 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  glPushMatrix();                                        	//    save transformation matrix
    // glTranslated(0.0, /*Size ()*.75*/0., 0);            	//    set the camera position

  glTranslated (m_transX, m_transY, m_camZ);            	//    apply object translation
  glRotated(m_rotX, 1.0, 0.0, 0.0);                    	//     -"-    -"-     rotation
  glRotated(m_rotY, 0.0, 1.0, 0.0);
  glRotated(m_rotZ, 0.0, 0.0, 1.0);
  
  RenderScene (0);                                		//    draw current frame
  
  glPopMatrix();                                        	//    restore transformation matrix

  swapBuffers ();                            			//    swap the buffers

  if (RenderToPixmap) {
    CurrentlyRendering = true;
    static unsigned long frame = 0;

    PreRedraw ();

#ifdef DEBUG
    cerr << "  C4DView::OnPaint () \n";
# endif
    QPixmap tmpPixmap = makePixmap ();
    //    QPixmap tmpPixmap = renderPixmap (/* width (), height (), false */);
#ifdef DEBUG
    cerr << "    renderPixmap ("<<width ()<<", "<<height()<< ")\n";
    cerr << "    " << tmpPixmap.width () << " " << tmpPixmap.height () << endl;
# endif

    QString imageFilename = QString ("/tmp/HyperspaceExplorer_Image.%1.png")
                                     .arg (frame++, 6)
                                     .replace (" ", "0");
    if (tmpPixmap.save (imageFilename, "PNG"))
      //      cerr << "writing " << iio.fileName () << " successful!";
      cerr << "writing " << imageFilename << " successful!\n";
    else
      //      cerr << "writing " << iio.fileName () << " failed!";
      cerr << "writing " << imageFilename << " failed!\n";
  }
}


/*******************************************************************************
 *  resizeEvent (): 
 */
void C4DView::resizeEvent (QResizeEvent *e) {           	//    resizing routine
  unsigned cx = e->size ().width (),                    	//    also, the definition of the
           cy = e->size ().height ();                   	//    GL viewport is done here
    if (cx == 0 && cy == 0) return;                     	//    zero size window taken care of

    XQGLWidget::resizeEvent (e);                        	//    window resizing
    
    GLsizei width = cx, height = cy;
    GLdouble aspect = GLdouble (width > 0? width: 1);    	//    calculate aspect ratio
    if (height != 0) aspect /= GLdouble (height);

    glViewport (0, 0, width, height);                    	//    define the viewport
    glMatrixMode (GL_PROJECTION);                        	//    perspective view
    glLoadIdentity ();                                    	//    reset any transforms
    gluPerspective (45, aspect,                            	//    set FOV, aspect,
                    .01*Size (),                    		//  front clipping plane
                    100.*Size ());                    		//  & back clipping plane

    glMatrixMode (GL_MODELVIEW);                        	//    return to model view
    glLoadIdentity ();                                    	//    reset

    glDrawBuffer (GL_BACK);                                	//    dump the buffer
}


/*******************************************************************************
 *  paintEvent (): 
 */
void C4DView::paintEvent (QPaintEvent *e) {
  OnPaint ();
}


/*******************************************************************************
 *  OpenGL initialization
 *  now this is not as boring as it seems, because further work has to be done here:
 *  trying to check for rendering to file, but this doesn't work yet.
 *  the rest of interesting inits is done in XQGLWidget::initializeGL (), btw.
 */
void C4DView::initializeGL (void) {

# ifdef DEBUG
    cerr << "initializeGL ()\n";
# endif
  XQGLWidget::initializeGL ();
 
  glDisable (GL_CULL_FACE);                            		//    disable face culling

  float *background = ::BackgroundColor();
  glClearColor (background[0], background[1], background[2], background[3]);	//    set background color

  if (RenderToPixmap /* && CurrentlyRendering */ ) {
#   ifdef DEBUG
      cerr << "  render to pixmap = true\n";
#   endif
    PreRedraw ();

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);    		//    clear the window

    if (DisplayPolygons)                                	//    this might move to a special routine
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);        	//    "SwitchWireframe ()"
    else 
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPushMatrix();                                        	//    save the transformation matrix
    // glTranslated(0.0, /*Size ()*.75*/0., 0);            	//    set the camera position

    glTranslated (m_transX, m_transY, m_camZ);            	//    apply object translation
    glRotated(m_rotX, 1.0, 0.0, 0.0);                    	//     -"-    -"-     rotation
    glRotated(m_rotY, 0.0, 1.0, 0.0);
    glRotated(m_rotZ, 0.0, 0.0, 1.0);


#   ifdef DEBUG
      cerr << "  RenderScene ()\n";
#   endif
    RenderScene (0);                                		//    draw current frame

    glPopMatrix();                                        	//    restore transformation matrix
  }
# ifdef DEBUG
    cerr << "initializeGL () done\n";
# endif
}


/*******************************************************************************
 *  display some info about current object and its transformations, not in a 
 *  status bar, as i can't get this to work with QGLWidget, but in the title bar
 *  side effect: checks rotation values for overflow and resets them to the
 *  interval [-360, 360]. is this wise?
 *  @param status	string to be displayed
 */
void C4DView::UpdateStatus (QString status) {            	//    write a text to the status bar
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
  /*     
  ostringstream o;
  o << "  cam_z = " << setw (4) << setprecision (3) << m_camZ 
    << "  r_x = " << setw (4) << setprecision (3) << m_rotX << "°"
    << "  r_y = " << setw (4) << setprecision (3) << m_rotY << "°"
    << "  r_z = " << setw (4) << setprecision (3) << m_rotZ << "°" << "   |  "
    << "  cam_w = " << setw (4) << setprecision (3) << -Tw - 2.
    << "  R_xw ="  << setw (4) << setprecision (3) << Rxw << "°"
    << "  R_yw ="  << setw (4) << setprecision (3) << Ryw << "°"
    << "  R_zw ="  << setw (4) << setprecision (3) << Rzw << "°"
    << ends;
    
  status += o.str ();
  */
  if (!status.isEmpty ()) {
      for (unsigned i = status.length (); i <= 24; i++) status = " "+status;
      status = " - "+status;
  }
  setCaption (ObjectName+status);
  //  StatusBar->message (ObjectName+status);
}


/*******************************************************************************
 *  @param on		wheter to use fog
 */
void C4DView::SetupDepthCue (bool on) {
  float size = Size ();
  DepthCue3D = on;
  if (on) {
    XQGLWidget::SetupDepthCue (fabs (m_camZ)-size/2., fabs (m_camZ)+size/2.*SR3);
    glEnable (GL_FOG);
  }
  else glDisable (GL_FOG);
}


/*******************************************************************************
 *  called whenever an object or the parameters have changed; changes the display
 *  on the status bar and for the names of the parameters on the ValuesDialog
 *  @param Title	name of the new object
 *  @param Parameter1	name of the new object's first parameter, if any
 *  @param Parameter2	name of the new object's second parameter, if any
 *  @param Parameter3	name of the new object's third parameter, if any
 *  @param Parameter4	name of the new object's fourth parameter, if any
 */
void C4DView::AssignValues (const char *Title,
			    const char *Parameter1, const char *Parameter2,
			    const char *Parameter3, const char *Parameter4) {
  if (Title) {
    ObjectName = Title;
    setCaption (ObjectName);
  }

  if (Parameter1) {
    Values->aText (Parameter1);
    Values->A->setEnabled (true);
    Values->ALabel->setEnabled (true);
  } else {
    Values->aText ("");
    Values->A->setEnabled (false);
    Values->ALabel->setEnabled (false);
  }
  if (Parameter2) {
    Values->bText (Parameter2);
    Values->B->setEnabled (true);
    Values->BLabel->setEnabled (true);
  } else {
    Values->bText ("");
    Values->B->setEnabled (false);
    Values->BLabel->setEnabled (false);
  }
  if (Parameter3) {
    Values->cText (Parameter3);
    Values->C->setEnabled (true);
    Values->CLabel->setEnabled (true);
  } else {
    Values->cText ("");
    Values->C->setEnabled (false);
    Values->CLabel->setEnabled (false);
  }
  if (Parameter4) {
    Values->dText (Parameter4);
    Values->D->setEnabled (true);
    Values->DLabel->setEnabled (true);
  } else {
    Values->dText ("");
    Values->D->setEnabled (false);
    Values->DLabel->setEnabled (false);
  }

  Transform ();
}


/*******************************************************************************
 *  called whenever an object or the parameters have changed; sets the parameters,
 *  applies the changed parameters to the function object and redraws it
 */
void C4DView::ApplyChanges (void) {
  F->SetParameters (Values->a (), Values->b (), Values->c (), Values->d ());
  /*
    ostrstream o;
    o << "Parameter A: " << Values->a () << "\t"
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
    << "dV  : " << Values->dv () << "\n"
    << ends;
    
    QMessageBox::warning (NULL, 
			  "C4DView::ApplyChanges ()", 
			  "OK");
  */
  F->ReInit (Values->tmin (), Values->tmax (), Values->dt (), 
	     Values->umin (), Values->umax (), Values->du (),
	     Values->vmin (), Values->vmax (), Values->dv ());
    
  Transform ();
  Redraw ();

}


/*******************************************************************************
 *  called whenever an object or the parameters have changed; this is the most
 *  generalized version, but it doesn't exist  yet
 */
void C4DView::ParametersChanged (double tmin, double tmax, unsigned tsteps,
				 double umin, double umax, unsigned usteps,
				 double vmin, double vmax, unsigned vsteps,
				 double a, double b, double c, double d,
				 QString &func) {
  QMessageBox::information (this, "C4DView::ParametersChanged", "... is not yet implemented");
}




