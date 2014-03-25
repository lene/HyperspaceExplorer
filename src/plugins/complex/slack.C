#include "Vector.H"			
#include <complex>						

using namespace VecMath;

                                                                
    extern "C" Vector<4> f (double, double);			
    extern "C" char *symbolic ();			        
                                                                
    Vector<4> f (double u, double v) {				
      static Vector<4> F;					
      std::complex<double> z (u, v), w = sin (z)*cos (z);	
      F[0] = u; 						
      F[1] = v;							
      F[2] = w.real ();						
      F[3] = w.imag ();						
                                                                
      return F; }						
                                                                
    char *symbolic () { return "sin (z)*cos (z)"; }	
