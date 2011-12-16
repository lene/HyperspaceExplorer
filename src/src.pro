TEMPLATE = lib

CONFIG -= debug
#CONFIG += release qt warn_on uic staticlib
CONFIG += debug qt warn_on uic dll staticlib

QT += opengl

VERSION = 0.7.1

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
###     Displayable
###
INCLUDEPATH += ./Displayable
DEPENDPATH += ./Displayable
HEADERS += \
           Displayable/Surface/Surface.h \
           Displayable/Surface/SurfaceImplementations.h \
           Displayable/Surface/ComplexFunction.h \
           Displayable/FunctionParameterValueBase.h \
           Displayable/FunctionParameterValue.h \
           Displayable/FunctionParameter.h \
           Displayable/FunctionParameterFactory.h \
           Displayable/ParameterMap.h \
           Displayable/Displayable.h \
           Displayable/DisplayableClass.h \
           Displayable/FunctionFactory.h \
           Displayable/Composite.h \
           Displayable/SimpleComposite.h \
           Displayable/DefinitionSpaceRange.h \
           Displayable/DefinitionRangeOfDimension.h \
           Displayable/DefinitionRangeOfDimension.impl.h \
           Displayable/FunctionHolder.h \
           Displayable/FunctionHolder.impl.h \
           Displayable/RealFunction.h \
           Displayable/RealFunctionImplementations.h \
           Displayable/CustomFunction.h \
           Displayable/ParametricFunction.h \
           Displayable/FunctionValueGrid.h \
           Displayable/LoopHelper.h \
           Displayable/Transformation.h \
           Displayable/Transformation.impl.h \
           Displayable/TransformationPolicy.h \
           Displayable/SimpleTransformationPolicy.h \
           Displayable/SimpleTransformationPolicy.impl.h \
           Displayable/MultithreadedTransformationPolicy.h \
           Displayable/MultithreadedTransformationPolicy.impl.h \
           Displayable/ViewpointList.h \
           Displayable/ViewpointList.impl.h \
           Displayable/Projection.h \
           Displayable/Projection.impl.h \
           Displayable/GridDrawer.h \
           Displayable/GridDrawer.impl.h \
           Displayable/Object.h \
           Displayable/Transform.h \
           Displayable/Sponge.h
#          Displayable/SteinerFunction.h
SOURCES += \
           Displayable/Surface/Surface.C \
           Displayable/Surface/SurfaceImplementations.cpp \
           Displayable/Surface/ComplexFunction.C \
           Displayable/FunctionParameterValue.C \
           Displayable/FunctionParameter.C \
           Displayable/ParameterMap.C \
           Displayable/Displayable.cpp \
           Displayable/DisplayableClass.cpp \
           Displayable/FunctionFactory.C \
           Displayable/Composite.cpp \
           Displayable/SimpleComposite.cpp \
           Displayable/DefinitionSpaceRange.cpp \
           Displayable/RealFunction.C \
           Displayable/RealFunctionImplementations.cpp \
           Displayable/CustomFunction.C \
           Displayable/Object.C \
           Displayable/Sponge.C
#          Displayable/SteinerFunction.C

###
###     Rotopes
###
INCLUDEPATH += ./Displayable/Rotopes
DEPENDPATH += ./Displayable/Rotopes
HEADERS += Displayable/Rotopes/Rotope.h \
           Displayable/Rotopes/RotopeFactory.h \
           Displayable/Rotopes/Projector.h \
           Displayable/Rotopes/RotopeInterface.h \
           Displayable/Rotopes/VertexData.h \
           Displayable/Rotopes/VertexDataPrinter.h \
           Displayable/Rotopes/Realm.h \
           Displayable/Rotopes/Extrude.h \
           Displayable/Rotopes/Taper.h \
           Displayable/Rotopes/Rotate.h \
           Displayable/Rotopes/Torate.h
SOURCES += Displayable/Rotopes/Rotope.C \
           Displayable/Rotopes/RotopeFactory.C \
           Displayable/Rotopes/RotopeInterface.C \
           Displayable/Rotopes/Realm.C \
           Displayable/Rotopes/RealmPrinter.C

###
###     LSystems
###
INCLUDEPATH += ./Displayable/LSystems
DEPENDPATH += ./Displayable/LSystems
HEADERS += \
           Displayable/LSystems/LSystem.h
SOURCES += \
           Displayable/LSystems/LSystem.cpp

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
           UI/ValuesDialog.h \
           UI/MouseHandler.h \
           UI/View.h \
           UI/ViewImpl.h \
           UI/ParameterInput.h \
           UI/RotationControl.h \
           UI/RotationSlider.h \
           UI/Help.h
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
           UI/RotationSlider.C \
           UI/Help.C
FORMS += UI/ComplexDialog.ui \
         UI/FunctionDialog.ui \
         UI/PolarDialog.ui \
         UI/SurfaceDialog.ui \
         UI/AnimationDialog.ui
RESOURCES = UI/AnimationDialog.qrc

###
###	Color
###
INCLUDEPATH += ./Color
DEPENDPATH += ./Color
HEADERS += \
	   Color/Color.h \
           Color/ColorManager.h \
           Color/Light.h
SOURCES += \
           Color/ColorManager.C \
           Color/Light.C

###
###     Utilities
###
INCLUDEPATH += ./Utilities
DEPENDPATH += ./Utilities
HEADERS += \
           Utilities/Globals.h \
           Utilities/Log.h \
           Utilities/NotYetImplementedException.h \
           Utilities/Observer.h \
           Utilities/Observer.impl.h  \
           Utilities/ScopedTimer.h  \
           Utilities/SingletonHolder.h \
           Utilities/Tree.h \
           Utilities/Tree.impl.h \
           Utilities/Util.h
SOURCES += \
           Utilities/Globals.C \
           Utilities/ScopedTimer.cpp \
           Utilities/Util.cpp

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
HEADERS += VecMath/ArrayList.h \
           VecMath/ArrayList.impl.h \
           VecMath/Matrix.h \
           VecMath/Matrix.impl.h \
           VecMath/MultiDimensionalVector.h \
           VecMath/MultiDimensionalVector.impl.h \
           VecMath/Rotation.h \
           VecMath/Vector.h
SOURCES += VecMath/Rotation.C

###
###     main directory
###
INCLUDEPATH += .
DEPENDPATH += .
HEADERS += \

###
################################################################################

INSTALLDIR = "/usr/local"
DEFINES += PREFIX="$${INSTALLDIR}"
DEFINES += PACKAGE_BUGREPORT="lene.preuss@gmail.com"
DEFINES += PACKAGE_VERSION="$${VERSION}"
DEFINES += USE_AUTO_PTR

CONFIG(debug){
    DEFINES += DEBUG TESTFEATURES
}

###
### turn profiling on in debug mode
###
QMAKE_CFLAGS_DEBUG += -pg -g3 -gdwarf-2
QMAKE_CXXFLAGS_DEBUG += -pg -g3 -gdwarf-2
QMAKE_LFLAGS_DEBUG += -pg

QMAKE_CXXFLAGS_RELEASE += -O2
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
QMAKE_CXXFLAGS += -std=c++0x
