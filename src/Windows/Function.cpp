// Function.cpp: Implementierung der Klasse Function.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
//#include <strstream>

#include "Function.h"
#include "Matrix.h"


UINT Delete (void *);


///////////////////////////////////////////////////////////////////////////////

Function::Function ():
		tmin (0),	tmax (0),	dt (0),
		umin (0),	umax (0),	du (0),
		vmin (0),	vmax (0),	dv (0),
		tsteps (0), usteps (0), vsteps (0),
		F (4),
		Xscr (NULL), XscrChunk (NULL), Xtrans (NULL), XtransChunk (NULL),
		R (NULL), G (NULL), B (NULL), RGBChunk (NULL),
		NumVertices (0) { }


Function::Function (double _tmin, double _tmax, double _dt,
					double _umin, double _umax, double _du,
				    double _vmin, double _vmax, double _dv):
		tmin (_tmin),	tmax (_tmax),	dt (_dt),
		umin (_umin),	umax (_umax),	du (_du),
		vmin (_vmin),	vmax (_vmax),	dv (_dv),
		tsteps ((tmax-tmin)/dt+1), usteps ((umax-umin)/du+1), vsteps ((vmax-vmin)/dv+1),
		F (4),
		Xscr (NULL), XscrChunk (NULL), Xtrans (NULL), XtransChunk (NULL),
		R (NULL), G (NULL), B (NULL), RGBChunk (NULL),
		NumVertices (0) { }


//	initialize the temporary storage areas Xscr[][][], Xtrans[][][],
//										   R[][][], G[][][], B[][][]
void Function::InitMem (void) {
	XscrChunk = new Vector [(tsteps+2)*(usteps+2)*(vsteps+2)];
	Xscr = new Vector ** [tsteps+2];
	
	XtransChunk = new Vector [(tsteps+2)*(usteps+2)*(vsteps+2)];
	Xtrans = new Vector ** [tsteps+2];

	RGBChunk = new float [3*(tsteps+2)*(usteps+2)*(vsteps+2)];
	R = new float ** [tsteps+2];
	G = new float ** [tsteps+2];
	B = new float ** [tsteps+2];

	for (unsigned t = 0; t <= tsteps+1; t++) {
		
		Xscr[t] = new Vector * [usteps+2];
		Xtrans[t] = new Vector * [usteps+2];

		R[t] = new float * [usteps+2];
		G[t] = new float * [usteps+2];
		B[t] = new float * [usteps+2];
	
		for (unsigned u = 0; u <= usteps+1; u++) {
	
			Xscr[t][u] = XscrChunk+t*(tsteps+2)*(usteps+2)+u*(usteps+2);
			Xtrans[t][u] = XtransChunk+t*(tsteps+2)*(usteps+2)+u*(usteps+2);

			R[t][u] = RGBChunk+1*t*(tsteps+2)*(usteps+2)+u*(usteps+2);
			G[t][u] = RGBChunk+2*t*(tsteps+2)*(usteps+2)+u*(usteps+2);
			B[t][u] = RGBChunk+3*t*(tsteps+2)*(usteps+2)+u*(usteps+2);
		}					//	for (unsigned u = 0; u <= usteps+1; u++) 

	}						//	for (unsigned t = 0; t <= tsteps+1; t++) 
}							//	Initialize ()

void Function::Initialize () {
	X =  new Vector ** [tsteps+2];
	Xchunk  = new Vector   [(tsteps+2)*(usteps+2)*(vsteps+2)];

	for (unsigned t = 0; t <= tsteps+1; t++) {
		X[t] = new Vector * [usteps+2];
		for (unsigned u = 0; u <= usteps+1; u++) {
			X[t][u]  =  Xchunk+t*(usteps+2)*(vsteps+2)+u*(vsteps+2);
			for (unsigned v = 0; v <= vsteps+1; v++) {
				X[t][u][v] = f (tmin+t*dt, umin+u*du, vmin+v*dv);
			}
		}
	}
	InitMem ();
}

