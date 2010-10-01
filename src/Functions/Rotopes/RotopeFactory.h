/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2008-2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/


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
        /** \tparam D Dimension of vector space we operate in
         *  \tparam d Dimension we want to extrude into
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
        /** \tparam D Dimension of vector space we operate in
         */
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
