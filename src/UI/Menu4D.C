/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/


#include <map>
#include <sstream>
#include <iterator>

#include <QShortcut>
#include <QMenuBar>
#include <QColorDialog>
#include <QMessageBox>

#include "Menu4D.h"
#include "4DView.h"
#include "Globals.h"
#include "RealFunctionImplementations.h"
#include "Surface/SurfaceImplementations.h"
#include "SlotHelper.h"
#include "AnimationDialogImpl.h"
#include "Help.h"
#include "ColorManager.h"

#include "FunctionHolder.impl.h"
#include "CustomFunctionSlot.impl.h"
#include "MultiDimensionalVector.impl.h"

using std::ostringstream;
using std::endl;
using std::ends;

using std::vector;
using std::string;

/// Disables menu entry if preprocessor variable TESTFEATURES is unset
inline void TESTED_FEATURE(QAction *item) {
# ifdef TESTFEATURES
    item->setEnabled (true);
# else
    item->setEnabled (false);
#endif
}

QMenu *C4DView::Menu4D::createMenu(const DisplayableClass &node) {
  QMenu *thisMenu = new QMenu(node.getDescription().c_str());

  vector<DisplayableClass> subClasses = node.getSubClasses();
  for (vector<DisplayableClass>::const_iterator i = subClasses.begin();
       i != subClasses.end(); ++i) {
    thisMenu->addMenu(createMenu(*i));
  }

  std::cerr << thisMenu->title().toStdString() << std::endl;
  vector<string> displayableNames = node.getDisplayableNames();
  for (vector<string>::const_iterator i = displayableNames.begin();
       i != displayableNames.end(); ++i) {
    insertAction(thisMenu, *i, true);
    std::cerr << "    " << *i << std::endl;
  }

  thisMenu->setTearOffEnabled(true);

  return thisMenu;
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

    _appear = addMenu(tr("Appearance"));
    _animation = addMenu(tr("Animation"));
    _help = addMenu(tr("Help"));

    generated_ = createMenu(DisplayableClass::getRootNode());
    addCustomFunctionEntries(generated_);
    
    addMenu(generated_);

    QString sup2(QChar(0x00B2));
    QString sup3(QChar(0x00B3));
/*
    std::copy(TheFunctionFactory::Instance().listFunctions().begin(),
              TheFunctionFactory::Instance().listFunctions().end(),
              std::ostream_iterator<std::string>(std::cerr, " "));
*/              

    createAppearanceMenu();
    
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
    insertAction(_animation, "Random Animation", SLOT (RandomAnimation()), false);

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

void C4DView::Menu4D::addCustomFunctionEntries(QMenu* functions_menu) {
  std::cerr << "*************************************************" << std::endl;
  QList<QWidget *> children = functions_menu->findChildren<QWidget *>();
  foreach(QWidget *item, children) {
    std::cerr << item->accessibleName().toStdString() << std::endl;
  }
  std::cerr << "*************************************************" << std::endl;
}

void C4DView::Menu4D::createAppearanceMenu() {
    ////////////////////////////////////////////////////////////////////////////
    //      "Appearance" Menu
    ////////////////////////////////////////////////////////////////////////////
    {
        insertAction(_appear, "Colors", SLOT(Colors ()));
        insertAction(_appear, "Shading", SLOT(Shade()));
        insertAction(_appear, "Depth Cue", SLOT(Fog()));
        insertAction(_appear, "4D Depth Cue", SLOT(HyperFog()));
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

        {
            _color = _appear->addMenu("Coloring Schemes");
            std::vector<std::string> colMgrList =
                    ColMgrMgr::Instance().getRegisteredColorManagers();
            for (std::vector<std::string>::const_iterator i = colMgrList.begin();
                 i != colMgrList.end(); ++i) {
                insertAction(_color, QString(i->c_str()));
            }
            connect(_color, SIGNAL(triggered(QAction *)),
                    this, SLOT(setColorManager(QAction *)));
        }
    
    }

    _appear->setTearOffEnabled(true);

}


/** Display a CustomFunction object */
void C4DView::Menu4D::customFunction() {
    CustomFunctionSlot<CustomFunction>::createCustomFunction(_parent);
}

/** Display a CustomPolarFunction object */
void C4DView::Menu4D::customPolarFunction() {
    CustomFunctionSlot<CustomPolarFunction>::createCustomFunction(_parent);
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

    _parent->paintEvent();
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

/** Set ColorManager to the selected menu item */
void C4DView::Menu4D::setColorManager(QAction *a) {
    if (a) {
        ColMgrMgr::Instance().setColorManager(a->text().toStdString());
        _parent->Redraw();
        /// check current menu item, uncheck others
        std::vector<std::string> colMgrList =
                ColMgrMgr::Instance().getRegisteredColorManagers();
        for (std::vector<std::string>::const_iterator i = colMgrList.begin();
             i != colMgrList.end(); ++i) {
            getAction(i->c_str())->setChecked(false);
        }
        getAction(a->text())->setChecked(true);
    }
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
        _parent->setImgDir(Dlg->getDir().toLatin1().data());
        _parent->setImgPrefix(Dlg->getPrefix().toLatin1().data());
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

/** Animate the object whith the rotation of the animation changing randomly
 *  every couple of seconds
 */
void C4DView::Menu4D::RandomAnimation() {
    static bool animated = false;
    animated = !animated;
    _parent->RandomAnimation(animated);
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
  menuBar->addMenu(generated_);
  menuBar->addMenu(_appear);
  menuBar->addMenu(_animation);
  menuBar->addMenu(_help);
  menuBar->addSeparator();
  menuBar->addAction(Globals::Instance().getQuitAction());
}


void updateFunctionMenuRecursively(const QString &item, const QMenu *rootNode) {
  QList<QAction *> actions = rootNode->actions();
  for (QList<QAction *>::const_iterator i = actions.constBegin(); i != actions.constEnd(); ++i) {
    const QMenu *submenu = (*i)->menu();
    if (submenu) {
      updateFunctionMenuRecursively(item, submenu);
    } else {
      (*i)->setChecked((*i)->text() == item);
    }
  }
}

/** \param item Title of the item whose checking status is toggled            */
void C4DView::Menu4D::updateFunctionMenu (const QString &item) {
  updateFunctionMenuRecursively(item, generated_);
}

/** \param key The title of the wanted menu item
 *  \return The QAction associated with \p key                                 */
QAction *&C4DView::Menu4D::getAction(const QString &key) {
    MenuMapType::iterator it;
    for (it = _menuMap.begin(); it != _menuMap.end(); ++it) {
        ActionMapType actionMap = it->second;
        if (actionMap.count(key)) return actionMap[key];
    }

    QString mapKeys;
    for (it = _menuMap.begin(); it != _menuMap.end(); ++it) {
      mapKeys += "( ";
      ActionMapType actionMap = it->second;
      for (ActionMapType::iterator jt = actionMap.begin(); jt != actionMap.end(); ++jt) {
        mapKeys += jt->first+", ";
      }
      mapKeys += " )\n";
    }
    throw std::logic_error(
      (key+" not found in list of menu entries:\n"+ mapKeys).toStdString());
}


/** Insert a menu item with a specified slot into a specified menu \em and into
 *  the hash map storing the actions by menu title. This is necessary to find
 *  the menus whenever you want to change the item titles.
 *  \param _menu the menu you want to add the item to
 *  \param title the title of the item
 *  \param slot The function triggered by the item's selection. If it is null,
 *              you have to connect the returned action to a slot by yourself.
 *  \param checkable whether the menu item is checkable
 *  \return The generated QAction
 */
QAction *C4DView::Menu4D::insertAction(QMenu *_menu, const QString &title,
                                       const char *slot, bool checkable) {
    QAction *tmp;
    if (slot) {
        tmp = _menu->addAction(
            title, (const QObject *)this, (const char *)slot,
            (const QKeySequence &)0);
    }
    else tmp = _menu->addAction(title);

    tmp->setCheckable(checkable);
    _menuMap[_menu].insert(std::pair<QString, QAction *>(title, tmp));
    return tmp;
}

QAction* C4DView::Menu4D::insertAction(QMenu* menu,
                                       const std::string &displayable_name,
                                       bool checkable) {
  QString title(displayable_name.c_str());
  QAction *tmp = menu->addAction(title,
                                 new SlotHelper(_parent, displayable_name),
                                 SLOT(slot()), (const QKeySequence &)0);
  tmp->setCheckable(checkable);
  _menuMap[menu].insert(std::pair<QString, QAction *>(title, tmp));

  return tmp;

}
