#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include "RotopeInterface.h"
#include "Projector.h"

#include <typeinfo>

/// Base class for all Rotope s.
/** Contains an array of vertices (Vectors) and a function to print them. This
 *  is used mainly in the development of Rotope objects.
 *
 *  \param D Dimension of the vector space we're working in
 *
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
template <unsigned D>
    class VertexData: public RotopeInterface {

        const static double PROJECTION_SCREEN_W = 2.;
        const static double PROJECTION_CAMERA_W = 8.;

    public:
        /// The array of realms
        virtual Realm &realm() { return _realm; }
        /// The array of vertices, projected to four dimensions if necessary
        virtual std::vector<VecMath::Vector<4> > vertices();

        virtual std::string toString();

    protected:
        /// Create an empty array of vertices.
        VertexData(): _dimension(0), _X(), _transform() {
            X().push_back(VecMath::Vector<D>());
        }

        /// Perform a \p D -dimensional transformation
        virtual void addTransform(unsigned, const VecMath::RotationBase *);

        /// Actual dimension of the object (in contrast to the vector space)
        virtual unsigned &dimension() { return _dimension; }
        /// The array of vertices
        std::vector<VecMath::Vector<D> > &X() { return _X; }
        const std::vector<VecMath::Vector<D> > &X() const { return _X; }


    private:
        /// Returns all vertices as a string, sorted in \c num_columns columns.
        std::string verticesToString(unsigned num_columns) const;

        const static int PRINT_VERTICES_COLUMN_WIDTH = 40;
        const static int PRINT_VERTICES_NUM_COLUMNS = 2;

        void printToStream(std::ostream &out);
        
        void printVertices(unsigned num_columns = PRINT_VERTICES_NUM_COLUMNS,
                           std::ostream &out = std::cout) const;

        /// Returns a line of \p num_columns vertices as string.
        /** \param base_index Index of the first vertex that is printed.
         *  \param num_columns How many vertices are printed in this row.
         */
        std::string verticesToStringRow(unsigned base_index, unsigned num_columns) const;

        void printVerticesRow(unsigned base_index,
                              unsigned num_columns = PRINT_VERTICES_NUM_COLUMNS,
                              std::ostream &out = std::cout) const;

        unsigned _dimension;                    ///< Dimension of the object
        std::vector<VecMath::Vector<D> > _X;    ///< The array of vertices
        /// The array of realms (D-1 dimensional surfaces of D-dimensional object)
        Realm _realm;

        /// List of transformations executed on the object in dimensions > 4
        std::vector<const VecMath::RotationBase *> _transform;

        /// Allow RotopeFactory free access to create vertex_data objects
        friend class RotopeFactory;
    };

/*  You shouldn't use "using" directives in a header file, but the code gets
    nearly unreadable otherwise. I mean, look at that:
    typename std::vector<VecMath::Vector<D> >::iterator i = _X.begin();
    And because I'm defining template classes here, code must be written in the
    header file anyway.
*/
using VecMath::Vector;
using VecMath::uintvec;
using std::vector;

#include <iomanip>
#include <algorithm>

template <unsigned D> std::string VertexData<D>::toString() {
    std::ostringstream o;
    printToStream(o);
    o << std::ends;
    return o.str();
}

template <unsigned D> void VertexData<D>::printToStream(std::ostream &out) {

    out << std::string(PRINT_VERTICES_NUM_COLUMNS*PRINT_VERTICES_COLUMN_WIDTH, '-')
        << std::endl;
    out << _dimension << "-dimensional object";

    out << "\n" << realm().size() << " realms: \n";
    std::copy(realm().begin(), realm().end(),
              std::ostream_iterator<std::string>(out, " "));
    out << "\n";

    out << verticesToString(PRINT_VERTICES_NUM_COLUMNS);

    out << std::string(PRINT_VERTICES_NUM_COLUMNS*PRINT_VERTICES_COLUMN_WIDTH, '-')
        << std::endl;
}

template <unsigned D> std::string VertexData<D>::verticesToString(
        unsigned num_columns) const {

    std::ostringstream vertices_outstream;

    printVertices(num_columns, vertices_outstream);
    vertices_outstream << std::ends;

    return vertices_outstream.str();
}

template <unsigned D> void VertexData<D>::printVertices(unsigned num_columns,
                                                         std::ostream &out) const {
    for (unsigned i = 0; i < X().size(); i += num_columns) {
        out << verticesToStringRow(i, num_columns) << std::endl;
    }
}


template <unsigned D> std::string VertexData<D>::verticesToStringRow(
        unsigned base_index, unsigned num_columns) const {

    std::ostringstream column_outstream;

    printVerticesRow(base_index, num_columns, column_outstream);
    column_outstream << std::ends;

    return column_outstream.str();
}

template <unsigned D> void VertexData<D>::printVerticesRow(unsigned base_index,
                                                            unsigned num_columns,
                                                            std::ostream& out) const {
    const unsigned PRINT_VERTICES_INDEX_WIDTH = 5;

    for (unsigned column = 0; column < num_columns; ++column) {

        if (base_index+column >= X().size()) break;

        std::string vec_as_string = X()[base_index+column].toString();

        int fill_width = PRINT_VERTICES_COLUMN_WIDTH-PRINT_VERTICES_INDEX_WIDTH-2-vec_as_string.length(),
            num_fill_chars = std::max(0, fill_width);

        out << std::setw(PRINT_VERTICES_INDEX_WIDTH) << base_index+column << ": "
            << vec_as_string
            << std::string(num_fill_chars, ' ');
    }
    
}

template <unsigned D>
    std::vector<VecMath::Vector<4> > VertexData<D>::vertices() {
//        Transform(VecMath::Rotation<D>(), VecMath::Vector<D>());
        Projector<D, 4> p;
        return p(X(), PROJECTION_SCREEN_W, PROJECTION_CAMERA_W);  /// \todo This is hardcoded! Ugh!
    }

/** \param R Rotation component of the transformation
 *  \param d Dimension on which the transform acts
 */
template <unsigned D>
    void VertexData<D>::addTransform(unsigned d,
                                      const VecMath::RotationBase *R) {
    std::cerr << "vertex_data<" << D << ">::addTransform("
            << d << ", " << typeid(R).name() << ")\n";
    _transform.resize(d+1);
    _transform[d] = R;
}

#endif
