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
###	Dialogs
###
INCLUDEPATH += ./Dialogs
DEPENDPATH += ./Dialogs
HEADERS += Dialogs/ComplexDialogImpl.H Dialogs/FunctionDialogImpl.H \
	   Dialogs/PolarDialogImpl.H Dialogs/SurfaceDialogImpl.H \
	   Dialogs/ValuesDialogImpl.H
SOURCES += Dialogs/ComplexDialogImpl.C Dialogs/FunctionDialogImpl.C \
	   Dialogs/PolarDialogImpl.C Dialogs/SurfaceDialogImpl.C \
	   Dialogs/ValuesDialogImpl.C
FORMS += Dialogs/ComplexDialog.ui Dialogs/FunctionDialog.ui \
	 Dialogs/PolarDialog.ui Dialogs/SurfaceDialog.ui Dialogs/ValuesDialog.ui
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
HEADERS += 4DView.H GLObject.H Globals.H Help.H Matrix.H XQGLWidget.H \
	   numclass.H Log.H 
SOURCES += 4DMenu.C 4DView.C Globals.C Help.C Main.C  PopupStuff.C \
	   XQGLWidget.C numclass.C Log.C
###
################################################################################

DEFINES += PACKAGE_BUGREPORT
DEFINES += PACKAGE_VERSION

DESTDIR = ../
TARGET = HyperspaceExplorer
