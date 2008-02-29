
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "Globals.H"
#include "Matrix.H"
#include "Function.H"

unsigned int Delete (void *);

using std::cerr;
using std::endl;

/*******************************************************************************
 *  auxiliary function to safely free a memory chunk
 *  @param x		pointer to memory
 */
template <typename T> unsigned int Delete (T *x) {
  if (x) {
    delete [] x;
    x = NULL;
  }
  return 0; 
}


//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Function default c'tor
 *  zeroes everything
 */
Function::Function ():
  tmin (0),       tmax (0),       dt (0),
  umin (0),       umax (0),       du (0),
  vmin (0),       vmax (0),       dv (0),
  tsteps (0), usteps (0), vsteps (0),
  NumVertices (0),
  F (4),
     Xtrans (NULL), Xscr (NULL), XtransChunk (NULL), XscrChunk (NULL),
  R (NULL), G (NULL), B (NULL), RGBChunk (NULL) { }


/*******************************************************************************
 *  Function c'tor given a definition set in R³ (as parameter space)
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Function::Function (double _tmin, double _tmax, double _dt,
		    double _umin, double _umax, double _du,
		    double _vmin, double _vmax, double _dv):
  tmin (_tmin),	tmax (_tmax),	dt (_dt),
  umin (_umin),	umax (_umax),	du (_du),
  vmin (_vmin),	vmax (_vmax),	dv (_dv),
  tsteps (unsigned ((tmax-tmin)/dt+1)), 
  usteps (unsigned ((umax-umin)/du+1)), 
  vsteps (unsigned ((vmax-vmin)/dv+1)),
  NumVertices (0),
  F (4),
     Xtrans (NULL), Xscr (NULL), XtransChunk (NULL), XscrChunk (NULL),
             R (NULL), G (NULL), B (NULL), RGBChunk (NULL) {
  if (MemRequired () > MaximumMemory) {				//  which is defined in Globals.H
    cerr << "Using a " << tsteps << "x" << usteps << "x" << vsteps
	 << " grid would require approx. " << MemRequired () << " MB of memory.\n";
    while (MemRequired () > MaximumMemory) {
      tsteps--; usteps--; vsteps--;
    }
    cerr << "Using a " << tsteps << "x" << usteps << "x" << vsteps
	 << " grid instead." << endl;
    dt = (tmax-tmin)/tsteps;
    du = (umax-umin)/usteps;
    dv = (vmax-vmin)/vsteps;
  }
}


/*******************************************************************************
 *  Initialize the temporary storage areas Xscr[][][], Xtrans[][][], 
 *                                         R[][][], G[][][], B[][][]
 */
void Function::InitMem (void) {
  XscrChunk = new Vector<3> [(tsteps+2)*(usteps+2)*(vsteps+2)];
  Xscr = new Vector<3> ** [tsteps+2];	// valgrind moans about lost bytes
        
  XtransChunk = new Vector<4> [(tsteps+2)*(usteps+2)*(vsteps+2)];
  Xtrans = new Vector<4> ** [tsteps+2];	// valgrind moans about lost bytes

  RGBChunk = new float [3*(tsteps+2)*(usteps+2)*(vsteps+2)];
  R = new float ** [tsteps+2];
  G = new float ** [tsteps+2];
  B = new float ** [tsteps+2];

  for (unsigned t = 0; t <= tsteps+1; t++) {
                
      Xscr[t] = new Vector<3> * [usteps+2];
      Xtrans[t] = new Vector<4> * [usteps+2];

    R[t] = new float * [usteps+2];
    G[t] = new float * [usteps+2];
    B[t] = new float * [usteps+2];
        
    for (unsigned u = 0; u <= usteps+1; u++) {
        
      Xscr[t][u] = XscrChunk+t*(tsteps+2)*(usteps+2)+u*(usteps+2);
      Xtrans[t][u] = XtransChunk+t*(tsteps+2)*(usteps+2)+u*(usteps+2);

      R[t][u] = RGBChunk+1*t*(tsteps+2)*(usteps+2)+u*(usteps+2);
      G[t][u] = RGBChunk+2*t*(tsteps+2)*(usteps+2)+u*(usteps+2);
      B[t][u] = RGBChunk+3*t*(tsteps+2)*(usteps+2)+u*(usteps+2);
    }                                       //      for (unsigned u = 0; u <= usteps+1; u++) 

  }                                               //      for (unsigned t = 0; t <= tsteps+1; t++) 
}                                                       //      InitiMem ()


