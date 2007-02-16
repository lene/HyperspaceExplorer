
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "Globals.H"

#include "Surface.H"
#include "Matrix.H"

unsigned int Delete (void *x);		// defined in Function.C


////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Surface default c'tor
 *  zeroes everything
 */
Surface::Surface ():
    umin (0),	umax (0),	du (0),
    vmin (0),	vmax (0),	dv (0),
    usteps (0), vsteps (0),
    NumVertices (0),
    F (4),
    Xscr (NULL), Xtrans (NULL), XscrChunk (NULL), XtransChunk (NULL),
    R (NULL), G (NULL), B (NULL), RGBChunk (NULL) { }


/*******************************************************************************
 *  Function c'tor given a definition set in R� (as parameter space)
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
Surface::Surface (double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv):
    umin (_umin),	umax (_umax),	du (_du/2),
    vmin (_vmin),	vmax (_vmax),	dv (_dv/2),
    usteps (unsigned (2*(umax-umin)/du+1)), vsteps (unsigned (2*(vmax-vmin)/dv+1)),
    NumVertices (0),
    F (4),
    Xscr (NULL), Xtrans (NULL), XscrChunk (NULL), XtransChunk (NULL),
    R (NULL), G (NULL), B (NULL), RGBChunk (NULL) { }


/*******************************************************************************
 *  Initialize the temporary storage areas Xscr[][], Xtrans[][], 
 *                                         R[][], G[][], B[][]
 */
void Surface::InitMem (void) {
    XscrChunk = new Vector [(usteps+2)*(vsteps+2)];
    Xscr = new Vector * [usteps+2];
	
    XtransChunk = new Vector [(usteps+2)*(vsteps+2)];
    Xtrans = new Vector * [usteps+2];

    RGBChunk = new float [3*(usteps+2)*(vsteps+2)];
    R = new float * [usteps+2];
    G = new float * [usteps+2];
    B = new float * [usteps+2];

    for (unsigned u = 0; u <= usteps+1; u++) {
	
	Xscr[u]   = XscrChunk+u*(usteps+2);
	Xtrans[u] = XtransChunk+u*(usteps+2);

	R[u] = RGBChunk+1*u*(usteps+2);
	G[u] = RGBChunk+2*u*(usteps+2);
	B[u] = RGBChunk+3*u*(usteps+2);
    }			//	for (unsigned u = 0; u <= usteps+1; u++) 
}			//	Initialize ()


/*******************************************************************************
 *  allocate and initialize X[][] with values of f()
 *  call InitMem () above
 */
void Surface::Initialize () {
    X = new Vector * [usteps+2];
    Xchunk = new Vector   [(usteps+2)*(vsteps+2)];

    for (unsigned u = 0; u <= usteps+1; u++) {
	X[u]  =  Xchunk+u*(vsteps+2);
	for (unsigned v = 0; v <= vsteps+1; v++) {
	    X[u][v] = f (umin+u*du, vmin+v*dv);
	}
    }

    InitMem ();
}


/*******************************************************************************
 *  placeholder for function to set parameters in descendants - empty because
 *  generic function has no parameters
 *  @param _a		1st parameter
 *  @param _b		2nd parameter
 *  @param _c		3rd parameter
 *  @param _d		4th parameter
 */
void Surface::SetParameters (double _a, double _b, double _c, double _d) { }


/*******************************************************************************
 *  re-initialize a Surface if the definition set has changed
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
void Surface::ReInit(double _tmin, double _tmax, double _dt,
		     double _umin, double _umax, double _du,
		     double _vmin, double _vmax, double _dv) {
    umin = _umin;	umax = _umax;	du = _du;
    vmin = _vmin;	vmax = _vmax;	dv = _dv;
    usteps = unsigned ((umax-umin)/du+1); vsteps = unsigned ((vmax-vmin)/dv+1);
	
	//	Free ();
	//	Delete (Xchunk); Delete (XscrChunk); Delete (XtransChunk);
    Delete (X); Delete (Xscr); Delete (Xtrans); Delete (R);
    Initialize ();
}


/*******************************************************************************
 *  auxiliary function to safely free all member arrays
 */
