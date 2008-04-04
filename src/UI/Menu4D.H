
#ifndef MENU4D_H
#define MENU4D_H

#include <QMenu>
#include <map>

class QString;
class QMenuBar;
class C4DView;
class Function;
class RealFunctionFactory;
class SurfaceFactory;

/** The menu for the C4DView. \n
 *  This class has been outsourced from C4DView to keep C4DView of a managable
 *  size.
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Menu4D: public QMenu {
    public:
        Menu4D(C4DView *);

        void updateFunctionMenu(const QString &);

        QAction *&getAction(const QString &key);

        void addToMenuBar(QMenuBar *menuBar);

        typedef std::map<QString, QAction *> ActionMapType;
        typedef std::map<QMenu *, ActionMapType> MenuMapType;

    private:
        QAction *insertAction(QMenu *, const QString &, const char *,
                              bool = true);
        QAction *insertAction(QMenu *, const QString &,
                              RealFunctionFactory *, bool = true);
        QAction *insertAction(QMenu *, const QString &,
                              SurfaceFactory *, bool = true);
        QAction *insertAction(QMenu *_menu, const Function *function,
                                 const char *slot, bool checkable = true);
        C4DView *parent;
        QMenu *functions, *appear, *animation, *help,
              *fr3r, *objects, *surfaces, *fcc;

        MenuMapType menuMap;
};

#endif
