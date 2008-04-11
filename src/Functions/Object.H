
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:       helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)


#if(!defined OBJECT_H)
#define OBJECT_H


#include <vector>
#include <sstream>
#include <string>

#include "Function.H"
#include "Vector.H"

struct EmptyType {};

/// Generalized four-dimensional Object, described by vertexes and surfaces
/** an Object is a four-dimensional geometrical object which can not be
 *  described as a mathematical function from R³ to R or from R² to R^4.
 *  Instead it is described as a set of surfaces.
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Object: public Function {
    public:
        /// a one-dimensional array of unsigned, implemented as a std::vector
        typedef std::vector<unsigned> uintvec1D;
        /// a two-dimensional array of unsigned, implemented as a nested std::vector
        typedef std::vector<uintvec1D> uintvec2D;

        Object (const QString &, unsigned, unsigned);
        virtual ~Object () { }
        virtual void ReInit (double, double, double,
                             double, double, double,
                             double, double, double);

        virtual void Transform (double Rxy, double Rxz, double Rxw,
                                double Ryz, double Ryw, double Rzw,
                                double Tx, double Ty, double Tz, double Tw);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);
        virtual VecMath::Vector<4> &operator () (double, double, double) {
            return F;
        }

        virtual unsigned getTsteps() const { return NumVertices; }
        virtual unsigned getUsteps() const { return 1; }
        virtual unsigned getVsteps() const { return 1; }

        virtual double getTmin() const { return -1; }
        virtual double getTmax() const { return 1; }
        virtual double getUmin() const { return -1; }
        virtual double getUmax() const { return 1; }
        virtual double getVmin() const { return -1; }
        virtual double getVmax() const { return 1; }

    protected:
        /// number of vertices the object possesses; must be set by implementations
        unsigned NumVertices;
        /// number of surfaces the object possesses; must be set by implementations
        unsigned NumSurfaces;

        vec4vec1D X;        ///< temporary storage for the function values
        vec4vec1D Xtrans;   ///< temp. storage for transformed function values
        vec3vec1D Xscr;     ///< temporary storage for projected function values

        /** storage for the coloring of the vertices - red component
         *  @todo turn these three arrays into a single array of Color's      */
        floatvec1D R;
        /** storage for the coloring of the vertices - red component
         *  @todo turn these three arrays into a single array of Color's      */
        floatvec1D G;
        /** storage for the coloring of the vertices - red component
         *  @todo turn these three arrays into a single array of Color's      */
        floatvec1D B;

        /// the surfaces, stored as vectors of indeces to the points in X
        uintvec2D Surface;

        /** A pointless function, but it must be overridden to satisfy the
         *  Function interface. In an Object it is never called because the
         *  four-dimensional object is represented by a list of surfaces instead
         *  of a mathematical function.                                       */
        virtual VecMath::Vector<4> &f (double, double, double) { return F; }
};


///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional cube
/** \ingroup ObjectGroup                                                    */
class Hypercube: public Object {
public:
    Hypercube (): Object ("Hypercube", 16, 24) {
        parameterNames.push_back("Size");
    }
    Hypercube (double _a, const VecMath::Vector<4> &_Center = VecMath::Vector<4>(0., 0., 0., 0.));
    virtual ~Hypercube() { }

    virtual void SetParameters (double _a = 0,
                                double = 0, double = 0, double = 0) {
        a = _a; }

    virtual std::string description () {
        std::ostringstream out;
        out << "Hypercube (a = " << a << ")" << std::ends;
        return out.str ();
    }
protected:
    virtual void Initialize();
    void DeclareSquare (unsigned, unsigned, unsigned, unsigned, unsigned);

    double a;
    VecMath::Vector<4> center;
};


///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional Menger Sponge.
/** A Menger Sponge in three dimensions is a fractal produced by subdividing
 *  a cube and taking away parts of the cube which get subsequentally
 *  smaller. The \em level parameter controls how often this process is repeated,
 *  i.e. how many holes there are in the final object. \n
 *  A four-dimensional Menger Sponge is created analogously from a hypercube.\n
 *  The fractal can be further controlled by the \em distance parameter:
 *  \li \em distance = 0: Only the innermost cube is removed, resulting in a
 *      four-dimensional foam with connected body and disjoint holes.
 *  \li \em distance = 1: the innermost and the next to innermost cubes are
 *      removed, which results in a foam in three dimensions, but has holes in
 *      the four-dimensional structure.
 *  \li \em distance = 2: the holes reach the surface of the cube, resulting in
 *      a sponge structure - both the holes and the cubes ("curd") are
 *      connected.
 *  \li \em distance = 3: only the corners of the hypercube remain, resulting in
 *      dust - the "curd" is disjoint, the holes are connected.
 *  \ingroup ObjectGroup                                                    */
