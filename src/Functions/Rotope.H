#ifndef ROTOPE_H
#define ROTOPE_H

#include <Object.H>

/// A four-dimensional <a href="http://teamikaria.com/wiki/Rotope">Rotope</a>.
/** \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
class Rotope : public Object {
public:
    Rotope(const QString &);

    ~Rotope();

};

/*  You shouldn't use "using" directives in a header file, but the code gets
    nearly unreadable otherwise:
    typename std::vector<VecMath::Vector<D> >::iterator i = _X.begin();
    And because I'm defining template classes here, code must be written in the
    header file anyway.
*/
using VecMath::Vector;
using std::vector;

/// Base class for all Rotope s. This class may vanish, as Object can take its place.
/** Contains an array of vertices (Vectors) and a function to print them. This
 *  is used mainly in the development of Rotope objects.
 *
 *  \param D Dimension of the vector space we're working in
 *
 *  \ingroup ObjectGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D>
    class vertex_data {
        public:
            void print();           ///< Output of all vertices

        protected:
            /// Create an empty array of vertices.
            /** Only derived classes can create a vertex_data object. */
            vertex_data(): _X() { _X.push_back(Vector<D>()); }

            vector<Vector<D> > _X;  ///< The array of vertices
    };

template <unsigned D> void vertex_data<D>::print() {
    std::string separator = "";
    for(typename vector<Vector<D> >::iterator i = _X.begin();
        i != _X.end(); ++i){
        std::cerr << separator << *i;
        separator = ", ";
    }
    std::cerr << "\n";
}

#endif
