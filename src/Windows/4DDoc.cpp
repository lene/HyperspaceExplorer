// 4DDoc.cpp : Implementierung der Klasse C4DDoc
//

#include "stdafx.h"

#include "4D.h"
#include "4DDoc.h"
#include "Matrix.h"

#include <string>
#include <fstream>
#include <process.h>

#include "Function.h"
#include "Surface.h"
#include "ComplexFunction.h"
#include "Object.h"


/////////////////////////////////////////////////////////////////////////////
// C4DDoc

IMPLEMENT_DYNCREATE(C4DDoc, CDocument)

BEGIN_MESSAGE_MAP(C4DDoc, CDocument)
	//{{AFX_MSG_MAP(C4DDoc)
	ON_COMMAND(ID_LIGHTING, OnLighting)
	ON_UPDATE_COMMAND_UI(ID_LIGHTING, OnUpdateLighting)
	ON_COMMAND(ID_LINES, OnLines)
	ON_UPDATE_COMMAND_UI(ID_LINES, OnUpdateLines)
	ON_COMMAND(ID_POLYGONS, OnPolygons)
	ON_UPDATE_COMMAND_UI(ID_POLYGONS, OnUpdatePolygons)
	ON_COMMAND(ID_COORDINATE_CROSS, OnCoordinateCross)
	ON_UPDATE_COMMAND_UI(ID_COORDINATE_CROSS, OnUpdateCoordinateCross)
 	ON_COMMAND(ID_DATEI_BENCHMARK, OnBenchmark)
 	ON_COMMAND(ID_DEPTHCUE_4D, OnDepthcue4d)
 	ON_UPDATE_COMMAND_UI(ID_DEPTHCUE_4D, OnUpdateDepthcue4d)
 	ON_COMMAND(ID_DEPTHCUE_3D, OnDepthcue3d)
 	ON_UPDATE_COMMAND_UI(ID_DEPTHCUE_3D, OnUpdateDepthcue3d)	
	ON_COMMAND(ID_VIEW_ANIMATE_BENCHMARK, OnAnimateBenchmark)
	ON_COMMAND(ID_FUNCTION_HYPERCUBE, OnFunctionHypercube)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_HYPERCUBE, OnUpdateFunctionHypercube)
	ON_COMMAND(ID_FUNCTION_HYPERSPHERE, OnFunctionHypersphere)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_HYPERSPHERE, OnUpdateFunctionHypersphere)
	ON_COMMAND(ID_FUNCTION_TORUS1, OnFunctionTorus1)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_TORUS1, OnUpdateFunctionTorus1)
	ON_COMMAND(ID_FUNCTION_TORUS2, OnFunctionTorus2)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_TORUS2, OnUpdateFunctionTorus2)	
 	ON_COMMAND(ID_FUNCTION_EXP_MINUS_R2, OnFunctionExpMinusR2)
 	ON_UPDATE_COMMAND_UI(ID_FUNCTION_EXP_MINUS_R2, OnUpdateFunctionExpMinusR2)
 	ON_COMMAND(ID_FUNCTION_ONE_OVER_R2, OnFunctionOneOverR2)
 	ON_UPDATE_COMMAND_UI(ID_FUNCTION_ONE_OVER_R2, OnUpdateFunctionOneOverR2)
 	ON_COMMAND(ID_FUNCTION_FR3R_GRAVITATIONPOTENTIAL, OnFunctionGravPotential)
 	ON_UPDATE_COMMAND_UI(ID_FUNCTION_FR3R_GRAVITATIONPOTENTIAL, OnUpdateFunctionGravPotential)
 	ON_COMMAND(ID_FUNCTION_SIN_R2, OnFunctionSinR2)
 	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SIN_R2, OnUpdateFunctionSinR2)
 	ON_COMMAND(ID_FUNCTION_POLAR_RPHITHETAPSI, OnFunctionPolarRphithetapsi)
 	ON_UPDATE_COMMAND_UI(ID_FUNCTION_POLAR_RPHITHETAPSI, OnUpdateFunctionPolarRphithetapsi)
 	ON_COMMAND(ID_FUNCTION_POLAR_RSINPHITHETAPSI, OnFunctionPolarRsinphithetapsi)
 	ON_UPDATE_COMMAND_UI(ID_FUNCTION_POLAR_RSINPHITHETAPSI, OnUpdateFunctionPolarRsinphithetapsi)
 	ON_COMMAND(ID_FUNCTION_POLAR_RSQRTPHI2THETA2PSI2, OnFunctionPolarRR)
 	ON_UPDATE_COMMAND_UI(ID_FUNCTION_POLAR_RSQRTPHI2THETA2PSI2, OnUpdateFunctionPolarRR)
	ON_COMMAND(ID_FUNCTION_SPONGE, OnFunctionSponge)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SPONGE, OnUpdateFunctionSponge)
	ON_COMMAND(ID_FUNCTION_OBJECTS_SIMPLEX, OnFunctionSimplex)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_OBJECTS_SIMPLEX, OnUpdateFunctionSimplex)
	ON_COMMAND(ID_FUNCTION_OBJECTS_PYRAMID, OnFunctionPyramid)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_OBJECTS_PYRAMID, OnUpdateFunctionPyramid)
	ON_COMMAND(ID_FUNCTION_SURFACES_1, OnFunctionSurfaces1)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_1, OnUpdateFunctionSurfaces1)
	ON_COMMAND(ID_FUNCTION_SURFACES_2, OnFunctionSurfaces2)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_2, OnUpdateFunctionSurfaces2)
	ON_COMMAND(ID_FUNCTION_SURFACES_Z, OnFunctionSurfacesZ3)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_Z, OnUpdateFunctionSurfacesZ3)
	ON_COMMAND(ID_FUNCTION_SURFACES_EZ, OnFunctionSurfacesez)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_EZ, OnUpdateFunctionSurfacesez)
	ON_COMMAND(ID_FUNCTION_SURFACES_HORIZON, OnFunctionSurfacesHorizon)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_HORIZON, OnUpdateFunctionSurfacesHorizon)
	ON_COMMAND(ID_FUNCTION_SURFACES_TORUS3, OnFunctionSurfacesTorus3)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_TORUS3, OnUpdateFunctionSurfacesTorus3)
	ON_COMMAND(ID_FUNCTION_SURFACES_E2, OnFunctionSurfacesEmz2)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_E2, OnUpdateFunctionSurfacesEmz2)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_ZA, OnFunctionZa)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_ZA, OnUpdateFunctionZa)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_COSHZ, OnFunctionCoshz)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_1Z, OnFunction1Overz)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_TANZ, OnFunctionSurfacesFccTanz)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_TANZ, OnUpdateFunctionSurfacesFccTanz)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_SINZ, OnFunctionSurfacesFccSinz)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_SINZ, OnUpdateFunctionSurfacesFccSinz)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_SINHZ, OnFunctionSurfacesFccSinhz)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_SINHZ, OnUpdateFunctionSurfacesFccSinhz)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_LNZ, OnFunctionSurfacesFccLnz)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_LNZ, OnUpdateFunctionSurfacesFccLnz)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_COSZ, OnFunctionSurfacesFccCosz)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_COSZ, OnUpdateFunctionSurfacesFccCosz)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_COSHZ, OnUpdateFunctionSurfacesFccCoshz)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_1Z, OnUpdateFunctionSurfacesFcc1z)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_1Z2, OnFunctionSurfacesFcc1z2)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_1Z2, OnUpdateFunctionSurfacesFcc1z2)
	ON_COMMAND(ID_FUNCTION_SURFACES_FCC_SQRTZ, OnFunctionSurfacesFccSqrtz)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_SURFACES_FCC_SQRTZ, OnUpdateFunctionSurfacesFccSqrtz)
 	ON_COMMAND(ID_DEPTHCUE_4D, OnDepthcue4d)
 	ON_UPDATE_COMMAND_UI(ID_DEPTHCUE_4D, OnUpdateDepthcue4d)
 	ON_COMMAND(ID_DEPTHCUE_3D, OnDepthcue3d)
 	ON_UPDATE_COMMAND_UI(ID_DEPTHCUE_3D, OnUpdateDepthcue3d)
	ON_COMMAND(ID_FUNCTION_POLYNOMIAL, OnFunctionPolynomial)
	ON_UPDATE_COMMAND_UI(ID_FUNCTION_POLYNOMIAL, OnUpdateFunctionPolynomial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C4DDoc Konstruktion/Destruktion

C4DDoc::C4DDoc(): 
		Props (this), F (NULL), 
		CamW (-2.), ScrW (0.),
		DepthCue3D (false), DepthCue4D (false), 
 		DisplayCoordinates (false),
 		NumVertices (0) {
	Cross = new Vector * [4]; CrossTrans = new Vector * [4]; CrossScr = new Vector * [4];
	for (unsigned j = 0; j < 4; j++) {
		Cross[j] = new Vector [2]; CrossTrans[j] = new Vector [2]; CrossScr[j] = new Vector [2];
	}
	Cross[0][0] = Vector (-5., 0., 0., 0.);	Cross[0][1] = Vector (5., 0., 0., 0.);
	Cross[1][0] = Vector (0., -5., 0., 0.);	Cross[1][1] = Vector (0., 5., 0., 0.);
	Cross[2][0] = Vector (0., 0., -5., 0.);	Cross[2][1] = Vector (0., 0., 5., 0.);
	Cross[3][0] = Vector (0., 0., 0., -5.);	Cross[3][1] = Vector (0., 0., 0., 5.);
}

C4DDoc::~C4DDoc() {
}


#ifdef _DEBUG
void C4DDoc::AssertValid() const { CDocument::AssertValid(); }
void C4DDoc::Dump(CDumpContext& dc) const {	CDocument::Dump(dc); }
#endif //_DEBUG

void C4DDoc::AssignValues (const char *Title) {
	tsteps = unsigned ((Props.tmax ()-Props.tmin ())/Props.dt ());
	usteps = unsigned ((Props.umax ()-Props.umin ())/Props.du ());
	vsteps = unsigned ((Props.vmax ()-Props.vmin ())/Props.dv ());

	if (Title) SetTitle (Title);
}

BOOL C4DDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (F == NULL)
		OnFunctionGravPotential ();
	else {
		F->SetParameters (Props.a (), Props.b (), Props.c (), Props.d ());
		F->ReInit (Props.tmin (), Props.tmax (), Props.dt (),
				   Props.umin (), Props.umax (), Props.du (),
				   Props.vmin (), Props.vmax (), Props.dv ());
		AssignValues (NULL);
		Transform ();
		Redraw ();
	}

	return TRUE;
}

