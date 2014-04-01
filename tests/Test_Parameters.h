/* 
 * File:   Test_Parameters.h
 * Author: lene
 *
 * Created on April 1, 2014, 5:01 PM
 */

#ifndef TEST_PARAMETERS_H
#define	TEST_PARAMETERS_H

#include <QtTest/QtTest>


class Test_Parameters: public QObject {

    Q_OBJECT
    
private slots:

    void test_insertAndRetrieve();
    void test_insertByDefault();
    void test_changeValue();
    void test_nonexistentEntry();
};

#endif	/* TEST_PARAMETERS_H */

