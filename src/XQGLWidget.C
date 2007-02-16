
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


//      project:      Extended QGLWidget
//      module:       XQGLWidget.C
//      compile with: make all
//      contains:     member function declarations for the extended OpenGL widget
//                    and some useful auxiliary routines
//                    uses OpenGL (e.g. MesaGL) and the Qt OpenGL extension

# include <time.h>
# include <sstream>

#include <qapp.h>
#include <qwidget.h>
#include <qgl.h>
#if (QT_VERSION < 300)
#else
# include <qcursor.h>
#endif

#include <GL/glu.h>

#include "XQGLWidget.H"
#include "GLObject.H"

void SetColor (const Vector &);

extern float White[], grey50[];
extern double SR3;


//      XQGLWidget:: public functions


/*******************************************************************************
 *  XQGLWidget constructor; does a lot of initialization to (usually sensible) hard-
 *  coded default values, creates the menus and accelerators
 *  @param parent	parent QWidget, defaults to NULL
 *  @param name		name, defaulting to ""
 */
XQGLWidget::XQGLWidget (QWidget *parent, const char *name) : 
    QGLWidget (parent, name), DrawObject (0),         //                                 *
    R (10), psi (0), theta (0), phi (0),        //                                 *
    Background (4, 0.25, 0.25, 0.25, 1.), Alpha (1.0),  //                         *
    light (true), fog (true), transparent (false), shade (true), colors (true) {
  QWidget *root = QApplication::desktop ();     //
  int screenheight = root->height ();           //  find screen size
  setMinimumSize (256, 256);                    //  hmm... shouldnt I find a more
  setMaximumSize (screenheight,screenheight);   //  flexible way? 
  resize (600, 600);                            //  resize (screenheight,screenheight);

  setCaption ("XQGLWidget");                    //  yeah or what else?

  menu = SetupMenu ();                          //  set up popup menu
  SetupAccel ();                               //  set up key accelerators
}


/*******************************************************************************
 *  OpenGL initialization
 *  setting background colors, setting up lighting, shading, fog and transparence
 */
void XQGLWidget::initializeGL (void) {          
# ifdef __DEBUG__
    cerr << "XQGLWidget::initializeGL " << light << shade << fog << transparent << endl;
# endif      

  glEnable (GL_DEPTH_TEST);                     //  enable 3D mode, sotosay
  glEnable (GL_NORMALIZE);                      //  automatically normalize surface normals
  
  glClearColor (Background[0], Background[1], Background[2], Background[3]);
                                                //  set background color
  if (!doubleBuffer ()) cerr << "Widget is single buffered\n";  //  bad luck; balk but continue

  InitLight ();                                 //  set up lighting parameters
  InitShade ();                                 //  ... flat or gouraud shading
  InitFog ();                                   //  ... depth cue or not
  InitTransparence ();                         	//  ... transparence
}


/*******************************************************************************
 *  OpenGL initialization
 *  setting background colors, setting up lighting, shading, fog and transparence
 */
void XQGLWidget::InitLight (void) {
  static GLfloat LightPos[4] = { 4., 4., 8., 0. };      //  this should be a member variable!

  if (light) {
    glEnable (GL_LIGHTING);                             //  enable lighting
    glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, 1);     //  specular reflections are computed 
                                                //  from the origin of the eye coordinate system
    glLightfv (GL_LIGHT0, GL_POSITION, LightPos);       //  set light position
    glLightfv (GL_LIGHT0, GL_DIFFUSE, White);           //  set diffuse color
    glLightfv (GL_LIGHT0, GL_AMBIENT, grey50);          //  set ambient color
    glEnable (GL_LIGHT0); }                             //  enable this light
  else {
    glDisable (GL_LIGHTING); } }                        //  disable lighting

void XQGLWidget::InitShade (void) {
  if (shade) glShadeModel (GL_SMOOTH);                  //  gouraud shading
  else       glShadeModel (GL_FLAT); }                  //  flat shading

void XQGLWidget::InitFog  (void) { 
  if (fog) {
    glEnable (GL_FOG);                                  //  enable depth cueing
    SetupDepthCue (R, 1.5); }                           //  set depth cue parameters
  else glDisable (GL_FOG); }                            //  disable depth cueing

