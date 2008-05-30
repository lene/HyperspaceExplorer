
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

/// \em SurfaceBase provides a base class for functions which take two parameters
/** The \em SurfaceBase interface provides abstract members for the evaluation of
 *  the function values on a two-dimensional grid.
 *
 *  abstract member:
 *      \li Vector &f (double, double);
 *
 *  member:
 *      \li operator () (double t, double u, double);
 *
 *  @todo Vector &normal (double, double); - or in base class?
 *
 *  \ingroup SurfaceGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class SurfaceBase: public Function {
    public:
        /** type of the function used to generate values, optimized with a
         *  reference as return value                                         */
        typedef VecMath::Vector<4> &function_type(double, double);
        /// the real, raw type of the function used to generate values
        typedef VecMath::Vector<4> raw_function_type (double, double);

        SurfaceBase() { }
        SurfaceBase(const QString &name,
                    double _tmin, double _tmax, double _dt,
                    double _umin, double _umax, double _du,
                    ParameterMap _parms = ParameterMap()):
                Function(name, _parms),
                tmin (_tmin), tmax (_tmax), dt (_dt),
                umin (_umin), umax (_umax), du (_du),
                tsteps (unsigned ((tmax-tmin)/dt+1)),
                usteps (unsigned ((umax-umin)/du+1)) { }

    protected:
        unsigned &getTsteps() { return tsteps; }
        unsigned getTsteps() const { return tsteps > 0? tsteps: 1; }
        unsigned &getUsteps() { return usteps; }
        unsigned getUsteps() const { return usteps > 0? usteps: 1; }

        double &getTmin() { return tmin; }
        double getTmin() const { return tmin; }
        double &getTmax() { return tmax; }
        double getTmax() const { return tmax; }
        double &getDt() { return dt; }
        const double &getDt() const { return dt; }
        double &getUmin() { return umin; }
        double getUmin() const { return umin; }
        double &getUmax() { return umax; }
        double getUmax() const { return umax; }
        double &getDu() { return du; }
        const double &getDu() const { return du; }

        /// The mathematical function defining the Function object
        virtual VecMath::Vector<4> &f(double, double) = 0;
        /// Function evaluation operator for three parameters
        /** @param t first argument, e.g. x or t
         *  @param u second argument, e.g. y or u
         *  @param v third argument, e.g. z or v
         *  @return f(t, u, v)                                                */
        VecMath::Vector<4> &operator () (double u, double v, double = 0) {
            return f(u,v);
        }

    private:
        double tmin, ///< min. value of the first parameter, here called t
               tmax, ///< min. value of the first parameter, here called t
               dt,   ///< stepsize in first parameter
               umin, ///< min. value of the second parameter, here called u
               umax, ///< min. value of the second parameter, here called u
               du;   ///< stepsize in second parameter
        unsigned tsteps, ///< number of steps in t
                 usteps; ///< number of steps in u

};


/** A function from \f$ R^2 \rightarrow R^4 \f$, thus describing a parametrized
 *  surface in hyperspace
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Surface: public SurfaceBase {
    public:
        Surface();
        Surface (const QString &name,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv,
                 ParameterMap _parms = ParameterMap());
        virtual ~Surface() { }

        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T);

        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);

        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv);

        vec4vec2D Data (void) { return X; }

        virtual unsigned getDefinitionSpaceDimensions() { return 2; }

    protected:
         virtual vec4vec1D df (double, double);
         virtual function_type normal;

         void Initialize (void);
         void InitMem (void);

         virtual unsigned long MemRequired (void);

         void DrawPlane (unsigned);
         void DrawStrip (unsigned);
/*
         double umin, umax, du,
	            vmin, vmax, dv;

         unsigned usteps, vsteps;*/

         unsigned NumVertices;

         VecMath::Vector<4> F;

         /// temporary storage for the function values on the grid
         vec4vec2D X, Xtrans;
         vec3vec2D Xscr;

         /// storage for the coloring of the vertices
//         floatvec2D R, G, B;
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

protected:
    virtual function_type f;
};

#endif
