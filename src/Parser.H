#ifndef PARSER_H
#define PARSER_H

#include "Parser.H"

#include <string>
#include <vector>
#include <stdexcept>

class C4DView;

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
        // currently defined interface follows; this is only a draft

        // statically set the state
        void setObject();
        void setParameters();
        void setTransform();

        // animation commands
        void setParametersStep();
        void setTransformStep();
        void setNumFrames(unsigned);
        void setLoop(unsigned);

        // view states
        void setColors(bool);
        void setShade(bool);
        void setLighting(bool);
        void setTransparent(bool);
        void setWireframe(bool);
        void setDepthcue3D(bool);
        void setDepthcue4D(bool);
        void setCoordinates(bool);

        // saving as images
        void setRenderToImages(bool);
        void setImageDir(const std::string &);
        void setImagePrefix(const std::string &);
        void setMaxFrames(unsigned);

    private:
        std::vector<std::string> lines;
        C4DView *view;
};

class Statement {
    public:
        Statement(const Parser *_parser, const std::string &_arg):
            m_arg(_arg), m_parser(_parser) { }
        virtual bool execute();
        const std::string &arg() { return m_arg; }
        const Parser *parser() { return m_parser; }
        
    private:
        std::string m_arg;
        const Parser *m_parser;
};

class ObjectStmt: public Statement {
    public:
        ObjectStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
        virtual bool execute();
};

class ParmStmt: public Statement {
    public:
        ParmStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
        virtual bool execute();
};

class XformStmt: public Statement {
    public:
        XformStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
        virtual bool execute();
};

class SleepStmt: public Statement {
    public:
        SleepStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
        virtual bool execute();
};

#endif
