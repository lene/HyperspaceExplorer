
//      project:      hyperspace explorer
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)
//
//	taken and adapted from:
//      project:      Extended QGLWidget
//      module:       PopupStuff.C
//      compile with: make all
//      contains:     member function declarations for the extended OpenGL widget
//                    and some useful auxiliary routines
//                    uses OpenGL (e.g. MesaGL) and the Qt OpenGL extension
//                    Menu, mouse event and keyboard accelerator declarations
//		      for XQGLWidget
//
//                    I wrote this module in 2000, maybe 2001, and never touched
//                    it since, because it Just Worked(TM) for me.
//                    Don't be surprised about some peculiarities. I have
//                    moved on since then.
//                    20080518: I'm working on getting rid of this module
//                    entirely, function by function. already weeded out over
//                    half of the code.
/*
#include <GL/glu.h>

#include <ctime>
#include <sstream>

#include <QDesktopWidget>
#include <QMouseEvent>
#include <QSlider>

#include "XQGLWidget.H"
#include "Log.H"
#include "Globals.H"
#include "Help.H"




/** XQGLWidget constructor; does a lot of initialization to (usually sensible)
 *  hardcoded default values, creates the menus and accelerators
 *  @param parent	parent QWidget, defaults to NULL
 *  @param name		name, defaulting to ""                                */
/*XQGLWidget::XQGLWidget (QWidget *parent) :
    QGLWidget (parent)
//
 {
    setMinimumSize (256, 256);                  //  hmm... shouldnt I find a more flexible way?
}


*/