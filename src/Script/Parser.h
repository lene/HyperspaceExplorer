#ifndef PARSER_H
#define PARSER_H

#include "Parser.h"
#include "View.h"

#include <string>
#include <vector>
#include <stdexcept>

//class UI::View;

/// Interpreting and executing scripts
namespace Script {

    std::string strip_ws(const std::string &s);
    bool starts_with(const std::string &haystack, const std::string &needle);
    std::string leading(const std::string &haystack, const std::string &needle);
    std::string trailing(const std::string &haystack, const std::string &needle);

    /// Parser reads a file and executes the commands in it in a C4DView
    /** This class takes the role of the Context class in the class diagram for
     *  the Interpreter pattern in the GOF book, p. 245
     *  \author Helge Preuss <lene.preuss@gmail.com>
     *  \ingroup ScriptingGroup                                               */
    class Parser {

        public:
            /// open a parser object for a given filename
            Parser(const std::string &file);

            /// Execute the commands described in the rc-file
            bool execute();

            /// Define the view we operate on
            void setView(UI::View *view) { _view = view; }
            /// \return The view we operate on
            UI::View *getView() const { return _view; }

        private:
            std::vector<std::string> _lines;    ///< Lines of the script
            UI::View *_view;     ///< The View on which we're operating
    };


}
#endif
