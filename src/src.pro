TEMPLATE = app

#CONFIG -= debug
#CONFIG += release qt warn_on uic
CONFIG += debug qt warn_on uic

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
HEADERS += Functions/ComplexFunction.H Functions/CustomFunction.H \
           Functions/Function.H Functions/Object.H Functions/Surface.H \
           Functions/RealFunction.H  Functions/FunctionParameter.H \
           Functions/ParameterMap.H Functions/FunctionFactory.H
#          Functions/SteinerFunction.H
SOURCES += Functions/ComplexFunction.C Functions/CustomFunction.C \
           Functions/Function.C Functions/Surface.C Functions/Object.C \
           Functions/RealFunction.C  Functions/FunctionParameter.C \
           Functions/FunctionFactory.C
#          Functions/SteinerFunction.C

###
###     Rotopes
###
INCLUDEPATH += ./Functions/Rotopes
DEPENDPATH += ./Functions/Rotopes
HEADERS += Functions/Rotopes/Rotope.H Functions/Rotopes/RotopeFactory.H \
           Functions/Rotopes/Projector.H Functions/Rotopes/RotopeBase.H \
           Functions/Rotopes/VertexData.H Functions/Rotopes/Realm.H \
           Functions/Rotopes/Extrude.H Functions/Rotopes/Taper.H \
           Functions/Rotopes/Rotate.H Functions/Rotopes/Torate.H
SOURCES += Functions/Rotopes/Rotope.C Functions/Rotopes/RotopeFactory.C \
           Functions/Rotopes/Realm.C

###
###     Script
###
INCLUDEPATH += ./Script
DEPENDPATH += ./Script
HEADERS += Script/Parser.H Script/Statement.H
SOURCES += Script/Parser.C Script/Statement.C

###
###     UI
###
INCLUDEPATH += ./UI
DEPENDPATH += ./UI
HEADERS += UI/4DView.H UI/ComplexDialogImpl.H UI/FunctionDialogImpl.H \
           UI/PolarDialogImpl.H UI/SurfaceDialogImpl.H UI/ValuesDialogImpl.H \
           UI/Menu4D.H UI/PluginCreator.H \
           UI/AnimationDialogImpl.H UI/SlotHelper.H UI/CustomFunctionSlot.impl.H \
           UI/TemplatedFunctionFactory.impl.H  UI/ValuesDialog.H \
           UI/MouseHandler.H UI/View.H UI/ViewImpl.H UI/ParameterInput.H \
           UI/RotationControl.H UI/RotationSlider.H
SOURCES += UI/4DView.C UI/Menu4D.C UI/ComplexDialogImpl.C \
           UI/FunctionDialogImpl.C UI/PolarDialogImpl.C UI/SurfaceDialogImpl.C \
           UI/ValuesDialogImpl.C UI/PluginCreator.C \
           UI/AnimationDialogImpl.C UI/SlotHelper.C \
           UI/MouseHandler.C UI/ViewImpl.C UI/ParameterInput.C \
           UI/RotationControl.C UI/RotationSlider.C
FORMS += UI/ComplexDialog.ui UI/FunctionDialog.ui \
         UI/PolarDialog.ui UI/SurfaceDialog.ui UI/AnimationDialog.ui
RESOURCES = UI/AnimationDialog.qrc

###
###     Loki
###
INCLUDEPATH += ./Loki
DEPENDPATH += ./Loki
HEADERS += Loki/SingletonHolder.H

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
HEADERS += VecMath/Matrix.H VecMath/NestedVector.H VecMath/Rotation.H \
           VecMath/Vector.H  VecMath/uintvec.H
SOURCES += VecMath/Rotation.C

###
###     main directory
###
INCLUDEPATH += .
DEPENDPATH += .
HEADERS += Globals.H Help.H Log.H Color.H ColorManager.H NotYetImplementedException.H \
           Light.H
SOURCES += Globals.C Help.C Main.C ColorManager.C Light.C

###
################################################################################

INSTALLDIR = "/usr/local"
DEFINES += PREFIX="$${INSTALLDIR}"
DEFINES += PACKAGE_BUGREPORT="scout@hyperspace-travel.de"
DEFINES += PACKAGE_VERSION="$${VERSION}"
DEFINES += USE_AUTO_PTR

CONFIG(debug){
    DEFINES += DEBUG TESTFEATURES DEBUG_ROTOPES
}

###
### turn profiling on in debug mode
###
QMAKE_CFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

###
### installation
###
DESTDIR = ../
TARGET = HyperspaceExplorer

target.path = $${INSTALLDIR}/bin
vector.files = Vector.H
vector.path = $${INSTALLDIR}/share/HyperspaceExplorer/plugins
docs.files = doc/*
docs.path =  $${INSTALLDIR}/share/HyperspaceExplorer/doc
INSTALLS += target vector docs
DISTFILES += ../devel/footer.html ../TODO

