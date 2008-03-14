TEMPLATE = app

CONFIG = release qt warn_on uic

QT += opengl qt3support

VERSION = 0.3.3

OBJECTS_DIR = tmp
MOC_DIR = tmp
UI_DIR = tmp
UI_HEADERS_DIR = tmp

################################################################################
###	subdirectories
###
###
###	Functions
###
INCLUDEPATH += ./Functions
DEPENDPATH += ./Functions
HEADERS += Functions/ComplexFunction.H Functions/CustomFunction.H \
	   Functions/Function.H Functions/Object.H Functions/Surface.H
#	   Functions/SteinerFunction.H
SOURCES += Functions/ComplexFunction.C Functions/CustomFunction.C \
	   Functions/Function.C Functions/Surface.C Functions/Object.C
#	   Functions/SteinerFunction.C

###
###	UI
###
INCLUDEPATH += ./UI
DEPENDPATH += ./UI
HEADERS += UI/4DView.H UI/ComplexDialogImpl.H UI/FunctionDialogImpl.H \
	   UI/PolarDialogImpl.H UI/SurfaceDialogImpl.H UI/ValuesDialogImpl.H \
	   UI/GLObject.H UI/XQGLWidget.H UI/Menu4D.H UI/PluginCreator.H
SOURCES += UI/4DView.C UI/Menu4D.C UI/ComplexDialogImpl.C \
	   UI/FunctionDialogImpl.C UI/PolarDialogImpl.C UI/SurfaceDialogImpl.C \
	   UI/ValuesDialogImpl.C UI/XQGLWidget.C UI/PluginCreator.C

FORMS += UI/ComplexDialog.ui UI/FunctionDialog.ui \
	 UI/PolarDialog.ui UI/SurfaceDialog.ui UI/ValuesDialog.ui

###
###	Loki
###
INCLUDEPATH += ./Loki
DEPENDPATH += ./Loki
HEADERS += Loki/SingletonHolder.H

###
###	plugins
###
#DEPENDPATH += ./plugins
#SOURCES += plugins/Simple.C plugins/jack.C plugins/jill.C plugins/joe.C
#           plugins/john.C "plugins/slack complex.C" "plugins/slack polar.C"
#           plugins/slack.C plugins/slack3.C "plugins/something else.C"
#           plugins/something_else.C plugins/sqrabs.C "plugins/sqrsin polar.C"
#           plugins/sqrsin.C plugins/strange.C

###
###	main directory
###
INCLUDEPATH += .
DEPENDPATH += .
HEADERS += Globals.H Help.H Matrix.H Vector.H Log.H 
SOURCES += Globals.C Help.C Main.C Log.C

###
################################################################################

DEFINES += PACKAGE_BUGREPORT
DEFINES += PACKAGE_VERSION
DEFINES += TESTFEATURES

DESTDIR = ../
TARGET = HyperspaceExplorer

target.path = /usr/local/bin
vector.files = Vector.H
vector.path = ~/.HyperspaceExplorer/plugins
INSTALLS += target
INSTALLS += vector
