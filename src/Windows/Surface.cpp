#include "stdafx.h"
//#include <strstream>

#include "Surface.h"
#include "Matrix.h"

UINT Delete (void *x);

///////////////////////////////////////////////////////////////////////////////

Surface::Surface ():
		umin (0),	umax (0),	du (0),
		vmin (0),	vmax (0),	dv (0),
		usteps (0), vsteps (0),
		F (4),
		Xscr (NULL), XscrChunk (NULL), Xtrans (NULL), XtransChunk (NULL),
		R (NULL), G (NULL), B (NULL), RGBChunk (NULL),
		NumVertices (0) { }


Surface::Surface (double _umin, double _umax, double _du,
				  double _vmin, double _vmax, double _dv):
		umin (_umin),	umax (_umax),	du (_du/2),
		vmin (_vmin),	vmax (_vmax),	dv (_dv/2),
		usteps ((umax-umin)/du+1), vsteps ((vmax-vmin)/dv+1),
		F (4),
		Xscr (NULL), XscrChunk (NULL), Xtrans (NULL), XtransChunk (NULL),
		R (NULL), G (NULL), B (NULL), RGBChunk (NULL),
		NumVertices (0) { }


//	initialize the temporary storage areas Xscr[][][], Xtrans[][][],
//										   R[][][], G[][][], B[][][]
void Surface::InitMem (void) {
	XscrChunk = new Vector [(usteps+2)*(vsteps+2)];
	Xscr = new Vector * [usteps+2];
	
	XtransChunk = new Vector [(usteps+2)*(vsteps+2)];
	Xtrans = new Vector * [usteps+2];

	RGBChunk = new float [3*(usteps+2)*(vsteps+2)];
	R = new float * [usteps+2];
	G = new float * [usteps+2];
	B = new float * [usteps+2];

	for (unsigned u = 0; u <= usteps+1; u++) {
	
		Xscr[u]   = XscrChunk+u*(usteps+2);
		Xtrans[u] = XtransChunk+u*(usteps+2);

		R[u] = RGBChunk+1*u*(usteps+2);
		G[u] = RGBChunk+2*u*(usteps+2);
		B[u] = RGBChunk+3*u*(usteps+2);
	}					//	for (unsigned u = 0; u <= usteps+1; u++) 
}							//	Initialize ()

void Surface::Initialize () {
		 X = new Vector * [usteps+2];
	Xchunk = new Vector   [(usteps+2)*(vsteps+2)];

	for (unsigned u = 0; u <= usteps+1; u++) {
		X[u]  =  Xchunk+u*(vsteps+2);
		for (unsigned v = 0; v <= vsteps+1; v++) {
			X[u][v] = f (umin+u*du, vmin+v*dv);
		}
	}

	InitMem ();
}

void Surface::SetParameters (double _a, double _b, double _c, double _d) {
//	ReInit (tmin, tmax, dt, umin, umax, du, vmin, vmax, dv);
}

void Surface::ReInit(double _tmin, double _tmax, double _dt,
					 double _umin, double _umax, double _du,
					 double _vmin, double _vmax, double _dv) {
	umin = _umin;	umax = _umax;	du = _du;
	vmin = _vmin;	vmax = _vmax;	dv = _dv;
	usteps = (umax-umin)/du+1; vsteps = (vmax-vmin)/dv+1;
	
//	Free ();
//	Delete (Xchunk); Delete (XscrChunk); Delete (XtransChunk);
	Delete (X); Delete (Xscr); Delete (Xtrans); Delete (R);
	Initialize ();
}

