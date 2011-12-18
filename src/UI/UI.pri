INCLUDEPATH += UI
DEPENDPATH += UI
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
