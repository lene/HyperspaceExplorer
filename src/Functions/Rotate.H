#ifndef ROTATE_H
#define ROTATE_H

#include "Rotope.H"

/// Base class for Rotate classes, providing the actual rotate() function
/** \param D Dimension of the vector space we're working in
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D>
    class rotate_base: public vertex_data<D> {

        public:
            /// Create a rotate_base object from an already existing object
            rotate_base(const vertex_data<D> &v):
                vertex_data<D>(v) { }

            /// Execute the rotate action of the previous object along axis \p d.
            void rotate(unsigned d);
    };

/// A class template to execute rotate actions on an object
/** The vertex array of the object is rotated into a set of consecutive
 *  dimensions.
 *
 *  As I find the concept hard to explain in words, let me give a few examples
 *  to illustrate the idea:
 *  \code Extrude<4, 0, 0> line; \endcode
 *  A line in four-space. A point is extruded along dimension 0 (\p x ).
 *  \code Rotate<4, 1, 1> triangle(line); \endcode
 *  An equilateral triangle in the \p xy -plane. The line along \p x is rotated
 *  into the \p y dimension.
 *  \code Rotate<4, 2, 2> tetrahedron1(triangle); \endcode
 *  Create a tetrahedron from an equilateral triangle by rotateing along the \p z
 *  axis.
 *  \code Rotate<4, 1, 2> tetrahedron2(line); \endcode
 *  Create another tetrahedron from a line by rotateing it into the dimensions 1
 *  to 2, ie. along \p y and \p z
 *  \code Extrude<4, 0, 1> square;
 * Rotate<4, 2, 2> pyramid(square); \endcode
 *  A four-sided pyramid is created by rotateing a square along the \p z axis.
 *  \code Rotate<4, 1, 3> pentachoron(line); \endcode
 *  A four-dimensional simplex, a pentachoron, is created by rotateing a line
 *  three times.
 *
 *  \param D Dimension of the vector space we're working in
 *  \param Dmin First of the set of dimensions being rotated into
 *  \param Dmax Last of the set of dimensions being rotated into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D, unsigned Dmin, unsigned Dmax>
    class Rotate: public Rotate<D, Dmin, Dmax-1> {
        public:
            /// Create a Rotate object from an already existing object
            /** \todo Guard against bad template parameters:
             *        - Dmin >= Dmax
             *        - Dmin or Dmax >= D
             *        - Dmin or Dmax >= vertex_data::_dimension
             *        - vertex_data::_dimension == 0
             */
            Rotate(const vertex_data<D> &v): Rotate<D, Dmin, Dmax-1>(v) {
                rotate_base<D>::rotate(Dmax);
            }
    };

/// Specialization of Rotate<D,Dmin,Dmax> to end recursion
/** \param D Dimension of the vector space we're working in
 *  \param Dmin Dimension being rotated into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D, unsigned Dmin>
    class Rotate<D, Dmin, Dmin>: public rotate_base<D> {
        public:
            /// Create a Rotate object from an already existing object
            /** \todo Guard against bad template parameters:
             *        - Dmin  >= D
             *        - Dmin  >= vertex_data::_dimension
             *        - vertex_data::_dimension == 0
             */
            Rotate(const vertex_data<D> &v): rotate_base<D>(v) {
                rotate_base<D>::rotate(Dmin);
            }
    };

template <unsigned D> void rotate_base<D>::rotate(unsigned d) {
    throw NotYetImplementedException("rotate_base<D>::rotate()");
}

#endif
