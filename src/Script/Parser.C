#include "Parser.H"
#include "Statement.H"

#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

using std::cout;
using std::endl;

namespace Script {
    string strip_ws(const string &s) {
        unsigned start = s.find_first_not_of(" \t\n\r");
        if (start >= s.length()) return string();
        return string(s, start, s.find_last_not_of(" \t\n\r")-start+1);
    }

    bool starts_with(const string &haystack, const string &needle) {
        if (haystack.empty()) return false;
        return (strip_ws(haystack).find(needle) == 0);
    }

    string leading(const string &haystack, const string &needle) {
        return strip_ws(string(haystack, 0, haystack.find(needle)));
    }

    string trailing(const string &haystack, const string &needle) {
        return strip_ws(string(haystack, haystack.find(needle)+needle.length()));
    }

    /// read in a command file
    Parser::Parser(const std::string &file) {
        std::ifstream infile(file.c_str());
        if (infile.good()) {
            char buffer[4096];
            while(!infile.eof()) {
                infile.getline(buffer, 4095, '\n');
                if (!(strip_ws(buffer).empty())) lines.push_back(string(buffer));
            }
        }
    }

    Parser::~Parser() { }

    /// execute the commands for the current command file
    /** @return success                                                           */
    bool Parser::execute() {
        for(vector<string>::iterator i = lines.begin(); i != lines.end(); i++) {
            StatementFactory::createStatement(this, *i)->execute();
        }
        return true;
    }

}
