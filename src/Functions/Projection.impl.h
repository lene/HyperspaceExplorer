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

template <unsigned N, unsigned Nnew, unsigned P, class Policy>
Projection<N, Nnew, P, Policy>::Projection(
const PointList &viewpoint, const PointList &eye,
const DistanceList &screenDistance, const BoolList &depthCue4D):
    _viewpoint(viewpoint), _eye(eye), _screen_distance(screenDistance), _depth_cue_4d(depthCue4D) {
  checkConsistency();
}

template <unsigned N, unsigned Nnew, unsigned P, class Policy>
Projection<N, Nnew, P, Policy>::Projection(double scrW, double camW, bool depthCue4D):
    _screen_W(scrW), _camera_W(camW), _depthCue4D(depthCue4D) {
  _viewpoint = makeViewPointList();
  checkConsistency();
}

template <unsigned N, unsigned Nnew, unsigned P, class Policy>
VecMath::NestedVector< VecMath::Vector<Nnew>, P >
Projection<N, Nnew, P, Policy>::project(
const VecMath::NestedVector< VecMath::Vector<N>, P > &values) {
  Policy p(_screen_W, _camera_W, _depthCue4D);
  return p.project(values);
}


template <unsigned N, unsigned Nnew, unsigned P, class Policy>
void Projection<N, Nnew, P, Policy>::checkConsistency() {
  checkDimensions();
}

template <unsigned N, unsigned Nnew, unsigned P, class Policy>
void Projection<N, Nnew, P, Policy>::checkDimensions() {
  if (Nnew > N) throw std::logic_error("Tried to project to a higher dimension");
  if (Nnew == N) throw std::logic_error("Explicit specialization should be called");
}

template <unsigned N, unsigned Nnew, unsigned P, class Policy>
typename Projection<N, Nnew, P, Policy>::PointList 
Projection<N, Nnew, P, Policy>::makeViewPointList() {
  PointList p(Vector<N>(0.));
  return p;
}





template <unsigned N, unsigned Nnew, unsigned P>
VecMath::NestedVector< VecMath::Vector<Nnew>, P >
SimpleProjectionPolicy< N, Nnew, P >::project(
const VecMath::NestedVector< VecMath::Vector<N>, P > &values) {
  
  VecMath::NestedVector< VecMath::Vector<Nnew>, P > v(values.size());
  
  for (unsigned i = 0; i < values.size(); ++i) {
    SimpleProjectionPolicy<N, Nnew, P-1> p(_screen_W, _camera_W, _depthCue4D);
    v[i] = p.project(values[i]);
  }

  return v;
  
}

template <unsigned N, unsigned Nnew>
VecMath::NestedVector< VecMath::Vector<Nnew>, 1 >
SimpleProjectionPolicy< N, Nnew, 1 >::project(
const VecMath::NestedVector< VecMath::Vector<N>, 1 > &values) {

  VecMath::NestedVector< VecMath::Vector<N-1>, 1 > v(values.size());

  for (unsigned i = 0; i < values.size(); ++i) {

    double projectionFactor = (_screen_W-_camera_W)/(values[i][N-1]-_camera_W);
    
    for (unsigned j = 0; j < N-1; ++j) v[i][j] = projectionFactor*values[i][j];
  
  }

  SimpleProjectionPolicy<N-1, Nnew, 1> p(_screen_W, _camera_W, _depthCue4D);
  
  return p.project(v);
  
}

#endif // PROJECTION_IMPL_H
