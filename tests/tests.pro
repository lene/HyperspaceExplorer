######################################################################
# Automatically generated by qmake (2.01a) Fri Jan 29 22:01:27 2010
######################################################################

CONFIG += qtestlib
CONFIG += debug qt warn_on uic

QT += opengl

TEMPLATE = app
TARGET =
DEPENDPATH += . ../src ../src/Functions ../src/Loki ../src/Script ../src/UI ../src/VecMath
INCLUDEPATH += . ../src ../src/Functions ../src/Loki ../src/Script ../src/UI ../src/VecMath

###
###     move all temporary files out of sight into subdirectory tmp
###
system(mkdir -p tmp)
OBJECTS_DIR = tmp
MOC_DIR = tmp
UI_DIR = tmp
UI_HEADERS_DIR = tmp
RCC_DIR = tmp

# Input
HEADERS += Test_Rotope.h \
           Test_Realm.h \
           Test_Vector.h \
           Test_Matrix.h \
           Test_NestedVector.h \
           Test_Rotation.h \
           Test_RealFunction.h \
           Test_Surface.h \
           Test_ParametricFunction.h \
           Test_FunctionValueGrid.h \
           Test_Transformation.h \
           Test_Projection.h \
           Test_FunctionFactory.h \
           Test_Function.h
SOURCES += main.cpp \
           Test_Rotope.cpp \
           Test_Realm.cpp \
           Test_Vector.cpp \
           Test_Matrix.cpp \
           Test_NestedVector.cpp \
           Test_Rotation.cpp \
           Test_RealFunction.cpp \
           Test_Surface.cpp \
           Test_ParametricFunction.cpp \
           Test_FunctionValueGrid.cpp \
           Test_Transformation.cpp \
           Test_Projection.cpp \
           Test_FunctionFactory.cpp \
           Test_Function.cpp

PRE_TARGETDEPS *= ../lib/libHyperspaceExplorer.a
LIBS *= ../lib/libHyperspaceExplorer.a

DEFINES += NEW_FUNCTION_HIERARCHY

TARGET = HyperspaceExplorer-tests

QMAKE_POST_LINK = ./HyperspaceExplorer-tests
