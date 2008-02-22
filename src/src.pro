TEMPLATE = app

CONFIG = debug qt warn_on uic

QT += opengl qt3support

HEADERS += 4DView.H ComplexDialogImpl.H 
HEADERS += FunctionDialogImpl.H GLObject.H Globals.H Help.H Matrix.H
HEADERS += PolarDialogImpl.H 
HEADERS += SurfaceDialogImpl.H ValuesDialogImpl.H XQGLWidget.H numclass.H \
 Log.H 

SOURCES += 4DMenu.C 4DView.C ComplexDialogImpl.C 
SOURCES += FunctionDialogImpl.C Globals.C Help.C
SOURCES += Main.C PolarDialogImpl.C PopupStuff.C 
SOURCES += SurfaceDialogImpl.C ValuesDialogImpl.C XQGLWidget.C
SOURCES += numclass.C Log.C

FORMS += ComplexDialog.ui FunctionDialog.ui PolarDialog.ui SurfaceDialog.ui
FORMS += ValuesDialog.ui

################################################################################
###	subdirectories
###

###	Functions

INCLUDEPATH += Functions
DEPENDPATH += Functions
HEADERS += Functions/ComplexFunction.H Functions/CustomFunction.H \
	   Functions/Function.H Functions/Object.H Functions/Surface.H 
#	   Functions/SteinerFunction.H
SOURCES += Functions/ComplexFunction.C Functions/CustomFunction.C \
	   Functions/Function.C Functions/Surface.C Functions/Object.C
#	   Functions/SteinerFunction.C

###	Loki

INCLUDEPATH += Loki
DEPENDPATH += Loki
HEADERS += Loki/SingletonHolder.H

################################################################################

DEFINES += PACKAGE_BUGREPORT
DEFINES += PACKAGE_VERSION

DESTDIR = ../
TARGET = HyperspaceExplorer
