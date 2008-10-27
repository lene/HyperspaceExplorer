
#include "Ball.H"


bool BallBase::randomSize = true;
double BallBase::rmax = 0.2;
unsigned BallBase::numSegments = 16;

GLint MakeStone (unsigned segments = 10, bool fill = true, double radius = 1.) {
  GLUquadricObj *quad = gluNewQuadric ();

  if (fill) {
    gluQuadricDrawStyle (quad, GLU_FILL);
    gluQuadricOrientation (quad, GLU_OUTSIDE);
    gluQuadricNormals (quad, GLU_SMOOTH); }
  else gluQuadricDrawStyle (quad, GLU_LINE);

  GLint list = glGenLists (1);
  glNewList (list, GL_COMPILE);

  gluSphere (quad, radius, segments, segments/2);
   
  glEndList ();
  
  gluDeleteQuadric (quad);
  
  return list; }

GLint BallBase::ball = MakeStone (12);

BallBase::BallBase () {
  m = randomSize? rnd (): 1.;
  r = pow (m, 1./3.)*rmax;
  if (BallBase::ball == 0) BallBase::ball = MakeStone (12);
}

