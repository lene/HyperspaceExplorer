#ifndef TAPER_H
#define TAPER_H

#include "Rotope.H"

/// Base class for Taper classes, providing the actual taper() function
/** \param D Dimension of the vector space we're working in
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D>
    class taper_base: public vertex_data<D> {

        public:
            /// Create a taper_base object from an already existing object
            taper_base(const vertex_data<D> &v):
                vertex_data<D>(v), _previous_dim(-1), _pre_previous_dim (-1) { }

            /// Execute the taper action of the previous object along axis \p d.
            /** Generally, a taper action is defined by the following formulas.
            *
            *  For going from a taper \f$ D-1 \f$ to the next, only the \f$ D-1 \f$ st and
            *  \f$ D \f$ th coordinate are affected.
            *
            *  The new point is extruded above the center of the \f$ D-1 \f$ st coordinate,
            *  thus \f$ X_{new,D-1} = \frac{X_{D-1} }{2} \f$ .
            *
            *  The \f$ D \f$ th coordinate is found by spanning a right triangle with the
            *  sides \f$ X_{new,D-1} \f$ and \f$ X_{D-2} \f$ , and solving the pythagorean
            *  equation for the missing cathetus.
            *
            *  While these formulas are relatively easy, keep in mind that
            *  -# You must store previous taper actions to remember \f$ D-1 \f$ and
            *     \f$ D-2 \f$ .
            *  -# If you haven't tapered at least twice before, you don't have values for
            *     \f$ D-1 \f$ and \f$ D-2 \f$. Thus, you must make up these values.
            *     Luckily, this is possible:
            *     -# If we taper for the first time, the new point lies above the center of
            *        the old surface. We calculate the mean of all \f$ D-1 \f$ coordinates
            *        and extrude above that point. The \f$ D \f$ coordinate is
            *        \f$ \sqrt{1 - \bar{x_i}^2} \f$. \f$ \bar{x_i} \f$ is considered to be
            *        equal to \f$ \frac{1}{2} \f$ in this function, because I don't see how
            *        it could have another value that makes sense.
            *     -# If we taper for the second time, we extrude above the center of the
            *        \f$ D-1 \f$ st coordinate, so the value for this is halved for the
            *        \f$ D-1 \f$ coordinate of the new point. The \f$ D \f$ coordinate is
            *        \f$ \sqrt{x_{D-1} }^2 - \frac{1}{2^2} } \f$ , because the second leg of
            *       the equilateral triangle was created by the \em first extrusion and
            *       is known to be of length \f$ \frac{1}{2} \f$ .
            *
            *  \param d The new dimension into which the object is tapered
            */
            void taper(unsigned d);

        private:
            /// \return Whether working on an object that's already a Taper.
            bool alreadyTapered() { return _previous_dim >= 0; }

            /// Axis the previous taper() action went along
            int _previous_dim;
            /// Axis the taper() action before the previous went along
            int _pre_previous_dim;
    };

/// A class template to execute taper actions on an object
/** The vertex array of the object is tapered into a set of consecutive
 *  dimensions.
 *
 *  As I find the concept hard to explain in words, let me give a few examples
 *  to illustrate the idea:
 *  \code Extrude<4, 0, 0> line; \endcode
 *  A line in four-space. A point is extruded along dimension 0 (\p x ).
 *  \code Taper<4, 1, 1> triangle(line); \endcode
 *  An equilateral triangle in the \p xy -plane. The line along \p x is tapered
 *  into the \p y dimension.
 *  \code Taper<4, 2, 2> tetrahedron1(triangle); \endcode
 *  Create a tetrahedron from an equilateral triangle by tapering along the \p z
 *  axis.
 *  \code Taper<4, 1, 2> tetrahedron2(line); \endcode
 *  Create another tetrahedron from a line by tapering it into the dimensions 1
 *  to 2, ie. along \p y and \p z
 *  \code Extrude<4, 0, 1> square;
 * Taper<4, 2, 2> pyramid(square); \endcode
 *  A four-sided pyramid is created by tapering a square along the \p z axis.
 *  \code Taper<4, 1, 3> pentachoron(line); \endcode
 *  A four-dimensional simplex, a pentachoron, is created by tapering a line
 *  three times.
 *
 *  \param D Dimension of the vector space we're working in
 *  \param Dmin First of the set of dimensions being tapered into
 *  \param Dmax Last of the set of dimensions being tapered into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D, unsigned Dmin, unsigned Dmax>
    class Taper: public Taper<D, Dmin, Dmax-1> {
        public:
            /// Create a Taper object from an already existing object
            /** \todo Guard against bad template parameters:
             *        - Dmin >= Dmax
             *        - Dmin or Dmax >= D
             *        - Dmin or Dmax >= vertex_data::_dimension
             *        - vertex_data::_dimension == 0
             */
            Taper(const vertex_data<D> &v): Taper<D, Dmin, Dmax-1>(v) {
                taper_base<D>::taper(Dmax);
            }
    };

