/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2009  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Matrix.h"
#include "Rotation.h"

#include <QtConcurrentMap>

/// Transforms Vertices or collections thereof according to a Rotation and a translation Vector.
/** The rotation Matrix and translation Vector are stored as class members, thus
 *  the name copy_member_transform.
 *
 *  operator() is called recursively on collections (works only for std::vector
 *  now) until the transformation has been called on every element.
 *
 * \tparam Type Class the transform is performed upon. Must be either
 *    VecMath::Vector, or a std::vector of objects (which in turn can be either
 *    Vector or another, potentially recursive, vector).
 * \tparam N Dimension of the vector space in which the transform takes place.
 */
template <typename Type, unsigned N> class copy_member_transform {
  public:

    /// Initializes the transform.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The object (vertex or collection of vertices) to be transformed.
     */
    copy_member_transform(VecMath::Matrix<N> &Rot, 
                          const VecMath::Vector<N> &T,
                          const VecMath::Vector<N> &scale,
                          const Type &X):
      m_Rot(Rot), m_T(T), m_scale(scale), m_X(X) { }

    /// Executes the transform.
    /** This is not defined for the generic case, but must be specialized for
     *  vertices and collections of vertices separately.
     */
    void operator() (Type &Xtrans);

  private:
    VecMath::Matrix<N> &m_Rot;          ///< Rotation to be executed.
    const VecMath::Vector<N> &m_T;      ///< Translation to be executed.
    const VecMath::Vector<N> &m_scale;  ///< Scaling to be executed.
    const Type &m_X;                    ///< Object to be transformed.
};

/// Specialization for a transform on a std::vector of objects
/** \tparam Type Class the transform is performed upon. Must be either
 *    VecMath::Vector, or a std::vector of objects (which in turn can be either
 *    Vector or another, potentially recursive, vector).
 *  \tparam N Dimension of the vector space in which the transform takes place.
 */
template <typename Type, unsigned N> class copy_member_transform< std::vector<Type>, N > {
  public:

    /// Initializes the transform.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The collection of vertices to be transformed.
     */
    copy_member_transform(VecMath::Matrix<N> &Rot, 
                          const VecMath::Vector<N> &T,
                          const VecMath::Vector<N> &scale,
                          const std::vector<Type> &X):
      m_Rot(Rot), m_T(T), m_scale(scale), m_X(X) { }

    /// Static convenience function easing the initialization of the transformation.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The collection of vertices to be transformed.
     *  \param Xtrans The transformed vertices.
     */
    static void xform(VecMath::Matrix<N> &Rot,
      const VecMath::Vector<N> &T,
      const VecMath::Vector<N> &scale,
      const std::vector<Type> &X, std::vector<Type> &Xtrans) {
      copy_member_transform<std::vector<Type>, N> trans(Rot, T, scale, X);
      trans(Xtrans);
    }

    /// Executes the transform for every vertex in the collection.
    /** For each member of the collection \p m_X, a copy_member_transform is
     *  recursively created and executed.
     *  \param Xtrans The collection holding the transformed vertices.
     */
    void operator() (std::vector<Type> &Xtrans) {
      typename std::vector<Type>::const_iterator i = m_X.begin();
      typename std::vector<Type>::iterator j = Xtrans.begin();
      while(i != m_X.end() && j != Xtrans.end()) {
        copy_member_transform<Type, N>::xform(m_Rot, m_T, m_scale, *i, *j);
        ++i; ++j;
      }
      // QtConcurrent::map(X, copy_member_transform<Type, N>::xform);
      }

  private:
    VecMath::Matrix<N> &m_Rot;      ///< Rotation to be executed.
    const VecMath::Vector<N> &m_T;  ///< Translation to be executed.
    const VecMath::Vector<N> &m_scale;  ///< Scaling to be executed.
    const std::vector<Type> &m_X;   ///< Collection of objects to be transformed.
};

/// Specialization for a transform on a single VecMath::Vector
/** \tparam N Dimension of the vector space in which the transform takes place.
 */
template <unsigned N> class copy_member_transform< VecMath::Vector<N>, N > {
  public:

    /// Initializes the transform.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The collection of vertices to be transformed.
     */
    copy_member_transform(VecMath::Matrix<N> &Rot, 
                          const VecMath::Vector<N> &T,
                          const VecMath::Vector<N> &scale,
                          const VecMath::Vector<N> &X):
      m_Rot(Rot), m_T(T), m_scale(scale), m_X(X) { }

    /// Static convenience function easing the initialization of the transformation.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The vertex to be transformed.
     *  \param Xtrans The transformed vertex.
     */
    static void xform(VecMath::Matrix<N> &Rot, 
                      const VecMath::Vector<N> &T,
                      const VecMath::Vector<N> &scale,
                      const VecMath::Vector<N> &X,
                      VecMath::Vector<N> &Xtrans) {
      copy_member_transform<VecMath::Vector<N>, N> trans(Rot, T, scale, X);
      trans(Xtrans);
    }

    /// Executes the transform on the vertex.
    /** \param Xtrans The transformed vertex.
     */
    void operator() (VecMath::Vector<N> &Xtrans) {
#warning "copy_member_transform::operator() To do: make operation equal to SimpleTransformationPolicy::transform()"
      Xtrans = VecMath::scale(m_Rot*(m_X+m_T), m_scale);
    }

  private:
    VecMath::Matrix<N> &m_Rot;      ///< Rotation to be executed.
    const VecMath::Vector<N> &m_T;  ///< Translation to be executed.
    const VecMath::Vector<N> &m_scale;  ///< Scaling to be executed.
    const VecMath::Vector<N> &m_X;  ///< Vertex to be transformed.
};


