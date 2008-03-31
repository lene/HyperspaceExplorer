
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "Globals.H"
#include "Matrix.H"
#include "Function.H"
#include "Log.H"

using std::cerr;
using std::endl;

using VecMath::Vector;
using VecMath::Matrix;


//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////


/// Function default c'tor
/** Zeroes everything       */
Function::Function ():
    tmin (0),       tmax (0),       dt (0),
    umin (0),       umax (0),       du (0),
    vmin (0),       vmax (0),       dv (0),
    tsteps (0), usteps (0), vsteps (0),
    NumVertices (0),
    F (),
    Xtrans(vec4vec3D()), Xscr(vec3vec3D()),
    R (floatvec3D()), G (floatvec3D()), B (floatvec3D()),
    functionName(""), parameterNames()
{ }


/** Function c'tor given a definition set in R³ (as parameter space)
 *  @param name a name for the function
 *  @param _tmin minimal value in t
 *  @param _tmax maximal value in t
 *  @param _dt stepsize in t
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Function::Function (const QString &name,
                    double _tmin, double _tmax, double _dt,
                    double _umin, double _umax, double _du,
                    double _vmin, double _vmax, double _dv):
    tmin (_tmin), tmax (_tmax), dt (_dt),
    umin (_umin), umax (_umax), du (_du),
    vmin (_vmin), vmax (_vmax), dv (_dv),
    tsteps (unsigned ((tmax-tmin)/dt+1)),
    usteps (unsigned ((umax-umin)/du+1)),
    vsteps (unsigned ((vmax-vmin)/dv+1)),
    NumVertices (0),
    F (),
    Xtrans(vec4vec3D()), Xscr(vec3vec3D()),
    R (floatvec3D()), G (floatvec3D()), B (floatvec3D()),
    functionName(name), parameterNames() {
    if (MemRequired () > Globals::Instance().getMaxMemory()) {
        cerr << "Using a " << tsteps << "x" << usteps << "x" << vsteps
             << " grid would require approx. " << MemRequired () << " MB of memory.\n";
        while (MemRequired () > Globals::Instance().getMaxMemory()) {
            tsteps--; usteps--; vsteps--;
        }
        cerr << "Using a " << tsteps << "x" << usteps << "x" << vsteps
             << " grid instead." << endl;
        dt = (tmax-tmin)/tsteps;
        du = (umax-umin)/usteps;
        dv = (vmax-vmin)/vsteps;
    }
}


/// Initialize the temporary storage areas
/** Xscr[][][], Xtrans[][][], R[][][], G[][][], B[][][]          */
void Function::InitMem (void) {

    Xscr.resize(tsteps+2);
    Xtrans.resize(tsteps+2);

    R.resize(tsteps+2);
    G.resize(tsteps+2);
    B.resize(tsteps+2);
    for (unsigned t = 0; t <= tsteps+1; t++) {

        Xscr[t].resize(usteps+2);
        Xtrans[t].resize(usteps+2);

        R[t].resize(usteps+2);
        G[t].resize(usteps+2);
        B[t].resize(usteps+2);

        for (unsigned u = 0; u <= usteps+1; u++) {

            Xscr[t][u].resize(vsteps+2);
            Xtrans[t][u].resize(vsteps+2);

            R[t][u].resize(vsteps+2);
            G[t][u].resize(vsteps+2);
            B[t][u].resize(vsteps+2);
        }                                       //      for (unsigned u = 0; u <= usteps+1; u++)

    }                                               //      for (unsigned t = 0; t <= tsteps+1; t++)
}                                                       //      InitiMem ()


/// Allocate and initialize X[][][] with values of f()
/** Call InitMem() above */
void Function::Initialize () {
    X = vec4vec3D(tsteps+2);

    for (unsigned t = 0; t <= tsteps+1; t++) {
        X[t].resize(usteps+2);

        for (unsigned u = 0; u <= usteps+1; u++) {
            X[t][u].resize(vsteps+2);

            for (unsigned v = 0; v <= vsteps+1; v++) {
                    double T = tmin+t*dt, U =umin+u*du, V = vmin+v*dv;
                    X[t][u][v] = f (T, U, V);
            }
        }
    }
    InitMem ();
}


/// Re-initialize a Function if the definition set has changed
/** @param tmin minimal value in t
 *  @param tmax maximal value in t
 *  @param dt stepsize in t
 *  @param umin minimal value in u
 *  @param umax maximal value in u
 *  @param du stepsize in u
 *  @param vmin minimal value in v
 *  @param vmax maximal value in v
 *  @param dv stepsize in v                                                   */
