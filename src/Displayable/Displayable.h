/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#if !defined(DISPLAYABLE_H)
#define DISPLAYABLE_H

#include "FunctionParameter.h"
#include "FunctionFactory.h"
#include "DisplayableClass.h"

#include <vector>

namespace UI {
  class View;
}

namespace VecMath {
    template <unsigned D, typename N> class Rotation;
    template <unsigned D, typename N> class Vector;
    template <typename T, unsigned D> class MultiDimensionalVector;
}
class ParameterMap;

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

/// A Displayable is a generalized four-dimensional object.
/** The Displayable interface provides abstract members for the definition of
 *  four-dimensional objects, together with methods to rotate and
 *  translate the resulting four-dimensional geometry in 4-space, to project the
 *  transformed geometry onto 3-space, and to draw the projected grid into a
 *  generalized View that can display three-dimensional objects.
 *
 *  It also handles object name, description and any parameters that might be
 *  needed to fully describe the object.
 *
 *  abstract members:
 *      \li Vector &f (double, double, double);
 *      \li Transform (double Rxy, double Rxz, double Rxw,
 *                     double Ryz, double Ryw, double Rzw,
 *                     double Tx, double Ty, double Tz, double Tw)
 *      \li Project (double ScrW, double CamW, bool DepthCue4D)
 *      \li Draw (View *view)
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
 *      \li ResetTransform ()
 *
 *  Displayable objects can be created directly via their various constructors, or
 *  via the createFunction() method of the FunctionFactory class. To enable the
 *  latter, a Displayable's definition must be augmented by the following code
 *  (for example):
 *  \code
 *  namespace {
 *      Displayable *createHypercube() { return new Hypercube(); }
 *      const bool registered =
 *          TheFunctionFactory::Instance().registerFunction(createHypercube, "Hypercube");
 *  }
 *  \endcode
 *
 *  \todo Rename other references to the name "Function"
 *  \todo Vector &normal (double, double, double); - or in derived classes?
 *  \todo  operator () (double t, double u, double v) - ditto
 *
 *  \ingroup FunctionGroup
 *  \author Helge Preuss <lene.preuss@gmail.com>                         */
class Displayable {

    public:

        /// function that is applied on the original vertices
        typedef void(*function_on_fourspace_vertex)(const VecMath::Vector<4, double> &);
        /// function that is applied on the original and transformed vertices
        typedef void(*function_on_fourspace_and_transformed_vertex)(const VecMath::Vector<4, double> &,
                                                                    const VecMath::Vector<4, double> &);
        /// function that is applied on the original and transformed vertices
        typedef void(*function_on_fourspace_transformed_and_projected_vertex)(const VecMath::Vector<4, double> &,
                                                                              const VecMath::Vector<4, double> &,
                                                                              const VecMath::Vector<3, double> &);
        /// function that is applied on vertices transformed and projected into 3-space
        typedef void(*function_on_projected_vertex)(const VecMath::Vector<3, double> &);

        /// Displayable default c'tor.
        Displayable();
        /// Displayable c'tor given a set of FunctionParameter
        Displayable (ParameterMap parameters);
        virtual ~Displayable();

        /// Execute the desired rotation and translation to the Displayable object
        virtual void Transform (const VecMath::Rotation<4, double> &R,
                                const VecMath::Vector<4, double> &T,
                                const VecMath::Vector<4, double> &scale = 1.) = 0;
        /// Overloaded function executing the transform to the default state
        void resetTransform();
        /// Projects the vertex data to 3D
        virtual void Project (double ScrW, double CamW, bool DepthCue4D) = 0;

        /// Draw the Displayable object
        virtual void Draw (UI::View *) = 0;

        /// Called when a Displayable must be created anew
        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv) = 0;

        /// Called by the ColorManager after setting the Displayable on the CM
        virtual void calibrateColors() = 0;

        /** \return The name of the Displayable in cleartext                     */
        virtual std::string getFunctionName() const = 0;

        /// number of argument given to the defining function
        virtual unsigned getDefinitionSpaceDimensions() = 0;

        /// Set parameters to the Displayable
        virtual void SetParameters(const ParameterMap &);

        /// \return The collection of all parameters (and their values)
        ParameterMap getParameters();

        /// \return The value of the parameter which is named \p name
        FunctionParameter::parameter_ptr_type getParameter(const std::string &name);

        /** \return number of parameters for the Displayable                     */
        virtual unsigned getNumParameters();

        /** \return Value of the parameter with the name \p name.             */
        FunctionParameter::value_ptr_type getParameterValue(const std::string &name);

        /// Set a parameter with a specified key from a supplied ParameterMap
        /** \tparam T Type of the parameter to be set.
         */
        template <typename T> void setParameter(const ParameterMap &parms,
                                                T &parm,
                                                const std::string &key);

        /// Loop over all vertices managed by the Displayable and call apply on them.
        virtual void for_each_vertex(function_on_fourspace_vertex apply) = 0;
        /// Loop over all vertices managed by the Displayable and their transformed
        /// images and call apply on them.
        /** This function is not pure virtual because it would be too tedious to
         *  require all implementing classes to provide an implementation.
         *
         *  The default implementation provided here throws an exception.
         */
        virtual void for_each_vertex_transformed(function_on_fourspace_and_transformed_vertex apply);
        /// Loop over all vertices managed by the Displayable, their transformed images
        /// and the projection into three-space and call apply on them.
        /** This function is not pure virtual because it would be too tedious to
        *  require all implementing classes to provide an implementation.
        *
        *  The default implementation provided here throws an exception.
        */
        virtual void for_each_vertex_transformed_projected(function_on_fourspace_transformed_and_projected_vertex apply);
        /// Loop over all vertices managed by the Displayable and call apply on them.
        virtual void for_each_projected(function_on_projected_vertex apply) = 0;

    protected:
        /// Function evaluation operator for three parameters
        /** \todo this is not general enough. should take the number of arguments
         *  that are actually needed.
         */
        virtual VecMath::Vector<4> &operator () (double, double, double);

        /// Numerical calculation of the derivatives in t, u and v
        /** \todo this is not general enough. should take the number of arguments
         *  that are actually needed.
         */
        virtual VecMath::MultiDimensionalVector< VecMath::Vector<4>, 1 > df (double, double, double);

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

namespace {
  static const DisplayableClass &displayable_class_root = DisplayableClass::makeRootNode("Displayable", "Objects");
}

#endif
