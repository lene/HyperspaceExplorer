
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//      author:       helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)

#include <sstream>
#include <iomanip>

#include <QMouseEvent>
#include <QMainWindow>
#include <QStatusBar>

#include "4DView.H"
#include "Menu4D.H"
#include "AnimationDialogImpl.H"
#include "Help.H"

#include "Globals.H"
#include "Log.H"
#include "ColorManager.H"

#include "Matrix.H"

#include "Function.H"
#include "Surface.H"
#include "ComplexFunction.H"
#include "Object.H"

#include "ParameterMap.H"

using std::ostringstream;
using std::cerr;
using std::endl;
using std::ends;
using std::auto_ptr;
using std::vector;

using VecMath::Vector;
using VecMath::Matrix;

GLfloat C4DView::LightPos[4] = { 4., 4., 8., 0. };

template<typename T> T min(const T &a, const T &b) {
    return (a < b? a: b);
}
template<typename T> T max(const T &a, const T &b) {
    return (a > b? a: b);
}

////////////////////////////////////////////////////////////////////////////////
// 	C4DView construction/destruction
////////////////////////////////////////////////////////////////////////////////

/// C4DView constructor
/** does a lot of initialization to (usually sensible)
 *  hardcoded default values, initializes the coordinate cross object (which
 *  could well be a class on its own), creates the necessary timers and menus,
 *  and finally creates a Hypercube as the default object to display
 *  @param parent	parent QWidget, defaults to NULL                      */
C4DView::C4DView(QWidget *parent):
    QGLWidget (parent),
    pImpl(new Impl(this)) {

    InitCross();

    setAnimationTimer(new QTimer (this));
    connect (AnimationTimer(), SIGNAL(timeout()), this, SLOT(OnTimer()));

    setAnimateRandomTimer(new QTimer (this));
    //  connect (AnimateRandomTimer, SIGNAL(timeout()), this, SLOT(RandomAnimation()));

    connect (Values(), SIGNAL (ApplyChanges (const ParameterMap &)),
             this, SLOT (ApplyChanges (const ParameterMap &)));

    setmenu(new Menu4D(this));
    menu()->addToMenuBar(Globals::Instance().getMainWindow()->menuBar());

    show ();

    ColMgrMgr::Instance().setColorManager(new xyz2RGBColorManager(F().get()));

    ObjectHypercube ();

    Light ();
}

/// C4DView destructor
C4DView::~C4DView() { }

/// Switch between wireframe and solid display
/** Account for antialiasing only in wireframe mode \n
 *  Change menu items accordingly \n
 *  Menu callback function                                                    */
void C4DView::Wireframe() {
    if (DisplayPolygons()) {
        menu()->getAction("Wireframe")->setText("Solid");
        menu()->getAction("Transparence")->setText("Line Antialiasing");
    } else {
        menu()->getAction("Wireframe")->setText("Wireframe");
        menu()->getAction("Transparence")->setText("Transparence");
        glDisable (GL_CULL_FACE);
    }
    menu()->getAction("Wireframe")->setChecked (DisplayPolygons());
    setWireframe (DisplayPolygons());

    OnPaint ();
}

/// switch coordinate cross on or off
/** change menu items accordingly \n
 *  menu callback function */
void C4DView::Coordinates() {
    setDisplayCoordinates(!DisplayCoordinates());
    menu()->getAction("Coordinate Cross")->setChecked (DisplayCoordinates());

    Redraw ();
}

/// switch 4D depth cue on or off
/** change menu items accordingly \n
 *  menu callback function */
void C4DView::HyperFog() {
    setDepthCue4D(!DepthCue4D());
    menu()->getAction("4D Depth Cue")->setChecked (DepthCue4D());

    Redraw ();
}

/// switch lighting on or off
/** change menu items accordingly \n
 *  menu callback function */
void C4DView::Light() {
    setLighting(!Lighting());
    if (Lighting()) {
        glEnable(GL_LIGHTING);                  //  turn on the light

        static GLfloat LightAmbient[]  = { 0.3f, 0.3f, 0.3f, 1.0f }, //  HARDCODED VALUES
                       LightDiffuse[]  = { 0.9f, 0.9f, 0.9f, 1.0f },
                       LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f },
                       LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //  light properties

        glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); // set the light properties
        glLightfv (GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
        glLightfv (GL_LIGHT0, GL_SPECULAR, LightSpecular);
        glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
        glEnable  (GL_LIGHT0);   // turn on the light
    } else {
        static GLfloat LightAmbient[]  = { 1.0f, 1.0f, 1.0f, 0.0f },
                       LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //      light properties

        glEnable  (GL_LIGHTING);
        glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); // set the light properties
        glLightfv (GL_LIGHT0, GL_DIFFUSE, LightAmbient);
        glLightfv (GL_LIGHT0, GL_SPECULAR, LightAmbient);
        glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
        glEnable  (GL_LIGHT0);    //      turn on the light
    }

    OnPaint ();
}

/// toggle colors
/** menu callback function */
void C4DView::Colors () {
    getColors() = !getColors();
    menu()->getAction("Colors")->setChecked(getColors());
    initializeGL ();
    repaint (); }

/// Toggle fog/depth cue
/** menu callback function */
void C4DView::Fog () {
  getFog() = !getFog();
  menu()->getAction("Depth Cue")->setChecked(getFog());
  InitFog ();
  repaint (); }

/// toggle object transparency
/** menu callback function */
void C4DView::Transparent () {
  getTransparent() = !getTransparent();
  menu()->getAction("Transparence")->setChecked(getTransparent());
  InitTransparence ();
  repaint (); }

/// toggle shading
/** menu callback function */
void C4DView::Shade () {
  getShade() = !getShade();
  menu()->getAction("Shading")->setChecked(getShade());
  InitShade ();
  repaint (); }

