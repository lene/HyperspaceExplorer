
#include "Rotation.H"
#include "Vector.H"

#include <string>

class Parser;

/// \defgroup ScriptingGroup Scripting

namespace Script {

    /// exception thrown when an unknown statement is encountered in a script
    /** \ingroup ScriptingGroup                                               */
    class BadStatementException: public std::runtime_error {
        public:
            /// Create a BadStatementException
            BadStatementException(const std::string &what):
                std::runtime_error(what) { }
    };

    /// \defgroup StatementGroup Statements possible in a script
    /// \ingroup ScriptingGroup

    /// Base class for all possible statements in a script
    /** This class represents the class AbstractExpression in the class diagram
     *  for the Interpreter pattern as implemented in the GOF book, p. 245
     *  \ingroup StatementGroup                                               */
    class Statement {

        public:
            /** \param parser The context in which the Statement is executed
             *  \param arg The argument supplied to the Statement
             */
            Statement(const Parser *parser, const std::string &arg):
                _arg(arg), _parser(parser) { }
            /// Executes the statement in the current context
            virtual bool execute();

        protected:
            /// \return Argument(s) following the statement
            const std::string &arg() { return _arg; }
            /// \return The current context
            const Parser *parser() { return _parser; }

        private:
            std::string _arg;       ///< Argument(s) following the statement
            const Parser *_parser;  ///< The current context
    };

    /// Statement with a single boolean parameter
    /** \ingroup StatementGroup                                               */
    class BoolStatement: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            BoolStatement (const Parser *p, const std::string &_arg);
            /// Executes the statement in the current context
            virtual bool execute() = 0;

        protected:
            /// \return The current state
            bool getValue() { return _bool; }

