#include "Vector.H"		

using namespace VecMath;

    Vector<4> f (double x, double y, double z) {		
      static Vector<4> F;				
      F[0] = x;						
      F[1] = y;						
      F[2] = z;						
      F[3] = sqrt (x*x*x*x+y*y*y*y+z*z*z*z);			
                                                        
      return F; }					
                                                        
    char *symbolic () { return "sqrt (x*x*x*x+y*y*y*y+z*z*z*z)"; }
    