#include "numclass.H"			
#include <complex>						
                                                                
    extern "C" Vector f (double, double);			
    extern "C" char *symbolic ();			        
                                                                
    Vector f (double u, double v) {				
      static Vector F (4);					
      complex<double> z (u, v), w = sin (z)*cos (z);	
      F[0] = u; 						
      F[1] = v;							
      F[2] = w.real ();						
      F[3] = w.imag ();						
                                                                
      return F; }						
                                                                
    char *symbolic () { return "sin (z)*cos (z)"; }	