/// Specialization of Taper<D,Dmin,Dmax> to end recursion
/** \param D Dimension of the vector space we're working in
 *  \param Dmin Dimension being tapered into
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D, unsigned Dmin>
    class Taper<D, Dmin, Dmin>: public taper_base<D> {
        public:
            /// Create a Taper object from an already existing object
            /** \todo Guard against bad template parameters:
             *        - Dmin  >= D
             *        - Dmin  >= vertex_data::_dimension
             *        - vertex_data::_dimension == 0
             */
            Taper(const vertex_data<D> &v): taper_base<D>(v) {
                taper_base<D>::taper(Dmin);
            }
    };

template <unsigned D> void taper_base<D>::taper(unsigned d) {

    if (d >= D) {
        throw std::logic_error(
            "taper_base::taper() called on a higher dimension than the "
            "vector space allows");
    }
    if (vertex_data<D>::X().size() < 2) {
        throw std::logic_error(
            "taper_base::taper() can only operate on at least two vertices");
    }

    Vector<D> xnew;     //  connect all vertices to this new vertex

    if (!alreadyTapered()) {
        /// By Pythagoras! The coordinate tapered into is sqrt(1-1/2^2).
        double displacement = sqrt(1.-0.25);
        /** If this is the first time we taper an object, we must extrude a new
            point above the middle of the old object.
            For all directions except the newly tapered one, the coordinate value
            is the mean of the old ones.\n
            We can skip the test for the dimension tapered into, because it's
            all zero by definition anyway.
        */
        for(unsigned i = 0; i < vertex_data<D>::X().size(); ++i) {
            xnew += vertex_data<D>::X()[i];
            vertex_data<D>::X()[i][d] -= displacement;
        }
        xnew *= 1./vertex_data<D>::X().size();

        xnew[d] = displacement;
    } else {
        /** Copy the last tapered point. It serves as reference, because only the
            coordinate last tapered into changes (it is halved), in addition to
            the newly extruded point.
        */
        xnew = vertex_data<D>::X().back();
        double displacement;

        if (_pre_previous_dim < 0) {
            /** If we have extruded only once before, we know the short cathetus
             *  of the right triangle spanned by the back of the equilateral
             *  triangle to be 0.5 - half a unit, because it lies in the center
             *  of the previous object.
             */
            displacement = sqrt(xnew[_previous_dim]*xnew[_previous_dim]-.25);
            xnew[d] = displacement;

            /** Consequently, in this dimension the new point lies in the center
             *  of the previous edge.
             */
            xnew[_previous_dim] /= 2.;
        } else {
            /** If we have stored at least two previous extrusions, the cathetus
             *  of the new triangle is defined by those.
             */
            displacement = sqrt(fabs(xnew[_previous_dim]*xnew[_previous_dim]-
                        xnew[_pre_previous_dim]*xnew[_pre_previous_dim]));
            xnew[d] = displacement;

            xnew[_previous_dim] /= 2.;
        }
        for(unsigned i = 0; i < vertex_data<D>::X().size(); ++i) {
            vertex_data<D>::X()[i][d] -= displacement;
        }

    }

    vertex_data<D>::X().push_back(xnew);

    /** Define surfaces now. Every two neighboring points from the old object
     *  are connected to the new point, thus spanning a surface.
     */
    if (!vertex_data<D>::surface().size()) {
        vertex_data<D>::addSurface(0, 1, 2);
    } else {
        for (unsigned i = 0; i < vertex_data<D>::surface().size(); i++) {
            for (unsigned j = 0; j < vertex_data<D>::surface()[i].size(); j++) {
                unsigned jnext = (j+1)%vertex_data<D>::surface()[i].size();
                vertex_data<D>::addSurface(
                    vertex_data<D>::surface()[i][j], vertex_data<D>::surface()[i][jnext],
                    vertex_data<D>::X().size()-1);
            }
        }
    }

    _pre_previous_dim = _previous_dim;
    _previous_dim = d;

    vertex_data<D>::dimension()++;   //  object is now one dimension higher
}

#endif
