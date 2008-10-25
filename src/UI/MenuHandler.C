//
// C++ Implementation: MenuHandler
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <sstream>
#include <iomanip>

#include "MenuHandler.H"
#include "Menu4D.H"

#include "Function.H"
#include "Surface.H"
#include "ComplexFunction.H"
#include "Object.H"
#include "AnimationDialogImpl.H"
#include "Help.H"

using std::ostringstream;
using std::cerr;
using std::endl;
using std::ends;


C4DView::MenuHandler::~MenuHandler() { }

/// Switch between wireframe and solid display
/** Account for antialiasing only in wireframe mode
 *
 *  Change menu items accordingly                   */
void C4DView::MenuHandler::Wireframe() {
    if (m_parent->DisplayPolygons()) {
        m_parent->Menu()->getAction("Wireframe")->setText("Solid");
        m_parent->Menu()->getAction("Transparence")->setText("Line Antialiasing");
    } else {
        m_parent->Menu()->getAction("Wireframe")->setText("Wireframe");
        m_parent->Menu()->getAction("Transparence")->setText("Transparence");
        glDisable (GL_CULL_FACE);
    }
    m_parent->Menu()->getAction("Wireframe")->setChecked (m_parent->DisplayPolygons());
    m_parent->setWireframe (m_parent->DisplayPolygons());

    m_parent->OnPaint ();
}

/// Switch coordinate cross on or off
/** Change menu items accordingly       */
void C4DView::MenuHandler::Coordinates() {
    m_parent->setCoordinates(!m_parent->DisplayCoordinates());
}

/// Switch 4D depth cue on or off
/** Change menu items accordingly */
void C4DView::MenuHandler::HyperFog() {
    m_parent->setHyperfog(!m_parent->DepthCue4D());
}

/// Switch lighting on or off
/** Change menu items accordingly
 *  \todo uses hardcoded values for light attributes
 *  \todo move all the GL stuff away from the menu handler, back into C4DView
 */
void C4DView::MenuHandler::Light() {
    m_parent->setLighting(!m_parent->Lighting());
    if (m_parent->Lighting()) {
        glEnable(GL_LIGHTING);                  //  turn on the light

        static GLfloat LightAmbient[]  = { 0.3f, 0.3f, 0.3f, 1.0f }, //  HARDCODED VALUES
                        LightDiffuse[]  = { 0.9f, 0.9f, 0.9f, 1.0f },
                        LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f },
                        LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //  light properties

        glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); // set the light properties
        glLightfv (GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
        glLightfv (GL_LIGHT0, GL_SPECULAR, LightSpecular);
        glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
        glEnable  (GL_LIGHT0);   // turn on the light
    } else {
        static GLfloat LightAmbient[]  = { 1.0f, 1.0f, 1.0f, 0.0f },
        LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //      light properties

        glEnable  (GL_LIGHTING);
        glLightfv (GL_LIGHT0, GL_AMBIENT, LightAmbient); // set the light properties
        glLightfv (GL_LIGHT0, GL_DIFFUSE, LightAmbient);
        glLightfv (GL_LIGHT0, GL_SPECULAR, LightAmbient);
        glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
        glEnable  (GL_LIGHT0);    //      turn on the light
    }

    m_parent->OnPaint ();
}

/// Toggle colors
void C4DView::MenuHandler::Colors () {
    m_parent->setColors(!m_parent->getColors());
}

/// Toggle fog/depth cue
void C4DView::MenuHandler::Fog () {
    m_parent->setFog(!m_parent->getFog());
}

/// Toggle object transparency
void C4DView::MenuHandler::Transparent () {
    m_parent->setTransparence(!m_parent->getTransparent());
}

/// Toggle shading
void C4DView::MenuHandler::Shade () {
    m_parent->setShading(!m_parent->getShade());
}

