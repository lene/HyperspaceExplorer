
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
            Statement(const Parser *_parser, const std::string &_arg):
                m_arg(_arg), m_parser(_parser) { }
            virtual bool execute();

        protected:
            const std::string &arg() { return m_arg; }
            const Parser *parser() { return m_parser; }

        private:
            std::string m_arg;
            const Parser *m_parser;
    };

    /// Statement with a single boolean parameter
    /** \ingroup StatementGroup                                               */
    class BoolStatement: public Statement {
        public:
            BoolStatement (const Parser *p, const std::string &_arg);
            virtual bool execute() = 0;

        protected:
            bool getValue() { return m_bool; }

        private:
            bool m_bool;
    };

    /// "size \em{width} \em{height} "
    /** sets the width and height of the viewport
     *  \ingroup StatementGroup                 */
    class SizeStmt: public Statement {
        public:
            SizeStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();
        private:
            unsigned width;
            unsigned height;
    };

    /// "object \em{object_name}"
    /** sets the object to be displayed to the supplied type
     *  \ingroup StatementGroup                                 */
    class ObjectStmt: public Statement {
        public:
            ObjectStmt(const Parser *p, const std::string &_arg):
                    Statement(p, _arg) { }
            virtual bool execute();
    };

    /// "parameter \em{double|int|unsigned|string} \em{parameter}"
    /** sets a parameter of the specified type to the object defined before
     *  \ingroup StatementGroup                                               */
    template <typename T = unsigned> class ParmStmt: public Statement {
        public:
            ParmStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
            virtual bool execute();
    };

    /// "transform \em{rotation}"
    /** sets the transform of the current object
     *  \todo add support for translations and 3D rotation
     *  \ingroup StatementGroup                                               */
    class XformStmt: public Statement {
        public:
            XformStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();

        protected:
            VecMath::Rotation<4> &r() { return m_r; }

        private:
            VecMath::Rotation<4> m_r;
    };

    /// "rotation \em{rotation}"
    /** not yet implemented
     *  \todo implement
     *  \ingroup StatementGroup                                               */
    class RotStmt: public XformStmt {
        public:
            RotStmt(const Parser *p, const std::string &_arg): XformStmt(p, _arg) { }
            virtual bool execute();
    };
    
    /// "transform_step \em{rotation}"
    /** sets the amount of rotation that takes place between two consecutive 
     *  frames
     *  \ingroup StatementGroup                                               */
    class DeltaStmt: public XformStmt {
        public:
            DeltaStmt(const Parser *p, const std::string &_arg): XformStmt(p, _arg) { }
            virtual bool execute();
    };

    /// "rotation_step \em{rotation}"
    /** not yet implemented
     *  \todo implement
     *  \ingroup StatementGroup                                               */
    class RotDeltaStmt: public DeltaStmt {
        public:
            RotDeltaStmt(const Parser *p, const std::string &_arg): DeltaStmt(p, _arg) { }
            virtual bool execute();
    };

    /// "frames \em{num_frames}"
    /** set the number of frames to display
     *  \ingroup StatementGroup                                               */
    class FramesStmt: public Statement {
        public:
            FramesStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();
        private:
            unsigned frames;
    };

    /// "loop \em{num_loops}"
    /** set the number of loops, ie. repetitions of \em{num_frames} frames
     *  \ingroup StatementGroup                                               */
    class LoopStmt: public Statement {
        public:
            LoopStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();
        private:
            unsigned loops;
    };
    
    /// "color \em{bool}"
    /** coloring on/off
     *  \ingroup StatementGroup                                               */
    class ColorStmt: public BoolStatement {
        public:
            ColorStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };
    
    /// "shading \em{bool}"
    /** shading on/off
     *  \ingroup StatementGroup                                               */
    class ShadingStmt: public BoolStatement {
        public:
            ShadingStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    /// "lighting \em{bool}"
    /** lighting on/off
     *  \ingroup StatementGroup                                               */
    class LightStmt: public BoolStatement {
        public:
            LightStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };
    
    /// "transparence \em{bool}"
    /** transparence on/off
     *  \ingroup StatementGroup                                               */
    class TransStmt: public BoolStatement {
        public:
            TransStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };
    
    /// "wireframe \em{bool}"
    /** wireframe on/off
     *  \ingroup StatementGroup                                               */
    class WireStmt: public BoolStatement {
        public:
            WireStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };
    
    /// "depthcue3d \em{bool}"
    /** depth cue on/off
     *  \ingroup StatementGroup                                               */
    class FogStmt: public BoolStatement {
        public:
            FogStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    /// "depthcue4d \em{bool}"
    /** 4D depth cue on/off
     *  \ingroup StatementGroup                                               */
    class Fog4DStmt: public BoolStatement {
        public:
            Fog4DStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    /// "coordinates \em{bool}"
    /** coordinate cross on/off
     *  \ingroup StatementGroup                                               */
    class CoordsStmt: public BoolStatement {
        public:
            CoordsStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    /// "animate"
    /** start the animation with the current parameters
     *  \ingroup StatementGroup                                               */
    class AnimateStmt: public Statement {
        public:
            AnimateStmt(const Parser *p): Statement(p, "") { }
            virtual bool execute();
    };

    /// "sleep \em{milliseconds}"
    /** pause for the specified amount of time
     *  \ingroup StatementGroup                                               */
    class SleepStmt: public Statement {
        public:
            SleepStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();
        private:
            unsigned msec;
    };

    /// "image_dir \em{directory}"
    /** where to store images from now on
     *  \ingroup StatementGroup                                               */
    class ImgDirStmt: public Statement {
        public:
            ImgDirStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
            virtual bool execute();
    };

    /// "image_prefix \em{filename_prefix}"
    /** how to begin filenames for images
     *  \ingroup StatementGroup                                               */
    class ImgPrefixStmt: public Statement {
        public:
            ImgPrefixStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
            virtual bool execute();
    };

    /// Factory object to create Statement objects from a Parser and a given line
    /** \ingroup StatementGroup                                               */
    class StatementFactory {
        public:
            static Statement *createStatement(const Parser *, const std::string &);
    };
}
