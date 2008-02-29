#include "Vector.H"			
#include <complex>						
                                                                
    extern "C" Vector f (double, double);			
    extern "C" char *symbolic ();			        
                                                                
    Vector f (double u, double v) {				
      static Vector F (4);					
      complex<double> z (u, v), w = z.real ()*z.imag ();	
      F[0] = u; 						
      F[1] = v;							
      F[2] = w.real ();						
      F[3] = w.imag ();						
                                                                
      return F; }						
                                                                
    char *symbolic () { return "z.real ()*z.imag ()"; }	
