PATH = Utilities
INCLUDEPATH += $${PATH}
DEPENDPATH += $${PATH}

HEADERS += \
           $${PATH}/ChangeDir.h  \
           $${PATH}/FunctionDLL.h \
           $${PATH}/Globals.h \
           $${PATH}/GLUPerspective.h \
           $${PATH}/Log.h \
           $${PATH}/Multithreading.h \
           $${PATH}/MultithreadingPrivate.h \
           $${PATH}/NotYetImplementedException.h \
           $${PATH}/Observer.h \
           $${PATH}/Observer.impl.h  \
           $${PATH}/ScopedTimer.h  \
           $${PATH}/SingletonHolder.h \
           $${PATH}/Util.h

SOURCES += \
           $${PATH}/ChangeDir.C  \
           $${PATH}/FunctionDLL.C \
           $${PATH}/Globals.C \
           $${PATH}/GLUPerspective.cpp \
           $${PATH}/ScopedTimer.cpp \
           $${PATH}/Util.cpp
