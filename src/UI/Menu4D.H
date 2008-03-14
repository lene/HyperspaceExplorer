
#include <QMenu>
#include <map>

class C4DView;
class QString;
class QMenuBar;

class Menu4D: public QMenu {
    public:
        Menu4D(C4DView *);
    
        void updateFunctionMenu(const QString &);
        
        QAction *&getAction(const QString &key);
        
        void addToMenuBar(QMenuBar *menuBar);
        
        typedef std::map<QString, QAction *> ActionMapType;
        typedef std::map<QMenu *, ActionMapType> MenuMapType;
        
    private:
        QAction *insertAction(QMenu *_menu, const QString &title, 
                              const char *slot, bool checkable = true);
/*        QAction *insertActionNew(QMenu *_menu, const QString &title, 
                                 const char *slot, bool checkable = true);*/
        C4DView *parent;
        QMenu *functions, *appear, *animation, *help,
              *fr3r, *objects, *surfaces, *fcc;
        
        MenuMapType menuMap;
};
