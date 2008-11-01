#ifndef TAPER_H
#define TAPER_H

#include "Rotope.H"

/**
	@author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D>
    class taper_base: public vertex_data<D> {

        public:

            taper_base():
                vertex_data<D>(), _previous_dim(-1), _pre_previous_dim (-1) { }
            taper_base(const vertex_data<D> &v):
                    vertex_data<D>(v), _previous_dim(-1), _pre_previous_dim (-1) { }

            /** \param d The new dimension into which is tapered */
            void taper(unsigned d) {

                if (d >= D)
                    throw std::logic_error(
                                           "taper_base::taper() called on a higher dimension"
                            " than the vector space allows");

                if (vertex_data<D>::_X.size() < 2)
                    throw std::logic_error(
                                           "taper_base::taper() can only operate on at least two"
                            " vertices");

                Vector<D> xnew;

                if (!alreadyTapered()) {
                    //  if this is the first time we taper an object, we must
                    //  extrude a new point above the middle of the old object.
                    //  for all directions except the newly tapered one, the
                    //  coordinate value is the mean of the old ones.

                    unsigned num_data = 0;
                    typename vector<Vector<D> >::iterator i;

                    //  we can skip the test for the dimension tapered into,
                    //  because it's all zero by definition anyway.
                    for(i = vertex_data<D>::_X.begin();
                        i != vertex_data<D>::_X.end();
                        ++i, ++num_data) {
                            xnew += *i;
                        }
                        xnew *= 1./num_data;

                    //  by pythagoras! the coordinate tapered into is
                    //  sqrt(1-1/(2^2))
                        xnew[d] = sqrt(1.-0.25);
                } else {
                    xnew = vertex_data<D>::_X.back();
                    std::cerr << "_previous_dim: " << _previous_dim
                            << ", x[]: " << xnew[_previous_dim] << "\n";
                    if (_pre_previous_dim < 0) {
                        xnew[d] = sqrt(xnew[_previous_dim]*xnew[_previous_dim]-.25);
                        xnew[_previous_dim] /= 2.;
                    } else {
                        std::cerr << "_pre_previous_dim: " << _pre_previous_dim
                                << ", x[]: " << xnew[_pre_previous_dim] << "\n";
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

#endif
