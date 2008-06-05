#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stdexcept>

class C4DView;

/// Parser reads a file and executes the commands in it in a C4DView
/**
    @author Helge Preuss <scout@hyperspace-travel.de>                         */
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
        void execute();

        /// define the view we operate on
        void setView(C4DView *);

    private:
        // currently defined interface follows; this is only a draft

        // statically set the state
        void setObject();
        void setParameters();
        void setTransform();

        // animation commands
        void setStartTransform();
        void setEndTransform();
        void setStartParameters();
        void setEndParameters();
        void setSteps(unsigned);
        void setLoop(bool);
        void animate(void);

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
};

#endif
