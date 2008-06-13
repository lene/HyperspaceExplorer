
#include "Rotation.H"
#include "Vector.H"

#include <string>

class Parser;

namespace Script {

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

    class DeltaStmt: public XformStmt {
        public:
            DeltaStmt(const Parser *p, const std::string &_arg): XformStmt(p, _arg) { }
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
