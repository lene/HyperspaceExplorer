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
#include "Util.h"

#include "Rotation.impl.h"

using VecMath::Vector;

#include <sstream>
#include <iterator>

Alphabet::Alphabet(const std::string& letters): letters_() {
  for(std::string::const_iterator it = letters.begin(); it != letters.end(); ++it) {
    if (*it != ' ' && *it != ',') {
        letters_.push_back(*it);
    }
  }
}

std::string Alphabet::toString() const {
    std::ostringstream o;
    std::copy(letters_.begin(), letters_.end(), std::ostream_iterator<char>(o, " "));
    return o.str();
}

Axiom::Axiom(const std::string& axiom): axiom_(axiom) { }

Rules::Rules(const std::string& rules) {
    std::vector<std::string> parts = Util::explode(",", rules);
}
LSystem::LSystem(unsigned level): Composite(), 
        level_(level),
        alphabet_("AB"), rules_("A: AB, B: A"), axiom_("A") {
  declareParameter("Level", (unsigned)2);
  declareParameter("Alphabet", std::string("..."));
  declareParameter("Rules", std::string("..."));
  declareParameter("Axiom", std::string("..."));

  Initialize();
}

LSystem::~LSystem() { }


std::string LSystem::getFunctionName() const { return "Lindenmayer System: "+alphabet_.toString(); }

void LSystem::SetParameters(const ParameterMap &parms) {
  std::cerr << "LSystem::SetParameters("<<parms.toString()<<")\n";
      for (ParameterMap::const_iterator i = parms.begin(); i != parms.end(); ++i) {
        if (i->second->getName() == "Alphabet") alphabet_ = i->second->toString();
        if (i->second->getName() == "Level") level_ = i->second->toUnsigned();
      }
//  Initialize();
}

void LSystem::Initialize() {
    std::cerr << "LSystem::Initialize("<<level_<<")\n";
    clear();
    generate(level_);
}
LSystem LSystem::generate(unsigned level) {
  addComponent(
    std::shared_ptr<Displayable> (new Hypercube),
    VecMath::makeVector(0., 0., 0., 0.),
    VecMath::Rotation<4>()
  );
  if (level > 0) {
      const double rotation_angle = 5.;
      const double displacement = 1.707;
      const double scale = 0.707;
      for (unsigned index = 0; index < 4; index++) {
          for (int sign = -1; sign < 1; sign += 2) {
              double x = (index == 0)*sign;
              double y = (index == 1)*sign;
              double z = (index == 2)*sign;
              double w = (index == 3)*sign;
              addComponent(
                        std::shared_ptr<Displayable> (new LSystem(level-1)),
                        displacement*VecMath::makeVector(x, y, z, w),
                        VecMath::Rotation<4>(rotation_angle, 0., 0., 0., 0., 0.),
                        VecMath::Vector<4>(scale)
               );
          }
      }
  }
  return *this;
}





