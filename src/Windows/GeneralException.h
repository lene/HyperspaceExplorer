// GeneralException.h: Schnittstelle für die Klasse GeneralException.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERALEXCEPTION_H__8EB0AEA5_FBF8_11D3_B3AF_004005A4A929__INCLUDED_)
#define AFX_GENERALEXCEPTION_H__8EB0AEA5_FBF8_11D3_B3AF_004005A4A929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

using namespace std;


class GeneralException {
public:
	GeneralException (string s) {
		MessageBox (NULL, ("An Error has occured:\n"+s).c_str (), "Uh-Oh", MB_ICONSTOP); }
	virtual ~GeneralException() {};
};

class GLException {
public:
	GLException (string s) {
		MessageBox (NULL, s.c_str (), "OpenGL problem", MB_ICONSTOP); }
	virtual ~GLException() {};
};

#endif // !defined(AFX_GENERALEXCEPTION_H__8EB0AEA5_FBF8_11D3_B3AF_004005A4A929__INCLUDED_)
