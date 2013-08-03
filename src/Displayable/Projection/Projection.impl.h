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

#ifndef PROJECTION_IMPL_H
#define PROJECTION_IMPL_H

#include "Projection.h"
#include "SinglethreadedProjectionPolicy.h"

#include "ViewpointList.impl.h"
#include "ArrayList.impl.h"

#include <stdexcept>
#include <sstream>

using VecMath::Vector;
using VecMath::MultiDimensionalVector;

/** \param viewpoint List of view points for the downprojection in each dimension.
 *  \param eye List of camera positions for the downprojection in each dimension.
 *  \param screenDistance List of screen distances for the downprojection in each
 *      dimension.
 *  \param depthCue List of flags whether depth cue is used for the downprojection
 *      in each dimension.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
Projection<N, Nnew, P, NUM, Policy>::Projection(
const PointList &viewpoint, const PointList &eye,
const DistanceList &screenDistance, const BoolList &depthCue):
    _viewpoint(viewpoint), _eye(eye), _screen_distance(screenDistance), _depth_cue(depthCue) {
  checkConsistency();
}

/** Camera is on the axis which is projected along at distance \p camW from
 *  the origin, the screen has distance \p scrW and \p depthCue4D indicates
 *  if depth cue is used, the same in every projection that is done to project
 *  from \p N to \p Nnew.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
Projection<N, Nnew, P, NUM, Policy>::Projection(NUM scrW, NUM camW, bool depthCue4D) {
  _viewpoint = makeOriginViewPointList();
  _eye = makeEyePointList(camW);
  _screen_distance = makeScreenDistanceList(scrW);
  _depth_cue = makeDepthCueList(depthCue4D);
  checkConsistency();
}

/** \param values The vertices which are projected to \p Nnew- space.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
VecMath::MultiDimensionalVector< VecMath::Vector<Nnew, NUM>, P >
Projection<N, Nnew, P, NUM, Policy>::project(
const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &values) {
  Policy p(_viewpoint, _eye, _screen_distance, _depth_cue);
  return p.project(values);
}

/** \todo check view points, eye points and distances.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
void Projection<N, Nnew, P, NUM, Policy>::checkConsistency() {
  checkDimensions();
}

/** \todo I would prefer a compilation error to throwing an exception when \p N
 *      equals \p Nnew, but I don't see how to achieve this.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
void Projection<N, Nnew, P, NUM, Policy>::checkDimensions() {
# if Nnew > N
#   error "Tried to project to a higher dimension"
# endif
  if (Nnew == N) throw std::logic_error("Explicit specialization should be called");
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
typename Projection<N, Nnew, P, NUM, Policy>::PointList
Projection<N, Nnew, P, NUM, Policy>::makeOriginViewPointList() {
  PointList p;
  return p;
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
typename Projection<N, Nnew, P, NUM, Policy>::PointList
Projection<N, Nnew, P, NUM, Policy>::makeEyePointList(NUM camW) {
  PointList p(camW);
  return p;
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
typename Projection<N, Nnew, P, NUM, Policy>::DistanceList
Projection<N, Nnew, P, NUM, Policy>::makeScreenDistanceList(NUM scrW) {
  DistanceList p(scrW);
  return p;
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
typename Projection<N, Nnew, P, NUM, Policy>::BoolList
Projection<N, Nnew, P, NUM, Policy>::makeDepthCueList(bool depthCue) {
  BoolList p(depthCue);
  return p;
}


#endif // PROJECTION_IMPL_H
