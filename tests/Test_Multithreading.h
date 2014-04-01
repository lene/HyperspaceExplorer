/* 
 * File:   Test_Multithreading.h
 * Author: lene
 *
 * Created on April 1, 2014, 12:59 PM
 */

#ifndef TEST_MULTITHREADING_H
#define	TEST_MULTITHREADING_H

#include <QtTest/QtTest>

class Test_Multithreading: public QObject {
    
    Q_OBJECT
    
private slots:

    void test_mapped();
    void test_partitionedMap();
    void test_partitionedMapInPlace();
    void test_partitionedMapped();
    
private:
    
    const unsigned CONTAINER_SIZE = 1024;
    
};

#endif	/* TEST_MULTITHREADING_H */

