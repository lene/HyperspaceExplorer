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
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Log{
    public:
        /** print a string with a line break */
        void log(std::string
#           ifdef DEBUG
                message
#           endif
                ) {
#           ifdef DEBUG
                std::cerr << message << std::endl;
#           endif
        }

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