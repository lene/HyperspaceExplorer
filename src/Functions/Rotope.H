#ifndef ROTOPE_H
#define ROTOPE_H

#include <Object.H>
#include "VertexData.H"

class BadRotopeOperation: public std::logic_error {
    public:
        BadRotopeOperation(const std::string &what): std::logic_error(what) {}
};

/// A four-dimensional <a href="http://teamikaria.com/wiki/Rotope">Rotope</a>.
/** \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
class Rotope : public Object {

    const static unsigned DIM = 6;      ///< Dimension of the Rotope object

    public:
        /// Construct a Rotope. Not yet implemented properly.
        Rotope();
        /// Execute a series of extrusions to construct a Rotope
        Rotope(const std::string &);

        ~Rotope();

        virtual void Initialize();

        virtual void Transform (const VecMath::Rotation<4> &,
                                const VecMath::Vector<4> &);
        virtual void Draw (void);
        virtual void SetParameters(const ParameterMap &parms) {
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                     if (i->second->getName() == "Generator")
                         _actions = std::string(*i->second);
                 }
#       else
                 setParameter(parms, this->_actions, "Generator");
#       endif
        }


        /** \return The name of the function in cleartext                     */
//        virtual QString getFunctionName() const { return "Rotope"; }
    private:
        /// Sequence of extrusion actions needed to generate the Rotope
        std::string _actions;
        /// Actual rotope object to which all functions are delegated
        RotopeBase *_rotope;
};

#endif
