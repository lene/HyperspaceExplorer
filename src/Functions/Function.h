//      project:      hyperspace explorer
//      module:       Function.H
//      contains:     class Function: abstract base class for all that follow
//		      implementations of the Function class
//      compile with: make all
//	author:	      helge preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)


#if !defined(FUNCTION_H)
#define FUNCTION_H

#include <vector>
#include <map>

#include <QString>

#include "ParameterMap.h"
#include "Vector.h"

#include "FunctionFactory.h"

namespace UI {
  class View;
}

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

/// A Function is a generalized four-dimensional mathematical function
/** The Function interface provides abstract members for the evaluation of
 *  the function values, usually on a grid, together with methods to rotate and
 *  translate the resulting four-dimensional geometry in 4-space, to project the
 *  transformed geometry onto 3-space, and to draw the projected grid into an
 *  OpenGL display list.
 *
 *  It also handles Function name and its parameters.
 *
 *  abstract members:
 *      \li Vector &f (double, double, double);
 *      \li Transform (double Rxy, double Rxz, double Rxw,
 *                     double Ryz, double Ryw, double Rzw,
 *                     double Tx, double Ty, double Tz, double Tw)
 *      \li Project (double ScrW, double CamW, bool DepthCue4D)
 *      \li Draw ()
 *      \li ReInit(double _tmin, double _tmax, double _dt,
 *                 double _umin, double _umax, double _du,
 *                 double _vmin, double _vmax, double _dv)
 *      \li Initialize ();
 *
 *  virtual members:
 *      \li Vector *df (double, double, double);
 *      \li SetParameters (double = 0, double = 0, double = 0, double = 0)
 *
 *  other useful members:
 *      \li Transform ()
 *
 *  Function objects can be created directly via their various constructors, or
 *  via the createFunction() method of the FunctionFactory class. To enable the
 *  latter, a Function's definition must be augmented by the following code
 *  (for example):
 *  \code
 *  namespace {
 *      Function *createHypercube() { return new Hypercube(); }
 *      const bool registered =
 *          TheFunctionFactory::Instance().registerFunction("Hypercube", createHypercube);
 *  }
 *  \endcode
 *
 *  \todo Vector &normal (double, double, double); - or in derived classes?
 *  \todo  operator () (double t, double u, double v) - ditto
 *
 *  \ingroup FunctionGroup
 *  \author Helge Preuss <lene.preuss@gmail.com>                         */
class Function {

    public:

        /// one-dimensional array of floats, implemented as a std::vector
        typedef std::vector<float> floatvec1D;
        /// two-dimensional array of floats, implemented as a nested std::vector
        typedef std::vector<floatvec1D> floatvec2D;
        /// three-dimensional array of floats, implemented as a nested std::vector
        typedef std::vector<floatvec2D> floatvec3D;

        /// one-dimensional array of Vector<3>, implemented as a std::vector
        typedef std::vector<VecMath::Vector<3> > vec3vec1D;
        /// two-dimensional array of Vector<3>, implemented as a nested std::vector
        typedef std::vector<vec3vec1D> vec3vec2D;
        /// three-dimensional array of Vector<3>, implemented as a nested std::vector
        typedef std::vector<vec3vec2D> vec3vec3D;

        /// one-dimensional array of Vector<4>, implemented as a std::vector
        typedef std::vector<VecMath::Vector<4> > vec4vec1D;
        /// two-dimensional array of Vector<4>, implemented as a nested std::vector
        typedef std::vector<vec4vec1D> vec4vec2D;
        /// three-dimensional array of Vector<4>, implemented as a nested std::vector
        typedef std::vector<vec4vec2D> vec4vec3D;

