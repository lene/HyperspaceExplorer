PATH = Displayable
INCLUDEPATH += $${PATH}
DEPENDPATH += $${PATH}
HEADERS += \
           $${PATH}/FunctionParameterValueBase.h \
           $${PATH}/FunctionParameterValue.h \
           $${PATH}/FunctionParameter.h \
           $${PATH}/FunctionParameterFactory.h \
           $${PATH}/ParameterMap.h \
           $${PATH}/Displayable.h \
           $${PATH}/DisplayableClass.h \
           $${PATH}/FunctionFactory.h \
           $${PATH}/Composite.h \
           $${PATH}/SimpleComposite.h \
           $${PATH}/DefinitionSpaceRange.h \
           $${PATH}/DefinitionRangeOfDimension.h \
           $${PATH}/DefinitionRangeOfDimension.impl.h \
           $${PATH}/VertexHolder.h \
           $${PATH}/VertexHolder.impl.h \
           $${PATH}/FunctionHolder.h \
           $${PATH}/FunctionHolder.impl.h \
           $${PATH}/RealFunction.h \
           $${PATH}/RealFunctionImplementations.h \
           $${PATH}/CustomFunction.h \
           $${PATH}/ParametricFunction.h \
           $${PATH}/VertexGrid.h \
           $${PATH}/FunctionValueGrid.h \
           $${PATH}/LoopHelper.h \
           $${PATH}/ViewpointList.h \
           $${PATH}/ViewpointList.impl.h \
           $${PATH}/GridDrawer.h \
           $${PATH}/GridDrawer.impl.h
#          $${PATH}/SteinerFunction.h
SOURCES += \
           $${PATH}/FunctionParameterValue.C \
           $${PATH}/FunctionParameter.C \
           $${PATH}/ParameterMap.C \
           $${PATH}/Displayable.cpp \
           $${PATH}/DisplayableClass.cpp \
           $${PATH}/FunctionFactory.C \
           $${PATH}/Composite.cpp \
           $${PATH}/SimpleComposite.cpp \
           $${PATH}/DefinitionSpaceRange.cpp \
           $${PATH}/DepthCueUtil.cpp \
           $${PATH}/RealFunction.C \
           $${PATH}/RealFunctionImplementations.cpp \
           $${PATH}/CustomFunction.C 
#          $${PATH}/SteinerFunction.C

################################################################################
###
###     subdirectories
###
include(Transformation/Transformation.pri)
include(Projection/Projection.pri)
include(Object/Object.pri)
include(Surface/Surface.pri)
include(Rotopes/Rotopes.pri)
include(LSystems/LSystems.pri)

