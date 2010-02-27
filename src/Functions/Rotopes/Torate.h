#ifndef TORATE_H
#define TORATE_H

#include "Rotope.h"

/// Base class for Torate classes, providing the actual torate() function
/** \param D Dimension of the vector space we're working in
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <lene.preuss@gmail.com>
 */
template <unsigned D>
    class torate_base: public vertex_data<D> {

        public:
            /// Create a torate_base object from an already existing object
            torate_base(const vertex_data<D> &v):
                vertex_data<D>(v) { }

            /// Execute the torate action of the previous object along axis \p d.
            void torate(unsigned d);
    };

/// A class template to execute torate actions on an object
/** The vertex array of the object is torateed into a set of consecutive
 *  dimensions.
 *
 *  As I find the concept hard to explain in words, let me give a few examples
 *  to illustrate the idea:
 *  \code Extrude<4, 0, 0> line; \endcode
 *  A line in four-space. A point is extruded along dimension 0 (\p x ).
 *  \code Torate<4, 1, 1> triangle(line); \endcode
 *  An equilateral triangle in the \p xy -plane. The line along \p x is torateed
 *  into the \p y dimension.
 *  \code Torate<4, 2, 2> tetrahedron1(triangle); \endcode
 *  Create a tetrahedron from an equilateral triangle by torateing along the \p z
 *  axis.
 *  \code Torate<4, 1, 2> tetrahedron2(line); \endcode
 *  Create another tetrahedron from a line by torateing it into the dimensions 1
 *  to 2, ie. along \p y and \p z
 *  \code Extrude<4, 0, 1> square;
 * Torate<4, 2, 2> pyramid(square); \endcode
 *  A four-sided pyramid is created by torateing a square along the \p z axis.
 *  \code Torate<4, 1, 3> pentachoron(line); \endcode
 *  A four-dimensional simplex, a pentachoron, is created by torateing a line
 *  three times.
 *
 *  \param D Dimension of the vector space we're working in
 *  \param Dmin First of the set of dimensions being torateed into
 *  \param Dmax Last of the set of dimensions being torateed into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <lene.preuss@gmail.com>
 */
template <unsigned D, unsigned Dmin, unsigned Dmax>
    class Torate: public Torate<D, Dmin, Dmax-1> {
        public:
            /// Create a Torate object from an already existing object
            /** \todo Guard against bad template parameters:
             *        - Dmin >= Dmax
             *        - Dmin or Dmax >= D
             *        - Dmin or Dmax >= vertex_data::_dimension
             *        - vertex_data::_dimension == 0
             */
            Torate(const vertex_data<D> &v): Torate<D, Dmin, Dmax-1>(v) {
                torate_base<D>::torate(Dmax);
            }
    };

/// Specialization of Torate<D,Dmin,Dmax> to end recursion
/** \param D Dimension of the vector space we're working in
 *  \param Dmin Dimension being torateed into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <lene.preuss@gmail.com>
 */
template <unsigned D, unsigned Dmin>
    class Torate<D, Dmin, Dmin>: public torate_base<D> {
        public:
            /// Create a Torate object from an already existing object
            /** \todo Guard against bad template parameters:
             *        - Dmin  >= D
             *        - Dmin  >= vertex_data::_dimension
             *        - vertex_data::_dimension == 0
             */
            Torate(const vertex_data<D> &v): torate_base<D>(v) {
                torate_base<D>::torate(Dmin);
            }
    };

template <unsigned D> void torate_base<D>::torate(unsigned) {
    throw NotYetImplementedException("torate_base<D>::torate()");
}

#endif
