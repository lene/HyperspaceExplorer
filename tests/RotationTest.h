#ifndef ROTATIONTEST_H_
#define ROTATIONTEST_H_

#include <QtTest/QtTest>


class RotationTest: public QObject {

    Q_OBJECT

private slots:
    void defaultCtor();
    void varargsCtor();
    void toMatrix();
    void plus();

};


#endif /* ROTATIONTEST_H_ */
