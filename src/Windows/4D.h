// 4D.h : Haupt-Header-Datei für die Anwendung 4D
//

#if !defined(AFX_4D_H__C44168C2_DFD1_11D3_B3A4_004005A4A929__INCLUDED_)
#define AFX_4D_H__C44168C2_DFD1_11D3_B3A4_004005A4A929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// C4DApp:
// Siehe 4D.cpp für die Implementierung dieser Klasse
//

class C4DApp : public CWinApp
{
public:
	C4DApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(C4DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(C4DApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_4D_H__C44168C2_DFD1_11D3_B3A4_004005A4A929__INCLUDED_)
