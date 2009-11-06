#include "Parser.h"
#include "Statement.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::string;
using std::vector;
using std::min;

using std::cout;
using std::endl;

namespace Script {
    /// Trim whitespace from the beginning and the end of a string
    /** \return The trimmed string
     */
    string strip_ws(const string &s) {
        unsigned start = s.find_first_not_of(" \t\n\r"),
                 end = s.find_last_not_of(" \t\n\r")+1;
        if ((start >= s.length()) || (start >= end)) return string();
        return string(s, start, end-start);
    }

    /// Remove everything beginning with a "#" character to the end of the line
    string strip_comments(const string &s) {
        return strip_ws(string(s, 0, s.find('#')));
    }

    /** Does \p haystack start with \p needle ?
     */
    bool starts_with(const string &haystack, const string &needle) {
        if (haystack.empty()) return false;
        return (strip_ws(haystack).find(needle) == 0);
    }

    /** \return the part of \p haystack before the start of \p needle
     */
    string leading(const string &haystack, const string &needle) {
        return strip_ws(string(haystack, 0, haystack.find(needle)));
    }

    /** \return the part of \p haystack after the end of \p needle
     */
    string trailing(const string &haystack, const string &needle) {
        return strip_ws(string(haystack, haystack.find(needle)+needle.length()));
    }

    /// Read a command file and store its content for later execution
    /** The content of \p file is stored line-wise
     *  \todo lines must not be longer than 4095 characters. Everything after
     *  that is discarded. This is a limitation of std::ifstream::getline().
     *  \param file The script file that is read
     */
    Parser::Parser(const std::string &file) {
        std::ifstream infile(file.c_str());
        if (infile.good()) {
            char buffer[4096];
            while(!infile.eof()) {
                infile.getline(buffer, 4095, '\n');
                if (!(strip_comments(buffer).empty()))
                    _lines.push_back(strip_comments(buffer));
            }
        }
    }

    /// execute the commands for the current command file
    /** Executes the statements in the file one after the other
     *  @return success                                                       */
    bool Parser::execute() {
        for(vector<string>::iterator i = _lines.begin(); i != _lines.end(); ++i) {
            StatementFactory::createStatement(this, *i)->execute();
        }
        return true;
    }

}
