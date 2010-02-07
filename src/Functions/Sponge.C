
#include "Sponge.h"

#include "Log.h"

#include <QtConcurrentRun>

#include <time.h>
#include <algorithm>

#define CONCURRENT
#undef CONCURRENT

#include <tr1/tuple>
using std::tr1::tuple;
using std::tr1::tuple_size;
using std::tr1::tuple_element;

namespace SpongeUtility {

  float time_to_float(clock_t time) {
    return float(time)/float(CLOCKS_PER_SEC);
  }

  template<typename T>
  bool isPermutation(T m0, T m1,
                     T n0, T n1) {
    if (m0 == n0 && m1 == n1) return true;
    if (m0 == n1 && m1 == n0) return true;
    return false;
  }

  template<typename T>
  bool isPermutation(T m0, T m1, T m2,
                     T n0, T n1, T n2) {
    if (m0 == n0 && isPermutation(m1, m2, n1, n2)) return true;
    if (m0 == n1 && isPermutation(m1, m2, n0, n2)) return true;
    if (m0 == n2 && isPermutation(m1, m2, n0, n1)) return true;
    return false;
  }

  template<typename T>
  bool isPermutation(T m0, T m1, T m2, T m3,
                     T n0, T n1, T n2, T n3) {
    if (m0 == n0 && isPermutation(m1, m2, m3, n1, n2, n3)) return true;
    if (m0 == n1 && isPermutation(m1, m2, m3, n0, n2, n3)) return true;
    if (m0 == n2 && isPermutation(m1, m2, m3, n0, n1, n3)) return true;
    if (m0 == n3 && isPermutation(m1, m2, m3, n0, n1, n2)) return true;
    return false;
  }

  template<typename T>
  bool isPermutation(T m0, T m1, T m2, T m3, T m4,
                     T n0, T n1, T n2, T n3, T n4) {
    if (m0 == n0 && isPermutation(m1, m2, m3, m4, n1, n2, n3, n4)) return true;
    if (m0 == n1 && isPermutation(m1, m2, m3, m4, n0, n2, n3, n4)) return true;
    if (m0 == n2 && isPermutation(m1, m2, m3, m4, n0, n1, n3, n4)) return true;
    if (m0 == n3 && isPermutation(m1, m2, m3, m4, n0, n1, n2, n4)) return true;
    if (m0 == n4 && isPermutation(m1, m2, m3, m4, n0, n1, n2, n3)) return true;
    return false;
  }

  /*
   * unfinished attempts at rewriting isPermutation() as a variadic template
   * using std::tr1::tuple follow.
   * needs the g++ option
   * QMAKE_CXXFLAGS += -std=c++0x
   * to compile.

    // attempt 1. function template.
    // failed because i could not find the right syntax to even learn the number
    // of elements in the tuple.
    bool isPermutation(tuple<members...> list1,
                       tuple<members...> list2) {
      if (list1 == list2) return true;
      if (tuple_size< list1 >::value != tuple_size< list2 >::value) {
        return false;
      }
      ...

      return false;
    }

    // attempt 2. use a class with variadic templates and a static member.
    // failed at the point of g++ error message:
    // sorry, unimplemented: cannot expand 'Args ...' into a fixed-length argument list
    template<typename T> struct IsPermutation<> { };
    template<typename T, T... Args>
      struct IsPermutation<T, Args...> {
        static const bool value = 1+IsPermutation<Args...>::value;
    };
*/
# ifdef CONCURRENT
  void renumber_Surfaces(VecMath::uintvec<2> &Surface, unsigned original_vertex, unsigned duplicate_vertex) {
  //  SingletonLog::Instance() << "renumberSurfaces(" << original_vertex << " " << duplicate_vertex << "\n";
    for (VecMath::uintvec<2>::iterator it = Surface.begin(); it != Surface.end(); ++it) {
      for (unsigned k = 0; k < 4; ++k) {
        if ((*it)[k] == duplicate_vertex) (*it)[k] = original_vertex;
        else if ((*it)[k] > duplicate_vertex) (*it)[k]--;
      }
    }
  }
# endif

}

