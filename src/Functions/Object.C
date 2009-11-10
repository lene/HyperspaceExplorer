
//      project:      hyperspace explorer
//      module:       Object.C
//      contains:     four-dimensional objects which cannot be defined as a
//                    function
//      compile with: make all
//      author:       helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)



#include "Globals.h"
#include "ColorManager.h"
#include "Log.h"

#include "Matrix.h"
#include "Transform.h"

#include "Object.h"

#include <limits>

using std::cerr;
using std::endl;

using VecMath::Vector;
using VecMath::Matrix;


///////////////////////////////////////////////////////////////////////////////


/** generic Object constructor; only allocates necessary arrays, children must
 *  fill them in their c'tor
 *  @param name name of the object
 *  @param vertices number of vertices
 *  @param surfaces number of surfaces                                        */
Object::Object (const QString &name, unsigned vertices, unsigned surfaces):
        Function (),
        X(vec4vec1D(vertices)), Xtrans(vec4vec1D(vertices)), Xscr(vec3vec1D()),
        Surface(4) {
    setfunctionName(name);

    for (unsigned i = 0; i < 4; i++) Surface[i].resize(surfaces);
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
    transform<vec4vec1D, 4>::xform(Rot, T, X, Xtrans);
    /*    for (unsigned i = 0; i < X.size(); i++)
            Xtrans[i] = (Rot*X[i])+T;
    */
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

        for (unsigned j = 0; j <= 2; j++)
            Xscr.at(i)[j] = ProjectionFactor*Xtrans[i][j];
    }

    if (!depthcue4d) return;

    //  apply hyperfog
    for (unsigned i = 0; i < X.size(); i++) {
        ColMgrMgr::Instance().depthCueColor(Wmax, Wmin, Xtrans[i][3], X[i]);
    }
}


