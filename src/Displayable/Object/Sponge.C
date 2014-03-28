/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "Sponge.h"

#include <algorithm>
#include <tuple>

#include "Log.h"
#include "ScopedTimer.h"

#include "FunctionHolder.impl.h"
#include "Vector.impl.h"
#include "MultiDimensionalVector.impl.h"
#include "FacePolygon.impl.h"


#define CONCURRENT
#undef CONCURRENT

#include "View.h"

using std::tuple;
using std::tuple_size;
using std::tuple_element;

namespace SpongeUtility {

  float time_to_float(clock_t time) {
    return float(time)/float(CLOCKS_PER_SEC);
  }


# ifdef CONCURRENT
  void renumber_Surfaces(VecMath::MultiDimensionalVector<unsigned, 2> &Surface,
                         unsigned original_vertex, unsigned duplicate_vertex) {
  //  SingletonLog::Instance() << "renumberSurfaces(" << original_vertex << " " << duplicate_vertex << "\n";
    for (VecMath::MultiDimensionalVector<unsigned, 2>::iterator it = Surface.begin();
         it != Surface.end(); ++it) {
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
//    setfunctionName("4-dimensional Menger Sponge");
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

#undef DEBUG_SPONGE

void AltSponge::X_push_back(const VecMath::Vector<4>& x) {
    auto Xold = X();
    Xold.push_back(x);
    setX(VertexGrid<4, 1, double>(Xold));
    SingletonLog::Instance() << "mighty inefficient implementation of X_push_back()\n";
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



void AltSponge::Initialize(void) {

# ifdef DEBUG_SPONGE
  ScopedTimer timer("AltSponge::Initialize()");
# endif

  distance = abs(distance);
  if (distance > 3) distance = 3;     //  dunno if this is wise


  for (unsigned current_level = 0; current_level <= Level; current_level++) {
#   ifdef DEBUG_SPONGE
    unsigned long SpongePerLevel = ((distance == 0)? 81:
                                    (distance == 1)? 72:
                                    (distance == 2)? 48:
                                    16);
    unsigned TotalCubes = pow(SpongePerLevel, Level);
    SingletonLog::Instance() << "Level: " << current_level << "/" << Level << " -- total cubes: " << TotalCubes << "\n";
#   endif
    if (current_level < 1) {

      clearAndResizeX(16);
      Surface.resize(24);

      Hypercube::Initialize();

    } else {
#     ifdef DEBUG_SPONGE
      for (unsigned i = 0; i < X_.size(); ++i) cerr << "X[" << i << "]" << X_[i]<< endl;
#     endif

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
                    auto vec = std::find(X().begin(), X().end(), xnew);
                    if (vec == X().end()) {
                      X_push_back(xnew);
                      new_vertices[k] = X().back();
                    } else {
                      new_vertices[k] = *vec;
                    }

                  }
                  //  now store pointer to new vertex in surface array
                  FacePolygon<4,4> new_surface(X(), new_vertices[0], new_vertices[1], new_vertices[2], new_vertices[3]);
                  Surface.push_back(new_surface);

                  //  and remove the old surface
                  // ...
                  surface_vec_type::iterator found = std::find(Surface.begin(), Surface.end(), Sold[i]);
                  if (found != Surface.end()) {
#                   ifdef DEBUG_SPONGE
                      found->print(); cerr << " == " << endl; Sold[i].print();
#                   endif
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

//  std::for_each(Surface.begin(), Surface.end(), std::mem_fun_ref(&FacePolygon<4, 4>::print));
#ifdef DEBUG_SPONGE
  SingletonLog::Instance() << "time for initializing: " << SpongeUtility::time_to_float(clock()-start_time) << "\n";
#endif
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
//    setfunctionName("4-dimensional Menger Sponge");
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

# ifdef DEBUG_SPONGE
  ScopedTimer timer("Sponge::Initialize()");
# endif

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
#   ifdef DEBUG_SPONGE
    SingletonLog::Instance() << "time for initializing: " << SpongeUtility::time_to_float(clock()-start_time) << "\n";
#   endif
}

/// Transforms a Sponge
/** The transformation is achieved by transforming all constituting sub-sponges.
 *  @param R rotation
 *  @param T translation                                                      */
void Sponge::Transform (const VecMath::Rotation<4> &R,
                        const VecMath::Vector<4> &T,
                        const VecMath::Vector<4> &scale) {
    for (unsigned i = 0; i < List.size (); i++)
        List[i]->Transform (R, T, scale);
}


void Sponge::Project (double scr_w, double cam_w, bool depthcue4d) {
//    SingletonLog::Instance().log("Sponge::Project()");
    for (unsigned i = 0; i < List.size (); i++)
        List[i]->Project (scr_w, cam_w, depthcue4d);
}

void Sponge::Draw (UI::View *view) {
    if (Level < 1) List[0]->Draw(view);
    else for (unsigned i = 0; i < List.size(); i++) List[i]->Draw(view);
    view->commitDraw();
}

void Sponge::SetParameters(const ParameterMap &parms) {
    std::cerr << "Sponge::SetParameters(" << parms.toString() << ")\n";
#   if 1
        for (ParameterMap::const_iterator i = parms.begin(); i != parms.end(); ++i) {
            if (i->second->getName() == "Level") Level = i->second->toUnsigned();
            if (i->second->getName() == "Distance") distance = i->second->toUnsigned();
            if (i->second->getName() == "Size") rad = i->second->toDouble();
        }
#   else
        setParameter(parms, this->Phase, "Phase");
#   endif
}

void Sponge::ReInit (double, double, double,
                     double, double, double,
                     double, double, double) {
    List.clear();
    Object::ReInit(0,0,0,0,0,0,0,0,0);
}

std::string Sponge::description () {
    std::ostringstream out;
    out << "Sponge (level = " << Level << ")" << std::ends;
    return out.str ();
}