/*******************************************************************************
 *  allocate and initialize X[][][] with values of f()
 *  call InitMem () above
 */
void Function::Initialize () {
    Xchunk = new Vector<4>   [(tsteps+2)*(usteps+2)*(vsteps+2)];
    X 	 = new Vector<4> ** [tsteps+2];	// valgrind moans about lost bytes

    for (unsigned t = 0; t <= tsteps+1; t++) {
        X[t] = new Vector<4> * [usteps+2];
        for (unsigned u = 0; u <= usteps+1; u++) {
            X[t][u]  =  Xchunk+t*(usteps+2)*(vsteps+2)+u*(vsteps+2);	//new Vector [vsteps+2];
            for (unsigned v = 0; v <= vsteps+1; v++) {
	            double T = tmin+t*dt, U =umin+u*du, V = vmin+v*dv;
	            X[t][u][v] = f (T, U, V);
            }
        }
    }
    InitMem ();
}


/*******************************************************************************
 *  re-initialize a Function if the definition set has changed
 *  @param tmin		minimal value in t
 *  @param tmax		maximal value in t
 *  @param dt		stepsize in t
 *  @param umin		minimal value in u
 *  @param umax		maximal value in u
 *  @param du		stepsize in u
 *  @param vmin		minimal value in v
 *  @param vmax		maximal value in v
 *  @param dv		stepsize in v
 */
void Function::ReInit(double _tmin, double _tmax, double _dt,
		      double _umin, double _umax, double _du,
		      double _vmin, double _vmax, double _dv) {

# ifdef DEBUG
  cerr  << "Function::ReInit(" << _tmin << ", " << _tmax << ", " << _dt << ", "
	<< _umin << ", " << _umax<< ", " << _du << ", " << _vmin << ", " << _vmax << ", " << _dv << ")\n";
# endif      

  tmin = _tmin;   tmax = _tmax;   dt = _dt;
  umin = _umin;   umax = _umax;   du = _du;
  vmin = _vmin;   vmax = _vmax;   dv = _dv;
  tsteps = unsigned ((tmax-tmin)/dt+1); usteps = unsigned ((umax-umin)/du+1); vsteps = unsigned ((vmax-vmin)/dv+1);
        
  //      Free ();
  
  //  for (unsigned t = 0; t <= tsteps+1; t++) 
  //    delete [] X[t];
  Delete (X);	//	! Mismatched delete !
  //  Delete (Xchunk);

  Initialize ();
}


/*******************************************************************************
 *  placeholder for function to set parameters in descendants - empty because
 *  generic function has no parameters
 *  @param _a		1st parameter
 *  @param _b		2nd parameter
 *  @param _c		3rd parameter
 *  @param _d		4th parameter
 */
void Function::SetParameters (double, double, double, double) { }


/*******************************************************************************
 *  auxiliary function to safely free all member arrays
 */
void Function::Free (void) {
  for (unsigned u = 0; u <= usteps+1; u++) {
    for (unsigned v = 0; v <= vsteps+1; v++) {
      Delete (X[u][v]);
      Delete (Xscr[u][v]);
      Delete (Xtrans[u][v]);
      Delete (R[u][v]);
      Delete (G[u][v]);
      Delete (B[u][v]);
    }
    Delete (X[u]);
    Delete (Xscr[u]);
    Delete (Xtrans[u]);
    Delete (R[u]);
    Delete (G[u]);
    Delete (B[u]);
  }
  Delete (X);
  Delete (Xscr);
  Delete (Xtrans);
  Delete (R);
  Delete (G);
  Delete (B);
  Delete (Xchunk);
  Delete (XscrChunk);
  Delete (XtransChunk);
  Delete (RGBChunk);
}


