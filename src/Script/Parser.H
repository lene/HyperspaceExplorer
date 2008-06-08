#ifndef PARSER_H
#define PARSER_H

#include "Parser.H"

#include <string>
#include <vector>
#include <stdexcept>

class C4DView;

namespace Script {

    std::string strip_ws(const std::string &s);
    bool starts_with(const std::string &haystack, const std::string &needle);
    std::string leading(const std::string &haystack, const std::string &needle);
    std::string trailing(const std::string &haystack, const std::string &needle);

/// Parser reads a file and executes the commands in it in a C4DView
    /** @author Helge Preuss <scout@hyperspace-travel.de>                         */
    class Parser {

        class BadCommandException: public std::runtime_error {
            public:
                BadCommandException(const std::string &what):
                    std::runtime_error(what) { }
        };

        public:
            /// open a parser object for a given filename
            Parser(const std::string &file);
            ~Parser();

            /// Execute the commands described in the rc-file
            bool execute();

            /// define the view we operate on
            void setView(C4DView *_view) { view = _view; }
            C4DView *getView() const { return view; }

        private:
            std::vector<std::string> lines;
            C4DView *view;
    };


}
#endif
