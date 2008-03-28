
//      project:      hyperspace explorer
//      module:       Function.H
//      contains:     class Function: abstract base class for all that follow
//		      implementations of the Function class
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(FUNCTION_H)
#define FUNCTION_H

#include "Vector.H"

/// \defgroup FunctionGroup Functions and objects
/// \defgroup RealGroup Functions R^3 -> R
/// \ingroup FunctionGroup
/// \defgroup PolarGroup Polar functions R^3 -> R
/// \ingroup RealGroup
/// \defgroup ObjectGroup Arbitrary four-dimensional objects, described by their surfaces
/// \ingroup FunctionGroup
/// \defgroup SurfaceGroup Functions R^2 -> R^4, describing surfaces in four-space
/// \ingroup FunctionGroup
/// \defgroup ComplexGroup Functions C -> C
/// \ingroup SurfaceGroup

/** a  Function is a mathematical function  \f$ f: R^3 \rightarrow R^4 \f$ ,
 *  evaluated on a 3-dimensional grid, together with methods  to rotate and
 *  translate the grid in 4-space,  to project the transformed grid onto
 *  3-space, and to draw the projected grid into an OpenGL display list.
 *
 *  abstract member:
 *	- Vector &f (double, double, double);
 *
 *  virtual members:
 *	- Vector *df (double, double, double);
 *	- Vector &normal (double, double, double);
 *	- Transform (double Rxy, double Rxz, double Rxw,
 *		     double Ryz, double Ryw, double Rzw,
 *		     double Tx, double Ty, double Tz, double Tw)
 *	- Project (double ScrW, double CamW, bool DepthCue4D)
 *	- Draw ()
 *	- ReInit(double _tmin, double _tmax, double _dt,
 *		 double _umin, double _umax, double _du,
 *		 double _vmin, double _vmax, double _dv)
 *	- SetParameters (double _a = 0, double _b = 0, double _c = 0, double _d = 0)
 *
 *  other useful members:
 *	- Transform ()
 *	- operator () (double t, double u, double v)
 *	- Initialize ();
 *	- InitMem ();
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Function {
    public:
        /// a one-dimensional array of floats, implemented as a std::vector
        typedef std::vector<float> floatvec1D;
        /// a two-dimensional array of floats, implemented as a nested std::vector
        typedef std::vector<floatvec1D> floatvec2D;
        /// a three-dimensional array of floats, implemented as a nested std::vector
        typedef std::vector<floatvec2D> floatvec3D;
        
        /// a one-dimensional array of Vector<3>, implemented as a std::vector
        typedef std::vector<VecMath::Vector<3> > vec3vec1D;
        /// a two-dimensional array of Vector<3>, implemented as a nested std::vector
        typedef std::vector<vec3vec1D> vec3vec2D;
        /// a three-dimensional array of Vector<3>, implemented as a nested std::vector
        typedef std::vector<vec3vec2D> vec3vec3D;
        
        /// a one-dimensional array of Vector<4>, implemented as a std::vector
        typedef std::vector<VecMath::Vector<4> > vec4vec1D;
        /// a two-dimensional array of Vector<4>, implemented as a nested std::vector
        typedef std::vector<vec4vec1D> vec4vec2D;
        /// a three-dimensional array of Vector<4>, implemented as a nested std::vector
        typedef std::vector<vec4vec2D> vec4vec3D;

        Function();
        Function (const QString &name,
                  double _tmin, double _tmax, double _dt,
                  double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv);
        virtual ~Function() { }

        virtual void Transform (double Rxy, double Rxz, double Rxw,
                                double Ryz, double Ryw, double Rzw,
                                double Tx, double Ty, double Tz, double Tw);
        void Transform (void) { Transform (0, 0, 0, 0, 0, 0,  0, 0, 0, 0); }

        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);

        virtual void ReInit(double _tmin, double _tmax, double _dt,
                double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv);
        virtual void SetParameters (double _a = 0, double _b = 0,
                                    double _c = 0, double _d = 0);

        vec4vec3D Data(void) { return X; }

        VecMath::Vector<4> &operator () (double t, double u, double v) {
            unsigned it = unsigned ((t-tmin)/dt),
                     iu = unsigned ((u-umin)/du),
                     iv = unsigned ((v-vmin)/dv);
            return X[it][iu][iv];
        }

        QString getFunctionName() const { return functionName; }
        unsigned getNumParameters() { return parameterNames.size(); }
        std::vector<QString> getParameterNames() { return parameterNames; }
        QString getParameterName(unsigned i) {
            return i < parameterNames.size()? parameterNames[i]: ""; }

        typedef VecMath::Vector<4> &function_type (double, double, double);
        typedef VecMath::Vector<4> raw_function_type (double, double, double);

    protected:
        virtual function_type f = 0;
        virtual vec4vec1D df (double, double, double);
        virtual function_type normal;

        virtual void Initialize (void);
        void InitMem (void);
//        void Free (void);
        virtual unsigned long MemRequired (void);

        void DrawPlane (unsigned);
        void DrawStrip (unsigned, unsigned);
        void DrawCube (unsigned, unsigned, unsigned);

        double tmin, tmax, dt,
               umin, umax, du,
               vmin, vmax, dv;

        unsigned tsteps, usteps, vsteps;

        unsigned NumVertices;

        VecMath::Vector<4> F;

        /// temporary storage for the function values on the grid
        vec4vec3D X, Xtrans;
        /// temporary storage for the projected function values
        vec3vec3D Xscr;
        
        /// storage for the coloring of the vertices
        floatvec3D R, G, B;

        QString functionName;
        std::vector<QString> parameterNames;

};


/*******************************************************************************
 *
 *  classes which implement Function::f (double, double, double) follow
 *  the descendants may also implement Function::df () and Function::normal (),
 *  but need not
 */

