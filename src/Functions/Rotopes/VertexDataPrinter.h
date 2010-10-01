/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef _VERTEXDATAPRINTER_H
#define _VERTEXDATAPRINTER_H

#include "VertexData.h"

#include "Vector.impl.h"

#include <iomanip>
#include <algorithm>

template <unsigned D>
    void VertexData<D>::VertexDataPrinter::printToStream(std::ostream &out) const {

    out << std::string(PRINT_VERTICES_NUM_COLUMNS*PRINT_VERTICES_COLUMN_WIDTH, '-')
        << std::endl;
    out << _vertexData->dimension() << "-dimensional object";

    out << "\n" << _vertexData->realm().size() << " realms: \n";
    for (Realm::realm_container_type::const_iterator it = _vertexData->realm().begin();
         it != _vertexData->realm().end(); ++it) {
      out << it->toString() << " ";
    }
    out << "\n";

    out << verticesToString(PRINT_VERTICES_NUM_COLUMNS);

    out << std::string(PRINT_VERTICES_NUM_COLUMNS*PRINT_VERTICES_COLUMN_WIDTH, '-')
        << std::endl;
}

template <unsigned D>
    std::string VertexData<D>::VertexDataPrinter::verticesToString(
        unsigned num_columns) const {

    std::ostringstream vertices_outstream;

    printVertices(num_columns, vertices_outstream);
    vertices_outstream << std::ends;

    return vertices_outstream.str();
}

template <unsigned D>
    void VertexData<D>::VertexDataPrinter::printVertices(unsigned num_columns,
                                                         std::ostream &out) const {
    for (unsigned i = 0; i < _vertexData->raw_vertices().size(); i += num_columns) {
        out << verticesToStringRow(i, num_columns) << std::endl;
    }
}


template <unsigned D>
    std::string VertexData<D>::VertexDataPrinter::verticesToStringRow(
        unsigned base_index, unsigned num_columns) const {

    std::ostringstream column_outstream;

    printVerticesRow(base_index, num_columns, column_outstream);
    column_outstream << std::ends;

    return column_outstream.str();
}

template <unsigned D>
    void VertexData<D>::VertexDataPrinter::printVerticesRow(unsigned base_index,
                                                            unsigned num_columns,
                                                            std::ostream& out) const {
    const unsigned PRINT_VERTICES_INDEX_WIDTH = 5;

    for (unsigned column = 0; column < num_columns; ++column) {

        if (base_index+column >= _vertexData->raw_vertices().size()) break;

        std::string vec_as_string = _vertexData->raw_vertices()[base_index+column].toString();

        int fill_width = PRINT_VERTICES_COLUMN_WIDTH-PRINT_VERTICES_INDEX_WIDTH-2-vec_as_string.length(),
            num_fill_chars = std::max(0, fill_width);

        out << std::setw(PRINT_VERTICES_INDEX_WIDTH) << base_index+column << ": "
            << vec_as_string
            << std::string(num_fill_chars, ' ');
    }

}


#endif	/* _VERTEXDATAPRINTER_H */