void C4DDoc::Transform (double Thetaxy, double Thetaxz, double Thetaxw, double Thetayz, double Thetayw, double Thetazw,
						double Tx, double Ty, double Tz, double Tw) {

	F->Transform (Thetaxy, Thetaxz, Thetaxw, Thetayz, Thetayw, Thetazw, 
				  Tx, Ty, Tz, Tw);

	Matrix<4> Rxy = Matrix<4> (0, 1, Thetaxy), Rxz = Matrix<4> (0, 2, Thetaxz), Rxw = Matrix<4> (0, 3, Thetaxw),
			  Ryz = Matrix<4> (1, 2, Thetayz), Ryw = Matrix<4> (1, 3, Thetayw), Rzw = Matrix<4> (2, 3, Thetazw),
			  Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw,
			  Rot = Rxyz*Rxwyz*Ryzw;
 	Vector Trans = Vector (Tx, Ty, Tz, Tw);

	for (unsigned i = 0; i < 2; i++)
		for (unsigned j = 0; j < 4; j++) 
			CrossTrans[j][i] = (Rot*Cross[j][i])+Trans;
}

void C4DDoc::Project (void) {
	F->Project (ScrW, CamW, DepthCue4D);

	if (DisplayCoordinates) {
		for (unsigned i = 0; i < 2; i++)
			for (unsigned j = 0; j < 4; j++) {
				double ProjectionFactor = (ScrW-CamW)/(CrossTrans[j][i][3]-CamW);
				CrossScr[j][i]= CrossTrans[j][i]*ProjectionFactor;
			}
	}

}

