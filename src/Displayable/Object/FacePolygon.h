/* 
 * File:   FacePolygon.h
 * Author: lene
 *
 * Created on December 18, 2011, 3:38 PM
 */

#ifndef FACEPOLYGON_H
#define	FACEPOLYGON_H

#include "MultiDimensionalVector.h"
#include "Vector.h"

#if USE_INT_INDICES
typedef VecMath::uintvec<2> surface_vec_type;
#else
/// Defines a surface element in \p D -space.
/**
 *  \tparam D Dimension of vector space the surface is defined in.
 *  \tparam N_vertex Number of vertices per surface element / polygon.
 */
template <unsigned D, unsigned N_vertex> class FacePolygon {

public:

    /// The type of the \p D -dimensional vertices.
    typedef VecMath::Vector<D> vertex_type;
    /// Pointer to vertex_type.
    typedef const vertex_type * vertex_ptr_type;

    /// Construct an empty SurfaceType.
    FacePolygon();

    /// Construct a SurfaceType with a vertex array and three vertices.
    FacePolygon(const VecMath::MultiDimensionalVector< vertex_type, 1 > &original_container,
                const vertex_type &v0, const vertex_type &v1,
                const vertex_type &v2);
    
    /// Construct a SurfaceType with a vertex array and four vertices.
    FacePolygon(const VecMath::MultiDimensionalVector< vertex_type, 1 > &original_container,
                const vertex_type &v0, const vertex_type &v1,
                const vertex_type &v2, const vertex_type &v3);
    
    /// Returns the \p i -th vertex.
    const vertex_ptr_type &operator[](unsigned i) const;

    /// Returns the \p i -th index into the vertices array.
    unsigned index(unsigned i) const;

    /// Preliminary version, only for N_vertex = 4
    bool operator==(const FacePolygon<D, N_vertex> &other) const;
    bool operator!=(const FacePolygon<D, N_vertex> &other) const { return !(*this == other); }
    /// Debugging output
    void print() const;
    
private:
      /// a version of std::find() that returns an index instead of an iterator
      static unsigned index_of(const vertex_type &x,
                               const VecMath::MultiDimensionalVector< vertex_type, 1 > &original_container);
      
      /// Array of vertices the Surface consists of
      vertex_ptr_type _vertices[N_vertex];

      /// Array of indices pointing into _vertices.
      unsigned _indices[N_vertex];
};

typedef std::vector< FacePolygon<4, 4> > surface_vec_type;
#endif

#endif	/* FACEPOLYGON_H */
