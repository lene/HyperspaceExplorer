
#ifndef MENU4D_H
#define MENU4D_H

#include <QMenu>
#include <map>

class QString;
class QMenuBar;
class C4DView;
class RealFunctionFactory;
class SurfaceFactory;

/// The menu for the C4DView
/** This class has been outsourced from C4DView to keep C4DView to a managable
 *  size.
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Menu4D: public QMenu {
    public:
        Menu4D(C4DView *);

        void updateFunctionMenu(const QString &);

        QAction *&getAction(const QString &key);

        void addToMenuBar(QMenuBar *menuBar);

    private:
        /// Assigns a QAction to a menu title
        typedef std::map<QString, QAction *> ActionMapType;
        /// Manages an ActionMap for each submenu
        typedef std::map<QMenu *, ActionMapType> MenuMapType;
        
        QAction *insertAction(QMenu *, const QString &, const char *,
                              bool = true);
        QAction *insertAction(QMenu *, const QString &,
                              RealFunctionFactory *, bool = true);
        QAction *insertAction(QMenu *, const QString &,
                              SurfaceFactory *, bool = true);

        C4DView *parent;        ///< the C4DView containing this menu
        QMenu *functions, *appear, *animation, *help,
              *fr3r, *objects, *surfaces, *fcc;

        MenuMapType menuMap;    ///< Keeps the QActions belonging to the menu entries
};

#endif
