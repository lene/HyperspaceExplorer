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

#include "Composite.h"
#include "Object.h"

#define USE_LSYSTEM


  class Alphabet {

  public:
    Alphabet(const std::string &letters);
    std::string toString() const;

  private:
      std::vector<char> letters_;
  };

  class Axiom {

  public:
    Axiom (const std::string &axiom);

  private:
    std::string axiom_;
  };

  class Rule {

  public:
    Rule(char from, const std::string &to);

  private:
      char predecessor_;
      std::string successor;

  };

  class Rules {

  public:
    Rules(const std::string &rules);
    std::string apply(const std::string &axiom);

  private:
    std::vector<Rule> rules_;
  };

class LSystem : public Composite {

public:

  LSystem(unsigned level = 3);
  virtual ~LSystem();
    
  virtual std::string getFunctionName() const;

  virtual void SetParameters(const ParameterMap &parameters);

protected:

  virtual void Initialize();

private:

    LSystem generate(unsigned level);

    unsigned level_;
    Alphabet alphabet_;
    Rules rules_;
    Axiom axiom_;

};

namespace {
  Displayable *createLSystem() { return new LSystem(); }
# ifdef USE_LSYSTEM
  const bool registered_lsystem = TheFunctionFactory::Instance().registerFunction(createLSystem, "Object");
# endif  
}

#endif // LSYSTEM_H
