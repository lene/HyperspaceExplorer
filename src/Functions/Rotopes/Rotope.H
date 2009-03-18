#ifndef ROTOPE_H
#define ROTOPE_H

#include "Object.H"
#include "VertexData.H"

/// Gets thrown when an operation is not yet (or will never be) supported
/** \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
class BadRotopeOperation: public std::logic_error {
    public:
        /// Create a BadRotopeOperation
        /** \param caller The function name throwing the BadRotopeOperation
         *  \param op The unsupported operation \p caller wanted to perform
         */
        BadRotopeOperation(const std::string &caller, const std::string &op):
            std::logic_error(caller+": "+"Unsupported action \""+op+"\"") {}
};

/// A four-dimensional <a href="http://teamikaria.com/wiki/Rotope">Rotope</a>.
/** \ingroup RotopeGroup
 *  \author Helge Preuss <scout@hyperspace-travel.de>
 */
class Rotope : public Object {

    const static unsigned DIM = 6;      ///< Default dimension of Rotope objects

    public:
        /// Construct a default Rotope (\p DIM -dimensional hypercube).
        Rotope();
        /// Execute a series of extrusions to construct a Rotope
        Rotope(const std::string &);

        ~Rotope();

        /// Execute the desired extrude actions and declare FunctionParameter s
        virtual void Initialize();

        /// Transforms a Rotope
        virtual void Transform (const VecMath::Rotation<4> &,
                                const VecMath::Vector<4> &);
        /// Draw the projected Rotope (onto screen or into GL list, in fact)
        virtual void Draw (void);

        /// Set parameters to the Function
        virtual void SetParameters(const ParameterMap &parms);

    private:
        /// Rotation in 5-space (for objects of dimension >= 5)
        VecMath::Rotation<5> _rot5D;
        /// Rotation in 6-space (for objects of dimension >= 6)
        VecMath::Rotation<6> _rot6D;
        /// Rotation in 7-space (for objects of dimension >= 7)
        VecMath::Rotation<7> _rot7D;
        /// Rotation in 8-space (for objects of dimension >= 8)
        VecMath::Rotation<8> _rot8D;
        /// Rotation in 9-space (for objects of dimension >= 9)
        VecMath::Rotation<9> _rot9D;
        /// Rotation in 10-space (for objects of dimension >= 10)
        VecMath::Rotation<10> _rot10D;
        /// Number of segments approximating the object in rotation operations
        unsigned _numSegments;

        void Draw(const Realm &);

        /// Sequence of extrusion actions needed to generate the Rotope
        std::string _actions;
        /// Actual rotope object to which all functions are delegated
        RotopeBase *_rotope;
};

#endif
