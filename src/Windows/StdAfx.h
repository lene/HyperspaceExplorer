//	stdafx.h : Include-Datei f�r Standard-System-Include-Dateien, oder projekt-
//	spezifische Include-Dateien, die h�ufig benutzt, aber in unregelm��igen 
//	Abst�nden ge�ndert werden.

#if !defined(STDAFX_H)
#define STDAFX_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden

#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <windows.h>
#include <afxdtctl.h>		// MFC-Unterst�tzung f�r allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterst�tzung f�r g�ngige Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <math.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <string>
using namespace std;

#include "GeneralException.h"
#include "Vektor.h"


const double pi = 4*atan (1);

int GetGLList ();
void SetColor (float R, float G, float B);

double atod (CString);
string itoa (int x);
string ftoa (double x);

int NumProcessors (void);

inline void Debug (string s, string h = "") {
	MessageBox (NULL, s.c_str (), h.c_str (), MB_ICONINFORMATION);
}

template <class T> void Swap (T &a, T &b) {
	T temp (a);
	a = b;
	b = temp;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(STDAFX_H)
