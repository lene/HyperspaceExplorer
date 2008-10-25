//
// C++ Implementation: C4DView::Menu4D
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <map>
#include <sstream>

#include <QShortcut>
#include <QMenuBar>
#include <QColorDialog>

#include "Menu4D.H"
#include "4DView.H"
#include "Globals.H"
#include "RealFunction.H"
#include "SlotHelper.H"
#include "AnimationDialogImpl.H"
#include "Help.H"

using std::ostringstream;
using std::endl;
using std::ends;

/// Disables menu entry if preprocessor variable TESTFEATURES is unset
inline void TESTED_FEATURE(QAction *item) {
# ifdef TESTFEATURES
    item->setEnabled (true);
# else
    item->setEnabled (false);
#endif
}

/** This Constructor is where the menu structure is defined; if you want to
 *  change the menu, do it here.
 *
 *  Basically this happens by inserting all the menu items and the QActions they
 *  trigger manually. The application of TemplatedRealFunctionFactory<Function>
 *  as Factory object helps to save a lot of redundant code, but still every
 *  menu item must be specified manually.
 */
C4DView::Menu4D::Menu4D(C4DView *_parent):
    m_parent(_parent) {

    functions = addMenu(tr("Object"));
    appear = addMenu(tr("Appearance"));
    animation = addMenu(tr("Animation"));
    help = addMenu(tr("Help"));

    ////////////////////////////////////////////////////////////////////////////
    //      "Objects" Menu
    ////////////////////////////////////////////////////////////////////////////
    {
        fr3r = functions->addMenu("f: R³ -> R");
        objects = functions->addMenu("Objects");
        surfaces = functions->addMenu("Surfaces");
        fcc = surfaces->addMenu("f: C -> C");
        {
            insertAction(fr3r, "1/(r²+1)",
                         new C4DView::TemplatedRealFunctionFactory<Fr3r>);
            insertAction(fr3r, "Gravitation Potential",
                         new C4DView::TemplatedRealFunctionFactory<GravitationPotential>);
            insertAction(fr3r, "sin (r²)",
                         new C4DView::TemplatedRealFunctionFactory<Fr3rSin>);
            insertAction(fr3r, "exp (r²)",
                         new C4DView::TemplatedRealFunctionFactory<Fr3rExp>);
            insertAction(fr3r, "Custom function", SLOT(customFunction()));
            insertAction(fr3r, "Polar: r = sin (pi/3.*(t+u+v))",
                         new C4DView::TemplatedRealFunctionFactory<PolarSin>);
            insertAction(fr3r, "Polar: r = 1/2+sin (Phase*pi*t*u*v)",
                         new C4DView::TemplatedRealFunctionFactory<PolarSin2>);
            insertAction(fr3r, "Polar: r = sqrt (t²+u²+v²)",
                         new C4DView::TemplatedRealFunctionFactory<PolarR>);
            insertAction(fr3r, "Custom polar function", SLOT(customPolarFunction()));
        }
        {
            insertAction(objects, "Hypersphere",
                         new C4DView::TemplatedRealFunctionFactory<Hypersphere>);
            insertAction(objects, "Hypercube", SLOT(ObjectHypercube()));
            insertAction(objects, "Hyperpyramid", SLOT(ObjectHyperpyramid()));
            insertAction(objects, "Menger Sponge", SLOT(ObjectHypersponge()));
            insertAction(objects, "Sierpinski Gasket", SLOT(ObjectGasket()));
            insertAction(objects, "Torus 1",
                         new C4DView::TemplatedRealFunctionFactory<Torus1>);
            insertAction(objects, "Torus 2",
                         new C4DView::TemplatedRealFunctionFactory<Torus2>);
        }
        {
            insertAction(surfaces, "Surface 1",
                         new C4DView::TemplatedSurfaceFactory<Surface1>);
            insertAction(surfaces, "Horizon",
                         new C4DView::TemplatedSurfaceFactory<Horizon>);
            insertAction(surfaces, "Torus 3",
                         new C4DView::TemplatedSurfaceFactory<Torus3>);
            insertAction(surfaces, "Custom surface", SLOT(customSurface()));
            {
                insertAction(fcc, "z²",
                             new C4DView::TemplatedSurfaceFactory<z2>);
                insertAction(fcc, "z³",
                             new C4DView::TemplatedSurfaceFactory<z3>);
                insertAction(fcc, "z^a",
                             new C4DView::TemplatedSurfaceFactory<zA>);
                insertAction(fcc, "e^z",
                             new C4DView::TemplatedSurfaceFactory<ez>);
                insertAction(fcc, "e^-z²",
                             new C4DView::TemplatedSurfaceFactory<emz2>);
                insertAction(fcc, "1/z",
                             new C4DView::TemplatedSurfaceFactory<zm1>);
                insertAction(fcc, "1/z²",
                             new C4DView::TemplatedSurfaceFactory<zm2>);
                insertAction(fcc, "sqrt (z)",
                             new C4DView::TemplatedSurfaceFactory<sqrtz>);
                insertAction(fcc, "ln (z)",
                             new C4DView::TemplatedSurfaceFactory<lnz>);
                insertAction(fcc, "sin (z)",
                             new C4DView::TemplatedSurfaceFactory<sinz>);
                insertAction(fcc, "cos (z)",
                             new C4DView::TemplatedSurfaceFactory<cosz>);
                insertAction(fcc, "sinh (z)",
                             new C4DView::TemplatedSurfaceFactory<sinhz>);
                insertAction(fcc, "cosh (z)",
                            new C4DView::TemplatedSurfaceFactory<coshz>);
                insertAction(fcc, "tan (z)",
                            new C4DView::TemplatedSurfaceFactory<tanz>);
                insertAction(fcc, "Custom complex function",
                             SLOT(customComplexFunction()));
                TESTED_FEATURE (getAction("Custom complex function"));
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////
    //      "Appearance" Menu
    ////////////////////////////////////////////////////////////////////////////
    {
        insertAction(appear, "Colors", SLOT(Colors ()));
        insertAction(appear, "Shading", SLOT(Shade()));
        insertAction(appear, "Depth Cue", SLOT(Fog()));
        insertAction(appear, "Transparence", SLOT(Transparent()));
        insertAction(appear, "Lighting", SLOT(Light()));
        insertAction(appear, "Wireframe", SLOT(Wireframe()), false);
        insertAction(appear, "Coordinate Cross", SLOT(Coordinates()));

        appear->addAction("Set Background Color", this, SLOT(setBackground()));

        getAction("Colors")->setChecked(m_parent->getColors());
        getAction("Shading")->setChecked(m_parent->getShade());
        getAction("Depth Cue")->setChecked(m_parent->getFog());
        getAction("Lighting")->setChecked(m_parent->getLight());
        getAction("Transparence")->setChecked(m_parent->getTransparent());
        getAction("Coordinate Cross")->setChecked(m_parent->getDisplayCoordinates());
    }
    insertAction(help, "Online help", SLOT(Help ()), false);
    help->insertSeparator (
        insertAction(help, tr("&About ..."), SLOT(about()), false));
    insertAction(help, tr("About &Qt ..."), SLOT(about()), false);

    addAction(Globals::Instance().getQuitAction());
    insertSeparator(Globals::Instance().getQuitAction());

    insertAction(animation, "Render to Images", SLOT(RenderToImages()));
    getAction("Render to Images")->setChecked(m_parent->getRenderToPixmap());

    insertAction(animation, "Animation Settings", SLOT(AnimationSettings()),
                 false);

    insertAction(animation, "Benchmark", SLOT (Benchmark()), false);
    insertAction(appear, "4D Depth Cue", SLOT(HyperFog()));

    if (m_parent->getDisplayPolygons()) {
        getAction("Wireframe")->setText("Solid");
        getAction("Transparence")->setText("Line Antialiasing");
        getAction("Transparence")->setEnabled(true);
    }
    else {
        getAction("Wireframe")->setText("Wireframe");
        getAction("Transparence")->setText("Transparence");
    }
      //      appear->setItemEnabled (transparentAction, DisplayPolygons);
    m_parent->setWireframe (m_parent->getDisplayPolygons());
}

/** Display a CustomFunction object */
void C4DView::Menu4D::customFunction() {
    CustomFunctionSlot<CustomFunction>::createCustomFunction(m_parent);
}

/** Display a CustomPolarFunction object */
void C4DView::Menu4D::customPolarFunction() {
    CustomFunctionSlot<CustomPolarFunction>::createCustomFunction(m_parent);
}

/** Display a Hypercube object */
void C4DView::Menu4D::ObjectHypercube() {
    m_parent->ObjectHypercube();
}

/** Display a Hyperpyramid object */
void C4DView::Menu4D::ObjectHyperpyramid() {
    m_parent->ObjectHyperpyramid();
}

/** Display a Hypersponge object */
void C4DView::Menu4D::ObjectHypersponge() {
    m_parent->ObjectHypersponge();
}

/** Display a Gasket object */
void C4DView::Menu4D::ObjectGasket() {
    m_parent->ObjectGasket();
}

/** Display a CustomSurface object */
void C4DView::Menu4D::customSurface() {
    CustomFunctionSlot<CustomSurface>::createCustomSurface(m_parent);
}

/** Display a CustomComplexFunction object */
void C4DView::Menu4D::customComplexFunction() {
    CustomFunctionSlot<CustomComplexFunction>::createCustomSurface(m_parent);
}


/** Toggle colors */
void C4DView::Menu4D::Colors () {
    m_parent->setColors(!m_parent->getColors());
}

/** Toggle shading */
void C4DView::Menu4D::Shade () {
    m_parent->setShading(!m_parent->getShade());
}

/** Toggle fog/depth cue */
void C4DView::Menu4D::Fog () {
    m_parent->setFog(!m_parent->getFog());
}

/** Toggle object transparency */
void C4DView::Menu4D::Transparent () {
    m_parent->setTransparence(!m_parent->getTransparent());
}

/** Switch lighting on or off
 *
 *  Change menu items accordingly
 *  \todo uses hardcoded values for light attributes
 *  \todo move all the GL stuff away from the menu handler, back into C4DView
 */
void C4DView::Menu4D::Light() {
    m_parent->setLighting(!m_parent->Lighting());
    if (m_parent->Lighting()) {
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

    m_parent->OnPaint ();
}

/** Switch between wireframe and solid display
 *
 *  Account for antialiasing only in wireframe mode
 *
 *  Change menu items accordingly                   */
void C4DView::Menu4D::Wireframe() {
    if (m_parent->DisplayPolygons()) {
        getAction("Wireframe")->setText("Solid");
        getAction("Transparence")->setText("Line Antialiasing");
    } else {
        getAction("Wireframe")->setText("Wireframe");
        getAction("Transparence")->setText("Transparence");
        glDisable (GL_CULL_FACE);
    }
    getAction("Wireframe")->setChecked (m_parent->DisplayPolygons());
    m_parent->setWireframe (m_parent->DisplayPolygons());

    m_parent->OnPaint ();
}

/** Switch coordinate cross on or off
 *
 *  Change menu items accordingly       */
void C4DView::Menu4D::Coordinates() {
    m_parent->setCoordinates(!m_parent->DisplayCoordinates());
}

/** Pop up a color selector and set the background to the chosen color */
void C4DView::Menu4D::setBackground() {
    m_parent->setBackground(Color(QColorDialog::getColor(Qt::white, m_parent)));
}

/** Switch 4D depth cue on or off
 *  Change menu items accordingly */
void C4DView::Menu4D::HyperFog() {
    m_parent->setHyperfog(!m_parent->DepthCue4D());
}


/** Switch rendering to files on or off
 *
 *  Change menu items accordingly        */
void C4DView::Menu4D::RenderToImages() {
    m_parent->setRenderToPixmap(!m_parent->RenderToPixmap());
    getAction("Render to Images")->setChecked(m_parent->RenderToPixmap());
}

/** Show a dialog to adjust animation settings - where to write image files and
 *  how many files to write. */
void C4DView::Menu4D::AnimationSettings() {
    UI::Dialogs::AnimationDialogImpl *Dlg = new UI::Dialogs::AnimationDialogImpl;
    if (Dlg->exec () == QDialog::Accepted) {
        m_parent->setanimationMaxFrames(Dlg->getFrames());
        m_parent->setanimationDirectory(Dlg->getDir());
        m_parent->setanimationPrefix(Dlg->getPrefix());
        SingletonLog::Instance()
            << "animationMaxFrames: " << (long)m_parent->animationMaxFrames()
            << ", animationDirectory: " << m_parent->animationDirectory().toStdString()
            << ", animationPrefix: "<< m_parent->animationPrefix().toStdString() << "\n";
    }
}

/** Run a benchmark test    */
void C4DView::Menu4D::Benchmark() {
    ostringstream Time;

    double time_4d = m_parent->Benchmark4D (360, 1., 0., 0.);

    Time << "4D viewpoint rotation: " << time_4d << " sec."
            << " (" << 360/1./time_4d << " fps)" << endl;

    float time_3d = m_parent->Benchmark3D (360, 1., 0., 0.);

    Time << "3D viewpoint rotation: " << time_3d << " sec."
            << " (" << 360/1./time_3d << " fps)" << ends;

    QMessageBox::information (NULL, "Benchmark results", Time.str ().c_str ());
    m_parent->UpdateStatus ();
}


/** Display help window */
void C4DView::Menu4D::Help () {
    static HelpWindow *H;
    H = new HelpWindow (C4DView::HelpFile.c_str());
    H->show();
}

/** Open an "About"-Dialog telling a few basics about the software */
void C4DView::Menu4D::about() {
    QMessageBox::about(m_parent, "Hyperspace Explorer",
                       "<p>A program to view four-dimensional objects "
                       "using OpenGL and the Qt GUI library.</p>"
                       "<p>author: "+QString(make_str(PACKAGE_BUGREPORT))+"</p>"
                       "<p>version: "+QString(make_str(PACKAGE_VERSION))+
                       " of "+QString(__DATE__)+"</p>"
                      );
}

/** Open an "About Qt"-Dialog */
void C4DView::Menu4D::aboutQt() {
    QMessageBox::aboutQt(m_parent, "Hyperspace Explorer" );
}


/** \param menuBar the menu bar you want augmented with the menu              */
void C4DView::Menu4D::addToMenuBar(QMenuBar *menuBar) {
    menuBar->addMenu(functions);
    menuBar->addMenu(appear);
    menuBar->addMenu(animation);
    menuBar->addMenu(help);
    menuBar->addSeparator();
    menuBar->addAction(Globals::Instance().getQuitAction());
}

/** \param item QString the item's title                                      */
void C4DView::Menu4D::updateFunctionMenu (const QString &item) {
    static QMenu* functionMenuList[] = {
        functions, fr3r, objects, surfaces, fcc
    };

    for (unsigned functionIdx = 0; functionIdx < sizeof(functionMenuList);
         ++functionIdx) {
             ActionMapType actionMap = menuMap[functionMenuList[functionIdx]];
             for (ActionMapType::iterator it = actionMap.begin();
                  it != actionMap.end(); ++it) {
                      it->second->setChecked(false);
                  }
         }

         getAction(item)->setChecked(true);
}

/** \param key The title of the wanted menu item
 *  \return the QAction associated with \p key                                 */
QAction *&C4DView::Menu4D::getAction(const QString &key) {
    MenuMapType::iterator it;
    for (it = menuMap.begin(); it != menuMap.end(); ++it) {
        ActionMapType actionMap = it->second;
        if (actionMap.count(key)) return actionMap[key];
    }
    throw key+" not found in list of menu entries!";    //  TODO clean exception
}

/** insert a menu item with a specified slot into a specified menu AND into
 *  the hash map storing the actions by menu title. this is necessary to find
 *  the menus whenever you want to change the item titles.
 *  \param _menu the menu you want to add the item to
 *  \param title the title of the item
 *  \param slot the function triggered by the item's selection
 *  \param checkable whether the menu item is checkable                       */
QAction *C4DView::Menu4D::insertAction(QMenu *_menu, const QString &title,
                                       const char *slot, bool checkable) {
    QAction *tmp = _menu->addAction(
        title, (const QObject *)this, (const char *)slot,
        (const QKeySequence &)0);
    tmp->setCheckable(checkable);
    menuMap[_menu].insert(std::pair<QString, QAction *>(title, tmp));
    return tmp;
}

/** This version is called whenever a new RealFunction should be
 *  initialized and displayed in C4DView
 *  \param _menu the menu you want to add the item to
 *  \param title the title of the item
 *  \param factory the factory object creating the desired RealFunction object
 *  \param checkable whether the menu item is checkable                       */
QAction *C4DView::Menu4D::insertAction(QMenu *_menu, const QString &title,
                                       RealFunctionFactory *factory,
                                       bool checkable) {
    QAction *tmp = _menu->addAction(title,
                                    new FunctionSlotHelper(m_parent, factory),
                                    SLOT(slot()), (const QKeySequence &)0);
    tmp->setCheckable(checkable);
    menuMap[fr3r].insert(std::pair<QString, QAction *>(title, tmp));

    return tmp;
}

/** This version is called whenever a new Surface should be
 *  initialized and displayed in C4DView
 *  \param _menu the menu you want to add the item to
 *  \param title the title of the item
 *  \param factory the factory object creating the desired Surface object
 *  \param checkable whether the menu item is checkable                       */
QAction *C4DView::Menu4D::insertAction(QMenu *_menu, const QString &title,
                                       SurfaceFactory *factory,
                                       bool checkable) {
    QAction *tmp = _menu->addAction(title,
                                    new SurfaceSlotHelper(m_parent, factory),
                                    SLOT(slot()), (const QKeySequence &)0);
    tmp->setCheckable(checkable);
    menuMap[fr3r].insert(std::pair<QString, QAction *>(title, tmp));

    return tmp;
}

