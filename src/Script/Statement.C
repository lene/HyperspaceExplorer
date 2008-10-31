
#include "View.H"
#include "Parser.H"
#include "Statement.H"
#include "FunctionFactory.H"

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

    BoolStatement::BoolStatement(const Parser *p, const std::string &_arg):
            Statement(p, _arg) {
        m_bool = (_arg == "1" || _arg == "on" || _arg == "true");
    }

    SizeStmt::SizeStmt(const Parser *p, const std::string &_arg):
            Statement(p, _arg) {
        width = Globals::Instance().atou(leading(arg(), " "));
        height = Globals::Instance().atou(trailing(arg(), " "));
    }

    bool SizeStmt::execute() {
        parser()->getView()->setSize(width, height);
        return true;
    }

    /** @todo make a map (or something like that) to call the right function for
    *        the string supplied as argument                                     */
    bool ObjectStmt::execute() {
        Function *f = TheFunctionFactory::Instance().createFunction(arg());
        if (!f) return false;
        parser()->getView()->setF(f);
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
    
    bool RotStmt::execute() {
        throw BadStatementException(arg());
        return true;
    }

    bool DeltaStmt::execute() {
        parser()->getView()->setdR(r());
        return true;
    }

    bool RotDeltaStmt::execute() {
        throw BadStatementException(arg());
        return true;
    }

    FramesStmt::FramesStmt(const Parser *p, const std::string &_arg):
            Statement(p, _arg) {
        frames = Globals::Instance().atou(trailing(arg(), " "));
    }

    bool FramesStmt::execute() {
        parser()->getView()->setNumFrames(frames);
        return true;
    }

    LoopStmt::LoopStmt(const Parser *p, const std::string &_arg):
            Statement(p, _arg) {
        loops = Globals::Instance().atou(trailing(arg(), " "));
    }

    bool LoopStmt::execute() {
        parser()->getView()->setNumLoops(loops);
        return true;
    }

    bool ColorStmt::execute() {
        parser()->getView()->setColors(getValue());
        return true;
    }
    bool ShadingStmt::execute() {
        parser()->getView()->setShading(getValue());
        return true;
    }
    bool LightStmt::execute() {
        parser()->getView()->setLighting(getValue());
        return true;
    }
    bool TransStmt::execute() {
        parser()->getView()->setTransparence(getValue());
        return true;
    }
    bool WireStmt::execute() {
        parser()->getView()->setSolid(!getValue());
        return true;
    }
    bool SolidStmt::execute() {
        parser()->getView()->setSolid(getValue());
        return true;
    }
    bool FogStmt::execute() {
        parser()->getView()->setFog(getValue());
        return true;
    }
    bool Fog4DStmt::execute() {
        parser()->getView()->setHyperfog(getValue());
        return true;
    }
    bool CoordsStmt::execute(){
        throw BadStatementException(arg());
        return true;
    }

    bool AnimateStmt::execute() {
        parser()->getView()->animate();
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

    bool ImgDirStmt::execute() {
        parser()->getView()->setImgDir(arg());
        return true;
    }

    bool ImgPrefixStmt::execute() {
        parser()->getView()->setImgPrefix(arg());
        return true;
    }
    
    Statement *StatementFactory::createStatement(const Parser *p,
                                                 const std::string &line) {
        if (starts_with(line, "set_size")) {
            return new SizeStmt(p, trailing(line, "set_size"));
        } else if (starts_with(line, "object")) {
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
            return new RotStmt(p, trailing(line, "rotation"));
        } else if (starts_with(line, "parameter_step")) {
            return new Statement(p, trailing(line, "parameter_step"));
        } else if (starts_with(line, "transform_step")) {
            return new DeltaStmt(p, trailing(line, "transform_step"));
        } else if (starts_with(line, "rotation_step")) {
            return new RotDeltaStmt(p, trailing(line, "rotation_step"));
        } else if (starts_with(line, "frames")) {
            return new FramesStmt(p, trailing(line, "frames"));
        } else if (starts_with(line, "loop")) {
            return new LoopStmt(p, trailing(line, "loop"));
        } else if (starts_with(line, "start_animation")) {
            return new AnimateStmt(p);
        } else if (starts_with(line, "colors")) {
            return new ColorStmt(p, trailing(line, "colors"));
        } else if (starts_with(line, "shading")) {
            return new ShadingStmt(p, trailing(line, "shading"));
        } else if (starts_with(line, "lighting")) {
            return new LightStmt(p, trailing(line, "lighting"));
        } else if (starts_with(line, "transparence")) {
            return new TransStmt(p, trailing(line, "transparence"));
        } else if (starts_with(line, "wireframe")) {
            return new WireStmt(p, trailing(line, "wireframe"));
        } else if (starts_with(line, "depthcue3d")) {
            return new FogStmt(p, trailing(line, "depthcue3d"));
        } else if (starts_with(line, "depthcue4d")) {
            return new Fog4DStmt(p, trailing(line, "depthcue4d"));
        } else if (starts_with(line, "coordinates")) {
            return new CoordsStmt(p, trailing(line, "coordinates"));
        } else if (starts_with(line, "image_dir")) {
            return new ImgDirStmt(p, trailing(line, "image_dir"));
        } else if (starts_with(line, "image_prefix")) {
            return new ImgPrefixStmt(p, trailing(line, "image_prefix"));
        } else if (starts_with(line, "sleep")) {
            return new SleepStmt(p, trailing(line, "sleep"));
        }
        throw BadStatementException(line);
    }
}