        private:
            bool _bool;         ///< The current state
    };

    /// "size <width> <height>"
    /** sets the width and height of the viewport
     *  \ingroup StatementGroup                 */
    class SizeStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            SizeStmt(const Parser *p, const std::string &_arg);
            /// Executes the statement in the current context
            virtual bool execute();
        private:
            unsigned _width;    ///< Width of the viewport
            unsigned _height;   ///< Height of the viewport
    };

    /// "object <object_name>"
    /** sets the object to be displayed to the supplied type
     *  \ingroup StatementGroup                                 */
    class ObjectStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            ObjectStmt(const Parser *p, const std::string &_arg):
                    Statement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "parameter <double|int|unsigned|string> <parameter>"
    /** sets a parameter of the specified type to the object defined before
     *  \ingroup StatementGroup                                               */
    template <typename T = unsigned> class ParmStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            ParmStmt(const Parser *p, const std::string &_arg):
                Statement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "transform <rotation>"
    /** sets the transform of the current object
     *  \todo add support for translations and 3D rotation
     *  \ingroup StatementGroup                                               */
    class XformStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            XformStmt(const Parser *p, const std::string &_arg);
            /// Executes the statement in the current context
            virtual bool execute();

        protected:
            /// \return The rotation state of the object
            VecMath::Rotation<4> &r() { return _r; }

        private:
            VecMath::Rotation<4> _r;    ///< The rotation state of the object
    };

    /// "rotation <rotation>"
    /** not yet implemented
     *  \todo implement
     *  \ingroup StatementGroup                                               */
    class RotStmt: public XformStmt {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            RotStmt(const Parser *p, const std::string &_arg):
                XformStmt(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "transform_step <rotation>"
    /** sets the amount of rotation that takes place between two consecutive
     *  frames
     *  \ingroup StatementGroup                                               */
    class DeltaStmt: public XformStmt {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            DeltaStmt(const Parser *p, const std::string &_arg):
                XformStmt(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "rotation_step <rotation>"
    /** not yet implemented
     *  \todo implement
     *  \ingroup StatementGroup                                               */
    class RotDeltaStmt: public DeltaStmt {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            RotDeltaStmt(const Parser *p, const std::string &_arg):
                DeltaStmt(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "frames <num_frames>"
    /** set the number of frames to display
     *  \ingroup StatementGroup                                               */
    class FramesStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            FramesStmt(const Parser *p, const std::string &_arg);
            /// Executes the statement in the current context
            virtual bool execute();
        private:
            unsigned _frames;   ///< Number of frames to display
    };

    /// "loop <num_loops>"
    /** set the number of loops, ie. repetitions of \p num_frames frames
     *  \ingroup StatementGroup                                               */
    class LoopStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            LoopStmt(const Parser *p, const std::string &_arg);
            /// Executes the statement in the current context
            virtual bool execute();
        private:
            unsigned _loops;    ///< Number of times to loop
    };

    /// "color <bool>"
    /** coloring on/off
     *  \ingroup StatementGroup                                               */
    class ColorStmt: public BoolStatement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            ColorStmt(const Parser *p, const std::string &_arg):
                BoolStatement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "shading <bool>"
    /** shading on/off
     *  \ingroup StatementGroup                                               */
    class ShadingStmt: public BoolStatement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            ShadingStmt(const Parser *p, const std::string &_arg):
                BoolStatement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "lighting <bool>"
    /** lighting on/off
     *  \ingroup StatementGroup                                               */
    class LightStmt: public BoolStatement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            LightStmt(const Parser *p, const std::string &_arg):
                BoolStatement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "transparence <bool>"
    /** transparence on/off
     *  \ingroup StatementGroup                                               */
    class TransStmt: public BoolStatement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            TransStmt(const Parser *p, const std::string &_arg):
                BoolStatement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "wireframe <bool>"
    /** wireframe on/off
     *  \ingroup StatementGroup                                               */
    class WireStmt: public BoolStatement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            WireStmt(const Parser *p, const std::string &_arg):
                BoolStatement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "solid <bool>"
    /** solid on/off - opposite of wireframe on/off
     *  \ingroup StatementGroup                                               */
    class SolidStmt: public BoolStatement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            SolidStmt(const Parser *p, const std::string &_arg):
                BoolStatement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "depthcue3d <bool>"
    /** depth cue on/off
     *  \ingroup StatementGroup                                               */
    class FogStmt: public BoolStatement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            FogStmt(const Parser *p, const std::string &_arg):
                BoolStatement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "depthcue4d <bool>"
    /** 4D depth cue on/off
     *  \ingroup StatementGroup                                               */
    class Fog4DStmt: public BoolStatement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            Fog4DStmt(const Parser *p, const std::string &_arg):
                BoolStatement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "coordinates <bool>"
    /** coordinate cross on/off
     *  \ingroup StatementGroup                                               */
    class CoordsStmt: public BoolStatement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            CoordsStmt(const Parser *p, const std::string &_arg):
                BoolStatement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "animate"
    /** start the animation with the current parameters
     *  \ingroup StatementGroup                                               */
    class AnimateStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             */
            AnimateStmt(const Parser *p): Statement(p, "") { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "sleep <milliseconds>"
    /** pause for the specified amount of time
     *  \ingroup StatementGroup                                               */
    class SleepStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            SleepStmt(const Parser *p, const std::string &_arg);
            /// Executes the statement in the current context
            virtual bool execute();
        private:
            unsigned _msec;     ///< Number of milliseconds to sleep
    };

    /// "image_dir <directory>"
    /** where to store images from now on
     *  \ingroup StatementGroup                                               */
    class ImgDirStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            ImgDirStmt(const Parser *p, const std::string &_arg):
                Statement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// "image_prefix <filename_prefix>"
    /** how to begin filenames for images
     *  \ingroup StatementGroup                                               */
    class ImgPrefixStmt: public Statement {
        public:
            /** \param p The context in which the Statement is executed
             *  \param _arg The argument supplied to the Statement
             */
            ImgPrefixStmt(const Parser *p, const std::string &_arg):
                Statement(p, _arg) { }
            /// Executes the statement in the current context
            virtual bool execute();
    };

    /// Factory object, creates Statement objects from a Parser and a given line
    /** \ingroup StatementGroup                                               */
    class StatementFactory {
        public:
            /// The Factory method
            static Statement *createStatement(const Parser *,
                                              const std::string &);
    };
}
