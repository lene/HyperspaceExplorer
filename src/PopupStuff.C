
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


//      project:      Extended QGLWidget
//      module:       PopupStuff.C
//      compile with: make all
//      contains:     Menu and keyboard accelerator declarations for XQGLWidget


#include <qapp.h>
#include <qpopupmenu.h>
#include <qaccel.h>
#include <qslider.h>
#include <qmessagebox.h>

#include "numclass.H"

#include "XQGLWidget.H"
#include "Help.H"

QPopupMenu *XQGLWidget::SetupMenu (void) {
    menu   = new QPopupMenu;
    appear = new QPopupMenu;
    help   = new QPopupMenu;
  
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

    //  Top level menu
void XQGLWidget::Rotate () {
    double theta_ = theta;
    for (double i = 0.; i < 360.; i += 3.) {
	theta = theta_+i;
	repaint (); }
    theta = theta_; }

void XQGLWidget::Help () {
    static HelpWindow *H;
    H = new HelpWindow ("Hyperspace_Explorer_Help.html",
			qApp->applicationDirPath ()+"/Documentation");
    H->setCaption("Qt Example - Helpviewer");
    H->show();

}

    //  Appearance menu
void XQGLWidget::Light () {                                  //  toggles lighting
    light = !light;
    appear->setItemChecked (lightID, light);
    InitLight ();
    repaint (); }

void XQGLWidget::Fog () {                                    //  toggles fog (depth cueing)
    fog = !fog;
    appear->setItemChecked (fogID, fog);
    InitFog ();
    repaint (); }

void XQGLWidget::Transparent () {
    transparent = !transparent;
    appear->setItemChecked (transparentID, transparent);
    InitTransparence ();
    repaint (); }

void XQGLWidget::Shade () {
    shade = !shade;
    appear->setItemChecked (shadeID, shade);
    InitShade ();
    repaint (); }

void XQGLWidget::Colors () {
    colors = !colors;
    appear->setItemChecked (colorsID, colors);
    initializeGL ();
    repaint (); }


void XQGLWidget::mousePressEvent (QMouseEvent *E) {
    int ButtonPressed = E->button ();
    if (ButtonPressed == RightButton)
#   if (QT_VERSION < 300)
      menu->exec (QCursor::pos ());
#   else
      menu->exec (E->pos());
#   endif
    else if (ButtonPressed == LeftButton) {
	xpressed = E->x (); ypressed = E->y (); }
    else if (ButtonPressed == MidButton) {
	if (E->state () && ShiftButton) ViewPos (R+1);
	else                            // ViewPos (R-1); }
	    ypressed = E->y (); } }

void XQGLWidget::mouseReleaseEvent (QMouseEvent *E) { 
    int ButtonPressed = E->button ();
    if (ButtonPressed == LeftButton) {
	int dx = E->x () - xpressed, dy = E->y () -ypressed,
	    dtheta = dx*90/width (), dpsi   = dy*90/height ();
	theta += dtheta; psi += dpsi;
	repaint (); } 
    if (ButtonPressed == MidButton) {
	double dr = double (E->y ()-ypressed)/height ()*5.;   //  the 5 may have to be reviewed
	if (dr) ViewPos (R*pow (1.25, dr));                           //  exponential change (1.25 also)
	else if (!(E->state () && ShiftButton))
	    ViewPos (R/1.25);
	    //    cerr << "dr = " << dr << " R = " <<R << endl;
    }
}

void XQGLWidget::mouseMoveEvent (QMouseEvent *) { }

    //  keyboard accelerators
void XQGLWidget::SetupAccel (void) {
    static QAccel *accel;
    accel = new QAccel (this);

    accel->connectItem (accel->insertItem (Qt::Key_Left),  this, SLOT (Left ()));
    accel->connectItem (accel->insertItem (Qt::Key_Right), this, SLOT (Right ()));
    accel->connectItem (accel->insertItem (Qt::Key_Up),    this, SLOT (Up ()));
    accel->connectItem (accel->insertItem (Qt::Key_Down),  this, SLOT (Down ())); 

    accel->connectItem (accel->insertItem (Qt::Key_Left+SHIFT),  this, SLOT (SLeft ()));
    accel->connectItem (accel->insertItem (Qt::Key_Right+SHIFT), this, SLOT (SRight ()));
    accel->connectItem (accel->insertItem (Qt::Key_Up+SHIFT),    this, SLOT (SUp ())); 
    accel->connectItem (accel->insertItem (Qt::Key_Down+SHIFT),  this, SLOT (SDown ()));

    accel->connectItem (accel->insertItem (Qt::Key_Left+ALT+CTRL),  this, SLOT (CALeft ()));
    accel->connectItem (accel->insertItem (Qt::Key_Right+ALT+CTRL), this, SLOT (CARight ()));
    accel->connectItem (accel->insertItem (Qt::Key_Up+ALT+CTRL),    this, SLOT (CAUp ())); 
    accel->connectItem (accel->insertItem (Qt::Key_Down+ALT+CTRL),  this, SLOT (CADown ())); 
 
    accel->connectItem (accel->insertItem (Qt::Key_A), this, SLOT (A ())); 

    accel->connectItem (accel->insertItem (Qt::Key_Q+CTRL), qApp, SLOT (quit ())); }

void XQGLWidget::Left () {
    theta -= 5; repaint (); }
void XQGLWidget::Right () {
    theta += 5; repaint (); }
void XQGLWidget::Up () {
    psi -= 5; repaint (); }
void XQGLWidget::Down () {
    psi += 5; repaint (); }

void XQGLWidget::SLeft () {
    theta -= 45; repaint (); }
void XQGLWidget::SRight () {
    theta += 45; repaint (); }
void XQGLWidget::SUp () {
    psi -= 45; repaint (); }
void XQGLWidget::SDown () {
    psi += 45; repaint (); }

void XQGLWidget::CALeft () {
    theta -= 1; repaint (); }
void XQGLWidget::CARight () {
    theta += 1; repaint (); }
void XQGLWidget::CAUp () {
    psi -= 1; repaint (); }
void XQGLWidget::CADown () {
    psi += 1; repaint (); }


void XQGLWidget::A () { 
    QSlider *GetAlpha = new QSlider    (0  , 255,  64, int (Alpha*255),
					QSlider::Horizontal, this);
    GetAlpha->setTickInterval (16);
    GetAlpha->setFixedSize (200, 20);
    GetAlpha->show ();
  
    connect (GetAlpha, SIGNAL(valueChanged(int)), this, SLOT(SetAlpha(int))); }

void XQGLWidget::Plus () {
}

void XQGLWidget::Minus () {
}

void XQGLWidget::about()
{
    QMessageBox::about( this, "Hyperspace Explorer",
                        "<p>A program to view four-dimensional objects "
                        "using OpenGL and the Qt GUI library.</p>"
                        "<p>author: "PACKAGE_BUGREPORT"</p>"
                        "<p>version: "PACKAGE_VERSION" of 2004-04-20</p>"
                        );
}


void XQGLWidget::aboutQt()
{
    QMessageBox::aboutQt( this, "Hyperspace Explorer" );
}


