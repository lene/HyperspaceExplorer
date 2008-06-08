
#include "Parser.H"
#include "Statement.H"
#include "4DView.H"

#include <iostream>

using std::string;
using std::vector;

using std::cout;
using std::endl;

namespace Script {

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

    template <> bool ParmStmt<double>::execute() {
        parser()->getView()->setParameter(leading(arg(), " "),
                Globals::Instance().atod(trailing(arg(), " ")));
        return true;
    }

    template <> bool ParmStmt<int>::execute() {
        parser()->getView()->setParameter(leading(arg(), " "),
               Globals::Instance().atoi(trailing(arg(), " ")));
        return true;
    }

    template <> bool ParmStmt<unsigned>::execute() {
        parser()->getView()->setParameter(leading(arg(), " "),
               Globals::Instance().atou(trailing(arg(), " ")));
        return true;
    }

    template <> bool ParmStmt<std::string>::execute() {
        parser()->getView()->setParameter(leading(arg(), " "), trailing(arg(), " "));
        return true;
    }

    XformStmt::XformStmt(const Parser *p, const std::string &_arg):
            Statement(p, _arg) {
        std::istringstream s(arg());
        s >> m_r;
    }

    bool XformStmt::execute() {
        parser()->getView()->applyTransform(r(), VecMath::Vector<4>());
        return true;
    }

    bool DeltaStmt::execute() {
//        parser()->getView()->applyTransform(r(), VecMath::Vector<4>());
        cout << "DeltaStmt::execute(" << r() << ")\n";
        return true;
    }

    FramesStmt::FramesStmt(const Parser *p, const std::string &_arg):
            Statement(p, _arg) {
        frames = Globals::Instance().atou(trailing(arg(), " "));
    }

    bool FramesStmt::execute() {
        cout << "FramesStmt::execute(" << frames << ")\n";
        return true;
    }

    LoopStmt::LoopStmt(const Parser *p, const std::string &_arg):
            Statement(p, _arg) {
        loops = Globals::Instance().atou(trailing(arg(), " "));
    }

    bool LoopStmt::execute() {
        cout << "LoopStmt::execute(" << loops << ")\n";
        return true;
    }

    bool AnimateStmt::execute() {
        cout << "AnimateStmt::execute()\n";
        return true;
    }

    SleepStmt::SleepStmt(const Parser *p, const std::string &_arg):
            Statement(p, _arg) {
        msec = Globals::Instance().atou(trailing(arg(), " "));
    }

    bool SleepStmt::execute() {
        usleep(msec*1000);
        return true;
    }

    Statement *StatementFactory::createStatement(const Parser *p,
                                                 const std::string &line) {
        if (starts_with(line, "object")) {
            return new ObjectStmt(p, trailing(line, "object"));
        } else if (starts_with(line, "parameter double ")) {
            return new ParmStmt<double>(p, trailing(line, "parameter double"));
        } else if (starts_with(line, "parameter int ")) {
            return new ParmStmt<int>(p, trailing(line, "parameter int"));
        } else if (starts_with(line, "parameter unsigned ")) {
            return new ParmStmt<unsigned>(p, trailing(line, "parameter unsigned"));
        } else if (starts_with(line, "parameter string ")) {
            return new ParmStmt<std::string>(p, trailing(line, "parameter string"));
        } else if (starts_with(line, "transform ")) {
            return new XformStmt(p, trailing(line, "transform"));
        } else if (starts_with(line, "rotation ")) {
            return new Statement(p, trailing(line, "rotation"));
        } else if (starts_with(line, "parameter_step")) {
            return new Statement(p, trailing(line, "parameter_step"));
        } else if (starts_with(line, "transform_step")) {
            return new DeltaStmt(p, trailing(line, "transform_step"));
        } else if (starts_with(line, "rotation_step")) {
            return new Statement(p, trailing(line, "rotation_step"));
        } else if (starts_with(line, "frames")) {
            return new FramesStmt(p, trailing(line, "frames"));
        } else if (starts_with(line, "loop")) {
            return new LoopStmt(p, trailing(line, "loop"));
        } else if (starts_with(line, "start_animation")) {
            return new AnimateStmt(p);
        } else if (starts_with(line, "colors")) {
            return new Statement(p, trailing(line, "colors"));
        } else if (starts_with(line, "shading")) {
            return new Statement(p, trailing(line, "shading"));
        } else if (starts_with(line, "lighting")) {
            return new Statement(p, trailing(line, "lighting"));
        } else if (starts_with(line, "transparence")) {
            return new Statement(p, trailing(line, "transparence"));
        } else if (starts_with(line, "wireframe")) {
            return new Statement(p, trailing(line, "wireframe"));
        } else if (starts_with(line, "depthcue3d")) {
            return new Statement(p, trailing(line, "depthcue3d"));
        } else if (starts_with(line, "depthcue4d")) {
            return new Statement(p, trailing(line, "depthcue4d"));
        } else if (starts_with(line, "coordinates")) {
            return new Statement(p, trailing(line, "coordinates"));
        } else if (starts_with(line, "image_dir")) {
            return new Statement(p, trailing(line, "image_dir"));
        } else if (starts_with(line, "image_prefix")) {
            return new Statement(p, trailing(line, "image_prefix"));
        } else if (starts_with(line, "sleep")) {
            return new SleepStmt(p, trailing(line, "sleep"));
        }
        return new Statement(p, line);
    }
}
