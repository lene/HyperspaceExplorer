TEMPLATE = app
CONFIG += debug qt warn_on uic
QT += opengl
INCLUDEPATH += ../src/Color \
	       ../src/Displayable \
               ../src/Displayable/Rotopes \
               ../src/Script \
               ../src/UI \
               ../src/Utilities \
               ../src/VecMath \
               ../src

SOURCES += Main.C

QMAKE_CLEAN += Makefile

PRE_TARGETDEPS *= ../lib/libHyperspaceExplorer.a \
                  ../tests/HyperspaceExplorer-tests
LIBS *= ../lib/libHyperspaceExplorer.a -ldl -lGLU -lQt5Concurrent

DESTDIR = ..
TARGET = HyperspaceExplorer

target.path = $${INSTALLDIR}/bin
vector.files = Vector.h
vector.path = $${INSTALLDIR}/share/HyperspaceExplorer/plugins
docs.files = doc/*
docs.path =  $${INSTALLDIR}/share/HyperspaceExplorer/doc
INSTALLS += target vector docs
DISTFILES += ../devel/footer.html ../TODO

QMAKE_CFLAGS_DEBUG += -pg -g3 -gdwarf-2
QMAKE_CXXFLAGS_DEBUG += -pg -g3 -gdwarf-2
QMAKE_LFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS += -std=c++0x
