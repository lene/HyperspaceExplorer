#include <map>

#include <QShortcut>
#include <QMenuBar>

#include "Menu4D.H"
#include "4DView.H"
#include "Globals.H"
#include "RealFunction.H"
#include "SlotHelper.H"

inline void TESTED_FEATURE(QAction *item) {
# ifdef TESTFEATURES
    item->setEnabled (true);
# else
    item->setEnabled (false);
#endif
}

Menu4D::Menu4D(C4DView *_parent):
    parent(_parent) {

    functions = addMenu(tr("Object"));
    appear = addMenu(tr("Appearance"));
    animation = addMenu(tr("Animation"));
    help = addMenu(tr("Help"));

    ////////////////////////////////////////////////////////////////////////////
    //      "Objects" Menu
    ////////////////////////////////////////////////////////////////////////////
    fr3r = functions->addMenu("f: R³ -> R");
    objects = functions->addMenu("Objects");
    surfaces = functions->addMenu("Surfaces");
    fcc = surfaces->addMenu("f: C -> C");

    insertAction(fr3r, "1/(r²+1)",
                 new C4DView::TemplatedFunctionFactory<Fr3r>);
    insertAction(fr3r, "Gravitation Potential",
                 new C4DView::TemplatedFunctionFactory<GravitationPotential>);
    insertAction(fr3r, "sin (r²)",
                 new C4DView::TemplatedFunctionFactory<Fr3rSin>);
    insertAction(fr3r, "exp (r²)",
                 new C4DView::TemplatedFunctionFactory<Fr3rExp>);
    insertAction(fr3r, "Custom function", SLOT(customFunction()));

    insertAction(fr3r, "Polar: r = sin (pi/3.*(t+u+v))",
                 new C4DView::TemplatedFunctionFactory<PolarSin>);
    insertAction(fr3r, "Polar: r = 1/2+sin (Phase*pi*t*u*v)",
                 new C4DView::TemplatedFunctionFactory<PolarSin2>);
    insertAction(fr3r, "Polar: r = sqrt (t²+u²+v²)",
                 new C4DView::TemplatedFunctionFactory<PolarR>);
    insertAction(fr3r, "Custom polar function", SLOT(customPolarFunction()));

//    insertAction(objects, "Hypersphere", SLOT(FunctionHypersphere()));
    insertAction(objects, "Hypersphere",
                 new C4DView::TemplatedFunctionFactory<Hypersphere>);
    insertAction(objects, "Hypercube", SLOT(ObjectHypercube()));
    insertAction(objects, "Hyperpyramid", SLOT(ObjectHyperpyramid()));
    insertAction(objects, "Menger Sponge", SLOT(ObjectHypersponge()));
    insertAction(objects, "Sierpinski Gasket", SLOT(ObjectGasket()));
//    insertAction(objects, "Torus 1", SLOT(FunctionTorus1()));
    insertAction(objects, "Torus 1",
                 new C4DView::TemplatedFunctionFactory<Torus1>);
//    insertAction(objects, "Torus 2", SLOT(FunctionTorus2()));
    insertAction(objects, "Torus 2",
                 new C4DView::TemplatedFunctionFactory<Torus2>);

    insertAction(surfaces, "Surface 1",
                 new C4DView::TemplatedSurfaceFactory<Surface1>);
    insertAction(surfaces, "Horizon",
                 new C4DView::TemplatedSurfaceFactory<Horizon>);
    insertAction(surfaces, "Torus 3",
                 new C4DView::TemplatedSurfaceFactory<Torus3>);
    insertAction(surfaces, "Custom surface", SLOT(customSurface()));

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
    insertAction(fcc, "Custom complex function", SLOT(customComplexFunction()));
    TESTED_FEATURE (getAction("Custom complex function"));

    ////////////////////////////////////////////////////////////////////////////
    //      "Appearance" Menu
    ////////////////////////////////////////////////////////////////////////////
    insertAction(appear, "Colors", SLOT(Colors ()));
    insertAction(appear, "Shading", SLOT(Shade()));
    insertAction(appear, "Depth Cue", SLOT(Fog()));
    insertAction(appear, "Transparence", SLOT(Transparent()));
    insertAction(appear, "Lighting", SLOT(Light()));
    insertAction(appear, "Wireframe", SLOT(Wireframe()), false);
    insertAction(appear, "Coordinate Cross", SLOT(Coordinates()));

//    appear->setCheckable (true);

    getAction("Colors")->setChecked(parent->getColors());
    getAction("Shading")->setChecked(parent->getShade());
    getAction("Depth Cue")->setChecked(parent->getFog());
    getAction("Lighting")->setChecked(parent->getLight());
    getAction("Transparence")->setChecked(parent->getTransparent());
    getAction("Coordinate Cross")->setChecked(parent->getDisplayCoordinates());

    insertAction(help, "Online help", SLOT(Help ()), false);
    help->insertSeparator (
        insertAction(help, tr("&About ..."), SLOT(about()), false));
    insertAction(help, tr("About &Qt ..."), SLOT(about()), false);

//    addAction("Quit",       qApp, SLOT(quit ()));
    addAction(Globals::Instance().getQuitAction());
    insertSeparator(Globals::Instance().getQuitAction());

    insertAction(animation, "Render to Images", SLOT(RenderToImages()));
    getAction("Render to Images")->setChecked(parent->getRenderToPixmap());
    TESTED_FEATURE (getAction("Render to Images"));

    insertAction(animation, "Animation Settings", SLOT(AnimationSettings()),
                 false);
    TESTED_FEATURE (getAction("Animation Settings"));

    insertAction(animation, "Benchmark", SLOT (Benchmark()), false);
    insertAction(appear, "4D Depth Cue", SLOT(HyperFog()));

    if (parent->getDisplayPolygons()) {
        getAction("Wireframe")->setText("Solid");
        getAction("Transparence")->setText("Line Antialiasing");
        getAction("Transparence")->setEnabled(true);
    }
    else {
        getAction("Wireframe")->setText("Wireframe");
        getAction("Transparence")->setText("Transparence");
        TESTED_FEATURE (getAction("Transparence"));
    }
      //      appear->setItemEnabled (transparentAction, DisplayPolygons);
    parent->setWireframe (parent->getDisplayPolygons());
}

