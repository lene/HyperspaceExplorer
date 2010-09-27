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

#include "Matrix.impl.h"

#include <typeinfo>

namespace VecMath {

const unsigned RotationAxes<3>::_axis[2][3] = {
  { 1, 0, 0 }, { 2, 2, 1}
};

const unsigned RotationAxes<4>::_axis[2][6] = {
  { 0, 0, 0, 1, 1, 2 }, { 1, 2, 3, 2, 3, 3 }
};

/** Compute the row/column in a rotation Matrix from the dimension
 *  of the vector space and the position of the rotation angle in
 *  the Rotation vector.
 *  \param which 0 for \p ii or 1 for \p jj
 *  \param index position in the Rotation vector                  
 */
unsigned RotationAxes<3>::axis(unsigned which, unsigned index) {
  return _axis[which][index];
}

/** Compute the row/column in a rotation Matrix from the dimension
 *  of the vector space and the position of the rotation angle in
 *  the Rotation vector.
 *  \param which 0 for \p ii or 1 for \p jj
 *  \param index position in the Rotation vector                  
 */
unsigned RotationAxes<4>::axis(unsigned which, unsigned index) {
  return _axis[which][index];
}


/// Specialization for a Rotation in four dimensions
template <> Rotation<4>::operator Matrix<4>() const {
  Matrix<4> Rxy = Matrix<4> (0, 1, axis[0]), Rxz = Matrix<4> (0, 2, axis[1]),
            Rxw = Matrix<4> (0, 3, axis[2]),  Ryz = Matrix<4> (1, 2, axis[3]),
            Ryw = Matrix<4> (1, 3, axis[4]), Rzw = Matrix<4> (2, 3, axis[5]),
            Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw,
            Rot = Rxyz*Rxwyz*Ryzw;

  return Rot;
}

/// Specialization for a Rotation in three dimensions
template <> Rotation<3>::operator Matrix<3>() const {
  Matrix<3> Rx = Matrix<3> (1, 2, axis[0]), Ry = Matrix<3> (0, 2, axis[1]),
            Rz = Matrix<3> (0, 1, axis[2]),
            Rot = Rx*Ry*Rz;

  return Rot;
}

/** This operator is not intended to be used in a production environment.
 *  It is defined so it can be overridden using late binding by a Rotation.
 *  In fact, it simply prints the typeid of the class.
 *
 *  \ingroup VecMath
 *  \param o ostream to push into
 *  \param r the RotationBase to print
 *  \return a new ostream to push Rotations and stuff into
 */
std::ostream &operator << (std::ostream &o, const RotationBase &r) {
  o << typeid(r).name();
  return o;
}

}