/// run a benchmark test
  /** menu callback function */
  void C4DView::Benchmark() {
      ostringstream Time;

      double time_4d = Benchmark4D (360, 1., 0., 0.);

      Time << "4D viewpoint rotation: " << time_4d << " sec."
              << " (" << 360/1./time_4d << " fps)" << endl;

      float time_3d = Benchmark3D (360, 1., 0., 0.);

      Time << "3D viewpoint rotation: " << time_3d << " sec."
              << " (" << 360/1./time_3d << " fps)" << ends;

      QMessageBox::information (NULL, "Benchmark results", Time.str ().c_str ());
      UpdateStatus ();
  }

/// switch rendering to files on or off
/** change menu items accordingly        \n
 *  menu callback function */
void C4DView::RenderToImages() {
  setRenderToPixmap(!RenderToPixmap());
  menu()->getAction("Render to Images")->setChecked(RenderToPixmap());
}

/// display a ObjectHypercube object
/** menu callback function */
void C4DView::ObjectHypercube() {
    menu()->updateFunctionMenu("Hypercube");

    setF(new Hypercube (/*Values()->a ()*/));

    AssignValues(F());
    Redraw ();
}

/// display a ObjectHyperpyramid object
/** menu callback function */
void C4DView::ObjectHyperpyramid() {
    menu()->updateFunctionMenu("Hyperpyramid");

    setF(new Pyramid (/*2.*Values()->a ()*/));

    AssignValues(F());
    Redraw ();
}

/// display a ObjectHypersponge object
/** menu callback function */
void C4DView::ObjectHypersponge() {
    menu()->updateFunctionMenu("Menger Sponge");

    setF(new Sponge ()
//                unsigned (Values()->a ()), int (Values()->b ()), Values()->c ())
//            1, 2, 0.8)
           );

    AssignValues(F());
    Redraw ();
}

/// display a ObjectGasket object
/** menu callback function */
void C4DView::ObjectGasket() {
    menu()->updateFunctionMenu("Sierpinski Gasket");

    setF(new Gasket (/* unsigned (Values()->a ()), 2.*Values()->b ()*/));

    AssignValues(F());
    Redraw ();
}

/// display a customFunction object
/** menu callback function */
void C4DView::customFunction() {
    CustomFunctionSlot<CustomFunction>::createCustomFunction(this);
}

/// display a customPolarFunction object
/** menu callback function */
void C4DView::customPolarFunction() {
    CustomFunctionSlot<CustomPolarFunction>::createCustomFunction(this);
}

/// display a customSurface object
/** menu callback function */
void C4DView::customSurface() {
    CustomFunctionSlot<CustomSurface>::createCustomSurface(this);
}

/// display a customComplexFunction object
/** menu callback function */
void C4DView::customComplexFunction() {
    CustomFunctionSlot<CustomComplexFunction>::createCustomSurface(this);
}

/// rotate in 3D 360 degrees
double C4DView::Benchmark3D (int num_steps,
                             double step_x, double step_y, double step_z,
                             bool display) {
    clock_t stime = clock ();                     //  record start time

    double Rx = m_rotX(), Ry = m_rotY(), Rz = m_rotZ();

    for (int step = 0; step < num_steps; step++) {
        setm_rotX(m_rotX() + step_x); setm_rotY(m_rotY() + step_y); setm_rotZ(m_rotZ() + step_z);
        if (display) {
            OnPaint ();
            UpdateStatus (QString::number ((100*step)/num_steps)+"% done");
        }
    }
    setm_rotX(Rx); setm_rotY(Ry); setm_rotZ(Rz);

  return double (clock ()-stime)/CLOCKS_PER_SEC;
}

/// rotate in 4D 360 degrees
double C4DView::Benchmark4D (int num_steps,
                             double step_xw, double step_yw, double step_zw,
                             bool display) {
  clock_t stime = clock ();                     //  record start time

  double Rxw = 0., Ryw = 0., Rzw = 0.;

  for (int step = 0; step < num_steps; step++) {
    Rxw += step_xw; Ryw += step_yw; Rzw += step_zw;
    Transform (0., 0. ,Rxw, 0. , Ryw, Rzw, 0., 0., 0., 0.);
    if (display) {
      Redraw ();
      UpdateStatus (QString::number ((100*step)/num_steps)+"% done");
    }
  }

  return double (clock ()-stime)/CLOCKS_PER_SEC;
}

/// Timer event handler
/** Updates values if in the middle of an animation, and renders an image. \n
 *  Writes image to file too, if wanted.                                      */
void C4DView::OnTimer() {
    setm_rotX(m_rotX() + dx()); setm_rotY(m_rotY() + dy()); setm_rotZ(m_rotZ() + dz());   //  update 3D viewpoint values

    SingletonLog::Instance() << "C4DView::OnTimer()\n"
            << "  dx = " <<  dx() << "  dy = " <<  dy() << "  dz = " <<  dz() << "\n"
            << " dxy = " << dxy() << " dxz = " << dxz() << " dxw = " << dxw()
            << " dyz = " << dyz() << " dyw = " << dyw() << " dzw = " << dzw()
            << "\n";

    if (dxy() != 0 || dxz() != 0 || dxw() != 0 ||     //  4D viewpoint animated?
        dyz() != 0 || dyw() != 0 || dzw() != 0 ) {

        setRxy(Rxy() + dxy()); setRxz(Rxz() + dxz()); setRxw(Rxw() + dxw());   //  update values
        setRyz(Ryz() + dyz()); setRyw(Ryw() + dyw()); setRzw(Rzw() + dzw());   //  update values

        Transform (Rxy(), Rxz(), Rxw(), Ryz(), Ryw(), Rzw(), Tx(), Ty(), Tz(), Tw());   // transform
        Redraw ();                                                  // implicit OnPaint()
        } else OnPaint ();                                              // explicit OnPaint()

        writeFrame();   //  if render to pixmap is selected, do it

        UpdateStatus (QString("Animation: Frame %1").arg(animationFrame())
                +(animationMaxFrames() > 0 && animationMaxFrames() < (unsigned)(-1)?
                QString("/%1").arg(animationMaxFrames()):
                QString(""))
                +" - Double-click LMB to stop");
}

/// show a dialog to adjust animation settings
/** Where to write image files and how many files to write \n
 *  menu callback function */
