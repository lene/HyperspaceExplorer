TEMPLATE = lib

#CONFIG -= debug
#CONFIG += release qt warn_on uic
CONFIG += debug qt warn_on uic dll staticlib

QT += opengl

VERSION = 0.6.4

###
###     move all temporary files out of sight into subdirectory tmp
###
system(mkdir -p tmp)
OBJECTS_DIR = tmp
MOC_DIR = tmp
UI_DIR = tmp
UI_HEADERS_DIR = tmp
RCC_DIR = tmp

################################################################################
###     subdirectories
###
###
###     Functions
###
INCLUDEPATH += ./Functions
DEPENDPATH += ./Functions
HEADERS += Functions/ComplexFunction.h \
           Functions/CustomFunction.h \
           Functions/Function.h \
           Functions/Object.h \
           Functions/Surface.h \
           Functions/RealFunction.h \
           Functions/FunctionParameter.h \
           Functions/ParameterMap.h \
           Functions/FunctionFactory.h \
           Functions/Transform.h \
           Functions/Sponge.h
#          Functions/SteinerFunction.h
SOURCES += Functions/ComplexFunction.C \
           Functions/CustomFunction.C \
           Functions/Function.C \
           Functions/Surface.C \
           Functions/Object.C \
           Functions/RealFunction.C \
           Functions/FunctionParameter.C \
           Functions/FunctionFactory.C \
           Functions/Sponge.C
#          Functions/SteinerFunction.C

###
###     Rotopes
###
INCLUDEPATH += ./Functions/Rotopes
DEPENDPATH += ./Functions/Rotopes
HEADERS += Functions/Rotopes/Rotope.h \
           Functions/Rotopes/RotopeFactory.h \
           Functions/Rotopes/Projector.h \
           Functions/Rotopes/RotopeInterface.h \
           Functions/Rotopes/VertexData.h \
           Functions/Rotopes/Realm.h \
           Functions/Rotopes/Extrude.h \
           Functions/Rotopes/Taper.h \
           Functions/Rotopes/Rotate.h \
           Functions/Rotopes/Torate.h
SOURCES += Functions/Rotopes/Rotope.C \
           Functions/Rotopes/RotopeFactory.C \
           Functions/Rotopes/Realm.C \
           Functions/Rotopes/RealmPrinter.C

###
###     Script
###
INCLUDEPATH += ./Script
DEPENDPATH += ./Script
HEADERS += Script/Parser.h \
           Script/Statement.h
SOURCES += Script/Parser.C \
           Script/Statement.C

###
###     UI
###
INCLUDEPATH += ./UI
DEPENDPATH += ./UI
HEADERS += UI/4DView.h \
           UI/ComplexDialogImpl.h \
           UI/FunctionDialogImpl.h \
           UI/PolarDialogImpl.h \
           UI/SurfaceDialogImpl.h \
           UI/ValuesDialogImpl.h \
           UI/Menu4D.h \
           UI/PluginCreator.h \
           UI/AnimationDialogImpl.h \
           UI/SlotHelper.h \
           UI/CustomFunctionSlot.impl.h \
           UI/TemplatedFunctionFactory.impl.h \
           UI/ValuesDialog.h \
           UI/MouseHandler.h \
           UI/View.h \
           UI/ViewImpl.h \
           UI/ParameterInput.h \
           UI/RotationControl.h \
           UI/RotationSlider.h
SOURCES += UI/4DView.C \
           UI/Menu4D.C \
           UI/ComplexDialogImpl.C \
           UI/FunctionDialogImpl.C \
           UI/PolarDialogImpl.C \
           UI/SurfaceDialogImpl.C \
           UI/ValuesDialogImpl.C \
           UI/PluginCreator.C \
           UI/AnimationDialogImpl.C \
           UI/SlotHelper.C \
           UI/MouseHandler.C \
           UI/ViewImpl.C \
           UI/ParameterInput.C \
           UI/RotationControl.C \
           UI/RotationSlider.C
FORMS += UI/ComplexDialog.ui \
         UI/FunctionDialog.ui \
         UI/PolarDialog.ui \
         UI/SurfaceDialog.ui \
         UI/AnimationDialog.ui
RESOURCES = UI/AnimationDialog.qrc

###
###     Loki
###
INCLUDEPATH += ./Loki
DEPENDPATH += ./Loki
HEADERS += Loki/SingletonHolder.h

###
###     plugins
###
#DEPENDPATH += ./plugins
#SOURCES += plugins/Simple.C plugins/jack.C plugins/jill.C plugins/joe.C
#           plugins/john.C "plugins/slack complex.C" "plugins/slack polar.C"
#           plugins/slack.C plugins/slack3.C "plugins/something else.C"
#           plugins/something_else.C plugins/sqrabs.C "plugins/sqrsin polar.C"
#           plugins/sqrsin.C plugins/strange.C

###
###     Vector Algebra
###
INCLUDEPATH += ./VecMath
DEPENDPATH += ./VecMath
HEADERS += VecMath/Matrix.h \
           VecMath/NestedVector.h \
           VecMath/Rotation.h \
           VecMath/Vector.h \
           VecMath/uintvec.h
SOURCES += VecMath/Rotation.C

###
###     main directory
###
INCLUDEPATH += .
DEPENDPATH += .
HEADERS += Globals.h \
           Help.h \
           Log.h \
           Color.h \
           ColorManager.h \
           NotYetImplementedException.h \
           Light.h
SOURCES += Globals.C \
           Help.C \
           ColorManager.C \
           Light.C

###
################################################################################

INSTALLDIR = "/usr/local"
DEFINES += PREFIX="$${INSTALLDIR}"
DEFINES += PACKAGE_BUGREPORT="lene.preuss@gmail.com"
DEFINES += PACKAGE_VERSION="$${VERSION}"
DEFINES += USE_AUTO_PTR

CONFIG(debug){
    DEFINES += DEBUG TESTFEATURES DEBUG_ROTOPES
}

###
### turn profiling on in debug mode
###
QMAKE_CFLAGS_DEBUG += -pg -g3 -gdwarf-2
QMAKE_CXXFLAGS_DEBUF += -pg -g3 -gdwarf-2
QMAKE_LFLAGS_DEBUG += -pg
###
### installation
###
DESTDIR = ../lib
TARGET = HyperspaceExplorer

target.path = $${INSTALLDIR}/lib
vector.files = Vector.h
vector.path = $${INSTALLDIR}/share/HyperspaceExplorer/plugins
docs.files = doc/*
docs.path =  $${INSTALLDIR}/share/HyperspaceExplorer/doc
INSTALLS += target vector docs
DISTFILES += ../devel/footer.html ../TODO

###
### C++0x support
#QMAKE_CXXFLAGS += -std=c++0x