void C4DDoc::Redraw () {
	if (ObjectList) glDeleteLists (ObjectList,1);
	while (!glIsList (ObjectList)) {
		ObjectList = GetGLList ();
		glNewList (ObjectList, GL_COMPILE);
		if (!glIsList (ObjectList)) {
			glEndList ();
		}
	}
	glNewList (ObjectList, GL_COMPILE);
	Project ();
	Draw ();
	glEndList ();
	
	if (DisplayCoordinates) {
		if (CoordinateCross) glDeleteLists (CoordinateCross,1);
		CoordinateCross = GetGLList ();
		glNewList (CoordinateCross, GL_COMPILE);
		DrawCoordinates ();
		glEndList ();
	}

 	C4DView *view = GetView ();
	view->Redisplay ();
}

void C4DDoc::DrawCoordinates () {
	for (unsigned j = 0; j < 3; j++) {
		switch (j) {
		case 0:
			SetColor (1., 0., 0.);
			break;
		case 1:
			SetColor (0., 1., 0.);
			break;
		case 2:
			SetColor (0., 0., 1.);
		}

		glBegin (GL_LINES);
		for (unsigned i = 0; i < 2; i++)
			glVertex3dv (CrossScr[j][i].data ());
		glEnd ();
	}
	glBegin (GL_LINES);
 	SetColor (1., 0., 1.);
 	glVertex3dv (CrossScr[3][0].data ());
 	SetColor (.1f, .05f, .1f);
 	glVertex3dv (CrossScr[3][1].data ());
 	glEnd ();
}

