
#ifndef MENU4D_H
#define MENU4D_H

#include <QMenu>
#include <map>

#include "4DView.h"

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
        /// "Object/Objects/Hypercube" menu item selected
        void ObjectHypercube();
        /// "Object/Objects/Hyperpyramid" menu item selected
        void ObjectHyperpyramid();
        /// "Object/Objects/Menger Sponge" menu item selected
        void ObjectHypersponge();
        /// "Object/Objects/Alt. Menger Sponge" menu item selected
        void ObjectAltSponge();
        /// "Object/Objects/Sierpinski Gasket" menu item selected
        void ObjectGasket();
        /// "Object/Objects/Rotope" menu item selected
        void ObjectRotope();
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

        /// insert a menu item with a specified slot into a specified menu
        QAction *insertAction(QMenu *, const QString &, const char * = 0,
                              bool = true);
        /// insert a menu item creating a RealFunction object into a specified menu
        QAction *insertAction(QMenu *, const QString &,
                              RealFunctionFactory *, bool = true);
        /// insert a menu item creating a Surface object into a specified menu
        QAction *insertAction(QMenu *, const QString &,
                              SurfaceFactory *, bool = true);

        C4DView *_parent;       ///< the C4DView containing this menu

        QMenu *_functions;      ///< The "Object" menu
        QMenu *_fr3r;           ///< The "Object/f:R^3 -> R" submenu
        QMenu *_objects;        ///< The "Object/Objects" submenu
        QMenu *_surfaces;       ///< The "Object/Surfaces" submenu
        QMenu *_fcc;            ///< The "Object/Surfaces/f:C -> C" submenu
        QMenu *_appear;         ///< The "Appearance" menu
        QMenu *_color;          ///< The "Appearance/Color Schemes" submenu
        QMenu *_animation;      ///< The "Animation" menu
        QMenu *_help;           ///< The "Help" menu

        MenuMapType menuMap;    ///< Keeps the QActions belonging to the menu entries
};

#endif
