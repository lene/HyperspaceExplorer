
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

std::string  C4DView::_helpFile = "Hyperspace_Explorer_Help.html";

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
    ViewImpl(),

    _rot(15., 15., 0.), _trans(0., 0.,-10.),

    _animationFrame(0),
    _animationMaxFrames((unsigned)-1),
    _animation_fps (50),

    _animated (false), _currentlyRendering (false),

    _objectList (0), _coordinateCross (0),

    _values (new UI::Dialogs::ValuesDialogImpl(this)) {

    InitCross();

    setAnimationTimer(new QTimer(this));
    connect (AnimationTimer(), SIGNAL(timeout()), this, SLOT(OnAnimationTimer()));

    setAnimateRandomTimer(new QTimer (this));

    connect (Values(), SIGNAL (ApplyChanges (const ParameterMap &)),
             this, SLOT (ApplyChanges (const ParameterMap &)));

    setMenu(new Menu4D(this));
    Menu()->addToMenuBar(Globals::Instance().getMainWindow()->menuBar());

    setMouseHandler(new MouseHandler4D(this));

    show();

    ColMgrMgr::Instance().setColorManager(new xyz2RGBColorManager(F().get()));

    ObjectHypercube();

    setLighting(true);
}

/// C4DView destructor
C4DView::~C4DView() { }

////////        Implementations of the View interface        ////////

void C4DView::ObjectHypercube() {
    Menu()->updateFunctionMenu("Hypercube");

    setF(new Hypercube ());

    AssignValues(F());
    Redraw ();
}

void C4DView::ObjectHyperpyramid() {
    Menu()->updateFunctionMenu("Hyperpyramid");

    setF(new Pyramid ());

    AssignValues(F());
    Redraw ();
}

void C4DView::ObjectHypersponge() {
    Menu()->updateFunctionMenu("Menger Sponge");

    setF(new Sponge ());

    AssignValues(F());
    Redraw ();
}

void C4DView::ObjectGasket() {
    Menu()->updateFunctionMenu("Sierpinski Gasket");

    setF(new Gasket ());

    AssignValues(F());
    Redraw ();
}

void C4DView::applyTransform(const VecMath::Rotation<4> &R,
                             const VecMath::Vector<4> &T) {
    Transform(R, T);
    Redraw();
}

void C4DView::animate() {
    for (unsigned i = 0; i < getNumLoops(); i++) {
        for (unsigned i = 0; i < getNumFrames(); i++) {
            addR(getdR());
            SingletonLog::Instance() << R() << "\n";
            Transform(R(), VecMath::Vector<4>());
            Project();
            Redraw();
        }
    }
}

void C4DView::setSize(unsigned w, unsigned h) {
    Globals::Instance().getMainWindow()->resize(w, h);
}

void C4DView::setBackground(const Color &col) {
    glClearColor (col.r(), col.g(), col.b(), col.a());
    if (glIsList (ObjectList())) paintEvent();
}

void C4DView::setColors(bool cols) {
    ViewImpl::setColors(cols);
    initializeGL ();
    repaint ();
}

void C4DView::setCoordinates(bool coords) {
    ViewImpl::setCoordinates(coords);
    Project();
    Redraw();
}

void C4DView::setFog(bool fog) {
    ViewImpl::setFog(fog);
    InitFog ();
    repaint ();
}

void C4DView::setHyperfog(bool fog) {
    ViewImpl::setHyperfog(fog);
    Project();
    Redraw ();
}

void C4DView::setLighting(bool light) {
    ViewImpl::setLighting(light);

    if (getLighting()) {
        LightOpenGL light(ViewImpl::getDefaultLightSource());
        light.render();
    } else {
#       if 1
            LightOpenGL light(ViewImpl::getFlatLightSource());
            light.render();
#       else
            glDisable(GL_LIGHTING);
#       endif
    }

    paintEvent ();
}

void C4DView::setShading(bool shade) {
    ViewImpl::setShading(shade);
    InitShade ();
    repaint ();
}

void C4DView::setTransparence (bool trans) {
    ViewImpl::setTransparence(trans);
    InitTransparence();
    repaint ();
}

