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

#if(!defined SPONGE_H)
#define SPONGE_H

#define USE_ALT_SPONGE 0

#include "ObjectImplementations.h"

////////////////////////////////////////////////////////////////////////////////

/// A four-dimensional Menger Sponge.
/** A Menger Sponge in three dimensions is a fractal produced by subdividing
 *  a cube and taking away parts of the cube which get subsequentally
 *  smaller. The \em level parameter controls how often this process is repeated,
 *  i.e. how many holes there are in the final object.
 *
 *  A four-dimensional Menger Sponge is created analogously from a hypercube.
 *
 *  The fractal can be further controlled by the \em distance parameter:
 *  \li \em distance = 0: Only the innermost cube is removed, resulting in a
 *      four-dimensional foam with connected body and disjoint holes.
 *  \li \em distance = 1: the innermost and the next to innermost cubes are
 *      removed, which results in a foam in three dimensions, but has holes in
 *      the four-dimensional structure.
 *  \li \em distance = 2: the holes reach the surface of the cube, resulting in
 *      a sponge structure - both the holes and the cubes ("curd") are
 *      connected.
 *  \li \em distance = 3: only the corners of the hypercube remain, resulting in
 *      dust - the "curd" is disjoint, the holes are connected.
 *  \ingroup ObjectGroup                                                    */
class Sponge: public Hypercube {
public:
    /// Sponge constructor
    /** @param _level hypersponge level
     *  @param _distance distance of subcubes to center to be counted as part of
     *                   the fractal
     *                   \li = 0: solid hypercube
     *                   \li = 1: foam
     *                   \li = 2: sponge
     *                   \li = 3: dust
     *                   \li >= 4: nothing
     *  @param _rad side_length/2
     *  @param _center center                                                 */
    Sponge (unsigned _level = 1, unsigned _distance = 2, double _rad = 0.8,
            VecMath::Vector<4> _center = VecMath::Vector<4>(0., 0.,0., 0.));
    virtual ~Sponge ();
    virtual std::string getFunctionName() const { return "4D Menger Sponge"; }

    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T,
                            const VecMath::Vector<4> &scale);
    /// Projects a Sponge into three-space
    /** The projection is achieved by projecting all constituting sub-sponges.
     *  @param ScrW w coordinate of screen
     *  @param CamW w coordinate of camera
     *  @param DepthCue4D wheter to use hyperfog/dc
     */
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    /// Draw the projected Sponge, drawing all sub-sponges, recursively.
    virtual void Draw (UI::View *view);

    virtual void SetParameters(const ParameterMap &parms);
    
    /// Rebuild the Sponge if the parameters have changed
    virtual void ReInit (double, double, double,
                         double, double, double,
                         double, double, double);
    
    /** @return A string with a description of the Hypersponge object         */
    virtual std::string description();
    
    unsigned getLevel() const { return level_; }
    int getDistance() const { return distance_; }
    
protected:
    virtual void Initialize();
    virtual unsigned long MemRequired (unsigned);
    unsigned level_;                 ///< Level of the hypersponge
    int distance_;                   ///< max. distance (see Initialize())
    double rad_;                     ///< radius, more correctly size, of the sponge
    VecMath::Vector<4> center_;      ///< center of the sponge

    /// List of sub-sponges (see Initialize())
    /** @todo Use smart pointers instead of a simple pointer-to-object        */
    std::vector<Hypercube *> List;

};

namespace {
    Displayable *createSponge() { return new Sponge(); }
    const bool registeredS = TheFunctionFactory::Instance().registerFunction(createSponge, "Object");
}

///////////////////////////////////////////////////////////////////////////////

/// An alternative hypersponge implementation with removal of duplicate faces
class AltSponge: public Hypercube {
public:
  /// AltSponge constructor
  /** @param _level hypersponge level
   *  @param _distance distance of subcubes to center to be counted as part of
   *    the fractal
   *      \li = 0: solid hypercube
   *      \li = 1: foam
   *      \li = 2: sponge
   *      \li = 3: dust
   *      \li >= 4: nothing
   *  @param _rad side_length/2
   *  @param _center center                                                 */
  AltSponge (unsigned _level = 1, unsigned _distance = 2, double _rad = 0.8,
             VecMath::Vector<4> _center = VecMath::Vector<4>(0., 0.,0., 0.));
  virtual ~AltSponge () { }
  virtual std::string getFunctionName() const { return "4D Menger Sponge (version)"; }

  virtual void SetParameters(const ParameterMap &parms) {
    std::cerr << "AltSponge::SetParameters(" << parms.toString() << ")\n";
#       if 1
    for (ParameterMap::const_iterator i = parms.begin();
         i != parms.end(); ++i) {
      if (i->second->getName() == "Level")
        level_ = i->second->toUnsigned();
      if (i->second->getName() == "Distance")
        distance_ = i->second->toInt();
      if (i->second->getName() == "Size")
        rad_ = i->second->toDouble();
     }
#       else
     setParameter(parms, this->Phase, "Phase");
#       endif
  }

  /** @return A string with a description of the Hypersponge object         */
  virtual std::string description () {
    std::ostringstream out;
    out << "Alternative Sponge (level = " << level_ << ")" << std::ends;
    return out.str ();
  }

    
  unsigned getLevel() const { return level_; }
  int getDistance() const { return distance_; }
  
protected:
  virtual void Initialize();
  virtual unsigned long MemRequired (unsigned);

  /// Remove all duplicate vertices, leaving only unique values
  void reduceVertices();
  /// Remove all duplicate surfaces
  void removeDuplicateSurfaces();
  /// When a duplicate vertex is removed, let all surfaces referencing it point to the original vertex.
  /** Also, all vertices after the removed one are shifted up by one element,
   *  so the surfaces pointing to them must be updated too.
   *
   *  \param original_vertex The vertex, first in the vertex array, that is kept.
   *  \param duplicate_vertex The removed vertex.
   */
  void renumberSurfaces(unsigned original_vertex, unsigned duplicate_vertex);
  
  void X_push_back(const VecMath::Vector<4> &x);

  unsigned level_;                 ///< Level of the hypersponge
  int distance_;                   ///< max. distance (see Initialize())
  double rad_;                     ///< radius, more correctly size, of the sponge
  VecMath::Vector<4> center_;      ///< center of the sponge
};

#if USE_ALT_SPONGE
namespace {
  Displayable *createAltSponge() { return new AltSponge(); }
  const bool registeredAS = TheFunctionFactory::Instance().registerFunction(createAltSponge, "Object");
}
#endif

#endif