void Menu4D::addToMenuBar(QMenuBar *menuBar) {
    menuBar->addMenu(functions);
    menuBar->addMenu(appear);
    menuBar->addMenu(animation);
    menuBar->addMenu(help);
    menuBar->addSeparator();
    menuBar->addAction(Globals::Instance().getQuitAction());
}

/** insert a menu item with a specified slot into a specified menu AND into
 *  the hash map storing the actions by menu title. this is necessary to find
 *  the menus whenever you want to change the item titles.
 *  @param _menu the menu you want to add the item to
 *  @param title the title of the item
 *  @param slot the function triggered by the item's selection
 *  @param checkable whether the menu item is checkable                       */
QAction *Menu4D::insertAction(QMenu *_menu, const QString &title,
                              const char *slot, bool checkable) {
    QAction *tmp = _menu->addAction(
        title, (const QObject *)parent, (const char *)slot,
        (const QKeySequence &)0);
    tmp->setCheckable(checkable);
    menuMap[_menu].insert(std::pair<QString, QAction *>(title, tmp));
    return tmp;
}

/// New version of insertAction() working with the SlotHelper class
/** @param _menu the menu you want to add the item to
 *  @param title the title of the item
 *  @param checkable whether the menu item is checkable                       */
QAction *Menu4D::insertAction(QMenu *_menu, const QString &title,
                              FunctionFactory *factory,
                              bool checkable) {
    QAction *tmp = _menu->addAction(title,
                                    new FunctionSlotHelper(parent, factory),
                                    SLOT(slot()), (const QKeySequence &)0);
    tmp->setCheckable(checkable);
    menuMap[fr3r].insert(std::pair<QString, QAction *>(title, tmp));

    return tmp;
}

/// New version of insertAction() working with the SlotHelper class
/** @param _menu the menu you want to add the item to
 *  @param title the title of the item
 *  @param checkable whether the menu item is checkable                       */
QAction *Menu4D::insertAction(QMenu *_menu, const QString &title,
                              SurfaceFactory *factory,
                              bool checkable) {
    QAction *tmp = _menu->addAction(title,
                                    new SurfaceSlotHelper(parent, factory),
                                    SLOT(slot()), (const QKeySequence &)0);
    tmp->setCheckable(checkable);
    menuMap[fr3r].insert(std::pair<QString, QAction *>(title, tmp));

    return tmp;
}

QAction *Menu4D::insertAction(QMenu *_menu, const FunctionBase *function,
                              const char *slot, bool checkable) {
    return insertAction(_menu, function->getFunctionName(), slot, checkable);
}

/** search for the supplied String in the list of menu entries in all submenus
 *  and return the associated QAction                                         */
QAction *&Menu4D::getAction(const QString &key) {
    MenuMapType::iterator it;
    for (it = menuMap.begin(); it != menuMap.end(); ++it) {
        ActionMapType actionMap = it->second;
        if (actionMap.count(key)) return actionMap[key];
    }
    throw key+" not found in list of menu entries!";    //  TODO clean exception
}

/** set the selected function as checked and all the others unchecked
    @param item QString the item's title                                      */
void Menu4D::updateFunctionMenu (const QString &item) {
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

