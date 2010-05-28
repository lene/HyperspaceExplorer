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

#include <Projection.h>

#include <stdexcept>
#include <sstream>

using VecMath::Vector;
using VecMath::NestedVector;

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
Projection<N, Nnew, P, NUM, Policy>::Projection(
const PointList &viewpoint, const PointList &eye,
const DistanceList &screenDistance, const BoolList &depthCue):
    _viewpoint(viewpoint), _eye(eye), _screen_distance(screenDistance), _depth_cue(depthCue) {
  checkConsistency();
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
Projection<N, Nnew, P, NUM, Policy>::Projection(NUM scrW, NUM camW, bool depthCue4D) {
  _viewpoint = makeViewPointList();
  _eye = makeEyePointList(camW);
  _screen_distance = makeScreenDistanceList(scrW);
  _depth_cue = makeDepthCueList(depthCue4D);
  checkConsistency();
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
VecMath::NestedVector< VecMath::Vector<Nnew, NUM>, P >
Projection<N, Nnew, P, NUM, Policy>::project(
const VecMath::NestedVector< VecMath::Vector<N, NUM>, P > &values) {
  Policy p(_viewpoint, _eye, _screen_distance, _depth_cue);
  return p.project(values);
}


template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
void Projection<N, Nnew, P, NUM, Policy>::checkConsistency() {
  checkDimensions();
}

/** \todo don't throw exceptions, throw compilation errors! */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
void Projection<N, Nnew, P, NUM, Policy>::checkDimensions() {
  if (Nnew > N) throw std::logic_error("Tried to project to a higher dimension");
  if (Nnew == N) throw std::logic_error("Explicit specialization should be called");
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
typename Projection<N, Nnew, P, NUM, Policy>::PointList
Projection<N, Nnew, P, NUM, Policy>::makeViewPointList() {
  PointList p;
  std::cerr << "makeViewPointList: " << p.toString() << std::endl;
  return p;
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
typename Projection<N, Nnew, P, NUM, Policy>::PointList
Projection<N, Nnew, P, NUM, Policy>::makeEyePointList(NUM camW) {
  PointList p(camW);
  std::cerr << "makeEyePointList: " << p.toString() << std::endl;

  return p;
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
typename Projection<N, Nnew, P, NUM, Policy>::DistanceList
Projection<N, Nnew, P, NUM, Policy>::makeScreenDistanceList(NUM scrW) {
  DistanceList p(scrW);
  std::cerr << "makeScreenDistanceList: " << p.toString() << std::endl;
  return p;
}

template <unsigned N, unsigned Nnew, unsigned P, typename NUM, class Policy>
typename Projection<N, Nnew, P, NUM, Policy>::BoolList
Projection<N, Nnew, P, NUM, Policy>::makeDepthCueList(bool depthCue) {
  BoolList p(depthCue);
  std::cerr << "makeDepthCueList: " << p.toString() << std::endl;
  return p;
}


template <unsigned N, unsigned Nnew, unsigned P, typename NUM>
VecMath::NestedVector< VecMath::Vector<Nnew, NUM>, P >
SimpleProjectionPolicy< N, Nnew, P, NUM >::project(
const VecMath::NestedVector< VecMath::Vector<N, NUM>, P > &values) {

  NestedVector< Vector<Nnew, NUM>, P > v(values.size());

  for (unsigned i = 0; i < values.size(); ++i) {
    SimpleProjectionPolicy<N, Nnew, P-1, NUM> p(_viewpoint, _eye, _screen_distance, _depth_cue);
    v[i] = p.project(values[i]);
  }

  return v;

}

template <unsigned N, unsigned Nnew, typename NUM>
VecMath::NestedVector< VecMath::Vector<Nnew, NUM>, 1 >
SimpleProjectionPolicy< N, Nnew, 1, NUM >::project(
const VecMath::NestedVector< VecMath::Vector<N, NUM>, 1 > &values) {

  NestedVector< Vector<N-1, NUM>, 1 > downprojected(values.size());

  NUM _screen_W = _screen_distance.head();
  NUM _camera_W = _eye.head()[N-1];
  for (unsigned i = 0; i < values.size(); ++i) {

    NUM projectionFactor = (_screen_W-_camera_W)/(values[i][N-1]-_camera_W);

    for (unsigned j = 0; j < N-1; ++j) downprojected[i][j] = projectionFactor*values[i][j];

  }

  ViewpointList<N-1, Nnew, NUM> v = _viewpoint.tail();
  ViewpointList<N-1, Nnew, NUM> e = _eye.tail();
  ArrayList<N-Nnew-1, NUM > s = _screen_distance.tail();
  ArrayList<N-Nnew-1, bool > d = _depth_cue.tail();
  SimpleProjectionPolicy<N-1, Nnew, 1, NUM> p(v, e, s, d);

  return p.project(downprojected);

}

#endif // PROJECTION_IMPL_H