void Function::ReInit(double _tmin, double _tmax, double _dt,
					  double _umin, double _umax, double _du,
					  double _vmin, double _vmax, double _dv) {
	tmin = _tmin;	tmax = _tmax;	dt = _dt;
	umin = _umin;	umax = _umax;	du = _du;
	vmin = _vmin;	vmax = _vmax;	dv = _dv;
	tsteps = (tmax-tmin)/dt+1; usteps = (umax-umin)/du+1; vsteps = (vmax-vmin)/dv+1;
	
//	Free ();
	Delete (X);

//	for (unsigned t = 0; t <= tsteps+1; t++) 
//		delete [] X[t];
//	Delete (Xchunk);

	Initialize ();
}

void Function::SetParameters (double _a, double _b, double _c, double _d) {
//	ReInit (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
}

UINT Delete (void *x) {
	if (x) delete [] x;
	return 0; 
}


void Function::Free (void) {
	CWinThread *DelThread;
	for (unsigned u = 0; u <= usteps+1; u++) {
		for (unsigned v = 0; v <= vsteps+1; v++) {
			DelThread = AfxBeginThread (Delete, X[u][v]);
			DelThread = AfxBeginThread (Delete, Xscr[u][v]);
			DelThread = AfxBeginThread (Delete, Xtrans[u][v]);
			DelThread = AfxBeginThread (Delete, R[u][v]);
			DelThread = AfxBeginThread (Delete, G[u][v]);
			DelThread = AfxBeginThread (Delete, B[u][v]);
		}
		DelThread = AfxBeginThread (Delete, X[u]);
		DelThread = AfxBeginThread (Delete, Xscr[u]);
		DelThread = AfxBeginThread (Delete, Xtrans[u]);
		DelThread = AfxBeginThread (Delete, R[u]);
		DelThread = AfxBeginThread (Delete, G[u]);
		DelThread = AfxBeginThread (Delete, B[u]);
	}
	DelThread = AfxBeginThread (Delete, X);
	DelThread = AfxBeginThread (Delete, Xscr);
	DelThread = AfxBeginThread (Delete, Xtrans);
	DelThread = AfxBeginThread (Delete, R);
	DelThread = AfxBeginThread (Delete, G);
	DelThread = AfxBeginThread (Delete, B);
	DelThread = AfxBeginThread (Delete, Xchunk);
	DelThread = AfxBeginThread (Delete, XscrChunk);
	DelThread = AfxBeginThread (Delete, XtransChunk);
	DelThread = AfxBeginThread (Delete, RGBChunk);
}

Function::~Function() {
	Free ();
}

Vector &Function::normal (double tt, double uu, double vv) {
	static Vector n;

	Vector *D = df (tt, uu, vv);

	n = vcross (D[0], D[1], D[2]);
	vnormalize (n);

	return n; 
}


/*	numerical calculation of the derivatives in u and v:
		df		  f(u+h, v) - f (u)	  df
		-- =  lim -----------------,  -- analogously
		du   h->0		  h			  dv
*/
Vector *Function::df (double tt, double uu, double vv) {	

	static Vector F0 (3);			//	f (u, v)
	static double h = 1e-5;						//	maybe tweak to get best results

	static Vector DF[3];

	F0 = operator () (tt, uu, vv);							

	F = operator () (tt+h, uu, vv);							//	derive after u
	DF[0] = (F-F0)/h;			

	F = operator () (tt, uu+h, vv);							//	derive after v
	DF[1] = (F-F0)/h;

	F = operator () (tt, uu, vv+h);							//	derive after v
	DF[2] = (F-F0)/h;	

	return DF; }


