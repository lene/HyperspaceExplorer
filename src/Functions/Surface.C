
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:       helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)


#include "Globals.H"
#include "ColorManager.H"

#include "Matrix.H"
#include "Surface.H"

using VecMath::Vector;
using VecMath::Matrix;

////////////////////////////////////////////////////////////////////////////////

/** Surface default c'tor \n
 *  zeroes everything    */
Surface::Surface ():
    umin (0), umax (0), du (0),
    vmin (0), vmax (0), dv (0),
    usteps (0), vsteps (0),
    NumVertices (0),
    F (4),
    Xtrans(vec4vec2D()), Xscr(vec3vec2D()) { }


/** Surface c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Surface::Surface (const QString &name,
                  double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv):
    umin (_umin), umax (_umax), du (_du/2),
    vmin (_vmin), vmax (_vmax), dv (_dv/2),
    usteps (unsigned (2*(umax-umin)/du+1)),
    vsteps (unsigned (2*(vmax-vmin)/dv+1)),
    NumVertices (0),
    F (4),
    Xtrans(vec4vec2D()), Xscr(vec3vec2D()) {
    functionName = name;
}

/** Initialize the temporary storage areas Xscr[][], Xtrans[][],
 *                                         R[][], G[][], B[][]                */
void Surface::InitMem (void) {
    Xscr.resize(usteps+2);
    Xtrans.resize(usteps+2);

    for (unsigned u = 0; u <= usteps+1; u++) {
        Xscr[u].resize(vsteps+2);
        Xtrans[u].resize(vsteps+2);
    }
}

/** allocate and initialize X[][] with values of f() \n
 *  call InitMem () above                                                     */
void Surface::Initialize () {
    double Wmax = 0, Wmin = 0;
    X = vec4vec2D(usteps+2);
    ColMgrMgr::Instance().setFunction(this);
    for (unsigned u = 0; u <= usteps+1; u++) {
        X[u].resize(vsteps+2);
        for (unsigned v = 0; v <= vsteps+1; v++) {
            X[u][v] = f (umin+u*du, vmin+v*dv);
            if (X[u][v][3] < Wmin) Wmin = X[u][v][3];
            if (X[u][v][3] > Wmax) Wmax = X[u][v][3];
        }
    }
    for (unsigned u = 0; u <= usteps+1; u++) {
        for (unsigned v = 0; v <= vsteps+1; v++) {
            ColMgrMgr::Instance().calibrateColor(
                X[u][v],
                Color(float(u)/float(usteps), float(v)/float(vsteps),
                      (Wmax-X[u][v][3])/(Wmax-Wmin)));
        }
    }

    InitMem ();
}

/** placeholder for function to set parameters in descendants - empty because
 *  generic function has no parameters
 *  @param _a 1st parameter
 *  @param _b 2nd parameter
 *  @param _c 3rd parameter
 *  @param _d 4th parameter                                                   */
void Surface::SetParameters (double, double, double, double) { }

/** re-initialize a Surface if the definition set has changed
 *  @param tmin minimal value in t (ignored)
 *  @param tmax maximal value in t (ignored)
 *  @param dt stepsize in t (ignored)
 *  @param umin minimal value in u
 *  @param umax maximal value in u
 *  @param du stepsize in u
 *  @param vmin minimal value in v
 *  @param vmax maximal value in v
 *  @param dv stepsize in v                                                   */
void Surface::ReInit(double, double, double,
                     double _umin, double _umax, double _du,
                     double _vmin, double _vmax, double _dv) {
    umin = _umin; umax = _umax; du = _du;
    vmin = _vmin; vmax = _vmax; dv = _dv;
    usteps = unsigned ((umax-umin)/du+1); vsteps = unsigned ((vmax-vmin)/dv+1);

    Initialize ();
}

/** return the approximate amount of memory needed to display a Function of
 *  current definition set \n
 *  uses hardcoded and experimentally found value for memory per cell - ICK!
 *  @return approx. mem required                                              */
unsigned long Surface::MemRequired (void) {
    return (vsteps+2)*(usteps+2);
}

/** calculate normal to function at a given point in definition set \n
 *  no further assumption is made than that f () is continuous \n
 *  this function is not yet used anywhere, but i like it
 *  @param uu u value
 *  @param vv v value
 *  @return surface normal, normalized                                        */
Vector<4> &Surface::normal (double uu, double vv) {
    static Vector<4> n;

    Function::vec4vec1D D = df (uu, vv);

    n = VecMath::vcross (D[0], D[1], D[2]);
    VecMath::vnormalize (n);

    return n;
}

/** numerical calculation of the derivatives in u and v:
    \f[
        \frac{df}{du} = \lim_{h \rightarrow 0}
            \frac{f(u+h, v) - f(u, v)}{h},
        \frac{df}{dv}\mbox{analogously}
    \f]
 *
 *  @param uu u value
 *  @param vv v value
 *  @return gradient in t, u and v as array                                   */
Function::vec4vec1D Surface::df (double uu, double vv) {

    static Vector<4> F0;        //  f (u, v)
    static double h = 1e-5;     //  maybe tweak to get best results

    static Function::vec4vec1D DF(3);

    F0 = operator () (uu, vv);

    F = operator () (uu+h, vv); //  derive after u
    DF[0] = (F-F0)/h;
    F = operator () (uu, vv+h); //  derive after v
    DF[1] = (F-F0)/h;
    DF[2] = (F-F0)/h;           //  are you sure this is correct?

    return DF;
}

