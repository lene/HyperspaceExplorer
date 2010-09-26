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
    template <unsigned D, typename N> Rotation<D, N>::Rotation (N r0, ... ):
            axis() {
        axis[0] = r0;
        va_list argp;
        va_start (argp, r0);
        for (unsigned i = 1; i < NumAxes<D>::num; i++) {
            axis[i] = va_arg (argp, N);
        }
        va_end (argp);
    }

    template <unsigned D, typename N>
            N &Rotation<D, N>::operator[] (unsigned i) {
        assert(i < NumAxes<D>::num);
        return axis[i];
    }

    template <unsigned D, typename N>
            N Rotation<D, N>::operator[] (unsigned i) const {
        assert(i < NumAxes<D>::num);
        return axis[i];
    }

    template <unsigned D, typename N> Rotation<D, N>::operator Matrix<D, N>() const {
        Matrix<D, N> R;
        for (unsigned i = 0; i < NumAxes<D>::num; i++) {
            if (axis[i]) {
                R *= Matrix<D, N>(RotationAxes<D>::axis(0, i),
                                  RotationAxes<D>::axis(1, i),
                                  axis[i]);
            }
        }
        return R;
    }

    template <unsigned D, typename N>
            Rotation<D, N> &Rotation<D, N>::operator +=(const Rotation<D, N>& that) {
        axis += that.axis;
        return *this;
    }

    template <unsigned D, typename N>
            Rotation<D, N> Rotation<D, N>::operator+ (const Rotation<D, N> &that) const {
        static Rotation<D, N> Z;
        Z = *this;
        return (Z += that);
    }

  
}
