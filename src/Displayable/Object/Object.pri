PATH = Displayable/Object
INCLUDEPATH += $${PATH}
DEPENDPATH += $${PATH}
HEADERS += \
           $${PATH}/Object.h \
           $${PATH}/SurfaceType.h \
           $${PATH}/SurfaceType.impl.h \
           $${PATH}/ObjectImplementations.h \
           $${PATH}/Sponge.h
SOURCES += \
           $${PATH}/Object.C \
           $${PATH}/ObjectImplementations.cpp \
           $${PATH}/Sponge.C
