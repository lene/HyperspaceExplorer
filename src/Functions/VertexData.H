#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include "RotopeBase.H"
#include "Projector.H"

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
    class vertex_data: public RotopeBase {

        public:
            virtual void print();           ///< Output of all vertices

            /// Create an empty array of vertices.
            vertex_data():
                    _dimension(0), _X(), _surface() {
                X().push_back(VecMath::Vector<D>());
            }

        protected:
            /// Add a surface to the array of surfaces
            virtual void addSurface(unsigned, unsigned, unsigned, unsigned);
            /// Add a surface to the array of surfaces
            virtual void addSurface(unsigned, unsigned, unsigned);

            /// Dimension of the object
            virtual unsigned &dimension() { return _dimension; }
            /// The array of vertices
            std::vector<VecMath::Vector<D> > &X() { return _X; }
            /// The array of surfaces
            virtual uintvec2D &surface() { return _surface; }
            /// The array of vertices, projected to four dimensions if necessary
            virtual std::vector<VecMath::Vector<4> > vertices();

        private:
            /// \return Whether argument or permutation of it already in _surface
            bool checkSurfaceExists(const uintvec1D &);

            unsigned _dimension;                    ///< Dimension of the object
            std::vector<VecMath::Vector<D> > _X;    ///< The array of vertices
            uintvec2D _surface;                     ///< The array of surfaces

        friend class Rotope;
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
        throw std::out_of_range("vertex_data<D>::addSurface(): index larger "
                                "than size of vertex array");
    }

    uintvec1D tmp;
    tmp.push_back(v1); tmp.push_back(v2); tmp.push_back(v3); tmp.push_back(v4);

    if (!checkSurfaceExists(tmp)) surface().push_back(tmp);
}

/** Overloaded version for three vertices
 *  \param v1 Index (in the vertex array) of the first vertex
 *  \param v2 Index (in the vertex array) of the second vertex
 *  \param v3 Index (in the vertex array) of the third vertex
 */
template <unsigned D> void vertex_data<D>::addSurface(unsigned v1, unsigned v2,
                                                      unsigned v3) {
    if (v1 >= X().size() || v2 >= X().size() || v3 >= X().size()) {
        throw std::out_of_range("vertex_data<D>::addSurface(): index larger "
                                "than size of vertex array");
    }

    uintvec1D tmp;
    tmp.push_back(v1); tmp.push_back(v2); tmp.push_back(v3);
    if (!checkSurfaceExists(tmp)) surface().push_back(tmp);
}

/** Test if a new surface is a permutation of a surface already existing.
 *  \param newSurface The surface to be tested whether it is already stored
 */
template <unsigned D> bool vertex_data<D>::checkSurfaceExists(const uintvec1D &newSurface) {

    for (unsigned i = 0; i < surface().size(); ++i) {

        /// Check for equality against every surface in \p _surface .

        vector<bool> found_equal_vertex(surface()[i].size());

        for (unsigned j = 0; j < surface()[i].size(); ++j) {
            found_equal_vertex[j] = false;
            for (unsigned k = 0; k < newSurface.size(); ++k) {
                if (surface()[i][j] == newSurface[k]) {
                    found_equal_vertex[j] = true;
                }
            }
        }
        bool surfaces_are_equal = true;

        /** Because the corners of a surface are all different numbers, if we
         *  found an equal vertex for each corner, the surface is considered
         *  equal.
         *
         *  That algorithm breaks down if there are surfaces which are odd
         *  permutations of existing surfaces, eg. (0, 1, 3, 2), (0, 1, 2, 3).
         *  I don't think such permutations make sense, as the edges of the
         *  surface would be self-intersecting.
         */
        for (unsigned i = 0; i < found_equal_vertex.size();
             surfaces_are_equal &= found_equal_vertex[i++]) ;
        if (surfaces_are_equal) return true;
    }
    return false;
}

template <unsigned D>
    std::vector<VecMath::Vector<4> > vertex_data<D>::vertices() {
        Projector<D, 4> p;
        return p(X(), 2., 4.);  /// \todo This is hardcoded! Ugh!
    }

#endif
