TEMPLATE = lib

CONFIG = debug qt warn_on uic

QT += opengl qt3support

HEADERS += ComplexFunction.H CustomFunction.H Function.H Object.H  Surface.H 
# SteinerFunction.H
SOURCES += ComplexFunction.C CustomFunction.C Function.C Object.C  Surface.C 
# SteinerFunction.C