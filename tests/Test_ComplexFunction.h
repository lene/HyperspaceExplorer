/* 
 * File:   Test_ComplexFunction.h
 * Author: lene
 *
 * Created on March 28, 2014, 7:54 PM
 */

#ifndef TEST_COMPLEXFUNCTION_H
#define	TEST_COMPLEXFUNCTION_H

#include "Test_Surface.h"

class Test_ComplexFunction: public Test_Surface {

  Q_OBJECT
  
private slots:
        void t_z2();
        void t_z3();
        void t_zA();
        void t_ez();
        void t_emz2();
        void t_zm1();
        void t_zm2();
        void t_sqrtz();
        void t_lnz();
        void t_sinz();
        void t_cosz();
        void t_sinhz();
        void t_coshz();
        void t_tanz();

};

#endif	/* TEST_COMPLEXFUNCTION_H */

