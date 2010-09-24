
//      project:      hyperspace explorer
//      module:       Object.C
//      contains:     four-dimensional objects which cannot be defined as a
//                    function
//      compile with: make all
//      author:       helge preuss (lene.preuss@gmail.com)
//      license:      GPL (see License.txt)



#include "Globals.h"
#include "ColorManager.h"
#include "Log.h"

#include "Matrix.h"
#include "Transform.h"

#include "Object.h"

using std::cerr;
using std::endl;

using VecMath::Vector;
using VecMath::Matrix;

///////////////////////////////////////////////////////////////////////////////


/** generic Object constructor; only allocates necessary arrays, children must
 *  fill them in their c'tor
 *  @param vertices number of vertices
 *  @param surfaces number of surfaces                                        */
Object::Object (unsigned vertices, unsigned surfaces):
        Function (),
        X(vec4vec1D(vertices)), Xtrans(vec4vec1D(vertices)), Xscr(vec3vec1D()),
        Surface(surfaces) {

    for (unsigned i = 0; i < surfaces; i++) Surface[i].resize(4);
}

/// Actually create the Object, this method is overridden in child classes
/** Calibrates the color manager from the vertices of the object.
 *
 *  In child classes, this method should be reimplemented to set up the arrays
 *  \p X and \p Surface. When that is finished, the reimplementation should
 *  call \code Object::Initialize() \endcode at the end of its own Initialize()
 *  routine to calibrate the color manager.
 */
void Object::Initialize() {
    calibrateColors();
}

void Object::calibrateColors() const {
    for (unsigned i = 0; i < X.size(); i++) {
        ColMgrMgr::Instance().calibrateColor(
            X[i],
            Color((X[i][0]+1)/2, (X[i][1]+1)/2, (X[i][2]+1)/2,
                  .75-(X[i][3]+1)/4));
    }
}

/** \param newX The array of vertices to be copied to \p X */
void Object::setX(const vec4vec1D &newX) {
    X = newX;
    Xtrans.resize(X.size());
    Xscr.resize(X.size());
}

/// Transforms an Object
/** @param R Rotation
 *  @param T Translation
 */
void Object::Transform (const VecMath::Rotation<4> &R,
                        const VecMath::Vector<4> &T) {
    Matrix<4> Rot(R);
    Xtrans.resize(X.size());
    transform<vec4vec1D, 4>::xform(Rot, T, X, Xtrans);
}

/// Projects an Object into three-space
/** @param scr_w w coordinate of screen
 *  @param cam_w w coordinate of camera
 *  @param depthcue4d wheter to use hyperfog/dc                               */
void Object::Project (double scr_w, double cam_w, bool depthcue4d) {

    double ProjectionFactor;
    double Wmax = 0, Wmin = 0;

    Xscr.resize(Xtrans.size());

    for (unsigned i = 0; i < Xtrans.size(); i++) {
        if (depthcue4d) {
            if (Xtrans[i][3] < Wmin) Wmin = Xtrans[i][3];
            if (Xtrans[i][3] > Wmax) Wmax = Xtrans[i][3];
        }

        ProjectionFactor = (scr_w-cam_w)/(Xtrans[i][3]-cam_w);

        for (unsigned j = 0; j <= 2; j++) {
            Xscr[i][j] = ProjectionFactor*Xtrans[i][j];
        }
    }

    if (!depthcue4d) return;

    //  apply hyperfog
    for (unsigned i = 0; i < X.size(); i++) {
        ColMgrMgr::Instance().depthCueColor(Wmax, Wmin, Xtrans[i][3], X[i]);
    }
}

#include <GL/gl.h>
/// Draw the projected Object (onto screen or into GL list, as it is)
void Object::Draw(UI::View *view) {
    glBegin (GL_QUADS);
    for (unsigned i = 0; i < Surface.size(); ++i) {
        for (unsigned j = 0; j < 4; j++) {
            if (Surface[i][j] < X.size() && Surface[i][j] < Xscr.size()) {
                setVertex(X[Surface[i][j]], Xscr[Surface[i][j]]);
            }
        }
    }
    glEnd ();
}

/** Reinitialize an Object. This function is called when the initialization is
 *  done outside the constructor.
 *
 *  Currently it does not differ from Initialize(). In fact, it simply calls
 *  Initialize().
 */
void Object::ReInit (double, double, double,
                     double, double, double,
                     double, double, double) {
    SingletonLog::Instance() << "Object::ReInit()\n";
    Initialize();
}

void Object::for_each(Function::function_on_fourspace_vertex apply) {
  std::for_each(X.begin(), X.end(), apply);
}

void Object::for_each(Function::function_on_projected_vertex apply) {
  std::for_each(Xscr.begin(), Xscr.end(), apply);
}

////////////////////////////////////////////////////////////////////////////////

/// Hypercube constructor
/** \param center center
 *  \param a side_length/2
 */
Hypercube::Hypercube (double a, const VecMath::Vector<4> &center):
    Object (16, 24),
    _a (a), _center(center) {
  declareParameter("Size", 1.0);
  Initialize();
}

