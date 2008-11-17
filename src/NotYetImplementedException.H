#ifndef NOTYETIMPLEMENTEDEXCEPTION_H
#define NOTYETIMPLEMENTEDEXCEPTION_H

#include <string>
#include <stdexcept>

/// This Exception is thrown when a feature is not yet implemented.
/** \author Helge Preuss <scout@hyperspace-travel.de> */
class NotYetImplementedException: public std::logic_error {
    public:
        /// \param what Should contain the name of the throwing class method
        NotYetImplementedException(const std::string &what):
            std::logic_error("\n"+what+":\nNot yet implemented!") {}
};

#endif
