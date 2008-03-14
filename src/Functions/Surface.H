
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if(!defined SURFACE_H)
#define SURFACE_H

#include "Function.H"


    ///////////////////////////////////////////////////////////////////////////////

class Surface: public Function {
    public:
        Surface();
        Surface (double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv);
        virtual ~Surface();

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

        VecMath::Vector<4> **Data (void) { return X; }

        VecMath::Vector<4> &operator () (double u, double v) {
            unsigned iu = unsigned ((u-umin)/du), iv = unsigned ((v-vmin)/dv);
            return X[iu][iv];
        }

        typedef VecMath::Vector<4> &function_type (double, double);
        typedef VecMath::Vector<4> raw_function_type (double, double);
    
    protected:
         virtual VecMath::Vector<4> &f (double, double,  double) { return F; }
         virtual function_type f  = 0;
         virtual VecMath::Vector<4> *df (double, double);
         virtual function_type normal;
	
         void Initialize (void);
         void InitMem (void);
         virtual void Free (void);
         virtual unsigned long MemRequired (void);
	
         void DrawPlane (unsigned);
         void DrawStrip (unsigned);

         double umin, umax, du,
	            vmin, vmax, dv;

         unsigned usteps, vsteps;

         unsigned NumVertices;

         VecMath::Vector<4> F;

	     //	temporary storage for the function values on the grid
         VecMath::Vector<4> **X, **Xtrans;
         VecMath::Vector<3> **Xscr;
         VecMath::Vector<4> *Xchunk, *XtransChunk;
         VecMath::Vector<3> *XscrChunk;
	
	     //	storage for the coloring of the vertices
         float **R, **G, **B;
         float *RGBChunk;
};

class Surface1: public Surface {
public:
    Surface1 (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv);
    virtual ~Surface1() { }
    virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
    virtual function_type f;
};


class Horizon: public Surface {
public:
    Horizon (double _umin, double _umax, double _du,
	     double _vmin, double _vmax, double _dv);
    virtual ~Horizon () { }
    virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
    virtual function_type f;
};


class Torus3: public Surface {
public:
    Torus3 (double _umin, double _umax, double _du,
	    double _vmin, double _vmax, double _dv);
    virtual ~Torus3 () { }
    virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
    virtual function_type f;
};

#endif
