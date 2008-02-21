TEMPLATE = app
TEMPLATE += subdirs

CONFIG = debug qt warn_on uic ordered

QT += opengl qt3support

SUBDIRS = Functions

HEADERS += 4DView.H ComplexDialogImpl.H FunctionDialogImpl.H GLObject.H
HEADERS += Globals.H Help.H Matrix.H PolarDialogImpl.H SurfaceDialogImpl.H
HEADERS += ValuesDialogImpl.H XQGLWidget.H numclass.H

SOURCES += 4DMenu.C 4DView.C ComplexDialogImpl.C FunctionDialogImpl.C Globals.C
SOURCES += Help.C Main.C PolarDialogImpl.C PopupStuff.C SurfaceDialogImpl.C 
SOURCES += ValuesDialogImpl.C XQGLWidget.C numclass.C

FORMS += ComplexDialog.ui FunctionDialog.ui PolarDialog.ui SurfaceDialog.ui
FORMS += ValuesDialog.ui

DEFINES += PACKAGE_BUGREPORT
DEFINES += PACKAGE_VERSION

DESTDIR = ../
TARGET = HyperspaceExplorer
