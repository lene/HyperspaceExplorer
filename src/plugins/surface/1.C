#include "numclass.H"	
                                                
    extern "C" Vector f (double, double);	
    extern "C" char *symbolic ();		
                                                
    Vector f (double u, double v) {		
      static Vector F (4);			
      F[0] = u+v;		
      F[1] = u-v;		
      F[2] = u*v;		
      F[3] = u/v;		
                                                
    return F; 					
}						
                                                
    char *symbolic () { return "(u+v, u-v, u*v, u/v)"; }