/*******************************************************************************
 *  return the approximate amount of memory needed to display a Function of current
 *  definition set
 *  uses hardcoded and experimentally found value for memory per cell - ICK!
 *  @return		approx. mem required
 */
unsigned long Function::MemRequired (void) {
  return ((tsteps+2)*(usteps+2)*(vsteps+2)*4)/1024+8;
}


/*******************************************************************************
 *  Function destructor
 */
Function::~Function() {
  //  Free ();				//  WHAT'S WRONG HERE?
}


/*******************************************************************************
 *  calculate normal to function at a given point in definition set
 *  no further assumption is made than that f () is continuous
 *  this function is not yet used anywhere, but i like it
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		surface normal, normalized
 */
Vector<4> &Function::normal (double tt, double uu, double vv) {
    static Vector<4> n;

    Vector<4> *D = df (tt, uu, vv);

    n = vcross (D[0], D[1], D[2]);
    vnormalize (n);

    return n; 
}


/*******************************************************************************
 *  numerical calculation of the derivatives in u and v:
 *
 *	df	  f(u+h, v) - f (u)   df     df
 *	-- =  lim -----------------,  -- and -- analogously
 *	du    h->0     	  h	      dv     dt
 *
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		gradient in t, u and v as array
 */
Vector<4> *Function::df (double tt, double uu, double vv) {	

  static Vector<4> F0;			//	f (u, v)
  static double h = 1e-5;		//	HARDCODED; uargh! maybe tweak to get best results
                                        //	don't want to find it out dynamically though
                                        //	(performance, elegance)
  static Vector<4> DF[3];

  F0 = operator () (tt, uu, vv);							

  F = operator () (tt+h, uu, vv);	//	derive after t
  DF[0] = (F-F0)/h;			

  F = operator () (tt, uu+h, vv);	//	derive after u
  DF[1] = (F-F0)/h;

  F = operator () (tt, uu, vv+h);	//	derive after v
  DF[2] = (F-F0)/h;	

  return DF; }


/*******************************************************************************
 *  transforms a Function
 *  as I look at it, i think this could be optimized by making the transformation
 *  matrices static and only canging the corresponding entries... but how to
 *  make this beautifully, i don't know
 *  @param thetaxy	rotation around xy plane (z axis); should be ignored because 3D rotation takes care of it, but isn't
 *  @param thetaxz	rotation around xz plane (y axis); should be ignored because 3D rotation takes care of it, but isn't
 *  @param thetaxw	rotation around xw plane
 *  @param thetayz	rotation around xy plane (x axis); should be ignored because 3D rotation takes care of it, but isn't
 *  @param thetayw	rotation around yw plane
 *  @param thetazw	rotation around zw plane
 *  @param tx		translation in x direction
 *  @param ty		translation in y direction
 *  @param tz		translation in z direction
 *  @param tw		translation in w direction
 */
void Function::Transform (double thetaxy, double thetaxz, double thetaxw, double thetayz, double thetayw, double thetazw,
			  double tx, double ty, double tz, double tw) {
    matrix<4> Rxy = matrix<4> (0, 1, thetaxy), Rxz = matrix<4> (0, 2, thetaxz), Rxw = matrix<4> (0, 3, thetaxw),
        Ryz = matrix<4> (1, 2, thetayz), Ryw = matrix<4> (1, 3, thetayw), Rzw = matrix<4> (2, 3, thetazw),
        Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw, 
        Rot = Rxyz*Rxwyz*Ryzw;
    Vector<4> trans = Vector<4>(tx, ty, tz, tw);
        
    for (unsigned t = 0; t <= tsteps+1; t++) {
        for (unsigned u = 0; u <= usteps+1; u++) 
            for (unsigned v = 0; v <= vsteps+1; v++)
	            Xtrans[t][u][v] = (Rot*X[t][u][v])+trans;
  }
}


