
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

    class Impl;
    Impl *pImpl_;
    
};

#endif
