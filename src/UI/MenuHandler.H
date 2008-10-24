//
// C++ Interface: MenuHandler
//
// Description: 
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "4DView.H"

/// Callback functions for menu items
/** Basically, all member functions are slots called by the Menu4D's items.\n
 *  Most of these slots must translate a parameter-less call to a state change
 *  in the associated C4DView.
 *  \todo Rework the member functions so that they work with a generic UI::View
 *  object instead of an explicitly specified C4DView.
 */
class C4DView::MenuHandler: public QObject {

    Q_OBJECT

    public slots:

        void Wireframe();
        void Coordinates();
        void HyperFog();
        void Light();
        void Colors();
        void Fog();
        void Transparent();
        void Shade();
        void Benchmark();
        void RenderToImages();

        void ObjectHypercube();
        void ObjectHyperpyramid();
        void ObjectHypersponge();
        void ObjectGasket();
        void customFunction();
        void customPolarFunction();
        void customSurface();
        void customComplexFunction();

        void AnimationSettings();
        void Help();
        void about ();
        void aboutQt ();

    public:
        MenuHandler(C4DView *parent): m_parent(parent) { }
        virtual ~MenuHandler();

    private:
        C4DView *m_parent;  ///< The associated C4DView
};
