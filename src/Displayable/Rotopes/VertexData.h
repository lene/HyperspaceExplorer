/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2009-2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include "RotopeInterface.h"
#include "Projector.h"

#include <typeinfo>

/// Base class for all Rotope s.
/** Contains an array of vertices (Vectors) and a function to print them. This
 *  is used mainly in the development of Rotope objects.
 *
 *  \tparam D Dimension of the vector space we're working in
 *
 *  \todo transforming rotopes, allowing for rotation in \p D dimensions and
 *      scaling.
 *
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
template <unsigned D>
    class VertexData: public RotopeInterface {

        /// Hardcoded screen distance for generation of the Projection in projected_vertices().
        /** \todo un-hardcode this (configure from Rotope)
         */
        static constexpr double PROJECTION_SCREEN_W = 2.;
        /// Hardcoded camera w coordinate for generation of the Projection in projected_vertices().
        /** \todo un-hardcode this (configure from Rotope)
         */
        static constexpr double PROJECTION_CAMERA_W = 8.;

    public:

        /// The array of realms (D-1 dimensional surfaces of D-dimensional object)
        virtual Realm &realm() { return _realm; }
        /// The array of realms (D-1 dimensional surfaces of D-dimensional object)
        virtual const Realm &realm() const { return _realm; }

        /// Read-only access to the list of vertices managed by this object
        const std::vector<VecMath::Vector<D> > &raw_vertices() const { return _raw_vertices; }
        virtual std::vector<VecMath::Vector<4> > projected_vertices();

        virtual unsigned dimension() const { return _dimension; }
        virtual unsigned &dimension() { return _dimension; }

        /// String representation.
        virtual std::string toString();


    protected:

        /// Default c'tor. VertexData objects can only be initialized in derived classes.
        VertexData(): _dimension(0), _raw_vertices(), _transform() {
            raw_vertices().push_back(VecMath::Vector<D>());
        }

        /// Perform a \p D -dimensional transformation
        virtual void addTransform(unsigned, const VecMath::RotationBase *);

        /// Read/write access to the list of vertices managed by this object
        std::vector<VecMath::Vector<D> > &raw_vertices() { return _raw_vertices; }
        /// Write access to the list of vertices managed by this object
        void set_raw_vertices(const std::vector<VecMath::Vector<D> > &new_vertices) {
            _raw_vertices = new_vertices;
        }

    private:

        unsigned _dimension;                    ///< Dimension of the object

        std::vector<VecMath::Vector<D> > _raw_vertices;    ///< The array of vertices

        /// The array of realms (D-1 dimensional surfaces of D-dimensional object)
        Realm _realm;

        /// List of transformations executed on the object in dimensions > 4
        std::vector<const VecMath::RotationBase *> _transform;

        /// Auxiliary class encapsulating printing and conversion to std::string.
        /** \todo This class is still a little chaotic. */
        class VertexDataPrinter {

            /// How many characters fit in a column.
            const static int PRINT_VERTICES_COLUMN_WIDTH = 40;
            /// In how many columns the output is ordered.
            const static int PRINT_VERTICES_NUM_COLUMNS = 2;

        public:

            /// Initializes a VertexDataPrinter with a VertexData object.
            VertexDataPrinter(VertexData *vertexData):
                _vertexData(vertexData) { }

            /// Prints the VertexData object on stream \p out.
            void printToStream(std::ostream &out) const;

        private:

            /// Returns all vertices as a string, sorted in \c num_columns columns.
            std::string verticesToString(unsigned num_columns) const;

            /// Print vertices to an arbitrary std::ostream.
            void printVertices(unsigned num_columns = PRINT_VERTICES_NUM_COLUMNS,
                               std::ostream &out = std::cout) const;

            /// Returns a line of \p num_columns vertices as string.
            /** \param base_index Index of the first vertex that is printed.
             *  \param num_columns How many vertices are printed in this row.
             */
            std::string verticesToStringRow(unsigned base_index, unsigned num_columns) const;

            /// Prints a line of \p num_columns vertices on \p out.
            void printVerticesRow(unsigned base_index,
                                  unsigned num_columns = PRINT_VERTICES_NUM_COLUMNS,
                                  std::ostream &out = std::cout) const;

            /// The VertexData object that is printed.
            VertexData *_vertexData;
        };

    /// Allow RotopeFactory free access to create VertexData objects
    friend class RotopeFactory;
    };

/*  You shouldn't use "using" directives in a header file, but the code gets
    nearly unreadable otherwise. I mean, just look at that:
    typename std::vector<VecMath::Vector<D> >::iterator i = _X.begin();
    And because I'm defining template classes here, code must be written in the
    header file anyway.
*/
using VecMath::Vector;
using std::vector;

#include "VertexDataPrinter.h"

template <unsigned D> std::string VertexData<D>::toString() {
    std::ostringstream o;
    VertexDataPrinter printer(this);
    printer.printToStream(o);
    o << std::ends;
    return o.str();
}


template <unsigned D>
    std::vector<VecMath::Vector<4> > VertexData<D>::projected_vertices() {
//        Transform(VecMath::Rotation<D>(), VecMath::Vector<D>());
        Projector<D, 4> p;
        return p(raw_vertices(), PROJECTION_SCREEN_W, PROJECTION_CAMERA_W);  /// \todo This is hardcoded! Ugh!
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
