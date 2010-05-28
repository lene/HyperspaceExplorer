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
template <unsigned N, unsigned Nnew, unsigned P, typename NUM> class SimpleProjectionPolicy;

/// A list of Vector s of dimension \p Nnew+1 through \p N.
/** These are used in storing the view points and camera positions when projecting
 *  a point in \p N space into \p Nnew dimensions. Every projection from one
 *  dimension to the next lower dimension needs a Vector of the original dimension
 *  as camera position and one as view point.
 */
template <unsigned N, unsigned Nnew, typename NUM = double> class ViewpointList {

  public:

    /// Creates a ViewpointList with all elements at the origin.
    ViewpointList(): _elements() {
      _elements.first = VecMath::Vector<N, NUM>();
      _elements.second = ViewpointList<N-1, Nnew, NUM>();
    }

    /// Creates a list of Vector s whose highest element is set to \p camW.
    ViewpointList(NUM camW): _elements() {
      _elements.first = VecMath::Vector<N, NUM>();
      _elements.first[N-1] = camW;
      _elements.second = ViewpointList<N-1, Nnew, NUM>(camW);
    }

    ViewpointList(const VecMath::Vector<N, NUM> &single_element);
    ViewpointList(const VecMath::Vector<N, NUM> &head, const ViewpointList<N-1, Nnew, NUM> &tail);

    /// Return the first element of a ViewpointList.
    const VecMath::Vector<N, NUM> &head() const { return _elements.first; }
    /// Return the first element of a ViewpointList.
    VecMath::Vector<N, NUM> &head() { return _elements.first; }
    /// Return a ViewpointList that contains all but the first element.
    const ViewpointList<N-1, Nnew, NUM> &tail() const { return _elements.second; }
    /// Return a ViewpointList that contains all but the first element.
    ViewpointList<N-1, Nnew, NUM> &tail() { return _elements.second; }

    template <unsigned i> VecMath::Vector<N-i, NUM> get() {
      if (i == 0) return head();
      return tail().get<i-1>();
    }
//    template <> VecMath::Vector<N> get<0>() { return head(); }

    /// String representation.
    std::string toString() const { return _elements.first.toString()+", "+_elements.second.toString(); }

    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0);
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1);
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2);
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3);
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4);
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5);
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5,
                              const VecMath::Vector<N-6, NUM> &x6);
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5,
                              const VecMath::Vector<N-6, NUM> &x6, const VecMath::Vector<N-7, NUM> &x7);

  private:

    /// The elements of the list are stored as a tuple, recursively defined.
    std::pair< VecMath::Vector<N, NUM>, ViewpointList<N-1, Nnew, NUM> > _elements;
};

/// Specialization of ViewpointList for a projection from \p N space to \p N space - which does nothing.
/** Needed to end recursion. */
template <unsigned N, typename NUM> class ViewpointList<N, N, NUM> {
  public:
    ViewpointList() { }
    ViewpointList(NUM) { }
    std::string toString() const { return ""; }
};

