
#if(!defined OBJECT_H)
#define OBJECT_H


#include <vector>

using namespace std;

#include "Function.h"


class Object: public Function {
public:
	Object (unsigned, unsigned);
	virtual ~Object ();
	virtual void ReInit (double _tmin, double _tmax, double _dt,
						 double _umin, double _umax, double _du,
						 double _vmin, double _vmax, double _dv) { }

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

	virtual void SetParameters (double _a = 0, double _b = 0, double _c = 0, double _d = 0) {
		a = _a; }

protected:
	void DeclareSquare (unsigned, unsigned, unsigned, unsigned, unsigned);

	double a;
};


///////////////////////////////////////////////////////////////////////////////

class Sponge: public Hypercube {
public:
	Sponge (unsigned level = 1, int distance = 1, double rad = 1, Vector Center = 0);
	virtual ~Sponge ();

	virtual void Transform (double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw,
							double Tx, double Ty, double Tz, double Tw);
	virtual void Project (double ScrW, double CamW, bool DepthCue4D);
	virtual void Draw (void);

protected:
	unsigned Level;
	vector<Hypercube *> List;
};


///////////////////////////////////////////////////////////////////////////////

class Simplex: public Object {
public:
	Simplex (): Object (5, 10) { }
	Simplex (const Vector &_Center, double _a = 1);
	virtual ~Simplex();

	virtual void SetParameters (double _a = 0, double _b = 0, double _c = 0, double _d = 0) {
		a = _a; }

protected:
	void DeclareTriangle (unsigned, unsigned, unsigned, unsigned);

	double a;
};


///////////////////////////////////////////////////////////////////////////////

class Pyramid: public Simplex {
public:
	Pyramid (unsigned level = 1, double rad = 1, Vector Center = 0);
	virtual ~Pyramid();

	virtual void Transform (double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw,
							double Tx, double Ty, double Tz, double Tw);
	virtual void Project (double ScrW, double CamW, bool DepthCue4D);
	virtual void Draw (void);

protected:
	unsigned Level;
	vector<Simplex *> List;
};

#endif