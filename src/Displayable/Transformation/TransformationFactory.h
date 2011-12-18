/* 
 * File:   TransformationFactory.h
 * Author: lene
 *
 * Created on December 17, 2011, 2:59 AM
 */

#ifndef TRANSFORMATIONFACTORY_H
#define	TRANSFORMATIONFACTORY_H

#include "SimpleTransformationPolicy.h"
#include "MultithreadedTransformationPolicy.h"

#include <memory>

template < unsigned N, unsigned P, typename NUM >
class Transformation;

template < unsigned N, unsigned P, typename NUM >
class TransformationFactory {
    
public:

    typedef enum { Singlethreaded, Multithreaded } Method;
    
    static void setTransformationMethod(const Method &method);

    static Method getTransformationMethod();
    
    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    static const Transformation< N, P, NUM > &create(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    );

        /// Initialize an identity Transformation.
    static const Transformation< N, P, NUM > &create();

    template <typename Policy> static const Transformation< N, P, NUM > &createWithPolicy(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    );
    
private:
    
    static std::shared_ptr< const Transformation< N, P, NUM > > pointerToImpl_;
    
    static Method method_;
    
};

#endif	/* TRANSFORMATIONFACTORY_H */
