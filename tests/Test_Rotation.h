#ifndef ROTATIONTEST_H_
#define ROTATIONTEST_H_

#include <QtTest/QtTest>


class Test_Rotation: public QObject {

    Q_OBJECT

    static const double EPSILON = 1e-8;

private slots:
    void defaultCtor();
    void varargsCtor();
    void toMatrix();
    void plus();

};


#endif /* ROTATIONTEST_H_ */
