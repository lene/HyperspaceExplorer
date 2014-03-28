/* 
 * File:   Test_ChangeDir.h
 * Author: lene
 *
 * Created on 28 March 2014, 18:38
 */

#ifndef TEST_CHANGEDIR_H
#define	TEST_CHANGEDIR_H

#include "ChangeDir.h"

#include <QtTest/QtTest>

class Test_ChangeDir: public QObject {
  
  Q_OBJECT
  
private slots:  
  void dirIsChanged();
  void changeBackOnExit();
  
private:
  QString temp_dir;    

};

#endif	/* TEST_CHANGEDIR_H */