/// An alternative transformation class template, taking the arguments as function parameters instead of member variables
/** \tparam Type Class the transform is performed upon. Must be either
 *    VecMath::Vector, or a std::vector of objects (which in turn can be either
 *    Vector or another, potentially recursive, vector).
 * \tparam N Dimension of the vector space in which the transform takes place.
 */
template <typename Type, unsigned N> class call_parameters_transform {
  public:

    /// Executes the transform on the vertex.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The vertex to be transformed.
     *  \param Xtrans The transformed vertex.
     */
    void operator() (VecMath::Matrix<N> &Rot,
                     const VecMath::Vector<N> &T,
                     const Type &X, Type &Xtrans);
};

/// Specialization for a transform on a std::vector of objects
/** \tparam Type Class the transform is performed upon. Must be either
 *    VecMath::Vector, or a std::vector of objects (which in turn can be either
 *    Vector or another, potentially recursive, vector).
 * \tparam N Dimension of the vector space in which the transform takes place.
 */
template <typename Type, unsigned N> class call_parameters_transform< std::vector<Type>, N > {
  public:
    /// Static convenience function easing the initialization of the transformation.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The vertex to be transformed.
     *  \param Xtrans The transformed vertex.
     */
    static void xform(VecMath::Matrix<N> &Rot,
                      const VecMath::Vector<N> &T,
                      const std::vector<Type> &X,
                      std::vector<Type> &Xtrans) {
        static call_parameters_transform<std::vector<Type>, N> trans;
        trans(Rot, T, X, Xtrans);
    }

    /// Executes the transform on the vertex.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The vertex to be transformed.
     *  \param Xtrans The transformed vertex.
     */
    void operator() (VecMath::Matrix<N> &Rot,
                     const VecMath::Vector<N> &T,
                     const std::vector<Type> &X, std::vector<Type> &Xtrans) {

        typename std::vector<Type>::const_iterator i = X.begin();
        typename std::vector<Type>::iterator j = Xtrans.begin();
        while(i != X.end() && j != Xtrans.end()) {
          call_parameters_transform<Type, N>::xform(Rot, T, *i, *j);
          ++i; ++j;
        }
      }

   //   QtConcurrent::map(X, transform<Type, N>::xform);
};

/// Specialization for a transform on a single VecMath::Vector
/** \tparam N Dimension of the vector space in which the transform takes place.
 */
template <unsigned N> class call_parameters_transform< VecMath::Vector<N>, N > {
  public:

    /// Static convenience function easing the initialization of the transformation.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The vertex to be transformed.
     *  \param Xtrans The transformed vertex.
     */
    static void xform(VecMath::Matrix<N> &Rot,
                                          const VecMath::Vector<N> &T,
                                          const VecMath::Vector<N> &X, VecMath::Vector<N> &Xtrans) {
        static call_parameters_transform<VecMath::Vector<N>, N> trans;
        trans(Rot, T, X, Xtrans);
    }

    /// Executes the transform on the vertex.
    /** \param Rot The rotation Matrix to be executed.
     *  \param T The Translation to be applied.
     *  \param X The vertex to be transformed.
     *  \param Xtrans The transformed vertex.
     */
    void operator() (VecMath::Matrix<N> &Rot, const VecMath::Vector<N> &T,
                     const VecMath::Vector<N> &X, VecMath::Vector<N> &Xtrans) {
#warning "call_parameters_transform::operator() To do: add scaling, make operation equal to SimpleTransformationPolicy::transform()"
        Xtrans = (Rot*X)+T;
    }
};


/// Default transform class - Okay, this is a hack, because i can't decide yet which transform is better suited
/** \todo Make the transformation to be used a policy to the Function class.
 *  \tparam Type Class the transform is performed upon. Must be either
 *    VecMath::Vector, or a std::vector of objects (which in turn can be either
 *    Vector or another, potentially recursive, vector).
 *  \tparam N Dimension of the vector space in which the transform takes place.
 */
template <typename Type, unsigned N> class transform: public copy_member_transform<Type, N> {
};

#endif // TRANSFORM_H
