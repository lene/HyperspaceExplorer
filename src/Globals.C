
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include <qstring.h>
#include <sstream>

#include "Globals.H"

#include "numclass.H"
#include "GLObject.H"

double SR3 = sqrt (3.);

inline void CheckGLErrors (const char *op = 0) {
#   ifdef __DEBUG
    GLenum error;
    while ((error = glGetError ()) != GL_NO_ERROR)
      cerr << "GL Err: " << op << ": " << gluErrorString (error) << endl; 
#   endif
}

double ALPHA = .9, SHININESS = 32.;

float fog_color[]  = { 0.2, 0.2, 0.2, 1.0 },
      White[]      = { 1.0, 1.0, 1.0, 1.0 },
      grey50[]     = { 0.5, 0.5, 0.5, 1.0 };


void SetColor (const Vector &RGB) {
  static float *ambient  = new float [4], 
               *diffuse  = new float [4], 
               *specular = new float [4];

  for (unsigned i = 0; i < 3; i++) {
    ambient[i]  = RGB[i]/2.;
    diffuse[i]  = RGB[i];
    specular[i] = RGB[i] > .5? 1.: 2*RGB[i]; }
  ambient[3] = diffuse[3] = specular[3] = ::ALPHA;

  glMaterialfv (GL_FRONT, GL_AMBIENT,  ambient);
  glMaterialfv (GL_FRONT, GL_DIFFUSE,  diffuse);
  glMaterialfv (GL_FRONT, GL_SPECULAR, specular);
  glMaterialf  (GL_FRONT, GL_SHININESS,::SHININESS); }

#if 1
int GetGLList() {
	int MyList = 1;
	
	//	find a free GL list
	while (glIsList (MyList) == GL_TRUE) MyList++;

	return MyList;
}
#endif

void SetColor(float R, float G, float B)
{
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

double atod (QString s) {
  return s.toDouble ();
}
#if 1
string itoa (int x) {
	ostringstream o;
	o << x << ends;
	return o.str (); 
}

string ftoa (double x) {
	ostringstream o;
	o << x << ends;
	return o.str (); 
}
#endif
Vector vnormalize (Vector x) {
	static Vector n (3);
	double norm = sqrt (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);

	if (norm == 0) return x;

	n[0] = x[0]/norm; n[1] = x[1]/norm; n[2] = x[2]/norm;
	return n;
}

Vector vnormalize (double xx, double yy, double zz) {
	static Vector x (3);

	x[0] = xx; x[1] = yy; x[2] = zz;
	return vnormalize (x);
}

Vector vcross (Vector a, Vector b) {
	static Vector c (3);
	
	c[0] = a[1]*b[2]-a[2]*b[1];
	c[1] = a[2]*b[0]-a[0]*b[2];
	c[2] = a[0]*b[1]-a[1]*b[0];

	return c; 
}

Vector vcross (Vector a, Vector b, Vector c) {
	static Vector d (4);
	double A = b[0]*c[1]-b[1]*c[0],
		   B = b[0]*c[2]-b[2]*c[0],
		   C = b[0]*c[3]-b[3]*c[0],
		   D = b[1]*c[2]-b[2]*c[1],
		   E = b[1]*c[3]-b[3]*c[1],
		   F = b[2]*c[3]-b[3]*c[2];
	
	d[0] =  a[1]*F - a[2]*E + a[3]*D;
	d[1] = -a[0]*F + a[2]*C - a[3]*B;
	d[2] =  a[0]*E - a[1]*C + a[3]*A;
	d[3] = -a[0]*D + a[1]*B - a[2]*A;
	
	return d; 
}