bool *ThreadDone = NULL;

void DrawThread (void *param) {
/*
	C4DDoc *Document = (C4DDoc *)param;
	unsigned CurrentProcessor = Document->CurrentProcessor;
	ThreadDone[CurrentProcessor] = false;

 	unsigned tstart = (CurrentProcessor*Document->tsteps)/NumProcessors (),
 			 tend   =((CurrentProcessor+1)*Document->tsteps)/NumProcessors () <= Document->tsteps?
 					 ((CurrentProcessor+1)*Document->tsteps)/NumProcessors (): Document->tsteps;
 	for (unsigned t = tstart; t < tend; t++)
 		Document->DrawPlane (&t);

	ThreadDone[CurrentProcessor] = true;
*/
}

void C4DDoc::Draw () {
//	if (ThreadDone == NULL) ThreadDone = new bool [NumProcessors ()];

	if (DisplayCoordinates) DrawCoordinates ();

	F->Draw ();
/*	
 	for (CurrentProcessor = 0; CurrentProcessor < NumProcessors (); CurrentProcessor++) {
 		_beginthread (DrawThread, NULL, this);
 		Sleep (10);
	}

	bool Done = false;
	while (Done == false) {
		Sleep (10);
		for (CurrentProcessor = 0; CurrentProcessor < NumProcessors (); CurrentProcessor++) 
			Done &= ThreadDone[CurrentProcessor];
	}
*/
}

void C4DDoc::RenderScene (unsigned Frame) {					//	draw (a frame of the animation)
	if (glIsList (ObjectList)) {
		glCallList (ObjectList);								//	draw the object
		glCallList (CoordinateCross);
	}
	else MessageBox (NULL, itoa (ObjectList).c_str (), "CGLDoc::RenderScene" , MB_ICONINFORMATION);
}

double C4DDoc::Size () {
	return sqrt ((Props.tmax ()-Props.tmin ())*(Props.tmax ()-Props.tmin ())
				+(Props.umax ()-Props.umin ())*(Props.umax ()-Props.umin ())
			    +(Props.vmax ()-Props.vmin ())*(Props.vmax ()-Props.vmin ())); }

C4DView *C4DDoc::GetView () {
	POSITION pos = GetFirstViewPosition();
	C4DView *view = (C4DView *)GetNextView (pos);
	return view; 
}

void C4DDoc::OnBenchmark() {
 	clock_t stime = clock ();					//  record start time
 
 	for (double Rxw = 0; Rxw < 360; Rxw++) {
 		Transform (0,0,Rxw,0,0,0,0,0,0,0);
 		Redraw ();
 	}
 	
 	float xtime = float (clock ()-stime)/CLOCKS_PER_SEC; 
 
 	ostrstream Time;
 	Time << "4D viewpoint rotation:" << setw (8) << setprecision (3) << xtime << "sec." << endl;
 
 	C4DView *view = GetView ();	
 	stime = clock ();
 	for (double Rz = 0; Rz < 360; Rz++) { 
 		view->SetRotation (0, 0, Rz);
 		view->Redisplay ();
 	}
 	
 	xtime = float (clock ()-stime)/CLOCKS_PER_SEC; 
 	
 	Time << "3D viewpoint rotation:" << setw (8) << setprecision (3) << xtime << "sec." << ends;
 
 	MessageBox (NULL, Time.str (), "Benchmark results", MB_ICONINFORMATION);
}
 

void C4DDoc::OnLighting() {
	C4DView *view = GetView ();	
	view->SetLighting (!view->GetLighting ());
	view->Redisplay (); 	
}

