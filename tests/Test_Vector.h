#ifndef VECTORTEST_H_
#define VECTORTEST_H_

#include <QtTest/QtTest>

/// Unit tests for class VecMath::Vector
class Test_Vector: public QObject {

    Q_OBJECT

private slots:
    void defaultConstructor();
    void varargsConstructor();
    void plus();
    void minus();
    void scale();
    void dotProduct();
    void sqnorm();
    void equals();
    void smaller();
    void toString();
};


#endif /* VECTORTEST_H_ */