void Function::Transform (double Thetaxy, double Thetaxz, double Thetaxw, double Thetayz, double Thetayw, double Thetazw,
						  double Tx, double Ty, double Tz, double Tw) {
	Matrix<4> Rxy = Matrix<4> (0, 1, Thetaxy), Rxz = Matrix<4> (0, 2, Thetaxz), Rxw = Matrix<4> (0, 3, Thetaxw),
			  Ryz = Matrix<4> (1, 2, Thetayz), Ryw = Matrix<4> (1, 3, Thetayw), Rzw = Matrix<4> (2, 3, Thetazw),
			  Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw, 
			  Rot = Rxyz*Rxwyz*Ryzw;
 	Vector Trans = Vector (Tx, Ty, Tz, Tw);
	
	for (unsigned t = 0; t <= tsteps+1; t++) {
		for (unsigned u = 0; u <= usteps+1; u++) 
			for (unsigned v = 0; v <= vsteps+1; v++)
				Xtrans[t][u][v] = (Rot*X[t][u][v])+Trans;
	}
}


void Function::Project (double ScrW, double CamW, bool DepthCue4D) {
	double ProjectionFactor;
	double Wmax = 0, Wmin = 0;

	for (unsigned t = 0; t <= tsteps+1; t++) {
		for (unsigned u = 0; u <= usteps+1; u++) 
			for (unsigned v = 0; v <= vsteps+1; v++) {

				if (Xtrans[t][u][v][3] < Wmin) Wmin = Xtrans[t][u][v][3];
				if (Xtrans[t][u][v][3] > Wmax) Wmax = Xtrans[t][u][v][3];

				ProjectionFactor = (ScrW-CamW)/(Xtrans[t][u][v][3]-CamW);

				for (unsigned i = 0; i <= 2; i++)
					Xscr[t][u][v][i] = ProjectionFactor*Xtrans[t][u][v][i];

				R[t][u][v] = float (t)/float (tsteps);								//	color scheme?
				G[t][u][v] = float (u)/float (usteps);
				B[t][u][v] = float (v)/float (vsteps);
			}
	}

 	if (!DepthCue4D) return;

 	for (t = 0; t <= tsteps+1; t++) 
 		for (unsigned u = 0; u <= usteps+1; u++) 
 			for (unsigned v = 0; v <= vsteps+1; v++) {
 				float DepthCueFactor = (Wmax-Xtrans[t][u][v][3])/(Wmax-Wmin)*0.9+0.1; //	??? !!!
 				R[t][u][v] = 0.1+(R[t][u][v]-0.1)*DepthCueFactor;
 				G[t][u][v] = 0.1+(G[t][u][v]-0.1)*DepthCueFactor;
 				B[t][u][v] = 0.1+(B[t][u][v]-0.1)*DepthCueFactor;
 			}
}


void Function::Draw (void) {
	for (unsigned t = 0; t < tsteps; t++) 
		DrawPlane (t);
}

	
void Function::DrawPlane (unsigned t){
	for (unsigned u = 0; u < usteps; u++) 
		DrawStrip (t, u);
}

void Function::DrawStrip (unsigned t, unsigned u){
	for (unsigned v = 0; v < vsteps; v++) 
		DrawCube (t, u, v);
}