void C4DView::AnimationSettings() {
    AnimationDialogImpl *Dlg = new AnimationDialogImpl;
    if (Dlg->exec () == QDialog::Accepted) {
        setanimationMaxFrames(Dlg->getFrames());
        setanimationDirectory(Dlg->getDir());
        setanimationPrefix(Dlg->getPrefix());
        SingletonLog::Instance()
                << "animationMaxFrames: " << (long)animationMaxFrames()
                << ", animationDirectory: " << animationDirectory().toStdString()
                << ", animationPrefix: "<< animationPrefix().toStdString() << "\n";
    }
}

/// Called whenever an object or the parameters have changed
/** Sets the parameters, applies the changed parameters to the function object
 *  and redraws it                                                            */
void C4DView::ApplyChanges (const ParameterMap &parms) {
    F().get()->SetParameters(parms);

    SingletonLog::Instance() << "C4DView::ApplyChanges ():\n"
                             << parms.print() << "\n"
                             << Values()->print() << "\n";

    F()->ReInit (Values()->tmin (), Values()->tmax (), Values()->dt (),
               Values()->umin (), Values()->umax (), Values()->du (),
               Values()->vmin (), Values()->vmax (), Values()->dv ());

    ColMgrMgr::Instance().setFunction(F().get());

    Transform ();

    Redraw ();
}

/** display help window
 * \todo HARDCODED filename */
void C4DView::Help () {
    static HelpWindow *H;
    H = new HelpWindow ("Hyperspace_Explorer_Help.html");
    H->show();
}

/** open an "About"-Dialog */
void C4DView::about() {
    QMessageBox::about(this, "Hyperspace Explorer",
                       "<p>A program to view four-dimensional objects "
                               "using OpenGL and the Qt GUI library.</p>"
                               "<p>author: "+QString(make_str(PACKAGE_BUGREPORT))+"</p>"
                               "<p>version: "+QString(make_str(PACKAGE_VERSION))+
                               " of "+QString(__DATE__)+"</p>"
                      );
}

/** open an "About Qt"-Dialog */
void C4DView::aboutQt() {
    QMessageBox::aboutQt( this, "Hyperspace Explorer" );
}

/// Application of translations and rotations
/** Calls F->Transform () and transforms the coordinate cross
 *  @param thetaxy rotation around xy plane (z axis); ignored because 3D rotation takes care of it
 *  @param thetaxz rotation around xz plane (y axis); ignored because 3D rotation takes care of it
 *  @param thetaxw rotation around xw plane
 *  @param thetayz rotation around xy plane (x axis); ignored because 3D rotation takes care of it
 *  @param thetayw rotation around yw plane
 *  @param thetazw rotation around zw plane
 *  @param tx translation in x direction
 *  @param ty translation in y direction
 *  @param tz translation in z direction
 *  @param tw translation in w direction                            */
void C4DView::Transform (double thetaxy, double thetaxz, double thetaxw,
                         double thetayz, double thetayw, double thetazw,
                         double tx, double ty, double tz, double tw) {
    if (F().get())
        F()->Transform (thetaxy, thetaxz, thetaxw, thetayz, thetayw, thetazw,
                      tx, ty, tz, tw);
    else return;

    Matrix<4> Rxy = Matrix<4> (0, 1, thetaxy), Rxz = Matrix<4> (0, 2, thetaxz),
              Rxw = Matrix<4> (0, 3, thetaxw), Ryz = Matrix<4> (1, 2, thetayz),
              Ryw = Matrix<4> (1, 3, thetayw), Rzw = Matrix<4> (2, 3, thetazw),
              Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw,
              Rot = Rxyz*Rxwyz*Ryzw;
    Vector<4> trans = Vector<4>(tx, ty, tz, tw);

    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 2; j++)
            CrossTrans[i][j] = (Rot*Cross[i][j])+trans;
}

/// Projects F and coordinate cross into three-space
/** */
void C4DView::Project (void) {
    if (F().get()) F()->Project (ScrW(), CamW(), DepthCue4D());
    else return;

    if (DisplayCoordinates()) {
        for (unsigned i = 0; i < 2; i++)
            for (unsigned j = 0; j < 4; j++) {
                double ProjectionFactor = (ScrW()-CamW())/(CrossTrans[j][i][3]-CamW());
                for (unsigned k = 0; k < CrossScr[j][i].dimension(); k++)
                    CrossScr[j][i][k] = CrossTrans[j][i][k]*ProjectionFactor;
            }
    }
}

/// draw the projected Object (onto screen or into GL list, as it is)
/** */
void C4DView::Draw () {
    if (DisplayCoordinates()) DrawCoordinates ();

    F()->Draw ();
}

/// 4D projection stuff
/** Separated from the 3D OpenGL handling into this function                  */
void C4DView::PreRedraw () {
//    SingletonLog::Instance().log("C4DView::PreRedraw ()");

    // this does seem very ineffective to me, deleting and reassigning the GL Lists,
    // but it does not seem to work any other way...?

    if (DisplayCoordinates()) {
        if (CoordinateCross()) glDeleteLists (CoordinateCross(), 1);
        setCoordinateCross(Globals::Instance().GetGLList());
        glNewList (CoordinateCross(), GL_COMPILE);
        DrawCoordinates();
        glEndList();
    }

    if (ObjectList()) glDeleteLists(ObjectList(), 1);
    setObjectList(Globals::Instance().GetGLList());
    glNewList (ObjectList(), GL_COMPILE_AND_EXECUTE);
        /*
        glBegin (GL_POINTS);
            setColor (0., 0., 0.);
            for (unsigned i = 0; i < 160; i++) glVertex3d (0., 0., i/100.);
        glEnd ();
        */
        Project ();
        Draw ();

    glEndList ();

//    SingletonLog::Instance().log("C4DView::PreRedraw () done");
}

/// Redraw handler
void C4DView::Redraw () {
  PreRedraw ();
  OnPaint ();
}

