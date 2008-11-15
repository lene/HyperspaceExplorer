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
                vertex_data<D>(v), _numSegments(3) { }

            /// Execute the rotate action of the previous object along axis \p d.
            void rotate(unsigned d);

        private:
            VecMath::Vector<D> rotate_vertex(const VecMath::Vector<D> &, double,
                                             unsigned, unsigned);
            void rotate_line(unsigned);
            void rotate_triangle(unsigned, const vector<unsigned> &);
            void rotate_quad(unsigned, const vector<unsigned> &);
            void rotate_polygon(unsigned, const vector<unsigned> &);

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

/** \param d The direction into which is extruded. The rotation takes place in
 *           the ( \p d, \p d-1 )-plane.
 */
template <unsigned D> void rotate_base<D>::rotate(unsigned d) {
    std::cerr << "rotate_base<" << D << ">::rotate(" << d << ")\n";
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

    if (vertex_data<D>::surface().empty()) {
        rotate_line(d);
    } else {
        RotopeBase::uintvec2D surface_old = vertex_data<D>::surface();

        /// Execute the rotation for all surfaces
        for (unsigned i = 0; i < surface_old.size(); ++i) {

            std::vector<unsigned> current_surface = surface_old[i];
            switch (current_surface.size()) {
                case 0: case 1: case 2:
                    throw new std::logic_error("size of surface < 3");
                    break;
                case 3:
                    rotate_triangle(d, current_surface);
                    break;
                case 4:
                    rotate_quad(d, current_surface);
                    break;
                default:
                    rotate_polygon(d, current_surface);
            }

            /// Delete current surface, it has been replaced by a rotation of itself
            vertex_data<D>::removeSurface(i);
            vertex_data<D>::print();
        }
    }

    vertex_data<D>::dimension()++;   //  object is now one dimension higher

#   if 0
        vertex_data<D>::print();
#   endif
}

template <unsigned D> VecMath::Vector<D> rotate_base<D>::rotate_vertex(
        const VecMath::Vector<D> &v, double rot,
        unsigned new_axis, unsigned old_axis) {
#   if 0
        std::cerr << "rotate_base<" << D << ">::rotate_vertex(" << v << ", "
                  << rot << ", " << new_axis << ", " << old_axis << ")\n";
#   endif
    VecMath::Vector<D> v_new(v);
    v_new[new_axis] = v_new[old_axis]*sin(rot);
    v_new[old_axis] *= cos(rot);
    return v_new;
}

template <unsigned D> void rotate_base<D>::rotate_line(unsigned d) {
    std::vector<unsigned> new_surface; ///< defines the disk
    new_surface.push_back(0);
    vertex_data<D>::X().pop_back();
    for (double rot = M_PI/_numSegments; rot < 2.*M_PI;
            rot += M_PI/_numSegments) {
        VecMath::Vector<D> current = vertex_data<D>::X()[0];
        VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                            d, d-1);
        vertex_data<D>::X().push_back(rotated_current);
        new_surface.push_back(vertex_data<D>::X().size()-1);
    }
    vertex_data<D>::surface().push_back(new_surface);
    vertex_data<D>::dimension()++;   //  object is now one dimension higher
    vertex_data<D>::print();
}

template <unsigned D> void rotate_base<D>::rotate_triangle(
        unsigned d, const vector<unsigned> &current_surface) {

    std::vector<unsigned> new_surface1; ///< defines the first cap
    new_surface1.push_back(current_surface[0]);

    unsigned old_current = 0;
    /** Rotate the current surface through 360 degrees.
     *  \bug Instead of rotating it through 180 degrees and using every
     *       vertex, we only take the vertices on one side of the rotation
     *       axis.
     */
    for (double rot = M_PI/_numSegments; rot <= 2.*M_PI;
         rot += M_PI/_numSegments) {

        unsigned cur_index = current_surface[0],
                 next_index = current_surface[2];

            VecMath::Vector<D> current = vertex_data<D>::X()[cur_index];
            VecMath::Vector<D> next = vertex_data<D>::X()[next_index];
            VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                               d, d-2);

            vertex_data<D>::X().push_back(rotated_current);

            new_surface1.push_back(vertex_data<D>::X().size()-1);

            /// New triangular surface (current, next, rotated_current)
            vertex_data<D>::addSurface(old_current, 2,
                                       vertex_data<D>::X().size()-1);

            old_current = vertex_data<D>::X().size()-1;
    }
    /// Add the new circular surface ("cap") generated by the rotation
    vertex_data<D>::addSurface(new_surface1);
}

