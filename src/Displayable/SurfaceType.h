/* 
 * File:   SurfaceType.h
 * Author: lene
 *
 * Created on December 18, 2011, 3:38 PM
 */

#ifndef SURFACETYPE_H
#define	SURFACETYPE_H

#include "Util.h"
 #include <QDebug>

#if USE_INT_INDICES
typedef VecMath::uintvec<2> surface_vec_type;
#else
/// Defines a surface element in \p D -space.
/**
 *  \tparam D Dimension of vector space the surface is defined in.
 *  \tparam N_vertex Number of vertices per surface element / polygon.
 */
template <unsigned D, unsigned N_vertex> class SurfaceType {

  public:

    /// The type of the \p D -dimensional vertices.
    typedef VecMath::Vector<D> vertex_type;
    /// Pointer to vertex_type.
    typedef const vertex_type * vertex_ptr_type;

    /// Construct an empty SurfaceType.
    SurfaceType() { for (unsigned i = 0; i < N_vertex; _vertices[i++] = 0) ; }

    /// Construct a SurfaceType with a vertex array and three vertices.
    SurfaceType(const std::vector<vertex_type> &original_container,
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

    /// Construct a SurfaceType with a vertex array and four vertices.
    SurfaceType(const std::vector<vertex_type> &original_container,
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

    /// Returns the \p i -th vertex.
    const vertex_ptr_type &operator[](unsigned i) const { return _vertices[i]; }

    /// Returns the \p i -th index into the vertices array.
    unsigned index(unsigned i) const { return _indices[i]; }

    /// Preliminary version, only for N_vertex = 4
    bool operator==(const SurfaceType<D, 4> &other) const {
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

    /// Debugging output
    void print() {
      for (unsigned i = 0; i < N_vertex; ++i)
        std::cerr << _indices[i] << ": " << *(_vertices[i]) << " ";
      std::cerr << std::endl;
    }

    private:
      /// a version of std::find() that returns an index instead of an iterator
      static unsigned index_of(const vertex_type &x,
                               const std::vector<vertex_type> &original_container) {
        // assuming that more surfaces have vertices that have just been added
        // to the end of original_container
        for (int i = original_container.size()-1; i >= 0; --i) {
          if (original_container[i] == x) return i;
        }
        throw std::logic_error("SurfaceType::index_of(): Tried to find the index of a vertex that was not in the container");
      }

      /// Array of vertices the Surface consists of
      /** \todo why not a vector or something?
       */
      vertex_ptr_type _vertices[N_vertex];

      /// Array of indices pointing into _vertices.
      /** \todo why not a vector or something?
       */
      unsigned _indices[N_vertex];
};

typedef std::vector< SurfaceType<4, 4> > surface_vec_type;
#endif

#endif	/* SURFACETYPE_H */