/// Wrapper for redraw handler
/** With an error reporting routine and exit strategy */
void C4DView::RenderScene (unsigned /* Frame */) {  //  draw (frame of animation)
    usleep (16000);
    while (!glIsList (ObjectList())) {
#       ifdef DEBUG
            switch (
                QMessageBox::warning (
                    NULL, "C4DView::RenderScene",
                    ("ObjectList No. "+Globals::Instance().itoa (ObjectList())+
                     " is not a GL list!").c_str (),
                    "Retry", "Die", 0, 0, 1)) {
                case 0: PreRedraw ();
                        break;
                case 1: exit (1);
                        break;
            }
            sleep (1);
#       else
            cerr << "C4DView::RenderScene ():  "
                 << "ObjectList No. " << Globals::Instance().itoa(ObjectList())
                 << " is not a GL list!" << endl;
            sleep (1);
            PreRedraw ();
#       endif
    }

    glCallList (ObjectList());                                //  draw the object
    if (DisplayCoordinates()) glCallList (CoordinateCross());
}

/// Should be called whenever the object is rotated or translated
/** Object drawing routine: Does all the OpenGL stuff necessary to paint the
 *  object on screen                                                          */
void C4DView::OnPaint() {
//    SingletonLog::Instance().log("C4DView::OnPaint ()");

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //  clear the window

    if (DisplayPolygons())                            //  this might move to a special
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //  routine "SwitchWireframe ()"
    else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPushMatrix();                                 //  save transformation Matrix
    // glTranslated(0.0, /*Size ()*.75*/0., 0);     //  set the camera position

    glTranslated (m_transX(), m_transY(), m_camZ());      //  apply object translation
    glRotated(m_rotX(), 1.0, 0.0, 0.0);               //   -"-    -"-     rotation
    glRotated(m_rotY(), 0.0, 1.0, 0.0);
    glRotated(m_rotZ(), 0.0, 0.0, 1.0);

    RenderScene (0);                                //  draw current frame

    glPopMatrix();                                  //  restore transformation Matrix

    swapBuffers ();                                 //  swap the buffers

    writeFrame();
}

/// Initialize the structures to display a four-dimensional coordinate cross
void C4DView::InitCross() {
    Cross = vector<vector<Vector<4> > > (4);
    CrossTrans = vector<vector<Vector<4> > > (4);
    CrossScr = vector<vector<Vector<3> > > (4);;
    for (unsigned j = 0; j < 4; j++) {
        Cross[j].resize(2);
        CrossTrans[j].resize(2);
        CrossScr[j].resize(2);
        for (unsigned k = 0; k < 2; k++) {
            //  CrossTrans[j][k] = Vector (4, 0., 0., 0., 0.);
            CrossScr[j][k] = Vector<3> (0., 0., 0.);
        }
    }
    Cross[0][0] = Vector<4>(-5., 0., 0., 0.);
    Cross[0][1] = Vector<4>( 5., 0., 0., 0.);
    Cross[1][0] = Vector<4>(0., -5., 0., 0.);
    Cross[1][1] = Vector<4>(0.,  5., 0., 0.);
    Cross[2][0] = Vector<4>(0., 0., -5., 0.);
    Cross[2][1] = Vector<4>(0., 0.,  5., 0.);
    Cross[3][0] = Vector<4>(0., 0., 0., -5.);
    Cross[3][1] = Vector<4>(0., 0., 0.,  5.);
}

/// Switch 3D depth cue on and off
/** @param on whether to use fog                                              */
void C4DView::SetupDepthCue (bool on) {
    setDepthCue3D(on);
    if (on) {
        cerr << "m_camZ(): " << m_camZ() << endl;
        SetupDepthCue(
            fabs(m_camZ())-Size()/2.,
            fabs(m_camZ())+Size()/2.*Globals::Instance().SR3);
        glEnable(GL_FOG);
    }
    else glDisable (GL_FOG);
}

/// Adjust parameters for depth cue
/** \todo fill in the meaning of the parameters
 *  @param dist
 *  @param size
 */
void C4DView::SetupDepthCue (float dist, float size) {
    glFogi (GL_FOG_MODE,  GL_LINEAR);             //  set fog mode to linear
    glFogfv(GL_FOG_COLOR, Globals::Instance().FogColor());
    glFogf (GL_FOG_START, max(dist-size/2., 0.));         //  ...
    glFogf (GL_FOG_END,   dist+size/2.*Globals::Instance().SR3);
}

/// draw the coordinate cross (on screen or int GL list)                      */
/** */
void C4DView::DrawCoordinates () {
    for (unsigned j = 0; j < 4; j++) {
        switch (j) {
        case 0:
            ColMgrMgr::Instance().setRGB (Color(1., 0., 0.));
            break;
        case 1:
            ColMgrMgr::Instance().setRGB (Color(0., 1., 0.));
            break;
        case 2:
            ColMgrMgr::Instance().setRGB (Color(0., 0., 1.));
            break;
        case 3:
            ColMgrMgr::Instance().setRGB (Color(1., 0., 1.));
            break;
        }
        glBegin (GL_LINES);
            for (unsigned i = 0; i < 2; i++)
                Globals::Instance().glVertex (CrossScr[j][i]);
        glEnd ();
    }
}

/// Err well.. just that!
/** Starts AnimationTimer, too...                                             */
void C4DView::StartAnimation () {
    SingletonLog::Instance().log("C4DView::StartAnimation ()");

    setAnimated(true);
    setanimationFrame(0);
    AnimationTimer()->start (1000/animation_fps());               //  go for 50 fps

    UpdateStatus ("Double-click LMB to stop animation");
}

/// you guessed it
void C4DView::StopAnimation () {
    SingletonLog::Instance().log("C4DView::StopAnimation ()");

    setAnimated(false);
    setdxy(0.); setdxz(0.); setdxw(0.); setdyz(0.); setdyw(0.); setdyw(0.);
    setdx(0.); setdy(0.); setdz(0.);
    AnimationTimer()->stop ();
    AnimateRandomTimer()->stop ();
    setCurrentlyRendering(false);
}

