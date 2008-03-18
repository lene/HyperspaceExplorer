
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

/** a  Function is a mathematical function  f: R^3 -> R^4,  evaluated on a
 *  3-dimensional grid, together with methods  to rotate and translate the grid
 *  in 4-space,  to project the transformed grid onto 3-space, and to draw the
 *  projected grid into an OpenGL display list.
 *  
 *  abstract member:
 *	- Vector &f (double, double, double);
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
 *  other useful members: 
 *	- Transform ()
 *	- operator () (double t, double u, double v)
 *	- Initialize ();
 *	- InitMem ();                                                         */
class Function {
    public:
        Function();
        Function (const QString &name,
                  double _tmin, double _tmax, double _dt,
                  double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv);
        virtual ~Function();

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

        VecMath::Vector<4> ***Data (void) { return X; }

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
        virtual VecMath::Vector<4> *df (double, double, double);
        virtual function_type normal;
    
        virtual void Initialize (void);
        void InitMem (void);
        void Free (void);
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

        //      temporary storage for the function values on the grid
        VecMath::Vector<4> ***X, ***Xtrans;
        VecMath::Vector<3> ***Xscr;
        VecMath::Vector<4> *Xchunk, *XtransChunk;
        VecMath::Vector<3> *XscrChunk;
        
        //      storage for the coloring of the vertices
        float ***R, ***G, ***B;
        float *RGBChunk;

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
