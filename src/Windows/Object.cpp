

#include "stdafx.h"

#include "Object.h"
#include "Matrix.h"

///////////////////////////////////////////////////////////////////////////////

Object::Object (unsigned vertices, unsigned surfaces):
		Function (),
		NumVertices (vertices), NumSurfaces (surfaces) {
	X	   = new Vector [NumVertices];
	Xtrans = new Vector [NumVertices];
	Xscr   = new Vector [NumVertices];
	R = new float [NumVertices];
	G = new float [NumVertices];
	B = new float [NumVertices];
	for (unsigned i = 0; i < 4; i++)
		Surface[i] = new unsigned [NumSurfaces];
}		

Object::~Object () {
	delete [] X;
	delete [] Xtrans;
	delete [] Xscr;
	delete [] R;
	delete [] G;
	delete [] B;
	for (unsigned i = 0; i < 4; i++)
		delete [] Surface[i];
}


void Object::Transform (double Thetaxy, double Thetaxz, double Thetaxw, double Thetayz, double Thetayw, double Thetazw,
						  double Tx, double Ty, double Tz, double Tw) {
	Matrix<4> Rxw = Matrix<4> (0, 3, Thetaxw), Ryw = Matrix<4> (1, 3, Thetayw), Rzw = Matrix<4> (2, 3, Thetazw),
			  Rxwyw = Rxw*Ryw, Rot = Rxwyw*Rzw;
 	Vector Trans = Vector (Tx, Ty, Tz, Tw);
		
	for (unsigned i = 0; i < NumVertices; i++) 	
		Xtrans[i] = (Rot*X[i])+Trans;
}


void Object::Project (double ScrW, double CamW, bool DepthCue4D) {
	double ProjectionFactor;
	double Wmax = 0, Wmin = 0;

	for (unsigned i = 0; i < NumVertices; i++) {
		if (Xtrans[i][3] < Wmin) Wmin = Xtrans[i][3];
		if (Xtrans[i][3] > Wmax) Wmax = Xtrans[i][3];

		ProjectionFactor = (ScrW-CamW)/(Xtrans[i][3]-CamW);

		for (unsigned j = 0; j <= 2; j++)
			Xscr[i][j] = ProjectionFactor*Xtrans[i][j];

		R[i] = (X[i][0]+1)/2;
		G[i] = (X[i][1]+1)/2;
		B[i] = (X[i][2]+1)/2;
	}
 	
	if (!DepthCue4D) return;

	for (i = 0; i < NumVertices; i++) {
 		float DepthCueFactor = (Wmax-Xtrans[i][3])/(Wmax-Wmin)*0.9+0.1; //	??? !!!
 		R[i] = 0.1+(R[i]-0.1)*DepthCueFactor;
 		G[i] = 0.1+(G[i]-0.1)*DepthCueFactor;
 		B[i] = 0.1+(B[i]-0.1)*DepthCueFactor;
 	}
}


void Object::Draw () {
	glBegin (GL_QUADS);	
		for (unsigned i = 0; i < NumSurfaces; i++) 
			for (unsigned j = 0; j < 4; j++) {
				SetColor (R[Surface[j][i]], G[Surface[j][i]], B[Surface[j][i]]);
				glVertex3dv (Xscr[Surface[j][i]].data ());
			}
	glEnd ();
}


///////////////////////////////////////////////////////////////////////////////

Hypercube::Hypercube (const Vector &Center, double _a):
		Object (16, 24),
		a (_a) {
	for (int x = 0; x <= 1; x++)
		for (int y = 0; y <= 1; y++)
			for (int z = 0; z <= 1; z++)
				for (int w = 0; w <= 1; w++)
					X[x+2*(y+2*(z+2*w))] = Vector (2*x-1, 2*y-1, 2*z-1, 2*w-1)*a+Center;

	DeclareSquare (0,  0, 1, 3, 2);
    DeclareSquare (1,  0, 1, 5, 4);    
    DeclareSquare (2,  0, 1, 9, 8);    
    DeclareSquare (3,  0, 2, 6, 4);    
    DeclareSquare (4,  0, 2,10, 8);    
    DeclareSquare (5,  0, 4,12, 8);    
    DeclareSquare (6,  1, 3, 7, 5);    
    DeclareSquare (7,  1, 3,11, 9);    
    DeclareSquare (8,  1, 5,13, 9);    
    DeclareSquare (9,  2, 3, 7, 6);    
    DeclareSquare (10, 2, 3,11,10);    
    DeclareSquare (11, 2, 6,14,10);    
    DeclareSquare (12, 3, 7,15,11);    
    DeclareSquare (13, 4, 5, 7, 6);    
    DeclareSquare (14, 4, 5,13,12);    
    DeclareSquare (15, 4, 6,14,12);    
    DeclareSquare (16, 5, 7,15,13);    
    DeclareSquare (17, 6, 7,15,14);    
    DeclareSquare (18, 8, 9,11,10);    
    DeclareSquare (19, 8, 9,13,12);    
    DeclareSquare (20, 8,10,14,12);    
    DeclareSquare (21, 9,11,15,13);    
    DeclareSquare (22,10,11,15,14);    
    DeclareSquare (23,12,13,15,14);    
}		

Hypercube::~Hypercube () { }


void Hypercube::DeclareSquare (unsigned i, unsigned a, unsigned b, unsigned c, unsigned d) {
    Surface[0][i] = a;
    Surface[1][i] = b;
    Surface[2][i] = c;
    Surface[3][i] = d; 
}