void Function::ReInit(double _tmin, double _tmax, double _dt,
                      double _umin, double _umax, double _du,
                      double _vmin, double _vmax, double _dv) {

    SingletonLog::Instance()  << "Function::ReInit(" << _tmin << ", " << _tmax << ", " << _dt << ", "
	<< _umin << ", " << _umax<< ", " << _du << ", " << _vmin << ", " << _vmax << ", " << _dv << ")\n";

  tmin = _tmin;   tmax = _tmax;   dt = _dt;
  umin = _umin;   umax = _umax;   du = _du;
  vmin = _vmin;   vmax = _vmax;   dv = _dv;
  tsteps = unsigned ((tmax-tmin)/dt+2); usteps = unsigned ((umax-umin)/du+2); vsteps = unsigned ((vmax-vmin)/dv+2);

  Initialize ();
}


/// Placeholder for function to set parameters in descendants
/** Empty because a generic function has no parameters                        */
void Function::SetParameters (double, double, double, double) { }

/// Return the approximate amount of memory needed to display a Function of
/// current definition set
/** \todo uses hardcoded and experimentally found value for memory per cell
 *  @return approx. mem required                                              */
unsigned long Function::MemRequired (void) {
  return ((tsteps+2)*(usteps+2)*(vsteps+2)*4)/1024+8;
}


/// Calculate normal to function at a given point in definition set.
/** No further assumption is made than that f () is continuous. \n
 *  This function is not yet used anywhere, but i like it.
 *  @param tt t value
 *  @param uu u value
 *  @param vv v value
 *  @return surface normal, normalized                                        */
Vector<4> &Function::normal (double tt, double uu, double vv) {
    static Vector<4> n;

    Function::vec4vec1D D = df (tt, uu, vv);

    n = VecMath::vcross (D[0], D[1], D[2]);
    VecMath::vnormalize (n);

    return n;
}


/// Numerical calculation of the derivatives in t, u and v
/** \f[
        \frac{df}{dt} = \lim_{h \rightarrow 0}
            \frac{f(t+h, u, v) - f(t, u, v)}{h},
        \frac{df}{du},\frac{df}{dv}\mbox{analogously}
    \f]
 *  @todo The h value is fixed and hardcoded. better approach, please!
 *  @todo I don't think calling operator() is right. Call f()!
 *  @param tt t value
 *  @param uu u value
 *  @param vv v value
 *  @return gradient in t, u and v as array                                   */
Function::vec4vec1D Function::df (double tt, double uu, double vv) {

    static Vector<4> F0;                //  f (u, v)
    static double h = 1e-5;
    static Function::vec4vec1D DF(3);

    F0 = operator () (tt, uu, vv);

    F = operator () (tt+h, uu, vv);     //  derive after t
    DF[0] = (F-F0)/h;

    F = operator () (tt, uu+h, vv);     //  derive after u
    DF[1] = (F-F0)/h;

    F = operator () (tt, uu, vv+h);     //  derive after v
    DF[2] = (F-F0)/h;

    return DF;
}


/// Transforms a Function
/** \todo As I look at it, i think this could be optimized by making the
 *        transformation matrices static and only canging the corresponding
 *        entries... but how to do this beautifully, i don't know
 *  @param thetaxy rotation around xy plane (z axis); should be ignored because
 *                 3D rotation takes care of it, but isn't
 *  @param thetaxz rotation around xz plane (y axis); should be ignored because
 *                 3D rotation takes care of it, but isn't
 *  @param thetaxw rotation around xw plane
 *  @param thetayz rotation around xy plane (x axis); should be ignored because
 *                 3D rotation takes care of it, but isn't
 *  @param thetayw rotation around yw plane
 *  @param thetazw rotation around zw plane
 *  @param tx translation in x direction
 *  @param ty translation in y direction
 *  @param tz translation in z direction
 *  @param tw translation in w direction                                      */
void Function::Transform (double thetaxy, double thetaxz, double thetaxw,
                          double thetayz, double thetayw, double thetazw,
                          double tx, double ty, double tz, double tw) {
    Matrix<4> Rxy = Matrix<4> (0, 1, thetaxy), Rxz = Matrix<4> (0, 2, thetaxz),
              Rxw = Matrix<4> (0, 3, thetaxw), Ryz = Matrix<4> (1, 2, thetayz),
              Ryw = Matrix<4> (1, 3, thetayw), Rzw = Matrix<4> (2, 3, thetazw),
              Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw,
              Rot = Rxyz*Rxwyz*Ryzw;
    Vector<4> trans = Vector<4>(tx, ty, tz, tw);

    for (unsigned t = 0; t <= tsteps+1; t++) {
        for (unsigned u = 0; u <= usteps+1; u++)
            for (unsigned v = 0; v <= vsteps+1; v++)
                Xtrans[t][u][v] = (Rot*X[t][u][v])+trans;
  }
}


/// Projects a Function into three-space
/** @todo replace hardcoded function to calculate 4D fog color with better one
 *  @param scr_w w coordinate of screen
 *  @param cam_w w coordinate of camera
 *  @param depthcue4d whether to use hyperfog/depth cue                       */
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