/// Starts a random animation
/** xw/yw/zw rotation speed changes every 10 seconds
 *  @todo make hardcoded duration of rotation change frequency adjustable
 *  @todo a menu entry for this                                               */
void C4DView::RandomAnimation() {
    AnimationTimer()->stop ();
    AnimateRandomTimer()->stop ();

    setdxw(float (rand ())/RAND_MAX);
    setdyw(float (rand ())/RAND_MAX);
    setdzw(float (rand ())/RAND_MAX);
    StartAnimation ();

    AnimateRandomTimer()->start (10000);
}

/// Make a pixmap to to be rendered by the GL widget, and render it.
/** this is an embarrassing workaround to make rendering to files work.
 *  QGLWidget's renderPixmap() method only produces black frames. Works with
 *  QPixmap::grabWindow() instead.                                            */
QPixmap C4DView::makePixmap() {

    this->activateWindow();
    this->raise();

    QPixmap pm = QPixmap::grabWindow(this->winId());

    if ( pm.isNull() ) {
        SingletonLog::Instance() << "Failed to render Pixmap.\n";
    }

    return pm;
}

/** writes a snapshot of the current frame of an animation or interactive
 *  display to disk \n
 *  updates animationFrame                                                    */
void C4DView::writeFrame() {
    if (RenderToPixmap() && (animationFrame() <= animationMaxFrames())) {

        setCurrentlyRendering(true);

        PreRedraw ();

        QPixmap tmpPixmap = makePixmap();

        unsigned animationCiphers = animationMaxFrames() > 0?
                (unsigned)(log((double)animationMaxFrames())/log(10.))+1: 6;
        QString imageFilename =
                QString (animationDirectory()+"/"+animationPrefix()+"%1.png")
                .arg (animationFrame(), animationCiphers)
                .replace (" ", "0");
        if (tmpPixmap.save (imageFilename, "PNG")) {
            cerr << "writing "
                    << imageFilename.toStdString() << " successful! ("
                    << (long)animationFrame() << "/" << (long)animationMaxFrames()
                    << ")\n";
        } else {
            SingletonLog::Instance() << "writing "
                    << imageFilename.toStdString() << " failed!\n";
        }
    }
    setanimationFrame(animationFrame()+1);
}

/// Keep all rotation angles in the interval [-360 degrees, 360 degrees]
void C4DView::checkAnglesForOverflow() {
    if (m_rotX() > 360) setm_rotX(m_rotX() - 360);
    if (m_rotX() <-360) setm_rotX(m_rotX() + 360);
    if (fabs (m_rotX()) < 1e-3) setm_rotX(0);
    if (m_rotY() > 360) setm_rotY(m_rotY() - 360);
    if (m_rotY() <-360) setm_rotY(m_rotY() + 360);
    if (fabs (m_rotY()) < 1e-3) setm_rotY(0);
    if (m_rotZ() > 360) setm_rotZ(m_rotZ() - 360);
    if (m_rotZ() <-360) setm_rotZ(m_rotZ() + 360);
    if (fabs (m_rotZ()) < 1e-3) setm_rotZ(0);
    if (Rxw() > 360) setRxw(Rxw() - 360);
    if (Rxw() <-360) setRxw(Rxw() + 360);
    if (Ryw() > 360) setRyw(Ryw() - 360);
    if (Ryw() <-360) setRyw(Ryw() + 360);
    if (Rzw() > 360) setRzw(Rzw() - 360);
    if (Rzw() <-360) setRzw(Rzw() + 360);
}

/// display some info about current object and its transformations
/** In the status bar.
 *
 *  Side effect: checks rotation values for overflow and resets them to the
 *  interval [-360, 360].
 *  @param status string to be displayed                                      */
void C4DView::UpdateStatus (QString status) {

    checkAnglesForOverflow();

    if (!status.isEmpty ()) {
        for (unsigned i = status.length (); i <= 24; i++) status = " "+status;
        status = " - "+status;
    }

    Globals::Instance().getMainWindow()->statusBar()->showMessage(
                      F()->getFunctionName()+status);

    setWindowTitle(F()->getFunctionName()+status);
}

/// Called whenever an object or the parameters have changed
/** Changes the display on the status bar and the number and names of the
 *  parameters and grid parameters on the ValuesDialog
 *  @param F the Function object for which the ValuesDialog is changed        */
void C4DView::AssignValues (const std::auto_ptr<Function> &F) {

    if (!F->getFunctionName().isEmpty()) {
        setWindowTitle(F->getFunctionName());
    }

    Values()->setFunction(F);
    Transform ();

    ColMgrMgr::Instance().setFunction(F.get());

    UpdateStatus("");
}

/// Get size of displayed area
/** @return approximate diameter of definition space                          */
double C4DView::Size () {
  return sqrt ((Values()->tmax ()-Values()->tmin ())*(Values()->tmax ()-Values()->tmin ())
              +(Values()->umax ()-Values()->umin ())*(Values()->umax ()-Values()->umin ())
              +(Values()->vmax ()-Values()->vmin ())*(Values()->vmax ()-Values()->vmin ()));
}

/// Mouse move event handler
/** Awfully long, which is UGLY, but it does not seem to make much sense to
 *  break it up, so here we go \n
 *  Particular mouse move/button/modifier key combinations documented in the
 *  code below
 *  @param e Qt's mouse event information structure                           */
