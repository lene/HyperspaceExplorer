/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2009-2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef TORATE_H
#define TORATE_H

#include "Rotope.h"

/// Base class for Torate classes, providing the actual torate() function
/** \tparam D Dimension of the vector space we're working in
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
template <unsigned D>
    class torate_base: public VertexData<D> {

    public:
        /// Create a torate_base object from an already existing object
        torate_base(const VertexData<D> &v):
            VertexData<D>(v) { }

        /// Execute the torate action of the previous object along axis \p d.
        void torate(unsigned d);

        /// \todo regenerate after setting _numSegments
        virtual void setRotationSegments(unsigned numSegments) {
            std::cerr << "torate_base::setRotationSegments(" << numSegments << ")\n";
            _numSegments = numSegments;
        }
    private:
        /// How many segments to use to approximate a circle
        unsigned _numSegments;
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
 *  \tparam D Dimension of the vector space we're working in
 *  \tparam Dmin First of the set of dimensions being torateed into
 *  \tparam Dmax Last of the set of dimensions being torateed into
 *
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
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
            Torate(const VertexData<D> &v): Torate<D, Dmin, Dmax-1>(v) {
                torate_base<D>::torate(Dmax);
            }
    };

/// Specialization of Torate<D,Dmin,Dmax> to end recursion
/** \tparam D Dimension of the vector space we're working in
 *  \tparam Dmin Dimension being torateed into
 *
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
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
            Torate(const VertexData<D> &v): torate_base<D>(v) {
                torate_base<D>::torate(Dmin);
            }
    };

template <unsigned D> void torate_base<D>::torate(unsigned) {
    throw NotYetImplementedException("torate_base<D>::torate()");
}

#endif