////////////////////////////////////////////////////////////////////////////////

/** a hypersphere: defining function is
    \f{eqnarray*} {
        F_0 & = & Radius*\sin(\psi)*\sin(\theta)*\cos(\phi)    \\
        F_1 & = & Radius*\sin(\psi)*\sin(\theta)*\sin(\phi)    \\
        F_2 & = & Radius*\sin(\psi)*\cos(\theta)              \\
        F_3 & = & Radius*\cos(\psi)
    \f}
 *  \ingroup FunctionGroup                                                    */
class Hypersphere: public Function {
    public:
        Hypersphere (double _tmin, double _tmax, double _dt,
	             double _umin, double _umax, double _du,
	             double _vmin, double _vmax, double _dv,
	             double _rad = 1);
        virtual ~Hypersphere() { }
        virtual void SetParameters (double _a = 0, double = 0, double = 0,
			            double = 0) { Radius = _a; }

    protected:
        virtual function_type f;
        virtual function_type normal;

        double Radius;
};


///////////////////////////////////////////////////////////////////////////////

/** a four-dimensional torus where there are three radii - one circling about
 *  the main axis, the second circling perpendicular to the first circle, and
 *  the third circling about the second circle, perpendicular to all other
 *  directions
 *  \ingroup FunctionGroup                                                    */
class Torus1: public Function {
    public:
        Torus1 (double _tmin, double _tmax, double _dt,
	        double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv,
	        double _R = 2, double _r = 1, double _rho = 0.5);
        virtual ~Torus1() { }
        virtual void SetParameters (double _a = 0, double _b = 0,
                                    double _c = 0, double = 0) {
            R = _a; r = _b; rho = _c; }

    protected:
        virtual function_type f;

        double R, r, rho;
};


///////////////////////////////////////////////////////////////////////////////

/** a four-dimensional torus where a sphere circles about a center point in a
 *  direction perpendicular to all directions making up the sphere
 *  \ingroup FunctionGroup                                                    */
class Torus2: public Function {
    public:
        Torus2 (double _tmin, double _tmax, double _dt,
	        double _umin, double _umax, double _du,
	        double _vmin, double _vmax, double _dv,
	        double _R = 1, double _r = 0.5);
        virtual ~Torus2 () { }
        virtual void SetParameters (double _a = 0, double _b = 0,
                                    double = 0, double = 0) {
                R = _a; r = _b; }

