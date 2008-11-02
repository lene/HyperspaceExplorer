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
            /// a one-dimensional array of unsigned, implemented as vector
            typedef std::vector<unsigned> uintvec1D;
            /// a two-dimensional array of unsigned, implemented as nested vector
            typedef std::vector<uintvec1D> uintvec2D;

            /// Create an empty array of vertices.
            /** Only derived classes can create a vertex_data object. */
            vertex_data():_dimension(0), _X(), _surface() {
                _X.push_back(VecMath::Vector<D>());
            }

            /// add a surface to the array of surfaces
            void addSurface(unsigned, unsigned, unsigned, unsigned);
            /// add a surface to the array of surfaces
            void addSurface(unsigned, unsigned, unsigned);

            unsigned &dimension() { return _dimension; }
            std::vector<VecMath::Vector<D> > &X() { return _X; }
            uintvec2D &surface() { return _surface; }

        private:
            unsigned _dimension;
            std::vector<VecMath::Vector<D> > _X;    ///< The array of vertices
            uintvec2D _surface;                     ///< The array of surfaces
    };

/*  You shouldn't use "using" directives in a header file, but the code gets
    nearly unreadable otherwise:
    typename std::vector<VecMath::Vector<D> >::iterator i = _X.begin();
    And because I'm defining template classes here, code must be written in the
    header file anyway.
*/
using VecMath::Vector;
using std::vector;

#include <iomanip>

template <unsigned D> void vertex_data<D>::print() {
    std::cerr << _dimension << "-dimensional object: ";
    std::string separator = "";
    for(typename vector<Vector<D> >::iterator i = _X.begin();
        i != _X.end(); ++i){
        std::cerr << separator << *i;
        separator = ", ";
    }
    std::cerr << "\n";

#   if 1
        std::cerr << "Surfaces: \n";
        for (unsigned i = 0; i < _surface.size(); ++i) {
            std::cerr << std::setw(4) << i << " (";
            separator = "";
            for (uintvec1D::iterator j = _surface[i].begin();
                 j != _surface[i].end(); ++j) {
                std::cerr << separator << std::setw(4) << *j;
                separator = ", ";
            }
            std::cerr << ")\n";
        }
        std::cerr << "\n";
#   endif

}

/**
 *  \param v1 Index (in the vertex array) of the first vertex
 *  \param v2 Index (in the vertex array) of the second vertex
 *  \param v3 Index (in the vertex array) of the third vertex
 *  \param v4 Index (in the vertex array) of the fourth vertex
 */
template <unsigned D> void vertex_data<D>::addSurface(unsigned v1, unsigned v2,
                                                      unsigned v3, unsigned v4) {
    if (v1 >= _X.size() || v2 >= _X.size() ||
        v3 >= _X.size() || v4 >= _X.size()) {
        throw std::out_of_range("vertex_data<D>::addSurface(): index larger "
                                "than size of vertex array");
    }

    uintvec1D tmp;
    tmp.push_back(v1); tmp.push_back(v2); tmp.push_back(v3); tmp.push_back(v4);

    _surface.push_back(tmp);
}

/** Overloaded version for three vertices
 *  \param v1 Index (in the vertex array) of the first vertex
 *  \param v2 Index (in the vertex array) of the second vertex
 *  \param v3 Index (in the vertex array) of the third vertex
 */
template <unsigned D> void vertex_data<D>::addSurface(unsigned v1, unsigned v2,
                                                      unsigned v3) {
    addSurface(v1, v2, v3, v3);
}

#endif