void C4DDoc::OnUpdateLighting(CCmdUI* pCmdUI) {
	C4DView *view = GetView ();	
	pCmdUI->SetCheck (view->GetLighting ());
}

void C4DDoc::OnLines() {
	C4DView *view = GetView ();	
	view->SetWireframe (true);
	view->Redisplay ();
}

void C4DDoc::OnUpdateLines(CCmdUI* pCmdUI) {
	C4DView *view = GetView ();	
	pCmdUI->SetCheck (view->GetWireframe ());
}

void C4DDoc::OnPolygons() {
	C4DView *view = GetView ();	
	view->SetWireframe (false);
	view->Redisplay ();
}

void C4DDoc::OnUpdatePolygons(CCmdUI* pCmdUI) {
	C4DView *view = GetView ();	
	pCmdUI->SetCheck (!view->GetWireframe ());
}

void C4DDoc::OnCoordinateCross() {
	DisplayCoordinates = !DisplayCoordinates;
	Redraw ();
}

void C4DDoc::OnUpdateCoordinateCross(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (DisplayCoordinates);
}

void C4DDoc::OnDepthcue4d() {
 	DepthCue4D = !DepthCue4D;
	Redraw ();
}

void C4DDoc::OnUpdateDepthcue4d(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (DepthCue4D);
}
 
void C4DDoc::OnDepthcue3d() {
 	DepthCue3D = !DepthCue3D;
 	C4DView *view = GetView ();	
 	view->SetDepthCue (DepthCue3D);
 	view->Redisplay ();
}

void C4DDoc::OnUpdateDepthcue3d(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (DepthCue3D);
}

void C4DDoc::OnAnimateBenchmark() {	OnBenchmark (); }

void C4DDoc::OnFunctionFr3r() {
	F = new Fr3r (Props.tmin (), Props.tmax (), Props.dt (),
				  Props.umin (), Props.umax (), Props.du (),
				  Props.vmin (), Props.vmax (), Props.dv ());

	AssignValues ("w = 1/(r²+1)");
	Props.SetParameterText ();
	 
	Transform ();
	Redraw ();
}

void C4DDoc::OnUpdateFunctionFr3r(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (dynamic_cast <Fr3r *> (F) != NULL);
}

void C4DDoc::OnFunctionHypercube() {
	F = new Hypercube (Vector (0, 0, 0, 0),
					   Props.a ());

	AssignValues ("Hypercube");
	Props.SetParameterText ("Size");
 
	Transform ();
	Redraw ();
}

void C4DDoc::OnUpdateFunctionHypercube(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (dynamic_cast <Hypercube *> (F) != NULL);	
}

void C4DDoc::OnFunctionHypersphere() {
	F = new Hypersphere (Props.tmin (), Props.tmax (), Props.dt (),
					     Props.umin (), Props.umax (), Props.du (),
					     Props.vmin (), Props.vmax (), Props.dv (),
						 Props.a ());

	AssignValues ("Hypersphere");
 	Props.SetParameterText ("Radius");

	Transform ();
	Redraw ();
}

void C4DDoc::OnUpdateFunctionHypersphere(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (dynamic_cast <Hypersphere *> (F) != NULL);
}

void C4DDoc::OnFunctionTorus1() {
	F = new Torus1 (Props.tmin (), Props.tmax (), Props.dt (),
				    Props.umin (), Props.umax (), Props.du (),
				    Props.vmin (), Props.vmax (), Props.dv (),
					Props.a (), Props.b (), Props.c ());

	AssignValues ("Torus 1");
 	Props.SetParameterText ("Major R", "Minor R", "Third R");

	Transform ();
	Redraw ();
}

void C4DDoc::OnUpdateFunctionTorus1(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (dynamic_cast <Torus1 *> (F) != NULL);
}

void C4DDoc::OnFunctionTorus2() {
	F = new Torus2 (Props.tmin (), Props.tmax (), Props.dt (),
				    Props.umin (), Props.umax (), Props.du (),
				    Props.vmin (), Props.vmax (), Props.dv (),
					Props.a (), Props.b ());

	AssignValues ("Torus 2");
 	Props.SetParameterText ("Major R", "Minor R");

	Transform ();
	Redraw ();
}

void C4DDoc::OnUpdateFunctionTorus2(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (dynamic_cast <Torus2 *> (F) != NULL);
}


