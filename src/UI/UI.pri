PATH = UI
INCLUDEPATH += $${PATH}
DEPENDPATH += $${PATH}
HEADERS += $${PATH}/4DView.h \
           $${PATH}/ComplexDialogImpl.h \
           $${PATH}/FunctionDialogImpl.h \
           $${PATH}/PolarDialogImpl.h \
           $${PATH}/SurfaceDialogImpl.h \
           $${PATH}/ValuesDialogImpl.h \
           $${PATH}/Menu4D.h \
           $${PATH}/PluginCreator.h \
           $${PATH}/AnimationDialogImpl.h \
           $${PATH}/SlotHelper.h \
           $${PATH}/CustomFunctionSlot.impl.h \
           $${PATH}/ValuesDialog.h \
           $${PATH}/MouseHandler.h \
           $${PATH}/View.h \
           $${PATH}/ViewImpl.h \
           $${PATH}/ParameterInput.h \
           $${PATH}/RotationControl.h \
           $${PATH}/RotationSlider.h \
           $${PATH}/Help.h
SOURCES += $${PATH}/4DView.C \
           $${PATH}/Menu4D.C \
           $${PATH}/ComplexDialogImpl.C \
           $${PATH}/FunctionDialogImpl.C \
           $${PATH}/PolarDialogImpl.C \
           $${PATH}/SurfaceDialogImpl.C \
           $${PATH}/ValuesDialogImpl.C \
           $${PATH}/PluginCreator.C \
           $${PATH}/AnimationDialogImpl.C \
           $${PATH}/SlotHelper.C \
           $${PATH}/MouseHandler.C \
           $${PATH}/ViewImpl.C \
           $${PATH}/ParameterInput.C \
           $${PATH}/RotationControl.C \
           $${PATH}/RotationSlider.C \
           $${PATH}/Help.C
FORMS += $${PATH}/ComplexDialog.ui \
         $${PATH}/FunctionDialog.ui \
         $${PATH}/PolarDialog.ui \
         $${PATH}/SurfaceDialog.ui \
         $${PATH}/AnimationDialog.ui
RESOURCES = $${PATH}/AnimationDialog.qrc
