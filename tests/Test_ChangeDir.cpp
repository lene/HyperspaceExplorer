/* 
 * File:   Test_ChangeDir.cpp
 * Author: lene
 * 
 * Created on 28 March 2014, 18:38
 */

#include "Test_ChangeDir.h"

#include "GlobalFunctions.h"

#include <QTemporaryDir>

using namespace UnitTests;

void Test_ChangeDir::initTestCase() {
}

void Test_ChangeDir::dirIsChanged() {
    QTemporaryDir temp_dir;
    test(temp_dir.isValid(), std::string("temporary directory created"));
    test(QDir::currentPath() != temp_dir.path(), std::string("whut? we already changed to the temp dir?"));
    ChangeDir path_change(temp_dir.path());
    test(QDir::currentPath() == temp_dir.path(), std::string("path changed"));
}

void Test_ChangeDir::changeBackOnExit() {
    QTemporaryDir temp_dir;
    test(temp_dir.isValid(), std::string("temporary directory created"));
    QString old_path = QDir::currentPath();
    test(old_path != temp_dir.path(), std::string("whut? we already changed to the temp dir?"));
    {
        ChangeDir path_change(temp_dir.path());
        test(QDir::currentPath() == temp_dir.path(), std::string("path changed"));
    }
    test(QDir::currentPath() == old_path, std::string("path changed back when objet went out of scope"));
}