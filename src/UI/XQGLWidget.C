
//      project:      hyperspace explorer
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)
//
//	taken and adapted from:
//      project:      Extended QGLWidget
//      module:       PopupStuff.C
//      compile with: make all
//      contains:     member function declarations for the extended OpenGL widget
//                    and some useful auxiliary routines
//                    uses OpenGL (e.g. MesaGL) and the Qt OpenGL extension
//                    Menu, mouse event and keyboard accelerator declarations
//		      for XQGLWidget
//
//                    I wrote this module in 2000, maybe 2001, and never touched
//                    it since, because it Just Worked(TM) for me.
//                    Don't be surprised about some peculiarities. I have
//                    moved on since then.

#include <GL/glu.h>

#include <ctime>
#include <sstream>

#include <QDesktopWidget>
#include <QMouseEvent>
#include <QSlider>

#include "XQGLWidget.H"
#include "GLObject.H"
#include "Log.H"
#include "Globals.H"
#include "Help.H"

//using std::cerr;
using std::endl;


GLfloat XQGLWidget::LightPos[4] = { 4., 4., 8., 0. };


/** XQGLWidget constructor; does a lot of initialization to (usually sensible)
 *  hardcoded default values, creates the menus and accelerators
 *  @param parent	parent QWidget, defaults to NULL
 *  @param name		name, defaulting to ""                                */
XQGLWidget::XQGLWidget (QWidget *parent) :
    QGLWidget (parent), DrawObject (0),
    R (10), psi (0), theta (0), phi (0),
    Background (4, 0.25, 0.25, 0.25, 1.), Alpha (1.0),
    light (true), fog (true), transparent (false), shade (true), colors (true) {
    setMinimumSize (256, 256);                  //  hmm... shouldnt I find a more flexible way?
}

/** OpenGL initialization
 *  setting background colors, setting up lighting, shading, fog and
 *  transparence                                                              */
void XQGLWidget::initializeGL (void) {
    SingletonLog::Instance().log("XQGLWidget::initializeGL()");

    glEnable (GL_DEPTH_TEST);                   //  enable 3D mode, sotosay
    glEnable (GL_NORMALIZE);                    //  automatically normalize surface normals

    glClearColor (Background[0], Background[1], Background[2], Background[3]);
                                                //  set background color
    if (!doubleBuffer ())                       //  this should happen rarely if ever
        SingletonLog::Instance().log("Widget is single buffered");  //  complain but continue

    InitLight ();                               //  set up lighting parameters
    InitShade ();                               //  ... flat or gouraud shading
    InitFog ();                                 //  ... depth cue or not
    InitTransparence ();                        //  ... transparence
}

/** OpenGL initialization
 *  setting background colors, setting up lighting, shading, fog and
 *  transparence
 *  @todo hardcoded light position and colors!                                */
void XQGLWidget::InitLight (void) {
    if (light) {
        glEnable(GL_LIGHTING);                          //  enable lighting
        //  compute specular reflections from origin of eye coordinate system
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
        glLightfv(GL_LIGHT0, GL_POSITION, LightPos);    //  set light position
        glLightfv(GL_LIGHT0, GL_DIFFUSE,
                  Globals::Instance().white());         //  diffuse color
        glLightfv(GL_LIGHT0, GL_AMBIENT,
                  Globals::Instance().grey50());        //  ambient color
        glEnable(GL_LIGHT0);                            //  enable this light
    } else {
        glDisable(GL_LIGHTING);                         //  disable lighting
    }
}

void XQGLWidget::InitShade (void) {
    if (shade) glShadeModel (GL_SMOOTH);        //  gouraud shading
    else       glShadeModel (GL_FLAT);          //  flat shading
}

void XQGLWidget::InitFog  (void) {
    if (fog) {
        glEnable (GL_FOG);                      //  enable depth cueing
        SetupDepthCue (R, 1.5);                 //  set depth cue parameters
    } else
        glDisable (GL_FOG);                     //  disable depth cueing
}

void XQGLWidget::InitTransparence (void) {
    if (transparent) {
        glEnable  (GL_BLEND);                               //  enable blending
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //  blending function
        glEnable  (GL_POINT_SMOOTH);                        //  draw smooth points
        glEnable  (GL_LINE_SMOOTH);                         //  draw smooth lines
        glEnable  (GL_POLYGON_SMOOTH);                      //  draw smooth surfaces
//        glDisable (GL_CULL_FACE);                           //  ...why?             *
    } else {
        glDisable (GL_BLEND);                               //  disable blending
        glDisable  (GL_POINT_SMOOTH);                       //  ..
        glDisable (GL_LINE_SMOOTH);                         //  ..
        glDisable (GL_POLYGON_SMOOTH);                      //  ..
//        glEnable  (GL_CULL_FACE);                           //                      *
    }
}

