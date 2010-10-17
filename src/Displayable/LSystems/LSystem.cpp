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

#include "LSystem.h"

LSystem::LSystem(): Object(1, 1) { }

LSystem::~LSystem() { }

void LSystem::Initialize() { }

void LSystem::for_each_projected(Displayable::function_on_projected_vertex apply)
{

}

void LSystem::for_each_vertex(Displayable::function_on_fourspace_vertex apply)
{

}

unsigned int LSystem::getDefinitionSpaceDimensions()
{

}

std::string LSystem::getFunctionName() const { return "Lindenmayer System"; }

void LSystem::calibrateColors() const {

}

void LSystem::ReInit(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)
{

}

void LSystem::Draw(UI::View* )
{

}

void LSystem::Project(double ScrW, double CamW, bool DepthCue4D)
{

}

void LSystem::Transform(const VecMath::Rotation< 4, double >& R, const VecMath::Vector< 4, double >& T)
{

}

