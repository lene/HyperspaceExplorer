#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

#include "SingletonHolder.H"
#include "Globals.H"

/** A class to conditionally print debug messages, depending on whether the
 *  preprocessor variable DEBUG is defined
 *
 *  That implies a lot of #ifdef DEBUG in its declaration as well as its
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

        /** print a string without a line break */
        Log &operator<<(const std::string &
#           ifdef DEBUG
                        message
#           endif
                       ) {
#           ifdef DEBUG
                std::cerr << message;
                std::cerr.flush();
#           endif
            return *this;
        }

        /** print a long integer without a line break */
        Log &operator<<(long x) {
            return operator<<(Globals::Instance().itoa(x));
        }

        /** print an unsigned long integer without a line break */
        Log &operator<<(unsigned long x) {
            return operator<<(Globals::Instance().itoa(x));
        }

        /** print a double without a line break */
        Log &operator<<(double x) {
            return operator<<(Globals::Instance().ftoa(x));
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
