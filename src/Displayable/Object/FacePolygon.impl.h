/* 
 * File:   SurfaceType.impl.h
 * Author: lene
 *
 * Created on December 18, 2011, 5:07 PM
 */

#ifndef SURFACETYPE_IMPL_H
#define	SURFACETYPE_IMPL_H

#include "FacePolygon.h"

#include <QDebug>

#include "Util.h"
#include "ArrayList.impl.h"

template <unsigned D, unsigned N_vertex> 
FacePolygon<D, N_vertex>::FacePolygon() { 
    for (unsigned i = 0; i < N_vertex; _vertices[i++] = 0) ; 
}

template <unsigned D, unsigned N_vertex> 
FacePolygon<D, N_vertex>::FacePolygon(
        const VecMath::MultiDimensionalVector< vertex_type, 1 > &original_container,
        const vertex_type &v0, const vertex_type &v1,
        const vertex_type &v2) { 
    _vertices[0] = &v0; _indices[0] = index_of(v0, original_container);
    _vertices[1] = &v1; _indices[1] = index_of(v1, original_container);
    _vertices[2] = &v2; _indices[2] = index_of(v2, original_container);
    for (unsigned i = 3; i < N_vertex; ++i) {
        _vertices[i] = 0;
        _indices[i] = 0;
    }
}

template <unsigned D, unsigned N_vertex> 
FacePolygon<D, N_vertex>::FacePolygon(
        const VecMath::MultiDimensionalVector< vertex_type, 1 > &original_container,
        const vertex_type &v0, const vertex_type &v1,
                const vertex_type &v2, const vertex_type &v3) {
      _vertices[0] = &v0; _indices[0] = index_of(v0, original_container);
      _vertices[1] = &v1; _indices[1] = index_of(v1, original_container);
      _vertices[2] = &v2; _indices[2] = index_of(v2, original_container);
      _vertices[3] = &v3; _indices[3] = index_of(v3, original_container);
      for (unsigned i = 4; i < N_vertex; ++i) {
        _vertices[i] = 0;
        _indices[i] = 0;
      }
    }

template <unsigned D, unsigned N_vertex> 
const typename FacePolygon<D, N_vertex>::vertex_ptr_type &
FacePolygon<D, N_vertex>::operator[](unsigned i) const { 
    return _vertices[i]; 
}

template <unsigned D, unsigned N_vertex> 
unsigned
FacePolygon<D, N_vertex>::index(unsigned i) const { 
    return _indices[i];
}

template <unsigned D, unsigned N_vertex> 
bool
FacePolygon<D, N_vertex>::operator==(const FacePolygon<D, N_vertex> &other) const {
    if (!isPermutation(
        ArrayList<N_vertex, unsigned>(_indices), 
        ArrayList<N_vertex, unsigned>(other._indices))) {
        return false;
    }
    print(); std::cerr << " == "; other.print(); std::cerr << "?\n";
    unsigned associated_index[N_vertex];
    for (unsigned i = 0; i < N_vertex; ++i) {
      for (unsigned j = 0; j < N_vertex; ++j) {
        if (other._indices[j] == _indices[i]) {
          associated_index[i] = j;
          break;
        }
      }
    }
    for (unsigned i = 0; i < N_vertex; ++i) {
      std::cerr << i << ": " << *_vertices[i] << " == " 
                << associated_index[i] << ": " << *other._vertices[associated_index[i]] << "?\n";
      if (*_vertices[i] != *other._vertices[associated_index[i]]) return false;
    }
    return true;
}

template <unsigned D, unsigned N_vertex> 
void
FacePolygon<D, N_vertex>::print() const {
    for (unsigned i = 0; i < N_vertex; ++i)
        std::cerr << _indices[i] << ": " << *(_vertices[i]) << " ";
    std::cerr << std::endl;
}

template <unsigned D, unsigned N_vertex> 
unsigned
FacePolygon<D, N_vertex>::index_of(
        const vertex_type &x,
        const VecMath::MultiDimensionalVector< vertex_type, 1 > &original_container) {
    // assuming that more surfaces have vertices that have just been added
    // to the end of original_container
    for (int i = original_container.size()-1; i >= 0; --i) {
        if (original_container[i] == x) return i;
    }
    throw std::logic_error("SurfaceType::index_of(): Tried to find the index of a vertex that was not in the container");
}


#endif	/* SURFACETYPE_IMPL_H */

