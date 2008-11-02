#ifndef EXTRUSION_H
#define EXTRUSION_H

#include "Rotope.H"

/// Base class for Extrude classes, providing the actual extrude() function
/** \ingroup ObjectGroup
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
 *  \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D, unsigned Dmin, unsigned Dmax>
    class Extrude: public Extrude<D, Dmin, Dmax-1> {
        public:
            /// Create an Extrude object from a point
            Extrude(): Extrude<D, Dmin, Dmax-1>() {
                extrude_base<D>::extrude(Dmax);
            }
            /// Create an Extrude object from an already existing object
            Extrude(const vertex_data<D> &v): Extrude<D, Dmin, Dmax-1>(v) {
                extrude_base<D>::extrude(Dmax);
            }
        };

/// Specialization of Extrude<D,Dmin,Dmax> to end recursion
/** \param D Dimension of the vector space we're working in
 *  \param Dmin Dimension being tapered into
 *
 *  \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D, unsigned Dmin>
    class Extrude<D, Dmin, Dmin>: public extrude_base<D> {
        public:
            /// Create an Extrude object from a point
            Extrude(): extrude_base<D>() {
                extrude_base<D>::extrude(Dmin);
            }
            /// Create an Extrude object from an already existing object
            Extrude(const vertex_data<D> &v): extrude_base<D>(v) {
                extrude_base<D>::extrude(Dmin);
            }
    };


/**
 *  \param d The new dimension into which the object is extruded
 */
template <unsigned D> void extrude_base<D>::extrude(unsigned d) {
    if (d >= D) {
        throw std::logic_error(
           "extrude_base::extrude() called on a higher dimension"
           " than the vector space allows");
    }

    vector<Vector<D> > Xnew = vertex_data<D>::_X;

    for (typename vector<Vector<D> >::iterator i = Xnew.begin();
        i != Xnew.end(); ++i){
        Vector<D> xtmp = *i;
        xtmp[d] = 1.;
        vertex_data<D>::_X.push_back(xtmp);
    }
}

#endif
