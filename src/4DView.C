
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

/////////////////////////////////////////////////////////////////////////////
// 	C4DView construction/destruction
//
//
//
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
  //  StatusBar = new QStatusBar (this);

  show ();
  
  ObjectHypercube ();

  Light ();

  //  in about half of all cases the call to ObjectHypercube () above produces a mutilated
  //  object, with vertices missing and generally wrong. i don't know why. all i can say
  //  is that a second call to ObjectHypercube () always seems to give a correct result.
  //  so:
  ObjectHypercube ();
}

//
//
//
C4DView::~C4DView() {
  for (unsigned j = 0; j < 4; j++) {
    delete [] Cross[j]; delete [] CrossTrans[j]; delete [] CrossScr[j];
  }
  delete [] Cross; delete [] CrossTrans; delete [] CrossScr;
}

/////////////////////////////////////////////////////////////////////////////
//	application of translations and rotations
//
//
//
void C4DView::Transform (double Thetaxy, double Thetaxz, double Thetaxw, double Thetayz, double Thetayw, double Thetazw,
			 double Tx, double Ty, double Tz, double Tw) {
  if (F) F->Transform (Thetaxy, Thetaxz, Thetaxw, Thetayz, Thetayw, Thetazw, 
		       Tx, Ty, Tz, Tw);
  else return;

  matrix<4> Rxy = matrix<4> (0, 1, Thetaxy), Rxz = matrix<4> (0, 2, Thetaxz), Rxw = matrix<4> (0, 3, Thetaxw),
            Ryz = matrix<4> (1, 2, Thetayz), Ryw = matrix<4> (1, 3, Thetayw), Rzw = matrix<4> (2, 3, Thetazw),
            Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw,
            Rot = Rxyz*Rxwyz*Ryzw;
  Vector Trans = Vector (4, Tx, Ty, Tz, Tw);

  for (unsigned i = 0; i < 4; i++)
    for (unsigned j = 0; j < 2; j++) 
      CrossTrans[i][j] = (Rot*Cross[i][j])+Trans;
}