/// Draw the projected Function (onto screen or into GL list, as it is)
/** */
void Function::Draw (void) {
  for (unsigned t = 0; t < tsteps; t++)
    DrawPlane (t);
}


/// Draw the current plane of the projected Function
/** @param t current t value                                                  */
void Function::DrawPlane (unsigned t){
  for (unsigned u = 0; u < usteps; u++)
    DrawStrip (t, u);
}


/// Draw the current strip of the projected Function
/** @param t current t value
 *  @param u current u value                                                  */
void Function::DrawStrip (unsigned t, unsigned u){
  for (unsigned v = 0; v < vsteps; v++)
    DrawCube (t, u, v);
}

using std::string;
using std::setw;
using std::setprecision;
/// Draw the current cube or cell of the projected Function
/** @param t current t value
 *  @param u current u value
 *  @param v current v value                                                  */
void Function::DrawCube (unsigned t, unsigned u, unsigned v) {
    static Vector<3> *V = new Vector<3> [8];

  V[0] = Xscr[t][u][v];     V[1] = Xscr[t][u][v+1];
  V[2] = Xscr[t][u+1][v];   V[3] = Xscr[t][u+1][v+1];
  V[4] = Xscr[t+1][u][v];   V[5] = Xscr[t+1][u][v+1];
  V[6] = Xscr[t+1][u+1][v]; V[7] = Xscr[t+1][u+1][v+1];

    glBegin (GL_QUAD_STRIP);
        if (t == 0) {
            Globals::Instance().setColor(R[t][u][v], G[t][u][v], B[t][u][v]);
            Globals::Instance().glVertex(V[0]);
            Globals::Instance().setColor(R[t][u][v+1], G[t][u][v+1], B[t][u][v+1]);
            Globals::Instance().glVertex(V[1]);
            NumVertices += 2;
        }
        Globals::Instance().setColor(R[t][u+1][v], G[t][u+1][v], B[t][u+1][v]);
        Globals::Instance().glVertex(V[2]);
        Globals::Instance().setColor(R[t][u+1][v+1], G[t][u+1][v+1], B[t][u+1][v+1]);
        Globals::Instance().glVertex(V[3]);
        Globals::Instance().setColor(R[t+1][u+1][v], G[t+1][u+1][v], B[t+1][u+1][v]);
        Globals::Instance().glVertex(V[6]);
        Globals::Instance().setColor(R[t+1][u+1][v+1], G[t+1][u+1][v+1], B[t+1][u+1][v+1]);
        Globals::Instance().glVertex(V[7]);
        Globals::Instance().setColor(R[t+1][u][v], G[t+1][u][v], B[t+1][u][v]);
        Globals::Instance().glVertex(V[4]);
        Globals::Instance().setColor(R[t+1][u][v+1], G[t+1][u][v+1], B[t+1][u][v+1]);
        Globals::Instance().glVertex(V[5]);
        NumVertices += 6;
        if (u == 0) {
            Globals::Instance().setColor(R[t][u][v], G[t][u][v], B[t][u][v]);
            Globals::Instance().glVertex(V[0]);
            Globals::Instance().setColor(R[t][u][v+1], G[t][u][v+1], B[t][u][v+1]);
            Globals::Instance().glVertex(V[1]);
            NumVertices += 2;
        }
    glEnd ();

    glBegin (GL_QUADS);
        if (v == 0) {
            Globals::Instance().setColor(R[t][u][v], G[t][u][v], B[t][u][v]);
            Globals::Instance().glVertex(V[0]);
            Globals::Instance().setColor(R[t][u+1][v], G[t][u+1][v], B[t][u+1][v]);
            Globals::Instance().glVertex(V[2]);
            Globals::Instance().setColor(R[t+1][u+1][v], G[t+1][u+1][v], B[t+1][u+1][v]);
            Globals::Instance().glVertex(V[6]);
            Globals::Instance().setColor(R[t+1][u][v], G[t+1][u][v], B[t+1][u][v]);
            Globals::Instance().glVertex(V[4]);
            NumVertices += 4;
        }
        Globals::Instance().setColor(R[t][u][v+1], G[t][u][v+1], B[t][u][v+1]);
        Globals::Instance().glVertex(V[1]);
        Globals::Instance().setColor(R[t][u+1][v+1], G[t][u+1][v+1], B[t][u+1][v+1]);
        Globals::Instance().glVertex(V[3]);
        Globals::Instance().setColor(R[t+1][u+1][v+1], G[t+1][u+1][v+1], B[t+1][u+1][v+1]);
        Globals::Instance().glVertex(V[7]);
        Globals::Instance().setColor(R[t+1][u][v+1], G[t+1][u][v+1], B[t+1][u][v+1]);
        Globals::Instance().glVertex(V[5]);
        NumVertices += 4;
    glEnd ();
}


////////////////////////////////////////////////////////////////////////////////