///////////////////////////////////////////////////////////////////////////////

Sponge::Sponge (unsigned level, int distance, double rad, Vector Center) {
	if (level < 1)
		List.push_back (new Hypercube (Center, rad));
	else {
		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++)
				for (int z = -1; z <= 1; z++)
					for (int w = -1; w <= 1; w++) {
						if (distance >= 0) {
							if (abs (x)+abs (y)+abs (z)+abs (w) > distance) {
								Vector NewCen = Vector (x, y, z, w)*rad;
								NewCen += Center;
								List.push_back (new Sponge (level-1, distance, rad/2, NewCen));
							}
						}
						else {
							if (abs (x)+abs (y)+abs (z)+abs (w) < distance) {
								Vector NewCen = Vector (x, y, z, w)*rad;
								NewCen += Center;
								List.push_back (new Sponge (level-1, rad/2, NewCen));
							}
						}
					}
	}
}

Sponge::~Sponge () { }

void Sponge::Transform (double Thetaxy, double Thetaxz, double Thetaxw, double Thetayz, double Thetayw, double Thetazw,
						double Tx, double Ty, double Tz, double Tw) {
	for (unsigned i = 0; i < List.size (); i++)
		List[i]->Transform (Thetaxy, Thetaxz, Thetaxw, Thetayz, Thetayw, Thetazw,
							Tx, Ty, Tz, Tw);
}

void Sponge::Project (double ScrW, double CamW, bool DepthCue4D) {
	for (unsigned i = 0; i < List.size (); i++)
		List[i]->Project (ScrW, CamW, DepthCue4D);
}

void Sponge::Draw (void) {
	for (unsigned i = 0; i < List.size (); i++)
		List[i]->Draw ();
}


///////////////////////////////////////////////////////////////////////////////

Simplex::Simplex (const Vector &Center, double _a):
		Object (5, 10),
		a (_a) {
	X[0] = Vector (0.0, 0.0, 0.0, 0.0);
	X[1] = Vector (1.0, 0.0, 0.0, 0.0);
	X[2] = Vector (0.5, sqrt (3.)/2., 0.0, 0.0);
	X[3] = Vector (0.5, sqrt (3.)/6., sqrt (2./3.), 0.0);
	X[4] = Vector (0.5, sqrt (3.)/6., 1./sqrt (6.), 1./sqrt (2.));

	for (unsigned i = 0; i < NumVertices; i++)
		X[i] = X[i]*a+Center;

	DeclareTriangle (0,  0, 1, 2);
    DeclareTriangle (1,  0, 1, 3);    
    DeclareTriangle (2,  0, 1, 4);    
    DeclareTriangle (3,  0, 2, 3);    
    DeclareTriangle (4,  0, 2, 4);    
    DeclareTriangle (5,  0, 3, 4);    
    DeclareTriangle (6,  1, 2, 3);    
    DeclareTriangle (7,  1, 2, 4);    
    DeclareTriangle (8,  1, 3, 4);    
    DeclareTriangle (9,  2, 3, 4);    
}		

Simplex::~Simplex () { }


void Simplex::DeclareTriangle (unsigned i, unsigned a, unsigned b, unsigned c) {
    Surface[0][i] = a;
    Surface[1][i] = b;
    Surface[2][i] = c;
    Surface[3][i] = c; 
}


///////////////////////////////////////////////////////////////////////////////

Pyramid::Pyramid (unsigned level, double rad, Vector Center) {
	if (level < 1)
		List.push_back (new Simplex (Center, rad));
	else {
		Vector NewCen = Vector (0.0, 0.0, 0.0, 0.0);
		NewCen += Center;
		List.push_back (new Pyramid (level-1, rad/2, NewCen));

		NewCen = Vector (1.0, 0.0, 0.0, 0.0)*rad;
		NewCen += Center;
		List.push_back (new Pyramid (level-1, rad/2, NewCen));

		NewCen = Vector (0.5, sqrt (3.)/2., 0.0, 0.0)*rad;
		NewCen += Center;
		List.push_back (new Pyramid (level-1, rad/2, NewCen));

		NewCen = Vector (0.5, sqrt (3.)/6., sqrt (2./3.), 0.0)*rad;
		NewCen += Center;
		List.push_back (new Pyramid (level-1, rad/2, NewCen));

		NewCen = Vector (0.5, sqrt (3.)/6., 1./sqrt (6.), 1./sqrt (2.))*rad;
		NewCen += Center;
		List.push_back (new Pyramid (level-1, rad/2, NewCen));
	}
}

Pyramid::~Pyramid () { }

void Pyramid::Transform (double Thetaxy, double Thetaxz, double Thetaxw, double Thetayz, double Thetayw, double Thetazw,
						double Tx, double Ty, double Tz, double Tw) {
	for (unsigned i = 0; i < List.size (); i++)
		List[i]->Transform (Thetaxy, Thetaxz, Thetaxw, Thetayz, Thetayw, Thetazw,
							Tx, Ty, Tz, Tw);
}

void Pyramid::Project (double ScrW, double CamW, bool DepthCue4D) {
	for (unsigned i = 0; i < List.size (); i++)
		List[i]->Project (ScrW, CamW, DepthCue4D);
}

void Pyramid::Draw (void) {
	for (unsigned i = 0; i < List.size (); i++)
		List[i]->Draw ();
}
