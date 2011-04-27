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

#include "Object.h"

#include "Rotation.impl.h"

using VecMath::Vector;

LSystem::LSystem(unsigned level): Composite(), level_(level) {
  addComponent(
    std::shared_ptr<Displayable> (new Hypercube),
    VecMath::makeVector(0., 0., 0., 0.),
    VecMath::Rotation<4>()
  );
  if (level_ > 0) {
      const double rotation_angle = 5.;
      const double displacement = 1.707;
      const double scale = 0.707;
      addComponent(
        std::shared_ptr<Displayable> (new LSystem(level_-1)),
        VecMath::makeVector(displacement, 0., 0., 0.),
        VecMath::Rotation<4>(rotation_angle, 0., 0., 0., 0., 0.),
        VecMath::Vector<4>(scale)
      );
      addComponent(
        std::shared_ptr<Displayable> (new LSystem(level_-1)),
        VecMath::makeVector(-displacement, 0., 0., 0.),
        VecMath::Rotation<4>(rotation_angle, 0., 0., 0., 0., 0.),
        VecMath::Vector<4>(scale)
      );
      addComponent(
        std::shared_ptr<Displayable> (new LSystem(level_-1)),
        VecMath::makeVector(0., displacement, 0., 0.),
        VecMath::Rotation<4>(0., rotation_angle, 0., 0., 0., 0.),
        VecMath::Vector<4>(scale)
      );
      addComponent(
        std::shared_ptr<Displayable> (new LSystem(level_-1)),
        VecMath::makeVector(0., -displacement, 0., 0.),
        VecMath::Rotation<4>(0., rotation_angle, 0., 0., 0., 0.),
        VecMath::Vector<4>(scale)
      );
      addComponent(
        std::shared_ptr<Displayable> (new LSystem(level_-1)),
        VecMath::makeVector(0., 0., displacement, 0.),
        VecMath::Rotation<4>(0., 0., rotation_angle, 0., 0., 0.),
        VecMath::Vector<4>(scale)
      );
      addComponent(
        std::shared_ptr<Displayable> (new LSystem(level_-1)),
        VecMath::makeVector(0., 0., -displacement, 0.),
        VecMath::Rotation<4>(0., 0., rotation_angle, 0., 0., 0.),
        VecMath::Vector<4>(scale)
      );
      addComponent(
        std::shared_ptr<Displayable> (new LSystem(level_-1)),
        VecMath::makeVector(0., 0., 0., displacement),
        VecMath::Rotation<4>(0., 0., 0., rotation_angle, 0., 0.),
        VecMath::Vector<4>(scale)
      );
      addComponent(
        std::shared_ptr<Displayable> (new LSystem(level_-1)),
        VecMath::makeVector(0., 0., 0., -displacement),
        VecMath::Rotation<4>(0., 0., 0., rotation_angle, 0., 0.),
        VecMath::Vector<4>(scale)
      );
  }
}

LSystem::~LSystem() { }


std::string LSystem::getFunctionName() const { return "Lindenmayer System"; }








