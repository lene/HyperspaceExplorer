
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

#include <QString>

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

class FunctionBase {
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

        FunctionBase();
        FunctionBase (const QString &name,
                  double _tmin, double _tmax, double _dt,
                  double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv);
        virtual ~FunctionBase() { }

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

        /** @return The name of the function in cleartext                     */
        QString getFunctionName() const { return functionName; }
        /** @return number of parameters for the function                     */
        unsigned getNumParameters() { return parameterNames.size(); }
        /** @return the names of the parameters for the function              */
        std::vector<QString> getParameterNames() { return parameterNames; }
            /// Get a specified parameter name from the list
            /** @param i index of the wanted parameter
             *  @return name of the ith parameter                                 */
        QString getParameterName(unsigned i) {
            return i < parameterNames.size()? parameterNames[i]: ""; }

    protected:
            /// Function evaluation operator for three parameters
        virtual VecMath::Vector<4> &operator () (double, double, double) = 0;

        virtual vec4vec1D df (double, double, double);

        virtual void Initialize (void) = 0;

        virtual unsigned long MemRequired (void);

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

            /// temporary storage for the value of the function at a given point
        VecMath::Vector<4> F;

        unsigned NumVertices;
            
            /// the name of the function as a free-form string
        QString functionName;
            /// list of the names of parameters to the function
        std::vector<QString> parameterNames;

};

/// A \em Function is a generalized four-dimensional mathematical function
/** The \em Function class provides the evaluation of the function values,
 *  usually on a grid, together with methods to rotate and translate the
 *  resulting four-dimensional geometry in 4-space, to project the transformed
 *  geometry onto 3-space, and to draw the projected grid into an OpenGL display
 *  list.
 *
 *  abstract member:
 *      \li Vector &f (double, double, double);
 *
 *  virtual members:
 *      \li Vector *df (double, double, double);
 *      \li Vector &normal (double, double, double);
 *      \li Transform (double Rxy, double Rxz, double Rxw,
 *                     double Ryz, double Ryw, double Rzw,
 *                     double Tx, double Ty, double Tz, double Tw)
 *      \li Project (double ScrW, double CamW, bool DepthCue4D)
 *      \li Draw ()
 *      \li ReInit(double _tmin, double _tmax, double _dt,
 *                 double _umin, double _umax, double _du,
 *                 double _vmin, double _vmax, double _dv)
 *      \li SetParameters (double _a = 0, double _b = 0, double _c = 0, double _d = 0)
 *
 *  other useful members:
 *      \li Transform ()
 *      \li operator () (double t, double u, double v)
 *      \li Initialize ();
 *      \li InitMem ();
 *
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class RealBase: public FunctionBase {
    public:
        typedef VecMath::Vector<4> &function_type(double, double, double);

        RealBase() { }
        RealBase(const QString &name,
                 double _tmin, double _tmax, double _dt,
                 double _umin, double _umax, double _du,
                 double _vmin, double _vmax, double _dv):
            FunctionBase(name, _tmin, _tmax, _dt, _umin, _umax, _du,
                               _vmin, _vmax, _dv) { }
    protected:
        /// The mathematical function defining the Function object
        virtual VecMath::Vector<4> &f(double, double, double) = 0;
};

class SurfaceBase: public FunctionBase {
    public:
        typedef VecMath::Vector<4> &function_type(double, double);

        SurfaceBase() { }
        SurfaceBase(const QString &name,
                    double _tmin, double _tmax, double _dt,
                    double _umin, double _umax, double _du,
                    double _vmin, double _vmax, double _dv):
            FunctionBase(name, _tmin, _tmax, _dt, _umin, _umax, _du,
                               _vmin, _vmax, _dv) { }
    protected:
        /// The mathematical function defining the Function object
        virtual VecMath::Vector<4> &f(double, double) = 0;
};

#endif
