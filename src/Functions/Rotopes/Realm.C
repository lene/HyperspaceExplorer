///
/// C++ Implementation: Realm
///
/// Description:
///
///
/// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2009
///
/// Copyright: See COPYING file that comes with this distribution
///
///
#include "Realm.H"

#include "Rotope.H"

using std::cout;
using std::endl;
using std::vector;

void Realm::print() const {
    if (_dimension) cout << "[" << _dimension << "] ";
    cout << "(";
    if (_dimension == 0) cout << _index;
    else {
        for (vector<Realm>::const_iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            i->print();
            cout << " ";
        }
    }
    cout << ")";
}

void Realm::add(unsigned delta) {
    if (_dimension == 0) _index += delta;
    else {
        for (vector<Realm>::iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            i->add(delta);
        }
    }
}

Realm Realm::extrude(unsigned delta) {
    vector<Realm> new_subrealms;
    
    /** There is an annoying problem with the circumstance that I'd like to
     *  store realms as [sets of] point sets of their dimension, and that OpenGL
     *  needs point sets to draw two dimensional surfaces (as opposed to sets of
     *  lines). I cannot, therefore, store a two dimensional Realm as a set of
     *  one dimensional Realm s in any efficient way. I need to treat two
     *  dimensional Realm s differently.
     * 
     *  That leads to special cases for each of the following operations:
     *  - Going from zero to one dimensions: Make a line from the point and its
     *    extruded image.
     *  - Going from one to two dimensions: make a surface from the two end
     *    points of the line and their extruded images, storing the Realm not
     *    as a set of lines, but as a set of points and manually setting its
     *    dimension to two.
     *  - Going from two to three dimensions: The top and bottom caps can be 
     *    copies of the current object, as in the default algorithm below, but
     *    the sides must be treated as lines, and thus repeat the algorithm 
     *    described above.
     *  - Default: Top and bottom caps are (shifted) copies of the current 
     *    Realm, while for the side connections the extrusion algorithm is
     *    called recursively.
     */
    switch(_dimension) {
        
        //  Extrude a point to a line
        case 0: {
            new_subrealms.push_back(_index);
            new_subrealms.push_back(_index+delta);
            Realm new_realm(new_subrealms);
            return new_realm;
        }
        //  Extrude a line to a square
        case 1: {
            // special case: make surfaces so OpenGL can draw them
            // _subrealm.size() should be 2
            new_subrealms.push_back(_subrealm[0]._index);
            new_subrealms.push_back(_subrealm[1]._index);
            new_subrealms.push_back(_subrealm[1]._index+delta);
            new_subrealms.push_back(_subrealm[0]._index+delta);
            Realm new_realm(new_subrealms);
            new_realm._dimension++;
            
            return new_realm;
        }
        //  Extrude a polygon to a prism
        case 2: {
            Realm copy(*this);
            new_subrealms.push_back(copy);
            for (unsigned i = 0; i < _subrealm.size(); ++i) {
                Realm new_subrealm;
                new_subrealm.push_back(_subrealm[i]._index);
                new_subrealm.push_back(_subrealm[(i+1)%_subrealm.size()]._index);
                new_subrealm.push_back(_subrealm[(i+1)%_subrealm.size()]._index+delta);
                new_subrealm.push_back(_subrealm[i]._index+delta);
                new_subrealm._dimension = 2;
                new_subrealms.push_back(new_subrealm);
            }
            copy.add(delta);
            new_subrealms.push_back(copy);
            Realm new_realm(new_subrealms);
            return new_realm;
        }
        //  Extrude an N-dimensional Realm to a N+1-dimensional one, where N > 2
        default: {
            Realm copy(*this);
            new_subrealms.push_back(copy);
            for (unsigned i = 0; i < _subrealm.size(); ++i) {
                new_subrealms.push_back(_subrealm[i].extrude(delta));
            }
            copy.add(delta);
            new_subrealms.push_back(copy);
            Realm new_realm(new_subrealms);
            return new_realm;
        }
    }
}

Realm Realm::taper(unsigned taper_index) {
    vector<Realm> new_subrealms;

    switch (_dimension) {
        case 0: {
            throw std::logic_error(
                "Realm::taper() can only operate on at least two vertices"
            );
        }
        //  taper a line to a triangle
        case 1: {
            _subrealm.push_back(Realm(taper_index));
            _dimension++;
            return *this;
        }
        //  taper a polygon to a pyramid
        case 2: {
            new_subrealms.push_back(*this);
            for (unsigned i = 0; i < _subrealm.size(); ++i) {
                Realm new_subrealm;
                new_subrealm.push_back(_subrealm[i]._index);
                new_subrealm.push_back(_subrealm[(i+1)%_subrealm.size()]._index);
                new_subrealm.push_back(taper_index);
                new_subrealm._dimension = 2;
                new_subrealms.push_back(new_subrealm);
            }
            Realm new_realm(new_subrealms);
            return new_realm;
        }
        //  taper an N-dimensional Realm to a N+1-dimensional one, where N > 2
        default: {
            new_subrealms.push_back(*this);
            for (unsigned i = 0; i < _subrealm.size(); ++i) {
                new_subrealms.push_back(_subrealm[i].taper(taper_index));
            }
            Realm new_realm(new_subrealms);
            return new_realm;
        }
    }
}

Realm Realm::rotate(double step){
    switch (_dimension) {
        case 0: {
            throw std::logic_error(
                "Realm::rotate() can only operate on at least two vertices"
            );
        }
        default: {
            throw NotYetImplementedException("Realm::rotate()");
        }
    }
}

Realm Realm::rotate_step(unsigned index, unsigned base, unsigned delta) {
    cout << "Realm::rotate_step(" << base << ", " << delta << ")\n";
    print(); cout << endl;
    switch (_dimension) {
        case 0: {
            throw std::logic_error(
                "Realm::rotate_step() can only operate on at least two vertices"
            );
        }
        case 1: {
            vector<Realm> new_subrealms;
            vector<Realm> temp_subrealms;
            temp_subrealms.push_back(_subrealm[index]._index+base);
            temp_subrealms.push_back(_subrealm[index]._index+base+delta);
            Realm new_realm(temp_subrealms);
            new_subrealms.push_back(new_realm);
            return Realm(new_subrealms);
        }
        default: {
            throw NotYetImplementedException("Realm::rotate_step()");
        }
    }
}
