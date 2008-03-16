#ifndef LOG_H
#define LOG_H

#include "SingletonHolder.H"

/** @author Helge Preuss <scout@hyperspace-travel.de> */
class Log{
public:
    void log(std::string);
    Log &operator<<(const std::string &);
    Log &operator<<(long);
    Log &operator<<(unsigned long);
    Log &operator<<(double);

private:
    Log();
    Log(const Log &);
    Log &operator=(const Log &);
    ~Log();

    friend class Loki::CreateUsingNew<Log>;
};

typedef Loki::SingletonHolder<Log> SingletonLog;
#endif
