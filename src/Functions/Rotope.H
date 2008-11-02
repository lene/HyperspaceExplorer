#ifndef ROTOPE_H
#define ROTOPE_H

#include <Object.H>

/** \defgroup RotopeGroup
 *  \ingroup ObjectGroup
 */

/// Base class for all Rotope s. This class may vanish, as Object can take its place.
/** Contains an array of vertices (Vectors) and a function to print them. This
 *  is used mainly in the development of Rotope objects.
 *
 *  \param D Dimension of the vector space we're working in
 *
 *  \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
template <unsigned D>
    class vertex_data: public Object {

        public:
            void print();           ///< Output of all vertices

        protected:
            /// Create an empty array of vertices.
            /** Only derived classes can create a vertex_data object. */
            vertex_data():
                    Object("Rotope", 0, 0),
                    _dimension(0), _X()/*, _surface() */{
                X().push_back(VecMath::Vector<D>());
            }

            /// Add a surface to the array of surfaces
            void addSurface(unsigned, unsigned, unsigned, unsigned);
            /// Add a surface to the array of surfaces
            void addSurface(unsigned, unsigned, unsigned);

            /// Dimension of the object
            unsigned &dimension() { return _dimension; }
            /// The array of vertices
            std::vector<VecMath::Vector<D> > &X() { return _X; }
            /// The array of surfaces
            uintvec2D &surface() { return _surface; }

        private:
            unsigned _dimension;                    ///< Dimension of the object
            std::vector<VecMath::Vector<D> > _X;    ///< The array of vertices
            uintvec2D _surface;                     ///< The array of surfaces

        friend class Rotope;
    };

/// A four-dimensional <a href="http://teamikaria.com/wiki/Rotope">Rotope</a>.
/** \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
class Rotope : public Object {
    public:
        /// Construct a Rotope. Not yet implemented properly.
        Rotope(const QString &);

        ~Rotope();

        virtual void Transform (const VecMath::Rotation<4> &,
                                const VecMath::Vector<4> &);
        virtual void Draw (void);

    private:
        vertex_data<4> *_rotope;
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
    for(typename vector<Vector<D> >::iterator i = X().begin();
        i != X().end(); ++i){
        std::cerr << separator << *i;
        separator = ", ";
    }
    std::cerr << "\n";

#   if 1
        std::cerr << "Surfaces: \n";
        for (unsigned i = 0; i < surface().size(); ++i) {
            std::cerr << std::setw(4) << i << " (";
            separator = "";
            for (uintvec1D::iterator j = surface()[i].begin();
                 j != surface()[i].end(); ++j) {
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
    if (v1 >= X().size() || v2 >= X().size() ||
        v3 >= X().size() || v4 >= X().size()) {
        std::cerr << "X.size(): " << X().size() << ", v1: " << v1 << ", v2: " << v2
                << ", v3: " << v3 << ", v4: " << v4 << "\n";
        throw std::out_of_range("vertex_data<D>::addSurface(): index larger "
                                "than size of vertex array");
    }

    uintvec1D tmp;
    tmp.push_back(v1); tmp.push_back(v2); tmp.push_back(v3); tmp.push_back(v4);

    surface().push_back(tmp);
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
