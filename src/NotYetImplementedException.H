#ifndef NOTYETIMPLEMENTEDEXCEPTION_H
#define NOTYETIMPLEMENTEDEXCEPTION_H

#include <string>
#include <stdexcept>

/**
    \author Helge Preuss <scout@hyperspace-travel.de>
*/
class NotYetImplementedException: public std::logic_error {
    public:
        NotYetImplementedException(const std::string &what):
            std::logic_error(what+": Not yet implemented!") {}
};

#endif
