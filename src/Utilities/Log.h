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

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

#include "SingletonHolder.h"
#include "Globals.h"
#include "Vector.h"
#include "Rotation.h"

/// Conditionally prints messages, if the preprocessor variable DEBUG is defined
/** That implies a lot of \#ifdef DEBUG in its declaration as well as its
 *  definition. Never mind the ugliness.
 *  @author Lene Preuss <lene.preuss@gmail.com>                         */
class Log{
    public:
        /** print a string with a line break
         */
        void log(std::string
#           ifdef DEBUG
                message
#           endif
                ) {
#           ifdef DEBUG
                std::cerr << message << std::endl;
#           endif
        }

        /** print a string without a line break
         */
        template <typename T> Log &operator<<(const T &
#           ifdef DEBUG
                out
#           endif
        ) {
#           ifdef DEBUG
                std::cerr << out;
                std::cerr.flush();
#           endif
            return *this;
}

    private:
        /** disabled default constructor */
        Log() { }
        /** disabled copy constructor */
        Log(const Log &);
        /** disabled assignment operator */
        Log &operator=(const Log &);
        /** disabled destructor */
        ~Log() { }

    friend class Loki::CreateUsingNew<Log>;
};

typedef Loki::SingletonHolder<Log> SingletonLog;
#endif
