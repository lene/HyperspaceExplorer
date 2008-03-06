#include "../Vector.H"		

using namespace VecMath;

                                                        
    extern "C" Vector<4> f (double, double, double);	
    extern "C" char *symbolic ();			
                                                        
    Vector<4> f (double x, double y, double z) {		
      static Vector<4> F;					
      F[0] = x;						
      F[1] = y;						
      F[2] = z;						
      F[3] = pow (x*x*sin (y*y), z*z);			
                                                        
      return F; }					
                                                        
    char *symbolic () { return "pow (x*x*sin (y*y), z*z)"; }
