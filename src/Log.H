#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

#include "SingletonHolder.H"
#include "Globals.H"

/** @author Helge Preuss <scout@hyperspace-travel.de> */
class Log{
    public:
        void log(std::string message) {
#           ifdef DEBUG
                std::cerr << message << std::endl;
#           endif
        }

        Log &operator<<(const std::string &message) {
#           ifdef DEBUG
                std::cerr << message;
#           endif
            return *this;
        }

        Log &operator<<(long x) {
            return operator<<(Globals::Instance().itoa(x));
        }

        Log &operator<<(unsigned long x) {
            return operator<<(Globals::Instance().itoa(x));
        }

        Log &operator<<(double x) {
            return operator<<(Globals::Instance().ftoa(x));
        }

private:
    Log() { }
    Log(const Log &);
    Log &operator=(const Log &);
    ~Log() { }

    friend class Loki::CreateUsingNew<Log>;
};

typedef Loki::SingletonHolder<Log> SingletonLog;
#endif