/*******************************************************************************
 *  projects a Function into three-space
 *  @param scr_w	w coordinate of screen
 *  @param cam_w	w coordinate of camera
 *  @param depthcue4d	wheter to use hyperfog/dc
 */
void Function::Project (double scr_w, double cam_w, bool depthcue4d) {
    double ProjectionFactor;
    double Wmax = 0, Wmin = 0;

    for (unsigned t = 0; t <= tsteps+1; t++) {
        for (unsigned u = 0; u <= usteps+1; u++) {
            for (unsigned v = 0; v <= vsteps+1; v++) {

            	if (Xtrans[t][u][v][3] < Wmin) Wmin = Xtrans[t][u][v][3];
	            if (Xtrans[t][u][v][3] > Wmax) Wmax = Xtrans[t][u][v][3];

	            ProjectionFactor = (scr_w-cam_w)/(Xtrans[t][u][v][3]-cam_w);

	            for (unsigned i = 0; i <= 2; i++) {
	                Xscr[t][u][v][i] = ProjectionFactor*Xtrans[t][u][v][i];
                }

	            R[t][u][v] = float (t)/float (tsteps);                  //      color schemes wanted
	            G[t][u][v] = float (u)/float (usteps);
	            B[t][u][v] = float (v)/float (vsteps);
            }
        }
    }

  if (!depthcue4d) return;

  for (unsigned t = 0; t <= tsteps+1; t++) 
    for (unsigned u = 0; u <= usteps+1; u++) 
      for (unsigned v = 0; v <= vsteps+1; v++) {
	float DepthCueFactor = (Wmax-Xtrans[t][u][v][3])/(Wmax-Wmin)*0.9+0.1; //	HARDCODED! EEEEEYYYYUUUURGHHHHHHH!
	R[t][u][v] = 0.1+(R[t][u][v]-0.1)*DepthCueFactor;
	G[t][u][v] = 0.1+(G[t][u][v]-0.1)*DepthCueFactor;
	B[t][u][v] = 0.1+(B[t][u][v]-0.1)*DepthCueFactor;
      }
}


/*******************************************************************************
 *  draw the projected Function (onto screen or into GL list, as it is)
 */
void Function::Draw (void) {
  for (unsigned t = 0; t < tsteps; t++) 
    DrawPlane (t);
}

        
/*******************************************************************************
 *  draw the current plane of the projected Function
 *  @param t	current t value
 */
void Function::DrawPlane (unsigned t){
  for (unsigned u = 0; u < usteps; u++) 
    DrawStrip (t, u);
}


/*******************************************************************************
 *  draw the current strip of the projected Function
 *  @param t	current t value
 *  @param u	current u value
 */
void Function::DrawStrip (unsigned t, unsigned u){
  for (unsigned v = 0; v < vsteps; v++) 
    DrawCube (t, u, v);
}

using std::string;
using std::setw;
using std::setprecision;
/*******************************************************************************
 *  draw the current cube or cell of the projected Function
 *  @param t	current t value
 *  @param u	current u value
 *  @param v	current v value
 */
