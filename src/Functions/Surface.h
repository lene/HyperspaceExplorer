
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
#include "NestedVector.h"

#include <utility>

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
class SurfaceDefinitionRange {
    public:

        /** \param _tmin lower bound in first parameter
         *  \param _tmax upper bound in first parameter
         *  \param _dt stepsize in first parameter
         *  \param _umin lower bound in second parameter
         *  \param _umax upper bound in second parameter
         *  \param _du stepsize in second parameter
         *  \param _parms parameters to the Surface                           */
        SurfaceDefinitionRange(double _tmin, double _tmax, double _dt,
                               double _umin, double _umax, double _du):
                tmin (_tmin), tmax (_tmax), dt (_dt),
                umin (_umin), umax (_umax), du (_du),
                tsteps (unsigned ((tmax-tmin)/dt+1)),
                usteps (unsigned ((umax-umin)/du+1)) { }

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
 *  @author Lene Preuss <lene.preuss@gmail.com>
 */
class Surface: public Function {

  public:

      /** type of the function used to generate values, optimized with a
       *  reference as return value                                         */
      typedef VecMath::Vector<4> &function_type(double, double);
      /// the real, raw type of the function used to generate values
      typedef VecMath::Vector<4> raw_function_type (double, double);
      
      Surface();
        Surface (double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv,
                 ParameterMap _parms = ParameterMap());
        virtual ~Surface();

        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T);

        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (UI::View *view);

        /// Called by the ColorManager after setting the Function on the CM
        virtual void calibrateColors() const;

        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv);

        /// \see Function::getDefinitionSpaceDimensions()
        virtual unsigned getDefinitionSpaceDimensions();

        virtual void for_each(function_on_fourspace_vertex apply);
        virtual void for_each(function_on_projected_vertex apply);

        /// Function evaluation operator for three parameters
        /** @param u first argument, e.g. y or u
         *  @param v second argument, e.g. z or v
         *  @return f(t, u, v)                                                */
        VecMath::Vector<4> &operator () (double u, double v, double = 0);

    protected:
        virtual vec4vec1D df (double, double);
        virtual function_type normal;

        void Initialize (void);

        /// Pointer to the actual ParametricFunction doing all the work.
        std::tr1::shared_ptr< ParametricFunction<4, 2> > _function;
        
        unsigned getTsteps() const;
        unsigned getUsteps() const;

        /// Array of function values.
        const VecMath::NestedVector< VecMath::Vector<4>, 2 > &X() const;
        /// Array of function values after transform.
        const VecMath::NestedVector< VecMath::Vector<4>, 2 > &Xtrans() const;
        /// Array of projected function values.
        const VecMath::NestedVector< VecMath::Vector<3>, 2 > &Xscr() const;

  private:

    void DrawStrip (unsigned t, UI::View *view);

    /// Set up the grid using boundaries and stepwidth.
    void setBoundariesAndStepwidth(double tmin, double tmax, double dt,
                                   double umin, double umax, double du);

    std::pair<double, double> findExtremesInW() const;

    SurfaceDefinitionRange definitionRange_;

    /// Array of function values.
    FunctionValueGrid<4, 2> _X;
    /// Array of function values after transform.
    FunctionValueGrid<4, 2>::value_storage_type _Xtrans;
    /// Array of projected function values.
    VecMath::NestedVector< VecMath::Vector<3>, 2 > _Xscr;

};

#endif
