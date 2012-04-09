/* 
 * File:   MultithreadedTransformation.h
 * Author: lene
 *
 * Created on March 30, 2012, 5:59 PM
 */

#ifndef MULTITHREADEDTRANSFORMATION_H
#define	MULTITHREADEDTRANSFORMATION_H

#include "Transformation.h"
#include "SinglethreadedTransformation.h"
#include "Multithreading.h"

#if DEBUG_TRANSFORMATION
#include <QDebug>
#include <QThreadPool>
#include <typeinfo>
#endif

/// Class template to apply a geometrical transformation on a set of vertices.
/** 
 *  This is an implementation that applies a transformation on every element of
 *  a MultiDimensionalVector with a multithreaded algorithm, in parallel.
 * 
 *  Instantiates SinglethreadedTransformation s on the VertexArray s constituting
 *  its operand and executes them in parallel.
 * 
 *  \tparam N Dimension of the vertices.
 *  \tparam P Dimension of the parameter space.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, unsigned P, typename NUM = double>
class MultithreadedTransformation: public TransformationImpl< N, P, NUM > {

public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, P, NUM >::value_storage_type value_storage_type;
    
    /// Execute the transform on a set of vertices.
    /**
     * @param operand A (multi-dimensional) array of vertices on which the transformation is performed
     * @return A (multi-dimensional) array of transformed vertices
     */
    virtual value_storage_type transform(const value_storage_type &x) const {    
        return Multithreading::mapped(x, functor_);
    }

private:

    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    MultithreadedTransformation(const VecMath::Rotation<N, NUM> &rotation,
                                const VecMath::Vector<N, NUM> &translation,
                                const VecMath::Vector<N, NUM> &scale): 
        TransformationImpl<N, P, NUM>(rotation, translation, scale), 
        functor_(rotation, translation, scale) { }
    
    void perform_transformation(const VecMath::Vector<N, NUM>& x, const VecMath::Vector<N, NUM>& xtrans);
    
    friend class TransformationFactory;
    friend class MultithreadedTransformation<N, P+1, NUM>;

    struct MapFunctor {

        typedef typename MultithreadedTransformation<N, P-1, NUM>::value_storage_type result_type;
        
        MapFunctor(const VecMath::Rotation<N, NUM> &rotation,
                   const VecMath::Vector<N, NUM> &translation,
                   const VecMath::Vector<N, NUM> &scale):
            matrix_(rotation), translation_(translation), scale_(scale) { }

        /** 
         *  Execute a transformation on a subpart of the MultithreadedTransformation's 
         *  operand
         *  
         *  \param arg The subpart
         */
        typename MultithreadedTransformation<N, P-1, NUM>::value_storage_type operator() (
            const VecMath::MultiDimensionalVector< VecMath::Vector<N, NUM>, P-1 > &arg
        ) {
            SinglethreadedTransformation<N, P-1, NUM> xform(matrix_, translation_, scale_);
            return xform.transform(arg);
        }

        VecMath::Rotation<N, NUM> matrix_;        ///< Rotation part of the Transformation.
        VecMath::Vector<N, NUM> translation_;   ///< Translation part of the Transformation.
        VecMath::Vector<N, NUM> scale_;         ///< Scaling part of the Transformation.

    } functor_;

};

/// Specialization for one-dimensional arrays.
/** 
 *  Executes the transformation on chunks of vertices that are chosen as big as
 *  possible for maximum usage of present processors and minimum overhead due to
 *  thread creation. \see Multithreading::partitionedMap().
 * 
 *  \tparam N Dimension of the vertices.
 *  \tparam NUM The numeric type of the \c Vector s.
 */
template <unsigned N, typename NUM>
class MultithreadedTransformation<N, 1, NUM>: public TransformationImpl< N, 1, NUM > {

public:

    /// Type for the storage of the function values on all grid points.
    typedef typename FunctionValueGrid< N, 1, NUM >::value_storage_type value_storage_type;
    
    /// Execute the transform on a set of vertices.
    /**
     * @param operand An array of vertices on which the transformation is performed
     * @return An array of transformed vertices
     */
    virtual value_storage_type transform(const value_storage_type &x) const {
        # if DEBUG_TRANSFORMATION
        qDebug() << "MultithreadedTransformationPolicy<" << N << ", " << 1 << ", " << typeid(NUM).name() << ">::transform("
                << x.toString().c_str()
                << ")";
        # endif
        return Multithreading::partitionedMapped(x, functor_);
    }

private:

    /// Initialize a Transformation with a Rotation, a translation Vector and a scaling Vector.
    /** \param rotation The amount the target is rotated.
     *  \param translation The translation Vector to add to all vertices.
     *  \param scale Scale the target, with independent values for each direction.
     */
    MultithreadedTransformation(const VecMath::Rotation<N, NUM> &rotation,
                                const VecMath::Vector<N, NUM> &translation,
                                const VecMath::Vector<N, NUM> &scale): 
        TransformationImpl<N, 1, NUM>(rotation, translation, scale), 
        functor_(rotation, translation, scale) { }

    void perform_transformation(const VecMath::Vector<N, NUM>& x, const VecMath::Vector<N, NUM>& xtrans);
    
    friend class TransformationFactory;
    friend class MultithreadedTransformation<N, 2, NUM>;

    struct MapFunctor {

        typedef VecMath::Vector<N, NUM> result_type;

        MapFunctor(const VecMath::Rotation<N, NUM> &rotation,
                const VecMath::Vector<N, NUM> &translation,
                const VecMath::Vector<N, NUM> &scale):
        matrix_(rotation), translation_(translation), scale_(scale) { }

        /** 
         *  Execute a transformation on a subpart of the MultithreadedTransformation's 
         *  operand
         *  
         *  \param arg The subpart
         */
        VecMath::Vector<N, NUM> operator() (const VecMath::Vector<N, NUM> &arg) const {
            return Transformation<N, 1, NUM>::perform(arg, matrix_, translation_, scale_);
        }

        VecMath::Matrix<N, NUM> matrix_;        ///< Rotation part of the Transformation.
        VecMath::Vector<N, NUM> translation_;   ///< Translation part of the Transformation.
        VecMath::Vector<N, NUM> scale_;         ///< Scaling part of the Transformation.

    } functor_;

};

#endif	/* MULTITHREADEDTRANSFORMATION_H */

