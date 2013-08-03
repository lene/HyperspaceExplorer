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
#include "MultiDimensionalVector.h"
#include "ViewpointList.h"
#include "ArrayList.h"

/// Forward declaration needed to make the SimpleProjectionPolicy a default template parameter for Projection.
template <unsigned N, unsigned Nnew, unsigned P, typename NUM> class SinglethreadedProjectionPolicy;

/// Class that projects a \p N dimensional vertex array to \p Nnew dimensions.
/** \tparam N Original dimension of the \c Vector s to project.
 *  \tparam Nnew Dimension to project into.
 *  \tparam P Dimension of parameter space of the projected vertex array.
 *  \tparam NUM The numeric type of the \c Vector s.
 *  \tparam Policy The class executing the actual projection on the vertices.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM = double, 
          typename Policy = SinglethreadedProjectionPolicy <N, Nnew, P, NUM> > 
class Projection {

  public:

    /// Type of the list of view points and camera positions.
    typedef ViewpointList< N, Nnew, NUM > PointList;
    /// Type of the list of screen distances from the camera.
    typedef ArrayList< N-Nnew, NUM > DistanceList;
    /// Type of the list of bools deciding whether each projection uses depth cue or not.
    typedef ArrayList< N-Nnew, bool > BoolList;

    /// Create a Projection with arbitrary view- and camera points for each dimension.
    Projection(const PointList &viewpoint, const PointList &eye,
               const DistanceList &screenDistance, const BoolList &depthCue4D);

    /// Create a Projection with view point at the origin and same parameters for each dimension.
    Projection(NUM scrW, NUM camW, bool depthCue4D);

    /// Execute the Projection on a \p P dimensional field of \p N dimensional vertices.
    VecMath::MultiDimensionalVector< VecMath::Vector<Nnew, NUM>, P > project(
            const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > &values);

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


#endif // PROJECTION_H
