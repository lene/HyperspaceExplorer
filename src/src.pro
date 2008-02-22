TEMPLATE = app

CONFIG = debug qt warn_on uic

QT += opengl qt3support

HEADERS += 4DView.H ComplexDialogImpl.H ComplexFunction.H CustomFunction.H
HEADERS += Function.H FunctionDialogImpl.H GLObject.H Globals.H Help.H Matrix.H
HEADERS += Object.H PolarDialogImpl.H Surface.H # SteinerFunction.H
HEADERS += SurfaceDialogImpl.H ValuesDialogImpl.H XQGLWidget.H numclass.H \
 Log.H 

SOURCES += 4DMenu.C 4DView.C ComplexDialogImpl.C ComplexFunction.C
SOURCES += CustomFunction.C Function.C FunctionDialogImpl.C Globals.C Help.C
SOURCES += Main.C Object.C PolarDialogImpl.C PopupStuff.C # SteinerFunction.C
SOURCES += Surface.C SurfaceDialogImpl.C ValuesDialogImpl.C XQGLWidget.C
SOURCES += numclass.C Log.C

FORMS += ComplexDialog.ui FunctionDialog.ui PolarDialog.ui SurfaceDialog.ui
FORMS += ValuesDialog.ui

################################################################################
###	subdirectories
###

###	Loki

INCLUDEPATH += Loki
DEPENDPATH += Loki
HEADERS += Loki/SingletonHolder.H

################################################################################

DEFINES += PACKAGE_BUGREPORT
DEFINES += PACKAGE_VERSION

DESTDIR = ../
TARGET = HyperspaceExplorer