void XQGLWidget::InitTransparence (void) {
  if (transparent) {
    glEnable  (GL_BLEND);                               //  enable blending
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //  blending function
    glEnable  (GL_POINT_SMOOTH);                        //  draw smooth points
    glEnable  (GL_LINE_SMOOTH);                         //  draw smooth lines
    glEnable  (GL_POLYGON_SMOOTH);                      //  draw smooth surfaces
    glDisable (GL_CULL_FACE);                           //  ...why?                *
 }
  else {
    glDisable (GL_BLEND);                               //  disable blending
    glDisable  (GL_POINT_SMOOTH);                       //  ..
    glDisable (GL_LINE_SMOOTH);                         //  ..
    glDisable (GL_POLYGON_SMOOTH);                      //  .. 
    glEnable  (GL_CULL_FACE); } }               //                                 *

//      SetAlpha (int a e [0, 255])
//      changes global transparence Alpha to a
void XQGLWidget::SetAlpha (int a) { 
  Alpha = float (a)/255.;                       //  calculate Alpha
  InitTransparence ();                          //  change GL state
  repaint ();                                  //  update picture
}


void XQGLWidget::paintGL () {
# ifdef __DEBUG__
    cerr << "XQGLWidget::paintGL ()\n";
# endif      

#if (QT_VERSION < 300)
  setCursor (Qt::WaitCursor);              	     //  change cursor to 'working'
#else
  setCursor (QCursor (Qt::WaitCursor));              //  change cursor to 'working'
#endif

# ifdef __DEBUG__
    cerr << "  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT )\n";
# endif      
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //  clear screen

  glPushMatrix ();                              //  save default view
  //  glMatrixMode (GL_MODELVIEW);              //  NECESSARY?

  glRotatef (GLfloat (psi),   1., 0., 0.);
  glRotatef (GLfloat (theta), 0., 1., 0.);
  glRotatef (GLfloat (phi),   0., 0., 1.);      //  rotate view

# ifdef __DEBUG__
    cerr << "    if (DrawObject) DrawObject->Draw ()\n";
# endif      

  if (DrawObject) DrawObject->Draw ();          //  draw what's there

  glPopMatrix ();                               //  restore default view

  setCursor (arrowCursor); }                    //  restore cursor

void XQGLWidget::Draw (void) {
  DrawObject->Draw (); }                        //  draw what's there

//  change of viewing distance is handled here too,
//  which is not so clean programming style...
void XQGLWidget::resizeGL (int width, int height) {
  GLfloat aspect = (float) width / (float) height,      //                         *
          angle  = .8*atan (2./R)*180./pi,      //                                 *
          across = SR3;                         //                                 *  
  if (angle < 0) angle = 180+angle;             //  keep positive viewing angle

  glViewport (0, 0, width, height);             //                                 *
  glMatrixMode (GL_PROJECTION);                 //                                 *
  glLoadIdentity ();                            //                                ?!
  gluPerspective (angle, aspect, .25, R+across);//                                 *
  glMatrixMode (GL_MODELVIEW);                  //                                 *
  glLoadIdentity ();                            //                                 *
  gluLookAt (0., 0., 1.,                        //                                 *
	     0., 0., 0.,
	     0., 1., 0.);
  glTranslatef (0, 0, -R);                      //                                 *
  if (fog) SetupDepthCue (R, 2.);               //                                 *
}


//      ViewPos (psi, theta, phi) 
//      called any time the viewing angle is changed on the command widget
void XQGLWidget::ViewPos (double psi_, double theta_, double phi_) {
  if ((psi != psi_) || (theta != theta_) || (phi != phi_)) {    //  any change?
    psi = psi_; theta = theta_; phi = phi_;     //  update values
    updateGL (); } }                            //  update picture

//      CanvasGL::ViewPos (R)
//      called any time the viewing distance is changed on the command widget
void XQGLWidget::ViewPos (double R_) {
  if (R != R_ && R_ > 0) {                      //  valid distance?
    R = R_;                                     //  update value
    resizeGL (width (), height());              //  update GL state
    updateGL (); } }                            //  update picture

void XQGLWidget::SetupDepthCue (float dist, float size) {
  static GLfloat back[4];                       //  copy background color because
  for (unsigned i = 0; i < 4; back[i] = Background[i++]);       //                 *

  glFogi (GL_FOG_MODE,  GL_LINEAR);             //  set fog mode to linear
  glFogfv(GL_FOG_COLOR, back);                  //  ... fog color 
  glFogf (GL_FOG_START, dist-size/2.);          //  ...                            *
  glFogf (GL_FOG_END,   dist+size/2.*SR3); }    //  ...                            *
