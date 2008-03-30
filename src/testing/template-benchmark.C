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

/*  compile with: g++ template-benchmark.C -I.. -DDIM=4 -lrt
    To run a benchmark suite and only display the interesting results do:
    for i in $(seq 3 8); do
      for opt in -O -O2 -O3; do
        g++ $opt -DDIM=$i -I.. template-benchmark.C -lrt
        ./a.out 1000000 "Optimization: $opt" | grep -a Opt
      done
    done
*/

#include <cstdlib>
#include <ctime>
#include <cmath>

#include <iostream>
#include <string>
#include <sstream>

#include "matrix-dynamic.H"
#include "matrix.H"

template<typename Matrix>
    class benchmark {
        public:
            benchmark (unsigned nloop, std::string msg) {
                struct timespec start, stop;

                Matrix A (0,1, 0.1), B (1,2, 1./3.);

                // get starting time
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);

                for (int i = 0; i < nloop; i++) A = A*B;

                // get final time
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&stop);

                double run_time =(stop.tv_sec-start.tv_sec)
                            +(double)(stop.tv_nsec-start.tv_nsec)/1.e9;

                // report runtime
                std::cout << msg << " run time: " << run_time << std::endl;

                //  if the resulting matrix is not accessed afterwards,
                //  the compiler just optimizes the for loop above away with
                //  higher optimization settings
                A.print();
            }
    };

    /** makes a string  from an integer value
     *  implemented because I called a function itoa () ages ago, for convenience
     *  @param x	number to be converted
     *  @return	its string representation                                     */
    std::string itoa (int x) {
        std::ostringstream o;
        o << x << std::ends;
        return o.str ();
    }

main (int argc, char **argv) {
#   ifndef DIM                  //  these options can be passed to the compiler
        const unsigned DIM = 12;//  using -DDIM=... -DNLOOP=...
#   endif
#   ifndef NLOOP
        const unsigned NLOOP = 100000;
#   endif

    unsigned nloop = NLOOP;
    std::string prefix;
    if (argc > 1) nloop = atoi (argv[1]);
    if (argc > 2) prefix = argv[2];

    while (prefix.length() < 30) prefix.append(" ");
    //  matrix multiplication with template metaprogramming
    std::string text = prefix+" template metaprogramming - DIM = "+itoa(DIM);
    benchmark<VecMath::Matrix<DIM> > b1 (nloop, text);

    //  traditional matrix multiplication with for-loops
    text = prefix+" for loops                - DIM = "+itoa(DIM);
    benchmark<matrix<DIM> > b2 (nloop, text);
}
