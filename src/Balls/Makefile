#
INCDIR = 
CFLAGS = -Wall -Wno-sign-compare -ffast-math -march=k6-2 -O6 #0 -g
LFLAGS = -lqt-mt
GLFLAGS = -lGL -lGLU
CC = g++-3.2 -ansi -pedantic
MOC = moc

########  files

UI	=  BallsUI.ui
UIHDR	=  BallsUI.H
UISRC	=  BallsUI.C
UIOBJ	=  BallsUI.o
UIMETA  = mBallsUI.C
UIMOBJ  = mBallsUI.o

IMPLHDR	=  BallsUIImpl.H
IMPLSRC	=  BallsUIImpl.C
IMPLOBJ	=  BallsUIImpl.o
IMPLMETA= mBallsUIImpl.C
IMPLMOBJ= mBallsUIImpl.o

HEADERS =  VecTemplate.H Ball.H Box.H BoxWidget.H
SOURCES =  Ball.C Box.C BoxWidget.C Balls.C  $(IMPLSRC)
OBJECTS =  Ball.o Box.o BoxWidget.o Balls.o $(UIOBJ) $(IMPLOBJ)
SRCMETA = mBoxWidget.C $(UIMETA) $(IMPLMETA) 
OBJMETA = mBoxWidget.o $(UIMOBJ) $(IMPLMOBJ)
TARGET  =  Balls

########  implicit rules

#	clear suffixes list
.SUFFIXES: 

#	define suffixes list
.SUFFIXES: .H .C .ui .o

.ui.H:;	uic -o $@ $<

.ui.C:; uic -o $@ -impl $*.H $<

.C.o: 
	$(CC) $(INCDIR) -c $(CFLAGS) $<

########  build rules

all: $(TARGET)
#	./$(TARGET)

profile: $(TARGET)
	./$(TARGET) --tmax 10
	gprof $(TARGET) gmon.out | less

clean:
	rm -f *~ core

clobber: clean
	rm -f $(OBJECTS) $(OBJMETA) $(SRCMETA) $(UIHDR) $(UISRC)

$(TARGET): $(UIHDR) $(UISRC) $(OBJECTS) $(OBJMETA)
	$(CC) $(OBJECTS) $(OBJMETA) -o $(TARGET) $(LFLAGS) $(GLFLAGS)
debug:	clobber
	CFLAGS=-g
	all

########  metaclasses

mBoxWidget.C: BoxWidget.H
	$(MOC) -o $@ BoxWidget.H
mBallsUI.C: BallsUI.H
	$(MOC) -o $@ BallsUI.H
mBallsUIImpl.C: BallsUIImpl.H
	$(MOC) -o $@ BallsUIImpl.H