/// Draw the projected Object (onto screen or into GL list, as it is)
void Object::Draw() {
//    std::cerr << "Object::Draw ()" << std::endl;
    glBegin (GL_QUADS);
    for (unsigned i = 0; i < Surface[0].size(); i++) {
//        std::cerr << "Drawing surface " << i << ": ";
        for (unsigned j = 0; j < 4; j++) {
            if (Surface[j][i] < X.size() && Surface[j][i] < Xscr.size()) {
//                std::cerr << X[Surface[j][i]] << ", ";
                setVertex(X[Surface[j][i]], Xscr[Surface[j][i]]);
            }
        }
//        std::cerr << std::endl;
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

////////////////////////////////////////////////////////////////////////////////


/// Hypercube constructor
/** \param center center
 *  \param a side_length/2
 */
Hypercube::Hypercube (double a, const VecMath::Vector<4> &center):
        Object ("Hypercube", 16, 24),
        _a (a), _center(center) {
    declareParameter("Size", 1.0);
    Initialize();
}

/// Actually creates the Hypercube
/** sets up the vertices of the Hypercube in \p X[], then sets up the surfaces
 *  of the Hypercube by declaring the appropriate squares as a list in
 *  \p Surface[][].                                                           */
void Hypercube::Initialize(void) {
    for (int x = 0; x <= 1; x++)
        for (int y = 0; y <= 1; y++)
            for (int z = 0; z <= 1; z++)
                for (int w = 0; w <= 1; w++) {
                    X[x+2*(y+2*(z+2*w))] =
                        Vector<4> (2.*x-1., 2.*y-1., 2.*z-1., 2.*w-1.)*_a+_center;
                }

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
    Surface[0][i+offset*24] = a+offset*16;
    Surface[1][i+offset*24] = b+offset*16;
    Surface[2][i+offset*24] = c+offset*16;
    Surface[3][i+offset*24] = d+offset*16;
}


////////////////////////////////////////////////////////////////////////////////


/// Construct a Hypersponge of level \p level
/** \param _level Level of recursion used in creating the Sponge
 *  \param _distance see Initialize()
 *  \param _rad Size of the Sponge - \p _rad is half the side length
 *  \param _center Center point of the Sponge                                 */
AltSponge::AltSponge (unsigned _level, unsigned _distance, double _rad,
                      VecMath::Vector<4> _center):
        Level (_level), distance(_distance), rad(_rad), center(_center) {
    setfunctionName("4-dimensional Menger Sponge");
//    clearParameterNames();
    declareParameter("Level", (unsigned)1, _level);
    declareParameter("Distance", (unsigned)2, _distance);
    declareParameter("Size", 0.8, _rad);

    Initialize();
}


/// return the approximate amount of memory needed to display a sponge of
/// current \p level and given \p distance
/** @todo uses hardcoded and experimentally found value for memory per hypercube
 *  @param distance see Initialize()
 *  @return approx. mem required                                              */
unsigned long AltSponge::MemRequired (unsigned distance) {
    double SpongePerLevel = ((distance == 0)? 81:
                             (distance == 1)? 72:
                             (distance == 2)? 48:
                             16);
    return (unsigned long) ((pow (SpongePerLevel, int (Level))*32)/1024+8)*1024*1024;
}

/// This function actually creates the hypersponge.
/** It views it as an assembly
 *  of \f$ 3^4 \f$ smaller sponges, slicing the sponge in three sub-sponges in
 *  every one of the four dimensions, and then taking away some of the resulting
 *  81 smaller sub-sponges.
 *  \li if the parameter \em distance is zero, it only removes the sub-sponge
 *      with distance 0 from the center, i.e. the one at the center.
 *  \li if the parameter \em distance is one, it only removes the sub-sponges
 *      with distance <= 1, amounting to nine removed sub-sponges. The three-
 *      dimensional surface of the hypercube enveloping the sponge is not
 *      breached, because the surface of a hypercube is two units away from the
 *      center, instead of one unit, as in 3D.
 *  \li if \em distance = 2, the holes reach the hypercubes surface, giving an
 *      object analogous to the three-dimensional Menger Sponge.
 *  \li if \em distance = 3, only the 16 corners of the hypercube remain, giving
 *      four-dimensional fractal dust.
 *
 *  If the \em level of the sponge is 1, the sub-sponges are hypercubes. Otherwise,
 *  they are Hypersponges with a \em level reduced by 1.
 *
 *  \todo Make this a recursive function, resizing the vector of surfaces and
 *    vertices with every call.
 *  \todo remove unused places in the vertices and surfaces arrays.
 *  \todo remove surfaces which are doubly-used, because they cancel each other.
 *  \todo make vertices unique in the vertex array, saving a (potentially huge)
 *    lot of memory.
 */
void AltSponge::Initialize(void) {
//    SingletonLog::Instance().log("Sponge::Initialize()");

    if (Level < 1)
        Hypercube::Initialize();
    else if (Level == 1) {
        distance = abs(distance);
        if (distance > 3) distance = 3;     //  dunno if this is wise
        distance=2; //  temp testing value
        unsigned long SpongePerLevel = ((distance == 0)? 81:
                                        (distance == 1)? 72:
                                        (distance == 2)? 48:
                                        16);
        unsigned TotalCubes = pow(SpongePerLevel, Level);
        TotalCubes = pow(81, Level);
        std::cerr << "total cubes: " << TotalCubes << std::endl;
        X.resize(TotalCubes*16);
        Xtrans.resize(TotalCubes*16);
        Xscr.resize(TotalCubes*16);
        for (unsigned i = 0; i < 4; i++) {
            Surface[i].resize(TotalCubes*24, std::numeric_limits<unsigned>::max());
        }

        rad = 1.;
        for (unsigned current_level = 0; current_level < Level; current_level++) {

            rad /= 3.;

            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    for (int z = -1; z <= 1; z++) {
                        for (int w = -1; w <= 1; w++) {
                            if (abs (x)+abs (y)+abs (z)+abs (w) > distance) {
                                Vector<4> NewCen =
                                    Vector<4> (double (x), double (y),
                                               double (z), double (w))*2*rad;
                                NewCen += center;

                                unsigned offset = (x+1)+3*((y+1)+3*((z+1)+3*(w+1)));
                                std::cerr << "offset: " << offset << ", NewCen: " << NewCen << std::endl;

                                for (int xx = 0; xx <= 1; xx++)
                                    for (int yy = 0; yy <= 1; yy++)
                                        for (int zz = 0; zz <= 1; zz++)
                                            for (int ww = 0; ww <= 1; ww++) {
                                                X[offset*16+xx+2*(yy+2*(zz+2*ww))] =
                                                    Vector<4> (2.*xx-1., 2.*yy-1., 2.*zz-1., 2.*ww-1.)*rad+NewCen;
                                            }

                                DeclareSquare (0,   0, 1, 3, 2, offset);
                                DeclareSquare (1,   0, 1, 5, 4, offset);
                                DeclareSquare (2,   0, 1, 9, 8, offset);
                                DeclareSquare (3,   0, 2, 6, 4, offset);
                                DeclareSquare (4,   0, 2,10, 8, offset);
                                DeclareSquare (5,   0, 4,12, 8, offset);
                                DeclareSquare (6,   1, 3, 7, 5, offset);
                                DeclareSquare (7,   1, 3,11, 9, offset);
                                DeclareSquare (8,   1, 5,13, 9, offset);
                                DeclareSquare (9,   2, 3, 7, 6, offset);
                                DeclareSquare (10,  2, 3,11,10, offset);
                                DeclareSquare (11,  2, 6,14,10, offset);
                                DeclareSquare (12,  3, 7,15,11, offset);
                                DeclareSquare (13,  4, 5, 7, 6, offset);
                                DeclareSquare (14,  4, 5,13,12, offset);
                                DeclareSquare (15,  4, 6,14,12, offset);
                                DeclareSquare (16,  5, 7,15,13, offset);
                                DeclareSquare (17,  6, 7,15,14, offset);
                                DeclareSquare (18,  8, 9,11,10, offset);
                                DeclareSquare (19,  8, 9,13,12, offset);
                                DeclareSquare (20,  8,10,14,12, offset);
                                DeclareSquare (21,  9,11,15,13, offset);
                                DeclareSquare (22, 10,11,15,14, offset);
                                DeclareSquare (23, 12,13,15,14, offset);
                            }
                        }
                    }
                }
            }
            reduceSurfaces();
            reduceVertices();
            removeDuplicateSurfaces();
        }

    }

    Object::Initialize();

}

