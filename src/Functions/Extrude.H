#ifndef EXTRUSION_H
#define EXTRUSION_H

#include "Rotope.H"

/// Base class for Extrude classes, providing the actual extrude() function
/** \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D>
    class extrude_base: public vertex_data<D> {

        public:

            /// Create an empty extrude_base object
            extrude_base(): vertex_data<D>() { }
            /// Create an extrude_base object from an already existing object
            extrude_base(const vertex_data<D> &v): vertex_data<D>(v) { }

            /// Extrudes an object along a given dimension
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
 *  \code Taper<4, 1, 1> triangle(line);
 * Extrude<4, 2, 2> prism; \endcode
 *  A line is tapered into a triangle, and then extruded to become a prism.
 *  \code Extrude<4, 0, 3> tesseract; \endcode
 *  Extruding a point i four dimensions gives a hypercube or tesseract.
 *
 *  \param D Dimension of the vector space we're working in
 *  \param Dmin First of the set of dimensions being tapered into
 *  \param Dmax Last of the set of dimensions being tapered into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
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
            Extrude(const vertex_data<D> &v): Extrude<D, Dmin, Dmax-1>(v) {
                extrude_base<D>::extrude(Dmax);
            }
        };

/// Specialization of Extrude<D,Dmin,Dmax> to end recursion
/** \param D Dimension of the vector space we're working in
 *  \param Dmin Dimension being tapered into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
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
            Extrude(const vertex_data<D> &v): extrude_base<D>(v) {
                extrude_base<D>::extrude(Dmin);
            }
    };


/** For each point in the vertex array, a copy is made and shifted along the
 *  \p d axis. Thus, a point becomes a line when extruded along axis 0, a line
 *  becomes a square when extruded along axis 1, and so on. A circle becomes a
 *  cylinder when extruded along axis 2, and similarly with all kinds of
 *  objects. You get the idea.
 *
 *  \param d The new dimension into which the object is extruded
 */
template <unsigned D> void extrude_base<D>::extrude(unsigned d) {
    if (d >= D) {
        throw std::logic_error(
           "extrude_base::extrude() called on a higher dimension"
           " than the vector space allows");
    }

    const vector<Vector<D> > Xold = vertex_data<D>::X();
    typename vertex_data<D>::uintvec2D surface_old =
            vertex_data<D>::surface();

    /// Extrude vertices into the \p d axis, setting the \p d coordinate to 1
    for (unsigned i = 0; i < Xold.size(); ++i) {
        Vector<D> xtmp = Xold[i];
        xtmp[d] = 0.5;
        vertex_data<D>::X()[i][d] = -0.5;
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
        // for (unsigned i = 0; i < Xold.size(); ++i) std::cerr << Xold[i] << " ";

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

    /// Remove double surfaces from area

    vertex_data<D>::dimension()++;   //  object is now one dimension higher
}

#endif
