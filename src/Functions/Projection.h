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

 *  \tparam N The dimension of the original vector space.
 *  \tparam Nnew The dimension of the vector space into which is projected.
 *  \tparam NUM The numeric type of the \c Vector s.
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

    /// Construct a ViewpointList with a single element.
    ViewpointList(const VecMath::Vector<N, NUM> &single_element);
    /// Construct a ViewpointList from an element and another ViewpointList.
    ViewpointList(const VecMath::Vector<N, NUM> &head, const ViewpointList<N-1, Nnew, NUM> &tail);

    /// Return the first element of a ViewpointList.
    const VecMath::Vector<N, NUM> &head() const { return _elements.first; }
    /// Return the first element of a ViewpointList.
    VecMath::Vector<N, NUM> &head() { return _elements.first; }
    /// Return a ViewpointList that contains all but the first element.
    const ViewpointList<N-1, Nnew, NUM> &tail() const { return _elements.second; }
    /// Return a ViewpointList that contains all but the first element.
    ViewpointList<N-1, Nnew, NUM> &tail() { return _elements.second; }

    /// Returns element \p i from the list.
    /** \tparam i The index of the requested element.
     */
    template <unsigned i> VecMath::Vector<N-i, NUM> get() {
      if (i == 0) return head();
      return tail().get<i-1>();
    }
//    template <> VecMath::Vector<N> get<0>() { return head(); }

    /// String representation.
    std::string toString() const { return _elements.first.toString()+", "+_elements.second.toString(); }

    /// Constructs a ViewpointList with one Member.
    /** \param x0 Viewpoint in Projection in first dimension.
     */
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0);
    /// Constructs a ViewpointList with two Members.
    /** \param x0 Viewpoint in Projection in first dimension.
     *  \param x1 Viewpoint in Projection in second dimension.
     */
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1);
    /// Constructs a ViewpointList with three Members.
    /** \param x0 Viewpoint in Projection in first dimension.
     *  \param x1 Viewpoint in Projection in second dimension.
     *  \param x2 Viewpoint in Projection in third dimension.
     */
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2);
    /// Constructs a ViewpointList with four Members.
    /** \param x0 Viewpoint in Projection in first dimension.
     *  \param x1 Viewpoint in Projection in second dimension.
     *  \param x2 Viewpoint in Projection in third dimension.
     *  \param x3 Viewpoint in Projection in fourth dimension.
     */
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3);
    /// Constructs a ViewpointList with five Members.
    /** \param x0 Viewpoint in Projection in first dimension.
     *  \param x1 Viewpoint in Projection in second dimension.
     *  \param x2 Viewpoint in Projection in third dimension.
     *  \param x3 Viewpoint in Projection in fourth dimension.
     *  \param x4 Viewpoint in Projection in fifth dimension.
     */
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4);
    /// Constructs a ViewpointList with six Members.
    /** \param x0 Viewpoint in Projection in first dimension.
     *  \param x1 Viewpoint in Projection in second dimension.
     *  \param x2 Viewpoint in Projection in third dimension.
     *  \param x3 Viewpoint in Projection in fourth dimension.
     *  \param x4 Viewpoint in Projection in fifth dimension.
     *  \param x5 Viewpoint in Projection in sixth dimension.
     */
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5);
    /// Constructs a ViewpointList with seven Members.
    /** \param x0 Viewpoint in Projection in first dimension.
     *  \param x1 Viewpoint in Projection in second dimension.
     *  \param x2 Viewpoint in Projection in third dimension.
     *  \param x3 Viewpoint in Projection in fourth dimension.
     *  \param x4 Viewpoint in Projection in fifth dimension.
     *  \param x5 Viewpoint in Projection in sixth dimension.
     *  \param x6 Viewpoint in Projection in seventh dimension.
     */
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5,
                              const VecMath::Vector<N-6, NUM> &x6);
    /// Constructs a ViewpointList with eight Members.
    /** \param x0 Viewpoint in Projection in first dimension.
     *  \param x1 Viewpoint in Projection in second dimension.
     *  \param x2 Viewpoint in Projection in third dimension.
     *  \param x3 Viewpoint in Projection in fourth dimension.
     *  \param x4 Viewpoint in Projection in fifth dimension.
     *  \param x5 Viewpoint in Projection in sixth dimension.
     *  \param x6 Viewpoint in Projection in seventh dimension.
     *  \param x7 Viewpoint in Projection in eight dimension.
     */
    static ViewpointList make(const VecMath::Vector<N, NUM>   &x0, const VecMath::Vector<N-1, NUM> &x1,
                              const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
                              const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5,
                              const VecMath::Vector<N-6, NUM> &x6, const VecMath::Vector<N-7, NUM> &x7);

  private:

    /// The elements of the list are stored as a tuple, recursively defined.
    std::pair< VecMath::Vector<N, NUM>, ViewpointList<N-1, Nnew, NUM> > _elements;
};