void XQGLWidget::paintGL () {
    SingletonLog::Instance().log("XQGLWidget::paintGL()");

    setCursor (QCursor (Qt::WaitCursor));       //  change cursor to 'working'

    SingletonLog::Instance().log("  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //  clear screen

    glPushMatrix ();                            //  save default view
    //  glMatrixMode (GL_MODELVIEW);            //  NECESSARY?

    glRotatef (GLfloat (psi),   1., 0., 0.);
    glRotatef (GLfloat (theta), 0., 1., 0.);
    glRotatef (GLfloat (phi),   0., 0., 1.);    //  rotate view

    SingletonLog::Instance().log("    if (DrawObject) DrawObject->Draw ()");
    if (DrawObject) DrawObject->Draw ();        //  draw what's there

    glPopMatrix ();                             //  restore default view

    setCursor (Qt::ArrowCursor);                //  restore cursor
}

void XQGLWidget::Draw (void) {
    DrawObject->Draw ();                        //  draw what's there
}

/** change of viewing distance is handled here too, which is not so clean
 *  programming style...
    \todo eliminate hardcoded constants                                       */
void XQGLWidget::resizeGL (int width, int height) {
    GLfloat aspect = (float) width / (float) height,
            angle  = .8*atan (2./R)*180./pi,
            across = Globals::Instance().SR3;
    if (angle < 0) angle = 180+angle;           //  keep positive viewing angle

    glViewport (0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (angle, aspect, .25, R+across);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0., 0., 1.,
	       0., 0., 0.,
	       0., 1., 0.);
    glTranslatef (0, 0, -R);
    if (fog) SetupDepthCue (R, 2.);
}


/** ViewPos (psi, theta, phi)
    called any time the viewing angle is changed on the command widget        */
// void XQGLWidget::ViewPos (double psi_, double theta_, double phi_) {
//     if ((psi != psi_) || (theta != theta_) || (phi != phi_)) {    //  any change?
//         psi = psi_; theta = theta_; phi = phi_; //  update values
//         updateGL (); } }                        //  update picture

/** called any time the viewing distance is changed on the command widget     */
// void XQGLWidget::ViewPos (double R_) {
//     if (R != R_ && R_ > 0) {                    //  valid distance?
//         R = R_;                                 //  update value
//         resizeGL (width (), height());          //  update GL state
//         updateGL ();                            //  update picture
//     }
// }

void XQGLWidget::SetupDepthCue (float dist, float size) {
  static GLfloat back[4];                       //  copy background color because
  for (unsigned i = 0; i < 4; i++) back[i] = Background[i];

  glFogi (GL_FOG_MODE,  GL_LINEAR);             //  set fog mode to linear
  glFogfv(GL_FOG_COLOR, back);                  //  ... fog color
  glFogf (GL_FOG_START, dist-size/2.);          //  ...
  glFogf (GL_FOG_END,   dist+size/2.*Globals::Instance().SR3);
}

////////////////////////////////////////////////////////////////////////////////
//
//	XQGLWidget mouse handling
//
////////////////////////////////////////////////////////////////////////////////

/** mouse press event handler; cares for popping up the menu (RMB), rotating
 *  (LMB) and zooming (MMB)
 *  @param e Qt's mouse event information structure                           */
// void XQGLWidget::mousePressEvent (QMouseEvent *E) {
//     SingletonLog::Instance() << "XQGLWidget::mousePressEvent ()\n";
//     int ButtonPressed = E->button ();
//     if (ButtonPressed == Qt::RightButton) {
//         SingletonLog::Instance() << "  ButtonPressed == Qt::RightButton\n";
//     } else if (ButtonPressed == Qt::LeftButton) {
//         xpressed = E->x(); ypressed = E->y();
//     } else if (ButtonPressed == Qt::MidButton) {
//         if (E->modifiers() && Qt::ShiftModifier) ViewPos (R+1);
//         else ypressed = E->y();               // ViewPos (R-1); }
//     }
// }


/** mouse release event handler; cares for executing the action associated with
 *  the mouse button
 *  \todo get rid of HARDCODED values for zooming!
 *  @param e	Qt's mouse event information structure                        */
// void XQGLWidget::mouseReleaseEvent (QMouseEvent *E) {
//   int ButtonPressed = E->button ();
//   if (ButtonPressed == Qt::LeftButton) {
//     int dx = E->x () - xpressed, dy = E->y () -ypressed,
//       dtheta = dx*90/width (), dpsi   = dy*90/height ();
//     theta += dtheta; psi += dpsi;
//     repaint (); }
//   if (ButtonPressed == Qt::MidButton) {
//     double dr = double (E->y ()-ypressed)/height ()*5.;   //  the 5 may have to be reviewed
//     if (dr) ViewPos (R*pow (1.25, dr));                   //  exponential change (1.25 also)
//     else if (!(E->modifiers() && Qt::ShiftModifier))
//       ViewPos (R/1.25);
//   }
// }


/** display help window
 * \todo HARDCODED filename */
void XQGLWidget::Help () {
   static HelpWindow *H;
   H = new HelpWindow ("Hyperspace_Explorer_Help.html");
   H->show();
}

/** open an "About"-Dialog */
void XQGLWidget::about() {
    QMessageBox::about(this, "Hyperspace Explorer",
                      "<p>A program to view four-dimensional objects "
                      "using OpenGL and the Qt GUI library.</p>"
                      "<p>author: "+QString(make_str(PACKAGE_BUGREPORT))+"</p>"
                      "<p>version: "+QString(make_str(PACKAGE_VERSION))+
                              " of "+QString(__DATE__)+"</p>"
              );
}


/** open an "About Qt"-Dialog */
void XQGLWidget::aboutQt() {
  QMessageBox::aboutQt( this, "Hyperspace Explorer" );
}