class Sponge: public Hypercube {
public:
    /// Sponge constructor
    /** @param _level hypersponge level
     *  @param _distance distance of subcubes to center to be counted as part of
     *                   the fractal
     *                   \li = 0: solid hypercube
     *                   \li = 1: foam
     *                   \li = 2: sponge
     *                   \li = 3: dust
     *                   \li >= 4: nothing
     *  @param _rad side_length/2
     *  @param _center center                                                 */
    Sponge (unsigned _level = 1, int _distance = 1, double _rad = 1,
            VecMath::Vector<4> _center = VecMath::Vector<4>(0., 0.,0., 0.));
    virtual ~Sponge ();

    virtual void Transform (double Rxy, double Rxz, double Rxw,
                            double Ryz, double Ryw, double Rzw,
                            double Tx, double Ty, double Tz, double Tw);
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    virtual void Draw (void);

    /** @param a Sponge level
     *  @param b Distance (see Initialize())
     *  @param c Sponge size                                                  */
    virtual void SetParameters (double _a = 0, double _b = 0, double _c = 0,
                                double = 0) {
        Level = (unsigned)_a;
        distance = (int)_b;
        rad = _c;
    }

    /// Rebuild the Sponge if the parameters have changed
    virtual void ReInit (double, double, double,
                         double, double, double,
                         double, double, double) {
        List.clear();
        Object::ReInit(0,0,0,0,0,0,0,0,0);
    }

    /** @return A string with a description of the Hypersponge object         */
    virtual std::string description () {
        std::ostringstream out;
        out << "Sponge (level = " << Level << ")" << std::ends;
        return out.str ();
    }

protected:
    virtual void Initialize();
    virtual unsigned long MemRequired (unsigned);
    unsigned Level;                 ///< Level of the hypersponge

    /// List of sub-sponges (see Initialize())
    /** @todo Use smart pointers instead of a simple pointer-to-object        */
    std::vector<Hypercube *> List;

    int distance;                   ///< max. distance (see Initialize())
    double rad;                     ///< radius, more correctly size, of the sponge
    VecMath::Vector<4> center;      ///< center of the sponge
};


///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional pyramid, also known as hypersimplex
/** \ingroup ObjectGroup                                                    */
class Pyramid: public Object {
public:
    Pyramid (): Object ("Hyperpyramid", 5, 10) {
        parameterNames.push_back("Size");
    }
    Pyramid (double _a, const VecMath::Vector<4> &_Center = VecMath::Vector<4> (0., 0., 0., 0.));
    virtual ~Pyramid() { }

    virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) {
        a = _a;
    }

protected:
    virtual void Initialize();
    void DeclareTriangle (unsigned, unsigned, unsigned, unsigned);

    VecMath::Vector<4> center;
    double a;
};


///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional version of the Sierpinski Gasket.
/** This object is similar to the Menger Sponge, but it uses a Hypersimplex as
 *  generator.
 *
 *  It lacks the \p distance parameter, because there is only one way
 *  to generate a Sierpinski Gasket of level \p n. Otherwise it is analogous to
 *  the Menger Sponge fractal.
 *  \ingroup ObjectGroup                                                      */
class Gasket: public Pyramid {
    public:
        Gasket (unsigned level = 1, double rad = 1,
                VecMath::Vector<4> Center = VecMath::Vector<4> (0., 0.,0., 0.));
        virtual ~Gasket() { }

        virtual void Transform (double Rxy, double Rxz, double Rxw,
                                double Ryz, double Ryw, double Rzw,
                                double Tx, double Ty, double Tz, double Tw);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);
        virtual void SetParameters (double _a = 0, double _b = 0,
                                    double = 0, double = 0) {
            Level = (unsigned)_a;
            rad = _b;
        }
        virtual void ReInit (double, double, double,
                             double, double, double,
                             double, double, double) {
            List.clear();
            Object::ReInit(0,0,0,0,0,0,0,0,0);
        }

    protected:
        virtual void Initialize();
        virtual unsigned long MemRequired (void);
        unsigned Level;
        std::vector<Pyramid *> List;
        double rad;
        VecMath::Vector<4> center;
};

#endif