void Function::DrawCube (unsigned t, unsigned u, unsigned v) {
	static Vector *V = new Vector [8];

	V[0] = Xscr[t][u][v];     V[1] = Xscr[t][u][v+1];
	V[2] = Xscr[t][u+1][v];   V[3] = Xscr[t][u+1][v+1];
	V[4] = Xscr[t+1][u][v];   V[5] = Xscr[t+1][u][v+1];
	V[6] = Xscr[t+1][u+1][v]; V[7] = Xscr[t+1][u+1][v+1];

	glBegin (GL_QUAD_STRIP);
 		if (t == 0) {
 			SetColor (R [t][u][v], G [t][u][v], B [t][u][v]);	
 			glVertex3dv (V[0].data ());
 			SetColor (R [t][u][v+1], G [t][u][v+1], B [t][u][v+1]);	
 			glVertex3dv (V[1].data ());
 			NumVertices += 2;
 		}
		SetColor (R [t][u+1][v], G [t][u+1][v], B [t][u+1][v]);	
		glVertex3dv (V[2].data ());
		SetColor (R [t][u+1][v+1], G [t][u+1][v+1], B [t][u+1][v+1]);	
		glVertex3dv (V[3].data ());
		SetColor (R [t+1][u+1][v], G [t+1][u+1][v], B [t+1][u+1][v]);	
		glVertex3dv (V[6].data ());
		SetColor (R [t+1][u+1][v+1], G [t+1][u+1][v+1], B [t+1][u+1][v+1]);	
		glVertex3dv (V[7].data ());
		SetColor (R [t+1][u][v], G [t+1][u][v], B [t+1][u][v]);	
		glVertex3dv (V[4].data ());
		SetColor (R [t+1][u][v+1], G [t+1][u][v+1], B [t+1][u][v+1]);	
		glVertex3dv (V[5].data ());		
 		NumVertices += 6;
 		if (u == 0) {
 			SetColor (R [t][u][v], G [t][u][v], B [t][u][v]);	
 			glVertex3dv (V[0].data ());
			SetColor (R [t][u][v+1], G [t][u][v+1], B [t][u][v+1]);	
			glVertex3dv (V[1].data ());
			NumVertices += 2;
		}
	glEnd ();

 	glBegin (GL_QUADS); 
 		if (v == 0) {	
 			SetColor (R [t][u][v], G [t][u][v], B [t][u][v]);	
 			glVertex3dv (V[0].data ());
 			SetColor (R [t][u+1][v], G [t][u+1][v], B [t][u+1][v]);	
 			glVertex3dv (V[2].data ());
 			SetColor (R [t+1][u+1][v], G [t+1][u+1][v], B [t+1][u+1][v]);	
 			glVertex3dv (V[6].data ());
 			SetColor (R [t+1][u][v], G [t+1][u][v], B [t+1][u][v]);	
 			glVertex3dv (V[4].data ());
 			NumVertices += 4;
 		}
 		SetColor (R [t][u][v+1], G [t][u][v+1], B [t][u][v+1]);	
 		glVertex3dv (V[1].data ());
 		SetColor (R [t][u+1][v+1], G [t][u+1][v+1], B [t][u+1][v+1]);	
 		glVertex3dv (V[3].data ());
 		SetColor (R [t+1][u+1][v+1], G [t+1][u+1][v+1], B [t+1][u+1][v+1]);	
 		glVertex3dv (V[7].data ());
 		SetColor (R [t+1][u][v+1], G [t+1][u][v+1], B [t+1][u][v+1]);	
 		glVertex3dv (V[5].data ());
 		NumVertices += 4;
 		
 	glEnd ();
}




///////////////////////////////////////////////////////////////////////////////

Hypersphere::Hypersphere (double _tmin, double _tmax, double _dt,
						  double _umin, double _umax, double _du,
						  double _vmin, double _vmax, double _dv,
						  double _rad):
		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
		Radius (_rad){
	Initialize ();
}

Hypersphere::~Hypersphere () { }


Vector &Hypersphere::f (double tt, double uu, double vv) {
	double sinphi = sin (pi/2*tt), cosphi = cos (pi/2*tt),	//  hypersphere
		   sintht = sin (pi*uu), costht = cos (pi*uu),
		   sinpsi = sin (pi*vv), cospsi = cos (pi*vv);
	F[0] = Radius*sinpsi*sintht*cosphi;
	F[1] = Radius*sinpsi*sintht*sinphi;
	F[2] = Radius*sinpsi*costht;
	F[3] = Radius*cospsi;

	return F; 
}

Vector &Hypersphere::normal (double tt, double uu, double vv) {
	static Vector n;

	n = f (tt, uu, vv);
	vnormalize (n);

	return n; 
}


///////////////////////////////////////////////////////////////////////////////

