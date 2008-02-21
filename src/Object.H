
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


class Object: public Function {
public:
    Object (unsigned, unsigned);
    virtual ~Object ();
    virtual void ReInit (double, double, double,
			 double, double, double,
			 double, double, double);

    virtual void Transform (double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw,
			    double Tx, double Ty, double Tz, double Tw);
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    virtual void Draw (void);

protected:
    unsigned NumVertices, NumSurfaces;
    Vector *X,
	   *Xtrans,
	   *Xscr;
    float *R, *G, *B;

    unsigned *Surface[4];

    virtual Vector &f (double, double, double) { return F; }
};


///////////////////////////////////////////////////////////////////////////////

class Hypercube: public Object {
public:
    Hypercube (): Object (16, 24) { }
    Hypercube (const Vector &_Center, double _a = 1);
    virtual ~Hypercube();
  
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
    Vector center;
};


///////////////////////////////////////////////////////////////////////////////

class Sponge: public Hypercube {
public:
	Sponge (unsigned level = 1, int distance = 1, double rad = 1,
		Vector Center = Vector (4, 0., 0.,0., 0.));
	virtual ~Sponge ();

	virtual void Transform (double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw,
							double Tx, double Ty, double Tz, double Tw);
	virtual void Project (double ScrW, double CamW, bool DepthCue4D);
	virtual void Draw (void);

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
    Vector center;
};


///////////////////////////////////////////////////////////////////////////////

class Pyramid: public Object {
public:
    Pyramid (): Object (5, 10) { }
    Pyramid (const Vector &_Center, double _a = 1);
    virtual ~Pyramid();

    virtual void SetParameters (double _a = 0, double = 0, double = 0, double = 0) {
		a = _a; }

protected:
    virtual void Initialize();
    void DeclareTriangle (unsigned, unsigned, unsigned, unsigned);

    Vector center;
    double a;
};


///////////////////////////////////////////////////////////////////////////////

class Gasket: public Pyramid {
public:
    Gasket (unsigned level = 1, double rad = 1, 
	    Vector Center = Vector (4, 0., 0.,0., 0.));
    virtual ~Gasket();

    virtual void Transform (double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw,
			    double Tx, double Ty, double Tz, double Tw);
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    virtual void Draw (void);

protected:
    virtual void Initialize();
    virtual unsigned long MemRequired (void);
    unsigned Level;
    std::vector<Pyramid *> List;
    double rad;
    Vector center;
};

#endif
