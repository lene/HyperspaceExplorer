// stdafx.cpp : Quelltextdatei, die nur die Standard-Includes einbindet
//	SDI.pch ist die vorcompilierte Header-Datei
//	stdafx.obj enthält die vorcompilierte Typinformation

#include "stdafx.h"

#include <strstream>

int GetGLList(){
	int MyList = 1;
	
	//	find a free GL list
	while (glIsList (MyList) == GL_TRUE) MyList++;

	return MyList;
}

void SetColor(float R, float G, float B) {
	static GLfloat RGB[4] = { 0., 0., 0., 1. };

	RGB[0] = float (R); if (RGB [0] > 1) RGB[0] = 1;
	RGB[1] = float (G); if (RGB [1] > 1) RGB[1] = 1;
	RGB[2] = float (B); if (RGB [2] > 1) RGB[2] = 1;
	glMaterialfv (GL_FRONT, GL_DIFFUSE, RGB);

	RGB[0] /= 2.; RGB[1] /= 2.; RGB[2] /= 2.;
	glMaterialfv (GL_FRONT, GL_AMBIENT, RGB);

	RGB[0] *= 4.; if (RGB [0] < 0.5) RGB[0] = 0.5;
	RGB[1] *= 4.; if (RGB [1] < 0.5) RGB[1] = 0.5;
	RGB[2] *= 4.; if (RGB [2] < 0.5) RGB[2] = 0.5;
	glMaterialfv (GL_FRONT, GL_SPECULAR, RGB);
	glMaterialf (GL_FRONT, GL_SHININESS, 32.);
}

double atod (CString s) {
/*	double d;

	st << s;
	st >> d; 

	return d; */
	return atof (s.GetBuffer (16));
}

string itoa (int x) {
	ostrstream o;
	o << x << ends;
	return o.str (); 
}

string ftoa (double x) {
	ostrstream o;
	o << x << ends;
	return o.str (); 
}

int NumProcessors (void) {
 	SYSTEM_INFO SysInfo;
 	GetSystemInfo (&SysInfo);
 	return SysInfo.dwNumberOfProcessors;
}
