#if !defined(AFX_SPONGEDLG_H__C44168FE_DFD1_11D3_B3A4_004005A4A929__INCLUDED_)
#define AFX_SPONGEDLG_H__C44168FE_DFD1_11D3_B3A4_004005A4A929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class C4DDoc;
#include "stdafx.h"
#include "4DView.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SpongeDlg 

class SpongeDlg : public CDialog
{
// Konstruktion
public:
	SpongeDlg(C4DDoc* pParent);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(SpongeDlg)
	enum { IDD = IDD_SPONGE_DLG };
	CString	m_sumax;
	CString	m_sumin;
	int		m_vsteps;
	int		m_usteps;
	CString	m_svmax;
	CString	m_svmin;
	CString	m_susteps;
	CString	m_svsteps;
	CString	m_sa;
	CString	m_sb;
	CString	m_sc;
	CString	m_sd;
	CString	m_stmax;
	CString	m_stmin;
	int		m_tsteps;
	CString	m_ststeps;
	//}}AFX_DATA

	double tmin () { return atof (m_stmin); }
	double tmax () { return atof (m_stmax); }
	double dt () { return (tmax ()-tmin ())/m_tsteps; }
	double umin () { return atof (m_sumin); }
	double umax () { return atof (m_sumax); }
	double du () { return (umax ()-umin ())/m_usteps; }
	double vmin () { return atof (m_svmin); }
	double vmax () { return atof (m_svmax); }
	double dv () { return (vmax ()-vmin ())/m_vsteps; }

	double a () { return atof (m_sa); }
	double b () { return atof (m_sb); }
	double c () { return atof (m_sc); }
	double d () { return atof (m_sd); }

	void SetParameterText (CString = "", CString = "", CString = "", CString = "");

	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(SpongeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	C4DDoc* pParent;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(SpongeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChange (UINT nIDEvent);
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPONGEDLG_H__C44168FE_DFD1_11D3_B3A4_004005A4A929__INCLUDED_
