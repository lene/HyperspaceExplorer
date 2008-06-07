#include "Parser.H"
#include "4DView.H"
#include "Rotation.H"
#include "Vector.H"

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
            if (starts_with(*i, "object")) {
                ObjectStmt(this, trailing(*i, "object")).execute();
            } else if (starts_with(*i, "parameter")) {
                ParmStmt(this, trailing(*i, "parameter")).execute();
            } else if (starts_with(*i, "transform")) {
                XformStmt(this, trailing(*i, "transform")).execute();
            } else if (starts_with(*i, "rotation")) {
                Statement(this, trailing(*i, "rotation")).execute();
            } else if (starts_with(*i, "parameter_step")) {
                Statement(this, trailing(*i, "parameter_step")).execute();
            } else if (starts_with(*i, "transform_step")) {
                Statement(this, trailing(*i, "transform_step")).execute();
            } else if (starts_with(*i, "rotation_step")) {
                Statement(this, trailing(*i, "rotation_step")).execute();
            } else if (starts_with(*i, "frames")) {
                Statement(this, trailing(*i, "frames")).execute();
            } else if (starts_with(*i, "loop")) {
                Statement(this, trailing(*i, "loop")).execute();
            } else if (starts_with(*i, "colors")) {
                Statement(this, trailing(*i, "colors")).execute();
            } else if (starts_with(*i, "shading")) {
                Statement(this, trailing(*i, "shading")).execute();
            } else if (starts_with(*i, "lighting")) {
                Statement(this, trailing(*i, "lighting")).execute();
            } else if (starts_with(*i, "transparence")) {
                Statement(this, trailing(*i, "transparence")).execute();
            } else if (starts_with(*i, "wireframe")) {
                Statement(this, trailing(*i, "wireframe")).execute();
            } else if (starts_with(*i, "depthcue3d")) {
                Statement(this, trailing(*i, "depthcue3d")).execute();
            } else if (starts_with(*i, "depthcue4d")) {
                Statement(this, trailing(*i, "depthcue4d")).execute();
            } else if (starts_with(*i, "coordinates")) {
                Statement(this, trailing(*i, "coordinates")).execute();
            } else if (starts_with(*i, "image_dir")) {
                Statement(this, trailing(*i, "image_dir")).execute();
            } else if (starts_with(*i, "image_prefix")) {
                Statement(this, trailing(*i, "image_prefix")).execute();
            } else if (starts_with(*i, "sleep")) {
                SleepStmt(this, trailing(*i, "sleep")).execute();
            } else {
                cout << *i << endl;
            }
        }
        return true;
    }


    bool Statement::execute() {
        cout << "Statement::execute(" << arg() << ")" << endl;
        return true;
    }

    /** @todo make a map (or something like that) to call the right function for
    *        the string supplied as argument                                     */
    bool ObjectStmt::execute() {
        if (arg() == "Hypersponge") {
            parser()->getView()->ObjectHypersponge();
        } else {
            cout << "ObjectStmt::execute(" << arg() << ")" << endl;
        }
        return true;
    }

    /** @todo find out the type of the argument and call the corresponding function
    *                                                                            */
    bool ParmStmt::execute() {
        parser()->getView()->setParameter(leading(arg(), " "), Globals::Instance().atou(trailing(arg(), " ")));
        return true;
    }

    bool XformStmt::execute() {
        std::istringstream s(arg());
        VecMath::Rotation<4> r;
        s >> r;
        parser()->getView()->applyTransform(r, VecMath::Vector<4>());
        return true;
    }

    bool SleepStmt::execute() {
        usleep(Globals::Instance().atou(trailing(arg(), " "))*1000);
        return true;
    }
}
