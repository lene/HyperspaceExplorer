/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
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

#include "Rotation.h"

namespace VecMath {

/** Compute the row/column in a rotation Matrix from the dimension
 *  of the vector space and the position of the rotation angle in
 *  the Rotation vector.
 *  \param which 0 for \p ii or 1 for \p jj
 *  \param index position in the Rotation vector                  
 */
template <unsigned D> 
unsigned RotationAxes<D>::axis(unsigned which, unsigned index) {
  throw NotYetImplementedException("RotationAxes<"+Util::itoa(D)+">::axis("+
                                   Util::itoa(which)+", "+Util::itoa(index)+")");
}
  
template <unsigned D, typename N> 
Rotation<D, N>::Rotation(): axis() { }
  
/** \param r0  angle about first rotation axis
 *  \param ... angle about the other axes                         
 */
template <unsigned D, typename N> 
Rotation<D, N>::Rotation (N r0, ... ): axis() {
        
  axis[0] = r0;
  va_list argp;
  va_start (argp, r0);
  for (unsigned i = 1; i < NumAxes<D>::num; i++) {
    axis[i] = va_arg (argp, N);
  }
  va_end (argp);
}
/** \param i index of the element
 *  \return non-const reference to the accessed element           
 */
template <unsigned D, typename N>
N &Rotation<D, N>::operator[] (unsigned i) {
  assert(i < NumAxes<D>::num);
  return axis[i];
}

/** \param i index of the element
 *  \return the accessed element                                  
 */
template <unsigned D, typename N>
N Rotation<D, N>::operator[] (unsigned i) const {
  assert(i < NumAxes<D>::num);
  return axis[i];
}

/** \todo default implementation does not work correctly yet
 *  \todo move out of the class 
 *  \see the specializations for 3 and 4 dimensions in Rotation.C 
 */
template <unsigned D, typename N> 
Rotation<D, N>::operator Matrix<D, N>() const {
  Matrix<D, N> R;
  for (unsigned i = 0; i < NumAxes<D>::num; i++) {
    if (operator[](i)) {
      R *= Matrix<D, N>(RotationAxes<D>::axis(0, i),
                        RotationAxes<D>::axis(1, i),
                        operator[](i));
    }
  }
  return R;
}

/** \param that other Rotation
 *  \return \c *this+that
 */
template <unsigned D, typename N>
Rotation<D, N> &Rotation<D, N>::operator +=(const Rotation<D, N>& that) {
  axis += that.axis;
  return *this;
}

/** \todo move out of the class */
template <unsigned D, typename N> 
Rotation<D, N>::operator bool() const {
  return sqnorm(axis) != 0.; 
}

template <unsigned D, typename N> 
const Vector<NumAxes<D>::num, N> &Rotation<D, N>::r() const { 
  return axis; 
}

template <unsigned D, typename N> 
Vector<NumAxes<D>::num, N> &Rotation<D, N>::r() { 
  return axis; 
}

template <unsigned D, typename N> 
std::string Rotation<D, N>::toString() const { 
  return axis.toString(); 
}

/** \param A first operand
 *  \param B second operand
 *  \return \c A+B
 */
template <unsigned D, typename N>
Rotation<D, N> operator+ (const Rotation<D, N> &A, const Rotation<D, N> &B) {
  Rotation<D, N> C(A);
  return (C += B);
}

/** \ingroup VecMath
 *  \param o ostream to push into
 *  \param v Rotation to print
 *  \return a new ostream to push Rotations and stuff into                */
template <unsigned D, typename N>
std::ostream &operator << (std::ostream &o, const Rotation<D, N> &v) {
  o << v.r();
  return o;
}

/** \ingroup VecMath
 *  \param in istringstream to read from
 *  \param v Rotation to read
 *  \return a new istringstream to read stuff from
 */
template <unsigned D, typename N>
std::istringstream &operator >> (std::istringstream &in, Rotation<D, N> &v) {
  in >> v.r();
  return in;
}

template <typename N> 
Rotation<3, N> makeRotation(N const &r0, N const &r1, N const &r2) {

  Rotation<3, N> r;

  r[0] = r0;
  r[1] = r1;
  r[2] = r2;

  return r;
}

template <typename N> 
Rotation<4, N> makeRotation(N const &r0, N const &r1, N const &r2, 
                            N const &r3, N const &r4, N const &r5) {

  Rotation<4, N> r;

  r[0] = r0;
  r[1] = r1;
  r[2] = r2;
  r[3] = r3;
  r[4] = r4;
  r[5] = r5;

  return r;
}

}
