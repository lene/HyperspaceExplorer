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

#ifndef FUNCTIONHOLDER_H
#define FUNCTIONHOLDER_H

#include "Function.h"

namespace VecMath {
  template <typename T, unsigned D> class MultiDimensionalVector;
}

template <unsigned N, unsigned P, typename NUM = double>
class FunctionHolder : public Function {

  public:
    
    FunctionHolder();
    
    virtual unsigned int getDefinitionSpaceDimensions();
    
  protected:
    
    /// Array of function values.
    const VecMath::MultiDimensionalVector< VecMath::Vector<N>, P > &X() const;
    /// Array of function values after transform.
    const VecMath::MultiDimensionalVector< VecMath::Vector<N>, P > &Xtrans() const;
    /// Array of projected function values.
    const VecMath::MultiDimensionalVector< VecMath::Vector<3>, P > &Xscr() const;

  private:
    
    class Impl;
    Impl *pImpl_;
    
};

#endif // FUNCTIONHOLDER_H
