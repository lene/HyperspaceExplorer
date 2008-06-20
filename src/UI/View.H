//
// C++ Interface: View
//
// Description: 
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef VIEW_H
#define VIEW_H 1

#include "ParameterMap.H"

class Function;

namespace UI {

    class View {
        class FunctionNotSupportedException: public std::runtime_error {
            public:
                FunctionNotSupportedException(const std::string &what):
                    std::runtime_error(what) { }
        };

        public:
            View(): numFrames(1), numLoops(1) { }

            /// Makes setting a parameter from the outside possible
            /** @param parmName Name of the parameter, as defined in the Function
            *  @param value Parameter value. Type must match exactly.            */
            template <typename T>
                    void setParameter(const std::string &parmName, const T &value) {
                ApplyChanges(ParameterMap(parmName, value));
            }

            virtual void applyTransform(const VecMath::Rotation<4> &R,
                                        const VecMath::Vector<4> &T) = 0;

            virtual void ObjectHypercube() = 0;
            virtual void ObjectHyperpyramid() = 0;
            virtual void ObjectHypersponge() = 0;
            virtual void ObjectGasket() = 0;

            virtual void setFunction(Function *) = 0;

            virtual void setdR(const VecMath::Rotation<4> &_dr) = 0;

            virtual void setNumFrames(unsigned _numFrames) { numFrames =_numFrames; }
            virtual void setNumLoops(unsigned _numLoops) { numLoops =_numLoops; }

            virtual void animate() = 0;

            virtual void setImgDir(const std::string &) = 0;
            virtual void setImgPrefix(const std::string &) = 0;

            virtual void setSize(unsigned, unsigned) = 0;

            virtual void setColors(bool) = 0;
            virtual void setShading(bool) = 0;
            virtual void setLighting(bool) = 0;
            virtual void setTransparence(bool) = 0;
            virtual void setWireframe(bool) = 0;
            virtual void setFog(bool) = 0;
            virtual void setHyperfog(bool) = 0;
            virtual void setCoordinates(bool) {
                throw FunctionNotSupportedException("setCoordinates()");
            }

        protected:
            virtual void ApplyChanges(const ParameterMap &) = 0;

            virtual unsigned getNumFrames() { return numFrames; }
            virtual unsigned getNumLoops() { return numLoops; }

        private:
            unsigned numFrames;
            unsigned numLoops;
    };

}

#endif
