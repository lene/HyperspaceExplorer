#ifndef ROTOPE_H
#define ROTOPE_H

#include <Object.H>

/**
	@author Helge Preuss <scout@hyperspace-travel.de>
 */
class Rotope : public Object {
public:
    Rotope(const QString &);

    ~Rotope();

};

using VecMath::Vector;
using std::vector;

template <unsigned D>
    class vertex_data {
        public:
            void print() {
                typename vector<Vector<D> >::iterator i;
                std::string separator = "";
                for(i = _X.begin(); i != _X.end(); ++i){
                    std::cerr << separator << *i;
                    separator = ", ";
                }
                std::cerr << "\n";
            }

        protected:
            vertex_data(): _X() { _X.push_back(Vector<D>()); }

            vector<Vector<D> > _X;
    };

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

    template <unsigned D, unsigned Dmin, unsigned Dmax>
        class Extrude: public Extrude<D, Dmin, Dmax-1> {
            public:
                Extrude(): Extrude<D, Dmin, Dmax-1>() { create(); }

                void create() { extrude_base<D>::extrude(Dmax); }
        };

    template <unsigned D, unsigned Dmin>
        class Extrude<D, Dmin, Dmin>: public extrude_base<D> {
            public:
                Extrude(): extrude_base<D>() { create(); }

                void create() {
                    extrude_base<D>::extrude(Dmin);
                }
        };

template <unsigned D>
    class taper_base: public vertex_data<D> {

        public:

            taper_base(): vertex_data<D>() { }

            /** \param dold The existing dimension along which is tapered
             *  \param dnew The new dimension \em into which is tapered
             */
            void taper(unsigned dold, unsigned dnew) {

                if (dold >= D || dnew >= D)
                    throw std::logic_error(
                        "taper_base::taper() called on a higher dimension"
                        " than the vector space allows");

                Vector<D> xtmp;

                typename vector<Vector<D> >::iterator i;
                for(i = vertex_data<D>::_X.begin();
                    i != vertex_data<D>::_X.end();
                    ++i) {

                    xtmp[dnew] = 1.;
                }
                vertex_data<D>::_X.push_back(xtmp);
            }
    };

#endif