void AltSponge::reduceSurfaces() {
  
    for (unsigned k = 0; k < 4; ++k) {
        std::cerr << "Pre-Removing: surface [" << k << "].size() = " << Surface[k].size() << std::endl;
        for (VecMath::uintvec<1>::iterator i = Surface[k].begin(); i != Surface[k].end(); ++i) {
            if (*i < X.size() || *i < Xscr.size()) continue;

            VecMath::uintvec<1>::iterator j = i;
            for (j = i+1; j != Surface[k].end(); ++j) {
                if (*j < X.size() || *j < Xscr.size()) break;
            }

            Surface[k].erase(i, j);
        }
        std::cerr << "Post-Removing: surface [" << k << "].size() = " << Surface[k].size() << std::endl;
    }

}

void AltSponge::reduceVertices() {

    unsigned i_num = 0;
    vec4vec1D::iterator itrans = Xtrans.begin();
    vec3vec1D::iterator iscr = Xscr.begin();
    
    std::cerr << "vertices before reduction: " << X.size() << std::endl;
    for (vec4vec1D::iterator i = X.begin(); i != X.end(); ++i, ++i_num, ++itrans, ++iscr) {
        

        bool found = true;
        while(found) {
            unsigned j_num = i_num+1;
            vec4vec1D::iterator jtrans = itrans+1;
            vec3vec1D::iterator jscr = iscr+1;
            
            found = false;
            
            for (vec4vec1D::iterator j = i+1; j != X.end(); ++j, ++j_num, ++jtrans, ++jscr) {

                if (*i == *j) {

                    // erase equal vertices
                    X.erase(j);
                    Xtrans.erase(jtrans);
                    Xscr.erase(jscr);
                    
                    // replace all surface indices pointing to equal vertex
                    for (unsigned k = 0; k < 4; ++k) {
                        for (VecMath::uintvec<1>::iterator it = Surface[k].begin(); it != Surface[k].end(); ++it) {
                            if (*it == j_num) *it = i_num;
                            else if (*it > j_num) (*it)--;
                        }
                    }

                    found = true;
                    break;
                }
            }
        }
    }

    std::cerr << "vertices after reduction: " << X.size() << std::endl;
}

bool isPermutation(unsigned m0, unsigned m1,
                   unsigned n0, unsigned n1) {
    if (m0 == n0 && m1 == n1) return true;
    if (m0 == n1 && m1 == n0) return true;
    return false;
}

