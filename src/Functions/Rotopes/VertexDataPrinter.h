/* 
 * File:   VertexDataPrinter.h
 * Author: lene
 *
 * Created on February 27, 2010, 5:32 PM
 */

#ifndef _VERTEXDATAPRINTER_H
#define	_VERTEXDATAPRINTER_H

#include "VertexData.h"

#include <iomanip>
#include <algorithm>

template <unsigned D>
    void VertexData<D>::VertexDataPrinter::printToStream(std::ostream &out) const {

    out << std::string(PRINT_VERTICES_NUM_COLUMNS*PRINT_VERTICES_COLUMN_WIDTH, '-')
        << std::endl;
    out << _vertexData->dimension() << "-dimensional object";

    out << "\n" << _vertexData->realm().size() << " realms: \n";
    std::copy(_vertexData->realm().cbegin(), _vertexData->realm().cend(),
              std::ostream_iterator<std::string>(out, " "));
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
