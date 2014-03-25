PATH = Utilities
INCLUDEPATH += $${PATH}
DEPENDPATH += $${PATH}
HEADERS += \
           $${PATH}/FunctionDLL.h \
           $${PATH}/Globals.h \
           $${PATH}/GLUPerspective.h \
           $${PATH}/Log.h \
           $${PATH}/Multithreading.h \
           $${PATH}/MultithreadingPrivate.h \
           $${PATH}/NotYetImplementedException.h \
           $${PATH}/Observer.h \
           $${PATH}/Observer.impl.h  \
           $${PATH}/PathChange.h  \
           $${PATH}/ScopedTimer.h  \
           $${PATH}/SingletonHolder.h \
           $${PATH}/Tree.h \
           $${PATH}/Tree.impl.h \
           $${PATH}/Util.h
SOURCES += \
           $${PATH}/FunctionDLL.C \
           $${PATH}/Globals.C \
           $${PATH}/GLUPerspective.cpp \
           $${PATH}/PathChange.C  \
           $${PATH}/ScopedTimer.cpp \
           $${PATH}/Util.cpp
