#include "Menu4D.H"
#include "4DView.H"

inline void TESTED_FEATURE(Q3PopupMenu *menu, int item) {
# ifdef TESTFEATURES
    menu->setItemEnabled (item, true);
# else
    menu->setItemEnabled (item, false);
#endif
}

Menu4D::Menu4D(C4DView *_parent):
    parent(_parent),
    functions(new Q3PopupMenu), appear(new Q3PopupMenu), 
    animation(new Q3PopupMenu), help(new Q3PopupMenu) {
    
    ////////////////////////////////////////////////////////////////////////////
    //      "Objects" Menu
    ////////////////////////////////////////////////////////////////////////////
    Q3PopupMenu *fr3r = new Q3PopupMenu, *objects = new Q3PopupMenu,
                *surfaces = new Q3PopupMenu, *fcc = new Q3PopupMenu;

    fr3r->insertItem ("1/(r²+1)", parent, SLOT(FR3R()));
    fr3r->insertItem ("Gravitation Potential", parent, SLOT(GravPotential()));
    fr3r->insertItem ("sin (r²)", parent, SLOT(SinR()));
    fr3r->insertItem ("exp (r²)", parent, SLOT(ExpR()));
    int tmp = fr3r->insertItem ("Custom function", parent, SLOT(customFunction()));    
    //    TESTED_FEATURE (fr3r, tmp);

    fr3r->insertItem ("Polar: r = sin (pi/3.*(t+u+v))", parent, SLOT(Sin2()));
    fr3r->insertItem ("Polar: r = 1/2+sin (Phase*pi*t*u*v)", parent, SLOT(Sin()));
    fr3r->insertItem ("Polar: r = sqrt (t²+u²+v²)", parent, SLOT(FunctionR()));
    tmp = fr3r->insertItem ("Custom polar function", parent, SLOT(customPolarFunction()));
    //    TESTED_FEATURE (fr3r, tmp);

    objects->insertItem ("Hypersphere", parent, SLOT(FunctionHypersphere()));
    objects->insertItem ("Hypercube", parent, SLOT(ObjectHypercube()));
    objects->insertItem ("Hyperpyramid", parent, SLOT(ObjectHyperpyramid()));
    objects->insertItem ("Menger Sponge", parent, SLOT(ObjectHypersponge()));
    objects->insertItem ("Sierpinski Gasket", parent, SLOT(ObjectGasket()));
    objects->insertItem ("Torus 1", parent, SLOT(FunctionTorus1()));
    objects->insertItem ("Torus 2", parent, SLOT(FunctionTorus2()));
    surfaces->insertItem ("Surface1", parent, SLOT(Surface_1()));
    surfaces->insertItem ("Horizon", parent, SLOT(SurfaceHorizon()));
    surfaces->insertItem ("Torus 3", parent, SLOT(SurfaceTorus3()));
    tmp = surfaces->insertItem ("Custom surface", parent, SLOT(customSurface()));
    TESTED_FEATURE (surfaces, tmp);

    fcc->insertItem ("z²", parent, SLOT(ComplexZ2()));
    fcc->insertItem ("z³", parent, SLOT(ComplexZ3()));
    fcc->insertItem ("z^a", parent, SLOT(ComplexZA()));
    fcc->insertItem ("e^z", parent, SLOT(ComplexEZ()));
    fcc->insertItem ("e^-z²", parent, SLOT(ComplexEMZ2()));
    fcc->insertItem ("1/z", parent, SLOT(ComplexZM1()));
    fcc->insertItem ("1/z²", parent, SLOT(ComplexZM2()));
    fcc->insertItem ("sqrt (z)", parent, SLOT(ComplexSqrtZ()));
    fcc->insertItem ("ln (z)", parent, SLOT(ComplexLnZ()));
    fcc->insertItem ("sin (z)", parent, SLOT(ComplexSinZ()));
    fcc->insertItem ("cos (z)", parent, SLOT(ComplexCosZ()));
    fcc->insertItem ("sinh (z)", parent, SLOT(ComplexSinhZ()));
    fcc->insertItem ("cosh (z)", parent, SLOT(ComplexCoshZ()));
    fcc->insertItem ("tan (z)", parent, SLOT(ComplexTanZ()));
    tmp = fcc->insertItem ("Custom complex function", parent, SLOT(customComplexFunction()));
    TESTED_FEATURE (fcc, tmp);

    functions->insertItem ("f: R³ -> R", fr3r, -1, 0);
    functions->insertItem ("Objects", objects, -1, 1);
    surfaces->insertItem ("f: C -> C", fcc, -1, 0);
    functions->insertItem ("Surfaces", surfaces, -1, 2);
    
    functions->setCheckable (true);
    
    insertItem ("Object", functions, -1, 0);
    
    ////////////////////////////////////////////////////////////////////////////
    //      "Appearance" Menu
    ////////////////////////////////////////////////////////////////////////////
    colorsID     = appear->insertItem ("Colors",       parent, SLOT(Colors ()));
    shadeID      = appear->insertItem ("Shading",      parent, SLOT(Shade()));
    fogID        = appear->insertItem ("Depth Cue",    parent, SLOT(Fog()));
    transparentID= appear->insertItem ("Transparence", parent, SLOT(Transparent()));
    lightID      = appear->insertItem ("Lighting",     parent, SLOT(Light()));
    linesID      = appear->insertItem ("Wireframe", parent, SLOT(Wireframe()));
    crossID      = appear->insertItem ("Coordinate Cross", parent, SLOT(Coordinates()));

    appear->setCheckable (true);

    appear->setItemChecked (colorsID, colors);
    appear->setItemChecked (shadeID, shade);
    appear->setItemChecked (fogID, fog);
    appear->setItemChecked (lightID, light); 
    appear->setItemChecked (transparentID, transparent);
    appear->setItemChecked (crossID, DisplayCoordinates); 

    help->insertItem ("Online help",       parent, SLOT(Help ()));
    help->insertSeparator ();
    help->insertItem( QObject::tr("&About ..."), parent, SLOT( about() ) );
    help->insertItem( QObject::tr("About &Qt ..."), parent, SLOT( aboutQt() ) );

    insertItem ("Appearance", appear); 
            //  insertItem ("Rotate",     parent, SLOT(Rotate()));
    insertItem ("Help", help); 
    insertSeparator ();
    insertItem ("Quit",       qApp, SLOT(quit ()));
            
    
    pixmapID = animation->insertItem ("Render to Images", parent, SLOT(RenderToImages()));
    animation->setItemChecked (pixmapID, RenderToPixmap);
    TESTED_FEATURE (animation, pixmapID);

    tmp = animation->insertItem ("Animation Settings", parent, SLOT(AnimationSettings()));
    TESTED_FEATURE (animation, tmp);
    
    animation->insertItem ("Benchmark", parent, SLOT (Benchmark()), (const QKeySequence &)0, -1, 2);
    hyperfogID = appear->insertItem ("4D Depth Cue", parent, SLOT(HyperFog()), (const QKeySequence &)0, -1, 3);
    
      
    insertItem ("Animation", animation, -1, 2);

    if (DisplayPolygons) {
        appear->changeItem (linesID, "Solid");
        appear->changeItem (transparentID, "Line Antialiasing");
        appear->setItemEnabled (transparentID, true);
    }
    else {
        appear->changeItem (linesID, "Wireframe");
        appear->changeItem (transparentID, "Transparence");
        TESTED_FEATURE (appear, transparentID);	
    }
      //      appear->setItemEnabled (transparentID, DisplayPolygons);
    parent->SetWireframe (DisplayPolygons);
}