#   if !USE_INT_INDICES
void Hypercube::Draw(UI::View *view) {
    glBegin (GL_QUADS);
    for (surface_vec_type::const_iterator i = Surface.begin(); i != Surface.end(); ++i) {
        for (unsigned j = 0; j < 4; j++) {
            if ((*i)[j] && i->index(j) < Xscr.size()) {
                setVertex(*((*i)[j]), Xscr[i->index(j)]);
            }
        }
    }
    glEnd ();
}
#endif

/// Actually creates the Hypercube
/** sets up the vertices of the Hypercube in \p X[], then sets up the surfaces
 *  of the Hypercube by declaring the appropriate squares as a list in
 *  \p Surface[][].                                                           */
void Hypercube::Initialize(void) {

    if (X.size() < 16) X.resize(16);

    for (int x = 0; x <= 1; x++)
        for (int y = 0; y <= 1; y++)
            for (int z = 0; z <= 1; z++)
                for (int w = 0; w <= 1; w++) {
                    X[x+2*(y+2*(z+2*w))] =
                        Vector<4> (2.*x-1., 2.*y-1., 2.*z-1., 2.*w-1.)*_a+_center;
                }

    if (Surface.size() < 24) Surface.resize(24);

    DeclareSquare (0,   0, 1, 3, 2);
    DeclareSquare (1,   0, 1, 5, 4);
    DeclareSquare (2,   0, 1, 9, 8);
    DeclareSquare (3,   0, 2, 6, 4);
    DeclareSquare (4,   0, 2,10, 8);
    DeclareSquare (5,   0, 4,12, 8);
    DeclareSquare (6,   1, 3, 7, 5);
    DeclareSquare (7,   1, 3,11, 9);
    DeclareSquare (8,   1, 5,13, 9);
    DeclareSquare (9,   2, 3, 7, 6);
    DeclareSquare (10,  2, 3,11,10);
    DeclareSquare (11,  2, 6,14,10);
    DeclareSquare (12,  3, 7,15,11);
    DeclareSquare (13,  4, 5, 7, 6);
    DeclareSquare (14,  4, 5,13,12);
    DeclareSquare (15,  4, 6,14,12);
    DeclareSquare (16,  5, 7,15,13);
    DeclareSquare (17,  6, 7,15,14);
    DeclareSquare (18,  8, 9,11,10);
    DeclareSquare (19,  8, 9,13,12);
    DeclareSquare (20,  8,10,14,12);
    DeclareSquare (21,  9,11,15,13);
    DeclareSquare (22, 10,11,15,14);
    DeclareSquare (23, 12,13,15,14);

    Object::Initialize();

#   if !USE_INT_INDICES
#     if 0
        for (surface_vec_type::iterator i = Surface.begin(); i != Surface.end(); ++i) i->print();
#     endif
#   endif

}

/// Declare a square in the \p Surface array
/** \param i index of the square
 *  \param a index of vertex 1
 *  \param b index of vertex 2
 *  \param c index of vertex 3
 *  \param d index of vertex 4
 *  \param offset if there are multiple cubes, the index of the cube
 */
void Hypercube::DeclareSquare (unsigned i, unsigned a, unsigned b, unsigned c, unsigned d, unsigned offset) {
  if (Surface.size() < i+offset*24) Surface.resize(i+offset*24);
# if USE_INT_INDICES
    if (Surface[i+offset*24].size() < 4) Surface[i+offset*24].resize(4);
    Surface[i+offset*24][0] = a+offset*16;
    Surface[i+offset*24][1] = b+offset*16;
    Surface[i+offset*24][2] = c+offset*16;
    Surface[i+offset*24][3] = d+offset*16;
# else
#     if 0
        std::cerr << "Surface.size() = " << Surface.size() << ", X.size() = " << X.size()
              << " i: " << i+offset*24 << " a: " << a+offset*16 << " b: " << b+offset*16 << " c: " << c+offset*16 << " d: " << d+offset*16 << std::endl;
#     endif
    Surface[i+offset*24] = SurfaceType<4, 4>(X, X[a+offset*16], X[b+offset*16], X[c+offset*16], X[d+offset*16]);
# endif
}


////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

/// Pyramid (hypersimplex) constructor
/** @param _center center
 *  @param _a side_length/2                                                   */
Pyramid::Pyramid (double _a, const VecMath::Vector<4> &_center):
        Object (5, 10),
        center(_center), a (_a) {
    declareParameter("Size", 1.0);
    Initialize();
}