using VecMath::Vector;
using std::cerr;
using std::endl;

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
 *  \li if the parameter \p distance is zero, it only removes the sub-sponge
 *      with distance 0 from the center, i.e. the one at the center.
 *  \li if the parameter \p distance is one, it only removes the sub-sponges
 *      with distance <= 1, amounting to nine removed sub-sponges. The three-
 *      dimensional surface of the hypercube enveloping the sponge is not
 *      breached, because the surface of a hypercube is two units away from the
 *      center, instead of one unit, as in 3D.
 *  \li if \p distance = 2, the holes reach the hypercubes surface, giving an
 *      object analogous to the three-dimensional Menger Sponge.
 *  \li if \p distance = 3, only the 16 corners of the hypercube remain, giving
 *      four-dimensional fractal dust.
 *
 *  If the \p level of the sponge is 1, the sub-sponges are hypercubes. Otherwise,
 *  they are Hypersponges with a \p level reduced by 1.
 * 
 * \todo merge joined surfaces into one. not trivial, because the surfaces have
 *       holes.
 */
#if USE_INT_INDICES
void AltSponge::Initialize(void) {

  clock_t start_time = clock ();                     //  record start time
  
  distance = abs(distance);
  if (distance > 3) distance = 3;     //  dunno if this is wise
    
    unsigned long SpongePerLevel = ((distance == 0)? 81:
    (distance == 1)? 72:
    (distance == 2)? 48:
    16);
  unsigned TotalCubes = pow(SpongePerLevel, Level);
  
  for (unsigned current_level = 0; current_level <= Level; current_level++) {
    
    SingletonLog::Instance() << "Level: " << current_level << "/" << Level << " -- total cubes: " << TotalCubes << "\n";
    
    if (current_level < 1) {
      
      X.resize(16);
      Surface.resize(24);
      
      Hypercube::Initialize();
      
    } else {

      vec4vec1D Xold(X);
      surface_vec_type Sold(Surface);
      
      for (unsigned i = 0; i < Xold.size(); ++i) Xold[i] *= 1./3.;

      try {
        X.resize(SpongePerLevel*X.size());
        Surface.resize(SpongePerLevel*Surface.size());
      } catch (std::bad_alloc) {
        X.resize(Xold.size());
        Surface.resize(Sold.size());
        return;
      }
      
      unsigned indexX = 0, indexS = 0;
      for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
          for (int z = -1; z <= 1; z++) {
            for (int w = -1; w <= 1; w++) {
              if (abs (x)+abs (y)+abs (z)+abs (w) > distance) {
                Vector<4> NewCen = Vector<4>((double)x, (double)y, (double)z, (double)w)*2./3.+center;
                           
                for (unsigned i = 0; i < Xold.size(); ++i) {
                  X[indexX+i] = Xold[i]+NewCen;
                }
                for (unsigned i = 0; i < Sold.size(); ++i) {
                  if (Surface[indexS+i].size() < 4) Surface[indexS+i].resize(4);
                  for (unsigned k = 0; k < 4; ++k) {
                    Surface[indexS+i][k] = Sold[i][k]+indexX;
                  }
                }
                indexX += Xold.size();
                indexS += Sold.size();
              }
            }
          }
        }
      }
      //  remove duplicate vertices and surfaces, except when we have dust
      if (distance < 3) {
        reduceVertices();
        removeDuplicateSurfaces();
      }
    }
    
  }
  
  Object::Initialize();
  SingletonLog::Instance() << "time for initializing: " << SpongeUtility::time_to_float(clock()-start_time) << "\n";
  
}

#else

