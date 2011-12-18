PATH = Displayable/Rotopes
INCLUDEPATH += $${PATH}
DEPENDPATH += $${PATH}
HEADERS += $${PATH}/Rotope.h \
           $${PATH}/RotopeFactory.h \
           $${PATH}/Projector.h \
           $${PATH}/RotopeInterface.h \
           $${PATH}/VertexData.h \
           $${PATH}/VertexDataPrinter.h \
           $${PATH}/Realm.h \
           $${PATH}/Extrude.h \
           $${PATH}/Taper.h \
           $${PATH}/Rotate.h \
           $${PATH}/Torate.h
SOURCES += $${PATH}/Rotope.C \
           $${PATH}/RotopeFactory.C \
           $${PATH}/RotopeInterface.C \
           $${PATH}/Realm.C \
           $${PATH}/RealmPrinter.C
