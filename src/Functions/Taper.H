#ifndef TAPER_H
#define TAPER_H

#include "Rotope.H"

/** \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D>
    class taper_base: public vertex_data<D> {

        public:

            taper_base():
                vertex_data<D>(), _previous_dim(-1), _pre_previous_dim (-1) { }
            taper_base(const vertex_data<D> &v):
                    vertex_data<D>(v), _previous_dim(-1), _pre_previous_dim (-1) { }

            /** Generally, a taper action is defined by the following formulas.
             *
             *  For going from a taper \f$ D-1 \f$ to the next, only the
             *  \f$ D-1 \f$ st and \f$ D \f$ th coordinate are affected.
             *
             *  The new point is extruded above the center of the \f$ D-1 \f$ st
             *  coordinate, thus \f$ X_{new}_{D-1} = \frac{X_{D-1}}{2} \f$.
             *
             *  The \f$ D \f$ th coordinate is found by spanning a right
             *  triangle with the sides \f$ X_{new}_{D-1} \f$ and
             *  \f$ X_{D-2} \f$.
             *
             *  While these formulas are relatively easy, keep in mind that
             *  -# you must store previous taper actions to remember \f$ D-1 \f$
             *     and \f$ D-2 \f$.
             *  -# if you haven't tapered at least twice before, you don't have
             *     values for \f$ D-1 \f$ and \f$ D-2 \f$.
             *
             *  \param d The new dimension into which is tapered */
            void taper(unsigned d) {

                if (d >= D) {
                    throw std::logic_error(
                        "taper_base::taper() called on a higher dimension"
                        " than the vector space allows");
                }
                if (vertex_data<D>::_X.size() < 2) {
                    throw std::logic_error(
                        "taper_base::taper() can only operate on at least two"
                        " vertices");
                }

                Vector<D> xnew;     //  connect all vertices to this new vertex

                if (!alreadyTapered()) {
                    /*  if this is the first time we taper an object, we must
                        extrude a new point above the middle of the old object.
                        for all directions except the newly tapered one, the
                        coordinate value is the mean of the old ones.

                        we can skip the test for the dimension tapered into,
                        because it's all zero by definition anyway.           */
                    for(unsigned i = 0; i < vertex_data<D>::_X.size(); ++i) {
                        xnew += vertex_data<D>::_X[i];
                    }
                    xnew *= 1./vertex_data<D>::_X.size();

                    /*  by pythagoras! the coordinate tapered into is
                        sqrt(1-1/2^2)                                         */
                    xnew[d] = sqrt(1.-0.25);
                } else {
                    /*  copy the last tapered point. it serves as reference,
                        because only the coordinate last tapered into changes
                        (it is halved), in addition to the newly extruded point
                    */
                    xnew = vertex_data<D>::_X.back();

                    if (_pre_previous_dim < 0) {
                        /*  if we have extruded only once before, we know the
                            short cathetus of the right triangle spanned by the
                            back of the equilateral triangle to be 0.5 - half a
                            unit, because it lies in the center of the previous
                            object.                                           */
                        xnew[d] = sqrt(xnew[_previous_dim]*xnew[_previous_dim]-.25);
                        /*  consequently, in this dimension the new point lies
                            in the center of the previous edge.               */
                        xnew[_previous_dim] /= 2.;
                    } else {
                        /*  we have stored at least two previous extrusions,
                            the cathetus of the new triangle is defined by them.
                        */
                        xnew[d] = sqrt(fabs(xnew[_previous_dim]*xnew[_previous_dim]-
                                xnew[_pre_previous_dim]*xnew[_pre_previous_dim]));
                        xnew[_previous_dim] /= 2.;
                    }
                }
                vertex_data<D>::_X.push_back(xnew);

                _pre_previous_dim = _previous_dim;
                _previous_dim = d;
            }

        private:
            bool alreadyTapered() { return _previous_dim >= 0; }

            int _previous_dim;
            int _pre_previous_dim;
    };

/** \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
    template <unsigned D, unsigned Dmin, unsigned Dmax>
        class Taper: public Taper<D, Dmin, Dmax-1> {
            public:
                Taper(): Taper<D, Dmin, Dmax-1>() { create(); }
                Taper(const vertex_data<D> &v): Taper<D, Dmin, Dmax-1>(v) {
                    create();
                }
                void create() { taper_base<D>::taper(Dmax); }
        };

/** \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
    template <unsigned D, unsigned Dmin>
        class Taper<D, Dmin, Dmin>: public taper_base<D> {
            public:
                Taper(): taper_base<D>() { create(); }
                Taper(const vertex_data<D> &v): taper_base<D>(v) {
                    create();
                }

                void create() {
                    taper_base<D>::taper(Dmin);
                }
        };

#endif
