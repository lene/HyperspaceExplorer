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

#ifndef ROTATE_H
#define ROTATE_H

#include "Rotope.h"

#include "MultiDimensionalVector.h"

/// Base class for Rotate classes, providing the actual rotate() function
/** \tparam D Dimension of the vector space we're working in
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
template <unsigned D>
    class rotate_base: public VertexData<D> {

    public:
        /// Create a rotate_base object from an already existing object
        rotate_base(const VertexData<D> &v): VertexData<D>(v) { }

        /// Execute the rotate action of the previous object along axis \p d.
        void rotate(unsigned d);

    private:
        /// \todo rename check_argument()
        void checkRotationArguments(unsigned d);

        /// Execute a rotation on a VecMath::Vector
        VecMath::Vector<D> rotate_vertex(const VecMath::Vector<D> &, double,
                                         unsigned, unsigned);
        /// Execute the rotate action on a line (generating a circle)
        void rotate_line(unsigned);
        /// Execute the rotate action on a triangle (generating a cone)
        void rotate_triangle(unsigned, const VecMath::MultiDimensionalVector<unsigned, 1> &);
        /// Execute the rotate action on a rectangle (generating a cylinder)
        void rotate_quad(unsigned, const VecMath::MultiDimensionalVector<unsigned, 1> &);
        /// Execute the rotate action on a polygon
        void rotate_polygon(unsigned, const VecMath::MultiDimensionalVector<unsigned, 1> &);
    };

/// A class template to execute rotate actions on an object
/** The vertex array of the object is rotated into a set of consecutive
 *  dimensions.
 *
 *  As I find the concept hard to explain in words, let me give a few examples
 *  to illustrate the idea:
 *  \code Extrude<4, 0, 0> line; \endcode
 *  A line in four-space. A point is extruded along dimension 0 ( \p x ).
 *  \code Rotate<4, 1, 1> circle(line); \endcode
 *  The line along \p x is rotated into the \p y - dimension resulting in a
 *  circle in the \p xy -plane.
 *  \code Rotate<4, 2, 2> sphere(circle); \endcode
 *  Create a sphere from a circle by rotating along the \p z axis.
 *  \code Rotate<4, 1, 2> also_a_sphere(line); \endcode
 *  Create another sphere from a line by rotating it into the dimensions 1 to
 *  2, ie. along \p y and \p z, in one operation.
 *  \code  Extrude<4, 0, 1> square;
 * Rotate<4, 2, 2> cylinder(square); \endcode
 *  A cylinder is created by rotating a square along the \p z axis. Alternately
 *  you could have extruded a circle.
 *  \code Rotate<4, 1, 3> glome(line); \endcode
 *  A four-dimensional sphere, also known as glome, is created by rotating a
 *  line three times.
 *
 *  \tparam D Dimension of the vector space we're working in
 *  \tparam Dmin First of the set of dimensions being rotated into
 *  \tparam Dmax Last of the set of dimensions being rotated into
 *
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
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
        Rotate(const VertexData<D> &v): Rotate<D, Dmin, Dmax-1>(v) {
            rotate_base<D>::rotate(Dmax);
        }

    };

/// Specialization of Rotate<D,Dmin,Dmax> to end recursion
/** \tparam D Dimension of the vector space we're working in
 *  \tparam Dmin Dimension being rotated into
 *
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
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
        Rotate(const VertexData<D> &v): rotate_base<D>(v) {
            rotate_base<D>::rotate(Dmin);
        }

    };

/** We must implement the following algorithm:
 *
 *  For every (\p d - 2)-surface realm in the (\p d - 1)-dimensional object:
 *      generate a new (\p d - 1)-dimensional object from the (\p d - 2)-surface
 *      realm and its rotated image
 *  Repeat until the rotation is full (180 degrees are enough)
 *
 *  \param d The direction into which is extruded. The rotation takes place in
 *           the ( \p d, \p d-1 )-plane.
 */
template <unsigned D> void rotate_base<D>::rotate(unsigned d) {
#   if DEBUG_ROTOPES
        SingletonLog::Instance().log(__PRETTY_FUNCTION__);
#   endif

    checkRotationArguments(d);

    std::vector<VecMath::Vector<D> > Xold = VertexData<D>::raw_vertices();
    for (unsigned i = 1; i <= RotopeInterface::_numSegments; ++i) {
        double rot = 1.*i*M_PI/RotopeInterface::_numSegments;
        for (typename std::vector<VecMath::Vector<D> >::iterator j = Xold.begin();
             j != Xold.end(); ++j) {
                 VertexData<D>::raw_vertices().push_back(rotate_vertex(*j, rot, d, d-1));
        }
    }

    VertexData<D>::dimension()++;   //  object is now one dimension higher

    VertexData<D>::realm() = VertexData<D>::realm().rotated(RotopeInterface::_numSegments, Xold.size());
}

