######################################################################
# Automatically generated by qmake (2.01a) Fri Jan 29 22:01:27 2010
######################################################################

QT += testlib

CONFIG += debug qt warn_on uic 
#CONFIG -= debug
#CONFIG += release qt warn_on uic

QT += opengl

QMAKE_CLEAN += Makefile

TEMPLATE = app
TARGET =
DEPENDPATH += . \
              ../src \
              ../src/Displayable \
              ../src/Displayable/Transformation \
              ../src/Displayable/Object \
              ../src/Utilities \
              ../src/Script \
              ../src/UI \
              ../src/VecMath \
              ../src/Color
INCLUDEPATH += . \
               ../src \
               ../src/Displayable \
               ../src/Displayable/Transformation \
               ../src/Displayable/Object \
               ../src/Utilities \
               ../src/Script \
               ../src/UI \
               ../src/VecMath \
               ../src/Color

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

INCLUDEPATH += ./Auxiliary
DEPENDPATH += ./Auxiliary

HEADERS += Auxiliary/GlobalFunctions.h \
           Auxiliary/MockView.h \
           Auxiliary/TestRunner.h
SOURCES += Auxiliary/GlobalFunctions.cpp \
           Auxiliary/MockView.cpp \
           Auxiliary/TestRunner.cpp

HEADERS += \
           Test_Util.h \
           Test_Composite.h \
           Test_Rotope.h \
           Test_Object.h \
           Test_ArrayList.h \
           Test_Observer.h \
           Test_DisplayableClass.h \
           Test_Realm.h \
           Test_Vector.h \
           Test_Matrix.h \
           Test_MultiDimensionalVector.h \
           Test_Rotation.h \
           Test_RealFunction.h \
           Test_Surface.h \
           Test_ParametricFunction.h \
           Test_FunctionValueGrid.h \
           Test_Transformation.h \
           Test_Projection.h \
           Test_GridDrawer.h \
           Test_FunctionFactory.h \
           Test_FunctionHolder.h \
           Test_PartitionedMultithreadedMap.h \
           Test_Function.h
SOURCES += \
           Test_Util.cpp \
           Test_Composite.cpp \
           Test_Rotope.cpp \
           Test_Object.cpp \
           Test_ArrayList.cpp \
           Test_Observer.cpp \
           Test_DisplayableClass.cpp \
           Test_Realm.cpp \
           Test_Vector.cpp \
           Test_Matrix.cpp \
           Test_MultiDimensionalVector.cpp \
           Test_Rotation.cpp \
           Test_RealFunction.cpp \
           Test_Surface.cpp \
           Test_ParametricFunction.cpp \
           Test_FunctionValueGrid.cpp \
           Test_Transformation.cpp \
           Test_Projection.cpp \
           Test_GridDrawer.cpp \
           Test_FunctionFactory.cpp \
           Test_FunctionHolder.cpp \
           Test_PartitionedMultithreadedMap.cpp \
           Test_Function.cpp \
           main.cpp

PRE_TARGETDEPS *= ../lib/libHyperspaceExplorer.a
LIBS *= ../lib/libHyperspaceExplorer.a
LIBS += -lQt5Concurrent

DEFINES += NEW_FUNCTION_HIERARCHY

TARGET = HyperspaceExplorer-tests

QMAKE_POST_LINK = ./HyperspaceExplorer-tests || rm -f $${TARGET}

###
### C++0x support
QMAKE_CXXFLAGS += -std=c++0x 
