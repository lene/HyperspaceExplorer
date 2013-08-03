/* 
 * File:   SinglethreadedProjectionPolicy.h
 * Author: lene
 *
 * Created on April 11, 2012, 2:06 PM
 */

#ifndef SINGLETHREADEDPROJECTIONPOLICY_H
#define	SINGLETHREADEDPROJECTIONPOLICY_H

#include "ProjectionPolicyBase.h"

/// Default Projection policy; single threaded, no optimizations.
/** \tparam N Original dimension of the \c Vector s to project.
 *  \tparam Nnew Dimension to project into.
 *  \tparam P Dimension of parameter space of the projected vertex array.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM> class SinglethreadedProjectionPolicy:
public ProjectionPolicyBase<N, Nnew, P, NUM> {

    typedef VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P > original_vertices;
    typedef VecMath::MultiDimensionalVector< VecMath::Vector<Nnew, NUM>, P > projected_vertices;
    
public:

    /// Create a SimpleProjectionPolicy with arbitrary view- and camera points for each dimension.
    /** \param viewpoint List of view points for the downprojection in each dimension.
     *  \param eye List of camera positions for the downprojection in each dimension.
     *  \param screen_distance List of screen distances for the downprojection in each
     *      dimension.
     *  \param depth_cue List of flags whether depth cue is used for the downprojection
     *      in each dimension.
     */
    SinglethreadedProjectionPolicy(
        typename Projection<N, Nnew, P, NUM>::PointList viewpoint,
        typename Projection<N, Nnew, P, NUM>::PointList eye,
        typename Projection<N, Nnew, P, NUM>::DistanceList screen_distance,
        typename Projection<N, Nnew, P, NUM>::BoolList depth_cue
    ): ProjectionPolicyBase<N, Nnew, P, NUM>(viewpoint, eye, screen_distance, depth_cue) { }

    /// Execute the Projection on the given grid of \p values.
    projected_vertices project(const original_vertices &original) {

        projected_vertices projected(original.size());

        project(original, projected);

        return projected;
    }

        /// Execute the Projection on the given grid of \p values.
    void project(const original_vertices &original, projected_vertices &projected) {
        SinglethreadedProjectionPolicy<N, Nnew, P-1, NUM> p(
            this->_viewpoint, this->_eye, this->_screen_distance, this->_depth_cue
        );
        for (unsigned i = 0; i < original.size(); ++i) {
            projected[i] = p.project(original[i]);
        }
    }

};

/// Default Projection policy - specialization to end recursion.
/** Operates on a one-dimensional vector of \c Vector s.
 *  \tparam N Original dimension of the \c Vector s to project.
 *  \tparam Nnew Dimension to project into.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned Nnew, typename NUM> 
class SinglethreadedProjectionPolicy<N, Nnew, 1, NUM>:
public ProjectionPolicyBase<N, Nnew, 1, NUM> {

  public:

    /// Create a SimpleProjectionPolicy with arbitrary view- and camera points for each dimension.
    /** \param viewpoint List of view points for the downprojection in each dimension.
     *  \param eye List of camera positions for the downprojection in each dimension.
     *  \param screen_distance List of screen distances for the downprojection in each
     *      dimension.
     *  \param depth_cue List of flags whether depth cue is used for the downprojection
     *      in each dimension.
     */
    SinglethreadedProjectionPolicy(
        typename Projection<N, Nnew, 1, NUM>::PointList viewpoint,
        typename Projection<N, Nnew, 1, NUM>::PointList eye,
        typename Projection<N, Nnew, 1, NUM>::DistanceList screen_distance,
        typename Projection<N, Nnew, 1, NUM>::BoolList depth_cue
    ): ProjectionPolicyBase<N, Nnew, 1, NUM>(viewpoint, eye, screen_distance, depth_cue) { }
    
    /// Execute the Projection on the given grid of \p values.
    VecMath::MultiDimensionalVector< VecMath::Vector<Nnew, NUM>, 1 > project(
        const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, 1 > &values
    ) {

        VecMath::MultiDimensionalVector< VecMath::Vector<N-1, NUM>, 1 > downprojected(values.size());

        NUM _screen_W = this->_screen_distance.head();
        NUM _camera_W = this->_eye.head()[N-1];
        for (unsigned i = 0; i < values.size(); ++i) {

            NUM projectionFactor = (_screen_W-_camera_W)/(values[i][N-1]-_camera_W);

            for (unsigned j = 0; j < N-1; ++j) downprojected[i][j] = projectionFactor*values[i][j];

        }

        ViewpointList<N-1, Nnew, NUM> v = this->_viewpoint.tail();
        ViewpointList<N-1, Nnew, NUM> e = this->_eye.tail();
        ArrayList<N-Nnew-1, NUM >     s = this->_screen_distance.tail();
        ArrayList<N-Nnew-1, bool >    d = this->_depth_cue.tail();
        SinglethreadedProjectionPolicy<N-1, Nnew, 1, NUM> p(v, e, s, d);

        return p.project(downprojected);

    }

};

/// Default Projection policy - specialization to end recursion.
/** Operates on a one-dimensional vector of \c Vector s, projecting from \p N-
 *  space to \p N- space - in other words, does nothing at all.
 *  \tparam N Original dimension of the \c Vector s to project.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, typename NUM> class SinglethreadedProjectionPolicy<N, N, 1, NUM> {

  public:

    /// Create a SimpleProjectionPolicy whose view- and camera points are ignored.
    SinglethreadedProjectionPolicy(
        typename Projection<N, N, 1, NUM>::PointList,
        typename Projection<N, N, 1, NUM>::PointList,
        typename Projection<N, N, 1, NUM>::DistanceList,
        typename Projection<N, N, 1, NUM>::BoolList
    ) { }

    /// Returns the given grid of \p values.
    VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, 1 > project(
        const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, 1 > &values
    ) {
        return values;
    }

};

#endif	/* SINGLETHREADEDPROJECTIONPOLICY_H */