void C4DView::mouseMoveEvent (QMouseEvent *e) {
    SingletonLog::Instance() << "C4DView::mouseMoveEvent ("
                << (long)e->modifiers()<<")\n";
    QPoint point = e->pos ();
    Qt::KeyboardModifiers s = e->modifiers();
    Qt::MouseButtons b = e->buttons();

    bool LeftButtonDown  = b & Qt::LeftButton,
         MidButtonDown   = b & Qt::MidButton,
         RightButtonDown = b & Qt::RightButton,
         AltPressed = s & Qt::AltModifier,
         ControlPressed = s & Qt::ControlModifier,
         ShiftPressed = s & Qt::ShiftModifier;

    SingletonLog::Instance() << (LeftButtonDown? "LMB ": "")
             << (MidButtonDown? "MMB ": "")
             << (RightButtonDown? "RMB ": "")
             << (AltPressed? "+ Alt ": "")
             << (ControlPressed? "+ Ctrl ": "")
             << (ShiftPressed? "+ Shift ": "") << "\n";

    bool ViewChanged = false;

    double xsize = width (),
           ysize = height ();


    if (xsize == 0 || ysize == 0) return;       //  pathological case better taken care of

    if (AltPressed) setTakingSpinValues(true);
    else            setTakingSpinValues(false);

    if (ControlPressed) {                                   //  CONTROL pressed

        if (LeftButtonDown || MidButtonDown || RightButtonDown) {   //  CONTROL + any Button

            ViewChanged = true;                         //  mark 4D viewpoint as changed

            double size = Size ();                      //  reference size for the translations

            //    translate x / y with LMB
            if (LeftButtonDown && !MidButtonDown && !RightButtonDown) { //  CONTROL+LMB pressed

               QPoint translate = m_LeftDownPos()-point;  //  store difference from button press position

               if (TakingSpinValues()) {    } else {      //  no translation animation (yet?)
                   setm_LeftDownPos(point);               //  reset start position for next mouse move

                   setTx(Tx() - translate.x ()*size/xsize);     //  add x translation
                   setTy(Ty() + translate.y ()*size/ysize);     //  add y translation

                   UpdateStatus ("translate x/y");
               }               //    if (TakingSpinValues)

            }                 //    if (LeftButtonDown && !MidButtonDown && !RightButtonDown)

            //    translate z / w with MMB
            if (MidButtonDown && !LeftButtonDown && !RightButtonDown) { //  CTRL + MMB pressed

                QPoint translate = m_MidDownPos()-point;   //  store difference from button press position

                if (TakingSpinValues()) {    } else {      //  no translation animation (yet?)
                    setm_MidDownPos(point);                //  reset start position for next mouse move

                    setTz(Tz() - translate.x ()*size/xsize);     //  add z translation
                    setTw(Tw() + translate.y ()*size/ysize);     //  add w translation

                    UpdateStatus ("translate z/w");
	        }            //  if (TakingSpinValues)

            }                //  if (MidButtonDown && !LeftButtonDown && !RightButtonDown)

        }                 //    if (LeftButtonDown || MidButtonDown || RightButtonDown)

    }                     //    if (::GetKeyState (VK_CONTROL) < 0)

    if (ShiftPressed) {                     //  rotate 4D viewpoint with SHIFT pressed

        if (LeftButtonDown || MidButtonDown || RightButtonDown) {   //  SHIFT + any button

            ViewChanged = true;                            //  mark 4D viewpoint as changed

            //    rotate xy / xz with LMB
            if (LeftButtonDown && !MidButtonDown && !RightButtonDown) { //  SHIFT + LMB

                QPoint rotate = m_LeftDownPos()-point;    //  store difference from button press position
                ViewChanged = false;                    //  takes only xy/xz values, which are
                                                        //  equivalent to z/y 3D rotation

                if (TakingSpinValues()) {
                    setdz(dz() + rotate.x ()/xsize*5);
                    setdy(dy() + rotate.y ()/ysize*5);
                    UpdateStatus ("taking xy/xz rotation speed");
                } else {                                //  immediate movement
                    setm_LeftDownPos(point);              //  reset start position for next mouse move

                    setm_rotZ(m_rotZ() - rotate.x ()/xsize*180);    //  add xy rotation ( = z in 3D)
                    setm_rotY(m_rotY() - rotate.y ()/ysize*180);    //  add xz rotation ( = y in 3D)

                    UpdateStatus ("rotate xy/xz");
                }        //    if (TakingSpinValues)
            }            //    if (LeftButtonDown && !MidButtonDown && !RightButtonDown)

            //    rotate xw / yz with MMB
            if (!LeftButtonDown && MidButtonDown && !RightButtonDown) { //  SHIFT + MMB

                QPoint rotate = m_MidDownPos()-point;        //  store difference from button press position

                if (TakingSpinValues()) {
                    setdxw(dxw() + rotate.x ()/xsize*5);
                    setdx(dx() + rotate.y ()/ysize*5);
                    if (dxw() == 0.) ViewChanged = false;

                    UpdateStatus ("taking xw / yz rotation speed");
                } else {                             		//    immediate movement
                    setm_MidDownPos(point);     //    reset start position for next mouse move

                    setRxw(Rxw() - rotate.x ()/xsize*180);            		//    add xw rotation
                    setm_rotX(m_rotX() - rotate.y ()/ysize*180);            		//    add yz  ( = x in 3D) rotation
                    if (Rxw() == 0.) ViewChanged = false;

	            UpdateStatus ("rotate xw/yz");
	        }        	//    if (TakingSpinValues)

            }          	//    if (!LeftButtonDown && MidButtonDown && !RightButtonDown)

            //    rotate yw / zw with RMB
            if (!LeftButtonDown && !MidButtonDown && RightButtonDown) {    	//  SHIFT + RMB pressed

	        QPoint rotate = m_RightDownPos()-point;    		//    store difference from button press position

	        if (TakingSpinValues()) {                    		//
	            setdyw(dyw() + rotate.x ()/xsize*5);
                setdzw(dzw() + rotate.y ()/ysize*5);                    	//
	            UpdateStatus ("taking yw / zw rotation speed");
	        } else {                                    		//    immediate movement
                setm_RightDownPos(point);                		//    reset start position for next mouse move

                setRyw(Ryw() - rotate.x ()/xsize*180);            		//    add yw rotation
                setRzw(Ryw() - rotate.y ()/ysize*180);            		//    add zw rotation

	            UpdateStatus ("rotate yw/zw");
	        }        	//    if (TakingSpinValues)

            }            	//    if (!LeftButtonDown && !MidButtonDown && RightButtonDown)

        }                	//    if (LeftButtonDown || MidButtonDown || RightButtonDown)

    }                     	//    if (::GetKeyState (VK_SHIFT) < 0)

    if (ViewChanged) {                                    	//    4D viewpoint has changed
        SingletonLog::Instance().log("C4DView::mouseMoveEvent: View changed ()");

        Transform (Rxy(), Rxz(), Rxw(), Ryz(), Ryw(), Rzw(), Tx(), Ty(), Tz(), Tw());   //    apply the 4D transformation
        Redraw ();
    } else {					//    4D viewpoint didn't change

        if (LeftButtonDown || MidButtonDown) {		//  LMB or MMB without modifier

            double size = Size ();            	//    reference size for the translations

            //    pan the view with MMB
            if (MidButtonDown && !LeftButtonDown) {		//  MMB

	        QPoint translate = m_MidDownPos()-point;    		//    store difference from button press position

	        if (TakingSpinValues()) {    } else {        		//    no translation animation (yet?)
	            setm_MidDownPos(point);                			//    reset start position for next mouse move

                setm_transX(m_transX() - translate.x ()*size/xsize);    //    add x translation
                setm_transY(m_transY() + translate.y ()*size/ysize);    //    add y translation

	            UpdateStatus ("translate x/y");
	        }            	//    if (TakingSpinValues)

            }                	//    if (MidButtonDown && !LeftButtonDown)

            //    rotate the view with LMB
            if (LeftButtonDown && !MidButtonDown) {				//  LMB

	        QPoint rotate = m_LeftDownPos()-point;        		//    store difference from button press position

 	        if (TakingSpinValues()) {                    		//
                setdx(dx() + rotate.x ()/xsize*5);
                setdy(dy() + rotate.y ()/ysize*5);                    	//
	            UpdateStatus ("taking x/y rotation speed");
	        } else {                                    		//    immediate movement
	            setm_LeftDownPos(point);                		//    reset start position for next mouse move

                setm_rotX(m_rotX() - rotate.y ()/ysize*180);        		//    add x rotation
                setm_rotY(m_rotY() - rotate.x ()/xsize*180);        		//    add y rotation

	            UpdateStatus ("rotate x/y");
	        }            	//    if (TakingSpinValues)

            }                	//    if (LeftButtonDown && !MidButtonDown)

            //    zoom with LMB+RMB
            if (LeftButtonDown && MidButtonDown) {				//  LMB+RMB

                QPoint zoom = m_LeftDownPos()-point;        		//    store difference from button press position

                if (TakingSpinValues()) {                    		//
	            setdz(dz() + zoom.x ()/xsize*10);
	            UpdateStatus ("taking z rotation speed");
	        } else {                                    		//    immediate movement
	            setm_LeftDownPos(point);                		//    reset start position for next mouse move

                    if (zoom.x () != 0) {
                        setm_camZ(m_camZ() * (1+zoom.x ()/xsize));            //      scale camera z position
                        SetupDepthCue (DepthCue3D());
	            }
                setm_rotZ(m_rotZ() - zoom.y ()/ysize*180);        		//    add z rotation

	            UpdateStatus ("translate/rotate z");
	        }            	//    if (TakingSpinValues)

            }                	//    if (LeftButtonDown && MidButtonDown)


        }                   //    if (LeftButtonDown || MidButtonDown)

    }                     //    if (ViewChanged)

    OnPaint ();                					//    redraw the window
}

