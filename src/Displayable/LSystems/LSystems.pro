TEMPLATE = app

CONFIG = debug qt warn_on uic

QT += opengl qt3support

INCLUDEPATH += .. ../../VecMath ../../Utilities

HEADERS += LSystem.h LSystem_old.h

SOURCES += LSystem.cpp LSystem_old.C LSys_aux.C
#SOURCES += numclass.C

DESTDIR = ./
TARGET = LSystem
