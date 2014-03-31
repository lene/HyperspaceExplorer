/* 
 * File:   Test_ColorManager.h
 * Author: lene
 *
 * Created on March 31, 2014, 1:16 PM
 */

#ifndef TEST_COLORMANAGER_H
#define	TEST_COLORMANAGER_H

#include <QtTest/QtTest>
class Test_ColorManager: public QObject {

    Q_OBJECT
    
private slots:
    
    void initTestCase();
    
    void testgetRegisteredColorManagers();
    void testisColorManagerSet();
    
    void testFastxyz2RGBColorManager();
    void testdepth2RGBColorManager();
    void testmonochromeColorManager();
    
};

#endif	/* TEST_COLORMANAGER_H */