void Function::DrawCube (unsigned t, unsigned u, unsigned v) {
    static Vector<3> *V = new Vector<3> [8];

  V[0] = Xscr[t][u][v];     V[1] = Xscr[t][u][v+1];
  V[2] = Xscr[t][u+1][v];   V[3] = Xscr[t][u+1][v+1];
  V[4] = Xscr[t+1][u][v];   V[5] = Xscr[t+1][u][v+1];
  V[6] = Xscr[t+1][u+1][v]; V[7] = Xscr[t+1][u+1][v+1];

#if 0
  cerr << "Function::DrawCube(" << t << ", " << u << ", " << v << "): " << endl
          << string(8, ' ') << setw(6) << setprecision(2) << V[3] << string(32, ' ') << V[7] << endl
          << endl;
#endif
  glBegin (GL_QUAD_STRIP);
    if (t == 0) {
      SetColor (R [t][u][v], G [t][u][v], B [t][u][v]);
      glVertex (V[0]);
      SetColor (R [t][u][v+1], G [t][u][v+1], B [t][u][v+1]); 
      glVertex (V[1]);
      NumVertices += 2;
    }
    SetColor (R [t][u+1][v], G [t][u+1][v], B [t][u+1][v]); 
    glVertex (V[2]);
    SetColor (R [t][u+1][v+1], G [t][u+1][v+1], B [t][u+1][v+1]);   
    glVertex (V[3]);
    SetColor (R [t+1][u+1][v], G [t+1][u+1][v], B [t+1][u+1][v]);   
    glVertex (V[6]);
    SetColor (R [t+1][u+1][v+1], G [t+1][u+1][v+1], B [t+1][u+1][v+1]);     
    glVertex (V[7]);
    SetColor (R [t+1][u][v], G [t+1][u][v], B [t+1][u][v]); 
    glVertex (V[4]);
    SetColor (R [t+1][u][v+1], G [t+1][u][v+1], B [t+1][u][v+1]);   
    glVertex (V[5]);             
    NumVertices += 6;
    if (u == 0) {
      SetColor (R [t][u][v], G [t][u][v], B [t][u][v]);       
      glVertex (V[0]);
      SetColor (R [t][u][v+1], G [t][u][v+1], B [t][u][v+1]); 
      glVertex (V[1]);
      NumVertices += 2;
    }
  glEnd ();
  
  glBegin (GL_QUADS);
    if (v == 0) {   
      SetColor (R [t][u][v], G [t][u][v], B [t][u][v]);       
      glVertex (V[0]);
      SetColor (R [t][u+1][v], G [t][u+1][v], B [t][u+1][v]); 
      glVertex (V[2]);
      SetColor (R [t+1][u+1][v], G [t+1][u+1][v], B [t+1][u+1][v]);   
      glVertex (V[6]);
      SetColor (R [t+1][u][v], G [t+1][u][v], B [t+1][u][v]); 
      glVertex (V[4]);
      NumVertices += 4;
    }
    SetColor (R [t][u][v+1], G [t][u][v+1], B [t][u][v+1]); 
    glVertex (V[1]);
    SetColor (R [t][u+1][v+1], G [t][u+1][v+1], B [t][u+1][v+1]);   
    glVertex (V[3]);
    SetColor (R [t+1][u+1][v+1], G [t+1][u+1][v+1], B [t+1][u+1][v+1]);     
    glVertex (V[7]);
    SetColor (R [t+1][u][v+1], G [t+1][u][v+1], B [t+1][u][v+1]);   
    glVertex (V[5]);
    NumVertices += 4;
  glEnd ();
}


////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Hypersphere c'tor given a definition set in R³ (as parameter space) and a
 *  radius
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _rad		radius
 */
Hypersphere::Hypersphere (double _tmin, double _tmax, double _dt,
			  double _umin, double _umax, double _du,
			  double _vmin, double _vmax, double _dv,
			  double _rad):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  Radius (_rad){
  Initialize ();
}


/*******************************************************************************
 *  Hypersphere destructor
 */
Hypersphere::~Hypersphere () { }



/*******************************************************************************
 *  Hypersphere defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &Hypersphere::f (double tt, double uu, double vv) {
  double sinphi = sin (pi/2*tt), cosphi = cos (pi/2*tt),	//  hypersphere
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv);
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;

  return F; 
}


/*******************************************************************************
 *  calculate normal to function at a given point in definition set
 *  overridden because it's much easier to calculate
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		surface normal, normalized
 */
Vector<4> &Hypersphere::normal (double tt, double uu, double vv) {
    static Vector<4> n;

  n = f (tt, uu, vv);
  vnormalize (n);

  return n; 
}


///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Torus1 c'tor given a definition set in R³ (as parameter space) and three
 *  radii: major, minor and... what'sitcalled... subminor
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _R		major radius
 *  @param _r		minor radius
 *  @param _rho		subminor radius
 */
