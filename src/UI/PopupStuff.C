
//      project:      hyperspace explorer
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)
//
//	taken and adapted from:
//      project:      Extended QGLWidget
//      module:       PopupStuff.C
//      compile with: make all
//      contains:     Menu, mouse event and keyboard accelerator declarations
//		      for XQGLWidget


#include <qapplication.h>
#include <q3popupmenu.h>
#include <q3accel.h>
#include <qslider.h>
#include <qmessagebox.h>
//Added by qt3to4:
#include <QMouseEvent>

#include "Vector.H"

#include "XQGLWidget.H"
#include "Help.H"

using std::cerr;

////////////////////////////////////////////////////////////////////////////////
//
//	XQGLWidget menu handling
//
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  create the menu 
 *  @return		the menu
 */
Q3PopupMenu *XQGLWidget::SetupMenu (void) {
  menu   = new Q3PopupMenu;
  appear = new Q3PopupMenu;
  help   = new Q3PopupMenu;
  
  colorsID     = appear->insertItem ("Colors",       this, SLOT(Colors ()));
  shadeID      = appear->insertItem ("Shading",      this, SLOT(Shade()));
  fogID        = appear->insertItem ("Depth Cue",    this, SLOT(Fog()));
  transparentID= appear->insertItem ("Transparence", this, SLOT(Transparent()));
  lightID      = appear->insertItem ("Lighting",     this, SLOT(Light()));
   
  appear->setCheckable (true);

  appear->setItemChecked (colorsID, colors);
  appear->setItemChecked (shadeID, shade);
  appear->setItemChecked (fogID, fog);
  appear->setItemChecked (lightID, light); 
  appear->setItemChecked (transparentID, transparent);

  help->insertItem ("Online help",       this, SLOT(Help ()));
  help->insertSeparator ();
  help->insertItem( QObject::tr("&About ..."), this, SLOT( about() ) );
  help->insertItem( QObject::tr("About &Qt ..."), this, SLOT( aboutQt() ) );

  menu->insertItem ("Appearance", appear); 
  //    menu->insertItem ("Rotate",     this, SLOT(Rotate()));
  menu->insertItem ("Help", help); 
  menu->insertSeparator ();
  menu->insertItem ("Quit",       qApp, SLOT(quit ()));

  return menu; }


/*******************************************************************************
 *  menu callback functions
 */
//  top level menu


/*******************************************************************************
 *  obsolete function to rotate display by 360 degrees, 3 degrees at a time,
 *  without ability to interrupt
 */
void XQGLWidget::Rotate () {
  double theta_ = theta;
  for (double i = 0.; i < 360.; i += 3.) {
    theta = theta_+i;
    repaint (); }
  theta = theta_; }

/*******************************************************************************
 *  display help window (using HARDCODED paths and filenames, YUCK!)
 */
void XQGLWidget::Help () {
  static HelpWindow *H;
  H = new HelpWindow ("Hyperspace_Explorer_Help.html",
		      qApp->applicationDirPath ());
  //    H->setCaption("Qt Example - Helpviewer");		//  huh?
  H->show();

}


//  appearance menu


/*******************************************************************************
 *  toggle lighting
 */
void XQGLWidget::Light () {
  light = !light;
  appear->setItemChecked (lightID, light);
  InitLight ();
  repaint (); }


/*******************************************************************************
 *  toggle fog/depth cue
 */
void XQGLWidget::Fog () {
  fog = !fog;
  appear->setItemChecked (fogID, fog);
  InitFog ();
  repaint (); }


/*******************************************************************************
 *  toggle object transparency
 */
void XQGLWidget::Transparent () {
  transparent = !transparent;
  appear->setItemChecked (transparentID, transparent);
  InitTransparence ();
  repaint (); }


/*******************************************************************************
 *  toggle shading
 */
void XQGLWidget::Shade () {
  shade = !shade;
  appear->setItemChecked (shadeID, shade);
  InitShade ();
  repaint (); }


/*******************************************************************************
 *  toggle colors
 */