/// Class that projects a \p N dimensional vertex array to \p Nnew dimensions.
/** \param N Original dimension of the Vector s to project.
 *  \param Nnew Dimension to project into.
 *  \param P Dimension of parameter space of the projected vertex array.
 *  \param Policy The class executing the actual projection on the vertices.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM = double, typename Policy = SimpleProjectionPolicy <N, Nnew, P, NUM> > class Projection {

  public:

    typedef ViewpointList< N, Nnew, NUM > PointList;
    typedef ArrayList< N-Nnew, NUM > DistanceList;
    typedef ArrayList< N-Nnew, bool > BoolList;

    /// Create a Projection with arbitrary view- and camera points for each dimension.
    Projection(const PointList &viewpoint, const PointList &eye,
               const DistanceList &screenDistance, const BoolList &depthCue4D);

    /// Create a Projection with view point at the origin, eye on the \em w axis and equal screen and eye distances in all dimensions.
    Projection(NUM scrW, NUM camW, bool depthCue4D);

    /// Execute the Projection on a \p P dimensional field of \p N dimensional vertices.
    VecMath::NestedVector< VecMath::Vector<Nnew, NUM>, P > project(
            const VecMath::NestedVector< VecMath::Vector<N, NUM>, P > &values);

  private:

    /// Check whether tis Projection is created with sensible parameters
    void checkConsistency();
    /// Check whether the template is instantiated with sensible values for the dimensions
    void checkDimensions();

    PointList makeViewPointList();
    PointList makeEyePointList(NUM camW);
    DistanceList makeScreenDistanceList(NUM scrW);
    BoolList makeDepthCueList(bool depthCue4D);

    PointList _viewpoint;
    PointList _eye;
    DistanceList _screen_distance;
    BoolList _depth_cue;

};

template <unsigned N, unsigned Nnew, unsigned P, typename NUM> class SimpleProjectionPolicy {

  public:

    SimpleProjectionPolicy(typename Projection<N, Nnew, P, NUM>::PointList viewpoint,
                           typename Projection<N, Nnew, P, NUM>::PointList eye,
                           typename Projection<N, Nnew, P, NUM>::DistanceList screen_distance,
                           typename Projection<N, Nnew, P, NUM>::BoolList depth_cue):
                           _viewpoint(viewpoint), _eye(eye),
                           _screen_distance(screen_distance), _depth_cue(depth_cue) { }

    VecMath::NestedVector< VecMath::Vector<Nnew, NUM>, P > project(
        const VecMath::NestedVector< VecMath::Vector<N, NUM>, P > &values);

  private:

    typename Projection<N, Nnew, P, NUM>::PointList _viewpoint;
    typename Projection<N, Nnew, P, NUM>::PointList _eye;
    typename Projection<N, Nnew, P, NUM>::DistanceList _screen_distance;
    typename Projection<N, Nnew, P, NUM>::BoolList _depth_cue;

};

template <unsigned N, unsigned Nnew, typename NUM> class SimpleProjectionPolicy<N, Nnew, 1, NUM> {

  public:

    SimpleProjectionPolicy(typename Projection<N, Nnew, 1, NUM>::PointList viewpoint,
                           typename Projection<N, Nnew, 1, NUM>::PointList eye,
                           typename Projection<N, Nnew, 1, NUM>::DistanceList screen_distance,
                           typename Projection<N, Nnew, 1, NUM>::BoolList depth_cue):
                           _viewpoint(viewpoint), _eye(eye),
                           _screen_distance(screen_distance), _depth_cue(depth_cue) { }

    VecMath::NestedVector< VecMath::Vector<Nnew, NUM>, 1 > project(
        const VecMath::NestedVector< VecMath::Vector<N, NUM>, 1 > &values);

  private:

    typename Projection<N, Nnew, 1, NUM>::PointList _viewpoint;
    typename Projection<N, Nnew, 1, NUM>::PointList _eye;
    typename Projection<N, Nnew, 1, NUM>::DistanceList _screen_distance;
    typename Projection<N, Nnew, 1, NUM>::BoolList _depth_cue;

};

template <unsigned N, typename NUM> class SimpleProjectionPolicy<N, N, 1, NUM> {

  public:

    SimpleProjectionPolicy(typename Projection<N, N, 1, NUM>::PointList,
                           typename Projection<N, N, 1, NUM>::PointList,
                           typename Projection<N, N, 1, NUM>::DistanceList,
                           typename Projection<N, N, 1, NUM>::BoolList) { }

    VecMath::NestedVector< VecMath::Vector<N, NUM>, 1 > project(
        const VecMath::NestedVector< VecMath::Vector<N, NUM>, 1 > &values) {
      return values;
    }

};

#include "Projection.impl.h"

#endif // PROJECTION_H