/// Run a benchmark test
void C4DView::MenuHandler::Benchmark() {
    ostringstream Time;

    double time_4d = m_parent->Benchmark4D (360, 1., 0., 0.);

    Time << "4D viewpoint rotation: " << time_4d << " sec."
         << " (" << 360/1./time_4d << " fps)" << endl;

    float time_3d = m_parent->Benchmark3D (360, 1., 0., 0.);

    Time << "3D viewpoint rotation: " << time_3d << " sec."
         << " (" << 360/1./time_3d << " fps)" << ends;

    QMessageBox::information (NULL, "Benchmark results", Time.str ().c_str ());
    m_parent->UpdateStatus ();
}

/// Switch rendering to files on or off
/** Change menu items accordingly        */
void C4DView::MenuHandler::RenderToImages() {
    m_parent->setRenderToPixmap(!m_parent->RenderToPixmap());
    m_parent->Menu()->getAction("Render to Images")->setChecked(m_parent->RenderToPixmap());
}
/// Display a ObjectHypercube object
void C4DView::MenuHandler::ObjectHypercube() {
    m_parent->ObjectHypercube();
}

/// Display a ObjectHyperpyramid object
void C4DView::MenuHandler::ObjectHyperpyramid() {
    m_parent->ObjectHyperpyramid();
}

/// Display a ObjectHypersponge object
void C4DView::MenuHandler::ObjectHypersponge() {
    m_parent->ObjectHypersponge();
}

/// Display a ObjectGasket object
void C4DView::MenuHandler::ObjectGasket() {
    m_parent->ObjectGasket();
}

/// Display a customFunction object
void C4DView::MenuHandler::customFunction() {
    CustomFunctionSlot<CustomFunction>::createCustomFunction(m_parent);
}

/// Display a customPolarFunction object
void C4DView::MenuHandler::customPolarFunction() {
    CustomFunctionSlot<CustomPolarFunction>::createCustomFunction(m_parent);
}

/// Display a customSurface object
void C4DView::MenuHandler::customSurface() {
    CustomFunctionSlot<CustomSurface>::createCustomSurface(m_parent);
}

/// Display a customComplexFunction object
void C4DView::MenuHandler::customComplexFunction() {
    CustomFunctionSlot<CustomComplexFunction>::createCustomSurface(m_parent);
}


/// Show a dialog to adjust animation settings
/** Where to write image files and how many files to write. */
void C4DView::MenuHandler::AnimationSettings() {
    UI::Dialogs::AnimationDialogImpl *Dlg = new UI::Dialogs::AnimationDialogImpl;
    if (Dlg->exec () == QDialog::Accepted) {
        m_parent->setanimationMaxFrames(Dlg->getFrames());
        m_parent->setanimationDirectory(Dlg->getDir());
        m_parent->setanimationPrefix(Dlg->getPrefix());
        SingletonLog::Instance()
                << "animationMaxFrames: " << (long)m_parent->animationMaxFrames()
                << ", animationDirectory: " << m_parent->animationDirectory().toStdString()
                << ", animationPrefix: "<< m_parent->animationPrefix().toStdString() << "\n";
    }
}

/// Display help window
void C4DView::MenuHandler::Help () {
    static HelpWindow *H;
    H = new HelpWindow (HelpFile.c_str());
    H->show();
}

/// Open an "About"-Dialog
void C4DView::MenuHandler::about() {
    QMessageBox::about(m_parent, "Hyperspace Explorer",
                       "<p>A program to view four-dimensional objects "
                               "using OpenGL and the Qt GUI library.</p>"
                               "<p>author: "+QString(make_str(PACKAGE_BUGREPORT))+"</p>"
                               "<p>version: "+QString(make_str(PACKAGE_VERSION))+
                               " of "+QString(__DATE__)+"</p>"
                      );
}

/// Open an "About Qt"-Dialog
void C4DView::MenuHandler::aboutQt() {
    QMessageBox::aboutQt(m_parent, "Hyperspace Explorer" );
}