////////        end View interface          ////////

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
            paintEvent ();
            UpdateStatus (QString::number ((100*step)/num_steps)+"% done");
        }
    }
    setm_rot(R);

  return double (clock ()-stime)/CLOCKS_PER_SEC;
}

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

/** Updates values if in the middle of an animation, and renders an image.
 *
 *  Writes image to file too, if wanted.                                      */
void C4DView::OnAnimationTimer() {

//    addm_rot(dR3());
//    setm_rotX(m_rotX() + dT()[0]); setm_rotY(m_rotY() + dT()[1]); setm_rotZ(m_rotZ() + dT()[2]);   //  update 3D viewpoint values

    SingletonLog::Instance() << "C4DView::OnAnimationTimer()\n"
//            << "  dR3 = " << dR3() << "\n"
            << "  dR = " << getdR() << "\n";

    if (getdR()) {     //  4D viewpoint animated?

        addR(getdR());

        Transform (R(), T());   // transform
        Redraw ();                                                  // implicit paintEvent()
    } else paintEvent ();                                              // explicit paintEvent()

    writeFrame();   //  if render to pixmap is selected, do it

    UpdateStatus (QString("Animation: Frame %1").arg(animationFrame())
                +(animationMaxFrames() > 0 && animationMaxFrames() < (unsigned)(-1)?
                QString("/%1").arg(animationMaxFrames()):
                QString(""))
                +" - Double-click LMB to stop");
}

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
            _crossTrans[i][j] = (Rot*_cross[i][j])+T;
}

/** Four-dimensional transform is set to no rotation, no translation.
 *
 *  Three-dimensional transform is 15 degrees about x and y axis, and
 *  10 units distance from the camera.                                */
void C4DView::Transform() {
    setT(VecMath::Vector<4>());
    setR(VecMath::Rotation<4>());

    setm_rot(VecMath::Rotation<3, GLdouble>(15., 15., 0.));
    setm_trans(VecMath::Vector<3, GLdouble>(0.,0.,-10.));

    Transform (R(), T());   //  apply 4D transformation
}

/** Projects F and coordinate cross into three-space */
void C4DView::Project(void) {
    if (F().get()) F()->Project (ScrW(), CamW(), getHyperfog());
    else return;

    if (getCoordinates()) {
        for (unsigned i = 0; i < 2; i++)
            for (unsigned j = 0; j < 4; j++) {
                double ProjectionFactor = (ScrW()-CamW())/(_crossTrans[j][i][3]-CamW());
                for (unsigned k = 0; k < _crossScr[j][i].dimension(); k++)
                    _crossScr[j][i][k] = _crossTrans[j][i][k]*ProjectionFactor;
            }
    }
}

/** Separated from the 3D OpenGL handling into this function
 *  \todo either PreRedraw() or Draw() should call DrawCoordinates(), but not
 *        both                                                                */
void C4DView::PreRedraw () {
    // this does seem very ineffective to me, deleting and reassigning the GL Lists,
    // but it does not seem to work any other way...?

    if (getCoordinates()) {
        if (CoordinateCross()) glDeleteLists (CoordinateCross(), 1);
        setCoordinateCross(Globals::Instance().GetGLList());
        glNewList (CoordinateCross(), GL_COMPILE);
            DrawCoordinates();
        glEndList();
    }

    if (ObjectList()) glDeleteLists(ObjectList(), 1);
    setObjectList(Globals::Instance().GetGLList());
    glNewList (ObjectList(), GL_COMPILE_AND_EXECUTE);
        Project ();
        F()->Draw ();
    glEndList ();
}

/** Draws the projected Function into GL display lists, and then draws those
 *  lists onto the screen                                                     */
void C4DView::Redraw () {
  PreRedraw ();
  paintEvent ();
}

/** Execute GL display lists, with error reporting and an exit strategy       */
void C4DView::RenderScene () {  //  draw (frame of animation)
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

    glCallList(ObjectList());                                //  draw the object
    if (getCoordinates()) glCallList(CoordinateCross());
}


