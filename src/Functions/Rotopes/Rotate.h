#ifndef ROTATE_H
#define ROTATE_H

#include "Rotope.h"

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
                vertex_data<D>(v), _numSegments(4) { }

            /// Execute the rotate action of the previous object along axis \p d.
            void rotate(unsigned d);

        private:
            /// Execute a rotation on a VecMath::Vector
            VecMath::Vector<D> rotate_vertex(const VecMath::Vector<D> &, double,
                                             unsigned, unsigned);
            /// Execute the rotate action on a line (generating a circle)
            void rotate_line(unsigned);
            /// Execute the rotate action on a triangle (generating a cone)
            void rotate_triangle(unsigned, const uintvec<1> &);
            /// Execute the rotate action on a rectangle (generating a cylinder)
            void rotate_quad(unsigned, const uintvec<1> &);
            /// Execute the rotate action on a polygon
            void rotate_polygon(unsigned, const uintvec<1> &);

            /// How many segments to use to approximate a circle
            unsigned _numSegments;
    };

/// A class template to execute rotate actions on an object
/** The vertex array of the object is rotated into a set of consecutive
 *  dimensions.
 *
 *  As I find the concept hard to explain in words, let me give a few examples
 *  to illustrate the idea:
 *  \code Extrude<4, 0, 0> line; \endcode
 *  A line in four-space. A point is extruded along dimension 0 (\p x ).
 *  \code Rotate<4, 1, 1> circle(line); \endcode
 *  A circle in the \p xy -plane. The line along \p x is rotated into the \p y
 *  dimension.
 *  \code Rotate<4, 2, 2> sphere(circle); \endcode
 *  Create a sphere from a circle by rotating along the \p z axis.
 *  \code Rotate<4, 1, 2> sphere2(line); \endcode
 *  Create another sphere from a line by rotating it into the dimensions 1 to
 *  2, ie. along \p y and \p z
 *  \code Extrude<4, 0, 1> square;
 *  Rotate<4, 2, 2> cylinder(square); \endcode
 *  A cylinder is created by rotateing a square along the \p z axis. Alternately
 *  you could have extruded a circle.
 *  \code Rotate<4, 1, 3> glome(line); \endcode
 *  A four-dimensional sphere, also known as glome, is created by rotating a
 *  line three times.
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
    if (d >= D) {
        throw std::logic_error(
           "rotate_base::rotate() called on a higher dimension"
           " than the vector space allows");
    }
    if (d == 0) {
        throw std::logic_error(
                "rotate_base::rotate() must be called on an object of dimension"
                " at least 1");
    }

    std::vector<VecMath::Vector<D> > Xold = vertex_data<D>::X();
    for (unsigned i = 1; i <= _numSegments; ++i) {
        double rot = 1.*i*M_PI/_numSegments;
        for (typename std::vector<VecMath::Vector<D> >::iterator j = Xold.begin();
             j != Xold.end(); ++j) {
                 vertex_data<D>::X().push_back(rotate_vertex(*j, rot, d, d-1));
        }
    }
    
    vertex_data<D>::realm() = vertex_data<D>::realm().rotate(_numSegments, Xold.size());
    std::cerr << "rotate_base<" << D << ">::rotate(" << d << ")" << std::endl;
	vertex_data<D>::printVertices();
    vertex_data<D>::dimension()++;   //  object is now one dimension higher

#   if DEBUG_ROTOPES
    vertex_data<D>::print();
#   endif
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
    uintvec<1> new_surface; // defines the disk
    new_surface.push_back(0);
    vertex_data<D>::X().pop_back();
    for (unsigned i = 1; i <= _numSegments; ++i) {
        double rot = 2.*i*M_PI/_numSegments;
        VecMath::Vector<D> current = vertex_data<D>::X()[0];
        VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                            d, d-1);
        vertex_data<D>::X().push_back(rotated_current);
        new_surface.push_back(vertex_data<D>::X().size()-1);
    }
    vertex_data<D>::surface().push_back(new_surface);
}

/** \param d Dimension to be rotated into - the vertices are rotated away from
 *           axis \p d-1
 *  \param current_surface The triangular surface to be extruded into a cone
 */
template <unsigned D> void rotate_base<D>::rotate_triangle(
        unsigned d, const uintvec<1> &current_surface) {

#   if DEBUG_ROTOPES
        SingletonLog::Instance().log(__PRETTY_FUNCTION__);
#   endif
    uintvec<1> new_surface; //  defines the first cap
    new_surface.push_back(current_surface[0]);

    unsigned old_current = 0;
    /** Rotate the current surface through 360 degrees.
     *  \bug Instead of rotating it through 180 degrees and using every vertex,
     *       we only take the vertices on one side of the rotation axis.
     */
    for (unsigned i = 1; i <= _numSegments; ++i) {

        double rot = 2.*i*M_PI/_numSegments;

        unsigned cur_index = current_surface[0],
                 next_index = current_surface[2];

            VecMath::Vector<D> current = vertex_data<D>::X()[cur_index];
            VecMath::Vector<D> next = vertex_data<D>::X()[next_index];
            VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                               d, d-2);

            /// New vertex generated by rotation about angle \p rot
            vertex_data<D>::X().push_back(rotated_current);

            /// Add new vertex to cap
            new_surface.push_back(vertex_data<D>::X().size()-1);

            /// New triangular surface (current, next, rotated_current)
            vertex_data<D>::addSurface(old_current, next_index,
                                       vertex_data<D>::X().size()-1);

            old_current = vertex_data<D>::X().size()-1;
    }
    /// Add the new circular surface ("cap") generated by the rotation
    vertex_data<D>::addSurface(new_surface);
}

