TEMPLATE = app

CONFIG = debug qt warn_on uic

QT += opengl

VERSION = 0.3.3

###
###     move all temporary files out of sight into subdirectory tmp
###
system(mkdir -p tmp)
OBJECTS_DIR = tmp
MOC_DIR = tmp
UI_DIR = tmp
UI_HEADERS_DIR = tmp

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
           Functions/ParameterMap.H
#          Functions/SteinerFunction.H
SOURCES += Functions/ComplexFunction.C Functions/CustomFunction.C \
           Functions/Function.C Functions/Surface.C Functions/Object.C \
           Functions/RealFunction.C  Functions/FunctionParameter.C
#          Functions/SteinerFunction.C

###
###     UI
###
INCLUDEPATH += ./UI
DEPENDPATH += ./UI
HEADERS += UI/4DView.H UI/ComplexDialogImpl.H UI/FunctionDialogImpl.H \
           UI/PolarDialogImpl.H UI/SurfaceDialogImpl.H UI/ValuesDialogImpl.H \
           UI/Menu4D.H UI/PluginCreator.H \
           UI/AnimationDialogImpl.H UI/SlotHelper.H UI/CustomFunctionSlot.impl.H \
           UI/TemplatedFunctionFactory.impl.H  UI/ValuesDialog.H
SOURCES += UI/4DView.C UI/Menu4D.C UI/ComplexDialogImpl.C \
           UI/FunctionDialogImpl.C UI/PolarDialogImpl.C UI/SurfaceDialogImpl.C \
           UI/ValuesDialogImpl.C UI/PluginCreator.C \
           UI/AnimationDialogImpl.C UI/SlotHelper.C

FORMS += UI/ComplexDialog.ui UI/FunctionDialog.ui \
         UI/PolarDialog.ui UI/SurfaceDialog.ui UI/AnimationDialog.ui

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
###     main directory
###
INCLUDEPATH += .
DEPENDPATH += .
HEADERS += Globals.H Help.H Matrix.H Vector.H Log.H Color.H ColorManager.H
SOURCES += Globals.C Help.C Main.C ColorManager.C

###
################################################################################

INSTALLDIR = "/usr/local"
DEFINES += PREFIX="$${INSTALLDIR}"
DEFINES += PACKAGE_BUGREPORT="helge.preuss@gmx.net"
DEFINES += PACKAGE_VERSION="$${VERSION}"
DEFINES += USE_AUTO_PTR

CONFIG(debug){
    DEFINES += DEBUG TESTFEATURES
}

DESTDIR = ../
TARGET = HyperspaceExplorer

target.path = $${INSTALLDIR}/bin
vector.files = Vector.H
vector.path = $${INSTALLDIR}/share/HyperspaceExplorer/plugins
doc.files = doc
doc.path =  $${INSTALLDIR}/share/HyperspaceExplorer
INSTALLS += target vector doc
