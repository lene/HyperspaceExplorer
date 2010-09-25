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

#ifndef DEFINITIONSPACERANGE_H
#define DEFINITIONSPACERANGE_H

class DefinitionSpaceRange {
  
  public:

    DefinitionSpaceRange();
    DefinitionSpaceRange(double minValue, double maxValue, double stepsize);
    DefinitionSpaceRange(double minValue, double maxValue, unsigned numSteps);
    ~DefinitionSpaceRange();
  
    double getMinValue() const;
    void setMinValue(double minValue);
    
    double getMaxValue() const;
    void setMaxValue(double maxValue);
    
    double getStepsize() const;
    void setStepsize(double stepsize);
    
    unsigned getNumSteps() const;
    void setNumSteps(unsigned numSteps);
    
    static double defaultMin,   ///< Default value for lower grid boundary
                  defaultMax,   ///< Default value for upper grid boundary
                  defaultStep;  ///< Default value for step size

  private:
    
    class Impl;
    Impl *pImpl_;
    
};

#endif // DEFINITIONSPACERANGE_H