bool isPermutation(unsigned m0, unsigned m1, unsigned m2,
                   unsigned n0, unsigned n1, unsigned n2) {
    if (m0 == n0 && isPermutation(m1, m2, n1, n2)) return true;
    if (m0 == n1 && isPermutation(m1, m2, n0, n2)) return true;
    if (m0 == n2 && isPermutation(m1, m2, n0, n1)) return true;
    return false;
}
bool isPermutation(unsigned m0, unsigned m1, unsigned m2, unsigned m3,
                   unsigned n0, unsigned n1, unsigned n2, unsigned n3) {
    if (m0 == n0 && isPermutation(m1, m2, m3, n1, n2, n3)) return true;
    if (m0 == n1 && isPermutation(m1, m2, m3, n0, n2, n3)) return true;
    if (m0 == n2 && isPermutation(m1, m2, m3, n0, n1, n3)) return true;
    if (m0 == n3 && isPermutation(m1, m2, m3, n0, n1, n2)) return true;
    return false;
}

void AltSponge::removeDuplicateSurfaces() {
    VecMath::uintvec<1>::iterator i0 = Surface[0].begin(), i1 = Surface[1].begin(), i2 = Surface[2].begin(), i3 = Surface[3].begin();
    std::cerr << "Pre-Removing: surface [0].size() = " << Surface[0].size() << std::endl;
    
    while (i0 != Surface[0].end()) {
        VecMath::uintvec<1>::iterator j0 = i0+1, j1 = i1+1, j2 = i2+1, j3 = i3+1;
        bool erased = false;
        while (j0 != Surface[0].end()) {
            if (isPermutation(*i0, *i1, *i2, *i3, *j0, *j1, *j2, *j3)) {
//                Surface[0].erase(i0);
//                Surface[1].erase(i1);
//                Surface[2].erase(i2);
//                Surface[3].erase(i3);
                Surface[0].erase(j0);
                Surface[1].erase(j1);
                Surface[2].erase(j2);
                Surface[3].erase(j3);
//                erased = true;
            } else {
                j0++;
                j1++;
                j2++;
                j3++;
            }
        }
        if (!erased) {
            i0++;
            i1++;
            i2++;
            i3++;
        }
    }
    std::cerr << "Post-Removing: surface [0].size() = " << Surface[0].size() << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

/// Construct a Hypersponge of level \p level
/** \param _level Level of recursion used in creating the Sponge
 *  \param _distance see Initialize()
 *  \param _rad Size of the Sponge - \p _rad is half the side length
 *  \param _center Center point of the Sponge                                 */
Sponge::Sponge (unsigned _level, unsigned _distance, double _rad,
                VecMath::Vector<4> _center):
        Level (_level), distance(_distance), rad(_rad), center(_center) {
    setfunctionName("4-dimensional Menger Sponge");
//    clearParameterNames();
    declareParameter("Level", (unsigned)1, _level);
    declareParameter("Distance", (unsigned)2, _distance);
    declareParameter("Size", 0.8, _rad);

    Initialize();
}


/// return the approximate amount of memory needed to display a sponge of
/// current \p level and given \p distance
/** @todo uses hardcoded and experimentally found value for memory per hypercube
 *  @param distance see Initialize()
 *  @return approx. mem required                                              */
unsigned long Sponge::MemRequired (unsigned distance) {
    double SpongePerLevel = ((distance == 0)? 81:
                             (distance == 1)? 72:
                             (distance == 2)? 48:
                             16);
    return (unsigned long) ((pow (SpongePerLevel, int (Level))*32)/1024+8)*1024*1024;
}


/// Sponge destructor
Sponge::~Sponge () {
    List.clear();
}

/// This function actually creates the hypersponge.
/** It views it as an assembly
 *  of \f$ 3^4 \f$ smaller sponges, slicing the sponge in three sub-sponges in
 *  every one of the four dimensions, and then taking away some of the resulting
 *  81 smaller sub-sponges.
 *  \li if the parameter \em distance is zero, it only removes the sub-sponge
 *      with distance 0 from the center, i.e. the one at the center.
 *  \li if the parameter \em distance is one, it only removes the sub-sponges
 *      with distance <= 1, amounting to nine removed sub-sponges. The three-
 *      dimensional surface of the hypercube enveloping the sponge is not
 *      breached, because the surface of a hypercube is two units away from the
 *      center, instead of one unit, as in 3D.
 *  \li if \em distance = 2, the holes reach the hypercubes surface, giving an
 *      object analogous to the three-dimensional Menger Sponge.
 *  \li if \em distance = 3, only the 16 corners of the hypercube remain, giving
 *      four-dimensional fractal dust.
 *
 *  If the \em level of the sponge is 1, the sub-sponges are hypercubes. Otherwise,
 *  they are Hypersponges with a \em level reduced by 1.
 */
void Sponge::Initialize(void) {
//    SingletonLog::Instance().log("Sponge::Initialize()");

    if (Level < 1)
        List.push_back (new Hypercube (rad*3./2., center));
    else {
        if (distance > 3) distance = 3;   //  dunno if this is wise

        if (0 && (MemRequired (distance) > Globals::Instance().getMaxMemory())) {
            cerr << "Menger sponge of level " << Level
                 << " would require approx. " << MemRequired (distance)/1024/1024
                 << " MB of memory." << endl;
            if (Globals::Instance().checkMemory()) {
                cerr << "This is more than your available Memory, "
                     << Globals::Instance().getMaxMemory()/1024/1024 << "MB" << endl;
                while (MemRequired (distance) > Globals::Instance().getMaxMemory())
                    Level--;
                cerr << "Using level " << Level << " instead." << endl;
            }
        }
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                for (int z = -1; z <= 1; z++) {
                    for (int w = -1; w <= 1; w++) {
                        if (distance >= 0) {
                            if (abs (x)+abs (y)+abs (z)+abs (w) > distance) {
                                Vector<4> NewCen =
                                    Vector<4> (double (x), double (y),
                                               double (z), double (w))*rad;
                                NewCen += center;
                                List.push_back (
                                    new Sponge (
                                        Level-1, distance, rad/3., NewCen));
                            }
                        } else {
                            if (abs (x)+abs (y)+abs (z)+abs (w) < distance) {
                                Vector<4> NewCen =
                                    Vector<4> (double (x), double (y),
                                               double (z), double (w))*rad;
                                NewCen += center;
                                List.push_back (
                                    new Sponge (
                                        Level-1, distance, rad/3., NewCen));
                            }
                        }
                    }
                }
            }
        }
    }

    Object::Initialize();
}

