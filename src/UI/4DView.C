
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
#include "MouseHandler.H"
#include "AnimationDialogImpl.H"
#include "Help.H"

#include "Globals.H"
#include "Log.H"
#include "ColorManager.H"

#include "Matrix.H"
#include "Rotation.H"

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
using VecMath::Rotation;
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

    setMenu(new Menu4D(this));
    Menu()->addToMenuBar(Globals::Instance().getMainWindow()->menuBar());

    setMouseHandler(new MouseHandler4D(this));

    show ();

    ColMgrMgr::Instance().setColorManager(new xyz2RGBColorManager(F().get()));

    ObjectHypercube ();

    Light ();
}

/// C4DView destructor
C4DView::~C4DView() { }

/// Switch between wireframe and solid display
/** Account for antialiasing only in wireframe mode
 *
 *  Change menu items accordingly
 *
 *  Menu callback function                                                    */
void C4DView::Wireframe() {
    if (DisplayPolygons()) {
        Menu()->getAction("Wireframe")->setText("Solid");
        Menu()->getAction("Transparence")->setText("Line Antialiasing");
    } else {
        Menu()->getAction("Wireframe")->setText("Wireframe");
        Menu()->getAction("Transparence")->setText("Transparence");
        glDisable (GL_CULL_FACE);
    }
    Menu()->getAction("Wireframe")->setChecked (DisplayPolygons());
    setWireframe (DisplayPolygons());

    OnPaint ();
}

/// Switch coordinate cross on or off
/** Change menu items accordingly
 *
 *  Menu callback function */
void C4DView::Coordinates() {
    setDisplayCoordinates(!DisplayCoordinates());
    Menu()->getAction("Coordinate Cross")->setChecked (DisplayCoordinates());

    Redraw ();
}

/// Switch 4D depth cue on or off
/** Change menu items accordingly
 *
 *  Menu callback function */
void C4DView::HyperFog() {
    setDepthCue4D(!DepthCue4D());
    Menu()->getAction("4D Depth Cue")->setChecked (DepthCue4D());

    Redraw ();
}

/// Switch lighting on or off
/** Change menu items accordingly
 *
 *  Menu callback function */
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
    Menu()->getAction("Colors")->setChecked(getColors());
    initializeGL ();
    repaint (); }

/// Toggle fog/depth cue
/** menu callback function */
void C4DView::Fog () {
  getFog() = !getFog();
  Menu()->getAction("Depth Cue")->setChecked(getFog());
  InitFog ();
  repaint (); }

/// toggle object transparency
/** menu callback function */
void C4DView::Transparent () {
    getTransparent() = !getTransparent();
    Menu()->getAction("Transparence")->setChecked(getTransparent());
    InitTransparence ();
    repaint ();
}

/// toggle shading
/** menu callback function */
void C4DView::Shade () {
    getShade() = !getShade();
    Menu()->getAction("Shading")->setChecked(getShade());
    InitShade ();
    repaint ();
}

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

/// Switch rendering to files on or off
/** Change menu items accordingly
 *
 *  Menu callback function */
void C4DView::RenderToImages() {
  setRenderToPixmap(!RenderToPixmap());
  Menu()->getAction("Render to Images")->setChecked(RenderToPixmap());
}

/// Display a ObjectHypercube object
/** Menu callback function */
void C4DView::ObjectHypercube() {
    Menu()->updateFunctionMenu("Hypercube");

    setF(new Hypercube (/*Values()->a ()*/));

    AssignValues(F());
    Redraw ();
}

/// Display a ObjectHyperpyramid object
/** Menu callback function */
void C4DView::ObjectHyperpyramid() {
    Menu()->updateFunctionMenu("Hyperpyramid");

    setF(new Pyramid (/*2.*Values()->a ()*/));

    AssignValues(F());
    Redraw ();
}

/// display a ObjectHypersponge object
/** menu callback function */
void C4DView::ObjectHypersponge() {
    Menu()->updateFunctionMenu("Menger Sponge");

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
    Menu()->updateFunctionMenu("Sierpinski Gasket");

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

    Vector<3> step(step_x, step_y, step_z);
//    double Rx = m_rotX(), Ry = m_rotY(), Rz = m_rotZ();
    Rotation<3> R = m_rot();

    for (int step = 0; step < num_steps; step++) {
        addm_rot(step);
//        setm_rotX(m_rotX() + step_x); setm_rotY(m_rotY() + step_y); setm_rotZ(m_rotZ() + step_z);
        if (display) {
            OnPaint ();
            UpdateStatus (QString::number ((100*step)/num_steps)+"% done");
        }
    }
    setm_rot(R);

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
    Transform (VecMath::Rotation<4>(0., 0. ,Rxw, 0. , Ryw, Rzw),
               VecMath::Vector<4>(0., 0., 0., 0.));
    if (display) {
      Redraw ();
      UpdateStatus (QString::number ((100*step)/num_steps)+"% done");
    }
  }

  return double (clock ()-stime)/CLOCKS_PER_SEC;
}

