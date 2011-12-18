/* 
 * File:   SurfaceType.impl.h
 * Author: lene
 *
 * Created on December 18, 2011, 5:07 PM
 */

#ifndef SURFACETYPE_IMPL_H
#define	SURFACETYPE_IMPL_H

#include "SurfaceType.h"

#include "Util.h"
#include <QDebug>

template <unsigned D, unsigned N_vertex> 
SurfaceType<D, N_vertex>::SurfaceType() { 
    for (unsigned i = 0; i < N_vertex; _vertices[i++] = 0) ; 
}

template <unsigned D, unsigned N_vertex> 
SurfaceType<D, N_vertex>::SurfaceType(
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
SurfaceType<D, N_vertex>::SurfaceType(
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
const typename SurfaceType<D, N_vertex>::vertex_ptr_type &
SurfaceType<D, N_vertex>::operator[](unsigned i) const { 
    return _vertices[i]; 
}

template <unsigned D, unsigned N_vertex> 
unsigned
SurfaceType<D, N_vertex>::index(unsigned i) const { 
    return _indices[i];
}

template <unsigned D, unsigned N_vertex> 
bool
SurfaceType<D, N_vertex>::operator==(const SurfaceType<D, 4> &other) const {
    if (N_vertex != 4) return false;
    if (!Util::isPermutation(
          _indices[0], _indices[1], _indices[2], _indices[3],
          other._indices[0], other._indices[1], other._indices[2], other._indices[3])) {
        return false;
    }
    return (_vertices[0] == other._vertices[0] &&
              _vertices[1] == other._vertices[1] &&
              _vertices[2] == other._vertices[2] &&
              _vertices[3] == other._vertices[3]);
}

template <unsigned D, unsigned N_vertex> 
void
SurfaceType<D, N_vertex>::print() {
    for (unsigned i = 0; i < N_vertex; ++i)
        std::cerr << _indices[i] << ": " << *(_vertices[i]) << " ";
    std::cerr << std::endl;
}

template <unsigned D, unsigned N_vertex> 
unsigned
SurfaceType<D, N_vertex>::index_of(
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

