
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
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <qmessagebox.h>

#include "ValuesDialogImpl.H"
#include "numclass.H"

using namespace std;
class Vector;

extern double SR3; 

const unsigned MaximumMemory = 180;

int GetGLList();

void SetColor(float R, float G, float B);

double atod (QString);

string itoa (int x);
string ftoa (double x);

Vector vnormalize (Vector );
Vector vcross (Vector , Vector);
Vector vcross (Vector , Vector, Vector);

inline void Debug (string s, string h = "") {
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
