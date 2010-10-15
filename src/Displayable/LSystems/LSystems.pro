TEMPLATE = app

CONFIG = debug qt warn_on uic

QT += opengl qt3support

INCLUDEPATH += ../../VecMath

HEADERS += LSystem.H # numclass.H ../Matrix.H

SOURCES += LSystem.C LSys_aux.C
#SOURCES += numclass.C

DESTDIR = ./
TARGET = LSystem
