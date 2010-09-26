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

#ifndef DEFINITIONRANGEOFDIMENSION_H
#define DEFINITIONRANGEOFDIMENSION_H

#include "DefinitionSpaceRange.h"

namespace VecMath {
  template<unsigned D, class N> class Vector;
}

template<unsigned D> class DefinitionRangeOfDimension {
  
  public:
    
    double getMinValue(unsigned i) const;
    VecMath::Vector<D, double> getMinValue() const;
    void setMinValue(unsigned i, double minValue);
    
    double getMaxValue(unsigned i) const;
    VecMath::Vector<D, double> getMaxValue() const;
    void setMaxValue(unsigned i, double maxValue);
    
    double getStepsize(unsigned i) const;
    VecMath::Vector<D, double> getStepsize() const;
    void setStepsize(unsigned i, double stepsize);
    
    unsigned getNumSteps(unsigned i) const;
    VecMath::Vector<D, unsigned> getNumSteps() const;
    void setNumSteps(unsigned i, unsigned numSteps);

  protected:
    
    void setRange(unsigned i, const DefinitionSpaceRange &range);
    
  private:
    
    DefinitionSpaceRange range_[D];
};

#endif // DEFINITIONRANGEOFDIMENSION_H
