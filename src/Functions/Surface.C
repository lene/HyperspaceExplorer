
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

/// Surface default c'tor, zeroes everything   
Surface::Surface ():
    SurfaceBase("", 0, 0, 0, 0, 0, 0), /*
    umin (0), umax (0), du (0),
    vmin (0), vmax (0), dv (0),
    usteps (0), vsteps (0), */
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
                  double _vmin, double _vmax, double _dv,
                    ParameterMap _parms):
    SurfaceBase(name, _umin, _umax, _du, _vmin, _vmax, _dv, _parms),
    NumVertices (0),
    F (4),
    Xtrans(vec4vec2D()), Xscr(vec3vec2D()) {
    setfunctionName(name);
}

/// Initialize the temporary storage areas Xscr[][], Xtrans[][]
void Surface::InitMem (void) {
    Xscr.resize(getTsteps()+2);
    Xtrans.resize(getTsteps()+2);

    for (unsigned t = 0; t <= getTsteps()+1; t++) {
        Xscr[t].resize(getUsteps()+2);
        Xtrans[t].resize(getUsteps()+2);
    }
}

/// allocate and initialize X[][] with values of f()
/** call InitMem () above                                                     */
void Surface::Initialize () {
    double Wmax = 0, Wmin = 0;
    X = vec4vec2D(getTsteps()+2);
    ColMgrMgr::Instance().setFunction(this);
    for (unsigned t = 0; t <= getTsteps()+1; t++) {
        X[t].resize(getUsteps()+2);
        for (unsigned u = 0; u <= getUsteps()+1; u++) {
            X[t][u] = f (getTmin()+t*getDt(), getUmin()+u*getDu());
            if (X[t][u][3] < Wmin) Wmin = X[t][u][3];
            if (X[t][u][3] > Wmax) Wmax = X[t][u][3];
        }
    }
    for (unsigned t = 0; t <= getTsteps()+1; t++) {
        for (unsigned u = 0; u <= getUsteps()+1; u++) {
            ColMgrMgr::Instance().calibrateColor(
                X[t][u],
                Color(float(t)/float(getTsteps()), float(u)/float(getUsteps()),
                      (Wmax-X[t][u][3])/(Wmax-Wmin)));
        }
    }

    InitMem ();
}

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
                     double _tmin, double _tmax, double _dt,
                     double _umin, double _umax, double _du) {
    getTmin() = _tmin; getTmax() = _tmax; getDt() = _dt;
    getUmin() = _umin; getUmax() = _umax; getDu() = _du;
    getTsteps() = unsigned ((getTmax()-getTmin())/getDt()+1);
    getUsteps() = unsigned ((getUmax()-getUmin())/getDu()+1);

    Initialize ();
}

/// return the approximate amount of memory needed to display a Function of current definition set
/** \todo uses hardcoded and experimentally found value for memory per cell
 *  @return approx. mem required                                              */
unsigned long Surface::MemRequired (void) {
    return (getTsteps()+2)*(getUsteps()+2);
}

/// calculate normal to function at a given point in definition set
/** no further assumption is made than that f () is continuous
 *
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

/// Transforms a Surface
/** as I look at it, i think this could be optimized by making the transformation
 *  matrices static and only canging the corresponding entries... but how to
 *  make this beautifully, i don't know
 *  @param R rotation
 *  @param T translation                                                      */
void Surface::Transform (const VecMath::Rotation<4> &R, const VecMath::Vector<4> &T) {
    Matrix<4> Rot(R);

    for (unsigned t = 0; t <= getTsteps()+1; t++)
        for (unsigned u = 0; u <= getUsteps()+1; u++)
            Xtrans[t][u] = (Rot*X[t][u])+T;
}

/** projects a Surface into three-space
 *  @param scr_w w coordinate of screen
 *  @param cam_w w coordinate of camera
 *  @param depthcue4d wheter to use hyperfog/depth cue                        */
void Surface::Project (double scr_w, double cam_w, bool depthcue4d) {
    double ProjectionFactor;
    double Wmax = 0, Wmin = 0;

    for (unsigned t = 0; t <= getTsteps()+1; t++)
        for (unsigned u = 0; u <= getUsteps()+1; u++) {

            if (Xtrans[t][u][3] < Wmin) Wmin = Xtrans[t][u][3];
            if (Xtrans[t][u][3] > Wmax) Wmax = Xtrans[t][u][3];

            ProjectionFactor = (scr_w-cam_w)/(Xtrans[t][u][3]-cam_w);

            for (unsigned i = 0; i <= 2; i++)
                Xscr[t][u][i] = ProjectionFactor*Xtrans[t][u][i];
    }

    if (!depthcue4d) return;

    for (unsigned t = 0; t <= getTsteps()+1; t++)
        for (unsigned u = 0; u <= getUsteps()+1; u++) {
            ColMgrMgr::Instance().depthCueColor(Wmax, Wmin,
                    Xtrans[t][u][3],
                    X[t][u]);
        }
}


/** draw the projected Surface (onto screen or into GL list, as it is)        */
void Surface::Draw (void) {
    NumVertices = 0;

    for (unsigned t = 0; t < getTsteps(); t++)
        DrawStrip (t);
}


/** draw the current strip of the projected Surface
 *  @param u current u value                                                  */
void Surface::DrawStrip (unsigned t){
    glBegin (GL_QUAD_STRIP);

    setVertex(X[t][0], Xscr[t][0]);
    setVertex(X[t+1][0], Xscr[t+1][0]);
    NumVertices += 2;

    for (unsigned u = 1; u <= getUsteps(); u++) {
        setVertex(X[t][u], Xscr[t][u]);
        setVertex(X[t+1][u], Xscr[t+1][u]);
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
