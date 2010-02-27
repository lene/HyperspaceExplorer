///
/// C++ Implementation: Rotope
///
/// Description:
///
///
/// \author Helge Preuss <lene.preuss@gmail.com>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#include "Extrude.h"
#include "Taper.h"
#include "Rotate.h"
#include "Torate.h"

using std::string;

/// A class to generate Rotopes
/** Sports a static method generate() which takes a list of extrusion actions as
 *  string and creates a Rotope of the actions, performing them in the order in
 *  which they were specified
 *
 *  \ingroup RotopeGroup
 */
class RotopeFactory {
    public:
        /// Generate a Rotope
        static RotopeInterface *generate(const std::string &actions);

    private:
        /// Functor class to perform an extrusion on a Rotope or vertex array
        /** \param D Dimension of vector space we operate in
         *  \param d Dimension we want to extrude into
         */
        template <unsigned D, unsigned d> class RotopeAction:
                public RotopeAction<D, d-1> {
            public:
                /// Perform the extrusion operations
                /** \param actions List of extrusion actions to perform
                 *  \param rotope Vertices to perform the extrusions on
                 *  \return New list of vertices, augmented by the extrusion
                 */
                VertexData<D> *operator()(std::string actions,
                                           VertexData<D> *rotope) {
                if (d >= D) {
                    throw std::logic_error("RotopeFactory::performAction() called "
                            "on a higher dimension than the vector space allows");
                }

                if (actions.empty()) return rotope;

                char action = actions[d];
                actions.erase(d);
                rotope = RotopeAction<D, d-1>::operator()(actions, rotope);

                switch(action) {
                    case 'E': case 'e':
                        return new Extrude<D, d, d>(*rotope);
                        break;
                    case 'T': case 't':
                        return new Taper<D, d, d>(*rotope);
                        break;
                    case 'R': case 'r':
                        return new Rotate<D, d, d>(*rotope);
                        break;
                    case 'D': case 'd':
                        return new Torate<D, d, d>(*rotope);
                        break;
                    default:
                        throw BadRotopeOperation("RotopeFactory::performAction()",
                                                 std::string(1, action));
                }
            }
        };

        /// Specialization for extruding into the dimension 0 to end recursion
        template <unsigned D> class RotopeAction<D, 0> {
            public:
                /// Perform the extrusion operations
                VertexData<D> *operator()(std::string actions,
                                           VertexData<D> *rotope) {
                    switch(actions[0]) {
                        case 'E': case 'e':
                            return new Extrude<D, 0, 0>(*rotope);
                            break;
                        default:
                            throw BadRotopeOperation("RotopeFactory::performAction()",
                                                     "First operation must be "
                                                        "extrusion");

                    }
                    return rotope;
                }
        };
};
