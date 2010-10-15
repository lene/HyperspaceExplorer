
#if (!defined BALL_H)
#define BALL_H

#include <vector>
#include "Vec.H"
//#include "Vector.H"
#include <qgl.h>

double rnd ();
void glMaterial (GLfloat r,GLfloat g,GLfloat b, GLfloat a = 1.0);
GLint MakeStone (unsigned segments = 10, bool fill = true, double radius = 1.);

/// Base class for the bouncing spheres template
class BallBase {
public:
  BallBase ();

  /// \todo document me
  static void setRandomSize (bool r) { randomSize = r; }
  /// \todo document me
  static bool getRandomSize () { return randomSize; }
  /// \todo document me
  static void setRMax (const double &r) { rmax = r; }
  /// \todo document me
  static double getRMax () { return rmax; }

  /// \todo document me
  static void setNumSegments (unsigned n) { numSegments = n; }

protected:
    /// \todo document me
    double r;
    /// \todo document me
    double m;

    /// \todo document me
    static bool randomSize;
    /// \todo document me
    static double rmax;
    /// \todo document me
    static unsigned numSegments;

    /// \todo document me
    static GLint ball;

  friend class BoxBase;
  //  friend bool touch(Ball &, Ball &, double = 0.);
  //  friend bool touch(const Ball &, const Ball &, double = 0.);
};

template <unsigned D> class Box;

/// Bouncing spheres template
template <unsigned D> class Ball: public BallBase {
public:
  Ball ();
  /// \todo document me
  void draw ();
  /// \todo document me
  void step (double dt);

protected:
  /// \todo document me
  void DrawBall (const Vec<D> &center, double r,
		 const Vec<4> &rgba);

  /// \todo document me
  Vec<D> x;
  /// \todo document me
  Vec<D> v; // , phi, omega;

  /// \todo document me
  friend class Box<D>;
    /// \todo document me
  template <unsigned d> friend bool touch(const Ball<d> &, const Ball<d> &, double = 0.);
};


template <unsigned D>
bool touch(const Ball<D> &ball1, const Ball<D> &ball2, double dist=0.) {
  Vec<D> X = ball1.x;			//  deviation to avoid bickering about 'discarding const qualifiers'
  X -= ball2.x;
  return (X.norm () <= ball1.r+ball2.r+dist);
}


template <unsigned D>
  void Ball<D>::DrawBall (const Vec<D> &center, double r,
			  const Vec<4> &rgba) {
  glPushMatrix();
  glTranslatef( center[0], center[1], center[2] );
  glScalef( r,r,r );
  glMaterial( rgba[0], rgba[1], rgba[2], rgba[3]);
  //  i have NO idea why, but the line 'if (ball == 0) ball = MakeStone ();'
  //  in the c'tor is NOT executed. so i have to do it again here. not pretty,
  //  but effective. when i understand the behavior, i will change it.
  if (ball == 0) ball = MakeStone (numSegments);
  glCallList (ball);
  glPopMatrix();
}


void DefineHypercube ();


template <unsigned D>
  void Line (const Vec<D> &x0,
	   const Vec<D> &x1) {
    glBegin( GL_LINES );
      glVertex3f(x0[0],x0[1],x0[2]);
      glVertex3f(x1[0],x1[1],x1[2]);
    glEnd();
  }

//  DrawHypercube (Dimension, vertices[])
//  draws a hypercube with given vertices on the grounds that any hypercube
//  is a cube stretched in an additional dimension; a cube is a square pulled
//  apart, a hypercube a cube pulled apart and so on.
//  DrawHypercube draws the (two) cubes a dimension lower (recursively calling
//  itself), and then finishes with drawing the connecting lines which resulted
//  in pulling the cubes apart along the new dimension.

template <unsigned D>
  void DrawHypercube (int d, Vec<D> x[]) {
    if (d > 1) {
      unsigned subhypercubesize = 1<<(d-1);
      DrawHypercube (d-1, x);
      DrawHypercube (d-1, x+subhypercubesize);

      for (unsigned i = 0; i < subhypercubesize; i++)
	Line (x[i], x[i+subhypercubesize]);
    }
    else Line (x[0],x[1]);
  }


template <unsigned D> Ball<D>::Ball ():
  BallBase (), x (), v () {
  if (ball == 0) ball = MakeStone ();
  for (int i = 0; i < D; i++) {
    x[i] = 2.*rnd ()-1.; v[i] = rnd ()-.5;
  }
}

template <unsigned D> void Ball<D>::step (double dt) { x += v*dt; }

template <unsigned D> void Ball<D>::draw () {
  static Vec<4> color (1., 0.5, 0.1, 1.0);
  static double distance = 0.;

  if (D > 3) {
    Vec<D> xproj;
    double projf;
    Box<D>::project (D, x, 1., xproj, projf);
    DrawBall (xproj, r*projf, color*projf);
  }
  else {
    const double dmax = sqrt (double (D));
    DrawBall (x, r*(dmax-distance)/dmax, color);
  }
}

#endif		// BALL_H
