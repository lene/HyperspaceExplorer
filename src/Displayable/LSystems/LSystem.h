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

#ifndef LSYSTEM_H
#define LSYSTEM_H

#include "Object.h"

#define USE_LSYSTEM

class LSystem : public Object {

public:
    LSystem();
    virtual ~LSystem();
    
    virtual std::string getFunctionName() const;
    virtual void calibrateColors() const;
    virtual void ReInit(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv);
    virtual void Draw(UI::View* view);
    virtual void Project(double ScrW, double CamW, bool DepthCue4D);
    virtual void Transform(const VecMath::Rotation< 4, double >& R, const VecMath::Vector< 4, double >& T);

protected:
    virtual void Initialize(void );
    
};

namespace {
  Displayable *createLSystem() { return new LSystem(); }
# ifdef USE_LSYSTEM
  const bool registered_lsystem = TheFunctionFactory::Instance().registerFunction(createLSystem, "Object");
# endif  
}

#endif // LSYSTEM_H