template <unsigned D> void rotate_base<D>::rotate_quad(
        unsigned d, const vector<unsigned> &current_surface) {
    unsigned old_current = 0;
    unsigned old_next = 1;
    std::vector<unsigned> new_surface1; ///< defines the first cap
    new_surface1.push_back(current_surface[0]);
    std::vector<unsigned> new_surface2; ///< defines the second cap, if any
    new_surface2.push_back(current_surface[2]);

    /** Rotate the current surface through 360 degrees.
     *  \bug Instead of rotating it through 180 degrees and using every
     *       vertex, we only take the vertices on one side of the rotation
     *       axis.
     */
    for (double rot = M_PI/_numSegments; rot <= 2.*M_PI;
         rot += M_PI/_numSegments) {

        for (unsigned j = 0; j < current_surface.size(); j += 4) {

            unsigned cur_index = current_surface[j];
            unsigned next_index = current_surface[(j+1)%current_surface.size()];

            VecMath::Vector<D> current = vertex_data<D>::X()[cur_index];
            VecMath::Vector<D> next = vertex_data<D>::X()[next_index];
            VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                               d, d-1);
            VecMath::Vector<D> rotated_next = rotate_vertex(next, rot, d, d-1);

            vertex_data<D>::X().push_back(rotated_current);

            new_surface1.push_back(vertex_data<D>::X().size()-1);

            /// New quad surface (current, next, rotated_next, rotated_current)
            vertex_data<D>::X().push_back(rotated_next);
            vertex_data<D>::addSurface(old_current, old_next,
                                       vertex_data<D>::X().size()-1,
                                       vertex_data<D>::X().size()-2);

            /// Update vertices from which to draw the next surface
            old_current = vertex_data<D>::X().size()-2;
            old_next = vertex_data<D>::X().size()-1;

            /// Add rotated_next to second cap
            new_surface2.push_back(vertex_data<D>::X().size()-1);
        }
    }
    /// Add the new circular surfaces ("caps") generated by the rotation
    vertex_data<D>::addSurface(new_surface1);
    if (!new_surface2.empty()) vertex_data<D>::addSurface(new_surface2);

}

template <unsigned D> void rotate_base<D>::rotate_polygon(
        unsigned d, const vector<unsigned> &current_surface) {

    unsigned offset = 0;
    const double epsilon = 0.01;

    vertex_data<D>::X().push_back(vertex_data<D>::X()[current_surface[0]]);

    /** Rotate the current surface through 360 degrees.
     *  \bug Instead of rotating it through 180 degrees and using every
     *       vertex, we only take the vertices on one side of the rotation
     *       axis.
     */
    for (double rot = M_PI/_numSegments; rot <= M_PI+epsilon;
         rot += M_PI/_numSegments) {

        for (unsigned j = 0; j < current_surface.size(); j++) {

            unsigned cur_index = j+offset;

            unsigned next_index = j+1+offset;

            VecMath::Vector<D> current = vertex_data<D>::X()[cur_index-offset];
            VecMath::Vector<D> next = vertex_data<D>::X()[next_index-offset];
            VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                               d, d-1);
            VecMath::Vector<D> rotated_next = rotate_vertex(next, rot, d, d-1);

            /// New quad surface (current, next, rotated_next, rotated_current)
//            if (rotated_next != next) {
                vertex_data<D>::X().push_back(rotated_next);
                std::cerr << "j: " << j << "offset: " << offset
                        << " cur_index: " << cur_index << " next_index: " << next_index
                        << " size: " << vertex_data<D>::X().size() << "\n";
                vertex_data<D>::addSurface(cur_index, next_index,
                                           vertex_data<D>::X().size()-1,
                                           vertex_data<D>::X().size()-2);
//          }

        }
        /// Update vertices from which to draw the next surface
        offset += current_surface.size();
    }
//    vertex_data<D>::print();
}

#endif
