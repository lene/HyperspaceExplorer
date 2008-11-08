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

#include "Rotope.H"
#include "Extrude.H"
#include "Taper.H"
#include "Rotate.H"
#include "Torate.H"

using std::string;

/// A very primitive class to generate Rotopes
class RotopeFactory {
    public:
    /// Generate a Rotope
    static RotopeBase *generate(const std::string &actions);

    private:

        template <unsigned D, unsigned d> class RotopeAction:
        public RotopeAction<D, d-1> {
            public:
                vertex_data<D> *operator()(std::string actions,
                                           vertex_data<D> *rotope) {
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
                        throw BadRotopeOperation(string("RotopeFactory::performAction(): "
                                "Unsupported action \"")+action+string("\""));
                }
                }
        };

        template <unsigned D> class RotopeAction<D, 0> {
            public:
                vertex_data<D> *operator()(std::string actions,
                                           vertex_data<D> *rotope) {
                    switch(actions[0]) {
                        case 'E': case 'e':
                            return new Extrude<D, 0, 0>(*rotope);
                            break;
                        default:
                            throw BadRotopeOperation("RotopeFactory::performAction()"
                                ": First operation must be an extrusion");

                    }
                    return rotope;
                }
        };
};
