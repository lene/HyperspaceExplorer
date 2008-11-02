#ifndef ROTOPE_H
#define ROTOPE_H

#include <Object.H>

/** \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
class Rotope : public Object {
public:
    Rotope(const QString &);

    ~Rotope();

};

using VecMath::Vector;
using std::vector;

/** \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
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


#endif
