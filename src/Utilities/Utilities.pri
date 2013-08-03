PATH = Utilities
INCLUDEPATH += $${PATH}
DEPENDPATH += $${PATH}
HEADERS += \
           $${PATH}/Globals.h \
           $${PATH}/Log.h \
           $${PATH}/NotYetImplementedException.h \
           $${PATH}/Observer.h \
           $${PATH}/Observer.impl.h  \
           $${PATH}/ScopedTimer.h  \
           $${PATH}/SingletonHolder.h \
           $${PATH}/Tree.h \
           $${PATH}/Tree.impl.h \
           $${PATH}/Multithreading.h \
           $${PATH}/MultithreadingPrivate.h \
           $${PATH}/GLUPerspective.h \
           $${PATH}/Util.h
SOURCES += \
           $${PATH}/GLUPerspective.cpp \
           $${PATH}/Globals.C \
           $${PATH}/ScopedTimer.cpp \
           $${PATH}/Util.cpp
