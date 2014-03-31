/* 
 * File:   Test_Projector.h
 * Author: lene
 *
 * Created on March 31, 2014, 3:43 PM
 */

#ifndef TEST_PROJECTOR_H
#define	TEST_PROJECTOR_H

#include <QtTest/QtTest>
#include "Rotopes/Projector.impl.h"

class Test_Projector: public QObject {

    Q_OBJECT
   
private slots:

    void testProject3Dto2D();
    
};

#endif	/* TEST_PROJECTOR_H */