    protected:
        virtual function_type f;

        double R, r;
};


///////////////////////////////////////////////////////////////////////////////

/** an example function from \f$R^3 \rightarrow R\f$
    \f{eqnarray*}{
        r^2      & = & x^2+y^2+z^2  \\
        f(x,y,z) & = & 1./(r^2+.25)
    \f}
 *  \ingroup RealGroup                                                    */
class Fr3r: public Function {
    public:
        Fr3r (double _tmin, double _tmax, double _dt,
              double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
        virtual ~Fr3r() { }

    protected:
        virtual function_type f;

        double Radius;
};


///////////////////////////////////////////////////////////////////////////////

/** a function describing the gravitational potential of a spherical mass
 *  \ingroup RealGroup                                                    */
class GravitationPotential: public Function {
    public:
        GravitationPotential (double _tmin, double _tmax, double _dt,
                              double _umin, double _umax, double _du,
                              double _vmin, double _vmax, double _dv,
                              double _M = 1, double _R = 0.25);
        virtual ~GravitationPotential () { }
        virtual void SetParameters (double _a = 0, double _b = 0, double = 0, double = 0) {
            M = _a; R = _b;
        }

    protected:
        virtual function_type f;

        double M,               //  not really M, but M/R^3
               R;
};

///////////////////////////////////////////////////////////////////////////////

/** \f$ f(x,y,z) = \sin (\pi*(x^2+y^2+z^2)) \f$
 *  \ingroup RealGroup                                                    */
class Fr3rSin: public Function {
public:
    Fr3rSin (double _tmin, double _tmax, double _dt,
	     double _umin, double _umax, double _du,
	     double _vmin, double _vmax, double _dv);
    virtual ~Fr3rSin () { }

protected:
    virtual function_type f;
};

///////////////////////////////////////////////////////////////////////////////

/** \f$ f(x,y,z) = \exp (x^2+y^2+z^2) \f$
 *  \ingroup RealGroup                                                    */
class Fr3rExp: public Function {
public:
    Fr3rExp (double _tmin, double _tmax, double _dt,
	     double _umin, double _umax, double _du,
	     double _vmin, double _vmax, double _dv);
    virtual ~Fr3rExp () { }

protected:
    virtual function_type f;
};

///////////////////////////////////////////////////////////////////////////////

/** a hypersphere as an example polar function
 *  \ingroup PolarGroup                                                    */
class Polar: public Function {
public:
    Polar (double _tmin, double _tmax, double _dt,
	   double _umin, double _umax, double _du,
	   double _vmin, double _vmax, double _dv);
    virtual ~Polar() { }

protected:
    virtual function_type f;
};


///////////////////////////////////////////////////////////////////////////////

/** \f$ r(\psi, \theta, \phi) = |\sin (Phase*\pi*\psi*\theta*\phi)| \f$
 *  \ingroup PolarGroup                                                    */
class PolarSin: public Function {
public:
    PolarSin (double _tmin, double _tmax, double _dt,
	      double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv,
	      double _phase = 2);
    virtual ~PolarSin () { }
    virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) {
	Phase = _a; }

protected:
    virtual function_type f;
    double Phase;
};


///////////////////////////////////////////////////////////////////////////////

/** \f$ r = \sin(\pi/3.*(\psi+\theta+\phi)) \f$
 *  \ingroup PolarGroup                                                    */
class PolarSin2: public Function {
public:
    PolarSin2 (double _tmin, double _tmax, double _dt,
	       double _umin, double _umax, double _du,
	       double _vmin, double _vmax, double _dv);
    virtual ~PolarSin2 () { }

protected:
    virtual function_type f;
};


///////////////////////////////////////////////////////////////////////////////

/** \f$ r = \sqrt{\psi^2+\theta^2+\phi^2} \f$
 *  \ingroup PolarGroup                                                    */
class PolarR: public Function {
public:
    PolarR (double _tmin, double _tmax, double _dt,
	    double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv,
	    double _phase = 2);
    virtual ~PolarR () { }
    virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) {
	Phase = _a; }

protected:
    virtual function_type f;
    double Phase;
};


#endif
