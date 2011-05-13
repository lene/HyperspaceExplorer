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
using std::vector;
using std::string;

#include <sstream>
#include <iterator>

Alphabet::Alphabet(const std::string& letters): letters_() {
  for(string::const_iterator it = letters.begin(); it != letters.end(); ++it) {
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

std::string::const_iterator Axiom::begin() const {
    return axiom_.begin();
}

std::string::const_iterator Axiom::end() const {
    return axiom_.end();
}

const std::string &Axiom::get() const {
  return axiom_;
}

Rule::Rule(const std::string& rule) {
  vector<string> parts = Util::explode(string(1, SEPARATOR), rule);
  if (parts.size() != 2) {

  } else {
    string before = Util::trim(parts[0]);
    if (before.length() != 1) {

    } else {
      predecessor_ = before.at(0);
    }

    successor_ = Util::trim(parts[1]);
  }
}

std::string Rule::apply(char atom) const {
  if (atom == predecessor_) {
      return successor_;
  }
  else return string(1, atom);
}

char Rule::getPredecessor() const { return predecessor_; }

std::string Rule::toString() const {
  std::ostringstream o;
  o << predecessor_ << ": " << successor_;
  return o.str();
}

Rules::Rules(const std::string& rules) {
    vector<string> parts = Util::explode(",", rules);
    for (vector<string>::const_iterator i = parts.begin(); i != parts.end(); ++i) {
      Rule rule(Util::trim(*i));
      rules_.insert(std::make_pair(rule.getPredecessor(), rule));
    }
}

std::string Rules::apply(const Axiom& axiom) const {
  string expanded;
  for (string::const_iterator it = axiom.begin(); it != axiom.end(); ++it) {
    storage_type::const_iterator rule = rules_.find(*it);
    if (rule != rules_.end()) {
      expanded.append(rule->second.apply(*it));
    } else {
      expanded.append(1, *it);
    }
  }
  return expanded;
}

Rules::storage_type::size_type Rules::size() const {
  return rules_.size();
}

std::string Rules::toString() const {
  std::ostringstream o;
  for (storage_type::const_iterator i = rules_.begin(); i != rules_.end(); ++i) {
      o << i->second.toString() << ", ";
  }
  return o.str();
}

LSystem::LSystem(unsigned level): Composite(), 
        level_(level),
        alphabet_("AB"), rules_("A: AB, B: A"), axiom_("A") {
  declareParameter("Level", (unsigned)2);
  declareParameter("Alphabet", std::string("AB ..."));
  declareParameter("Rules", std::string("A: AB, B: A ..."));
  declareParameter("Axiom", std::string("A ..."));

  Initialize();
}

LSystem::~LSystem() { }


std::string LSystem::getFunctionName() const { 
  return "Lindenmayer System: "+rules_.toString();
}

void LSystem::SetParameters(const ParameterMap &parms) {
  for (ParameterMap::const_iterator i = parms.begin(); i != parms.end(); ++i) {
    if (i->second->getName() == "Level") level_ = i->second->toUnsigned();
    if (i->second->getName() == "Alphabet") alphabet_ = i->second->toString();
    if (i->second->getName() == "Rules") rules_ = i->second->toString();
    if (i->second->getName() == "Axiom") axiom_ = i->second->toString();
  }
    string product = expand(axiom_.get(), level_);
    std::cerr << product << std::endl;
  std::cerr << getFunctionName() << std::endl;
}

void LSystem::Initialize() {
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

std::string LSystem::expand(const std::string &axiom, unsigned level) {
  if (level > 0 && rules_.size() > 0) {
    string expanded = rules_.apply(axiom);
    return expand(expanded, level-1);
  }

  return axiom;
}



