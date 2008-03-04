#include <map>

#include <QShortcut>

#include "Menu4D.H"
#include "4DView.H"

inline void TESTED_FEATURE(QAction *item) {
# ifdef TESTFEATURES
    item->setEnabled (true);
# else
    item->setEnabled (false);
#endif
}

Menu4D::Menu4D(C4DView *_parent):
    parent(_parent) {
    
    functions = addMenu("Object");
    appear = addMenu("Appearance");
    animation = addMenu("Animation");
    help = addMenu("Help");
    
    ////////////////////////////////////////////////////////////////////////////
    //      "Objects" Menu
    ////////////////////////////////////////////////////////////////////////////
    QMenu *fr3r = functions->addMenu("f: R³ -> R"),
          *objects = functions->addMenu("Objects"),
          *surfaces = functions->addMenu("Surfaces"), 
          *fcc = surfaces->addMenu("f: C -> C");

    insertAction(fr3r, "1/(r²+1)", SLOT(FR3R()));
    insertAction(fr3r, "Gravitation Potential", SLOT(GravPotential()));
    insertAction(fr3r, "sin (r²)", SLOT(SinR()));
    insertAction(fr3r, "exp (r²)", SLOT(ExpR()));
    insertAction(fr3r, "Custom function", SLOT(customFunction()));
    
    insertAction(fr3r, "Polar: r = sin (pi/3.*(t+u+v))", SLOT(Sin2()));
    insertAction(fr3r, "Polar: r = 1/2+sin (Phase*pi*t*u*v)", SLOT(Sin()));
    insertAction(fr3r, "Polar: r = sqrt (t²+u²+v²)", SLOT(FunctionR()));
    insertAction(fr3r, "Custom polar function", SLOT(customPolarFunction()));

    insertAction(objects, "Hypersphere", SLOT(FunctionHypersphere()));
    insertAction(objects, "Hypercube", SLOT(ObjectHypercube()));
    insertAction(objects, "Hyperpyramid", SLOT(ObjectHyperpyramid()));
    insertAction(objects, "Menger Sponge", SLOT(ObjectHypersponge()));
    insertAction(objects, "Sierpinski Gasket", SLOT(ObjectGasket()));
    insertAction(objects, "Torus 1", SLOT(FunctionTorus1()));
    insertAction(objects, "Torus 2", SLOT(FunctionTorus2()));
    insertAction(surfaces, "Surface1", SLOT(Surface_1()));
    insertAction(surfaces, "Horizon", SLOT(SurfaceHorizon()));
    insertAction(surfaces, "Torus 3", SLOT(SurfaceTorus3()));
    insertAction(surfaces, "Custom surface", SLOT(customSurface()));
    TESTED_FEATURE (getAction("Custom surface"));

    insertAction(fcc, "z²", SLOT(ComplexZ2()));
    insertAction(fcc, "z³", SLOT(ComplexZ3()));
    insertAction(fcc, "z^a", SLOT(ComplexZA()));
    insertAction(fcc, "e^z", SLOT(ComplexEZ()));
    insertAction(fcc, "e^-z²", SLOT(ComplexEMZ2()));
    insertAction(fcc, "1/z", SLOT(ComplexZM1()));
    insertAction(fcc, "1/z²", SLOT(ComplexZM2()));
    insertAction(fcc, "sqrt (z)", SLOT(ComplexSqrtZ()));
    insertAction(fcc, "ln (z)", SLOT(ComplexLnZ()));
    insertAction(fcc, "sin (z)", SLOT(ComplexSinZ()));
    insertAction(fcc, "cos (z)", SLOT(ComplexCosZ()));
    insertAction(fcc, "sinh (z)", SLOT(ComplexSinhZ()));
    insertAction(fcc, "cosh (z)", SLOT(ComplexCoshZ()));
    insertAction(fcc, "tan (z)", SLOT(ComplexTanZ()));
    insertAction(fcc, "Custom complex function", SLOT(customComplexFunction()));
    TESTED_FEATURE (getAction("Custom complex function"));
    
    functions->setCheckable (true);
        
    ////////////////////////////////////////////////////////////////////////////
    //      "Appearance" Menu
    ////////////////////////////////////////////////////////////////////////////
    insertAction(appear, "Colors", SLOT(Colors ()));
    insertAction(appear, "Shading", SLOT(Shade()));
    insertAction(appear, "Depth Cue", SLOT(Fog()));
    insertAction(appear, "Transparence", SLOT(Transparent()));
    insertAction(appear, "Lighting", SLOT(Light()));
    insertAction(appear, "Wireframe", SLOT(Wireframe()));
    insertAction(appear, "Coordinate Cross", SLOT(Coordinates()));

    appear->setCheckable (true);

    getAction("Colors")->setChecked(parent->getColors());
    getAction("Shading")->setChecked(parent->getShade());
    getAction("Depth Cue")->setChecked(parent->getFog());
    getAction("Lighting")->setChecked(parent->getLight()); 
    getAction("Transparence")->setChecked(parent->getTransparent());
    getAction("Coordinate Cross")->setChecked(parent->getDisplayCoordinates()); 

    insertAction(help, "Online help", SLOT(Help ()));
    help->insertSeparator ();
    help->insertItem( QObject::tr("&About ..."), parent, SLOT( about() ) );
    help->insertItem( QObject::tr("About &Qt ..."), parent, SLOT( aboutQt() ) );

            //  addAction("Rotate",     parent, SLOT(Rotate()));
    insertSeparator ();
    addAction("Quit",       qApp, SLOT(quit ()));
            
    
    insertAction(animation, "Render to Images", SLOT(RenderToImages()));
    getAction("Render to Images")->setChecked(parent->getRenderToPixmap());
    TESTED_FEATURE (getAction("Render to Images"));

    insertAction(animation, "Animation Settings", SLOT(AnimationSettings()));
    TESTED_FEATURE (getAction("Animation Settings"));
    
    insertAction(animation, "Benchmark", SLOT (Benchmark()));
    insertAction(appear, "4D Depth Cue", SLOT(HyperFog()));

    if (parent->getDisplayPolygons()) {
        getAction("Wireframe")->setText("Solid");
        getAction("Transparence")->setText("Line Antialiasing");
        getAction("Transparence")->setEnabled(true);
    }
    else {
        getAction("Wireframe")->setText("Wireframe");
        getAction("Transparence")->setText("Transparence");
        TESTED_FEATURE (getAction("Transparence"));	
    }
      //      appear->setItemEnabled (transparentAction, DisplayPolygons);
    parent->SetWireframe (parent->getDisplayPolygons());
}

/*******************************************************************************
 *  rotate in 3D 360 degrees
 */
void Menu4D::updateFunctionMenu (const QString &item) {
    /*  for (unsigned i = 0; i < 32; i++)
    functions->setItemChecked (i, false);
    */
    getAction(item)->setChecked(true);
}
