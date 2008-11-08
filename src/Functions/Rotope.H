#ifndef ROTOPE_H
#define ROTOPE_H

#include <Object.H>
#include "VertexData.H"

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

        virtual void Transform (const VecMath::Rotation<4> &,
                                const VecMath::Vector<4> &);
        virtual void Draw (void);

        /** \return The name of the function in cleartext                     */
//        virtual QString getFunctionName() const { return "Rotope"; }
    private:
        /// Actual rotope object to which all functions are delegated
        RotopeBase *_rotope;
};

#endif
