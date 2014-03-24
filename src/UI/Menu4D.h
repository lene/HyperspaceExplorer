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

#ifndef MENU4D_H
#define MENU4D_H

#include <QMenu>
#include <map>

#include "4DView.h"
#include "FunctionFactory.h"

class QString;
class QMenuBar;
class RealFunctionFactory;
class SurfaceFactory;

/// The menu for the C4DView and handlers for menu events
/** This class has been outsourced from C4DView to keep C4DView to a managable
 *  size.
 *  \ingroup UIGroup
 *  @author Helge Preuss <lene.preuss@gmail.com>                         */
class C4DView::Menu4D: public QMenu {

    Q_OBJECT


    public:
        /// Creates the application's main menu and all its submenus
        Menu4D(C4DView *);

    public slots:
        /// "Object/f:R^3 -> R/Custom function" menu item selected
        void customFunction();
        /// "Object/f:R^3 -> R/Custom polar function" menu item selected
        void customPolarFunction();
        /// "Object/Surfaces/Custom surface" menu item selected
        void customSurface();
        /// "Object/Surfaces/f:C -> C/Custom complex function" menu item selected
        void customComplexFunction();

        void Colors();          ///< "Appearance/Colors" menu item selected
        void Shade();           ///< "Appearance/Shading" menu item selected
        void Fog();             ///< "Appearance/Depth Cue" menu item selected
        void Transparent();     ///< "Appearance/Transparence" menu item selected
        void Light();           ///< "Appearance/Lighting" menu item selected
        void Wireframe();       ///< "Appearance/Wireframe" menu item selected
        void Coordinates();     ///< "Appearance/Coordinate Cross" menu item selected
        void setBackground();   ///< "Appearance/Set Background Color" menu item selected
        void HyperFog();        ///< "Appearance/4D Depth Cue" menu item selected
        void setColorManager(QAction *); ///< "Appearance/Coloring Scheme" submenu item selected

        void RenderToImages();  ///< "Animation/Render to Images" menu item selected
        void AnimationSettings(); ///< "Animation/Animation Settings" menu item selected
        void Benchmark();       ///< "Animation/Benchmark" menu item selected
        void RandomAnimation(); ///< "Animation/Random Animation" menu item selected

        void Help();            ///< "Help/Online Help" menu item selected
        void about ();          ///< "Help/About" menu item selected
        void aboutQt ();        ///< "Help/About Qt" menu item selected

    public:
        /// Add the menu to a QMenuBar
        void addToMenuBar(QMenuBar *menuBar);
        /// Set the selected function as checked and uncheck all the others
        void updateFunctionMenu(const QString &);
        /// Search for the QAction associated with a menu item
        QAction *&getAction(const QString &key);

    private:
        /// Assigns a QAction to a menu title
        typedef std::map<QString, QAction *> ActionMapType;
        /// Manages an ActionMap for each submenu
        typedef std::map<QMenu *, ActionMapType> MenuMapType;

        void createAppearanceMenu();
        
        /// Creates a menu with submenus from a DisplayableClass
        QMenu *createMenu(const DisplayableClass &node);

        /// insert a menu item with a specified slot into a specified menu
        QAction *insertAction(QMenu *, const QString &, const char * = 0,
                              bool = true);
        /// insert a menu item creating a Surface object into a specified menu
        QAction *insertAction(QMenu *, const std::string &, bool = true);
        
        void addClassSubmenu(QMenu *thisMenu, const std::vector<DisplayableClass> & subClasses);
        void addDisplayableEntries(QMenu *thisMenu, const std::vector<std::string> & displayableNames);
        const char * getCustomFunctionSlot(const std::string & displayable);
        
        C4DView *_parent;       ///< the C4DView containing this menu

        QMenu *_appear;         ///< The "Appearance" menu
        QMenu *_color;          ///< The "Appearance/Color Schemes" submenu
        QMenu *_animation;      ///< The "Animation" menu
        QMenu *_help;           ///< The "Help" menu
        QMenu *generated_;      ///< The auto-generated Displayable menu

        MenuMapType _menuMap;    ///< Keeps the QActions belonging to the menu entries
};

#endif