void XQGLWidget::Colors () {
  colors = !colors;
  appear->setItemChecked (colorsID, colors);
  initializeGL ();
  repaint (); }


////////////////////////////////////////////////////////////////////////////////
//
//	XQGLWidget mouse handling
//
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  mouse press event handler; cares for popping up the menu (RMB), rotating (LMB)
 *  and zooming (MMB)
 *  @param e	Qt's mouse event information structure
 */
void XQGLWidget::mousePressEvent (QMouseEvent *E) {
#ifdef DEBUG
  cerr << "XQGLWidget::mousePressEvent ()\n";
#endif
  int ButtonPressed = E->button ();
  if (ButtonPressed == Qt::RightButton) {
#   if (QT_VERSION < 300)
      menu->exec (QCursor::pos ());
#   else
      menu->exec (this->mapToGlobal(E->pos()));
#ifdef DEBUG
      cerr << "  ButtonPressed == Qt::RightButton\n";
#endif
#   endif
  }
  else if (ButtonPressed == Qt::LeftButton) {
    xpressed = E->x (); ypressed = E->y (); }
  else if (ButtonPressed == Qt::MidButton) {
    if (E->state () && Qt::ShiftButton) ViewPos (R+1);
    else                            // ViewPos (R-1); }
      ypressed = E->y (); } }


/*******************************************************************************
 *  mouse release event handler; cares for executing the action associated with
 *  the mouse button
 *  uses HARDCODED values for zooming!
 *  @param e	Qt's mouse event information structure
 */
void XQGLWidget::mouseReleaseEvent (QMouseEvent *E) { 
  int ButtonPressed = E->button ();
  if (ButtonPressed == Qt::LeftButton) {
    int dx = E->x () - xpressed, dy = E->y () -ypressed,
      dtheta = dx*90/width (), dpsi   = dy*90/height ();
    theta += dtheta; psi += dpsi;
    repaint (); } 
  if (ButtonPressed == Qt::MidButton) {
    double dr = double (E->y ()-ypressed)/height ()*5.;   //  the 5 may have to be reviewed
    if (dr) ViewPos (R*pow (1.25, dr));                   //  exponential change (1.25 also)
    else if (!(E->state () && Qt::ShiftButton))
      ViewPos (R/1.25);
    //    cerr << "dr = " << dr << " R = " <<R << endl;
  }
}


/*******************************************************************************
 *  mouse move event handler; empty, included out of anality or something
 */
void XQGLWidget::mouseMoveEvent (QMouseEvent *) { }


////////////////////////////////////////////////////////////////////////////////
//
//	XQGLWidget keyboard accelerators
//
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  create keyboard accelerators
 */
void XQGLWidget::SetupAccel (void) {
  static Q3Accel *accel;
  accel = new Q3Accel (this);

  accel->connectItem (accel->insertItem (Qt::Key_Left),  this, SLOT (Left ()));
  accel->connectItem (accel->insertItem (Qt::Key_Right), this, SLOT (Right ()));
  accel->connectItem (accel->insertItem (Qt::Key_Up),    this, SLOT (Up ()));
  accel->connectItem (accel->insertItem (Qt::Key_Down),  this, SLOT (Down ())); 

  accel->connectItem (accel->insertItem (Qt::Key_Left+Qt::SHIFT),  this, SLOT (SLeft ()));
  accel->connectItem (accel->insertItem (Qt::Key_Right+Qt::SHIFT), this, SLOT (SRight ()));
  accel->connectItem (accel->insertItem (Qt::Key_Up+Qt::SHIFT),    this, SLOT (SUp ())); 
  accel->connectItem (accel->insertItem (Qt::Key_Down+Qt::SHIFT),  this, SLOT (SDown ()));

  accel->connectItem (accel->insertItem (Qt::Key_Left+Qt::ALT+Qt::CTRL),  this, SLOT (CALeft ()));
  accel->connectItem (accel->insertItem (Qt::Key_Right+Qt::ALT+Qt::CTRL), this, SLOT (CARight ()));
  accel->connectItem (accel->insertItem (Qt::Key_Up+Qt::ALT+Qt::CTRL),    this, SLOT (CAUp ())); 
  accel->connectItem (accel->insertItem (Qt::Key_Down+Qt::ALT+Qt::CTRL),  this, SLOT (CADown ())); 
 
  accel->connectItem (accel->insertItem (Qt::Key_A), this, SLOT (A ())); 

  accel->connectItem (accel->insertItem (Qt::Key_Q+Qt::CTRL), qApp, SLOT (quit ())); }
 