Torus1::Torus1 (double _tmin, double _tmax, double _dt,
			    double _umin, double _umax, double _du,
			    double _vmin, double _vmax, double _dv,
				double _R, double _r, double _rho):
		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
		R (_R), r (_r), rho (_rho) {
	Initialize ();
}

Torus1::~Torus1 () { }

Vector &Torus1::f (double tt, double uu, double vv) {
	F[0] =  cos (pi*tt)*(R+cos (pi*uu)*(r+rho*cos (pi*vv))); 
	F[1] =  sin (pi*tt)*(R+cos (pi*uu)*(r+rho*cos (pi*vv))); 
	F[2] =				   sin (pi*uu)*(r+rho*cos (pi*vv));  
	F[3] =								  rho*sin (pi*vv);   

	return F; 
}


///////////////////////////////////////////////////////////////////////////////

Torus2::Torus2 (double _tmin, double _tmax, double _dt,
			    double _umin, double _umax, double _du,
			    double _vmin, double _vmax, double _dv,
				double _R, double _r):
		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
		R (_R), r (_r) {
	Initialize ();
}

Torus2::~Torus2 () { }

Vector &Torus2::f (double tt, double uu, double vv) {
	F[0] =  cos (pi*tt)*(R+r*cos (pi*uu)*cos (pi*vv)); 
	F[1] =  cos (pi*tt)*(R+r*cos (pi*uu)*sin (pi*vv)); 
	F[2] =	cos (pi*tt)*(R+r*sin (pi*uu));
	F[3] =	sin (pi*tt)*R;								  

	return F; 
}


///////////////////////////////////////////////////////////////////////////////

Fr3r::Fr3r (double _tmin, double _tmax, double _dt,
		    double _umin, double _umax, double _du,
			double _vmin, double _vmax, double _dv):
		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

Fr3r::~Fr3r () { }


Vector &Fr3r::f (double tt, double uu, double vv) {
	F[0] = tt;
	F[1] = uu;
	F[2] = vv;
	double rsq = tt*tt+uu*uu+vv*vv;
	F[3] = 1/(rsq+.25);

	return F; }

///////////////////////////////////////////////////////////////////////////////

GravitationPotential::GravitationPotential (double xmin, double xmax, double dx,
											double ymin, double ymax, double dy,
											double zmin, double zmax, double dz,
											double _M, double _R):
		Function (xmin, xmax, dx, ymin, ymax, dy, zmin, zmax, dz),
		M (_M), R (_R) {
	Initialize ();
}


GravitationPotential::~GravitationPotential () { }

Vector &GravitationPotential::f (double tt, double uu, double vv) {
	const double G = 1;
	F[0] = tt;
	F[1] = uu;
	F[2] = vv;
	double rsq = tt*tt+uu*uu+vv*vv;
	if (rsq > R*R)
		F[3] = G*M/rsq;
	else 
		F[3] = G*M/(R*R*R)*sqrt (rsq);

	return F; 
}


///////////////////////////////////////////////////////////////////////////////

Fr3rSin::Fr3rSin (double _tmin, double _tmax, double _dt,
 				  double _umin, double _umax, double _du,
 				  double _vmin, double _vmax, double _dv):
 		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
 	Initialize ();
}
 
Fr3rSin::~Fr3rSin () { }
 
 
Vector &Fr3rSin::f (double tt, double uu, double vv) {
 	F[0] = tt;
 	F[1] = uu;
 	F[2] = vv;
	F[3] = sin (pi*(tt*tt+uu*uu+vv*vv));

	return F;
}


///////////////////////////////////////////////////////////////////////////////

Fr3rExp::Fr3rExp (double _tmin, double _tmax, double _dt,
 				  double _umin, double _umax, double _du,
 				  double _vmin, double _vmax, double _dv):
 		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
 	Initialize ();
}
 
