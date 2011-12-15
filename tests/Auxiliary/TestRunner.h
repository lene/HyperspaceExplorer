/* 
 * File:   TestRunner.h
 * Author: lene
 *
 * Created on December 15, 2011, 8:45 PM
 */

#ifndef TESTRUNNER_H
#define	TESTRUNNER_H

#include <QtTest/QtTest>

class TestRunner {

  public:

    TestRunner();

    void run(QObject *test);

    void printSummary() const;

    unsigned exitValue() const;

  private:

    class Impl;
    Impl *pImpl;
    
};

#endif	/* TESTRUNNER_H */