void C4DView::InitCross() {
    _cross = vector<vector<Vector<4> > > (4);
    _crossTrans = vector<vector<Vector<4> > > (4);
    _crossScr = vector<vector<Vector<3> > > (4);;
    for (unsigned j = 0; j < 4; j++) {
        _cross[j].resize(2);
        _crossTrans[j].resize(2);
        _crossScr[j].resize(2);
        for (unsigned k = 0; k < 2; k++) {
            //  CrossTrans[j][k] = Vector (4, 0., 0., 0., 0.);
            _crossScr[j][k] = Vector<3> (0., 0., 0.);
        }
    }
    _cross[0][0] = Vector<4>(-5., 0., 0., 0.);
    _cross[0][1] = Vector<4>( 5., 0., 0., 0.);
    _cross[1][0] = Vector<4>(0., -5., 0., 0.);
    _cross[1][1] = Vector<4>(0.,  5., 0., 0.);
    _cross[2][0] = Vector<4>(0., 0., -5., 0.);
    _cross[2][1] = Vector<4>(0., 0.,  5., 0.);
    _cross[3][0] = Vector<4>(0., 0., 0., -5.);
    _cross[3][1] = Vector<4>(0., 0., 0.,  5.);
}

/// Switch 3D depth cue on and off
/** @param on whether to use fog                                              */
void C4DView::SetupDepthCue (bool on) {
    ViewImpl::setFog(on);
    if (on) {
        SingletonLog::Instance() << "m_camZ(): " << m_trans()[2] << "\n";
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
    glFogf (GL_FOG_START, std::max(dist-size/2., 0.));         //  ...
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
                Globals::Instance().glVertex (_crossScr[j][i]);
        glEnd ();
    }
}

