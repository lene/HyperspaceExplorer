/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
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

#ifndef PROJECTION_H
#define PROJECTION_H

#include "Vector.h"
#include "NestedVector.h"
#include "ArrayList.h"

/// Forward declaration needed to make the SimpleTransformationPolicy a default template parameter for Transformation.
template <unsigned N, unsigned Nnew, unsigned P> class SimpleProjectionPolicy;


template <unsigned N, unsigned Nnew> class ViewpointList {

  public:
    
    ViewpointList(): _elements() { 
      _elements.first = VecMath::Vector<N>(); 
      _elements.second = ViewpointList<N-1, Nnew>();
    }
    ViewpointList(double camW): _elements() {
      _elements.first = VecMath::Vector<N>(); 
      _elements.first[N-1] = camW;
      _elements.second = ViewpointList<N-1, Nnew>(camW);
    }
    const VecMath::Vector<N> &head() const { return _elements.first; }
    VecMath::Vector<N> &head() { return _elements.first; }
    const ViewpointList<N-1, Nnew> &tail() const { return _elements.second; }
    ViewpointList<N-1, Nnew> &tail() { return _elements.second; }
    std::string toString() const { return _elements.first.toString()+", "+_elements.second.toString(); }

  private:
    std::pair< VecMath::Vector<N>, ViewpointList<N-1, Nnew> > _elements;
};

template <unsigned N> class ViewpointList<N, N> {
  public:
    ViewpointList() { }
    ViewpointList(double) { }
    std::string toString() const { return ""; }
};

/// Class that projects a \p N dimensional vertex array to \p Nnew dimensions.
/** \param N Original dimension of the Vector s to project.
 *  \param Nnew Dimension to project into.
 *  \param P Dimension of parameter space of the projected vertex array.
 *  \param Policy The class executing the actual projection on the vertices.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename Policy = SimpleProjectionPolicy <N, Nnew, P> > class Projection {
  
  public:

    typedef ViewpointList< N, Nnew > PointList;
    typedef ArrayList< N-Nnew, double > DistanceList;
    typedef ArrayList< N-Nnew, bool > BoolList;

    /// Create a Projection with arbitrary view- and camera points for each dimension.
    Projection(const PointList &viewpoint, const PointList &eye,
               const DistanceList &screenDistance, const BoolList &depthCue4D);

    /// Create a Projection with view point at the origin, eye on the \em w axis and equal screen and eye distances in all dimensions.
    Projection(double scrW, double camW, bool depthCue4D);

    /// Execute the Projection on a \p P dimensional field of \p N dimensional vertices.
    VecMath::NestedVector< VecMath::Vector<Nnew>, P > project(
            const VecMath::NestedVector< VecMath::Vector<N>, P > &values);

  private:

    /// Check whether tis Projection is created with sensible parameters
    void checkConsistency();
    /// Check whether the template is instantiated with sensible values for the dimensions
    void checkDimensions();
    
    PointList makeViewPointList();
    PointList makeEyePointList(double camW);
    DistanceList makeScreenDistanceList(double scrW);
    BoolList makeDepthCueList(bool depthCue4D);
    
    PointList _viewpoint;
    PointList _eye; 
    DistanceList _screen_distance;
    BoolList _depth_cue;

};

template <unsigned N, unsigned Nnew, unsigned P> class SimpleProjectionPolicy {
  
  public:

    SimpleProjectionPolicy(typename Projection<N, Nnew, P>::PointList viewpoint, 
                           typename Projection<N, Nnew, P>::PointList eye,
                           typename Projection<N, Nnew, P>::DistanceList screen_distance,
                           typename Projection<N, Nnew, P>::BoolList depth_cue):
                           _viewpoint(viewpoint), _eye(eye), 
                           _screen_distance(screen_distance), _depth_cue(depth_cue) { }

    VecMath::NestedVector< VecMath::Vector<Nnew>, P > project(
        const VecMath::NestedVector< VecMath::Vector<N>, P > &values);

  private:

    typename Projection<N, Nnew, P>::PointList _viewpoint;
    typename Projection<N, Nnew, P>::PointList _eye; 
    typename Projection<N, Nnew, P>::DistanceList _screen_distance;
    typename Projection<N, Nnew, P>::BoolList _depth_cue;
    
};

template <unsigned N, unsigned Nnew> class SimpleProjectionPolicy<N, Nnew, 1> {
  
  public:
    
    SimpleProjectionPolicy(typename Projection<N, Nnew, 1>::PointList viewpoint, 
                           typename Projection<N, Nnew, 1>::PointList eye,
                           typename Projection<N, Nnew, 1>::DistanceList screen_distance,
                           typename Projection<N, Nnew, 1>::BoolList depth_cue):
                           _viewpoint(viewpoint), _eye(eye), 
                           _screen_distance(screen_distance), _depth_cue(depth_cue) { }
    
    VecMath::NestedVector< VecMath::Vector<Nnew>, 1 > project(
        const VecMath::NestedVector< VecMath::Vector<N>, 1 > &values);
    
  private:
    
    typename Projection<N, Nnew, 1>::PointList _viewpoint;
    typename Projection<N, Nnew, 1>::PointList _eye; 
    typename Projection<N, Nnew, 1>::DistanceList _screen_distance;
    typename Projection<N, Nnew, 1>::BoolList _depth_cue;
    
};

template <unsigned N> class SimpleProjectionPolicy<N, N, 1> {
  
  public:
    
    SimpleProjectionPolicy(typename Projection<N, N, 1>::PointList, 
                           typename Projection<N, N, 1>::PointList,
                           typename Projection<N, N, 1>::DistanceList,
                           typename Projection<N, N, 1>::BoolList) { }

    VecMath::NestedVector< VecMath::Vector<N>, 1 > project(
        const VecMath::NestedVector< VecMath::Vector<N>, 1 > &values) {
      return values;
    }
    
};

#include "Projection.impl.h"

#endif // PROJECTION_H
