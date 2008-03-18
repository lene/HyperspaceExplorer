
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if(!defined OBJECT_H)
#define OBJECT_H


#include <vector>
#include <sstream>
#include <string>

#include "Function.H"
#include "Vector.H"

/** an Object is a four-dimensional geometrical object which can not be
 *  described as a mathematical function from R³ to R or from R² to R^4.
 *  Instead it is described as a set of surfaces.
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Object: public Function {
    public:
        Object (const QString &, unsigned, unsigned);
        virtual ~Object ();
        virtual void ReInit (double, double, double,
                             double, double, double,
                             double, double, double);

        virtual void Transform (double Rxy, double Rxz, double Rxw,
                                double Ryz, double Ryw, double Rzw,
                                double Tx, double Ty, double Tz, double Tw);
        virtual void Project (double ScrW, double CamW, bool DepthCue4D);
        virtual void Draw (void);

    protected:
        unsigned NumVertices, NumSurfaces;
        VecMath::Vector<4> *X, *Xtrans;
        VecMath::Vector<3> *Xscr;
        float *R, *G, *B;

        unsigned *Surface[4];

        virtual VecMath::Vector<4> &f (double, double, double) { return F; }
};


///////////////////////////////////////////////////////////////////////////////

/** a four-dimensional cube */
class Hypercube: public Object {
public:
    Hypercube (): Object ("Hypercube", 16, 24) {
        parameterNames.push_back("Size");
    }
    Hypercube (double _a, const VecMath::Vector<4> &_Center = VecMath::Vector<4>(0., 0., 0., 0.));
    virtual ~Hypercube() { }

    virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) {
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

/** A four-dimensional Menger Sponge.\n
 *  A Menger Sponge in three dimensions is a fractal produced by subdividing
 *  a cube and taking away parts of the cube which get subsequentally
 *  smaller.\n
 *  A four-dimensional Menger Sponge is created analogously from a hypercube.\n
 *  The fractal can be further controlled by the distance parameter:
 *  \li distance = 0: Only the innermost cube is removed, resulting in a
 *  four-dimensional foam
 *  \li distance = 1: the innermost and the next to innermost cubes are removed,
 *  resulting in a foam in three dimensions, but holes in the four-dimensional
 *  structure
 *  \li distance = 2: the holes reach the surface of the cube, resulting in a
 *  sponge structure
 *  \li distance = 3: only the corners of the hypercube remain, resulting in
 *  dust
 */
class Sponge: public Hypercube {
public:
    Sponge (unsigned level = 1, int distance = 1, double rad = 1,
            VecMath::Vector<4> Center = VecMath::Vector<4>(0., 0.,0., 0.));
    virtual ~Sponge ();

    virtual void Transform (double Rxy, double Rxz, double Rxw,
                            double Ryz, double Ryw, double Rzw,
			    double Tx, double Ty, double Tz, double Tw);
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    virtual void Draw (void);

    virtual void SetParameters (double _a = 0, double _b = 0, double _c = 0,
                                double = 0) {
	Level = (unsigned)_a;
	distance = (int)_b;
	rad = _c;
    }

    virtual void ReInit (double, double, double,
			 double, double, double,
			 double, double, double) {
	List.clear();
	Object::ReInit(0,0,0,0,0,0,0,0,0);
    }

    virtual std::string description () {
	std::ostringstream out;
	out << "Sponge (level = " << Level << ")" << std::ends;
	return out.str ();
    }
protected:
    virtual void Initialize();
    virtual unsigned long MemRequired (unsigned);
    unsigned Level;
    std::vector<Hypercube *> List;
    int distance;
    double rad;
    VecMath::Vector<4> center;
};


///////////////////////////////////////////////////////////////////////////////

/** A four-dimensional pyramid, also known as hypersimplex */
class Pyramid: public Object {
public:
    Pyramid (): Object ("Hyperpyramid", 5, 10) {
        parameterNames.push_back("Size");
    }
    Pyramid (double _a, const VecMath::Vector<4> &_Center = VecMath::Vector<4> (0., 0., 0., 0.));
    virtual ~Pyramid() { }

    virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) {
		a = _a; }

protected:
    virtual void Initialize();
    void DeclareTriangle (unsigned, unsigned, unsigned, unsigned);

    VecMath::Vector<4> center;
    double a;
};


///////////////////////////////////////////////////////////////////////////////

/** A four-dimensional version of the Sierpinski Gasket.\n
 *  It is similar to the Menger Sponge, but it uses a Hypersimplex as generator.
 */
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