template <unsigned D> void rotate_base<D>::checkRotationArguments(unsigned d) {
    if (d >= D) {
        throw std::invalid_argument(
           "rotate_base::rotate() called on a higher dimension"
           " than the vector space allows");
    }
    if (d == 0) {
        throw std::invalid_argument(
                "rotate_base::rotate() must be called on an object of dimension"
                " at least 1");
    }
}

/** \param v The vertex to be rotated about \p rot radians
 *  \param rot Angle of the rotation, in radians
 *  \param new_axis Direction to be rotated into
 *  \param old_axis Axis to be rotated away from
 */
template <unsigned D> VecMath::Vector<D> rotate_base<D>::rotate_vertex(
        const VecMath::Vector<D> &v, double rot,
        unsigned new_axis, unsigned old_axis) {
#   if DEBUG_ROTOPES >= 2
        SingletonLog::Instance().log(__PRETTY_FUNCTION__);
#   endif
    VecMath::Vector<D> v_new(v);
    v_new[new_axis] = v_new[old_axis]*sin(rot);
    v_new[old_axis] *= cos(rot);
    return v_new;
}

/** \param d Dimension to be rotated into - the vertices are rotated away from
 *           axis \p d-1
 */
template <unsigned D> void rotate_base<D>::rotate_line(unsigned d) {
#   if DEBUG_ROTOPES
        SingletonLog::Instance().log(__PRETTY_FUNCTION__);
#   endif
    VecMath::MultiDimensionalVector<unsigned, 1> new_surface; // defines the disk
    new_surface.push_back(0);
    VertexData<D>::raw_vertices().pop_back();
    for (unsigned i = 1; i <= RotopeInterface::_numSegments; ++i) {
        double rot = 2.*i*M_PI/RotopeInterface::_numSegments;
        VecMath::Vector<D> current = VertexData<D>::raw_vertices()[0];
        VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                            d, d-1);
        VertexData<D>::raw_vertices().push_back(rotated_current);
        new_surface.push_back(VertexData<D>::raw_vertices().size()-1);
    }
    VertexData<D>::surface().push_back(new_surface);
}

/** \param d Dimension to be rotated into - the vertices are rotated away from
 *           axis \p d-1
 *  \param current_surface The triangular surface to be extruded into a cone
 */
template <unsigned D> void rotate_base<D>::rotate_triangle(
        unsigned d, const VecMath::MultiDimensionalVector<unsigned, 1> &current_surface) {

#   if DEBUG_ROTOPES
        SingletonLog::Instance().log(__PRETTY_FUNCTION__);
#   endif
    VecMath::MultiDimensionalVector<unsigned, 1> new_surface; //  defines the first cap
    new_surface.push_back(current_surface[0]);

    unsigned old_current = 0;
    /** Rotate the current surface through 360 degrees.
     *  \bug Instead of rotating it through 180 degrees and using every vertex,
     *       we only take the vertices on one side of the rotation axis.
     */
    for (unsigned i = 1; i <= RotopeInterface::_numSegments; ++i) {

        double rot = 2.*i*M_PI/RotopeInterface::_numSegments;

        unsigned cur_index = current_surface[0],
                 next_index = current_surface[2];

            VecMath::Vector<D> current = VertexData<D>::raw_vertices()[cur_index];
            VecMath::Vector<D> next = VertexData<D>::raw_vertices()[next_index];
            VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                               d, d-2);

            /// New vertex generated by rotation about angle \p rot
            VertexData<D>::raw_vertices().push_back(rotated_current);

            /// Add new vertex to cap
            new_surface.push_back(VertexData<D>::raw_vertices().size()-1);

            /// New triangular surface (current, next, rotated_current)
            VertexData<D>::addSurface(old_current, next_index,
                                       VertexData<D>::raw_vertices().size()-1);

            old_current = VertexData<D>::raw_vertices().size()-1;
    }
    /// Add the new circular surface ("cap") generated by the rotation
    VertexData<D>::addSurface(new_surface);
}

/** \param d Dimension to be rotated into - the vertices are rotated away from
 *           axis \p d-1
 *  \param current_surface The rectangular surface to be extruded into a cylinder
 */
