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

#include "Util.h"

#include "Vector.h"

#include <QString>

#include <iterator>
#include <string>
#include <sstream>

#include <GL/gl.h>
#include <GL/glu.h>

using VecMath::Vector;
using std::string;
using std::ostringstream;

namespace Util {
  
  template<typename T> std::ostream& operator<<(std::ostream& s,
                                                std::vector<T> const& v) {
    s << "(";
    copy(v.begin(), v.end(), std::ostream_iterator<T>(s, " "));
    s << ")";
    return s;
  }

  /** debug function for OpenGL commands; outputs all current GL errors on cerr
  *  @param op optional repetition of last GL command                          */
  void CheckGLErrors (const char *
  #ifdef DEBUG
  op
  #endif
  ) {
    #   ifdef DEBUG
    GLenum error;
    while ((error = glGetError ()) != GL_NO_ERROR)
      std::cerr << "GL Err: " << op << ": " << gluErrorString (error) << std::endl;
    #   endif
  }

  /** find the ID of the first free GL list
  *  @return first free GL list                                           */
  int GetGLList() {
    int MyList = 1;

    // find a free GL list
    while (glIsList(MyList) == GL_TRUE) MyList++;

    return MyList;
  }

  void glVertex(const Vector< 3, double >& V) {
    if (std::isfinite (V.sqnorm()))
      glVertex3dv(V.data());
  }

  /** normalizes a Vector made from 3 doubles out-of-place
  *  @param xx x component of Vector to be normalized
  *  @param yy y component of Vector to be normalized
  *  @param zz z component of Vector to be normalized
  *  @return normalized Vector                                             */
  Vector<3, double> vnormalize(double xx, double yy, double zz) {
    static Vector<3, double> x;

    x[0] = xx; x[1] = yy; x[2] = zz;
    return VecMath::vnormalize(x);
  }

  /** makes a double precision value from a QString
  *  implemented because I called a function atod () ages ago, for convenience
  *  @param s  string to be converted
  *  @return its numerical value                                           */
  double atod(QString s) {
    return s.toDouble();
  }

  double atod (const std::string &s) {
    return QString(s.c_str()).toDouble();
  }

  int atoi(const std::string &s) {
    return QString(s.c_str()).toInt();
  }

  unsigned atou(const std::string &s) {
    return QString(s.c_str()).toUInt();
  }

  /** makes a string  from an integer value
  *  implemented because I called a function itoa () ages ago, for convenience
  *  @param x number to be converted
  *  @return  its string representation                                     */
  string itoa(int x) {
    ostringstream o;
    o << x;
    return o.str ();
  }

  /** makes a string  from a double value
  *  implemented because I called a function ftoa () ages ago, for convenience
  *  @param x  number to be converted
  *  @return its string representation                                     */
  string ftoa(double x) {
    ostringstream o;
    o << x;
    return o.str ();
  }

  std::string sup2() {
    return "²";
    static QString qsup2(QChar(0x00B2));
    static std::string sup2_(qsup2.toStdString());
    return sup2_;
  }

  std::string sup3() {
    return "³";
    static QString qsup3(QChar(0x00B3));
    static std::string sup3_(qsup3.toStdString());
    return sup3_;
  }

}