        /// function that is applied on the original vertices
        typedef void(*function_on_fourspace_vertex)(const VecMath::Vector<4> &);
        /// function that is applied on the original and transformed vertices
        typedef void(*function_on_fourspace_and_transformed_vertex)(const VecMath::Vector<4> &,
                                                                    const VecMath::Vector<4> &);
        /// function that is applied on the original and transformed vertices
        typedef void(*function_on_fourspace_transformed_and_projected_vertex)(const VecMath::Vector<4> &,
                                                                              const VecMath::Vector<4> &,
                                                                              const VecMath::Vector<3> &);
        /// function that is applied on vertices transformed and projected into 3-space
        typedef void(*function_on_projected_vertex)(const VecMath::Vector<3> &);

        /// Function default c'tor
        Function();
        /// Function c'tor given a definition set in \f$ R^3 \f$ (as parameter space)
        Function (ParameterMap parameters);
        virtual ~Function();

        /// Execute the desired rotation and translation to the Function object
        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T) = 0;
        /// Overloaded function executing the transform to the default state
        void resetTransform();

        /// Projects the vertex data to 3D
        virtual void Project (double ScrW, double CamW, bool DepthCue4D) = 0;

        /// Draw the function
        virtual void Draw (UI::View *) = 0;

        /// Called when a Function must be created anew
        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv) = 0;

        /// Called by the ColorManager after setting the Function on the CM
        virtual void calibrateColors() const = 0;

        /** \return The name of the function in cleartext                     */
        virtual std::string getFunctionName() const = 0;

        /// number of argument given to the defining function
        virtual unsigned getDefinitionSpaceDimensions() = 0;

        /// Set parameters to the Function
        virtual void SetParameters(const ParameterMap &);

        /// \return The collection of all parameters (and their values)
        ParameterMap getParameters();

        /// \return The value of the parameter which is named \p name
        FunctionParameter::parameter_ptr_type getParameter(const std::string &name);

        /** \return number of parameters for the function                     */
        unsigned getNumParameters();

        /** \return Value of the parameter with the name \p name.             */
        FunctionParameter::value_ptr_type getParameterValue(const std::string &name);

        /// Set a parameter with a specified key from a supplied ParameterMap
        /** \tparam T Type of the parameter to be set.
         */
        template <typename T> void setParameter(const ParameterMap &parms,
                                                T &parm,
                                                const std::string &key);

        /// Loop over all vertices managed by the Function and call apply on them.
        virtual void for_each(function_on_fourspace_vertex apply) = 0;
        /// Loop over all vertices managed by the Function and their transformed
        /// images and call apply on them.
        /** This function is not pure virtual because it would be too tedious to
         *  require all implementing classes to provide an implementation.
         *
         *  The default implementation provided here throws an exception.
         */
        virtual void for_each(function_on_fourspace_and_transformed_vertex apply);
        /// Loop over all vertices managed by the Function, their transformed images
        /// and the projection into three-space and call apply on them.
        /** This function is not pure virtual because it would be too tedious to
        *  require all implementing classes to provide an implementation.
        *
        *  The default implementation provided here throws an exception.
        */
        virtual void for_each(function_on_fourspace_transformed_and_projected_vertex apply);
        /// Loop over all vertices managed by the Function and call apply on them.
        virtual void for_each(function_on_projected_vertex apply) = 0;

    protected:
        /// Function evaluation operator for three parameters
        virtual VecMath::Vector<4> &operator () (double, double, double) = 0;

        /// Numerical calculation of the derivatives in t, u and v
        virtual vec4vec1D df (double, double, double);

        /// This abstract function is called in the constructor of descendants
        virtual void Initialize (void) = 0;

        /// Return the approximate amount of memory needed to display a Function of current definition set
        virtual unsigned long MemRequired (void);

        /// Add a parameter to the list of parameters
        /** \tparam T Type of the parameter to be declared.
         */
        template <typename T> void declareParameter(const std::string &,
                                                    const T &);
        /// Add a parameter to the list of parameters
        /** \tparam T Type of the parameter to be declared.
         */
        template <typename T> void declareParameter(const std::string &,
                const T &, const T &);

    private:

      class Impl;
      Impl *pImpl_;
};


#endif
