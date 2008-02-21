
//      project:      hyperspace explorer
//      module:       Globals.H
//      contains:     declarations for some global auxiliary functions and
//		      variables
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(GLOBALS_H)
#define GLOBALS_H

#include <string>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>

#include <qmessagebox.h>

#include "ValuesDialogImpl.H"
#include "numclass.H"

class Vector;

const bool check_memory = false;

extern double SR3; 

extern unsigned long MaximumMemory;

int GetGLList();

void SetColor(float R, float G, float B);

extern float background[], fog_color[];

inline float *BackgroundColor() { return background; }
inline void setBackground(float r, float g, float b, float a = 1.0) {
  background[0] = r;
  background[1] = g;
  background[2] = b;
  background[3] = a;
}

inline float *FogColor() { return fog_color; }
inline void setFogColor(float r, float g, float b, float a = 1.0) {
  fog_color[0] = r;
  fog_color[1] = g;
  fog_color[2] = b;
  fog_color[3] = a;
}

double atod (QString);

std::string itoa (int x);
std::string ftoa (double x);

Vector vnormalize (Vector );
Vector vcross (Vector , Vector);
Vector vcross (Vector , Vector, Vector);

inline void Debug (std::string s, std::string h = "") {
    QMessageBox::information (NULL, h.c_str (), s.c_str ());
}

inline void glVertex (Vector &V) {
    if (__finite (V.sqnorm ()))
	glVertex3dv (V.data ());
}
    
template <class T> void Swap (T &a, T &b) {
	T temp (a);
	a = b;
	b = temp;
}


#endif // !defined(GLOBALS_H)
