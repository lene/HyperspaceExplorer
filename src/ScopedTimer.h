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

#ifndef SCOPEDTIMER_H
#define SCOPEDTIMER_H

#include <iostream>

/// A class to write timing information to a std::ostream
/** To use a ScopedTimer, simply instantiate one in the function whose run time
 *  you want to measure. As soon as the object goes out of scope, the time it
 *  took to execute the code between the instantiation and the destruction of
 *  the ScopedTimer is printed to a std::ostream, by default std::cerr.
 */
class ScopedTimer {

  public:
    ScopedTimer(const std::string &message, std::ostream &out = std::cerr);
    ~ScopedTimer();

  private:
    class Impl;
    Impl *pImpl_;
};

#endif // SCOPEDTIMER_H