template <unsigned D> void rotate_base<D>::rotate_quad(
        unsigned d, const VecMath::MultiDimensionalVector<unsigned, 1> &current_surface) {
#   if DEBUG_ROTOPES
        SingletonLog::Instance().log(__PRETTY_FUNCTION__);
#   endif
    unsigned old_current = current_surface[0];  //  saved index to current vertex
    unsigned old_next = current_surface[1];     //  saved index to next vertex

    VecMath::MultiDimensionalVector<unsigned, 1> bottom;       //  defines the first ("bottom") cap
    /// Save first vertex of "bottom" cap.
    bottom.push_back(current_surface[0]);
    /** Save first vertex of "top" cap.
     *  This relies on quads being defined in the order, 0, 1, 2, 3, where
     *  vertex 2 and 3 lie in the direction of the extrusion.
     */
    VecMath::MultiDimensionalVector<unsigned, 1> top;          //  defines the second ("top") cap
    top.push_back(current_surface[2]);

    /** Rotate the current surface through 360 degrees.
     *  \bug Instead of rotating it through 180 degrees and using every vertex,
     *       we only take the vertices on one side of the rotation axis. Taking
     *       the indexes on the other side too would be an indexing nightmare.
     */
    for (unsigned i = 1; i <= RotopeInterface::_numSegments; ++i) {

        double rot = 2.*i*M_PI/RotopeInterface::_numSegments;

        unsigned cur_index = current_surface[0];
        unsigned next_index = current_surface[1];

        VecMath::Vector<D> current = VertexData<D>::raw_vertices()[cur_index];
        VecMath::Vector<D> next = VertexData<D>::raw_vertices()[next_index];

        /// New vertices generated by rotation about angle \p rot.
        VecMath::Vector<D> rotated_current = rotate_vertex(current, rot, d, d-1);
        VecMath::Vector<D> rotated_next = rotate_vertex(next, rot, d, d-1);

        VertexData<D>::raw_vertices().push_back(rotated_current);
        VertexData<D>::raw_vertices().push_back(rotated_next);

        /// Add quad surface: (current, next, rotated_next, rotated_current).
        VertexData<D>::addSurface(old_current, old_next,
                                   VertexData<D>::raw_vertices().size()-1,
                                   VertexData<D>::raw_vertices().size()-2);

        /// Update vertices from which to draw the next surface.
        old_current = VertexData<D>::raw_vertices().size()-2;
        old_next = VertexData<D>::raw_vertices().size()-1;

        /// Add rotated vertex to bottom cap and rotated_next to top cap.
        bottom.push_back(VertexData<D>::raw_vertices().size()-2);
        top.push_back(VertexData<D>::raw_vertices().size()-1);
    }
    /// Add the new circular surfaces ("caps") generated by the rotation.
    VertexData<D>::addSurface(bottom);
    VertexData<D>::addSurface(top);
}

/** \param d Dimension to be rotated into - the vertices are rotated away from
 *           axis \p d-1
 *  \param current_surface The polygonal surface to be extruded into a sphere
 */
template <unsigned D> void rotate_base<D>::rotate_polygon(
        unsigned d, const VecMath::MultiDimensionalVector<unsigned, 1> &current_surface) {
#   if DEBUG_ROTOPES
        SingletonLog::Instance().log(__PRETTY_FUNCTION__);
#   endif

    unsigned offset = 0;

    VertexData<D>::raw_vertices().push_back(VertexData<D>::raw_vertices()[current_surface[0]]);

    /// Rotate the current surface through 180 degrees along its central axis
    for (unsigned i = 1; i <= (RotopeInterface::_numSegments+1)/2; ++i) {

        double rot = 1.*i*M_PI/((RotopeInterface::_numSegments+1)/2);

        for (unsigned j = 0; j < current_surface.size(); j++) {

            unsigned cur_index = j+offset;

            unsigned next_index = j+1+offset;

            VecMath::Vector<D> current = VertexData<D>::raw_vertices()[cur_index-offset];
            VecMath::Vector<D> next = VertexData<D>::raw_vertices()[next_index-offset];
            VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                               d, d-1);
            VecMath::Vector<D> rotated_next = rotate_vertex(next, rot, d, d-1);

            /// New quad surface (current, next, rotated_next, rotated_current)
            VertexData<D>::raw_vertices().push_back(rotated_next);
#           if DEBUG_ROTOPES >= 2
            std::cerr << "j: " << j << "offset: " << offset
                      << " cur_index: " << cur_index << " next_index: " << next_index
                      << " size: " << VertexData<D>::raw_vertices().size() << "\n";
#           endif
            VertexData<D>::addSurface(cur_index, next_index,
                                       VertexData<D>::raw_vertices().size()-1,
                                       VertexData<D>::raw_vertices().size()-2);

        }
        /// Update vertices from which to draw the next surface
        offset += current_surface.size();
    }
}

#endif
