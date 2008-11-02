#ifndef EXTRUSION_H
#define EXTRUSION_H

#include "Rotope.H"

/** \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D>
    class extrude_base: public vertex_data<D> {

        public:

            extrude_base(): vertex_data<D>() { }

            void extrude(unsigned d) {

                if (d >= D)
                    throw std::logic_error(
                        "extrude_base::extrude() called on a higher dimension"
                        " than the vector space allows");

                vector<Vector<D> > Xnew = vertex_data<D>::_X;

                typename vector<Vector<D> >::iterator i;
                for(i = Xnew.begin(); i != Xnew.end(); ++i){
                    Vector<D> xtmp = *i;
                    xtmp[d] = 1.;
                    vertex_data<D>::_X.push_back(xtmp);
                }
            }
    };

/** \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
    template <unsigned D, unsigned Dmin, unsigned Dmax>
        class Extrude: public Extrude<D, Dmin, Dmax-1> {
            public:
                Extrude(): Extrude<D, Dmin, Dmax-1>() { create(); }

                void create() { extrude_base<D>::extrude(Dmax); }
        };

/** \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
    template <unsigned D, unsigned Dmin>
        class Extrude<D, Dmin, Dmin>: public extrude_base<D> {
            public:
                Extrude(): extrude_base<D>() { create(); }

                void create() {
                    extrude_base<D>::extrude(Dmin);
                }
        };

#endif
