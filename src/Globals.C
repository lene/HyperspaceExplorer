
//      project:      hyperspace explorer
//      module:       Globals.C
//      contains:     definitions of global variables and functions
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include <qstring.h>
#include <fstream>
#include <sstream>

#include "Globals.H"

#include "Vector.H"
#include "GLObject.H"

using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::ostringstream;
using std::ends;

/*******************************************************************************
 *  sqrt (3), stored to save computation time, probably superfluous, wtf
 */
double SR3 = sqrt (3.);


/*******************************************************************************
 *  global (YUCK!) alpha value for transparent display
 */
double ALPHA = .9;


/*******************************************************************************
 *  global (YUCK!) shininess value
 */
double SHININESS = 32.;


/*******************************************************************************
 *  global (YUCK!) fog/depth cue color
 */
float fog_color[]  = { 0.2, 0.2, 0.2, 1.0 };


/*******************************************************************************
 *  color definition for White
 */
float White[]      = { 1.0, 1.0, 1.0, 1.0 };


/*******************************************************************************
 *  color definition for Black
 */
float grey50[]     = { 0.5, 0.5, 0.5, 1.0 };

float background[] = { 0.1, 0.1, 0.1, 1.0 };

/*
inline float *BackgroundColor() {
  return background;
}
inline float setBackground(float r, float g, float b, float a = 1.0) {
  background[0] = r;
  background[1] = g;
  background[2] = b;
  background[3] = a;
}
*/
/*******************************************************************************
 *  debug function for OpenGL commands; outputs all current GL errors on cerr
 *  @param op		optional repetition of last GL command
 */
inline void CheckGLErrors (const char *op = 0) {
#   ifdef __DEBUG
    GLenum error;
    while ((error = glGetError ()) != GL_NO_ERROR)
      cerr << "GL Err: " << op << ": " << gluErrorString (error) << endl; 
#   endif
}


/*******************************************************************************
 *  set the current OpenGL color
 *  uses HARDCODED simple algorithm to set ambient and specular values for a
 *  specific color: if halves resp. dobles them, clipping at 1.0
 *  THIS FUNCTION IS UGLY IN MANY RESPECTS!
 *  @param RGB		RGB value to be set
 */
void SetColor (const Vector<4> &RGB) {
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
  glMaterialf  (GL_FRONT, GL_SHININESS,::SHININESS);
}


/*******************************************************************************
 *  set the current OpenGL color
 *  uses HARDCODED simple algorithm to set ambient and specular values for a
 *  specific color: if halves resp. dobles them, clipping at 1.0
 *  THIS FUNCTION IS UGLY IN MANY RESPECTS!
 *  @param R		R value to be set
 *  @param G		G value to be set
 *  @param B		B value to be set
 */
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
	glMaterialf (GL_FRONT, GL_SHININESS, ::SHININESS);
}


/*******************************************************************************
 *  find the ID of the first free GL list
 *  @return	first freee GL list
 */
#if 1
int GetGLList() {
	int MyList = 1;
	
	//	find a free GL list
	while (glIsList (MyList) == GL_TRUE) MyList++;

	return MyList;
}
#endif


/*******************************************************************************
 *  makes a double precision value from a QString
 *  implemented because I called a function atod () ages ago, for convenience
 *  @param s	string to be converted
 *  @return	its numerical value
 */
double atod (QString s) {
  return s.toDouble ();
}


#if 1
/*******************************************************************************
 *  makes a string  from an integer value
 *  implemented because I called a function itoa () ages ago, for convenience
 *  @param x	number to be converted
 *  @return	its string representation
 */
string itoa (int x) {
	ostringstream o;
	o << x << ends;
	return o.str (); 
}


/*******************************************************************************
 *  makes a string  from a double value
 *  implemented because I called a function ftoa () ages ago, for convenience
 *  @param x	number to be converted
 *  @return	its string representation
 */
string ftoa (double x) {
	ostringstream o;
	o << x << ends;
	return o.str (); 
}
#endif


/*******************************************************************************
 *  normalizes a Vector made from 3 doubles out-of-place
 *  @param xx	x component of Vector to be normalized
 *  @param yy	y component of Vector to be normalized
 *  @param zz	z component of Vector to be normalized
 *  @return	normalized Vector
 */
Vector<3> vnormalize (double xx, double yy, double zz) {
	static Vector<3> x;

	x[0] = xx; x[1] = yy; x[2] = zz;
	return vnormalize (x);
}


/*******************************************************************************
 *  get the system memory from /proc/meminfo
 *  of course, this only works on OS's with /proc filesystem and /proc/meminfo
 *  information!
 *  relies on /proc/meminfo of being of the format:
 *  MemTotal:       506912 kB
 *  ...
 *  returns 512 MB as default memory size, when /proc/meminfo is not present
 *  @return	total memory size, or 512 MB
 */
unsigned long check_proc_meminfo () {
  ifstream in ("/proc/meminfo");
  if (!in) {
    cerr << "no /proc/meminfo - setting Memory limit of 512 MB" << endl;
    return 512*1024*1024;
  }
  string meminfo;
  in >> meminfo;
  in >> meminfo;
  return strtoul (meminfo.c_str (), NULL, 10)*1024;
}


/*******************************************************************************
 *  maximum memory that should be consumed; calls check_proc_meminfo () above
 */
extern unsigned long MaximumMemory = check_proc_meminfo (); 