void C4DDoc::OnFunctionOneOverR2() {
 	F = new Fr3r (Props.tmin (), Props.tmax (), Props.dt (),
 				  Props.umin (), Props.umax (), Props.du (),
 				  Props.vmin (), Props.vmax (), Props.dv ());
 	AssignValues ("w = 1/(r²+0.5)");
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionOneOverR2(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Fr3r *> (F) != NULL);
}

void C4DDoc::OnFunctionGravPotential() {
 	F = new GravitationPotential (Props.tmin (), Props.tmax (), Props.dt (),
 								  Props.umin (), Props.umax (), Props.du (),
 								  Props.vmin (), Props.vmax (), Props.dv (),
								  Props.a (), Props.b ());
 	AssignValues ("GravitationPotential");
 	Props.SetParameterText ("Mass", "Radius");
	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionGravPotential(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <GravitationPotential *> (F) != NULL);
}

void C4DDoc::OnFunctionExpMinusR2() {
 	F = new Fr3rExp (Props.tmin (), Props.tmax (), Props.dt (),
 					 Props.umin (), Props.umax (), Props.du (),
 					 Props.vmin (), Props.vmax (), Props.dv ());

 	AssignValues ("w = exp (-r²)");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionExpMinusR2(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Fr3rExp *> (F) != NULL);
}
 
void C4DDoc::OnFunctionSinR2() {
 	F = new Fr3rSin (Props.tmin (), Props.tmax (), Props.dt (),
 					 Props.umin (), Props.umax (), Props.du (),
 					 Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("w = sin (r²)");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}
 
void C4DDoc::OnUpdateFunctionSinR2(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Fr3rSin *> (F) != NULL);
}
 
void C4DDoc::OnFunctionPolarRphithetapsi() {
 	F = new Polar (Props.tmin (), Props.tmax (), Props.dt (),
 				   Props.umin (), Props.umax (), Props.du (),
 				   Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("R = phi+theta+psi");
 	Props.SetParameterText ();
	 
 	Transform ();
 	Redraw ();
}
 
void C4DDoc::OnUpdateFunctionPolarRphithetapsi(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Polar *> (F) != NULL);
}

void C4DDoc::OnFunctionPolarRsinphithetapsi() {
 	F = new PolarSin (Props.tmin (), Props.tmax (), Props.dt (),
 					  Props.umin (), Props.umax (), Props.du (),
 					  Props.vmin (), Props.vmax (), Props.dv (),
					  Props.a ());
 
 	AssignValues ("R = sin (phi*theta*psi)");
	Props.SetParameterText ("Phase");
 	 
 	Transform ();
 	Redraw ();
}
 
void C4DDoc::OnUpdateFunctionPolarRsinphithetapsi(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <PolarSin *> (F) != NULL);
}

void C4DDoc::OnFunctionPolarRR() {
 	F = new PolarR (Props.tmin (), Props.tmax (), Props.dt (),
 					Props.umin (), Props.umax (), Props.du (),
 					Props.vmin (), Props.vmax (), Props.dv (), 
					Props.a ());
 
 	AssignValues ("R = sqrt (phi²+theta²+psi²)");
	Props.SetParameterText ("Phase");
 	 
 	Transform ();
 	Redraw ();
}
 
void C4DDoc::OnUpdateFunctionPolarRR (CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <PolarR *> (F) != NULL);
}

void C4DDoc::OnFunctionSponge() {
 	F = new Sponge (unsigned (Props.a ()), 2, .707, Vector (0, 0, 0, 0));
 
 	AssignValues ("Hypersponge");
	Props.SetParameterText ("Level");
 	 
 	Transform ();
 	Redraw ();	
}

void C4DDoc::OnUpdateFunctionSponge(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Sponge *> (F) != NULL);
}

void C4DDoc::OnFunctionSimplex() {
 	F = new Simplex (Vector (-0.5, -sqrt (3.)/6., -1./sqrt (6.), 0.), 1.);
 
 	AssignValues ("Hypersimplex");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();	
}

void C4DDoc::OnUpdateFunctionSimplex(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Simplex *> (F) != NULL);
}

void C4DDoc::OnFunctionPyramid() {
 	F = new Sponge (unsigned (Props.a ()), 1., Vector (0, 0, 0, 0));
 
 	AssignValues ("Pyramid");
	Props.SetParameterText ("Level");
 	 
 	Transform ();
 	Redraw ();	
}

