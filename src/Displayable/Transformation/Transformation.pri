PATH = Displayable/Transformation
INCLUDEPATH += $${PATH}
DEPENDPATH += $${PATH}

HEADERS += $${PATH}/Transformation.h 
HEADERS += $${PATH}/Transformation.impl.h 
HEADERS += $${PATH}/SinglethreadedTransformation.h 
HEADERS += $${PATH}/SinglethreadedTransformation.impl.h 
HEADERS += $${PATH}/MultithreadedTransformation.h 
HEADERS += $${PATH}/MultithreadedTransformation.impl.h 
HEADERS += $${PATH}/TransformationFactory.h 
HEADERS += $${PATH}/TransformationFactory.impl.h 
HEADERS += $${PATH}/TransformationPolicy.h 
HEADERS += $${PATH}/MultithreadedTransformationPolicy.h 
HEADERS += $${PATH}/MultithreadedTransformationPolicy.impl.h

SOURCES += $${PATH}/TransformationFactory.cpp