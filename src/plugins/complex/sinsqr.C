#include "../Vector.H"		

using namespace VecMath;

                                                        
    extern "C" Vector<4> f (double, double);	
    extern "C" char *symbolic ();			
                                                        
    Vector<4> f (double x, double y) {		
      static Vector<4> F;				
      complex<double> z (u, v), w = sin (z*z);
      
      F[0] = u; 						
      F[1] = v;							
      F[2] = w.real ();						
      F[3] = w.imag ();						
                                                                
      return F; }						
                                                                
    char *symbolic () { return "sin (z*z)"; }	
