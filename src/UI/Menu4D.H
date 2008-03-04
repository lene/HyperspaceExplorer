
#include <QMenu>
#include <map>

class C4DView;
class QString;

class Menu4D: public QMenu {
    public:
        Menu4D(C4DView *);
    
//        void updateFunctionMenu(const QString &);
        void updateFunctionMenu(int);
        QAction *getAction(const QString &key) {
            return actionMap[key];
        }
    private:
        QAction *insertAction(QMenu *_menu, const QString &title, 
                              const char *slot) {
            QAction *tmp =
                _menu->addAction(
                    title, (const QObject *)parent, (const char *)slot,
                    (const QKeySequence &)0);
            actionMap.insert(std::pair<QString, QAction *>(title, tmp));
            return tmp;
        }
        
        C4DView *parent;
        QMenu *functions, *appear, *animation, *help;
        
        QAction *linesAction, *crossAction, *hyperfogAction, *pixmapAction,
                *lightAction, *fogAction, *transparentAction, *shadeAction,
                *colorsAction;
        QAction *funcAction[32];
        std::map<QString, QAction *> actionMap;
};
