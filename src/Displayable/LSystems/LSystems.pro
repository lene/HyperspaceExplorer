TEMPLATE = app

CONFIG = debug qt warn_on uic

QT += opengl qt3support

INCLUDEPATH += .. ../../VecMath ../../Utilities

HEADERS += LSystem_old.h #  LSystem.h

SOURCES += LSystem_old.C LSys_aux.C # LSystem.cpp

DESTDIR = ./
TARGET = LSystem
