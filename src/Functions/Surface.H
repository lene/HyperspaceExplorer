
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:       helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)


#if(!defined SURFACE_H)
#define SURFACE_H

#include "Function.H"


////////////////////////////////////////////////////////////////////////////////

/** A function from \f$ R^2 \rightarrow R^4 \f$, thus describing a parametrized
 *  surface in hyperspace
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Surface: public Function {
    public:
        Surface();
        Surface (const QString &name,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv);
        virtual ~Surface() { }

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

        vec4vec2D Data (void) { return X; }

        VecMath::Vector<4> &operator () (double u, double v) {
            unsigned iu = unsigned ((u-umin)/du), iv = unsigned ((v-vmin)/dv);
            return X[iu][iv];
        }

        typedef VecMath::Vector<4> &function_type (double, double);
        typedef VecMath::Vector<4> raw_function_type (double, double);

    protected:
         virtual VecMath::Vector<4> &f (double, double,  double) { return F; }
         virtual function_type f  = 0;
         virtual vec4vec1D df (double, double);
         virtual function_type normal;

         void Initialize (void);
         void InitMem (void);

         virtual unsigned long MemRequired (void);

         void DrawPlane (unsigned);
         void DrawStrip (unsigned);

         double umin, umax, du,
	            vmin, vmax, dv;

         unsigned usteps, vsteps;

         unsigned NumVertices;

         VecMath::Vector<4> F;
	     
         /// temporary storage for the function values on the grid
         vec4vec2D X, Xtrans;
         vec3vec2D Xscr;
         
	     /// storage for the coloring of the vertices
         floatvec2D R, G, B;
};

/** An example surface:
    \f{eqnarray*}{
        F_0 & = & Radius*\sin \theta*\sin \psi;   \\
        F_1 & = & Radius*\cos \theta*\sin \psi;   \\
        F_2 & = & Radius*\cos \theta;             \\
        F_3 & = & Radius*\cos \psi;
    \f}
 *  \ingroup SurfaceGroup                                                    */
class Surface1: public Surface {
public:
    Surface1 (double _umin, double _umax, double _du,
	      double _vmin, double _vmax, double _dv);
    virtual ~Surface1() { }
    virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
    virtual function_type f;
};

/** A four-dimensional surface described by Thomas Banchoff
    \f{eqnarray*}{
        t & = & \theta*\pi                  \\
        p & = & \phi*frac{\pi}{2}           \\
        F_0 & = (1-\sin{t})*\cos{p}         \\
        F_1 & = (1-\sin{t})*\sin{p}         \\
        F_2 & = (1+\sin{t})*\cos{p}         \\
        F_3 & = (1+\sin{t})*\sin{p}         \\
        F & = & F*\frac{1}{\sqrt{2}}*\cos{t}
    \f}
 *  \ingroup SurfaceGroup                                                    */
class Horizon: public Surface {
public:
    Horizon (double _umin, double _umax, double _du,
	     double _vmin, double _vmax, double _dv);
    virtual ~Horizon () { }
    virtual void SetParameters (double = 0, double = 0, double = 0, double = 0) { }

protected:
    virtual function_type f;
};

/** Another torus version, this time as a two-dimensional surface in
 *  four-space
 *  \ingroup SurfaceGroup                                                    */
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