/** \param d Dimension to be rotated into - the vertices are rotated away from
 *           axis \p d-1
 *  \param current_surface The rectangular surface to be extruded into a cylinder
 */
template <unsigned D> void rotate_base<D>::rotate_quad(
        unsigned d, const uintvec<1> &current_surface) {
#   if DEBUG_ROTOPES
        SingletonLog::Instance().log(__PRETTY_FUNCTION__);
#   endif
    unsigned old_current = current_surface[0];  //  saved index to current vertex
    unsigned old_next = current_surface[1];     //  saved index to next vertex

    uintvec<1> bottom;       //  defines the first ("bottom") cap
    /// Save first vertex of "bottom" cap.
    bottom.push_back(current_surface[0]);
    /** Save first vertex of "top" cap.
     *  This relies on quads being defined in the order, 0, 1, 2, 3, where
     *  vertex 2 and 3 lie in the direction of the extrusion.
     */
    uintvec<1> top;          //  defines the second ("top") cap
    top.push_back(current_surface[2]);

    /** Rotate the current surface through 360 degrees.
     *  \bug Instead of rotating it through 180 degrees and using every vertex,
     *       we only take the vertices on one side of the rotation axis. Taking
     *       the indexes on the other side too would be an indexing nightmare.
     */
    for (unsigned i = 1; i <= _numSegments; ++i) {

        double rot = 2.*i*M_PI/_numSegments;

        unsigned cur_index = current_surface[0];
        unsigned next_index = current_surface[1];

        VecMath::Vector<D> current = vertex_data<D>::X()[cur_index];
        VecMath::Vector<D> next = vertex_data<D>::X()[next_index];

        /// New vertices generated by rotation about angle \p rot.
        VecMath::Vector<D> rotated_current = rotate_vertex(current, rot, d, d-1);
        VecMath::Vector<D> rotated_next = rotate_vertex(next, rot, d, d-1);

        vertex_data<D>::X().push_back(rotated_current);
        vertex_data<D>::X().push_back(rotated_next);

        /// Add quad surface: (current, next, rotated_next, rotated_current).
        vertex_data<D>::addSurface(old_current, old_next,
                                   vertex_data<D>::X().size()-1,
                                   vertex_data<D>::X().size()-2);

        /// Update vertices from which to draw the next surface.
        old_current = vertex_data<D>::X().size()-2;
        old_next = vertex_data<D>::X().size()-1;

        /// Add rotated vertex to bottom cap and rotated_next to top cap.
        bottom.push_back(vertex_data<D>::X().size()-2);
        top.push_back(vertex_data<D>::X().size()-1);
    }
    /// Add the new circular surfaces ("caps") generated by the rotation.
    vertex_data<D>::addSurface(bottom);
    vertex_data<D>::addSurface(top);
}

/** \param d Dimension to be rotated into - the vertices are rotated away from
 *           axis \p d-1
 *  \param current_surface The polygonal surface to be extruded into a sphere
 */
template <unsigned D> void rotate_base<D>::rotate_polygon(
        unsigned d, const uintvec<1> &current_surface) {
#   if DEBUG_ROTOPES
        SingletonLog::Instance().log(__PRETTY_FUNCTION__);
#   endif

    unsigned offset = 0;

    vertex_data<D>::X().push_back(vertex_data<D>::X()[current_surface[0]]);

    /// Rotate the current surface through 180 degrees along its central axis
    for (unsigned i = 1; i <= (_numSegments+1)/2; ++i) {

        double rot = 1.*i*M_PI/((_numSegments+1)/2);

        for (unsigned j = 0; j < current_surface.size(); j++) {

            unsigned cur_index = j+offset;

            unsigned next_index = j+1+offset;

            VecMath::Vector<D> current = vertex_data<D>::X()[cur_index-offset];
            VecMath::Vector<D> next = vertex_data<D>::X()[next_index-offset];
            VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                               d, d-1);
            VecMath::Vector<D> rotated_next = rotate_vertex(next, rot, d, d-1);

            /// New quad surface (current, next, rotated_next, rotated_current)
            vertex_data<D>::X().push_back(rotated_next);
#           if DEBUG_ROTOPES >= 2
            std::cerr << "j: " << j << "offset: " << offset
                      << " cur_index: " << cur_index << " next_index: " << next_index
                      << " size: " << vertex_data<D>::X().size() << "\n";
#           endif
            vertex_data<D>::addSurface(cur_index, next_index,
                                       vertex_data<D>::X().size()-1,
                                       vertex_data<D>::X().size()-2);

        }
        /// Update vertices from which to draw the next surface
        offset += current_surface.size();
    }
}

#endif
