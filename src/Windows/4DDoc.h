// 4DDoc.h : Schnittstelle der Klasse C4DDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_4DDOC_H__C44168F5_DFD1_11D3_B3A4_004005A4A929__INCLUDED_)
#define AFX_4DDOC_H__C44168F5_DFD1_11D3_B3A4_004005A4A929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpongeDlg.h"

class Function;

class C4DDoc : public CDocument {
// Implementierung
public:
	double Size ();

	void RenderScene (unsigned Frame);
	
	virtual ~C4DDoc();

	void Transform (double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw,
					double Tx, double Ty, double Tz, double Tw);
	void Transform (void) {	Transform (0, 0, 0, 0, 0, 0,  0, 0, 0, 0); }


	void Redraw ();
 	unsigned CurrentProcessor;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(C4DDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

protected: // Nur aus Serialisierung erzeugen
	C4DDoc();
	DECLARE_DYNCREATE(C4DDoc)

	void Project ();
	void Draw ();

	GLint ObjectList, CoordinateCross;

	void DrawCoordinates (void);

	void AssignValues (const char *Title);

	Function *F;
	SpongeDlg Props;
//	Vector ***Data;

	unsigned tsteps, usteps, vsteps;
	double CamW, ScrW;
	
	Vector **Cross, **CrossTrans, **CrossScr;
	bool DisplayCoordinates;

	bool DepthCue3D, DepthCue4D;

	C4DView *GetView (void);

	unsigned NumVertices;
 
// Generierte Message-Map-Funktionen
	//{{AFX_MSG(C4DDoc)
	afx_msg void OnLighting();
	afx_msg void OnUpdateLighting(CCmdUI* pCmdUI);
	afx_msg void OnLines();
	afx_msg void OnUpdateLines(CCmdUI* pCmdUI);
	afx_msg void OnPolygons();
	afx_msg void OnUpdatePolygons(CCmdUI* pCmdUI);
	afx_msg void OnCoordinateCross();
	afx_msg void OnUpdateCoordinateCross(CCmdUI* pCmdUI);
	afx_msg void OnBenchmark();
 	afx_msg void OnDepthcue4d();
 	afx_msg void OnUpdateDepthcue4d(CCmdUI* pCmdUI);
 	afx_msg void OnDepthcue3d();
 	afx_msg void OnUpdateDepthcue3d(CCmdUI* pCmdUI);
	afx_msg void OnAnimateBenchmark();
	afx_msg void OnFunctionFr3r();
	afx_msg void OnUpdateFunctionFr3r(CCmdUI* pCmdUI);
	afx_msg void OnFunctionHypercube();
	afx_msg void OnUpdateFunctionHypercube(CCmdUI* pCmdUI);
	afx_msg void OnFunctionHypersphere();
	afx_msg void OnUpdateFunctionHypersphere(CCmdUI* pCmdUI);
	afx_msg void OnFunctionTorus1();
	afx_msg void OnUpdateFunctionTorus1(CCmdUI* pCmdUI);
	afx_msg void OnFunctionTorus2();
	afx_msg void OnUpdateFunctionTorus2(CCmdUI* pCmdUI);
 	afx_msg void OnFunctionExpMinusR2();
 	afx_msg void OnUpdateFunctionExpMinusR2(CCmdUI* pCmdUI);
 	afx_msg void OnFunctionOneOverR2();
 	afx_msg void OnUpdateFunctionOneOverR2(CCmdUI* pCmdUI);
 	afx_msg void OnFunctionGravPotential();
 	afx_msg void OnUpdateFunctionGravPotential(CCmdUI* pCmdUI);
 	afx_msg void OnFunctionSinR2();
 	afx_msg void OnUpdateFunctionSinR2(CCmdUI* pCmdUI);
 	afx_msg void OnFunctionPolarRphithetapsi();
 	afx_msg void OnUpdateFunctionPolarRphithetapsi(CCmdUI* pCmdUI);
 	afx_msg void OnFunctionPolarRsinphithetapsi();
 	afx_msg void OnUpdateFunctionPolarRsinphithetapsi(CCmdUI* pCmdUI);
 	afx_msg void OnFunctionPolarRR();
 	afx_msg void OnUpdateFunctionPolarRR(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSponge();
	afx_msg void OnUpdateFunctionSponge(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSimplex();
	afx_msg void OnUpdateFunctionSimplex(CCmdUI* pCmdUI);
	afx_msg void OnFunctionPyramid();
	afx_msg void OnUpdateFunctionPyramid(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfaces1();
	afx_msg void OnUpdateFunctionSurfaces1(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfaces2();
	afx_msg void OnUpdateFunctionSurfaces2(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesZ3();
	afx_msg void OnUpdateFunctionSurfacesZ3(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesez();
	afx_msg void OnUpdateFunctionSurfacesez(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesHorizon();
	afx_msg void OnUpdateFunctionSurfacesHorizon(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesTorus3();
	afx_msg void OnUpdateFunctionSurfacesTorus3(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesEmz2();
	afx_msg void OnUpdateFunctionSurfacesEmz2(CCmdUI* pCmdUI);
	afx_msg void OnFunctionZa();
	afx_msg void OnUpdateFunctionZa(CCmdUI* pCmdUI);
	afx_msg void OnFunctionCoshz();
	afx_msg void OnFunction1Overz();
	afx_msg void OnFunctionSurfacesFccTanz();
	afx_msg void OnUpdateFunctionSurfacesFccTanz(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesFccSinz();
	afx_msg void OnUpdateFunctionSurfacesFccSinz(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesFccSinhz();
	afx_msg void OnUpdateFunctionSurfacesFccSinhz(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesFccLnz();
	afx_msg void OnUpdateFunctionSurfacesFccLnz(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesFccCosz();
	afx_msg void OnUpdateFunctionSurfacesFccCosz(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFunctionSurfacesFccCoshz(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFunctionSurfacesFcc1z(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesFcc1z2();
	afx_msg void OnUpdateFunctionSurfacesFcc1z2(CCmdUI* pCmdUI);
	afx_msg void OnFunctionSurfacesFccSqrtz();
	afx_msg void OnUpdateFunctionSurfacesFccSqrtz(CCmdUI* pCmdUI);
	afx_msg void OnFunctionPolynomial();
	afx_msg void OnUpdateFunctionPolynomial(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_4DDOC_H__C44168F5_DFD1_11D3_B3A4_004005A4A929__INCLUDED_)