void Surface::Free (void) {
    for (unsigned u = 0; u <= usteps+1; u++) {
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
unsigned long Surface::MemRequired (void) {
    return (tsteps+2)*(usteps+2);
}


/*******************************************************************************
 *  Surface destructor
 */
Surface::~Surface() {
    Free ();
}


/*******************************************************************************
 *  calculate normal to function at a given point in definition set
 *  no further assumption is made than that f () is continuous
 *  this function is not yet used anywhere, but i like it
 *  @param uu		u value
 *  @param vv		v value
 *  @return		surface normal, normalized
 */
Vector &Surface::normal (double uu, double vv) {
    static Vector n;

    Vector *D = df (uu, vv);

    n = vcross (D[0], D[1], D[2]);
    vnormalize (n);

    return n; 
}


/*******************************************************************************
 *  numerical calculation of the derivatives in u and v:
 *
 *		df	  f(u+h, v) - f (u)   df
 *		-- =  lim -----------------,  -- analogously
 *		du   h->0      	  h   	      dv
 *
 *  @param uu		u value
 *  @param vv		v value
 *  @return		gradient in t, u and v as array
*/
Vector *Surface::df (double uu, double vv) {	

    static Vector F0 (3);					//	f (u, v)
    static double h = 1e-5;					//	maybe tweak to get best results

    static Vector DF[3];

    F0 = operator () (uu, vv);							

    F = operator () (uu+h, vv);					//	derive after u
    DF[0] = (F-F0)/h;			

    F = operator () (uu, vv+h);					//	derive after v
    DF[1] = (F-F0)/h;

    DF[2] = (F-F0)/h;						//	are you sure this is correct?

    return DF; }


/*******************************************************************************
 *  transforms a Surface
 *  as I look at it, i think this could be optimized by making the transformation
 *  matrices static and only canging the corresponding entries... but how to
 *  make this beautifully, i don't know
 *  @param thetaxy	rotation around xy plane (z axis);  ignored because 3D rotation takes care of it
 *  @param thetaxz	rotation around xz plane (y axis);  ignored because 3D rotation takes care of it
 *  @param thetaxw	rotation around xw plane
 *  @param thetayz	rotation around xy plane (x axis);  ignored because 3D rotation takes care of it
 *  @param thetayw	rotation around yw plane
 *  @param thetazw	rotation around zw plane
 *  @param tx		translation in x direction
 *  @param ty		translation in y direction
 *  @param tz		translation in z direction
 *  @param tw		translation in w direction
 */
void Surface::Transform (double thetaxy, double thetaxz, double thetaxw, double thetayz, double thetayw, double thetazw,
			 double tx, double ty, double tz, double tw) {
    matrix<4> Rxw = matrix<4> (0, 3, thetaxw), Ryw = matrix<4> (1, 3, thetayw), Rzw = matrix<4> (2, 3, thetazw),
	Rxwyw = Rxw*Ryw, Rot = Rxwyw*Rzw;
    Vector trans = Vector (4, tx, ty, tz, tw);
	
    for (unsigned u = 0; u <= usteps+1; u++) 
	for (unsigned v = 0; v <= vsteps+1; v++)
	    Xtrans[u][v] = (Rot*X[u][v])+trans;
}


/*******************************************************************************
 *  projects a Surface into three-space
 *  @param scr_w	w coordinate of screen
 *  @param cam_w	w coordinate of camera
 *  @param depthcue4d	wheter to use hyperfog/dc
 */
void Surface::Project (double scr_w, double cam_w, bool depthcue4d) {
    double ProjectionFactor;
    double Wmax = 0, Wmin = 0;

    for (unsigned u = 0; u <= usteps+1; u++) 
	for (unsigned v = 0; v <= vsteps+1; v++) {

	    if (Xtrans[u][v][3] < Wmin) Wmin = Xtrans[u][v][3];
	    if (Xtrans[u][v][3] > Wmax) Wmax = Xtrans[u][v][3];

	    ProjectionFactor = (scr_w-cam_w)/(Xtrans[u][v][3]-cam_w);

	    for (unsigned i = 0; i <= 2; i++)
		Xscr[u][v][i] = ProjectionFactor*Xtrans[u][v][i];

	    R[u][v] = float (u)/float (usteps);
	    G[u][v] = float (v)/float (vsteps);
	    B[u][v] = (Wmax-X[u][v][3])/(Wmax-Wmin);
	}

    if (!depthcue4d) return;

    for (unsigned u = 0; u <= usteps+1; u++) 
	for (unsigned v = 0; v <= vsteps+1; v++) {
	    float DepthCueFactor = (Wmax-Xtrans[u][v][3])/(Wmax-Wmin)*0.9+0.1; //	??? !!!
	    R[u][v] = 0.1+(R[u][v]-0.1)*DepthCueFactor;
	    G[u][v] = 0.1+(G[u][v]-0.1)*DepthCueFactor;
	    B[u][v] = 0.1+(B[u][v]-0.1)*DepthCueFactor;
	}
}


/*******************************************************************************
 *  draw the projected Surface (onto screen or into GL list, as it is)
 */
void Surface::Draw (void) {
    NumVertices = 0;

    for (unsigned u = 0; u < usteps; u++) 
	DrawStrip (u);
}


/*******************************************************************************
 *  draw the current strip of the projected Function
 *  @param u	current u value
 */
void Surface::DrawStrip (unsigned u){
    glBegin (GL_QUAD_STRIP);

    SetColor (R [u][0], G [u][0], B [u][0]);	
    glVertex (Xscr[u][0]);
    SetColor (R [u+1][0], G [u+1][0], B [u+1][0]);	
    glVertex (Xscr[u+1][0]);
    NumVertices += 2;

    for (unsigned v = 1; v <= vsteps; v++) {
	SetColor (R [u][v], G [u][v], B [u][v]);	
	glVertex (Xscr[u][v]);
	SetColor (R [u+1][v], G [u+1][v], B [u+1][v]);	
	glVertex (Xscr[u+1][v]);

	NumVertices += 2;
    }
 		
    glEnd ();
}


    ///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Surface1 c'tor given a definition set in R� (as parameter space) 
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _rad		radius
 */
Surface1::Surface1 (double _umin, double _umax, double _du,
		    double _vmin, double _vmax, double _dv):
    Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
    Initialize ();
}


/*******************************************************************************
 *  Surface1 destructor
 */
Surface1::~Surface1 () { }


/*******************************************************************************
 *  Surface1 defining function
 *  @param uu		u value
 *  @param vv		v value
 *  @return		(sintht*sinpsi, costht*sinpsi, costht, cospsi)
 */
Vector &Surface1::f (double uu, double vv) {
    double sintht = sin (pi*uu), costht = cos (pi*uu),
	sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
	Radius = 1;
    F[0] = Radius*sintht*sinpsi;
    F[1] = Radius*costht*sinpsi;
    F[2] = Radius*costht;
    F[3] = Radius*cospsi;

    return F; 
}


    ///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Horizon c'tor given a definition set in R� (as parameter space) 
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _rad		radius
 */
Horizon::Horizon (double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv):
    Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
    Initialize ();
}

