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

#include "View.h"

using VecMath::Vector;

LSystem::LSystem(): Object(0, 0) { }

LSystem::~LSystem() { }

void LSystem::Initialize() { }

std::string LSystem::getFunctionName() const { return "Lindenmayer System"; }

void LSystem::calibrateColors() const {

}

void LSystem::ReInit(double, double, double, double, double, double, double, double, double) {

}

void LSystem::Draw(std::shared_ptr<UI::View> view ) {
  view->drawQuadrangle(Vector<4>(1., 0., 0., 0.),
                       Vector<4>(0., 1., 0., 0.),
                       Vector<4>(0., 0., 1., 0.),
                       Vector<4>(0., 0., 0., 1.),
                       Vector<3>(1., 0., 0.),
                       Vector<3>(0., 1., 0.),
                       Vector<3>(0., 0., 1.),
                       Vector<3>(0., 0., 0.));
}

void LSystem::Project(double ScrW, double CamW, bool DepthCue4D)
{

}

void LSystem::Transform(const VecMath::Rotation< 4, double >& R, const VecMath::Vector< 4, double >& T)
{

}