void C4DDoc::OnUpdateFunctionPyramid(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Pyramid *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfaces1() {
 	F = new Surface1 (Props.umin (), Props.umax (), Props.du (),
 					  Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("some surface");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfaces1(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Surface1 *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesHorizon() {
 	F = new Horizon (Props.umin (), Props.umax (), Props.du (),
 					 Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("Horizon");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesHorizon(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Horizon *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesTorus3() {
 	F = new Torus3 (Props.umin (), Props.umax (), Props.du (),
 					Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("Torus (3)");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesTorus3(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <Torus3 *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfaces2() {
 	F = new z2 (Props.umin (), Props.umax (), Props.du (),
 				Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("z²");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfaces2(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <z2 *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesZ3() {
 	F = new z3 (Props.umin (), Props.umax (), Props.du (),
 				Props.vmin (), Props.vmax (), Props.dv ());
 
	AssignValues ("z³");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesZ3(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <z3 *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesez() {
 	F = new ez (Props.umin (), Props.umax (), Props.du (),
 				Props.vmin (), Props.vmax (), Props.dv (),
				Props.a ());
 
 	AssignValues ("e^z");
	Props.SetParameterText ("alpha");
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesez(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <ez *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesEmz2() {
 	F = new emz2 (Props.umin (), Props.umax (), Props.du (),
 						 Props.vmin (), Props.vmax (), Props.dv (),
						 Props.a ());
 
 	AssignValues ("e^-z²");
	Props.SetParameterText ("alpha");
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesEmz2(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <emz2 *> (F) != NULL);	
}

void C4DDoc::OnFunctionZa() {
 	F = new zA (Props.umin (), Props.umax (), Props.du (),
 				Props.vmin (), Props.vmax (), Props.dv (),
				Props.a ());
 
 	AssignValues ("z^a");
	Props.SetParameterText ("a");
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionZa(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <zA *> (F) != NULL);	
}


void C4DDoc::OnFunction1Overz() {
 	F = new zm1 (Props.umin (), Props.umax (), Props.du (),
 				 Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("1/z");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesFcc1z(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <zm1 *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesFcc1z2() {
 	F = new zm2 (Props.umin (), Props.umax (), Props.du (),
 			 	 Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("1/z²");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesFcc1z2(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <zm2 *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesFccSinz() {
 	F = new sinz (Props.umin (), Props.umax (), Props.du (),
 				  Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("sin z");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesFccSinz(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <sinz *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesFccCosz() {
 	F = new cosz (Props.umin (), Props.umax (), Props.du (),
 				  Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("cos z");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesFccCosz(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <cosz *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesFccTanz() {
 	F = new tanz (Props.umin (), Props.umax (), Props.du (),
 				  Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("tan z");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesFccTanz(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <tanz *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesFccSinhz() {
 	F = new sinhz (Props.umin (), Props.umax (), Props.du (),
 				   Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("sinh z");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesFccSinhz(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <sinhz *> (F) != NULL);	
}

void C4DDoc::OnFunctionCoshz() {
 	F = new coshz (Props.umin (), Props.umax (), Props.du (),
 				   Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("cosh z");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesFccCoshz(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <coshz *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesFccLnz() {
 	F = new lnz (Props.umin (), Props.umax (), Props.du (),
 			 	 Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("ln z");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesFccLnz(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <lnz *> (F) != NULL);	
}

void C4DDoc::OnFunctionSurfacesFccSqrtz() {
 	F = new sqrtz (Props.umin (), Props.umax (), Props.du (),
 			 	   Props.vmin (), Props.vmax (), Props.dv ());
 
 	AssignValues ("sqrt z");
	Props.SetParameterText ();
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionSurfacesFccSqrtz(CCmdUI* pCmdUI) {
 	pCmdUI->SetCheck (dynamic_cast <sqrtz *> (F) != NULL);	
}

void C4DDoc::OnFunctionPolynomial() {
 	F = new Polynomial (Props.umin (), Props.umax (), Props.du (),
 			 			Props.vmin (), Props.vmax (), Props.dv (),
						Props.a (), Props.b (), Props.c (), Props.d ());
 
 	AssignValues ("a4*z^4 + a3*z³ + a2*z² + a1*z");
	Props.SetParameterText ("a1", "a2", "a3", "a4");
 	 
 	Transform ();
 	Redraw ();
}

void C4DDoc::OnUpdateFunctionPolynomial(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (dynamic_cast <Polynomial *> (F) != NULL);	
}
