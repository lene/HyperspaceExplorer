
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "Globals.H"
#include "SteinerFunction.H"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

SteinerFunction::SteinerFunction (double _umin, double _umax, double _ustep,
				  double _vmin, double _vmax, double _vstep,
				  double _a):
  umin (_umin),	umax (_umax),	du (_ustep),
  vmin (_vmin),	vmax (_vmax),	dv (_vstep),
  a (_a),
  F (new double [3]), DF (new double * [3]) {
  for (unsigned i = 0; i < 3; i++)
    DF[i] = new double [3];
}

SteinerFunction::~SteinerFunction() {
}

double *SteinerFunction::f (double uu, double vv) {
  F[0] = (a+cos(uu/2)*sin(vv)-sin(uu/2)*sin(2*vv))*cos(uu);	//	klein bottle
  F[1] = (a+cos(uu/2)*sin(vv)-sin(uu/2)*sin(2*vv))*sin(uu);
  F[2] = sin(uu/2)*sin(vv)+cos(uu/2)*sin(2*vv);				

/*	double b=1, c=0.1, n=3;
	F[0] = a*(1-vv/(2*pi))*cos(n*vv)*(1+cos(uu))+c*cos(n*vv);	//	conic spiral
    F[1] = a*(1-vv/(2*pi))*sin(n*vv)*(1+cos(uu))+c*sin(n*vv);
    F[2] = b*vv/(2*pi)+a*(1-vv/(2*pi))*sin(uu);					*/

  return F; 
}

double **SteinerFunction::df (double uu, double vv) {
	//	derive after uu first
  DF[0][0] = -1/2.*(sin (uu/2)*sin (vv) + cos (uu/2)*sin (2*vv))*cos (uu)
             -   (a+cos (uu/2)*sin (vv) - sin (uu/2)*sin (2*vv))*sin (uu);
  DF[0][1] =  1/2.*(sin (uu/2)*sin (vv) + cos (uu/2)*sin (2*vv))*sin (uu)
             +   (a+cos (uu/2)*sin (vv) - sin (uu/2)*sin (2*vv))*cos (uu);
  DF[0][2] =  1/2.*(cos (uu/2)*sin (vv) - sin (uu/2)*sin (2*vv));

	//	now vv
  DF[1][0] =	(cos (uu/2)*cos (vv) - 2*sin (uu/2)*cos (2*vv))*cos (uu);
  DF[1][1] =	(cos (uu/2)*cos (vv) - 2*sin (uu/2)*cos (2*vv))*sin (uu);
  DF[1][2] =	 sin (uu/2)*cos (vv) + 2*cos (uu/2)*cos (2*vv);

  return DF; 
}


void SteinerFunction::Draw (void) {
  for (double u = umin; u <= umax; u += du) {
    glBegin (GL_QUAD_STRIP);
    for (double v = vmin; v <= vmax+dv; v += dv) {
      F = f (u, v);
      SetColor (F[0], F[1], F[2]);
      glVertex (F);
      F = f (u+du, v);
      SetColor (F[0], F[1], F[2]);
      glVertex (F);
    }
    glEnd ();
  }		
}