/// Mouse button event handler
/** Only sets flags which buttons are down
 *  @param e Qt's mouse event information structure                           */
void C4DView::mousePressEvent (QMouseEvent *e) {
    SingletonLog::Instance().log("C4DView::mousePressEvent ()");

    QPoint point = e->pos ();
    Qt::MouseButtons b = e->buttons();

    if ((b & Qt::LeftButton) != 0) {
        setm_LeftDownPos(point);
    }
    if ((b & Qt::MidButton) != 0) {
        setm_MidDownPos(point);
    }
    if ((b & Qt::RightButton) != 0) {
        setm_RightDownPos(point);
        Qt::KeyboardModifiers s = e->modifiers();
        bool AltPressed = s & Qt::AltModifier,
             ControlPressed = s & Qt::ControlModifier,
             ShiftPressed = s & Qt::ShiftModifier;
        if (b == Qt::RightButton && !(AltPressed || ControlPressed || ShiftPressed))
            menu()->exec (this->mapToGlobal(point));
//            XQGLWidget::mousePressEvent (e);
    }
}

/// Mouse button release event handler
/** If taking values for an animation, starts the animation
 *  @param e Qt's mouse event information structure                           */
void C4DView::mouseReleaseEvent ( QMouseEvent *e) {
    SingletonLog::Instance().log("C4DView::mouseReleaseEvent ()");

    Qt::MouseButtons b = e->buttons();

    if (TakingSpinValues()) {
        StartAnimation ();
        setTakingSpinValues(false);
    }

    UpdateStatus ("");
    if (b == Qt::RightButton) QGLWidget::mouseReleaseEvent (e);
}

/// Double click event handler
/** Stops animation, if running, or resets transformation values to default
 *  @param e Qt's mouse event information structure                           */
void C4DView::mouseDoubleClickEvent (QMouseEvent *e) {
    SingletonLog::Instance().log("C4DView::mouseDoubleClickEvent ()");

    if (Animated()) StopAnimation ();
    else {
        setTx(0); setTy(0); setTz(0); setTw(0);
        setRxy(0); setRxz(0); setRxw(0); setRyz(0); setRyw(0); setRzw(0);

        setm_rotX(15); setm_rotY(15); setm_rotZ(0);
        setm_transX(0); setm_transY(0);
        setm_camZ(-10);

        Transform (Rxy(), Rxz(), Rxw(), Ryz(), Ryw(), Rzw(), Tx(), Ty(), Tz(), Tw());
        Redraw ();                                    		//    implicit OnPaint ()
    }

    UpdateStatus ("DoubleClick");

    QGLWidget::mouseDoubleClickEvent (e);
}

/** paintEvent() */
void C4DView::paintEvent (QPaintEvent *) {
    OnPaint ();
}

