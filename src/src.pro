TEMPLATE = app

CONFIG = debug qt warn_on uic

QT += opengl qt3support

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
	   UI/GLObject.H UI/XQGLWidget.H UI/Menu4D.H
SOURCES += UI/4DView.C UI/4DMenu.C UI/ComplexDialogImpl.C \
	   UI/FunctionDialogImpl.C UI/PolarDialogImpl.C UI/SurfaceDialogImpl.C \
	   UI/ValuesDialogImpl.C UI/XQGLWidget.C UI/Menu4D.C

FORMS += UI/ComplexDialog.ui UI/FunctionDialog.ui \
	 UI/PolarDialog.ui UI/SurfaceDialog.ui UI/ValuesDialog.ui
###
###	Loki
###
INCLUDEPATH += ./Loki
DEPENDPATH += ./Loki
HEADERS += Loki/SingletonHolder.H
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

DESTDIR = ../
TARGET = HyperspaceExplorer