/*******************************************************************************
 *  "Left" key: rotate 5 degrees left
 */
void XQGLWidget::Left () {
  theta -= 5; repaint (); }
 
/*******************************************************************************
 *  "Right" key: rotate 5 degrees right
 */
void XQGLWidget::Right () {
  theta += 5; repaint (); }
 
/*******************************************************************************
 *  "Up" key: rotate 5 degrees up
 */
void XQGLWidget::Up () {
  psi -= 5; repaint (); } 

/*******************************************************************************
 *  "Down" key: rotate 5 degrees down
 */
void XQGLWidget::Down () {
  psi += 5; repaint (); }


/*******************************************************************************
 *  Shift-"Left" key: rotate 45 degrees left
 */
void XQGLWidget::SLeft () {
  theta -= 45; repaint (); }

/*******************************************************************************
 *  Shift-"Right" key: rotate 45 degrees left
 */
void XQGLWidget::SRight () {
  theta += 45; repaint (); }

/*******************************************************************************
 *  Shift-"Up" key: rotate 45 degrees left
 */
void XQGLWidget::SUp () {
  psi -= 45; repaint (); }

/*******************************************************************************
 *  Shift-"Down" key: rotate 45 degrees left
 */
void XQGLWidget::SDown () {
  psi += 45; repaint (); }

 
/*******************************************************************************
 *  Ctrl-Alt-"Left" key: rotate 1 degrees left
 */
void XQGLWidget::CALeft () {
  theta -= 1; repaint (); }
 
/*******************************************************************************
 *  Ctrl-Alt-"Right" key: rotate 1 degrees left
 */
void XQGLWidget::CARight () {
  theta += 1; repaint (); }
 
/*******************************************************************************
 *  Ctrl-Alt-"Up" key: rotate 1 degrees left
 */
void XQGLWidget::CAUp () {
  psi -= 1; repaint (); } 

/*******************************************************************************
 *  Ctrl-Alt-"Down" key: rotate 1 degrees left
 */
void XQGLWidget::CADown () {
  psi += 1; repaint (); }


/*******************************************************************************
 *  "A" key: should open a slider to adjust alpha value. not yet implemented
 *  correctly.
 */
void XQGLWidget::A () { 
  QSlider *GetAlpha = new QSlider    (0  , 255,  64, int (Alpha*255),
				      Qt::Horizontal, this);
  GetAlpha->setTickInterval (16);
  GetAlpha->setFixedSize (200, 20);
  GetAlpha->show ();
  
  connect (GetAlpha, SIGNAL(valueChanged(int)), this, SLOT(SetAlpha(int))); }


/*******************************************************************************
 *  no function
 */
void XQGLWidget::Plus () {
}

/*******************************************************************************
 *  no function
 */
void XQGLWidget::Minus () {
}


/*******************************************************************************
 *  open an "About"-Dialog
 */
void XQGLWidget::about()
{
  QMessageBox::about( this, "Hyperspace Explorer",
		      "<p>A program to view four-dimensional objects "
		      "using OpenGL and the Qt GUI library.</p>"
		      "<p>author: "+QString(PACKAGE_BUGREPORT)+"</p>"
		      "<p>version: "+QString(PACKAGE_VERSION)+" of 2004-04-20</p>"
		      );
}


/*******************************************************************************
 *  open an "About Qt"-Dialog
 */
void XQGLWidget::aboutQt()
{
  QMessageBox::aboutQt( this, "Hyperspace Explorer" );
}


