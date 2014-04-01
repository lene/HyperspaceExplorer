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

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <stdexcept>

namespace UI {
class View;
}

/// Interpreting and executing scripts
namespace Script {

    std::string strip_ws(const std::string &s);
    bool starts_with(const std::string &haystack, const std::string &needle);
    std::string leading(const std::string &haystack, const std::string &needle);
    std::string trailing(const std::string &haystack, const std::string &needle);

    /// Parser reads a file and executes the commands in it in a C4DView
    /** This class takes the role of the Context class in the class diagram for
     *  the Interpreter pattern in the GOF book, p. 245
     *  \author Lene Preuss <lene.preuss@gmail.com>
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
