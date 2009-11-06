///
/// C++ Implementation: Rotope
///
/// Description:
///
///
/// \author Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///

#include "RotopeFactory.h"
#include "Extrude.h"
#include "Taper.h"
#include "Rotate.h"
#include "Torate.h"

using std::string;

/** Takes a list of extrusion actions as string and creates a Rotope of the
 *  actions, performing them in the order in which they were specified
 *  \param actions The list of extrusion operations
 *  \return Rotope generated from \p actions
 */
RotopeBase *RotopeFactory::generate(const std::string &actions) {
    switch (actions.length()) {
        case 0: case 1: // case 2: case 3:
            throw std::logic_error("RotopeFactory::generate() must be called"
                    " with a dimension of at least 4");
            break;
        case 2: {
            vertex_data<4> tmp;
            RotopeAction<4,1> perform;
            return perform(actions, &tmp);
        }
        case 3: {
            vertex_data<4> tmp;
            RotopeAction<4,2> perform;
            return perform(actions, &tmp);
        }
        case 4: {
            vertex_data<4> tmp;
            RotopeAction<4,3> perform;
            return perform(actions, &tmp);
        }
        case 5: {
            vertex_data<5> tmp;
            RotopeAction<5,4> perform;
            return perform(actions, &tmp);
        }
        case 6: {
            vertex_data<6> tmp;
            RotopeAction<6,5> perform;
            return perform(actions, &tmp);
        }
        case 7: {
            vertex_data<7> tmp;
            RotopeAction<7,6> perform;
            return perform(actions, &tmp);
        }
        case 8: {
            vertex_data<8> tmp;
            RotopeAction<8,7> perform;
            return perform(actions, &tmp);
        }
        case 9: {
            vertex_data<9> tmp;
            RotopeAction<9,8> perform;
            return perform(actions, &tmp);
        }
        case 10: {
            vertex_data<10> tmp;
            RotopeAction<10,9> perform;
            return perform(actions, &tmp);
        }
        default:
            throw NotYetImplementedException("RotopeFactory::generate(): "
                    "Rotopes of dimensions higher than 10 currently not "
                    "supported");
    }

    // This is needed to prevent a compiler warning about not returning void
    return new vertex_data<4>;
}
