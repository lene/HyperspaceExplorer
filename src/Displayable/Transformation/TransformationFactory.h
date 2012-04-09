/* 
 * File:   TransformationFactory.h
 * Author: lene
 *
 * Created on December 17, 2011, 2:59 AM
 */

#ifndef TRANSFORMATIONFACTORY_H
#define	TRANSFORMATIONFACTORY_H

#include <memory>

namespace VecMath {
    template < unsigned N, typename NUM > class Rotation;
    template < unsigned N, typename NUM > class Vector;
}
template < unsigned N, unsigned P, typename NUM >
class Transformation;

/// This class creates a Transformation. Always use it instead of the Transformation constructor.
/** 
 *  The method used for performing a Transformation is assigned with
 *  setTransformationMethod() and a Transformation is created (according to the
 *  globally selected Method) with create().
 */
class TransformationFactory {
    
public:

    /// The methods in which a Transformation can be performed.
    typedef enum { Singlethreaded, Multithreaded } Method;
    
    /// Globally set how a Transformation is performed.
    static void setTransformationMethod(const Method &method);

    /// How a Transformation is performed.
    static Method getTransformationMethod();
    
    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    template < unsigned N, unsigned P, typename NUM = double >
    static const Transformation< N, P, NUM > *create(
        const VecMath::Rotation<N, NUM> &rotation,
        const VecMath::Vector<N, NUM> &translation,
        const VecMath::Vector<N, NUM> &scale
    );

    /// Initialize an identity Transformation.
    template < unsigned N, unsigned P, typename NUM = double >
    static const Transformation< N, P, NUM > *create();

private:
    
    static Method method_;
    
};

#endif	/* TRANSFORMATIONFACTORY_H */