/// Specialization of ViewpointList for a projection from \p N space to \p N space - which does nothing.
/** Needed to end recursion.
 *  \tparam N The dimension of the vector space.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, typename NUM> class ViewpointList<N, N, NUM> {
  public:
    /// Constructs empty ViewpointList.
    ViewpointList() { }
    /// Constructs empty ViewpointList.
    ViewpointList(NUM) { }
    /// String representation.
    std::string toString() const { return ""; }
};

/// Class that projects a \p N dimensional vertex array to \p Nnew dimensions.
/** \tparam N Original dimension of the \c Vector s to project.
 *  \tparam Nnew Dimension to project into.
 *  \tparam P Dimension of parameter space of the projected vertex array.
 *  \tparam NUM The numeric type of the \c Vector s.
 *  \tparam Policy The class executing the actual projection on the vertices.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM = double, typename Policy = SimpleProjectionPolicy <N, Nnew, P, NUM> > class Projection {

  public:

    /// Type of the list of view points and camera positions.
    typedef ViewpointList< N, Nnew, NUM > PointList;
    /// Type of the list of screen distances from the camera.
    typedef ArrayList< N-Nnew, NUM > DistanceList;
    /// Type of the list of bools deciding whether each projection uses depth cue or not.
    typedef ArrayList< N-Nnew, bool > BoolList;

    /// Create a Projection with arbitrary view- and camera points for each dimension.
    /** \param viewpoint List of view points for the downprojection in each dimension.
     *  \param eye List of camera positions for the downprojection in each dimension.
     *  \param screenDistance List of screen distances for the downprojection in each
     *      dimension.
     *  \param depthCue4D List of flags whether depth cue is used for the downprojection
     *      in each dimension.
     */
    Projection(const PointList &viewpoint, const PointList &eye,
               const DistanceList &screenDistance, const BoolList &depthCue4D);

    /// Create a Projection with view point at the origin and same parameters for each dimension.
    /** Camera is on the axis which is projected along at distance \p camW from
     *  the origin, the screen has distance \p scrW and \p depthCue4D indicates
     *  if depth cue is used, the same in every projection that is done to project
     *  from \p N to \p Nnew.
     */
    Projection(NUM scrW, NUM camW, bool depthCue4D);

    /// Execute the Projection on a \p P dimensional field of \p N dimensional vertices.
    /** \param values The vertices which are projected to \p Nnew- space.
     */
    VecMath::NestedVector< VecMath::Vector<Nnew, NUM>, P > project(
            const VecMath::NestedVector< VecMath::Vector<N, NUM>, P > &values);

  private:

    /// Check whether this Projection is created with sensible parameters.
    void checkConsistency();
    /// Check whether the template is instantiated with sensible values for the dimensions.
    void checkDimensions();

    /// Generates a ViewpointList looking at the origin in every dimension.
    PointList makeOriginViewPointList();
    /// Generates a list of camera positions \p camW units away from the origin in every dimension.
    PointList makeEyePointList(NUM camW);
    /// Generates a list of screen distances \p scrW units away each.
    DistanceList makeScreenDistanceList(NUM scrW);
    /// Generates a list of bools which all are equal to \p depthCue4D.
    BoolList makeDepthCueList(bool depthCue4D);

    /// List of view points for the downprojection in each dimension.
    PointList _viewpoint;
    /// List of camera positions for the downprojection in each dimension.
    PointList _eye;
    /// List of screen distances for the downprojection in each dimension.
    DistanceList _screen_distance;
    /// List of flags whether depth cue is used for the downprojection in each dimension.
    BoolList _depth_cue;

};

