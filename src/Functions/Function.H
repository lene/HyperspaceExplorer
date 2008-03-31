
//      project:      hyperspace explorer
//      module:       Function.H
//      contains:     class Function: abstract base class for all that follow
//		      implementations of the Function class
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(FUNCTION_H)
#define FUNCTION_H

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

        /// Type of the function used to generate values
        /** Optimized by using a reference as return value.                   */
        typedef VecMath::Vector<4> &function_type (double, double, double);
        /// The real, raw type of the function used to generate values
        typedef VecMath::Vector<4> raw_function_type (double, double, double);

        Function();
        Function (const QString &name,
                  double _tmin, double _tmax, double _dt,
                  double _umin, double _umax, double _du,
                  double _vmin, double _vmax, double _dv);
        virtual ~Function() { }

        virtual void Transform (double Rxy, double Rxz, double Rxw,
                                double Ryz, double Ryw, double Rzw,
                                double Tx, double Ty, double Tz, double Tw);
        /// Overloaded function executing the transform to the default state
        void Transform (void) { Transform (0, 0, 0, 0, 0, 0,  0, 0, 0, 0); }

        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);

        virtual void ReInit(double _tmin, double _tmax, double _dt,
                double _umin, double _umax, double _du,
                double _vmin, double _vmax, double _dv);
        virtual void SetParameters (double _a = 0, double _b = 0,
                                    double _c = 0, double _d = 0);

        /// Function evaluation operator
        /** As optimization, returns the precomputed value on the grid point
         *  closest to (t, u, v)
         *  @param t first argument, e.g. x or t
         *  @param u second argument, e.g. y or u
         *  @param v third argument, e.g. z or v
         *  @return f(t, u, v), approximated by the value on the grid point
         *          closest to (t, u, v)                                      */
        VecMath::Vector<4> &operator () (double t, double u, double v) {
            unsigned it = unsigned ((t-tmin)/dt),
                     iu = unsigned ((u-umin)/du),
                     iv = unsigned ((v-vmin)/dv);
            return X[it][iu][iv];
        }

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
        /// The mathematical function defining the Function object
        virtual function_type f = 0;
        virtual vec4vec1D df (double, double, double);
        virtual function_type normal;

        virtual void Initialize (void);
        void InitMem (void);

        virtual unsigned long MemRequired (void);

        void DrawPlane (unsigned);
        void DrawStrip (unsigned, unsigned);
        void DrawCube (unsigned, unsigned, unsigned);

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

        /// counter for the number of GL vertices used drawing the function
        unsigned NumVertices;

        /// temporary storage for the value of the function at a given point
        VecMath::Vector<4> F;

        vec4vec3D X,      ///< temporary storage for function values on grid
                  Xtrans; ///< temporary storage for transformed function values
        vec3vec3D Xscr;   ///< temporary storage for projected function values

        /// storage for the coloring of the vertices - red component
        /** @todo turn these three arrays into a single array of Color's      */
        floatvec3D R;
        /// storage for the coloring of the vertices - red component
        /** @todo turn these three arrays into a single array of Color's      */
        floatvec3D G;
        /// storage for the coloring of the vertices - red component
        /** @todo turn these three arrays into a single array of Color's      */
        floatvec3D B;

        /// the name of the function as a free-form string
        QString functionName;
        /// list of the names of parameters to the function
        std::vector<QString> parameterNames;

};

#endif
