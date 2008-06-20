
#include "Rotation.H"
#include "Vector.H"

#include <string>

class Parser;

namespace Script {

    class BadStatementException: public std::runtime_error {
        public:
                BadStatementException(const std::string &what):
                    std::runtime_error(what) { }
    };

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

    class BoolStatement: public Statement {
        public:
            BoolStatement (const Parser *p, const std::string &_arg);
            virtual bool execute() = 0;

        protected:
            bool getValue() { return m_bool; }

        private:
            bool m_bool;
    };

    class SizeStmt: public Statement {
        public:
            SizeStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();
        private:
            unsigned width;
            unsigned height;
    };

    class ObjectStmt: public Statement {
        public:
            ObjectStmt(const Parser *p, const std::string &_arg):
                    Statement(p, _arg) { }
            virtual bool execute();
    };

    template <typename T = unsigned> class ParmStmt: public Statement {
        public:
            ParmStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
            virtual bool execute();
    };

    class XformStmt: public Statement {
        public:
            XformStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();

        protected:
            VecMath::Rotation<4> &r() { return m_r; }

        private:
            VecMath::Rotation<4> m_r;
    };

    class RotStmt: public XformStmt {
        public:
            RotStmt(const Parser *p, const std::string &_arg): XformStmt(p, _arg) { }
            virtual bool execute();
    };

    class DeltaStmt: public XformStmt {
        public:
            DeltaStmt(const Parser *p, const std::string &_arg): XformStmt(p, _arg) { }
            virtual bool execute();
    };

    class RotDeltaStmt: public DeltaStmt {
        public:
            RotDeltaStmt(const Parser *p, const std::string &_arg): DeltaStmt(p, _arg) { }
            virtual bool execute();
    };

    class FramesStmt: public Statement {
        public:
            FramesStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();
        private:
            unsigned frames;
    };

    class LoopStmt: public Statement {
        public:
            LoopStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();
        private:
            unsigned loops;
    };

    class ColorStmt: public BoolStatement {
        public:
            ColorStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };
    
    class ShadingStmt: public BoolStatement {
        public:
            ShadingStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    class LightStmt: public BoolStatement {
        public:
            LightStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    class TransStmt: public BoolStatement {
        public:
            TransStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    class WireStmt: public BoolStatement {
        public:
            WireStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    class FogStmt: public BoolStatement {
        public:
            FogStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    class Fog4DStmt: public BoolStatement {
        public:
            Fog4DStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    class CoordsStmt: public BoolStatement {
        public:
            CoordsStmt(const Parser *p, const std::string &_arg): BoolStatement(p, _arg) { }
            virtual bool execute();
    };

    class AnimateStmt: public Statement {
        public:
            AnimateStmt(const Parser *p): Statement(p, "") { }
            virtual bool execute();
    };

    class SleepStmt: public Statement {
        public:
            SleepStmt(const Parser *p, const std::string &_arg);
            virtual bool execute();
        private:
            unsigned msec;
    };

    class ImgDirStmt: public Statement {
        public:
            ImgDirStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
            virtual bool execute();
    };

    class ImgPrefixStmt: public Statement {
        public:
            ImgPrefixStmt(const Parser *p, const std::string &_arg): Statement(p, _arg) { }
            virtual bool execute();
    };

    class StatementFactory {
        public:
            static Statement *createStatement(const Parser *, const std::string &);
    };
}