void Surface::Free (void) {
	CWinThread *DelThread;
	for (unsigned u = 0; u <= usteps+1; u++) {
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
/*
	for (unsigned u = 0; u <= usteps+1; u++) {
		Delete (X[u]);
		Delete (Xscr[u]);
		Delete (Xtrans[u]);
		Delete (R[u]);
		Delete (G[u]);
		Delete (B[u]);
	}
	Delete (X);
	Delete (Xscr);
	Delete (Xtrans);
	Delete (R);
	Delete (G);
	Delete (B);
	Delete (Xchunk);
	Delete (RGBChunk);
*/
}

Surface::~Surface() {
	Free ();
}

Vector &Surface::normal (double uu, double vv) {
	static Vector n;

	Vector *D = df (uu, vv);

	n = vcross (D[0], D[1], D[2]);
	vnormalize (n);

	return n; 
}


/*	numerical calculation of the derivatives in u and v:
		df		  f(u+h, v) - f (u)	  df
		-- =  lim -----------------,  -- analogously
		du   h->0		  h			  dv
*/
Vector *Surface::df (double uu, double vv) {	

	static Vector F0 (3);			//	f (u, v)
	static double h = 1e-5;						//	maybe tweak to get best results

	static Vector DF[3];

	F0 = operator () (uu, vv);							

	F = operator () (uu+h, vv);							//	derive after u
	DF[0] = (F-F0)/h;			

	F = operator () (uu, vv+h);							//	derive after v
	DF[1] = (F-F0)/h;

	DF[2] = (F-F0)/h;	

	return DF; }


void Surface::Transform (double Thetaxy, double Thetaxz, double Thetaxw, double Thetayz, double Thetayw, double Thetazw,
						  double Tx, double Ty, double Tz, double Tw) {
	Matrix<4> Rxw = Matrix<4> (0, 3, Thetaxw), Ryw = Matrix<4> (1, 3, Thetayw), Rzw = Matrix<4> (2, 3, Thetazw),
			  Rxwyw = Rxw*Ryw, Rot = Rxwyw*Rzw;
 	Vector Trans = Vector (Tx, Ty, Tz, Tw);
	
	for (unsigned u = 0; u <= usteps+1; u++) 
		for (unsigned v = 0; v <= vsteps+1; v++)
			Xtrans[u][v] = (Rot*X[u][v])+Trans;
}


void Surface::Project (double ScrW, double CamW, bool DepthCue4D) {
	double ProjectionFactor;
	double Wmax = 0, Wmin = 0;

	for (unsigned u = 0; u <= usteps+1; u++) 
		for (unsigned v = 0; v <= vsteps+1; v++) {

			if (Xtrans[u][v][3] < Wmin) Wmin = Xtrans[u][v][3];
			if (Xtrans[u][v][3] > Wmax) Wmax = Xtrans[u][v][3];

			ProjectionFactor = (ScrW-CamW)/(Xtrans[u][v][3]-CamW);

			for (unsigned i = 0; i <= 2; i++)
				Xscr[u][v][i] = ProjectionFactor*Xtrans[u][v][i];

			R[u][v] = float (u)/float (usteps);
			G[u][v] = float (v)/float (vsteps);
			B[u][v] = (Wmax-X[u][v][3])/(Wmax-Wmin);
		}

 	if (!DepthCue4D) return;

	for (u = 0; u <= usteps+1; u++) 
		for (unsigned v = 0; v <= vsteps+1; v++) {
			float DepthCueFactor = (Wmax-Xtrans[u][v][3])/(Wmax-Wmin)*0.9+0.1; //	??? !!!
			R[u][v] = 0.1+(R[u][v]-0.1)*DepthCueFactor;
			G[u][v] = 0.1+(G[u][v]-0.1)*DepthCueFactor;
			B[u][v] = 0.1+(B[u][v]-0.1)*DepthCueFactor;
		}
}


void Surface::Draw (void) {
	NumVertices = 0;

	for (unsigned u = 0; u < usteps; u++) 
		DrawStrip (u);
}

void Surface::DrawStrip (unsigned u){
	glBegin (GL_QUAD_STRIP);

	SetColor (R [u][0], G [u][0], B [u][0]);	
	glVertex3dv (Xscr[u][0].data ());
	SetColor (R [u+1][0], G [u+1][0], B [u+1][0]);	
	glVertex3dv (Xscr[u+1][0].data ());
	NumVertices += 2;

	for (unsigned v = 1; v <= vsteps; v++) {
 		SetColor (R [u][v], G [u][v], B [u][v]);	
 		glVertex3dv (Xscr[u][v].data ());
 		SetColor (R [u+1][v], G [u+1][v], B [u+1][v]);	
 		glVertex3dv (Xscr[u+1][v].data ());

		NumVertices += 2;
	}
 		
 	glEnd ();
}


///////////////////////////////////////////////////////////////////////////////

Surface1::Surface1 (double _umin, double _umax, double _du,
					double _vmin, double _vmax, double _dv):
		Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

Surface1::~Surface1 () { }


Vector &Surface1::f (double uu, double vv) {
	double sintht = sin (pi*uu), costht = cos (pi*uu),
		   sinpsi = sin (pi*vv), cospsi = cos (pi*vv),
		   Radius = 1;
	F[0] = Radius*sintht*sinpsi;
	F[1] = Radius*costht*sinpsi;
	F[2] = Radius*costht;
	F[3] = Radius*cospsi;

	return F; 
}


///////////////////////////////////////////////////////////////////////////////

Horizon::Horizon (double _umin, double _umax, double _du,
				  double _vmin, double _vmax, double _dv):
		Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

Horizon::~Horizon () { }


Vector &Horizon::f (double t, double phi) {
	t *= pi; phi *= pi/2;
	F[0] = (1-sin (t))*cos (phi);
	F[1] = (1-sin (t))*sin (phi);
	F[2] = (1+sin (t))*cos (phi);
	F[3] = (1+sin (t))*sin (phi);
	F *= 1./sqrt (2.)*cos (t);

	return F; 
}


///////////////////////////////////////////////////////////////////////////////

Torus3::Torus3 (double _umin, double _umax, double _du,
				  double _vmin, double _vmax, double _dv):
		Surface (_umin, _umax, _du, _vmin, _vmax, _dv) {
	Initialize ();
}

Torus3::~Torus3 () { }


Vector &Torus3::f (double theta, double phi) {
	theta *= pi; phi *= pi;
	F[0] = cos (theta);
	F[1] = sin (theta);
	F[2] = cos (phi);
	F[3] = sin (phi);

	return F; 
}



