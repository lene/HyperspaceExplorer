###
### build a library
###
TEMPLATE = lib

###
###     choose one:
###
###     release mode
CONFIG -= debug
CONFIG += release qt warn_on uic staticlib
###     debug mode
#CONFIG += debug qt warn_on uic dll staticlib

###
###     set the version number here
###
VERSION = 0.8.0

################################################################################
###
###     build
###

###
###     move all temporary files out of sight into subdirectory tmp
###
system(mkdir -p tmp)
OBJECTS_DIR = tmp
MOC_DIR = tmp
UI_DIR = tmp
UI_HEADERS_DIR = tmp
RCC_DIR = tmp

QMAKE_CLEAN += Makefile

###
###     C++20 support
###
QMAKE_CXXFLAGS += -std=c++2a

###
###     OpenGL support
###
QT += opengl widgets

###
###     global defines
###
DEFINES += PACKAGE_BUGREPORT="lene.preuss@gmail.com"
DEFINES += PACKAGE_VERSION="$${VERSION}"
DEFINES += USE_AUTO_PTR

###
###     defines for debug mode
###
CONFIG(debug){
    DEFINES += DEBUG TESTFEATURES
}

###
### turn profiling on in debug mode
###
QMAKE_CFLAGS_DEBUG += -pg -g3 -gdwarf-2 -O0
QMAKE_CXXFLAGS_DEBUG += -pg -g3 -gdwarf-2 -O0
QMAKE_LFLAGS_DEBUG += -pg

###
###     optimization for release mode
###
QMAKE_CXXFLAGS_RELEASE += -O2


################################################################################
###
### installation
###
DESTDIR = ../lib
TARGET = HyperspaceExplorer
INSTALLDIR = "/usr/local"
DEFINES += PREFIX="$${INSTALLDIR}"

target.path = $${INSTALLDIR}/lib
vector.files = Vector.h
vector.path = $${INSTALLDIR}/share/HyperspaceExplorer/plugins
docs.files = doc/*
docs.path =  $${INSTALLDIR}/share/HyperspaceExplorer/doc
INSTALLS += target vector docs
DISTFILES += ../devel/footer.html ../TO-DO

################################################################################
###
###     subdirectories
###
HEADERS += Color/Color.pri
include(Color/Color.pri)
HEADERS += Displayable/Displayable.pri
include(Displayable/Displayable.pri)
HEADERS += Script/Script.pri
include(Script/Script.pri)
HEADERS += UI/UI.pri
include(UI/UI.pri)
HEADERS += Utilities/Utilities.pri
include(Utilities/Utilities.pri)
HEADERS += VecMath/VecMath.pri
include(VecMath/VecMath.pri)
#HEADERS += plugins/plugins.pri
#include(plugins/plugins.pri)