/// Err well.. just that!
/** Starts AnimationTimer, too...                                             */
void C4DView::StartAnimation () {
    if (/*!dR3() &&*/ !getdR()) {
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
    AnimationTimer()->stop ();
    AnimateRandomTimer()->stop ();
    setCurrentlyRendering(false);
}

/// Starts a random animation
/** xw/yw/zw rotation speed changes every 10 seconds
 *  @todo make hardcoded duration of rotation change frequency adjustable
 *  @todo a menu entry for this                                               */
void C4DView::RandomAnimation(bool start) {
    if (start) {
        AnimationTimer()->stop ();
        AnimateRandomTimer()->stop ();

        setdR(VecMath::Rotation<4>(0.,0.,double(rand ())/RAND_MAX,0.,double(rand ())/RAND_MAX,double(rand ())/RAND_MAX));
        StartAnimation ();

        AnimateRandomTimer()->start (10000);
    } else {
        disconnect(this, SLOT(RandomAnimation()));
    }
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
    if (getWriteImages() && (animationFrame() <= animationMaxFrames())) {

        setCurrentlyRendering(true);

        PreRedraw ();

        QPixmap tmpPixmap = makePixmap();

        unsigned animationCiphers = animationMaxFrames() > 0?
                (unsigned)(log((double)animationMaxFrames())/log(10.))+1: 6;
        QString imageFilename =
                QString (
                         QString(getImgDir().c_str())+"/"+
                         QString(getImgPrefix().c_str())+"%1.png")
                .arg (animationFrame(), animationCiphers)
                .replace (" ", "0");
        if (tmpPixmap.save (imageFilename, "PNG")) {
            SingletonLog::Instance() << "writing "
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
    Transform();

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

/** Delegates to MouseHandler4D::mouseMoveEvent()                             */
void C4DView::mouseMoveEvent(QMouseEvent *e) {
    MouseHandler()->mouseMoveEvent(e);
}

/** Delegates to MouseHandler4D::mousePressEvent()                            */
void C4DView::mousePressEvent(QMouseEvent *e) {
    MouseHandler()->mousePressEvent(e);
}

/** Delegates to MouseHandler4D::mouseReleaseEvent()                          */
void C4DView::mouseReleaseEvent(QMouseEvent *e) {
    MouseHandler()->mouseReleaseEvent(e);
}

/** Delegates to MouseHandler4D::mouseDoubleClickEvent()                      */
void C4DView::mouseDoubleClickEvent(QMouseEvent *e) {
    MouseHandler()->mouseDoubleClickEvent(e);
}

/** Paint event handler and object drawing routine: called whenever the object
 *  is transformed, Does all the OpenGL stuff necessary to paint the object on
 *  screen
 */
void C4DView::paintEvent (QPaintEvent *) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //  clear the window

    if (getSolid())                              //  this might move to a special
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      //  routine "SwitchWireframe ()"
    else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPushMatrix();                                 //  save transformation Matrix
    // glTranslated(0.0, /*Size ()*.75*/0., 0);     //  set the camera position

    glTranslated (m_trans()[0], m_trans()[1], m_trans()[2]);      //  apply object translation
    glRotated(m_rot()[0], 1.0, 0.0, 0.0);               //   -"-    -"-     rotation
    glRotated(m_rot()[1], 0.0, 1.0, 0.0);
    glRotated(m_rot()[2], 0.0, 0.0, 1.0);

    RenderScene ();                                //  draw current frame

    glPopMatrix();                                  //  restore transformation Matrix

    swapBuffers ();                                 //  swap the buffers
}

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

/** Now this is not as boring as it seems, because further work has to be done
 *  here: Set up lights, shading, depth cue and transparence, wireframe mode,
 *  background, and position the object wrt the camera.
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

    setDefaultBackground();

    if (getWriteImages() /* && CurrentlyRendering */ ) {
        SingletonLog::Instance().log("  render to pixmap = true");

        PreRedraw ();

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //  clear the window

        if (getSolid())                          //  this might move to a
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //  special routine
        else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //  "SwitchWireframe()"

        glPushMatrix();                         //  save the transformation Matrix
        // glTranslated(0.0, /*Size ()*.75*/0., 0);     //  set the camera position

        glTranslated (m_trans()[0], m_trans()[1], m_trans()[2]);    //  apply object translation
        glRotated(m_rot()[0], 1.0, 0.0, 0.0);   //   -"-    -"-     rotation
        glRotated(m_rot()[1], 0.0, 1.0, 0.0);
        glRotated(m_rot()[2], 0.0, 0.0, 1.0);


        SingletonLog::Instance().log("  RenderScene");
        RenderScene ();                        //  draw current frame

        glPopMatrix();                          //  restore transformation Matrix
    }
    SingletonLog::Instance().log("C4DView::initializeGL() done");
}

/// OpenGL initialization for light(s)
void C4DView::InitLight (void) {
    if (getLighting()) {
        glEnable(GL_LIGHTING);                          //  enable lighting
        //  compute specular reflections from origin of eye coordinate system
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
#       if 0
        glLightfv(GL_LIGHT0, GL_POSITION, getLightPos());    //  set light position
        glLightfv(GL_LIGHT0, GL_DIFFUSE,
                  Globals::Instance().white());         //  diffuse color
        glLightfv(GL_LIGHT0, GL_AMBIENT,
                  Globals::Instance().grey50());        //  ambient color
        glEnable(GL_LIGHT0);                            //  enable this light
#       else
        LightOpenGL light(ViewImpl::getDefaultLightSource());
        light.render();
#       endif
    } else {
        glDisable(GL_LIGHTING);                         //  disable lighting
    }
}

/// OpenGL initialization for shading (gouraud or flat shading)
void C4DView::InitShade (void) {
    if (getShading()) glShadeModel (GL_SMOOTH);        //  gouraud shading
    else              glShadeModel (GL_FLAT);          //  flat shading
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
void C4DView::InitTransparence (void) {
    if (getTransparence()) {
        glEnable (GL_BLEND);                               //  enable blending
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //  blending function
        glEnable (GL_POINT_SMOOTH);                        //  draw smooth points
        glEnable (GL_LINE_SMOOTH);                         //  draw smooth lines
        glEnable (GL_POLYGON_SMOOTH);                      //  draw smooth surfaces
        glDisable(GL_CULL_FACE);                           //  draw both sides of faces
    } else {
        glDisable(GL_BLEND);                               //  disable blending
        glDisable(GL_POINT_SMOOTH);                       //  ..
        glDisable(GL_LINE_SMOOTH);                         //  ..
        glDisable(GL_POLYGON_SMOOTH);                      //  ..
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
