
#include "ObjectImplementations.h"

#include "View.h"

#include "FunctionHolder.impl.h"
#include "Vector.impl.h"
#include "FacePolygon.impl.h"

using VecMath::Vector;
using VecMath::Matrix;

using std::cerr;
using std::endl;

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
    for (surface_vec_type::const_iterator i = Surface.begin(); i != Surface.end(); ++i) {
      view->drawQuadrangle(*((*i)[0]), *((*i)[1]), *((*i)[2]), *((*i)[3]),
                         Xscr()[i->index(0)], Xscr()[i->index(1)], Xscr()[i->index(2)], Xscr()[i->index(3)]);
  }
  view->commitDraw();
}
#endif

/// Actually creates the Hypercube
/** sets up the vertices of the Hypercube in \p X[], then sets up the surfaces
 *  of the Hypercube by declaring the appropriate squares as a list in
 *  \p Surface[][].                                                           */
void Hypercube::Initialize(void) {

    if (X().size() < num_vertices) resizeX(num_vertices);

    for (int x = 0; x <= 1; x++)
        for (int y = 0; y <= 1; y++)
            for (int z = 0; z <= 1; z++)
                for (int w = 0; w <= 1; w++) {
                    setX(
                        x+2*(y+2*(z+2*w)),
                        Vector<4> (2.*x-1., 2.*y-1., 2.*z-1., 2.*w-1.)*_a+_center
                    );
                }

    if (Surface.size() < num_faces) Surface.resize(num_faces);

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
  if (Surface.size() < i+offset*num_faces) Surface.resize(i+offset*num_faces);
# if USE_INT_INDICES
    if (Surface[i+offset*num_faces].size() < 4) Surface[i+offset*num_faces].resize(4);
    Surface[i+offset*num_faces][0] = a+offset*num_vertices;
    Surface[i+offset*num_faces][1] = b+offset*num_vertices;
    Surface[i+offset*num_faces][2] = c+offset*num_vertices;
    Surface[i+offset*num_faces][3] = d+offset*num_vertices;
# else
#     if 0
        qDebug() << "Surface.size() = " << Surface.size() << ", X.size() = " << X().size()
                 << " i: " << i+offset*num_faces 
                 << " a: " << a+offset*num_vertices << " b: " << b+offset*num_vertices 
                 << " c: " << c+offset*num_vertices << " d: " << d+offset*num_vertices;
        for (auto it = X().begin(); it != X().end(); ++it) qDebug() << it->toString().c_str();

#     endif
    Surface[i+offset*num_faces] = FacePolygon<4, 4>(
            X(),
            X()[a+offset*num_vertices], X()[b+offset*num_vertices], 
            X()[c+offset*num_vertices], X()[d+offset*num_vertices]
    );
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
    setX(0, Vector<4> (0.0, 0.0, 0.0, 0.0));
    setX(1, Vector<4> (1.0, 0.0, 0.0, 0.0));
    setX(2, Vector<4> (0.5, sqrt (3.)/2., 0.0, 0.0));
    setX(3, Vector<4> (0.5, sqrt (3.)/6., sqrt (2./3.), 0.0));
    setX(4, Vector<4> (0.5, sqrt (3.)/6., 1./sqrt (6.), 1./sqrt (2.)));

    Vector<4> center_of_mass (0.5, sqrt (3.)/4., sqrt (1./6.), 1./sqrt (8.));
    for (unsigned i = 0; i < X().size(); i++)
        setX(i, X()[i]*a+center-center_of_mass*a);

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
                        const VecMath::Vector<4> &T,
                        const VecMath::Vector<4> &scale) {
    for (unsigned i = 0; i < List.size (); i++)
        List[i]->Transform (R, T, scale);
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
void Gasket::Draw (UI::View *view) {
    for (unsigned i = 0; i < List.size (); i++) List[i]->Draw(view);
    view->commitDraw();
}

