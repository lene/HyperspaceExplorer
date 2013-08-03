/* 
 * File:   ProjectionPolicyBase.h
 * Author: lene
 *
 * Created on April 11, 2012, 3:46 PM
 */

#ifndef PROJECTIONPOLICYBASE_H
#define	PROJECTIONPOLICYBASE_H

#include "Projection.h"

template <unsigned N, unsigned Nnew, unsigned P, typename NUM> class ProjectionPolicyBase {

protected:
    
    ProjectionPolicyBase(
        typename Projection<N, Nnew, P, NUM>::PointList viewpoint,
        typename Projection<N, Nnew, P, NUM>::PointList eye,
        typename Projection<N, Nnew, P, NUM>::DistanceList screen_distance,
        typename Projection<N, Nnew, P, NUM>::BoolList depth_cue
    ):
        _viewpoint(viewpoint), _eye(eye),
        _screen_distance(screen_distance), _depth_cue(depth_cue) { }

    /// List of view points for the downprojection in each dimension.
    typename Projection<N, Nnew, P, NUM>::PointList _viewpoint;
    /// List of camera positions for the downprojection in each dimension.
    typename Projection<N, Nnew, P, NUM>::PointList _eye;
    /// List of screen distances for the downprojection in each dimension.
    typename Projection<N, Nnew, P, NUM>::DistanceList _screen_distance;
    /// List of flags whether depth cue is used for the downprojection in each dimension.
    typename Projection<N, Nnew, P, NUM>::BoolList _depth_cue;

};

#endif	/* PROJECTIONPOLICYBASE_H */