void AltSponge::Initialize(void) {

  clock_t start_time = clock ();                     //  record start time
  
  distance = abs(distance);
  if (distance > 3) distance = 3;     //  dunno if this is wise
    
    unsigned long SpongePerLevel = ((distance == 0)? 81:
                                    (distance == 1)? 72:
                                    (distance == 2)? 48:
                                    16);
  unsigned TotalCubes = pow(SpongePerLevel, Level);
  
  for (unsigned current_level = 0; current_level <= Level; current_level++) {
    
    SingletonLog::Instance() << "Level: " << current_level << "/" << Level << " -- total cubes: " << TotalCubes << "\n";
    
    if (current_level < 1) {
      
      X.resize(16);
      Surface.resize(24);
      
      Hypercube::Initialize();
      
    } else {
      
      for (unsigned i = 0; i < X.size(); ++i) cerr << "X[" << i << "]" << X[i]<< endl;

      surface_vec_type Sold(Surface);
      
      for (double x = -1; x <= 1; x++) {
        for (double y = -1; y <= 1; y++) {
          for (double z = -1; z <= 1; z++) {
            for (double w = -1; w <= 1; w++) {
              
              if (fabs (x)+fabs (y)+fabs (z)+fabs (w) > distance) {

                Vector<4> NewCen = Vector<4> (x, y, z, w)*2./3. + center;

                for (unsigned i = 0; i < Sold.size(); ++i) {
                  
                  Vector<4> new_vertices[4];
                  
                  for (unsigned k = 0; k < 4; ++k) {
                    
                    //  create new vertex and store it if necessary
                    Vector<4> xold = *(Sold[i][k]), xnew = xold/3.+NewCen;
//                    cerr << "xold: " << xold << ", xnew: " << xnew << endl;
                    vec4vec1D::const_iterator vec = std::find(X.begin(), X.end(), xnew);
                    if (vec == X.end()) {
                      X.push_back(xnew);
                      new_vertices[k] = X.back();
                    } else {
                      new_vertices[k] = *vec;
                    }

                  }
                  //  now store pointer to new vertex in surface array
                  SurfaceType<4,4> new_surface(X, new_vertices[0], new_vertices[1], new_vertices[2], new_vertices[3]);
                  Surface.push_back(new_surface);
                  
                  //  and remove the old surface
                  // ...
                  surface_vec_type::iterator found = std::find(Surface.begin(), Surface.end(), Sold[i]);
                  if (found != Surface.end()) {
                    found->print(); cerr << " == " << endl; Sold[i].print();
                    Surface.erase(std::find(Surface.begin(), Surface.end(), Sold[i]));
                  }
                }
                
              }
              
            }
          }
        }
      }
//      for (unsigned i = 0; i < X.size(); ++i) cerr << "X[" << i << "]" << X[i]<< endl;
      
      //  remove duplicate surfaces, except when we have dust
      if (distance < 3) {
//        removeDuplicateSurfaces();
      }
    }
    
  }
  
  Object::Initialize();

//  std::for_each(Surface.begin(), Surface.end(), std::mem_fun_ref(&SurfaceType<4, 4>::print));
  
  SingletonLog::Instance() << "time for initializing: " << SpongeUtility::time_to_float(clock()-start_time) << "\n";
  
}
#endif

#if USE_INT_INDICES
void AltSponge::renumberSurfaces(unsigned original_vertex, unsigned duplicate_vertex) {
//	SingletonLog::Instance() << "renumberSurfaces(" << original_vertex << " " << duplicate_vertex << "\n";
    for (surface_vec_type::iterator it = Surface.begin(); it != Surface.end(); ++it) {
        for (unsigned k = 0; k < 4; ++k) {
            if ((*it)[k] == duplicate_vertex) (*it)[k] = original_vertex;
            else if ((*it)[k] > duplicate_vertex) (*it)[k]--;
        }
    }
}