Torus1::Torus1 (double _tmin, double _tmax, double _dt,
		double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _R, double _r, double _rho):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  R (_R), r (_r), rho (_rho) {
  Initialize ();
}


/*******************************************************************************
 *  Torus1 destructor
 */
Torus1::~Torus1 () { }


/*******************************************************************************
 *  Torus1 defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &Torus1::f (double tt, double uu, double vv) {
  F[0] =  cos (pi*tt)*(R+cos (pi*uu)*(r+rho*cos (pi*vv))); 
  F[1] =  sin (pi*tt)*(R+cos (pi*uu)*(r+rho*cos (pi*vv))); 
  F[2] =  sin (pi*uu)*(r+rho*cos (pi*vv));  
  F[3] =  rho*sin (pi*vv);   

  return F; 
}


///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Torus2 c'tor given a definition set in R³ (as parameter space) and two
 *  radii - a major and a minor (defining a sphere)
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _R		major radius
 *  @param _r		minor radius
 */
Torus2::Torus2 (double _tmin, double _tmax, double _dt,
		double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _R, double _r):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  R (_R), r (_r) {
  Initialize ();
}


/*******************************************************************************
 *  Torus2 destructor
 */
Torus2::~Torus2 () { }


/*******************************************************************************
 *  Torus2 defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &Torus2::f (double tt, double uu, double vv) {
  F[0] =  cos (pi*tt)*(R+r*cos (pi*uu)*cos (pi*vv)); 
  F[1] =  cos (pi*tt)*(R+r*cos (pi*uu)*sin (pi*vv)); 
  F[2] =  cos (pi*tt)*(R+r*sin (pi*uu));
  F[3] =  sin (pi*tt)*R;								  

  return F; 
}


////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Fr3r (example R³->R function) c'tor given a definition set in R³
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Fr3r::Fr3r (double _tmin, double _tmax, double _dt,
	    double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}


/*******************************************************************************
 *  Fr3r destructor
 */
Fr3r::~Fr3r () {}


/*******************************************************************************
 *  Fr3r defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &Fr3r::f (double tt, double uu, double vv) {
  F[0] = tt;
  F[1] = uu;
  F[2] = vv;
  double rsq = tt*tt+uu*uu+vv*vv; 
  F[3] = 1./(rsq+.25);
  // sin (pi*(tt*tt+uu*uu+vv*vv));
  // exp (tt*tt+uu*uu+vv*vv);														

  return F; }


////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  GravitationPotential c'tor given a definition set in R³ (as parameter space),
 *  a mass and a radius of a spherical mass
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _M		Mass
 *  @param _R		radius
 */
GravitationPotential::GravitationPotential (double xmin, double xmax, double dx,
					    double ymin, double ymax, double dy,
					    double zmin, double zmax, double dz,
					    double _M, double _R):
  Function (xmin, xmax, dx, ymin, ymax, dy, zmin, zmax, dz),
  M (_M), R (_R) {
  Initialize ();
}


/*******************************************************************************
 *  Hypersphere destructor
 */
GravitationPotential::~GravitationPotential () { }


/*******************************************************************************
 *  Hypersphere defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &GravitationPotential::f (double tt, double uu, double vv) {
  const double G = 1;		//  arbitrary value for gravitation constant
  F[0] = tt;
  F[1] = uu;
  F[2] = vv;
  double rsq = tt*tt+uu*uu+vv*vv;
  if (rsq > R*R)
    F[3] = G*M/rsq;
  else 
    F[3] = G*M/(R*R*R)*sqrt (rsq);

  return F; 
}


///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Fr3rSin c'tor given a definition set in R³ (as parameter space)
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Fr3rSin::Fr3rSin (double _tmin, double _tmax, double _dt,
		  double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}


/*******************************************************************************
 *  Fr3rSin destructor
 */
Fr3rSin::~Fr3rSin () { }
 
 
/*******************************************************************************
 *  Fr3rSin defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		sin (pi*(x²+y²+z²))
 */
