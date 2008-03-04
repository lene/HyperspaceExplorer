
#include <Q3PopupMenu>

class C4DView;

class Menu4D: public Q3PopupMenu {
    public:
        Menu4D(C4DView *);
    
    private:
        C4DView *parent;
        Q3PopupMenu *functions, *animation, *appear, *help;
        
        int linesID, crossID, hyperfogID, pixmapID,
            lightID, fogID, transparentID, shadeID,    //  appearance items
            colorsID;
        int funcID[32];

};