void AltSponge::reduceVertices() {

    unsigned i_num = 0;

    //  copy vertex data from a std::vector into a std::list for more efficient erasing
    typedef std::list<VecMath::Vector<4> > container_type;
    container_type X_tmp(X.size());
    std::copy(X.begin(), X.end(), X_tmp.begin());

    SingletonLog::Instance() << "vertices before reduction: " << X.size() << "\n";
    clock_t start_time = clock ();
    
#	ifdef CONCURRENT
    QFuture<void> future;
#	endif

    for (container_type::iterator i = X_tmp.begin(); i != X_tmp.end(); ++i, ++i_num) {

        //  used to identify the index of the removed vertex in the Surface array
        unsigned j_num = i_num+1;

        container_type::iterator j = i;
        for (++j; j != X_tmp.end(); ++j, ++j_num) {

            if (*i == *j) {

                // erase equal vertices
                j = X_tmp.erase(j);

                // replace all surface indices pointing to equal vertex
#               ifdef CONCURRENT
                /* My tries to multithread the replacing of indices are preserved
                 * here. Apparently multithreading does not speed up the function,
                 * but instead slows it down, so I'm not finishing this now.
                 */
                future.waitForFinished();
                //	using class function
//                future = QtConcurrent::run(*this, &AltSponge::renumberSurfaces, i_num, j_num);
                future = QtConcurrent::run(SpongeUtility::renumber_Surfaces, Surface, i_num, j_num);
#               else
                renumberSurfaces(i_num, j_num);
#               endif
            }
        }
    }

    X.resize(X_tmp.size());
    std::copy(X_tmp.begin(), X_tmp.end(), X.begin());

    SingletonLog::Instance() << "vertices after reduction: " << X_tmp.size() << "\n"
                             << "time for reducing: " << SpongeUtility::time_to_float(clock()-start_time) << "\n";

}


void AltSponge::removeDuplicateSurfaces() {

    //  copy surface data from a std::vector into a std::list for more efficient erasing
    typedef std::list<VecMath::uintvec<1> > container_type;
    container_type S_tmp(Surface.size());
    std::copy(Surface.begin(), Surface.end(), S_tmp.begin());

    container_type::iterator i = S_tmp.begin();
    unsigned i_num = 0;

    SingletonLog::Instance() << "Pre-Removing dups: surface.size() = " << S_tmp.size() << "\n";
    clock_t start_time = clock ();                     //  record start time

    while (i != S_tmp.end()) {

        bool erased = false;

        container_type::iterator j = i;
        ++j;

        while (j != S_tmp.end()) {

            if (SpongeUtility::isPermutation((*i)[0], (*i)[1], (*i)[2], (*i)[3],
                                             (*j)[0], (*j)[1], (*j)[2], (*j)[3])) {

                S_tmp.erase(j);
                erased = true;
                break;

            } else {
                ++j;
            }
        }

        if (erased) {
            i = S_tmp.erase(i);
        } else {
            ++i;
            i_num++;
        }
    }

    Surface.resize(S_tmp.size());
    std::copy(S_tmp.begin(), S_tmp.end(), Surface.begin());

    SingletonLog::Instance() << "Post-Removing dups: surface.size() = " << S_tmp.size() << "\n"
                             << "time for reducing: " << SpongeUtility::time_to_float(clock()-start_time) << "\n";

}
#endif
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
    clock_t start_time = clock ();                     //  record start time

    if (Level < 1)
        List.push_back (new Hypercube (rad*3./2., center));
    else {
        if (distance > 3) distance = 3;   //  dunno if this is wise

        if (0 && (MemRequired (distance) > Globals::Instance().getMaxMemory())) {
            std::cerr << "Menger sponge of level " << Level
					  << " would require approx. " << MemRequired (distance)/1024/1024
					  << " MB of memory." << std::endl;
            if (Globals::Instance().checkMemory()) {
            	std::cerr << "This is more than your available Memory, "
						  << Globals::Instance().getMaxMemory()/1024/1024 << "MB" << std::endl;
                while (MemRequired (distance) > Globals::Instance().getMaxMemory())
                    Level--;
                std::cerr << "Using level " << Level << " instead." << std::endl;
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
    SingletonLog::Instance() << "time for initializing: " << SpongeUtility::time_to_float(clock()-start_time) << "\n";

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

