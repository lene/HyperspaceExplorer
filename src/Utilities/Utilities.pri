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
           $${PATH}/Util.h
SOURCES += \
           $${PATH}/Globals.C \
           $${PATH}/ScopedTimer.cpp \
           $${PATH}/Util.cpp