/// Actually creates the Pyramid
/** \see Hypercube::Initialize() */
void Pyramid::Initialize() {
    X[0] = Vector<4> (0.0, 0.0, 0.0, 0.0);
    X[1] = Vector<4> (1.0, 0.0, 0.0, 0.0);
    X[2] = Vector<4> (0.5, sqrt (3.)/2., 0.0, 0.0);
    X[3] = Vector<4> (0.5, sqrt (3.)/6., sqrt (2./3.), 0.0);
    X[4] = Vector<4> (0.5, sqrt (3.)/6., 1./sqrt (6.), 1./sqrt (2.));

    Vector<4> center_of_mass (0.5, sqrt (3.)/4., sqrt (1./6.), 1./sqrt (8.));
    for (unsigned i = 0; i < X.size(); i++)
        X[i] = X[i]*a+center-center_of_mass*a;

    DeclareTriangle (0,  0, 1, 2);
    DeclareTriangle (1,  0, 1, 3);
    DeclareTriangle (2,  0, 1, 4);
    DeclareTriangle (3,  0, 2, 3);
    DeclareTriangle (4,  0, 2, 4);
    DeclareTriangle (5,  0, 3, 4);
    DeclareTriangle (6,  1, 2, 3);
    DeclareTriangle (7,  1, 2, 4);
    DeclareTriangle (8,  1, 3, 4);
    DeclareTriangle (9,  2, 3, 4);

    Object::Initialize();
}

/// Declare a triangle in the \p Surface array
/** @param i index of the square
 *  @param a index of vertex 1
 *  @param b index of vertex 2
 *  @param c index of vertex 3                                                */
void Pyramid::DeclareTriangle (unsigned i, unsigned a, unsigned b, unsigned c) {
    Surface[i][0] = a;
    Surface[i][1] = b;
    Surface[i][2] = c;
    Surface[i][3] = c;
}


////////////////////////////////////////////////////////////////////////////


/// Gasket constructor
/** \param level hyper-sierpinski gasket level
 *  \param _rad side_length/2
 *  \param _center center                                                      */
Gasket::Gasket (unsigned level, double _rad, VecMath::Vector<4> _center):
        Level (level), rad(_rad), center(_center) {
//    setfunctionName("4-dimensional Sierpinski Gasket");
//    clearParameterNames();
    declareParameter("Level", 3);
    declareParameter("Size", 1.0);
    Initialize();
}

/// return the approximate amount of memory needed to display a gasket of current level
/** @todo uses hardcoded and experimentally found value for memory per simplex
 *  @return approx. mem required                                             */
unsigned long Gasket::MemRequired (void) {
    return (unsigned long) ((pow (5., (int)Level)*14.5)/1024+8)*1024*1024;
}

/// This function actually creates the Sierpinski Gasket
/** @see Sponge::Initialize() */
void Gasket::Initialize() {
    if (Level < 1)
        List.push_back (new Pyramid (rad, center));
    else {
        if (MemRequired () > Globals::Instance().getMaxMemory()) {
            cerr << "Sierpinski gasket of level " << Level
                 << " would require approx. " << MemRequired ()/1024/1024
                 << " MB of memory." << endl;
            if (Globals::Instance().checkMemory()) {
                cerr << "This is more than your available Memory of "
                     << Globals::Instance().getMaxMemory()/1024/1024 << "MB." << endl;
                while (MemRequired () > Globals::Instance().getMaxMemory()) Level--;
                cerr << "Using level " << Level << " instead." << endl;
            }
        }
        rad = rad/2;

        Vector<4> center_of_mass (0.5, sqrt (3.)/4., sqrt (1./6.), 1./sqrt (8.));

        Vector<4> NewCen = Vector<4> (0.0, 0.0, 0.0, 0.0);
        NewCen += center;
        List.push_back (new Gasket (Level-1, rad, NewCen));

        NewCen = Vector<4> (1.0, 0.0, 0.0, 0.0)*rad;
        NewCen += center;
        List.push_back (new Gasket (Level-1, rad, NewCen));

        NewCen = Vector<4> (0.5, sqrt (3.)/2., 0.0, 0.0)*rad;
        NewCen += center;
        List.push_back (new Gasket (Level-1, rad, NewCen));

        NewCen = Vector<4> (0.5, sqrt (3.)/6., sqrt (2./3.), 0.0)*rad;
        NewCen += center;
        List.push_back (new Gasket (Level-1, rad, NewCen));

        NewCen = Vector<4> (0.5, sqrt (3.)/6., 1./sqrt (6.), 1./sqrt (2.))*rad;
        NewCen += center;
        List.push_back (new Gasket (Level-1, rad, NewCen));
    }

    Object::Initialize();
}

/// Transforms a Gasket
/** \param R Rotation
 *  \param T Translation
 */
void Gasket::Transform (const VecMath::Rotation<4> &R,
                        const VecMath::Vector<4> &T) {
    for (unsigned i = 0; i < List.size (); i++)
        List[i]->Transform (R, T);
}

/// projects a Gasket into three-space
/** @param scr_w w coordinate of screen
 *  @param cam_w w coordinate of camera
 *  @param depthcue4d wheter to use hyperfog/dc                               */
void Gasket::Project (double scr_w, double cam_w, bool depthcue4d) {
    for (unsigned i = 0; i < List.size (); i++)
        List[i]->Project (scr_w, cam_w, depthcue4d);
}

/// draw the projected Gasket (onto screen or into GL list, as it is)
/** */
void Gasket::Draw (UI::View* view) {
    for (unsigned i = 0; i < List.size (); i++) List[i]->Draw(view);
}