//
//
//
void C4DView::Project (void) {
  if (F) F->Project (ScrW, CamW, DepthCue4D);
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

//
//
//
double C4DView::Size () {
  return sqrt ((Values->tmax ()-Values->tmin ())*(Values->tmax ()-Values->tmin ())
	      +(Values->umax ()-Values->umin ())*(Values->umax ()-Values->umin ())
	      +(Values->vmax ()-Values->vmin ())*(Values->vmax ()-Values->vmin ()));
}   

//
//
//
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

//
//
//
void C4DView::Draw () {
  if (DisplayCoordinates) DrawCoordinates ();

  F->Draw ();
}

//
//
//
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
	  dz = rotate.x ()/xsize*10; 
	  dy = rotate.y ()/ysize*10;                    	//
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
	  dxw = rotate.x ()/xsize*10; 
	  dx = rotate.y ()/ysize*10;                    	//
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
	  dyw = rotate.x ()/xsize*10; 
	  dzw = rotate.y ()/ysize*10;                    	//
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
	  dx = rotate.x ()/xsize*10; 
	  dy = rotate.y ()/ysize*10;                    	//
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
	  dz = zoom.x ()/xsize*20; 
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


//
//
//
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

//
//
//
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

//
//
//
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

//
//
//
void C4DView::StartAnimation () {
# if 0
  cerr << "C4DView::StartAnimation ()\n";
# endif

  Animated = true;
  AnimationTimer->start (1000/animation_fps);                                 //    go for 50 fps
  
  UpdateStatus ("Double-click LMB to stop animation");
}

//
//
//
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

//
//
//
void C4DView::OnTimer() {
  m_rotX += dx; m_rotY += dy; m_rotZ += dz;        		//    update 3D viewpoint values

# if 0
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
  
  if (RenderToPixmap) {
    CurrentlyRendering = true;
    static unsigned long frame = 0;
    
    cerr << "C4DView::OnTimer() ";
    QPixmap tmpPixmap = renderPixmap (width (), height (), false);
    cerr << tmpPixmap.width () << " " << tmpPixmap.height () << endl;

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
    
  UpdateStatus ("Double-click LMB to stop animation");
}

void C4DView::RandomAnimation() {
  AnimationTimer->stop ();
  AnimateRandomTimer->stop ();

  dxw = float (rand ())/RAND_MAX;
  dyw = float (rand ())/RAND_MAX; 
  dzw = float (rand ())/RAND_MAX;
  StartAnimation ();

  AnimateRandomTimer->start (10000);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    from here on it gets pretty boring OpenGL management stuff
//

void C4DView::Redraw () {
  if (ObjectList) glDeleteLists (ObjectList,1); 
  ObjectList = GetGLList ();
  glNewList (ObjectList, GL_COMPILE_AND_EXECUTE);

    Project ();
    Draw (); 

  glEndList ();
  
  if (DisplayCoordinates) {
    if (CoordinateCross) glDeleteLists (CoordinateCross,1);
    CoordinateCross = GetGLList ();
    glNewList (CoordinateCross, GL_COMPILE);
      DrawCoordinates ();
    glEndList ();
  }

  OnPaint ();
}

//
//
//
void C4DView::RenderScene (unsigned Frame) {			//	draw (a frame of the animation)
  if (glIsList (ObjectList)) {
    glCallList (ObjectList);					//	draw the object
    if (DisplayCoordinates)
      glCallList (CoordinateCross);
  }
  else {
#if 1
    switch (QMessageBox::warning (NULL, 
				  "C4DView::RenderScene", 
				 ("ObjectList No. "+itoa (ObjectList)+
				  " is not a GL list!").c_str (),
				  "Retry", "Die", 0,
				  0, 1)) {
    case 0: Redraw ();
            break;
    case 1: exit (1);
            break;
    }
#else
    Redraw ();
#endif
  }
}

//
//	OnPaint: should be called whenever the object is rotaded or translated
//
void C4DView::OnPaint() {                                	//    object drawing routine
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

    RenderScene (0);                                		//    draw current frame

    glPopMatrix();                                        	//    restore transformation matrix

    swapBuffers ();                            			//    swap the buffers
}

//
//	resizeEvent (): 
//
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

/////////////////////////////////////////////////////////////////////////////
// C4DView Zeichnen

void C4DView::paintEvent (QPaintEvent *e) {
  OnPaint ();
}

/////////////////////////////////////////////////////////////////////////////
// C4DView Nachrichten-Handler

void C4DView::initializeGL (void) {
  
  XQGLWidget::initializeGL ();
 
  glDisable (GL_CULL_FACE);                            		//    disable face culling
  
  glClearColor (0.1f, 0.1f, 0.1f, 1.);                    	//    set background color

  if (RenderToPixmap /* && CurrentlyRendering */) {
    if (ObjectList) glDeleteLists (ObjectList,1); 
    ObjectList = GetGLList ();
    glNewList (ObjectList, GL_COMPILE_AND_EXECUTE);

      Project ();
      Draw (); 

    glEndList ();
  
    if (DisplayCoordinates) {
      if (CoordinateCross) glDeleteLists (CoordinateCross,1);
      CoordinateCross = GetGLList ();
      glNewList (CoordinateCross, GL_COMPILE);
        DrawCoordinates ();
      glEndList ();
    }
  }
}


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
  ostrstream o;
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

void C4DView::SetupDepthCue (bool on) {
  float size = Size ();
  DepthCue3D = on;
  if (on) {
    XQGLWidget::SetupDepthCue (fabs (m_camZ)-size/2., fabs (m_camZ)+size/2.*SR3);
    glEnable (GL_FOG);
  }
  else glDisable (GL_FOG);
}

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

void C4DView::ParametersChanged (double tmin, double tmax, unsigned tsteps,
				 double umin, double umax, unsigned usteps,
				 double vmin, double vmax, unsigned vsteps,
				 double a, double b, double c, double d,
				 QString &func) {
  QMessageBox::information (this, "C4DView::ParametersChanged", "... is not yet implemented");
}




