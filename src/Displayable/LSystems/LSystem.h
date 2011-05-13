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


  /// The alphabet for the Lindenmayer System.
  /** See http://en.wikipedia.org/wiki/L-system#L-system_structure for definitions.
   *
   *  The Alphabet may consist of uppercase letters.
   *
   *  The following characters are reserved:
   *  - \p + and \p - for rotation about the \c x axis, \p ^ and \p v for rotation about the
   *    \c y axis, &lt; and &gt; for rotations about the \c z axis, and \p [ and \p ]
   *    for rotations about the \c w axis. Rotations about higher axes are... not yet implemented, come to think of it.
   *  - \p f and \p b for stepping one step forward or one step backward.
   *  - \p { and \p } for grouping.
   *  - \p s for defining a scale factor.
   *  - \p a for defining a rotation angle.
   */
  class Alphabet {

  public:

    static const char LEFT_X = '+';
    static const char RIGHT_X = '-';
    static const char LEFT_Y = '^';
    static const char RIGHT_Y = 'v';
    static const char LEFT_Z = '<';
    static const char RIGHT_Z = '>';
    static const char LEFT_W = '[';
    static const char RIGHT_W = ']';

    static const char FORWARD = 'f';
    static const char BACK = 'b';

    static const char OPEN_GROUP = '{';
    static const char CLOSE_GROUP = '}';

    static const char SCALE = 's';
    static const char ANGLE = 'a';


    Alphabet(const std::string &letters);
    std::string toString() const;

  private:
      std::vector<char> letters_;
  };

  class Axiom {

  public:
    Axiom (const std::string &axiom);

    std::string::const_iterator begin();
    std::string::const_iterator end();

  private:
    std::string axiom_;
  };

  class Rule {

  public:
    static const char SEPARATOR = ':';

    Rule(const std::string &rule);

    std::string toString() const;

  private:
      char predecessor_;
      std::string successor_;

  };

  class Rules {

  public:
    Rules(const std::string &rules);

    std::string apply(const std::string &axiom);
    std::string toString() const;

  private:
    typedef std::map<char, Rule> storage_type;
    storage_type rules_;
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
