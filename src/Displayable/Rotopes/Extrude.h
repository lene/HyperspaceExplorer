/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef EXTRUSION_H
#define EXTRUSION_H

#include "Rotope.h"

/// Base class for Extrude classes, providing the actual extrude() function
/** \tparam D Dimension of the vector space we're working in
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <lene.preuss@gmail.com>
 */
template <unsigned D>
    class extrude_base: public VertexData<D> {

    public:

        /// Create an empty extrude_base object
        extrude_base(): VertexData<D>() { }
        /// Create an extrude_base object from an already existing object
        extrude_base(const VertexData<D> &v): VertexData<D>(v) { }

        /// Extrudes an object along a given dimension
        /** For each point in the vertex array, a copy is made and shifted along the
        *  \p d axis. Thus, a point becomes a line when extruded along axis 0, a line
        *  becomes a square when extruded along axis 1, and so on. A circle becomes a
        *  cylinder when extruded along axis 2, and similarly with all kinds of
        *  objects. You get the idea. \see Extrude for more examples.
        *
        *  \param d The new dimension into which the object is extruded
        */
        void extrude(unsigned d);

    };

/// A class template to execute extrusion actions on an object
/** The vertex array of the object is extrudeded into a set of consecutive
 *  dimensions.
 *
 *  As I find the concept hard to explain in words, let me give a few examples
 *  to illustrate the idea:
 *  \code Extrude<4, 0, 0> line; \endcode
 *  A line in four-space. A point is extruded along dimension 0 (\p x ).
 *  \code Extrude<4, 0, 1> square; \endcode
 *  A point is extruded into two dimensions, giving a square.
 *  \code Extrude<4, 2, 2> cube; \endcode
 *  The square is extruded into the third dimension to a cube.
 *  \code
 *  Taper<4, 1, 1> triangle(line);
 *  Extrude<4, 2, 2> prism;
 *  \endcode
 *  A line is tapered into a triangle, and then extruded to become a prism.
 *  \code Extrude<4, 0, 3> tesseract; \endcode
 *  Extruding a point i four dimensions gives a hypercube or tesseract.
 *
 *  \tparam D Dimension of the vector space we're working in
 *  \tparam Dmin First of the set of dimensions being tapered into
 *  \tparam Dmax Last of the set of dimensions being tapered into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <lene.preuss@gmail.com>
 */
template <unsigned D, unsigned Dmin, unsigned Dmax>
    class Extrude: public Extrude<D, Dmin, Dmax-1> {
    public:
        /// Create an Extrude object from a point
        /** \todo Guard against bad template parameters:
         *        - Dmin >= Dmax
         *        - Dmin or Dmax >= D
         *        - Dmin or Dmax >= vertex_data::_dimension
         *        - vertex_data::_dimension == 0
         */
        Extrude(): Extrude<D, Dmin, Dmax-1>() {
            extrude_base<D>::extrude(Dmax);
        }

        /// Create an Extrude object from an already existing object
        /** \todo Guard against bad template parameters:
         *        - Dmin >= Dmax
         *        - Dmin or Dmax >= D
         *        - Dmin or Dmax >= vertex_data::_dimension
         *        - vertex_data::_dimension == 0
         */
        Extrude(const VertexData<D> &v): Extrude<D, Dmin, Dmax-1>(v) {
            extrude_base<D>::extrude(Dmax);
        }
    };

/// Specialization of Extrude<D,Dmin,Dmax> to end recursion
/** \tparam D Dimension of the vector space we're working in
 *  \tparam Dmin Dimension being tapered into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <lene.preuss@gmail.com>
 */
template <unsigned D, unsigned Dmin>
    class Extrude<D, Dmin, Dmin>: public extrude_base<D> {
    public:
        /// Create an Extrude object from a point
        /** \todo Guard against bad template parameters:
         *        - Dmin >= Dmax
         *        - Dmin or Dmax >= D
         *        - Dmin or Dmax >= vertex_data::_dimension
         */
        Extrude(): extrude_base<D>() {
            extrude_base<D>::extrude(Dmin);
        }

        /// Create an Extrude object from an already existing object
        /** \todo Guard against bad template parameters:
         *        - Dmin >= D
         *        - Dmin >= vertex_data::_dimension
         */
        Extrude(const VertexData<D> &v): extrude_base<D>(v) {
            extrude_base<D>::extrude(Dmin);
        }
    };


template <unsigned D> void extrude_base<D>::extrude(unsigned d) {
    if (d >= D) {
        throw std::logic_error(
           "extrude_base::extrude() called on a higher dimension"
           " than the vector space allows");
    }

    VecMath::Vector<D> x;
    x[d] = 1.;
    unsigned xsize = VertexData<D>::raw_vertices().size();
    for (unsigned i = 0; i < xsize; ++i) {
        VertexData<D>::raw_vertices()[i] -= x;
        VertexData<D>::raw_vertices().push_back(VertexData<D>::raw_vertices()[i]+x*2.);
    }

    if (d == 0) VertexData<D>::realm() = Realm(0);

    VertexData<D>::realm() = VertexData<D>::realm().extruded(xsize);

    VertexData<D>::dimension()++;   //  object is now one dimension higher
}

#endif
