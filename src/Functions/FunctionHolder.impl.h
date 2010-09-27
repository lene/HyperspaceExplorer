/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "FunctionHolder.h"

#include "FunctionValueGrid.h"

template <unsigned N, unsigned P, typename NUM>
class FunctionHolder<N, P, NUM>::Impl {

  public:
    
  private:

    /// Array of function values.
    FunctionValueGrid<4, 3> _X;
    /// Array of function values after transform.
    FunctionValueGrid<4, 3>::value_storage_type _Xtrans;
    /// Array of projected function values.
    VecMath::MultiDimensionalVector< VecMath::Vector<3>, 3 > _Xscr;

};

template <unsigned N, unsigned P, typename NUM>
FunctionHolder<N, P, NUM>::FunctionHolder(): Function(), pImpl_(new Impl) { }

template <unsigned N, unsigned P, typename NUM>
unsigned int FunctionHolder<N, P, NUM>::getDefinitionSpaceDimensions() {
  return P;
}
