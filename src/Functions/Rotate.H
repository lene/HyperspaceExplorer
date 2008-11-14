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
                vertex_data<D>(v), _numSegments(10) { }

            /// Execute the rotate action of the previous object along axis \p d.
            void rotate(unsigned d);

        private:
            /// Extrude the object for distance \p dist along axis \p d
            void extrude(unsigned d, double dist, const vector<Vector<D> > &);
            VecMath::Vector<D> rotate_vertex(const VecMath::Vector<D> &, double,
                                             unsigned, unsigned);

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

template <unsigned D> void rotate_base<D>::extrude(unsigned d,
        double dist, const vector<Vector<D> > &Xold) {

    typename vertex_data<D>::uintvec2D surface_old =
            vertex_data<D>::surface();

    /// Extrude vertices into the \p d axis, setting the \p d coordinate to 1
    for (unsigned i = 0; i < Xold.size(); ++i) {
        Vector<D> xtmp = Xold[i];
        xtmp[d] = dist;
        vertex_data<D>::X().push_back(xtmp);
    }

    if (vertex_data<D>::dimension() == 1) {
        vertex_data<D>::addSurface(0, 1, 3, 2);
    } else if (vertex_data<D>::dimension() > 1) {
        /// Extrude surfaces from each edge of the base surface to its image
        for (unsigned i = 0; i < surface_old.size(); ++i) {
            for (unsigned j = 0; j < surface_old[i].size(); j++) {
                unsigned j_ = (j+1)%surface_old[i].size();
                vertex_data<D>::addSurface(surface_old[i][j],
                                           surface_old[i][j_],
                                           surface_old[i][j_]+Xold.size(),
                                                   surface_old[i][j]+Xold.size());
            }
        }

        /** add all surfaces which were in the old vertex array, but extruded
            along the \p d axis. This is achieved by copying the old surface
            array and adding the size of the old vertex array to each of the
            indices therein.
        */
        for (unsigned i = 0; i < surface_old.size(); ++i) {
            typename vertex_data<D>::uintvec1D tmp = surface_old[i];
            for (unsigned j = 0; j < tmp.size(); ++j) {
                tmp[j] += Xold.size();
            }
            vertex_data<D>::addSurface(tmp[0], tmp[1], tmp[2], tmp[3]);
        }
    }
}

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

    RotopeBase::uintvec2D surface_old = vertex_data<D>::surface();
    for (unsigned i = 0; i < surface_old.size(); ++i) {

        std::vector<unsigned> current_surface =
                vertex_data<D>::surface()[i];
        if (current_surface.size() < 3)
            throw new std::logic_error("size of surface < 3");

        unsigned old_current = 0, old_next = 1;
        for (double rot = M_PI/_numSegments; rot <= 2.*M_PI;
             rot += M_PI/_numSegments) {

            for (unsigned j = 0; j < current_surface.size(); j += 4) {

                std::cerr << "surface[" << i << "]: (";
                for (unsigned k = 0; k < current_surface.size(); ++k)
                    std::cerr << current_surface[k] << " ";
                std::cerr << ")\n";

                unsigned cur_index = current_surface[j],
                    next_index = current_surface[(j+1)%current_surface.size()];

                std::cerr << "j: " << j << ": "
                        << cur_index << "->" << next_index << "\n";

                VecMath::Vector<D> current = vertex_data<D>::X()[cur_index];
                VecMath::Vector<D> next = vertex_data<D>::X()[next_index];
                VecMath::Vector<D> rotated_current = rotate_vertex(current, rot,
                                                                   d, d-1);

                vertex_data<D>::X().push_back(rotated_current);

                if (current_surface.size() == 3) {
                    // new surface (current, next, rotated)
                    vertex_data<D>::addSurface(j, (j+1)%3,
                                               vertex_data<D>::X().size()-1);
                } else {
                    VecMath::Vector<D> rotated_next = rotate_vertex(next, rot,
                                                                    d, d-1);
                    // new surface (current, next, rotated_next, rotated_current)
                    vertex_data<D>::X().push_back(rotated_next);
                    vertex_data<D>::addSurface(old_current, old_next,
                                               vertex_data<D>::X().size()-1,
                                               vertex_data<D>::X().size()-2);

                    old_current = vertex_data<D>::X().size()-2;
                    old_next = vertex_data<D>::X().size()-1;
                }

                std::cerr << "surface[" << i << "] after addSurface(): (";
                for (unsigned k = 0; k < current_surface.size(); ++k)
                    std::cerr << current_surface[k] << " ";
                std::cerr << ")\n";
            }
        }
        // delete surface[i];
        vertex_data<D>::removeSurface(i);
        // add caps
    }

    vertex_data<D>::dimension()++;   //  object is now one dimension higher

    vertex_data<D>::print();
}

template <unsigned D> VecMath::Vector<D> rotate_base<D>::rotate_vertex(
        const VecMath::Vector<D> &v, double rot,
        unsigned new_axis, unsigned old_axis) {
    std::cerr << "rotate_base<" << D << ">::rotate_vertex(" << v << ", " << rot << ", " << new_axis << ", " << old_axis << ")\n";
    VecMath::Vector<D> v_new(v);
    v_new[new_axis] = v_new[old_axis]*sin(rot);
    v_new[old_axis] *= cos(rot);
    return v_new;
}

#endif
