/* 
 * File:   MultithreadedProjectionPolicy.h
 * Author: lene
 *
 * Created on April 11, 2012, 3:50 PM
 */

#ifndef MULTITHREADEDPROJECTIONPOLICY_H
#define	MULTITHREADEDPROJECTIONPOLICY_H

#include "ProjectionPolicyBase.h"

#include "SinglethreadedProjectionPolicy.h"

/// Default Projection policy; single threaded, no optimizations.
/** \tparam N Original dimension of the \c Vector s to project.
 *  \tparam Nnew Dimension to project into.
 *  \tparam P Dimension of parameter space of the projected vertex array.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned Nnew, unsigned P, typename NUM> class MultithreadedProjectionPolicy:
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
    MultithreadedProjectionPolicy(
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

    private:

#       if 1
        struct MapFunctor {
            
            typedef VecMath::MultiDimensionalVector< VecMath::Vector<Nnew, NUM>, P-1 > result_type;

            MapFunctor(SinglethreadedProjectionPolicy<N, Nnew, P-1, NUM> &projector):
                projector_(projector) { }

            /** 
            *  Execute a transformation on a subpart of the MultithreadedTransformation's 
            *  operand
            *  
            *  \param arg The subpart
            */
            result_type operator() (
                const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P-1 > &arg
            ) {
                return projector_.project(arg);
            }
            
        private:
            
            SinglethreadedProjectionPolicy<N, Nnew, P-1, NUM> &projector_;
            
        };
#       endif        
};



#endif	/* MULTITHREADEDPROJECTIONPOLICY_H */