Vector<4> &Fr3rSin::f (double tt, double uu, double vv) {
  F[0] = tt;
  F[1] = uu;
  F[2] = vv;
  F[3] = sin (pi*(tt*tt+uu*uu+vv*vv));

  return F;
}


///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Fr3rExp c'tor given a definition set in R³ (as parameter space)
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Fr3rExp::Fr3rExp (double _tmin, double _tmax, double _dt,
		  double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}


/*******************************************************************************
 *  Fr3rExp destructor
 */
Fr3rExp::~Fr3rExp () { }
 
 
/*******************************************************************************
 *  Fr3rExp defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		exp (x²+y²+z²)
 */
Vector<4> &Fr3rExp::f (double tt, double uu, double vv) {
  F[0] = tt;
  F[1] = uu;
  F[2] = vv;
  F[3] = exp (tt*tt+uu*uu+vv*vv);														
 
  return F; }
 
 
///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Polar (example polar function) c'tor given a definition set in [t, u, v]
 *  as parameter space
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Polar::Polar (double _tmin, double _tmax, double _dt,
	      double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}


/*******************************************************************************
 *  Polar destructor
 */
Polar::~Polar () { }


/*******************************************************************************
 *  Polar defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector<4> &Polar::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),	
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = sin (pi/3.*(tt+uu+vv));
 
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;
 
  return F; 
}
 
 
///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  PolarSin c'tor given a definition set in R³ (as parameter space) and a
 *  phase
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _phase	phase
 */
PolarSin::PolarSin (double _tmin, double _tmax, double _dt,
		    double _umin, double _umax, double _du,
		    double _vmin, double _vmax, double _dv,
		    double _phase):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  Phase (_phase) {
  Initialize ();
}


/*******************************************************************************
 *  PolarSin destructor
 */
PolarSin::~PolarSin () { }


/*******************************************************************************
 *  PolarSin defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		r = 1/2 + |sin (pi*phase*theta*phi*psi)|
 */
Vector<4> &PolarSin::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),	
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = .5+fabs (sin (Phase*tt*uu*vv*pi));
 
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;
 
  return F; 
}
 

///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  PolarSin2 c'tor given a definition set in R³ (as parameter space)
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
PolarSin2::PolarSin2 (double _tmin, double _tmax, double _dt,
		      double _umin, double _umax, double _du,
		      double _vmin, double _vmax, double _dv):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
  Initialize ();
}


/*******************************************************************************
 *  PolarSin2 destructor
 */
PolarSin2::~PolarSin2 () { }


/*******************************************************************************
 *  PolarSin2 defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		r = sin (pi/3*(phi+theta+psi))
 */
Vector<4> &PolarSin2::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),	
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = sin (pi/3.*(tt+uu+vv));
 
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;
 
  return F; 
}
 

///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  PolarR c'tor given a definition set in R³ (as parameter space) and a
 *  phase
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _phase	phase
 */
PolarR::PolarR (double _tmin, double _tmax, double _dt,
		double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv,
		double _phase):
  Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
  Phase (_phase) {
  Initialize ();
}
 
/*******************************************************************************
 *  PolarR destructor
 */
PolarR::~PolarR () { }
 
/*******************************************************************************
 *  PolarR defining function
 *  @param tt		t value
 *  @param uu		u value
 *  @param vv		v value
 *  @return		r = sqrt (phi²+theta²+psi²)
 */
Vector<4> &PolarR::f (double tt, double uu, double vv) {
  double sinphi = sin (pi*tt), cosphi = cos (pi*tt),	
    sintht = sin (pi*uu), costht = cos (pi*uu),
    sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
    Radius = sqrt (tt*tt+uu*uu+vv*vv);
 
  F[0] = Radius*sinpsi*sintht*cosphi;
  F[1] = Radius*sinpsi*sintht*sinphi;
  F[2] = Radius*sinpsi*costht;
  F[3] = Radius*cospsi;
 
  return F; 
}


