
//      project:      hyperspace explorer
//      module:       SteinerFunction.C
//      contains:     Steiner surfaces -- this is sort of a dead branch, haven't
//		      really implemented anything; the present example is in 3D
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "Globals.H"
#include "SteinerFunction.H"


//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  SteinerFunction c'tor given a definition set in R² (as parameter space)
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _a		parameter for klein bottle
 */
SteinerFunction::SteinerFunction (double _umin, double _umax, double _ustep,
				  double _vmin, double _vmax, double _vstep,
				  double _a):
  umin (_umin),	umax (_umax),	du (_ustep),
  vmin (_vmin),	vmax (_vmax),	dv (_vstep),
  a (_a),
  F (3), DF (new Vector [3]) {
  for (unsigned i = 0; i < 3; i++)
    DF[i] = new Vector (3);
}


/*******************************************************************************
 *  SteinerFunction destructor
 */
SteinerFunction::~SteinerFunction() {
}


/*******************************************************************************
 *  SteinerFunction defining function
 *  @param uu		u value
 *  @param vv		v value
 *  @return		value of defining function at point in question
 */
Vector &SteinerFunction::f (double uu, double vv) {
  F[0] = (a+cos(uu/2)*sin(vv)-sin(uu/2)*sin(2*vv))*cos(uu);	//	klein bottle
  F[1] = (a+cos(uu/2)*sin(vv)-sin(uu/2)*sin(2*vv))*sin(uu);
  F[2] = sin(uu/2)*sin(vv)+cos(uu/2)*sin(2*vv);				

/*	double b=1, c=0.1, n=3;
	F[0] = a*(1-vv/(2*pi))*cos(n*vv)*(1+cos(uu))+c*cos(n*vv);	//	conic spiral
    F[1] = a*(1-vv/(2*pi))*sin(n*vv)*(1+cos(uu))+c*sin(n*vv);
    F[2] = b*vv/(2*pi)+a*(1-vv/(2*pi))*sin(uu);					*/

  return F; 
}


/*******************************************************************************
 *  hand-rolled implementation of the derivatives in u and v (for klein's bottle)
 *  @param uu		u value
 *  @param vv		v value
 *  @return		gradient in u and v as array
 */
Vector *SteinerFunction::df (double uu, double vv) {
  static Vector F0 (3);			//	f (u, v)
  static Vector DF[2];
  
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


/*******************************************************************************
 *  three-dimensional implementation of the draw routine
 */
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