/// Timer event handler
/** Updates values if in the middle of an animation, and renders an image.
 *
 *  Writes image to file too, if wanted.                                      */
void C4DView::OnTimer() {

    addm_rot(dR3());
//    setm_rotX(m_rotX() + dT()[0]); setm_rotY(m_rotY() + dT()[1]); setm_rotZ(m_rotZ() + dT()[2]);   //  update 3D viewpoint values

    SingletonLog::Instance() << "C4DView::OnTimer()\n"
            << "  dT = " << dR3() << "\n"
            << "  dR = " << dR() << "\n";

    if (dR()) {     //  4D viewpoint animated?

        addR(dR());

        Transform (R(), T());   // transform
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
/** Where to write image files and how many files to write.
 *
 *  Menu callback function */
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
                             << "  Parms = " << parms.print() << "\n"
                             << "  Values = " << Values()->print() << "\n";

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
 *  @param R rotation
 *  @param T translation                                                      */
void C4DView::Transform(const VecMath::Rotation<4> &R,
                        const VecMath::Vector<4> &T) {
    if (F().get()) { F()->Transform (R, T); }
    else { return; }

    Matrix<4> Rot(R);
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 2; j++)
            CrossTrans[i][j] = (Rot*Cross[i][j])+T;
}

/// Projects F and coordinate cross into three-space
/** */
void C4DView::Project(void) {
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

/// 4D projection stuff
/** Separated from the 3D OpenGL handling into this function
 *  \todo either PreRedraw() or Draw() should call DrawCoordinates(), but not
 *        both                                                                */
void C4DView::PreRedraw () {
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
        F()->Draw ();

    glEndList ();
}

/// Redraw handler
void C4DView::Redraw () {
  PreRedraw ();
  OnPaint ();
}

/// Wrapper for redraw handler
/** With an error reporting routine and exit strategy */
void C4DView::RenderScene (unsigned /* Frame */) {  //  draw (frame of animation)
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
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //  clear the window

    if (DisplayPolygons())                            //  this might move to a special
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //  routine "SwitchWireframe ()"
    else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPushMatrix();                                 //  save transformation Matrix
    // glTranslated(0.0, /*Size ()*.75*/0., 0);     //  set the camera position

    glTranslated (m_trans()[0], m_trans()[1], m_trans()[2]);      //  apply object translation
    glRotated(m_rot()[0], 1.0, 0.0, 0.0);               //   -"-    -"-     rotation
    glRotated(m_rot()[1], 0.0, 1.0, 0.0);
    glRotated(m_rot()[2], 0.0, 0.0, 1.0);

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
        cerr << "m_camZ(): " << m_trans()[2] << endl;
        SetupDepthCue(
            fabs(m_trans()[2])-Size()/2.,
            fabs(m_trans()[2])+Size()/2.*Globals::Instance().SR3);
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
    if (!dR3() && !dR()) {
        return;
    }

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
    setdR(VecMath::Rotation<4>());
    setdR3(VecMath::Rotation<3>());
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

    setdR(VecMath::Rotation<4>(0.,0.,double(rand ())/RAND_MAX,0.,double(rand ())/RAND_MAX,double(rand ())/RAND_MAX));
    StartAnimation ();

    AnimateRandomTimer()->start (10000);
}

/// Make a pixmap to to be rendered by the GL widget, and render it.
/** This is an embarrassing workaround to make rendering to files work.
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

/** Writes a snapshot of the current frame of an animation or interactive
 *  display to disk.
 *  Updates animationFrame                                                    */
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
    if (m_rot()[0] > 360) addm_rot(Rotation<3>(-360.,0.,0.));
    if (m_rot()[0] <-360) addm_rot(Rotation<3>( 360.,0.,0.));
    if (fabs (m_rot()[0]) < 1e-3)  setm_rot(Rotation<3>(0., m_rot()[1], m_rot()[2]));
    if (m_rot()[1] > 360) addm_rot(Rotation<3>(0.,-360.,0.));
    if (m_rot()[1] <-360) addm_rot(Rotation<3>(0., 360.,0.));
    if (fabs (m_rot()[1]) < 1e-3)  setm_rot(Rotation<3>(m_rot()[0], 0., m_rot()[2]));
    if (m_rot()[2] > 360) addm_rot(Rotation<3>(0.,0.,-360.));
    if (m_rot()[2] <-360) addm_rot(Rotation<3>(0.,0., 360.));
    if (fabs (m_rot()[2]) < 1e-3) setm_rot(Rotation<3>(m_rot()[0], m_rot()[1], 0.));
    if (R()[2] > 360) addR(Rotation<4>(0.,0.,-360.,0.,0.,0.));
    if (R()[2] <-360) addR(Rotation<4>(0.,0., 360.,0.,0.,0.));
    if (R()[4] > 360) addR(Rotation<4>(0.,0.,0.,0.,-360.,0.));
    if (R()[4] <-360) addR(Rotation<4>(0.,0.,0.,0., 360.,0.));
    if (R()[5] > 360) addR(Rotation<4>(0.,0.,0.,0.,0.,-360.));
    if (R()[5] <-360) addR(Rotation<4>(0.,0.,0.,0.,0., 360.));
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
/** Delegates to MouseHandler4D::mouseMoveEvent()                             */
void C4DView::mouseMoveEvent(QMouseEvent *e) {
    MouseHandler()->mouseMoveEvent(e);
}

/// Mouse press event handler
/** Delegates to MouseHandler4D::mousePressEvent()                            */
void C4DView::mousePressEvent(QMouseEvent *e) {
    MouseHandler()->mousePressEvent(e);
}

/// Mouse release event handler
/** Delegates to MouseHandler4D::mouseReleaseEvent()                          */
void C4DView::mouseReleaseEvent(QMouseEvent *e) {
    MouseHandler()->mouseReleaseEvent(e);
}

/// Double click event handler
/** Delegates to MouseHandler4D::mouseDoubleClickEvent()                      */
void C4DView::mouseDoubleClickEvent(QMouseEvent *e) {
    MouseHandler()->mouseDoubleClickEvent(e);
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
 *  here.
 *  \todo trying to check for rendering to file, but this doesn't work yet.
 *  \todo clean up, check what is really needed - in particular it calls
 *        PreRedraw() twice, once via RenderScene()                           */
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

    glDisable (GL_CULL_FACE);                   //  disable face culling

    float *background = Globals::Instance().BackgroundColor();
    //  set background color
    glClearColor (background[0], background[1], background[2], background[3]);

    if (RenderToPixmap() /* && CurrentlyRendering */ ) {
        SingletonLog::Instance().log("  render to pixmap = true");

        PreRedraw ();

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //  clear the window

        if (DisplayPolygons())                          //  this might move to a
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //  special routine
        else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //  "SwitchWireframe()"

        glPushMatrix();                         //  save the transformation Matrix
        // glTranslated(0.0, /*Size ()*.75*/0., 0);     //  set the camera position

        glTranslated (m_trans()[0], m_trans()[1], m_trans()[2]);    //  apply object translation
        glRotated(m_rot()[0], 1.0, 0.0, 0.0);   //   -"-    -"-     rotation
        glRotated(m_rot()[1], 0.0, 1.0, 0.0);
        glRotated(m_rot()[2], 0.0, 0.0, 1.0);


        SingletonLog::Instance().log("  RenderScene");
        RenderScene (0);                        //  draw current frame

        glPopMatrix();                          //  restore transformation Matrix
    }
    SingletonLog::Instance().log("C4DView::initializeGL() done");
}

/// OpenGL initialization for light(s)
/** @todo hardcoded light position and colors!                                */
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

/// OpenGL initialization for shading (gouraud or flat shading)
void C4DView::InitShade (void) {
    if (getShade()) glShadeModel (GL_SMOOTH);        //  gouraud shading
    else            glShadeModel (GL_FLAT);          //  flat shading
}

/// OpenGL initialization for fog
void C4DView::InitFog  (void) {
    if (getFog()) {
        glEnable (GL_FOG);                      //  enable depth cueing
        SetupDepthCue(
            fabs(m_trans()[2])-Size()/2.,
            fabs(m_trans()[2])+Size()/2.*Globals::Instance().SR3);
    } else
        glDisable (GL_FOG);                     //  disable depth cueing
}

/// OpenGL initialization for transparence
/** @todo is GL_CULL_FACE needed or not?                                      */
void C4DView::InitTransparence (void) {
    if (getTransparent()) {
        glEnable  (GL_BLEND);                               //  enable blending
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //  blending function
        glEnable  (GL_POINT_SMOOTH);                        //  draw smooth points
        glEnable  (GL_LINE_SMOOTH);                         //  draw smooth lines
        glEnable  (GL_POLYGON_SMOOTH);                      //  draw smooth surfaces
//        glDisable (GL_CULL_FACE);                           //  ...why?            *
    } else {
        glDisable (GL_BLEND);                               //  disable blending
        glDisable  (GL_POINT_SMOOTH);                       //  ..
        glDisable (GL_LINE_SMOOTH);                         //  ..
        glDisable (GL_POLYGON_SMOOTH);                      //  ..
//        glEnable  (GL_CULL_FACE);                           //                     *
    }
}

/** change of viewing distance is handled here too, which is not so clean
 *  programming style...
    \todo eliminate hardcoded constants                                       */
void C4DView::resizeGL (int width, int height) {
    GLfloat aspect = (float) width / (float) height,
            angle  = .8*atan (2./distance())*180./pi,
            across = Globals::Instance().SR3;
    if (angle < 0) angle = 180+angle;           //  keep positive viewing angle

    glViewport (0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (angle, aspect, .25, distance()+across);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0., 0., 1.,
               0., 0., 0.,
               0., 1., 0.);
    glTranslatef (0, 0, -distance());
    if (getFog())
        SetupDepthCue(
            fabs(m_trans()[2])-Size()/2.,
            fabs(m_trans()[2])+Size()/2.*Globals::Instance().SR3);
}
