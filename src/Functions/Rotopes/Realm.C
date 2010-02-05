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
#include "Realm.h"

#include "Rotope.h"

#include <exception>
#include <list>

using std::cout;
using std::endl;
using std::vector;
using std::list;

void Realm::push_back(const Realm &r) {
    if (!_dimension) _dimension = r._dimension+1;
    if (r._dimension != _dimension-1)
        throw std::logic_error("you can only add realms of dimension this->_dimension-1");
    _subrealm.push_back(r); 
}

void Realm::print() const {
    const std::string spacer = "    ";
    static unsigned max_dimension = _dimension;
    if (_dimension > max_dimension) max_dimension = _dimension;

    if (_dimension) {
        for (unsigned space = 0; space < max_dimension-_dimension; ++space) cout << spacer;
        cout << "[" << _dimension << "] ";
        cout << "(";
    }
    if (_dimension == 0) cout << _index;
    else {
        if (_dimension > 2) cout << endl;// << spacer;
        for (vector<Realm>::const_iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            i->print();
            cout << " ";
        }
    }
    if (_dimension > 2) {
        for (unsigned space = 0; space < max_dimension-_dimension; ++space) cout << spacer;
    }
    if (_dimension) {
        cout << ")";
        cout << endl;
    }
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

Realm Realm::rotate(unsigned num_segments, unsigned size){
    switch (_dimension) {
        case 0: {
            throw std::logic_error(
                "Realm::rotate() can only operate on at least two vertices"
            );
        }
        /** To rotate a line we must do the following.
         *  
         *  Rotate both endpoints of the line N times, first the one, then the 
         *  other. Connect the last rotated image of the first endpoint to the
         *  original second point and the last rotated image of the second point
         *  to the first point. If we start with the line [0, 1] and rotate it 
         *  with \p num_segments = 3, we get [ 0, 2, 3, 1, 4, 5 ].
         *  
         */
        case 1: {
            /// Copy the subrealms to a list for easier insertion
            list<Realm> temp_list;
//          copy(_subrealm.begin(), _subrealm.end(), temp_list.begin());  // this segfaults! why?
            for (vector<Realm>::iterator i = _subrealm.begin(); i != _subrealm.end(); ++i) 
                temp_list.push_back(*i);
            list<vector<Realm> > realms_to_add;

            unsigned index = 0;
            for (list<Realm>::iterator i = temp_list.begin(); i != temp_list.end(); ++i, ++index) {
                i->print(); cout << endl;
                vector<Realm> to_add;
                for (unsigned j = 0; j < num_segments; ++j) {
                    to_add.push_back(rotate_step(index, j*size, size));
                }
                realms_to_add.push_back(to_add);
            }
            list<Realm>::iterator i = temp_list.begin();
            ++i;
            list<vector<Realm> >::iterator inew = realms_to_add.begin();
            if (false) for ( ; inew != realms_to_add.end(); ++i, ++inew) {
                cout << "realms to add: ";
                for (vector<Realm>::iterator j = inew->begin(); j != inew->end(); ++j) {
                    j->print();
                }
                cout << endl;
                temp_list.insert(i, inew->begin(), inew->end());
            }

            /// Copy the subrealms back from the temporary list to a vector
            _subrealm.clear();
//          copy(temp_list.begin(), temp_list.end(), _subrealm.begin());
            for (list<Realm>::iterator i = temp_list.begin(); i != temp_list.end(); ++i) _subrealm.push_back(*i);

            _dimension++;
            print();  cout << endl;

            return *this;
        }
        /** For a two-dimensional surface we have to do the following.
         * 
         *  First, because the surface is not stored as a list of lines, but 
         *  rather as a list of points (because drawing the surface from lines
         *  would be too tedious in OpenGL) we have to split the surface corner
         *  points into line segments. Say we have a square defined as [0, 1, 3, 2]
         *  we must first split it into its edges: [0, 1], [1, 3], [3, 2], [2, 1].
         * 
         *  Say we have \p num_segments = 3. What we want in the end is for the 
         *  sides of the prism: 
         *  [0, 1, 5, 4], [4, 5, 7, 6], [6, 7, 3, 2], [2, 3, 9, 8], [8, 9, 11, 10],
         *  [10, 11, 1, 0]
         *  and for the caps: 
         *  [0, 4, 6, 2, 8, 10], [1, 5, 7, 3, 9, 11]
         *
         */
        case 2: {
            unsigned index = 0;
            cout << "subrealm: "; print(); cout << "num_segments: " << num_segments << endl;
            vector<Realm> temp_subrealms;
            for (unsigned j = 0; j < num_segments; ++j) {
                rotate_step(index, j*size, size).print(); cout << endl;
                temp_subrealms.push_back(rotate_step(index, j*size, size));
            }
            vector<Realm> edges;
            /** make the first edge the first line in the temporary list of
             *  subrealms (assuming we have a square). to do that remove the 
             *  last two vertices from the square.
             *  \todo achieve the desired effect for any polygon
             */
            Realm first_edge(*this);
            first_edge._subrealm.pop_back();
            first_edge._subrealm.pop_back();
            edges.push_back(first_edge);

            /// then add the following edges by using only the first point of the edge
            for (unsigned i = 0; i < temp_subrealms.size(); ++i) {
                edges.push_back(temp_subrealms[i]._subrealm[0]);
            }

            /** at this point the array of subrealms has the form:
             *  [0, 1], [4, 5], [8, 9], ...
             *  \todo we need to step through the vector members and assemble surfaces
             *  of the form [0, 1, 5, 4], [4, 5, 9, 8], ...
             */
            vector<Realm> surfaces;
            for (unsigned i = 0; i < edges.size(); ++i) {
                Realm new_surface;
                for (vector<Realm>::iterator j = edges[i].begin(); 
                     j != edges[i].end(); ++j) {
                    new_surface.push_back(*j);
                }
                for (vector<Realm>::reverse_iterator j = edges[(i+1)%edges.size()].rbegin(); 
                     j != edges[(i+1)%edges.size()].rend(); ++j) {
                    new_surface.push_back(*j);
                }
                surfaces.push_back(new_surface);
            }
            Realm new_realm(surfaces);
            cout << "new realm: "; new_realm.print(); cout << endl;
            
            return new_realm;
        }
        default: {
            vector<Realm> temp_subrealms;
            for (unsigned i = 0; i < _subrealm.size(); ++i) {
                temp_subrealms.push_back(_subrealm[i].rotate(num_segments, size));
            }
            temp_subrealms.push_back(*this);
            Realm new_realm(temp_subrealms);
            cout << "new realm: "; new_realm.print(); cout << endl;
            return new_realm;
        }
    }
}

Realm Realm::rotate_step(unsigned index, unsigned base, unsigned delta) {
    cout << "Realm::rotate_step(" << index << ", " << base << ", " << delta << "): ";
    switch (_dimension) {
        case 0: {
            throw std::logic_error(
                "Realm::rotate_step() can only operate on at least two vertices"
            );
        }
        case 1: {
            return Realm(_subrealm[index]._index+base+delta);
        }
        case 2: {
            vector<Realm> new_subrealms;
            for (unsigned i = 0; i < _subrealm.size(); ++i) {
                Realm new_subrealm;
                new_subrealm.push_back(_subrealm[i]);
                new_subrealm.push_back(_subrealm[(i+1)%_subrealm.size()]);
                new_subrealm.add(delta+base);
                new_subrealm.print();cout << endl;
                new_subrealms.push_back(new_subrealm);
            }
            return new_subrealms;
        }
        default: {
            throw NotYetImplementedException("Realm::rotate_step()");
        }
    }
}
