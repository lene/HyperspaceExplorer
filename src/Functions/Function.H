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
        /// the container a function's parameters are stored in

        Function();
        Function (const QString &name,
                  double _tmin, double _tmax, double _dt,
                  double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv,
                  ParameterMap _parms = ParameterMap());
        virtual ~Function() { }

        virtual void Transform (double Rxy, double Rxz, double Rxw,
                                double Ryz, double Ryw, double Rzw,
                                double Tx, double Ty, double Tz, double Tw) = 0;
        /// Overloaded function executing the transform to the default state
        void Transform (void) { Transform (0, 0, 0, 0, 0, 0,  0, 0, 0, 0); }

        virtual void Project (double ScrW, double CamW, bool DepthCue4D) = 0;
        virtual void Draw (void) = 0;

        virtual void ReInit(double _tmin, double _tmax, double _dt,
                            double _umin, double _umax, double _du,
                            double _vmin, double _vmax, double _dv) = 0;
        virtual void SetParameters (double _a = 0, double _b = 0,
                                    double _c = 0, double _d = 0);
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

        virtual unsigned getTsteps() const { return tsteps > 0? tsteps: 1; }
        virtual unsigned getUsteps() const { return usteps > 0? usteps: 1; }
        virtual unsigned getVsteps() const { return vsteps > 0? vsteps: 1; }

        double &getTmin() { return tmin; }
        virtual double getTmin() const { return tmin; }
        double &getTmax() { return tmax; }
        virtual double getTmax() const { return tmax; }
        double &getDt() { return dt; }
        const double &getDt() const { return dt; }
        double &getUmin() { return umin; }
        virtual double getUmin() const { return umin; }
        double &getUmax() { return umax; }
        virtual double getUmax() const { return umax; }
        double &getDu() { return du; }
        const double &getDu() const { return du; }
        double &getVmin() { return vmin; }
        virtual double getVmin() const { return vmin; }
        double &getVmax() { return vmax; }
        virtual double getVmax() const { return vmax; }
        double &getDv() { return dv; }
        const double &getDv() const { return dv; }

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

        void addVertices(unsigned num) { NumVertices += num; }

    private:
    protected:  //  only until I sorted out bad design in derived classes
        double tmin, ///< min. value of the first parameter, here called t
               tmax, ///< min. value of the first parameter, here called t
               dt,   ///< stepsize in first parameter
               umin, ///< min. value of the second parameter, here called u
               umax, ///< min. value of the second parameter, here called u
               du,   ///< stepsize in second parameter
               vmin, ///< min. value of the third parameter, here called v
               vmax, ///< min. value of the third parameter, here called v
               dv;   ///< stepsize in third parameter

        unsigned tsteps, ///< number of steps in t
                 usteps, ///< number of steps in u
                 vsteps; ///< number of steps in v

    private:  //  only until I sorted out bad design in derived classes
        /// temporary storage for the value of the function at a given point
        VecMath::Vector<4> F;

        unsigned NumVertices;

    protected:  //  only until I sorted out bad design in derived classes
        /// the name of the function as a free-form string
        QString functionName;
    private:
        void insertParameter(
            const std::pair<std::string, FunctionParameter *> &value) {
            parameters.insert(value);
        }
        /// list of the names of parameters to the function
//        std::vector<QString> parameterNames;
        ParameterMap parameters;
};

/// Add a parameter with a name and a default value to the parameter list
template <typename T> inline
        void Function::declareParameter(const std::string &_name,
                                        const T &_default) {
            //  temporary measure to avoid code breaking when newParameterName()
            //  is replaced with declareParameter()
//            parameterNames.push_back(QString(_name.c_str()));
            if (parameters.find(_name) == parameters.end()) {
                insertParameter(
                    std::make_pair(_name,
                        ParameterFactory::Instance().
                            createParameterWithDefault(_name, _default)));
            }
        }

/// \em RealBase provides a base class for functions which take three parameters
/** The \em RealBase interface provides abstract members for the evaluation of
 *  the function values on a three-dimensional grid.
 *
 *  abstract member:
 *      \li Vector &f (double, double);
 *
 *  member:
 *      \li operator () (double t, double u, double);
 *
 *  @todo Vector &normal (double, double, double); - or in base class?
 *
 *  \ingroup RealGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class RealBase: public Function {
    public:
        /** type of the function used to generate values, optimized with a
         *  reference as return value                                         */
        typedef VecMath::Vector<4> &function_type(double, double, double);
        /// the real, raw type of the function used to generate values
        typedef VecMath::Vector<4> raw_function_type (double, double, double);

        RealBase() { }
        RealBase(const QString &name,
                 double _tmin, double _tmax, double _dt,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv,
                 ParameterMap _parms = ParameterMap()):
            Function(name, _tmin, _tmax, _dt, _umin, _umax, _du,
                     _vmin, _vmax, _dv, _parms) { }
    protected:
        /// The mathematical function defining the Function object
        virtual VecMath::Vector<4> &f(double, double, double) = 0;
        /// Function evaluation operator for three parameters
        /** @param t first argument, e.g. x or t
         *  @param u second argument, e.g. y or u
         *  @param v third argument, e.g. z or v
         *  @return f(t, u, v)                                                */
        VecMath::Vector<4> &operator () (double t, double u, double v) {
            return f(t,u,v);
        }
};

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
                    double _vmin, double _vmax, double _dv):
            Function(name, _tmin, _tmax, _dt, _umin, _umax, _du,
                               _vmin, _vmax, _dv) { }
    protected:
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

};

#endif
