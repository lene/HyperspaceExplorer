//      project:      hyperspace explorer
//      module:       Function.H
//      contains:     class Function: abstract base class for all that follow
//		      implementations of the Function class
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(FUNCTION_H)
#define FUNCTION_H

#include <vector>
#include <map>

#include <QString>

#include "ParameterMap.H"
#include "Vector.H"

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

/// A \em Function is a generalized four-dimensional mathematical function
/** The \em Function interface provides abstract members for the evaluation of
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
 *  @todo Vector &normal (double, double, double); - or in derived classes?
 *  @todo  operator () (double t, double u, double v) - ditto
 *
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
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
        Function (const QString &name, ParameterMap _parms = ParameterMap());
        virtual ~Function() { }

        virtual void Transform (const VecMath::Rotation<4> &R,
//                                double Rxy, double Rxz, double Rxw,
//                                double Ryz, double Ryw, double Rzw,
                                const VecMath::Vector<4> &T) = 0;
        /// Overloaded function executing the transform to the default state
        void Transform() { Transform (VecMath::Rotation<4>(),  VecMath::Vector<4>()); }

        virtual void Project (double ScrW, double CamW, bool DepthCue4D) = 0;
        virtual void Draw (void) = 0;

        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv) = 0;
        /// Set parameters to the Function
        virtual void SetParameters(const ParameterMap &) {
            std::cerr << "Function::SetParameters()" << std::endl;
        }

        /** @return The name of the function in cleartext                     */
        QString getFunctionName() const { return functionName; }
        /** @return number of parameters for the function                     */
        unsigned getNumParameters() { return parameters.size(); }

        ParameterMap getParameters() { return parameters; }
        FunctionParameter *getParameter(QString name) {
            return parameters[name.toStdString()];
        }

        /// Set a parameter with a specified key from a supplied ParameterMap
        template <typename T> void setParameter(const ParameterMap &parms,
                                                T &parm,
                                                const std::string &key) {
            std::cerr<< "Function::SetParameter(";
            for (ParameterMap::const_iterator i = parameters.begin();
                 i != parms.end(); ++i) {
                std::cerr << i->second->getName() << ", " << T(*(i->second));
                if (i->second->getName() == key) parm = T(*(i->second));
            }
            std::cerr << ", " << parm << ", " << key << ") \n";
        }

        virtual unsigned getDefinitionSpaceDimensions() = 0;

    protected:
        /// Function evaluation operator for three parameters
        virtual VecMath::Vector<4> &operator () (double, double, double) = 0;

        void setVertex(const VecMath::Vector<4> &X, VecMath::Vector<3> &Xscr);

        virtual vec4vec1D df (double, double, double);

        virtual void Initialize (void) = 0;

        virtual unsigned long MemRequired (void);

//        void clearParameterNames() { parameterNames.clear(); }
        /// Add a parameter to the list of parameters
        template <typename T> void declareParameter(const std::string &,
                                                    const T &);
        /// Add a parameter to the list of parameters
        template <typename T> void declareParameter(const std::string &,
                const T &, const T &);

        void addVertices(unsigned num) { NumVertices += num; }

        void setfunctionName(const QString &_name) { functionName = _name; }

    private:
        void insertParameter(
            const std::pair<std::string, FunctionParameter *> &value) {
            parameters.insert(value);
        }

        /// temporary storage for the value of the function at a given point
        VecMath::Vector<4> F;

        unsigned NumVertices;

        /// the name of the function as a free-form string
        QString functionName;

        /// list of the parameters to the function
        ParameterMap parameters;
        /// list of the names of parameters to the function
        /** needed additionally to the ParameterMap, because the map does not
         *  keep the parameters in the order they are declared
         *  \todo move this functionality into ParameterMap                   */
        std::vector<std::string> parameterNames;
};

/// Add a parameter with a name and a default value to the parameter list
template <typename T> inline
        void Function::declareParameter(const std::string &_name,
                                        const T &_default) {
            parameterNames.push_back(_name);
            if (parameters.find(_name) == parameters.end()) {
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
            parameterNames.push_back(_name);
            if (parameters.find(_name) == parameters.end()) {
                insertParameter(
                    std::make_pair(_name,
                        ParameterFactory::Instance().
                            createParameterWithDefault(_name, _default)));
                parameters[_name]->setValue(new FunctionParameterValue<T>(_value));
            }
        }
#endif