/*******************************************************************************
 *  Horizon destructor
 */
Horizon::~Horizon () { }

/*******************************************************************************
 *  Horizon defining function
 *  @param uu		u value
 *  @param vv		v value
 *  @return		aah, see below
 */
Vector &Horizon::f (double t, double phi) {
    t *= pi; phi *= pi/2;
    F[0] = (1-sin (t))*cos (phi);
    F[1] = (1-sin (t))*sin (phi);
    F[2] = (1+sin (t))*cos (phi);
    F[3] = (1+sin (t))*sin (phi);
    F *= 1./sqrt (2.)*cos (t);

    return F; 
}


    ///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  Torus3 c'tor given a definition set in R� (as parameter space) 
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _rad		radius
 */
Torus3::Torus3 (double _umin, double _umax, double _du,
		double _vmin, double _vmax, double _dv):
    Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
    Initialize ();
}

/*******************************************************************************
 *  Torus3 destructor
 */
Torus3::~Torus3 () { }

/*******************************************************************************
 *  Torus3 defining function
 *  @param uu		u value
 *  @param vv		v value
 *  @return		(costht, sintht, cosphi, sinphi)
 */
Vector &Torus3::f (double theta, double phi) {
    theta *= pi; phi *= pi;
    F[0] = cos (theta);
    F[1] = sin (theta);
    F[2] = cos (phi);
    F[3] = sin (phi);

    return F; 
}



