
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:       lene preuss (lene.preuss@gmail.com)
//      license:      GPL (see License.txt)


#if(!defined SURFACE_H)
#define SURFACE_H

#include "Function.h"

#include "ParametricFunction.h"
#include "FunctionValueGrid.h"

////////////////////////////////////////////////////////////////////////////////

/// SurfaceBase provides a base class for functions which take two parameters
/** The SurfaceBase interface provides abstract members for the evaluation
 * of the function values on a two-dimensional grid.
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
 *  @author Lene Preuss <lene.preuss@gmail.com>                         */
class SurfaceBase: public Function {
    public:
        /** type of the function used to generate values, optimized with a
         *  reference as return value                                         */
        typedef VecMath::Vector<4> &function_type(double, double);
        /// the real, raw type of the function used to generate values
        typedef VecMath::Vector<4> raw_function_type (double, double);

        SurfaceBase() { }
        /** \param name a name for the Surface
         *  \param _tmin lower bound in first parameter
         *  \param _tmax upper bound in first parameter
         *  \param _dt stepsize in first parameter
         *  \param _umin lower bound in second parameter
         *  \param _umax upper bound in second parameter
         *  \param _du stepsize in second parameter
         *  \param _parms parameters to the Surface                           */
        SurfaceBase(const QString &name,
                    double _tmin, double _tmax, double _dt,
                    double _umin, double _umax, double _du,
                    ParameterMap _parms = ParameterMap()):
                Function(name, _parms),
                tmin (_tmin), tmax (_tmax), dt (_dt),
                umin (_umin), umax (_umax), du (_du),
                tsteps (unsigned ((tmax-tmin)/dt+1)),
                usteps (unsigned ((umax-umin)/du+1)) { }

        /// Function evaluation operator for three parameters
        /** @param u first argument, e.g. y or u
         *  @param v second argument, e.g. z or v
         *  @return f(t, u, v)                                                */
        VecMath::Vector<4> &operator () (double u, double v, double = 0) {
            return f(u,v);
        }

    protected:
        /// number of steps in t
        unsigned &getTsteps() { return tsteps; }
        /// number of steps in t
        unsigned getTsteps() const { return tsteps > 0? tsteps: 1; }
        /// number of steps in u
        unsigned &getUsteps() { return usteps; }
        /// number of steps in u
        unsigned getUsteps() const { return usteps > 0? usteps: 1; }

        double &getTmin() { return tmin; }          ///< min. value of the first parameter, t
        double getTmin() const { return tmin; }     ///< min. value of the first parameter, t
        double &getTmax() { return tmax; }          ///< max. value of the first parameter, t
        double getTmax() const { return tmax; }     ///< max. value of the first parameter, t
        double &getDt() { return dt; }              ///< delta in t
        const double &getDt() const { return dt; }  ///< delta in t
        double &getUmin() { return umin; }          ///< min. value of the second parameter, u
        double getUmin() const { return umin; }     ///< min. value of the second parameter, u
        double &getUmax() { return umax; }          ///< max. value of the second parameter, u
        double getUmax() const { return umax; }     ///< max. value of the second parameter, u
        double &getDu() { return du; }              ///< delta in u
        const double &getDu() const { return du; }  ///< delta in u

        /// The mathematical function defining the Function object
        virtual VecMath::Vector<4> &f(double, double) = 0;

    static double _min, ///< Default value for lower grid boundary
                  _max, ///< Default value for upper grid boundary
                  _d;   ///< Default value for step size

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


/// Parametrized surface in four-space defined by \f$ f: R^2 \rightarrow R^4 \f$
/** \ingroup FunctionGroup
 *  @author Lene Preuss <lene.preuss@gmail.com>                         */
class Surface: public SurfaceBase {
    public:
        Surface();
        Surface (const QString &name);
        Surface (const QString &name,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv,
                 ParameterMap _parms = ParameterMap());
        virtual ~Surface() { }

        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T);

        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);

        /// Called by the ColorManager after setting the Function on the CM
        virtual void calibrateColors() const;

        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv);

        vec4vec2D Data (void) { return _X; } ///< direct access to the function values

        /// \see Function::getDefinitionSpaceDimensions()
        virtual unsigned getDefinitionSpaceDimensions() { return 2; }

    protected:
         virtual vec4vec1D df (double, double);
         virtual function_type normal;

         void Initialize (void);
         void InitMem (void);

         virtual unsigned long MemRequired (void);

         void DrawStrip (unsigned);

         virtual vec4vec2D X() const { return _X; }
         virtual vec4vec2D Xtrans() const { return _Xtrans; }
         
         /// redeclare \see Function::NumVertices as protected
         unsigned NumVertices;

         VecMath::Vector<4> F;

         vec4vec2D _X,       ///< temporary storage for the function values on the grid
                   _Xtrans;  ///< temporary storage for the function values on the grid
         vec3vec2D _Xscr;    ///< temporary storage for the function values on the grid
};

/// An example surface:
/** \f{eqnarray*}{
        F_0 & = & Radius*\sin \theta*\sin \psi   \\
        F_1 & = & Radius*\cos \theta*\sin \psi   \\
        F_2 & = & Radius*\cos \theta             \\
        F_3 & = & Radius*\cos \psi
    \f}
 *  \ingroup SurfaceGroup                                                    */
class Surface1: public Surface {
public:
    Surface1(): Surface("Surface1") { }
    Surface1 (double _umin, double _umax, double _du,
              double _vmin, double _vmax, double _dv);
    virtual ~Surface1() { }

    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T);
    virtual void ReInit(double _tmin, double _tmax, double _dt,
                        double _umin, double _umax, double _du,
                        double _vmin, double _vmax, double _dv);

protected:
    virtual function_type f;
    virtual vec4vec2D X() const;
    virtual vec4vec2D Xtrans() const;
    
  private:

    class DefiningFunction: public ParametricFunction<4, 2> {
      public:
        virtual return_type f(const argument_type &x);
    };
    std::tr1::shared_ptr<DefiningFunction> _function;
    FunctionValueGrid<4, 2> _X_as_grid;
    FunctionValueGrid<4, 2>::value_storage_type _Xtrans_as_grid;
};

namespace {
    Function *createSurface1() { return new Surface1(); }
    const bool registeredS1 =
            TheFunctionFactory::Instance().registerFunction("Surface1", createSurface1);
}

/// A four-dimensional surface described by Thomas Banchoff
/** \f{eqnarray*}{
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
    Horizon(): Surface("Horizon") { }
    Horizon (double _umin, double _umax, double _du,
             double _vmin, double _vmax, double _dv);
    virtual ~Horizon () { }

protected:
    virtual function_type f;
};

namespace {
    Function *createHorizon() { return new Horizon(); }
    const bool registeredS2 =
            TheFunctionFactory::Instance().registerFunction("Horizon", createHorizon);
}

/// Another torus version, this time as a two-dimensional surface in four-space
/** \ingroup SurfaceGroup                                                    */
class Torus3: public Surface {
public:
    Torus3(): Surface("Torus3") { }
    Torus3 (double _umin, double _umax, double _du,
            double _vmin, double _vmax, double _dv);
    virtual ~Torus3 () { }

protected:
    virtual function_type f;
};

namespace {
    Function *createTorus3() { return new Torus3(); }
    const bool registeredS3 =
            TheFunctionFactory::Instance().registerFunction("Torus3", createTorus3);
}

#endif