/** transforms a Surface \n
 *  as I look at it, i think this could be optimized by making the transformation
 *  matrices static and only canging the corresponding entries... but how to
 *  make this beautifully, i don't know
 *  @param thetaxy rotation around xy plane (z axis);  ignored because 3D rotation takes care of it
 *  @param thetaxz rotation around xz plane (y axis);  ignored because 3D rotation takes care of it
 *  @param thetaxw rotation around xw plane
 *  @param thetayz rotation around xy plane (x axis);  ignored because 3D rotation takes care of it
 *  @param thetayw rotation around yw plane
 *  @param thetazw rotation around zw plane
 *  @param tx translation in x direction
 *  @param ty translation in y direction
 *  @param tz translation in z direction
 *  @param tw translation in w direction                                      */
void Surface::Transform (double, double, double thetaxw,
                         double, double thetayw, double thetazw,
                         double tx, double ty, double tz, double tw) {
    Matrix<4> Rxw = Matrix<4> (0, 3, thetaxw),
              Ryw = Matrix<4> (1, 3, thetayw),
              Rzw = Matrix<4> (2, 3, thetazw),
              Rxwyw = Rxw*Ryw, Rot = Rxwyw*Rzw;
    Vector<4> trans = Vector<4> (tx, ty, tz, tw);

    for (unsigned u = 0; u <= usteps+1; u++)
        for (unsigned v = 0; v <= vsteps+1; v++)
            Xtrans[u][v] = (Rot*X[u][v])+trans;
}

/** projects a Surface into three-space
 *  @param scr_w w coordinate of screen
 *  @param cam_w w coordinate of camera
 *  @param depthcue4d wheter to use hyperfog/depth cue                        */
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
    }

    if (!depthcue4d) return;

    for (unsigned u = 0; u <= usteps+1; u++)
        for (unsigned v = 0; v <= vsteps+1; v++) {
            ColMgrMgr::Instance().depthCueColor(Wmax, Wmin,
                    Xtrans[u][v][3],
                    X[u][v]);
        }
}


/** draw the projected Surface (onto screen or into GL list, as it is)        */
void Surface::Draw (void) {
    NumVertices = 0;

    for (unsigned u = 0; u < usteps; u++)
        DrawStrip (u);
}


/** draw the current strip of the projected Surface
 *  @param u current u value                                                  */
void Surface::DrawStrip (unsigned u){
    glBegin (GL_QUAD_STRIP);

    setVertex(X[u][0], Xscr[u][0]);
    setVertex(X[u+1][0], Xscr[u+1][0]);
    NumVertices += 2;

    for (unsigned v = 1; v <= vsteps; v++) {
        setVertex(X[u][v], Xscr[u][v]);
        setVertex(X[u+1][v], Xscr[u+1][v]);
        NumVertices += 2;
    }

    glEnd ();
}


///////////////////////////////////////////////////////////////////////////////


/** Surface1 c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Surface1::Surface1 (double _umin, double _umax, double _du,
                    double _vmin, double _vmax, double _dv):
        Surface ("Surface 1", _umin, _umax, _du, _vmin, _vmax, _dv) {
    Initialize ();
}

/** Surface1 defining function
 *  @param uu u value
 *  @param vv v value
 *  @return (sintht*sinpsi, costht*sinpsi, costht, cospsi)                    */
Vector<4> &Surface1::f (double uu, double vv) {
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


/** Horizon c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v                                                  */
Horizon::Horizon (double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv):
    Surface ("Horizon", _umin, _umax, _du, _vmin, _vmax, _dv) {
    Initialize ();
}

/** Horizon defining function
 *  @param uu u value
 *  @param vv v value
 *  @return aah, see below */
Vector<4> &Horizon::f (double t, double phi) {
    t *= pi; phi *= pi/2;
    F[0] = (1-sin (t))*cos (phi);
    F[1] = (1-sin (t))*sin (phi);
    F[2] = (1+sin (t))*cos (phi);
    F[3] = (1+sin (t))*sin (phi);
    F *= 1./sqrt (2.)*cos (t);

    return F;
}


////////////////////////////////////////////////////////////////////////////////


/** Torus3 c'tor given a definition set in \f$ R^2 \f$ (as parameter space)
 *  @param _umin minimal value in u
 *  @param _umax maximal value in u
 *  @param _du stepsize in u
 *  @param _vmin minimal value in v
 *  @param _vmax maximal value in v
 *  @param _dv stepsize in v
 *  @param _rad radius                                                        */
Torus3::Torus3 (double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv):
        Surface ("Torus 3", _umin, _umax, _du, _vmin, _vmax, _dv) {
    Initialize ();
}

/** Torus3 defining function
 *  @param theta u value
 *  @param phi v value
 *  @return (costht, sintht, cosphi, sinphi)                                  */
Vector<4> &Torus3::f (double theta, double phi) {
    theta *= pi; phi *= pi;
    F[0] = cos (theta);
    F[1] = sin (theta);
    F[2] = cos (phi);
    F[3] = sin (phi);

    return F;
}