Fr3rExp::~Fr3rExp () { }
 
 
Vector &Fr3rExp::f (double tt, double uu, double vv) {
 	F[0] = tt;
 	F[1] = uu;
 	F[2] = vv;
 	F[3] = exp (tt*tt+uu*uu+vv*vv);														
 
 	return F; }
 
 
///////////////////////////////////////////////////////////////////////////////

Polar::Polar (double _tmin, double _tmax, double _dt,
 			  double _umin, double _umax, double _du,
 			  double _vmin, double _vmax, double _dv):
 		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
 	Initialize ();
}
 
Polar::~Polar () { }
 
Vector &Polar::f (double tt, double uu, double vv) {
 	double sinphi = sin (pi*tt), cosphi = cos (pi*tt),	
 		   sintht = sin (pi*uu), costht = cos (pi*uu),
 		   sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
 		   Radius = sin (pi/3.*(tt+uu+vv));
 
 	F[0] = Radius*sinpsi*sintht*cosphi;
 	F[1] = Radius*sinpsi*sintht*sinphi;
 	F[2] = Radius*sinpsi*costht;
 	F[3] = Radius*cospsi;
 
 	return F; 
}
 
 
///////////////////////////////////////////////////////////////////////////////

PolarSin::PolarSin (double _tmin, double _tmax, double _dt,
 					double _umin, double _umax, double _du,
 					double _vmin, double _vmax, double _dv,
 					double _phase):
 		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
 		Phase (_phase) {
 	Initialize ();
}
 
PolarSin::~PolarSin () { }
 
Vector &PolarSin::f (double tt, double uu, double vv) {
 	double sinphi = sin (pi*tt), cosphi = cos (pi*tt),	
 		   sintht = sin (pi*uu), costht = cos (pi*uu),
 		   sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
 		   Radius = .5+fabs (sin (Phase*tt*uu*vv*pi));
 
	F[0] = Radius*sinpsi*sintht*cosphi;
 	F[1] = Radius*sinpsi*sintht*sinphi;
 	F[2] = Radius*sinpsi*costht;
 	F[3] = Radius*cospsi;
 
 	return F; 
}
 

///////////////////////////////////////////////////////////////////////////////

PolarSin2::PolarSin2 (double _tmin, double _tmax, double _dt,
 				 	  double _umin, double _umax, double _du,
 					  double _vmin, double _vmax, double _dv):
 		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv) {
 	Initialize ();
}
 
PolarSin2::~PolarSin2 () { }
 
Vector &PolarSin2::f (double tt, double uu, double vv) {
 	double sinphi = sin (pi*tt), cosphi = cos (pi*tt),	
 		   sintht = sin (pi*uu), costht = cos (pi*uu),
 		   sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
 		   Radius = sin (pi/3.*(tt+uu+vv));
 
	F[0] = Radius*sinpsi*sintht*cosphi;
 	F[1] = Radius*sinpsi*sintht*sinphi;
 	F[2] = Radius*sinpsi*costht;
 	F[3] = Radius*cospsi;
 
 	return F; 
}
 

///////////////////////////////////////////////////////////////////////////////

PolarR::PolarR (double _tmin, double _tmax, double _dt,
 				double _umin, double _umax, double _du,
 				double _vmin, double _vmax, double _dv,
 				double _phase):
 		Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
 		Phase (_phase) {
 	Initialize ();
}
 
PolarR::~PolarR () { }
 
Vector &PolarR::f (double tt, double uu, double vv) {
 	double sinphi = sin (pi*tt), cosphi = cos (pi*tt),	
 		   sintht = sin (pi*uu), costht = cos (pi*uu),
 		   sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
 		   Radius = sqrt (tt*tt+uu*uu+vv*vv);
 
	F[0] = Radius*sinpsi*sintht*cosphi;
 	F[1] = Radius*sinpsi*sintht*sinphi;
 	F[2] = Radius*sinpsi*costht;
 	F[3] = Radius*cospsi;
 
 	return F; 
}