
#include "BoxWidget.H"

extern GLint ball;
extern GLdouble &view_rotx, &view_roty, &view_rotz,
                &drotx, &droty, &drotz;

extern double t;

int BoxWidget::timer_interval = 10;

BoxWidget::BoxWidget (unsigned dim, unsigned nballs, double _Xcam,
		      QWidget *parent=0, const char *name=0 ):
    QGLWidget( parent, name ), 
    display (true),
    saveName ("Pic_") {
  BoxArray[0] = BoxArray[1] = 0;
  BoxArray[2] = new Box<2> (0);
  BoxArray[3] = new Box<3> (1);
  BoxArray[4] = new Box<4> (1);
  BoxArray[5] = new Box<5> (0);
  BoxArray[6] = new Box<6> (0);
  BoxArray[7] = new Box<7> (0);
  BoxArray[8] = new Box<8> (0);
  BoxArray[9] = new Box<9> (0);
  setDimension (dim);
  B->setNumBalls (nballs);
  setXCam (_Xcam);
  if (display) show ();
  startTimer( timer_interval );
}

void BoxWidget::initializeGL() {
  static GLfloat pos[4] = {1.0, 1.0, 2.0, 0.0 },
                 White[4] = {1.0,1.0,1.0,1.0},   
		 grey50[4] = {0.5,0.5,0.5,1.0};

  glLightfv( GL_LIGHT0, GL_POSITION, pos );
  glLightfv (GL_LIGHT0, GL_DIFFUSE, White);
  glLightfv (GL_LIGHT0, GL_AMBIENT, grey50);
  glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, 1);
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );

  glEnable( GL_CULL_FACE );
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_NORMALIZE );

  glFogi (GL_FOG_MODE, GL_LINEAR);
  glFogf (GL_FOG_START, -getXCam ()[2]-3.0);
  glFogf (GL_FOG_END,   -getXCam ()[2]+3.0);
  glEnable (GL_FOG);

  bool antialias = false;
  if (antialias) {
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_POLYGON_SMOOTH); }
  else {
    glDisable (GL_BLEND);
    glDisable (GL_LINE_SMOOTH);
    glDisable (GL_POLYGON_SMOOTH); }

  glShadeModel( GL_SMOOTH );
}

void BoxWidget::resizeGL( int width, int height ) {
    GLfloat w = (float) width / (float) height;
    GLfloat h = 1.0;

    glViewport( 0, 0, width, height );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -w, w, -h, h, 
	       fabs (getXCam ()[2])-3.0, fabs (getXCam ()[2])+3.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, getXCam ()[2] );
}


void BoxWidget::paintGL() {    
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
  //  view_rotx += drotx;
  //  view_roty += droty;
  //  view_rotz += drotz;

  glPushMatrix();
  glRotatef( view_rotx, 1.0, 0.0, 0.0 );
  glRotatef( view_roty, 0.0, 1.0, 0.0 );
  glRotatef( view_rotz, 0.0, 0.0, 1.0 );

  glPushMatrix();

  B->draw ();

  glPopMatrix();
}

void BoxWidget::timerEvent(QTimerEvent*) {
  for (int i = 0; i < steps_between; i++) 
    B->step (dt);
  if (display) updateGL();
  if (save) saveImage ();
}

#include <qfile.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qfile.h>

void BoxWidget::saveImage () {
  QImage tmpImage = renderPixmap ().convertToImage ();
  int post = -int (log10 (getDeltaT ()*(steps_between+1)));
  QFile outfile (saveName
		 +("0000"+QString::number (t, 'f', post))
		 .right (unsigned (log10 (getTMax ()))+1+1+post)
		 +".png");
  outfile.open (IO_WriteOnly);
  QDataStream outstream (&outfile);
  outstream << tmpImage;
  outfile.close();
}
