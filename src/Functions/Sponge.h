
#if(!defined SPONGE_H)
#define SPONGE_H

#include "Object.h"

////////////////////////////////////////////////////////////////////////////////

/// An alternative hypersponge implementation with removal of duplicate faces
class AltSponge: public Hypercube {
public:
    /// AltSponge constructor
    /** @param _level hypersponge level
     *  @param _distance distance of subcubes to center to be counted as part of
     *    the fractal
     *      \li = 0: solid hypercube
     *      \li = 1: foam
     *      \li = 2: sponge
     *      \li = 3: dust
     *      \li >= 4: nothing
     *  @param _rad side_length/2
     *  @param _center center                                                 */
    AltSponge (unsigned _level = 1, unsigned _distance = 2, double _rad = 0.8,
            VecMath::Vector<4> _center = VecMath::Vector<4>(0., 0.,0., 0.));
    virtual ~AltSponge () { }

    virtual void SetParameters(const ParameterMap &parms) {
        std::cerr << "AltSponge::SetParameters(" << parms.toString() << ")\n";
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Level")
                    Level = i->second->toUnsigned();
                if (i->second->getName() == "Distance")
                    distance = i->second->toInt();
                if (i->second->getName() == "Size")
                    rad = i->second->toDouble();
            }
#       else
            setParameter(parms, this->Phase, "Phase");
#       endif
        }

    /** @return A string with a description of the Hypersponge object         */
    virtual std::string description () {
        std::ostringstream out;
        out << "Alternative Sponge (level = " << Level << ")" << std::ends;
        return out.str ();
    }

protected:
    virtual void Initialize();
    virtual unsigned long MemRequired (unsigned);

    /// Remove all duplicate vertices, leaving only unique values
    void reduceVertices();
    /// Remove all duplicate surfaces
    void removeDuplicateSurfaces();
    /// When a duplicate vertex is removed, let all surfaces referencing it point to the original vertex.
    /** Also, all vertices after the removed one are shifted up by one element,
     *  so the surfaces pointing to them must be updated too.
     *
     *  \param original_vertex The vertex, first in the vertex array, that is kept.
     *  \param duplicate_vertex The removed vertex.
     */
    void renumberSurfaces(unsigned original_vertex, unsigned duplicate_vertex);

    unsigned Level;                 ///< Level of the hypersponge
    int distance;                   ///< max. distance (see Initialize())
    double rad;                     ///< radius, more correctly size, of the sponge
    VecMath::Vector<4> center;      ///< center of the sponge
};

namespace {
    Function *createAltSponge() { return new AltSponge(); }
    const bool registeredAS = TheFunctionFactory::Instance().registerFunction(createAltSponge);
}

///////////////////////////////////////////////////////////////////////////////

/// A four-dimensional Menger Sponge.
/** A Menger Sponge in three dimensions is a fractal produced by subdividing
 *  a cube and taking away parts of the cube which get subsequentally
 *  smaller. The \em level parameter controls how often this process is repeated,
 *  i.e. how many holes there are in the final object.
 *
 *  A four-dimensional Menger Sponge is created analogously from a hypercube.
 *
 *  The fractal can be further controlled by the \em distance parameter:
 *  \li \em distance = 0: Only the innermost cube is removed, resulting in a
 *      four-dimensional foam with connected body and disjoint holes.
 *  \li \em distance = 1: the innermost and the next to innermost cubes are
 *      removed, which results in a foam in three dimensions, but has holes in
 *      the four-dimensional structure.
 *  \li \em distance = 2: the holes reach the surface of the cube, resulting in
 *      a sponge structure - both the holes and the cubes ("curd") are
 *      connected.
 *  \li \em distance = 3: only the corners of the hypercube remain, resulting in
 *      dust - the "curd" is disjoint, the holes are connected.
 *  \ingroup ObjectGroup                                                    */
class Sponge: public Hypercube {
public:
    /// Sponge constructor
    /** @param _level hypersponge level
     *  @param _distance distance of subcubes to center to be counted as part of
     *                   the fractal
     *                   \li = 0: solid hypercube
     *                   \li = 1: foam
     *                   \li = 2: sponge
     *                   \li = 3: dust
     *                   \li >= 4: nothing
     *  @param _rad side_length/2
     *  @param _center center                                                 */
    Sponge (unsigned _level = 1, unsigned _distance = 2, double _rad = 0.8,
            VecMath::Vector<4> _center = VecMath::Vector<4>(0., 0.,0., 0.));
    virtual ~Sponge ();

    virtual void Transform (const VecMath::Rotation<4> &R,
                            const VecMath::Vector<4> &T);
    virtual void Project (double ScrW, double CamW, bool DepthCue4D);
    virtual void Draw (UI::View *view);

    virtual void SetParameters(const ParameterMap &parms) {
        std::cerr << "Sponge::SetParameters(" << parms.toString() << ")\n";
#       if 1
            for (ParameterMap::const_iterator i = parms.begin();
                 i != parms.end(); ++i) {
                if (i->second->getName() == "Level")
                    Level = i->second->toUnsigned();
                if (i->second->getName() == "Distance")
                    distance = i->second->toInt();
                if (i->second->getName() == "Size")
                    rad = i->second->toDouble();
            }
#       else
            setParameter(parms, this->Phase, "Phase");
#       endif
        }

    /// Rebuild the Sponge if the parameters have changed
    virtual void ReInit (double, double, double,
                         double, double, double,
                         double, double, double) {
        List.clear();
        Object::ReInit(0,0,0,0,0,0,0,0,0);
    }

    /** @return A string with a description of the Hypersponge object         */
    virtual std::string description () {
        std::ostringstream out;
        out << "Sponge (level = " << Level << ")" << std::ends;
        return out.str ();
    }

protected:
    virtual void Initialize();
    virtual unsigned long MemRequired (unsigned);
    unsigned Level;                 ///< Level of the hypersponge

    /// List of sub-sponges (see Initialize())
    /** @todo Use smart pointers instead of a simple pointer-to-object        */
    std::vector<Hypercube *> List;

    int distance;                   ///< max. distance (see Initialize())
    double rad;                     ///< radius, more correctly size, of the sponge
    VecMath::Vector<4> center;      ///< center of the sponge
};

namespace {
    Function *createSponge() { return new Sponge(); }
    const bool registeredS = TheFunctionFactory::Instance().registerFunction(createSponge);
}

#endif
