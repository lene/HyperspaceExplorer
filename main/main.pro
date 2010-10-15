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

PRE_TARGETDEPS *= ../lib/libHyperspaceExplorer.a \
                  ../tests/HyperspaceExplorer-tests
LIBS *= ../lib/libHyperspaceExplorer.a

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
