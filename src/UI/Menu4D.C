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
 *  as Factory object _helps to save a lot of redundant code, but still every
 *  menu item must be specified manually.
 */
C4DView::Menu4D::Menu4D(C4DView *_parent):
    _parent(_parent) {

    _functions = addMenu(tr("Object"));
    _appear = addMenu(tr("Appearance"));
    _animation = addMenu(tr("Animation"));
    _help = addMenu(tr("Help"));

    ////////////////////////////////////////////////////////////////////////////
    //      "Objects" Menu
    ////////////////////////////////////////////////////////////////////////////
    {
        _fr3r = _functions->addMenu("f: R³ -> R");
        _objects = _functions->addMenu("Objects");
        _surfaces = _functions->addMenu("Surfaces");
        _fcc = _surfaces->addMenu("f: C -> C");
        {
            insertAction(_fr3r, "1/(r²+1)",
                         new C4DView::TemplatedRealFunctionFactory<Fr3r>);
            insertAction(_fr3r, "Gravitation Potential",
                         new C4DView::TemplatedRealFunctionFactory<GravitationPotential>);
            insertAction(_fr3r, "sin (r²)",
                         new C4DView::TemplatedRealFunctionFactory<Fr3rSin>);
            insertAction(_fr3r, "exp (r²)",
                         new C4DView::TemplatedRealFunctionFactory<Fr3rExp>);
            insertAction(_fr3r, "Custom function", SLOT(customFunction()));
            insertAction(_fr3r, "Polar: r = sin (pi/3.*(t+u+v))",
                         new C4DView::TemplatedRealFunctionFactory<PolarSin>);
            insertAction(_fr3r, "Polar: r = 1/2+sin (Phase*pi*t*u*v)",
                         new C4DView::TemplatedRealFunctionFactory<PolarSin2>);
            insertAction(_fr3r, "Polar: r = sqrt (t²+u²+v²)",
                         new C4DView::TemplatedRealFunctionFactory<PolarR>);
            insertAction(_fr3r, "Custom polar function", SLOT(customPolarFunction()));
        }
        {
            insertAction(_objects, "Hypersphere",
                         new C4DView::TemplatedRealFunctionFactory<Hypersphere>);
            insertAction(_objects, "Hypercube", SLOT(ObjectHypercube()));
            insertAction(_objects, "Hyperpyramid", SLOT(ObjectHyperpyramid()));
            insertAction(_objects, "Menger Sponge", SLOT(ObjectHypersponge()));
            insertAction(_objects, "Sierpinski Gasket", SLOT(ObjectGasket()));
            insertAction(_objects, "Torus 1",
                         new C4DView::TemplatedRealFunctionFactory<Torus1>);
            insertAction(_objects, "Torus 2",
                         new C4DView::TemplatedRealFunctionFactory<Torus2>);
        }
        {
            insertAction(_surfaces, "Surface 1",
                         new C4DView::TemplatedSurfaceFactory<Surface1>);
            insertAction(_surfaces, "Horizon",
                         new C4DView::TemplatedSurfaceFactory<Horizon>);
            insertAction(_surfaces, "Torus 3",
                         new C4DView::TemplatedSurfaceFactory<Torus3>);
            insertAction(_surfaces, "Custom surface", SLOT(customSurface()));
            {
                insertAction(_fcc, "z²",
                             new C4DView::TemplatedSurfaceFactory<z2>);
                insertAction(_fcc, "z³",
                             new C4DView::TemplatedSurfaceFactory<z3>);
                insertAction(_fcc, "z^a",
                             new C4DView::TemplatedSurfaceFactory<zA>);
                insertAction(_fcc, "e^z",
                             new C4DView::TemplatedSurfaceFactory<ez>);
                insertAction(_fcc, "e^-z²",
                             new C4DView::TemplatedSurfaceFactory<emz2>);
                insertAction(_fcc, "1/z",
                             new C4DView::TemplatedSurfaceFactory<zm1>);
                insertAction(_fcc, "1/z²",
                             new C4DView::TemplatedSurfaceFactory<zm2>);
                insertAction(_fcc, "sqrt (z)",
                             new C4DView::TemplatedSurfaceFactory<sqrtz>);
                insertAction(_fcc, "ln (z)",
                             new C4DView::TemplatedSurfaceFactory<lnz>);
                insertAction(_fcc, "sin (z)",
                             new C4DView::TemplatedSurfaceFactory<sinz>);
                insertAction(_fcc, "cos (z)",
                             new C4DView::TemplatedSurfaceFactory<cosz>);
                insertAction(_fcc, "sinh (z)",
                             new C4DView::TemplatedSurfaceFactory<sinhz>);
                insertAction(_fcc, "cosh (z)",
                            new C4DView::TemplatedSurfaceFactory<coshz>);
                insertAction(_fcc, "tan (z)",
                            new C4DView::TemplatedSurfaceFactory<tanz>);
                insertAction(_fcc, "Custom complex function",
                             SLOT(customComplexFunction()));
                TESTED_FEATURE (getAction("Custom complex function"));
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////
    //      "Appearance" Menu
    ////////////////////////////////////////////////////////////////////////////
    {
        insertAction(_appear, "Colors", SLOT(Colors ()));
        insertAction(_appear, "Shading", SLOT(Shade()));
        insertAction(_appear, "Depth Cue", SLOT(Fog()));
        insertAction(_appear, "Transparence", SLOT(Transparent()));
        insertAction(_appear, "Lighting", SLOT(Light()));
        insertAction(_appear, "Wireframe", SLOT(Wireframe()), false);
        insertAction(_appear, "Coordinate Cross", SLOT(Coordinates()));

        _appear->addAction("Set Background Color", this, SLOT(setBackground()));

        getAction("Colors")->setChecked(_parent->getColors());
        getAction("Shading")->setChecked(_parent->getShading());
        getAction("Depth Cue")->setChecked(_parent->getFog());
        getAction("Lighting")->setChecked(_parent->getLighting());
        getAction("Transparence")->setChecked(_parent->getTransparence());
        getAction("Coordinate Cross")->setChecked(_parent->getCoordinates());
    }
    insertAction(_help, "Online _help", SLOT(Help ()), false);
    _help->insertSeparator (
        insertAction(_help, tr("&About ..."), SLOT(about()), false));
    insertAction(_help, tr("About &Qt ..."), SLOT(about()), false);

    addAction(Globals::Instance().getQuitAction());
    insertSeparator(Globals::Instance().getQuitAction());

    insertAction(_animation, "Render to Images", SLOT(RenderToImages()));
    getAction("Render to Images")->setChecked(_parent->getWriteImages());

    insertAction(_animation, "Animation Settings", SLOT(AnimationSettings()),
                 false);

    insertAction(_animation, "Benchmark", SLOT (Benchmark()), false);
    insertAction(_appear, "4D Depth Cue", SLOT(HyperFog()));

    if (_parent->getSolid()) {
        getAction("Wireframe")->setText("Solid");
        getAction("Transparence")->setText("Line Antialiasing");
        getAction("Transparence")->setEnabled(true);
    }
    else {
        getAction("Wireframe")->setText("Wireframe");
        getAction("Transparence")->setText("Transparence");
    }
      //      _appear->setItemEnabled (transparentAction, DisplayPolygons);
    _parent->setSolid(!_parent->getSolid());
}

/** Display a CustomFunction object */
void C4DView::Menu4D::customFunction() {
    CustomFunctionSlot<CustomFunction>::createCustomFunction(_parent);
}

/** Display a CustomPolarFunction object */
void C4DView::Menu4D::customPolarFunction() {
    CustomFunctionSlot<CustomPolarFunction>::createCustomFunction(_parent);
}

/** Display a Hypercube object */
void C4DView::Menu4D::ObjectHypercube() {
    _parent->ObjectHypercube();
}

/** Display a Hyperpyramid object */
void C4DView::Menu4D::ObjectHyperpyramid() {
    _parent->ObjectHyperpyramid();
}

/** Display a Hypersponge object */
void C4DView::Menu4D::ObjectHypersponge() {
    _parent->ObjectHypersponge();
}

/** Display a Gasket object */
void C4DView::Menu4D::ObjectGasket() {
    _parent->ObjectGasket();
}

/** Display a CustomSurface object */
void C4DView::Menu4D::customSurface() {
    CustomFunctionSlot<CustomSurface>::createCustomSurface(_parent);
}

/** Display a CustomComplexFunction object */
void C4DView::Menu4D::customComplexFunction() {
    CustomFunctionSlot<CustomComplexFunction>::createCustomSurface(_parent);
}


/** Toggle colors */
void C4DView::Menu4D::Colors () {
    _parent->setColors(!_parent->getColors());
    getAction("Colors")->setChecked(_parent->getColors());
}

/** Toggle shading */
void C4DView::Menu4D::Shade () {
    _parent->setShading(!_parent->getShading());
    getAction("Shading")->setChecked(_parent->getShading());
}

/** Toggle fog/depth cue */
void C4DView::Menu4D::Fog () {
    _parent->setFog(!_parent->getFog());
    getAction("Depth Cue")->setChecked(_parent->getFog());
}

/** Toggle object transparency */
void C4DView::Menu4D::Transparent () {
    _parent->setTransparence(!_parent->getTransparence());
    getAction("Transparence")->setChecked(_parent->getTransparence());
}

/** Switch lighting on or off
 *
 *  Change menu items accordingly */
void C4DView::Menu4D::Light() {
    _parent->setLighting(!_parent->getLighting());
    getAction("Lighting")->setChecked(_parent->getLighting());
}

/** Switch between wireframe and solid display
 *
 *  Account for antialiasing only in wireframe mode
 *
 *  Change menu items accordingly                   */
void C4DView::Menu4D::Wireframe() {
    if (_parent->getSolid()) {
        getAction("Wireframe")->setText("Solid");
        getAction("Transparence")->setText("Line Antialiasing");
    } else {
        getAction("Wireframe")->setText("Wireframe");
        getAction("Transparence")->setText("Transparence");
        glDisable(GL_CULL_FACE);
    }
    getAction("Wireframe")->setChecked(_parent->getSolid());
    _parent->setSolid(!_parent->getSolid());

    _parent->OnPaint ();
}

/** Switch coordinate cross on or off
 *
 *  Change menu items accordingly       */
void C4DView::Menu4D::Coordinates() {
    _parent->setCoordinates(!_parent->getCoordinates());
    getAction("Coordinate Cross")->setChecked(_parent->getCoordinates());
}

/** Pop up a color selector and set the background to the chosen color */
void C4DView::Menu4D::setBackground() {
    _parent->setBackground(Color(QColorDialog::getColor(Qt::white, _parent)));
}

/** Switch 4D depth cue on or off
 *  Change menu items accordingly */
void C4DView::Menu4D::HyperFog() {
    _parent->setHyperfog(!_parent->getHyperfog());
    getAction("4D Depth Cue")->setChecked(_parent->getHyperfog());
}


/** Switch rendering to files on or off
 *
 *  Change menu items accordingly        */
void C4DView::Menu4D::RenderToImages() {
    _parent->setWriteImages(!_parent->getWriteImages());
    getAction("Render to Images")->setChecked(_parent->getWriteImages());
}

/** Show a dialog to adjust _animation settings - where to write image files and
 *  how many files to write. */
void C4DView::Menu4D::AnimationSettings() {
    UI::Dialogs::AnimationDialogImpl *Dlg = new UI::Dialogs::AnimationDialogImpl;
    if (Dlg->exec () == QDialog::Accepted) {
        _parent->setanimationMaxFrames(Dlg->getFrames());
        _parent->setImgDir(Dlg->getDir().toAscii().data());
        _parent->setImgPrefix(Dlg->getPrefix().toAscii().data());
        SingletonLog::Instance()
            << "animationMaxFrames: " << (long)_parent->animationMaxFrames()
            << ", animationDirectory: " << _parent->getImgDir()
            << ", animationPrefix: "<< _parent->getImgPrefix() << "\n";
    }
}

/** Run a benchmark test    */
void C4DView::Menu4D::Benchmark() {
    ostringstream Time;

    double time_4d = _parent->Benchmark4D (360, 1., 0., 0.);

    Time << "4D viewpoint rotation: " << time_4d << " sec."
            << " (" << 360/1./time_4d << " fps)" << endl;

    float time_3d = _parent->Benchmark3D (360, 1., 0., 0.);

    Time << "3D viewpoint rotation: " << time_3d << " sec."
            << " (" << 360/1./time_3d << " fps)" << ends;

    QMessageBox::information (NULL, "Benchmark results", Time.str ().c_str ());
    _parent->UpdateStatus ();
}


/** Display _help window */
void C4DView::Menu4D::Help () {
    static HelpWindow *H;
    H = new HelpWindow (C4DView::_helpFile.c_str());
    H->show();
}

/** Open an "About"-Dialog telling a few basics about the software */
void C4DView::Menu4D::about() {
    QMessageBox::about(_parent, "Hyperspace Explorer",
                       "<p>A program to view four-dimensional _objects "
                       "using OpenGL and the Qt GUI library.</p>"
                       "<p>author: "+QString(make_str(PACKAGE_BUGREPORT))+"</p>"
                       "<p>version: "+QString(make_str(PACKAGE_VERSION))+
                       " of "+QString(__DATE__)+"</p>"
                      );
}

/** Open an "About Qt"-Dialog */
void C4DView::Menu4D::aboutQt() {
    QMessageBox::aboutQt(_parent, "Hyperspace Explorer" );
}


/** \param menuBar The menu bar you want augmented with the menu              */
void C4DView::Menu4D::addToMenuBar(QMenuBar *menuBar) {
    menuBar->addMenu(_functions);
    menuBar->addMenu(_appear);
    menuBar->addMenu(_animation);
    menuBar->addMenu(_help);
    menuBar->addSeparator();
    menuBar->addAction(Globals::Instance().getQuitAction());
}

/** \param item Title of the item whose checking status is toggled            */
void C4DView::Menu4D::updateFunctionMenu (const QString &item) {
    static QMenu* functionMenuList[] = {
        _functions, _fr3r, _objects, _surfaces, _fcc
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
 *  \return The QAction associated with \p key                                 */
QAction *&C4DView::Menu4D::getAction(const QString &key) {
    MenuMapType::iterator it;
    for (it = menuMap.begin(); it != menuMap.end(); ++it) {
        ActionMapType actionMap = it->second;
        if (actionMap.count(key)) return actionMap[key];
    }
    throw key+" not found in list of menu entries!";    //  TODO clean exception
}


/** Insert a menu item with a specified slot into a specified menu \em and into
 *  the hash map storing the actions by menu title. This is necessary to find
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
                                    new FunctionSlotHelper(_parent, factory),
                                    SLOT(slot()), (const QKeySequence &)0);
    tmp->setCheckable(checkable);
    menuMap[_fr3r].insert(std::pair<QString, QAction *>(title, tmp));

    return tmp;
}

/** This version is called whenever a new Surface should be initialized and
 *  displayed in C4DView
 *  \param _menu the menu you want to add the item to
 *  \param title the title of the item
 *  \param factory the factory object creating the desired Surface object
 *  \param checkable whether the menu item is checkable                       */
QAction *C4DView::Menu4D::insertAction(QMenu *_menu, const QString &title,
                                       SurfaceFactory *factory,
                                       bool checkable) {
    QAction *tmp = _menu->addAction(title,
                                    new SurfaceSlotHelper(_parent, factory),
                                    SLOT(slot()), (const QKeySequence &)0);
    tmp->setCheckable(checkable);
    menuMap[_fr3r].insert(std::pair<QString, QAction *>(title, tmp));

    return tmp;
}

