bin_PROGRAMS = HyperspaceExplorer
DIST_SUBDIRS = Documentation

%.moc.C: %.H
	$(MOC) -o $@ $<

%.H: %.ui
	$(UIC) -o $@ $<

%.C: %.ui
	$(UIC) -o $@ -impl $*.H $<

HyperspaceExplorer_UISRC =                		 \
	ValuesDialog.ui SurfaceDialog.ui  		 \
	ComplexDialog.ui FunctionDialog.ui PolarDialog.ui

HyperspaceExplorer_SRC =                				 \
	4DView.C 4DMenu.C XQGLWidget.C PopupStuff.C Help.C 		 \
	Globals.C numclass.C 					 \
	Function.C Surface.C ComplexFunction.C Object.C CustomFunction.C \
	Main.C

HyperspaceExplorer_IMPL_HDRS = ValuesDialogImpl.H FunctionDialogImpl.H  \
	SurfaceDialogImpl.H ComplexDialogImpl.H PolarDialogImpl.H

HyperspaceExplorer_HDRS = 4DView.H XQGLWidget.H GLObject.H Help.H	\
	Globals.H numclass.H Matrix.H					\
	Function.H Surface.H ComplexFunction.H Object.H CustomFunction.H

HyperspaceExplorer_IMPL = 					   \
        ValuesDialogImpl.C SurfaceDialogImpl.C ComplexDialogImpl.C \
        FunctionDialogImpl.C PolarDialogImpl.C

HyperspaceExplorer_UI =                   \
	ValuesDialog.H ValuesDialog.C	  \
	SurfaceDialog.H SurfaceDialog.C   \
	ComplexDialog.H ComplexDialog.C   \
	FunctionDialog.H FunctionDialog.C \
	PolarDialog.H PolarDialog.C

ValuesDialog.H: ValuesDialog.ui
ValuesDialog.C: ValuesDialog.ui ValuesDialog.H
SurfaceDialog.H: SurfaceDialog.ui
SurfaceDialog.C: SurfaceDialog.ui SurfaceDialog.H
ComplexDialog.H: ComplexDialog.ui
ComplexDialog.C: ComplexDialog.ui ComplexDialog.H
FunctionDialog.H: FunctionDialog.ui
FunctionDialog.C: FunctionDialog.ui FunctionDialog.H
PolarDialog.H: PolarDialog.ui
PolarDialog.C: PolarDialog.ui PolarDialog.H

ValuesDialogImpl.C:  ValuesDialogImpl.H
SurfaceDialogImpl.C: SurfaceDialogImpl.H
ComplexDialogImpl.C: ComplexDialogImpl.H
FunctionDialogImpl.C: FunctionDialogImpl.H
PolarDialogImpl.C: PolarDialogImpl.H

HyperspaceExplorer_MOC =                              \
        ValuesDialog.moc.C ValuesDialogImpl.moc.C     \
        SurfaceDialog.moc.C SurfaceDialogImpl.moc.C   \
        ComplexDialog.moc.C ComplexDialogImpl.moc.C   \
        FunctionDialog.moc.C FunctionDialogImpl.moc.C \
        PolarDialog.moc.C PolarDialogImpl.moc.C       \
	4DView.moc.C XQGLWidget.moc.C Help.moc.C

BUILT_SOURCES = $(HyperspaceExplorer_MOC) $(HyperspaceExplorer_UI)

HyperspaceExplorer_SOURCES = 						 \
	4DView.C 4DMenu.C XQGLWidget.C PopupStuff.C Help.C 		 \
	Globals.C numclass.C 					 \
	Function.C Surface.C ComplexFunction.C Object.C CustomFunction.C \
	Main.C 								 \
	$(HyperspaceExplorer_IMPL) 					 \
	$(HyperspaceExplorer_UISRC) 					 \
	$(HyperspaceExplorer_HDRS) 					 \
	$(HyperspaceExplorer_IMPL_HDRS) 				 \
	$(BUILT_SOURCES)

CLEANFILES = $(HyperspaceExplorer_MOC) $(HyperspaceExplorer_UI)
EXTRA_DIST = Documentation

HyperspaceExplorer_LDADD = $(QT_GUILINK) $(QT_LDADD) $(EXTRA_LDADD)

AM_CXXFLAGS := $(CXXFLAGS) $(EXTRA_CXXFLAGS) -I../include $(QT_CXXFLAGS) \
		-ansi -Wall -ffast-math

# a kludge to keep the uic- and moc-generated files out of the distribution
# this builds them first and then deletes them again, but i can't figure out
# how to do this correctly with automake
dist-hook:
	cd $(distdir); rm -f $(BUILT_SOURCES)

# 
install-data-local:
	 $(INSTALL_DATA) numclass.o $(bindir)/numclass.o
	 $(INSTALL_DATA) numclass.H $(bindir)/numclass.H
	 cp -r $(DIST_SUBDIRS) $(bindir)

uninstall-local:
	 rm -rf $(bindir)/numclass.o $(bindir)/numclass.H $(bindir)/$(DIST_SUBDIRS)
