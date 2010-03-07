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

        Function();
        Function (const QString &name, ParameterMap parameters = ParameterMap());
        virtual ~Function() { }

        /// Execute the desired rotation and translation to the Function object
        virtual void Transform (const VecMath::Rotation<4> &R,
                                const VecMath::Vector<4> &T) = 0;
        /// Overloaded function executing the transform to the default state
        void Transform() { Transform (VecMath::Rotation<4>(),  VecMath::Vector<4>()); }

        /// Projects the vertex data to 3D
        virtual void Project (double ScrW, double CamW, bool DepthCue4D) = 0;

        /// Draw the function
        /** This method is overridden in all descendants */
        virtual void Draw (void) = 0;

        /// Called when a Function must be created anew
        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv) = 0;

        /// Called by the ColorManager after setting the Function on the CM
        virtual void calibrateColors() const = 0;

        /// Set parameters to the Function
        /** \todo This function is only there to provide an interface, and it's
         *  not abstract so that Function s which don't have Parameters don't
         *  need to reimplement an unneeded method. But the present implementation
         *  does not make sense.
         */
        virtual void SetParameters(const ParameterMap &) {
            std::cerr << "Function::SetParameters()" << std::endl;
        }

        /** \return The name of the function in cleartext                     */
        virtual QString getFunctionName() const { return _functionName; }
        /** \return number of parameters for the function                     */
        unsigned getNumParameters() { return _parameters.size(); }

        /// \return The collection of all parameters (and their values)
        ParameterMap getParameters() { return _parameters; }
        /// \return The value of the parameter which is named \p name
        FunctionParameter *getParameter(const QString &name) {
          std::string key = name.toStdString();
          return _parameters.getParameter(key);
        }

        /// Set a parameter with a specified key from a supplied ParameterMap
        template <typename T> void setParameter(const ParameterMap &parms,
                                                T &parm,
                                                const std::string &key) {
            std::cerr<< "Function::SetParameter(";
            for (ParameterMap::const_iterator i = _parameters.begin();
                 i != parms.end(); ++i) {
                std::cerr << i->second->getName() << ", " << T(*(i->second));
                if (i->second->getName() == key) parm = T(*(i->second));
            }
            std::cerr << ", " << parm << ", " << key << ") \n";
        }

        /// number of argument given to the defining function
        virtual unsigned getDefinitionSpaceDimensions() = 0;

    protected:
        /// Function evaluation operator for three parameters
        virtual VecMath::Vector<4> &operator () (double, double, double) = 0;

        /// Set a color and a vertex datum in OpenGL
        /** \todo Make this independent from the rendering subsystem */
        void setVertex(const VecMath::Vector<4> &X, VecMath::Vector<3> &Xscr);

        virtual vec4vec1D df (double, double, double);

        /// This abstract function is called in the constructor of descendants
        virtual void Initialize (void) = 0;

        virtual unsigned long MemRequired (void);

//        void clearParameterNames() { parameterNames.clear(); }
        /// Add a parameter to the list of parameters
        template <typename T> void declareParameter(const std::string &,
                                                    const T &);
        /// Add a parameter to the list of parameters
        template <typename T> void declareParameter(const std::string &,
                const T &, const T &);

        /// Remember that we've set some more vertices
        void addVertices(unsigned num) { _numVertices += num; }

        /// Define the name of the Function
        void setfunctionName(const QString &_name) { _functionName = _name; }

        /// temporary storage for the value of the function at a given point
        VecMath::Vector<4> _F;

    private:
        /// Declare a new parameter for the Function
        void insertParameter(
            const std::pair<std::string, FunctionParameter *> &value) {
            _parameters.insert(value);
        }


        /// counter for assessing how much RAM is used
        unsigned _numVertices;

        /// the name of the function as a free-form string
        QString _functionName;

        /// list of the parameters to the function
        ParameterMap _parameters;
        /// Ordered list of the names of parameters to the function
        /** needed additionally to the ParameterMap, because the map does not
         *  keep the parameters in the order they are declared.
         *  \todo move this functionality into ParameterMap                   */
        std::vector<std::string> _parameterNames;
        
};

/// Add a parameter with a name and a default value to the parameter list
template <typename T> inline
        void Function::declareParameter(const std::string &_name,
                                        const T &_default) {
            _parameterNames.push_back(_name);
            if (_parameters.find(_name) == _parameters.end()) {
                insertParameter(
                    std::make_pair(_name,
                        ParameterFactory::Instance().
                            createParameterWithDefault(_name, _default)));
            }
        }

/// Add a parameter with a name and a default value to the parameter list
template <typename T> inline
        void Function::declareParameter(const std::string &_name,
                                        const T &_default, const T &_value) {
            _parameterNames.push_back(_name);
            if (_parameters.find(_name) == _parameters.end()) {
                insertParameter(
                    std::make_pair(_name,
                        ParameterFactory::Instance().
                            createParameterWithDefault(_name, _default)));
                _parameters[_name]->setValue(new FunctionParameterValue<T>(_value));
            }
        }
#endif