/// Default Projection policy; single threaded, no optimizations.
/** \tparam N Original dimension of the \c Vector s to project.
 *  \tparam Nnew Dimension to project into.
 *  \tparam P Dimension of parameter space of the projected vertex array.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM> class SimpleProjectionPolicy {

  public:

    /// Create a SimpleProjectionPolicy with arbitrary view- and camera points for each dimension.
    /** \param viewpoint List of view points for the downprojection in each dimension.
     *  \param eye List of camera positions for the downprojection in each dimension.
     *  \param screen_distance List of screen distances for the downprojection in each
     *      dimension.
     *  \param depth_cue List of flags whether depth cue is used for the downprojection
     *      in each dimension.
     */
    SimpleProjectionPolicy(typename Projection<N, Nnew, P, NUM>::PointList viewpoint,
                           typename Projection<N, Nnew, P, NUM>::PointList eye,
                           typename Projection<N, Nnew, P, NUM>::DistanceList screen_distance,
                           typename Projection<N, Nnew, P, NUM>::BoolList depth_cue):
                           _viewpoint(viewpoint), _eye(eye),
                           _screen_distance(screen_distance), _depth_cue(depth_cue) { }

    /// Execute the Projection on the given grid of \p values.
    VecMath::NestedVector< VecMath::Vector<Nnew, NUM>, P > project(
        const VecMath::NestedVector< VecMath::Vector<N, NUM>, P > &values);

  private:

    /// List of view points for the downprojection in each dimension.
    typename Projection<N, Nnew, P, NUM>::PointList _viewpoint;
    /// List of camera positions for the downprojection in each dimension.
    typename Projection<N, Nnew, P, NUM>::PointList _eye;
    /// List of screen distances for the downprojection in each dimension.
    typename Projection<N, Nnew, P, NUM>::DistanceList _screen_distance;
    /// List of flags whether depth cue is used for the downprojection in each dimension.
    typename Projection<N, Nnew, P, NUM>::BoolList _depth_cue;

};

/// Default Projection policy - specialization to end recursion.
/** Operates on a one-dimensional vector of \c Vector s.
 *  \tparam N Original dimension of the \c Vector s to project.
 *  \tparam Nnew Dimension to project into.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned Nnew, typename NUM> class SimpleProjectionPolicy<N, Nnew, 1, NUM> {

  public:

    /// Create a SimpleProjectionPolicy with arbitrary view- and camera points for each dimension.
    /** \param viewpoint List of view points for the downprojection in each dimension.
     *  \param eye List of camera positions for the downprojection in each dimension.
     *  \param screen_distance List of screen distances for the downprojection in each
     *      dimension.
     *  \param depth_cue List of flags whether depth cue is used for the downprojection
     *      in each dimension.
     */
    SimpleProjectionPolicy(typename Projection<N, Nnew, 1, NUM>::PointList viewpoint,
                           typename Projection<N, Nnew, 1, NUM>::PointList eye,
                           typename Projection<N, Nnew, 1, NUM>::DistanceList screen_distance,
                           typename Projection<N, Nnew, 1, NUM>::BoolList depth_cue):
                           _viewpoint(viewpoint), _eye(eye),
                           _screen_distance(screen_distance), _depth_cue(depth_cue) { }

    /// Execute the Projection on the given grid of \p values.
    VecMath::NestedVector< VecMath::Vector<Nnew, NUM>, 1 > project(
        const VecMath::NestedVector< VecMath::Vector<N, NUM>, 1 > &values);

  private:

    /// List of view points for the downprojection in each dimension.
    typename Projection<N, Nnew, 1, NUM>::PointList _viewpoint;
    /// List of camera positions for the downprojection in each dimension.
    typename Projection<N, Nnew, 1, NUM>::PointList _eye;
    /// List of screen distances for the downprojection in each dimension.
    typename Projection<N, Nnew, 1, NUM>::DistanceList _screen_distance;
    /// List of flags whether depth cue is used for the downprojection in each dimension.
    typename Projection<N, Nnew, 1, NUM>::BoolList _depth_cue;

};

/// Default Projection policy - specialization to end recursion.
/** Operates on a one-dimensional vector of \c Vector s, projecting from \p N-
 *  space to \p N- space - in other words, does nothing at all.
 *  \tparam N Original dimension of the \c Vector s to project.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, typename NUM> class SimpleProjectionPolicy<N, N, 1, NUM> {

  public:

    /// Create a SimpleProjectionPolicy whose view- and camera points are ignored.
    SimpleProjectionPolicy(typename Projection<N, N, 1, NUM>::PointList,
                           typename Projection<N, N, 1, NUM>::PointList,
                           typename Projection<N, N, 1, NUM>::DistanceList,
                           typename Projection<N, N, 1, NUM>::BoolList) { }

    /// Returns the given grid of \p values.
    VecMath::NestedVector< VecMath::Vector<N, NUM>, 1 > project(
        const VecMath::NestedVector< VecMath::Vector<N, NUM>, 1 > &values) {
      return values;
    }

};

#include "Projection.impl.h"

#endif // PROJECTION_H
