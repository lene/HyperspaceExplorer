#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include "RotopeBase.H"
#include "Projector.H"

//  utility functions
    
/// Print a std::vector on a std::ostream
/** \param s The ostream to which \p v is sent
 *  \param v The vector to print
 *  \return \p s
 */
template<typename T> std::ostream& operator<<(std::ostream& s, 
                                              std::vector<T> const& v) {
    s << "(";
    copy(v.begin(), v.end(), std::ostream_iterator<T>(s, " "));
    s << ")";
    return s;
}

/// Find an element in a vector
/** \param find_me The element to find in the vector \p v
 *  \param v The vector to search for element \p find_me
 *  \return The \p vector<T>::iterator pointing to the element or \p v.end() if it is not in \p v
 */
template <typename T> typename std::vector<T>::iterator find(T find_me, std::vector<T> &v) {
    typename std::vector<T>::iterator i = v.begin();
    while(*i != find_me && i != v.end()) ++i;
    return i;
}

/// Base class for all Rotope s.
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

        protected:
            /// Create an empty array of vertices.
            vertex_data(): _dimension(0), _X(), _surface(), _transform() {
                X().push_back(VecMath::Vector<D>());
            }
            /// Add a quadrilateral surface to the array of surfaces
            virtual void addSurface(unsigned, unsigned, unsigned, unsigned);
            /// Add a triangular surface to the array of surfaces
            virtual void addSurface(unsigned, unsigned, unsigned);
            /// Add a polygonal surface to the array of surfaces
            virtual void addSurface(const std::vector<unsigned> &);
            /// Remove a surface by giving its index in the surface array
            virtual void removeSurface(const std::vector<unsigned> &);

            /// Perform a \p D -dimensional transformation
            virtual void addTransform(unsigned, const VecMath::RotationBase *);

            /// Actual dimension of the object (in contrast to the vector space)
            virtual unsigned &dimension() { return _dimension; }
            /// The array of vertices
            std::vector<VecMath::Vector<D> > &X() { return _X; }
            /// The array of surfaces
            virtual uintvec2D &surface() { return _surface; }
            /// The array of vertices, projected to four dimensions if necessary
            virtual std::vector<VecMath::Vector<4> > vertices();

            /// Output of a single surface
            void printSurface(const uintvec1D &);

        private:
            /// \return Whether argument or permutation of it already in _surface
            bool checkSurfaceExists(const uintvec1D &);

            unsigned _dimension;                    ///< Dimension of the object
            std::vector<VecMath::Vector<D> > _X;    ///< The array of vertices
            uintvec2D _surface;                     ///< The array of surfaces

            /// List of transformations executed on the object in dimensions > 4
            std::vector<const VecMath::RotationBase *> _transform;

            /// Allow RotopeFactory free access to create vertex_data objects
            friend class RotopeFactory;
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

/** \param v The printed surface as vector of indices into the vertex array */
template <unsigned D> void vertex_data<D>::printSurface(const uintvec1D &v) {
    std::cerr << " (";
    std::string separator = "";
    for (uintvec1D::const_iterator j = v.begin();
         j != v.end(); ++j) {
        std::cerr << separator << std::setw(4) << *j;
        separator = ", ";
    }
    std::cerr << ")\n";
}

template <unsigned D> void vertex_data<D>::print() {
    std::cerr << _dimension << "-dimensional object: ";
    std::string separator = "";
#   if DEBUG_ROTOPE
    std::cerr << X().size() << " vertices\n";
    unsigned count = 0;
    for (typename vector<Vector<D> >::iterator i = X().begin();
         i != X().end(); ++i, count++){
        separator = "\n";
        std::cerr << count << ": " << *i << separator;
    }
    std::cerr << "\n";
#   endif

#   if DEBUG_ROTOPE
        std::cerr << surface().size() << " surfaces: \n";
        for (unsigned i = 0; i < surface().size(); ++i) {
            std::cerr << std::setw(4) << i;
            printSurface(surface()[i]);
        }
        std::cerr << "\n";
#   endif

}

/** Add a surface to the array of surfaces
 *  \param v List of indices in the vertex array
 */
template <unsigned D> void vertex_data<D>::addSurface(const std::vector<unsigned> & v) {
    for (unsigned i = 0; i < v.size(); ++i) {
        if (v[i] >= X().size()) {
            throw std::out_of_range("vertex_data<D>::addSurface(): index larger "
                    "than size of vertex array");
        }
    }

    if (!checkSurfaceExists(v)) {
#       if DEBUG_ROTOPE
            std::cerr << "addSurface" << v<< "\n";
#       endif
        surface().push_back(v);
    }
}

/** Overloaded version for 4 vertices
 *  \param v1 Index (in the vertex array) of the first vertex
 *  \param v2 Index (in the vertex array) of the second vertex
 *  \param v3 Index (in the vertex array) of the third vertex
 *  \param v4 Index (in the vertex array) of the fourth vertex
 */
template <unsigned D> void vertex_data<D>::addSurface(unsigned v1, unsigned v2,
                                                      unsigned v3, unsigned v4) {
    /// If rectangle is degenerate, add a triangle
    if (v1 == v2 || v1 == v3 || v1 == v4) addSurface(v2, v3, v4);
    else if (v2 == v3 || v2 == v4) addSurface(v1, v3, v4);
    else if (v3 == v4) addSurface(v1, v2, v4);
    else {
        uintvec1D tmp;
        tmp.push_back(v1); tmp.push_back(v2); tmp.push_back(v3); tmp.push_back(v4);
        addSurface(tmp);
    }
}

/** Overloaded version for three vertices
 *  \param v1 Index (in the vertex array) of the first vertex
 *  \param v2 Index (in the vertex array) of the second vertex
 *  \param v3 Index (in the vertex array) of the third vertex
 */
template <unsigned D> void vertex_data<D>::addSurface(unsigned v1, unsigned v2,
                                                      unsigned v3) {
    /// If triangle is degenerate, do nothing
    if (v1 == v2 || v1 == v3 || v2 == v3) return;
    uintvec1D tmp;
    tmp.push_back(v1); tmp.push_back(v2); tmp.push_back(v3);

    addSurface(tmp);
}

/** \param remove_me Index (in the surface array) of the surface to be removed
 */
template <unsigned D> void vertex_data<D>::removeSurface(const std::vector<unsigned> &remove_me) {
    uintvec2D::iterator i = find(remove_me, surface());
    if (i != surface().end()) surface().erase(i);
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
//        Transform(VecMath::Rotation<D>(), VecMath::Vector<D>());
        Projector<D, 4> p;
        return p(X(), 2., 8.);  /// \todo This is hardcoded! Ugh!
    }

/*template <unsigned D>
    void vertex_data<D>::Transform(const VecMath::Rotation<D> &R,
                                   const VecMath::Vector<D> &T) {
        VecMath::Matrix<D> Rot(R);
        / *
        std::cerr << R << "\n"
                << Rot << "\n";
        * /
        for(unsigned i = 0; i < _X.size(); ++i){
            _X[i] = Rot*_X[i]+T;
        }
    }
*/
/** \param R Rotation component of the transformation
 *  \param d Dimension on which the transform acts
 */
template <unsigned D>
    void vertex_data<D>::addTransform(unsigned d,
                                      const VecMath::RotationBase *R) {
    std::cerr << "vertex_data<" << D << ">::addTransform("
            << d << ", " << typeid(R).name() << ")\n";
    _transform.resize(d+1);
    _transform[d] = R;
}

#endif
