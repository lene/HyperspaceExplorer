/***************************************************************************
 *   Copyright (C) 2004 by helge preuss                                    *
 *   scout@hyperspace-travel.de                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


//#include "vector.H"
#include "matrix.H"

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <numeric>
#include <sstream>


//#ifdef DMALLOC
//#include "dmalloc.h"

//#endif



using namespace std;


main (int argc, char **argv) {
# ifndef DIM  				//  these options can be passed to the compiler
    const unsigned DIM = 10;		//  using -DDIM=... -DNLOOP=...
# endif
# ifndef NLOOP    
    const unsigned NLOOP = 1;		
# endif

    unsigned nloop = NLOOP;

    if (argc > 1) nloop = atoi (argv[1]);

# if 0    
    vec<DIM> v (true), w (true);
    v.print ();  w.print ();
    cout << v.dot (w) << endl;
    cout << vec<DIM>::Access<1>::checked_access (v) << endl;
    //  cout << vec<DIM>::Access<DIM+1>::checked_access (v) << endl;
# endif
  clock_t stime = clock ();					//  record start time
 
  SquareMatrix<DIM> A, B (true);
    //   A.print ();
//   B.print ();
    SquareMatrix<DIM> C = A;

# if 0
    for (int i = 0; i < nloop; i++) {
    C *= B;
    //  C.own_data (true);

    double d;
    d = B.det ();
    cout << d << endl;
# endif
  }
  double execution_time = double (clock ()-stime)/double (CLOCKS_PER_SEC);
  cout << "dimension: " << DIM 
       << setprecision(7) << "  execution_time = " << execution_time << endl
       << "(" << double (nloop)/execution_time << " matrix multiplications per second)" << endl
       << "(" << double (nloop)/execution_time*DIM*DIM*DIM/1000/1000 << " MFLOPS (add+multiply))"
       << endl;
}

