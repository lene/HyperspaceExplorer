
#if (!defined BOX_H)
#define BOX_H

#include "Ball.H"
#include "Matrix.H"

extern double &rot_xw, &rot_yw, &rot_zw,
              &drot_xw,&drot_yw,&drot_zw,
              &rot_xyz, &rot_xyw, &rot_xzw, &rot_yzw,
              &drot_xyz,&drot_xyw,&drot_xzw,&drot_yzw;

extern double rot[][8], drot[][8];

/// Base class and interface for a Box of any dimension
class BoxBase {
public:
  BoxBase ();
  virtual ~BoxBase () { };

  /// Set friction for collisions
  static void setFriction(const double &_f) { friction = _f; }
  /// \return Friction for collisions
  static double getFriction () { return friction; }
  /// Set elasticity for collisions
  static void setElasticity(const double &_e) { elasticity = _e;}
  /// \return Elasticity for collisions
  static double getElasticity () { return elasticity; }
  /// Set gravitation
  static void setGravitation (const double &_g) { gravity = _g; }
  /// \return Gravitation
  static double getGravitation () { return gravity; }
  /// \todo document me
  static void setRMax (const double &_g) { BallBase::setRMax (_g); }
  /// \todo document me
  static double getRMax () { return BallBase::getRMax (); }
  /// \todo document me
  static void setMaxT(const double &_t) {
    max_t = _t;
    if (_t <= 0) max_t = 1e310;
  }
  /// \todo document me
  static double getMaxT () { return max_t; }
  /// \todo document me
  static void setSloppy (bool _s) { sloppy = _s; }
  /// \todo document me
  static double getSloppy () { return sloppy; }
  /// \todo document me
  static void setRndSize (bool r) { BallBase::setRandomSize (r); }
  /// \todo document me
  static double getRndSize () { return BallBase::getRandomSize (); }

  /// \todo document me
  virtual void draw() = 0;
  /// \todo document me
  virtual void step (const double &) = 0;

  /// \todo document me
  virtual void setNumBalls (unsigned) = 0;
  /// \todo document me
  virtual unsigned getNumBalls () = 0;

  /// \todo document me
  virtual void setXCam (const double &) = 0;
  /// \todo document me
  virtual double *getXCam () = 0;
  /// \todo document me
  virtual unsigned getDimension () = 0;

  /// \todo document me
  double getT () { return t; }
  /// \todo document me
  unsigned getCollisions () { return num_collisions; }

  /// \todo document me
  void setRotation (unsigned axis1, unsigned axis2, double phi) {
    drot[axis2-1][axis1] = phi;
  }
  /// \todo document me
  double getRotation (unsigned axis1, unsigned axis2) {
    return drot[axis2-1][axis1];
  }

protected:
  /// \todo document me
  unsigned num_collisions;
  /// \todo document me
  double t;

  /// \todo document me
  static double max_t;
  /// \todo document me
  static double friction;
  /// \todo document me
  static double elasticity;
  /// \todo document me
  static double gravity;

  /// \todo document me
  static bool sloppy;
};

/// Hypercube of dimension \p D, which contains a number of Balls
template <unsigned D> class Box: public BoxBase {
public:
  /// \todo document me
  Box (unsigned n = 1);
  virtual ~Box () { };

  /// \todo document me
  virtual void draw();
  /// \todo document me
  virtual void step (const double &dt);

  /// \todo document me
  virtual void setNumBalls (unsigned n);
  /// \todo document me
  virtual unsigned getNumBalls () { return balls.size (); }

  /// \todo document me
  virtual unsigned getDimension () { return D; }

  /// \todo document me
  virtual void setXCam (const double &_Xcam) {
    for (int i = 0; i < D; Xcam[i++] = -_Xcam);
  }
  /// \todo document me
  virtual double *getXCam () { return Xcam; }

  /// \todo document me
  static Vec<D> project (unsigned d,
                         const Vec<D> &X, const double &r,
                         Vec<D> &Xproj, double &rproj);

  /// \todo document me
  static Vec<D> vertices[1 << D];

protected:
  /// \todo document me
  Ball<D> *makeBall ();
  /// \todo document me
  void addBall ();
  /// \todo document me
  void deleteBall ();
  /// \todo document me
  void collide (Vec<D> &, Vec<D> &, Vec<D> &,
                const double &, const double &);
  /// \todo document me
  void rotate (Vec<D> [1<<D]);
  /// \todo document me
  static void DefineHypercube ();

  /// \todo document me
  Vec<D> Xmin;
  /// \todo document me
  Vec<D> Xmax;
  /// \todo document me
  vector<Ball<D> *> balls;

  /// \todo document me
  static Vec<D>   vtrans[1 << D];
  /// \todo document me
  static matrix<D> R;
  /// \todo document me
  static double Xcam[D];
};

template <unsigned D> void Box<D>::rotate (Vec<D> vtrans[1<<D]) {
  for (unsigned i = 1; i < D; i++)
    for (unsigned j = 0; j < i; j++)
      rot[i-1][j] = drot[i-1][j]*t;

  if (D > 3) R = matrix<D> ();
  for (unsigned i = 3; i < D; i++)
    for (unsigned j = 0; j < i; j++) {
      rot[i-1][j] = drot[i-1][j]*t;
      R = R*matrix<D> (j, i, rot[i-1][j]);
    }
}

template <unsigned D> Box<D>::Box (unsigned n):
    BoxBase (),
    Xmin (), Xmax (),
    balls () {
  for (int i = 0; i < D; i++) {
    Xmin[i]= -1.; Xmax[i] = 1.;
  }

  DefineHypercube ();
  DrawHypercube (D, vertices);

  setNumBalls (n);
}

