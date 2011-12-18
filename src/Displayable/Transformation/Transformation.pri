PATH = Displayable/Transformation
INCLUDEPATH += $${PATH}
DEPENDPATH += $${PATH}

HEADERS += \
           $${PATH}/Transformation.h \
           $${PATH}/Transformation.impl.h \
           $${PATH}/TransformationFactory.h \
           $${PATH}/TransformationFactory.impl.h \
           $${PATH}/TransformationPolicy.h \
           $${PATH}/SimpleTransformationPolicy.h \
           $${PATH}/SimpleTransformationPolicy.impl.h \
           $${PATH}/MultithreadedTransformationPolicy.h \
           $${PATH}/MultithreadedTransformationPolicy.impl.h
