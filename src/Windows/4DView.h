// 4DView.h : Schnittstelle der Klasse C4DView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_4DVIEW_H__C44168CA_DFD1_11D3_B3A4_004005A4A929__INCLUDED_)
#define AFX_4DVIEW_H__C44168CA_DFD1_11D3_B3A4_004005A4A929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Vector;

class C4DView : public CView {
public:
	C4DDoc* GetDocument();
	void NewDocument (void);

	virtual ~C4DView();

	void Transform ();
	Vector Project (Vector);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void SetWireframe (bool wire) { DisplayPolygons = !wire; }
	bool GetWireframe (void) { return !DisplayPolygons; }
	void SetLighting (bool light) { Lighting = light; }
	bool GetLighting (void) { return Lighting; }
 	void SetDepthCue (bool on) { 
 		SetupDepthCue (on);
 		Redisplay ();
	}
 	void SetRotation (double rx, double ry, double rz) {
 		m_rotX = rx; m_rotY = ry; m_rotZ = rz; }


// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(C4DView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

protected: // Nur aus Serialisierung erzeugen
	C4DView();
	DECLARE_DYNCREATE(C4DView)

	double Tx,  Ty,  Tz,  Tw,
		   Rxy, Rxz, Rxw, Ryz, Ryw, Rzw;

	GLdouble m_rotX,   m_rotY,
			 m_transX, m_transY,
			 m_camZ, m_rotZ;

	bool m_RightButtonDown, m_MidButtonDown, m_LeftButtonDown;
	CPoint m_RightDownPos, m_MidDownPos, m_LeftDownPos;

	HGLRC m_hGLContext;
	bool CreateViewGLContext (HDC hDC);
	int m_GLPixelIndex;
	bool SetWindowPixelFormat (HDC hDC);
	void Redisplay (void);

	bool AntiAlias, DisplayPolygons, Lighting, DepthCue3D;

	bool Animated;
	void StartAnimation ();
	void StopAnimation ();
	bool TakingSpinValues;
	double dxy, dxz, dxw, dyz, dyw, dzw,
		   dx, dy, dz;

	HDC hDC;
	HWND m_hStatusBar;
	void UpdateStatus (string = "");
	void SetupDepthCue (bool);

// Generierte Message-Map-Funktionen
	//{{AFX_MSG(C4DView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
 	afx_msg void OnAnimateRandom();
	afx_msg void OnLighting();
	afx_msg void OnUpdateLighting(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_4DVIEW_H__C44168CA_DFD1_11D3_B3A4_004005A4A929__INCLUDED_)