template <unsigned D> Ball<D> *Box<D>::makeBall () {
  Ball<D> *tmp = new Ball<D>;
  bool touched = true;
  while (touched) {
    touched = false;
    for (int j = 0; j < balls.size (); j++)
      if (touch (*balls[j], *tmp, tmp->r))
	touched = true;

    if (touched) {
      delete tmp; tmp = new Ball<D>; }
  }
  return tmp;
}

template <unsigned D> void Box<D>::addBall () {
  Ball<D> *tmp = makeBall ();
  balls.push_back (tmp);
}

template <unsigned D> void Box<D>::deleteBall () {
  if (balls[balls.size ()]) {
    delete balls[balls.size ()];
    balls[balls.size ()] = 0;
  }
  balls.pop_back ();
  //  cerr << "D " << balls.size ()<< " ";
}

template <unsigned D> void Box<D>::setNumBalls (unsigned newnum) {
  //  cerr << "S<"<<D<<">: " << balls.size ()<< " -> " << newnum << " ";
  if (newnum > balls.size ())
    for (int i = balls.size (); i < newnum; i++)
      addBall ();
  else if (newnum < balls.size ())
    for (int i = balls.size (); i > newnum; i--)
      deleteBall ();
  else { /* nothing to be done */ }
}


template <unsigned D>
  void Box<D>::collide (Vec<D> &v1, Vec<D> &v2,
			Vec<D> &dx,
			const double &m1, const double &m2) {
  if ((v1-v2).sqnorm() == 0) return;

  Vec<D> dxunity = dx.normalize ();
  double cosa1 = dxunity*v1, cosa2 = dxunity*v2;
  Vec<D> v1rad = dxunity*cosa1, v2rad = dxunity*cosa2,
                 v1tan = v1 - v1rad, v2tan = v2 - v2rad,
                 vcm = (v1rad*m1+v2rad*m2)/(m1+m2),
                 p1rad = (v1rad-vcm)*m1,
                 v1rad_ = vcm - p1rad/m1*elasticity,
                 v2rad_ = vcm + p1rad/m2*elasticity;
  v1 = v1rad_+v1tan;
  v2 = v2rad_+v2tan;
}

template <unsigned D> void Box<D>::step (const double &dt) {
  t += dt; if (t >= max_t) {
    cout << num_collisions<< endl;
    exit (0);
  }

  //  cerr << balls.size () << endl;
  for (int i = 0; i < balls.size(); i++) {

    for (int j = i+1; j < balls.size(); j++)
      if (touch (*balls[i], *balls[j])) {

	double &m1 = balls[i]->m, &m2 = balls[j]->m;
	Vec<D> &v1 = balls[i]->v, &v2 = balls[j]->v;
	if (!sloppy) {
	  Vec<D> dx = balls[i]->x - balls[j]->x;
	  collide (v1, v2, dx, m1, m2);
	}
	else {
	  Vec<D> vcm = (v1*m1+v2*m2)/(m1+m2),
	         p1 = (v1-vcm)*m1;  //  = p2 =(v2rad-vcm)*m2,
	  v1 = vcm - p1*elasticity/m1, v2 = vcm + p1*elasticity/m2; // - p2/m2;
	}

	balls[i]->step (dt); balls[j]->step (dt);
	num_collisions++;
      }

    for (int k = 0; k < D; k++) {
      if (balls[i]->x[k] <= Xmin[k]+balls[i]->r) {
	balls[i]->x[k] = Xmin[k]+balls[i]->r;
	balls[i]->v[k] = -balls[i]->v[k]*(1-friction);
      }
      if (balls[i]->x[k] >= Xmax[k]-balls[i]->r) {
	balls[i]->x[k] = Xmax[k]-balls[i]->r;
	balls[i]->v[k] = -balls[i]->v[k]*(1-friction);
      }
    }

    if (gravity) balls[i]->v[1] -= gravity*dt;
    balls[i]->step(dt);
  }
}

template <unsigned D>
  Vec<D> Box<D>::project (unsigned d,
				  const Vec<D> &X, const double &r,
				  Vec<D> &Xproj, double &rproj) {
  if (d > 3) {
    Vec<D> Xtrans = R*X;
    double projectionfactor = -Xcam[d-1]/(Xtrans[d-1]-Xcam[d-1]);

    for (int i = 0; i < d-1; i++)
      Xproj[i]=Xtrans[i]*projectionfactor;
    rproj = r*projectionfactor;

    Xproj[d-1] = rproj;	//  pack radius into the unused component, just in case

    return project (d-1, Xproj, rproj, Xproj, rproj);
  }
  else return X;
}


//  DefineHypercube ()
//  creates an array of vectors which contain the edges of a hypercube of
//  dimension num_dimensions in an ordered way
template <unsigned D> void Box<D>::DefineHypercube () {
  for (unsigned i = 0; i < 1<<D; i++)
    for (unsigned j = 0; j < D; j++)
      vertices[i][j] = i&(1<<j)? 1.0: -1.0;
}


#include <GL/gl.h>

template <unsigned D> void Box<D>::draw () {
  glPushMatrix();
  glTranslatef( 0.,0.,0. );
  glScalef( 1.,1.,1. );
  glMaterial (1.0,0.9,1.0);
  //  glLineWidth( 2.0 );

  if (D < 4)
    DrawHypercube (D, vertices);
  else {
    rotate (vtrans);
    static double dummy;
    for (unsigned i = 0; i < (1 << D); i++)
      project (D, vertices[i], 1., vtrans[i], dummy);
    DrawHypercube (D, vtrans);
  }

  glPopMatrix();

  for (int i = 0; i < balls.size(); i++) {
    balls[i]->draw();
  }
}

#endif
