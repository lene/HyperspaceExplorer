#ifndef VIEWPOINTLIST_IMPL_H
#define VIEWPOINTLIST_IMPL_H

#include <ViewpointList.h>


template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM >::ViewpointList():
    _elements() {
  _elements.first = VecMath::Vector<N, NUM>();
  _elements.second = ViewpointList<N-1, Nnew, NUM>();
}

/** \param camW Coordinate of camera in the axis along which each Projection occurs.
 */
template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM >::ViewpointList(NUM camW):
    _elements() {
  _elements.first = VecMath::Vector<N, NUM>();
  _elements.first[N-1] = camW;
  _elements.second = ViewpointList<N-1, Nnew, NUM>(camW);
}

template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM >::ViewpointList(
const VecMath::Vector<N, NUM> &head,
const ViewpointList<N-1, Nnew, NUM> &tail):
    _elements(head, tail) { }

/** \param x0 Viewpoint in Projection in first dimension.
 */
template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM > ViewpointList< N, Nnew, NUM >::make(
const VecMath::Vector<N, NUM>   &x0) {
  return ViewpointList<N, Nnew, NUM>(x0);
}

/** \param x0 Viewpoint in Projection in first dimension.
 *  \param x1 Viewpoint in Projection in second dimension.
 */
template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM > ViewpointList< N, Nnew, NUM >::make(
const VecMath::Vector<N, NUM> &x0, const VecMath::Vector<N-1, NUM> &x1) {
    return ViewpointList<N, Nnew, NUM>(x0, make(x1));
}

/** \param x0 Viewpoint in Projection in first dimension.
 *  \param x1 Viewpoint in Projection in second dimension.
 *  \param x2 Viewpoint in Projection in third dimension.
 */
template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM > ViewpointList< N, Nnew, NUM >::make(
const VecMath::Vector<N, NUM> &x0, const VecMath::Vector<N-1, NUM> &x1,
const VecMath::Vector<N-2, NUM> &x2) {
    return ViewpointList<N, Nnew, NUM>(x0, make(x1, x2));
}

/** \param x0 Viewpoint in Projection in first dimension.
 *  \param x1 Viewpoint in Projection in second dimension.
 *  \param x2 Viewpoint in Projection in third dimension.
 *  \param x3 Viewpoint in Projection in fourth dimension.
 */
template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM > ViewpointList< N, Nnew, NUM >::make(
const VecMath::Vector<N, NUM> &x0, const VecMath::Vector<N-1, NUM> &x1,
const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3) {
    return ViewpointList<N, Nnew, NUM>(x0, make(x1, x2, x3));
}

/** \param x0 Viewpoint in Projection in first dimension.
 *  \param x1 Viewpoint in Projection in second dimension.
 *  \param x2 Viewpoint in Projection in third dimension.
 *  \param x3 Viewpoint in Projection in fourth dimension.
 *  \param x4 Viewpoint in Projection in fifth dimension.
 */
template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM > ViewpointList< N, Nnew, NUM >::make(
const VecMath::Vector<N, NUM> &x0, const VecMath::Vector<N-1, NUM> &x1,
const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
const VecMath::Vector<N-4, NUM> &x4) {
    return ViewpointList<N, Nnew, NUM>(x0, make(x1, x2, x3, x4));
}

/** \param x0 Viewpoint in Projection in first dimension.
 *  \param x1 Viewpoint in Projection in second dimension.
 *  \param x2 Viewpoint in Projection in third dimension.
 *  \param x3 Viewpoint in Projection in fourth dimension.
 *  \param x4 Viewpoint in Projection in fifth dimension.
 *  \param x5 Viewpoint in Projection in sixth dimension.
 */
template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM > ViewpointList< N, Nnew, NUM >::make(
const VecMath::Vector<N, NUM> &x0, const VecMath::Vector<N-1, NUM> &x1,
const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5) {
    return ViewpointList<N, Nnew, NUM>(x0, make(x1, x2, x3, x4, x5));
}

/** \param x0 Viewpoint in Projection in first dimension.
 *  \param x1 Viewpoint in Projection in second dimension.
 *  \param x2 Viewpoint in Projection in third dimension.
 *  \param x3 Viewpoint in Projection in fourth dimension.
 *  \param x4 Viewpoint in Projection in fifth dimension.
 *  \param x5 Viewpoint in Projection in sixth dimension.
 *  \param x6 Viewpoint in Projection in seventh dimension.
 */
template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM > ViewpointList< N, Nnew, NUM >::make(
const VecMath::Vector<N, NUM> &x0, const VecMath::Vector<N-1, NUM> &x1,
const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5,
const VecMath::Vector<N-6, NUM> &x6) {
    return ViewpointList<N, Nnew, NUM>(x0, make(x1, x2, x3, x4, x5, x6));
}

/** \param x0 Viewpoint in Projection in first dimension.
 *  \param x1 Viewpoint in Projection in second dimension.
 *  \param x2 Viewpoint in Projection in third dimension.
 *  \param x3 Viewpoint in Projection in fourth dimension.
 *  \param x4 Viewpoint in Projection in fifth dimension.
 *  \param x5 Viewpoint in Projection in sixth dimension.
 *  \param x6 Viewpoint in Projection in seventh dimension.
 *  \param x7 Viewpoint in Projection in eight dimension.
 */
template <unsigned N, unsigned Nnew, typename NUM>
ViewpointList< N, Nnew, NUM > ViewpointList< N, Nnew, NUM >::make(
const VecMath::Vector<N, NUM> &x0, const VecMath::Vector<N-1, NUM> &x1,
const VecMath::Vector<N-2, NUM> &x2, const VecMath::Vector<N-3, NUM> &x3,
const VecMath::Vector<N-4, NUM> &x4, const VecMath::Vector<N-5, NUM> &x5,
const VecMath::Vector<N-6, NUM> &x6, const VecMath::Vector<N-7, NUM> &x7) {
    return ViewpointList<N, Nnew, NUM>(x0, make(x1, x2, x3, x4, x5, x6, x7));
}

#endif