/// Resizing routine
/** Also, the definition of the GL viewport is done here                      */
void C4DView::resizeEvent (QResizeEvent *e) {
    unsigned cx = e->size ().width (),
             cy = e->size ().height ();
    if (cx == 0 && cy == 0) return;             //  zero size window taken care of

    QGLWidget::resizeEvent (e);                //  window resizing

    GLsizei width = cx, height = cy;
    GLdouble aspect = GLdouble (width > 0? width: 1);   //  calculate aspect ratio
    if (height != 0) aspect /= GLdouble (height);

    glViewport (0, 0, width, height);           //  define the viewport
    glMatrixMode (GL_PROJECTION);               //  perspective view
    glLoadIdentity ();                          //  reset any transforms
    gluPerspective (45, aspect,                 //  set FOV, aspect,
                    .01*Size (),                //  front clipping plane
                    100.*Size ());              //  & back clipping plane

    glMatrixMode (GL_MODELVIEW);                //  return to model view
    glLoadIdentity ();                          //  reset

    glDrawBuffer (GL_BACK);                     //  dump the buffer
}

/// OpenGL initialization
/** Now this is not as boring as it seems, because further work has to be done
 *  here: \n
 *  \todo trying to check for rendering to file, but this doesn't work yet.
 *
 *  the rest of interesting inits is done in XQGLWidget::initializeGL (), btw.*/
void C4DView::initializeGL (void) {
    SingletonLog::Instance().log("C4DView::initializeGL ()");

    glEnable (GL_DEPTH_TEST);                   //  enable 3D mode, sotosay
    glEnable (GL_NORMALIZE);                    //  automatically normalize surface normals

    if (!doubleBuffer ())                       //  this should happen rarely if ever
        SingletonLog::Instance().log("Widget is single buffered");  //  complain but continue

    InitLight ();                               //  set up lighting parameters
    InitShade ();                               //  ... flat or gouraud shading
    InitFog ();                                 //  ... depth cue or not
    InitTransparence ();                        //  ... transparence

    glDisable (GL_CULL_FACE);                           //  disable face culling

    float *background = Globals::Instance().BackgroundColor();
    //  set background color
    glClearColor (background[0], background[1], background[2], background[3]);

    if (RenderToPixmap() /* && CurrentlyRendering */ ) {
        SingletonLog::Instance().log("  render to pixmap = true");

        PreRedraw ();

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //  clear the window

        if (DisplayPolygons())                            //  this might move to a
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //  special routine "SwitchWireframe()"
        else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glPushMatrix();                                 //  save the transformation Matrix
        // glTranslated(0.0, /*Size ()*.75*/0., 0);     //  set the camera position

        glTranslated (m_transX(), m_transY(), m_camZ());      //  apply object translation
        glRotated(m_rotX(), 1.0, 0.0, 0.0);               //   -"-    -"-     rotation
        glRotated(m_rotY(), 0.0, 1.0, 0.0);
        glRotated(m_rotZ(), 0.0, 0.0, 1.0);


        SingletonLog::Instance().log("  RenderScene");
        RenderScene (0);                                //  draw current frame

        glPopMatrix();                                  //  restore transformation Matrix
    }
    SingletonLog::Instance().log("C4DView::initializeGL() done");
}

/** OpenGL initialization
 *  setting background colors, setting up lighting, shading, fog and
 *  transparence
 *  @todo hardcoded light position and colors!                                */
void C4DView::InitLight (void) {
    if (getLight()) {
        glEnable(GL_LIGHTING);                          //  enable lighting
        //  compute specular reflections from origin of eye coordinate system
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
        glLightfv(GL_LIGHT0, GL_POSITION, LightPos);    //  set light position
        glLightfv(GL_LIGHT0, GL_DIFFUSE,
                  Globals::Instance().white());         //  diffuse color
        glLightfv(GL_LIGHT0, GL_AMBIENT,
                  Globals::Instance().grey50());        //  ambient color
        glEnable(GL_LIGHT0);                            //  enable this light
    } else {
        glDisable(GL_LIGHTING);                         //  disable lighting
    }
}

void C4DView::InitShade (void) {
    if (getShade()) glShadeModel (GL_SMOOTH);        //  gouraud shading
    else            glShadeModel (GL_FLAT);          //  flat shading
}

void C4DView::InitFog  (void) {
    if (getFog()) {
        glEnable (GL_FOG);                      //  enable depth cueing
        SetupDepthCue(
            fabs(m_camZ())-Size()/2.,
            fabs(m_camZ())+Size()/2.*Globals::Instance().SR3);
    } else
        glDisable (GL_FOG);                     //  disable depth cueing
}

void C4DView::InitTransparence (void) {
    if (getTransparent()) {
        glEnable  (GL_BLEND);                               //  enable blending
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //  blending function
        glEnable  (GL_POINT_SMOOTH);                        //  draw smooth points
        glEnable  (GL_LINE_SMOOTH);                         //  draw smooth lines
        glEnable  (GL_POLYGON_SMOOTH);                      //  draw smooth surfaces
//        glDisable (GL_CULL_FACE);                           //  ...why?             *
    } else {
        glDisable (GL_BLEND);                               //  disable blending
        glDisable  (GL_POINT_SMOOTH);                       //  ..
        glDisable (GL_LINE_SMOOTH);                         //  ..
        glDisable (GL_POLYGON_SMOOTH);                      //  ..
//        glEnable  (GL_CULL_FACE);                           //                      *
    }
}

/** change of viewing distance is handled here too, which is not so clean
 *  programming style...
    \todo eliminate hardcoded constants                                       */
void C4DView::resizeGL (int width, int height) {
    GLfloat aspect = (float) width / (float) height,
            angle  = .8*atan (2./R())*180./pi,
            across = Globals::Instance().SR3;
    if (angle < 0) angle = 180+angle;           //  keep positive viewing angle

    glViewport (0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (angle, aspect, .25, R()+across);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0., 0., 1.,
	       0., 0., 0.,
	       0., 1., 0.);
    glTranslatef (0, 0, -R());
    if (getFog())
        SetupDepthCue(
            fabs(m_camZ())-Size()/2.,
            fabs(m_camZ())+Size()/2.*Globals::Instance().SR3);
}
