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
    static RotopeBase *generate(const std::string &actions) {
        RotopeBase *tmp;
        switch (actions.length()) {
            case 0: case 1: case 2: case 3:
                throw std::logic_error("RotopeFactory::generate() must be called"
                        " with a dimension of at least 4");
                break;
            case 4:
                tmp = new vertex_data<4>;
                break;
            case 5:
                tmp = new vertex_data<5>;
                break;
            case 6:
                tmp = new vertex_data<6>;
                break;
            case 7:
                tmp = new vertex_data<7>;
                break;
            case 8:
                tmp = new vertex_data<8>;
                break;
            case 9:
                tmp = new vertex_data<9>;
                break;
            case 10:
                tmp = new vertex_data<10>;
                break;
            default:
                throw NotYetImplementedException("RotopeFactory::generate(): "
                         "Rotopes of dimensions higher than 10 currently not "
                         "supported");
        }

        for (unsigned i = 0; i < actions.length(); ++i) {
            tmp = performAction(actions[i], i, tmp);
        }

        return tmp;
    }

    private:
        template <unsigned D> vertex_data<D> *performAction(char action,
                unsigned d, vertex_data<D> *rotope) {
            switch(action) {
                case 'E': case 'e':
                    std::cerr << "extrude\n";
                    return new Extrude<D, d, d+1>(*rotope);
                    break;
                case 'T': case 't':
                    std::cerr << "taper\n";
                    break;
                case 'R': case 'r':
                    throw NotYetImplementedException("RotopeFactory::performAction()"
                            ": Rotation operation");
                case 'D': case 'd':
                    throw NotYetImplementedException("RotopeFactory::performAction()"
                            ": Displaced rotation operation");
                default:
                    throw std::logic_error(string("RotopeFactory::performAction(): "
                            "Unsupported action \"")+action+string("\""));
            }
        }
};
