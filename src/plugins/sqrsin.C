#include "numclass.H"		
                                                        
    extern "C" Vector f (double, double, double);	
    extern "C" char *symbolic ();			
                                                        
    Vector f (double x, double y, double z) {		
      static Vector F (4);				
      F[0] = x;						
      F[1] = y;						
      F[2] = z;						
      F[3] = sin (x)+sin (y)+sin (z);			
                                                        
      return F; }					
                                                        
    char *symbolic () { return "sin (x)+sin (y)+sin (z)"; }
