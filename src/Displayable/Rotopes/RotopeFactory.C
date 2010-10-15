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


#include "RotopeFactory.h"
#include "Extrude.h"
#include "Taper.h"
#include "Rotate.h"
#include "Torate.h"

using std::string;

/** \param actions List of extrusion actions to perform
 *  \param rotope Vertices to perform the extrusions on
 *  \return New list of vertices, augmented by the extrusion
 */
template <unsigned D, unsigned d>
VertexData<D> *RotopeFactory::RotopeAction<D, d>::operator()(string actions,
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
      throw BadRotopeOperation("RotopeFactory::performAction()", string(1, action));
  }
}

template <unsigned D>
VertexData<D> *RotopeFactory::RotopeAction<D, 0>::operator()(string actions,
                                                             VertexData<D> *rotope) {
  switch(actions[0]) {
    case 'E': case 'e':
      return new Extrude<D, 0, 0>(*rotope);
      break;
    default:
      throw BadRotopeOperation("RotopeFactory::performAction()",
                               "First operation must be extrusion");
  }
  return rotope;
}

/** Takes a list of extrusion actions as string and creates a Rotope of the
 *  actions, performing them in the order in which they were specified
 *  \param actions The list of extrusion operations
 *  \return Rotope generated from \p actions
 */
RotopeInterface *RotopeFactory::generate(const std::string &actions) {
    switch (actions.length()) {
        case 0: case 1:
            throw std::logic_error("RotopeFactory::generate() must be called"
                    " with a dimension of at least 2");
            break;
        case 2: {
            VertexData<4> tmp;
            RotopeAction<4,1> perform;
            return perform(actions, &tmp);
        }
        case 3: {
            VertexData<4> tmp;
            RotopeAction<4,2> perform;
            return perform(actions, &tmp);
        }
        case 4: {
            VertexData<4> tmp;
            RotopeAction<4,3> perform;
            return perform(actions, &tmp);
        }
        case 5: {
            VertexData<5> tmp;
            RotopeAction<5,4> perform;
            return perform(actions, &tmp);
        }
        case 6: {
            VertexData<6> tmp;
            RotopeAction<6,5> perform;
            return perform(actions, &tmp);
        }
        case 7: {
            VertexData<7> tmp;
            RotopeAction<7,6> perform;
            return perform(actions, &tmp);
        }
        case 8: {
            VertexData<8> tmp;
            RotopeAction<8,7> perform;
            return perform(actions, &tmp);
        }
        case 9: {
            VertexData<9> tmp;
            RotopeAction<9,8> perform;
            return perform(actions, &tmp);
        }
        case 10: {
            VertexData<10> tmp;
            RotopeAction<10,9> perform;
            return perform(actions, &tmp);
        }
        default:
            throw NotYetImplementedException("RotopeFactory::generate(): "
                    "Rotopes of dimensions higher than 10 currently not "
                    "supported");
    }

    // This is needed to prevent a compiler warning about not returning void
    return new VertexData<4>;
}