/// Transforms a Sponge
/** The transformation is achieved by transforming all constituting sub-sponges.
 *  @param R rotation
 *  @param T translation                                                      */
void Sponge::Transform (const VecMath::Rotation<4> &R,
                        const VecMath::Vector<4> &T) {
    for (unsigned i = 0; i < List.size (); i++)
        List[i]->Transform (R, T);
}


/// Projects a Sponge into three-space
/** The projection is achieved by projecting all constituting sub-sponges.
 *  @param scr_w w coordinate of screen
 *  @param cam_w w coordinate of camera
 *  @param depthcue4d wheter to use hyperfog/dc                               */
void Sponge::Project (double scr_w, double cam_w, bool depthcue4d) {
//    SingletonLog::Instance().log("Sponge::Project()");
    for (unsigned i = 0; i < List.size (); i++)
        List[i]->Project (scr_w, cam_w, depthcue4d);
}

/// Draw the projected Sponge (onto screen or into GL list, as it is)
/** Draws all sub-sponges, recursively.                                       */
void Sponge::Draw (void) {
    if (Level < 1) List[0]->Draw();
    else for (unsigned i = 0; i < List.size(); i++) List[i]->Draw();
}


////////////////////////////////////////////////////////////////////////////////

/// Pyramid (hypersimplex) constructor
/** @param _center center
 *  @param _a side_length/2                                                   */
Pyramid::Pyramid (double _a, const VecMath::Vector<4> &_center):
        Object ("Hyperpyramid", 5, 10),
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
    Surface[0][i] = a;
    Surface[1][i] = b;
    Surface[2][i] = c;
    Surface[3][i] = c;
}


////////////////////////////////////////////////////////////////////////////


/// Gasket constructor
/** \param level hyper-sierpinski gasket level
 *  \param _rad side_length/2
 *  \param _center center                                                      */
Gasket::Gasket (unsigned level, double _rad, VecMath::Vector<4> _center):
        Level (level), rad(_rad), center(_center) {
    setfunctionName("4-dimensional Sierpinski Gasket");
//    clearParameterNames();
    declareParameter("Level", 3);
    declareParameter("Size", 1.0);
    Initialize();
}

/// return the approximate amount of memory needed to display a gasket of
/// current level
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
void Gasket::Draw (void) {
    for (unsigned i = 0; i < List.size (); i++) List[i]->Draw ();
}
