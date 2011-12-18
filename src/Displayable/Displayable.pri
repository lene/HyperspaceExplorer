INCLUDEPATH += Displayable
DEPENDPATH += Displayable
HEADERS += \
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
           Displayable/ViewpointList.h \
           Displayable/ViewpointList.impl.h \
           Displayable/Projection.h \
           Displayable/Projection.impl.h \
           Displayable/GridDrawer.h \
           Displayable/GridDrawer.impl.h
#          Displayable/SteinerFunction.h
SOURCES += \
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
           Displayable/CustomFunction.C 
#          Displayable/SteinerFunction.C

################################################################################
###
###     subdirectories
###
include(Transformation/Transformation.pri)
include(Object/Object.pri)
include(Surface/Surface.pri)
include(Rotopes/Rotopes.pri)
include(LSystems/LSystems.pri)

