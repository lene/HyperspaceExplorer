/* 
 * File:   TransformationPolicy.h
 * Author: lene
 *
 * Created on December 15, 2011, 11:42 PM
 */

#ifndef TRANSFORMATIONPOLICY_H
#define	TRANSFORMATIONPOLICY_H

#include "FunctionValueGrid.h"

template <unsigned N, unsigned P, typename NUM = double>
class TransformationPolicy {

  public:
    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, P, NUM >::value_storage_type value_storage_type;

    value_storage_type transform(const value_storage_type &operand);

  protected:

    TransformationPolicy(const VecMath::Rotation<N, NUM> &rotation,
                         const VecMath::Vector<N, NUM> &translation,
                         const VecMath::Vector<N, NUM> &scale):
    rotation_(rotation), translation_(translation), scale_(scale) { }

    VecMath::Rotation<N, NUM> rotation_;      ///< Rotation part of the Transformation.
    VecMath::Vector<N, NUM> translation_;   ///< Translation part of the Transformation.
    VecMath::Vector<N, NUM> scale_;         ///< Scaling part of the Transformation.

};

#endif	/* TRANSFORMATIONPOLICY_H */

