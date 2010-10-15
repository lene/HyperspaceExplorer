/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef NOTYETIMPLEMENTEDEXCEPTION_H
#define NOTYETIMPLEMENTEDEXCEPTION_H

#include <string>
#include <stdexcept>

/// This Exception is thrown when a feature is not yet implemented.
/** \author Lene Preuss <lene.preuss@gmail.com> */
class NotYetImplementedException: public std::logic_error {
    public:
        /// \param what Should contain the name of the throwing class method
        NotYetImplementedException(const std::string &what):
            std::logic_error("\n"+what+":\nNot yet implemented!") {}
};

#endif
