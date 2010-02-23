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
#include <stdexcept>
#include <list>

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::list;

void Realm::clear() {
    _subrealm.clear();
    _dimension = 0;
    _index = 0;
}

void Realm::push_back(const Realm &r) {
    if (!_dimension) _dimension = r._dimension+1;
    if (r._dimension != _dimension-1)
        throw std::invalid_argument("you can only add realms of dimension this->_dimension-1");
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

Realm::operator unsigned() const { 
    if (dimension() == 0) return _index; 
    throw std::invalid_argument("Only a 0-dimensional Realm can be converted to an unsigned index.");
}
    
bool Realm::contains(const Realm &other) {
    if (std::find(_subrealm.begin(), _subrealm.end(), other) != _subrealm.end()) return true;
     
    if (other.dimension() < dimension()-1) {
        for (vector<Realm>::iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            if (i->contains(other)) return true;
        }
    }
    
    return false;
}

Realm Realm::extrude(unsigned delta) {
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
    case 0: return extrudePoint(delta);
    case 1: return extrudeLine(delta);
    case 2: return extrudePolygon(delta);
    default: return extrudeRealm(delta);
    }
}

Realm Realm::extrudePoint(unsigned delta) {
    vector<Realm> new_subrealms;
    new_subrealms.push_back(_index);
    new_subrealms.push_back(_index+delta);
    Realm new_realm(new_subrealms);
    return new_realm;
}

Realm Realm::extrudeLine(unsigned delta) {
    vector<Realm> new_subrealms;
    new_subrealms.push_back(_subrealm[0]._index);
    new_subrealms.push_back(_subrealm[1]._index);
    new_subrealms.push_back(_subrealm[1]._index+delta);
    new_subrealms.push_back(_subrealm[0]._index+delta);
    Realm new_realm(new_subrealms);
    new_realm._dimension++;

    return new_realm;
}

Realm Realm::extrudePolygon(unsigned delta) {
    vector<Realm> new_subrealms;

    Realm copied_realm(*this);
    new_subrealms.push_back(copied_realm);
    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        Realm new_subrealm;
        new_subrealm.push_back(_subrealm[i]._index);
        new_subrealm.push_back(_subrealm[(i+1)%_subrealm.size()]._index);
        new_subrealm.push_back(_subrealm[(i+1)%_subrealm.size()]._index+delta);
        new_subrealm.push_back(_subrealm[i]._index+delta);
        new_subrealm._dimension = 2;
        new_subrealms.push_back(new_subrealm);
    }
    copied_realm.add(delta);
    new_subrealms.push_back(copied_realm);
    Realm new_realm(new_subrealms);
    return new_realm;
}

Realm Realm::extrudeRealm(unsigned delta) {
    vector<Realm> new_subrealms;
    Realm copied_realm(*this);
    new_subrealms.push_back(copied_realm);
    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        new_subrealms.push_back(_subrealm[i].extrude(delta));
    }
    copied_realm.add(delta);
    new_subrealms.push_back(copied_realm);
    Realm new_realm(new_subrealms);
    return new_realm;
}

Realm Realm::taper(unsigned taper_index) {
    switch (_dimension) {
    case 0: throw std::logic_error(
            "Realm::taper() can only operate on at least two vertices"
    );
    case 1: return taperLine(taper_index);    
    case 2: return taperPolygon(taper_index);
    default: return taperRealm(taper_index);
    }
}

Realm Realm::taperLine(unsigned taper_index) {
    _subrealm.push_back(Realm(taper_index));
    _dimension++;
    return *this;
}

Realm Realm::taperPolygon(unsigned taper_index) {
    vector<Realm> new_subrealms;
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

Realm Realm::taperRealm(unsigned taper_index) {
    vector<Realm> new_subrealms;
    new_subrealms.push_back(*this);
    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        new_subrealms.push_back(_subrealm[i].taper(taper_index));
    }
    Realm new_realm(new_subrealms);
    return new_realm;
}

const bool Realm::DEBUG_ROTATE = true;

Realm Realm::rotate(unsigned num_segments, unsigned size) {

    if (DEBUG_ROTATE) { cerr << "Realm::rotate(" << num_segments << ", " << size << ")--------------------------\n"; }
    switch (_dimension) {
    case 0: throw std::logic_error(
            "Realm::rotate() can only operate on at least two vertices"
    );
    case 1: return rotateLine(num_segments, size);
    case 2: return rotatePolygon(num_segments, size);
    default: return rotateRealm(num_segments, size);
    }
}

/** To rotate a line we must do the following.
 *
 *  Rotate both endpoints of the line N times, first the one, then the
 *  other. Connect the last rotated image of the first endpoint to the
 *  original second point and the last rotated image of the second point
 *  to the first point. If we start with the line [0, 1] and rotate it
 *  with \p num_segments = 3, we get [ 0, 2, 3, 1, 4, 5 ].
 */
Realm Realm::rotateLine(unsigned num_segments, unsigned size) {
    //  this case seems to be working properly.

    /// Copy the subrealms to a list for easier insertion
    list<Realm> temp_list(_subrealm.size());
    std::copy(_subrealm.begin(), _subrealm.end(), temp_list.begin());

    list< vector<Realm> > realms_to_add;

    unsigned index = 0;
    for (list<Realm>::iterator i = temp_list.begin(); i != temp_list.end(); ++i, ++index) {
        vector<Realm> to_add;
        for (unsigned j = 0; j < num_segments; ++j) {
            to_add.push_back(rotateStep(index, j*size, size));
        }
        realms_to_add.push_back(to_add);
    }
    list<Realm>::iterator i = temp_list.begin();
    ++i;
    list< vector<Realm> >::iterator inew = realms_to_add.begin();
    for ( ; inew != realms_to_add.end(); ++i, ++inew) {
        for (vector<Realm>::iterator j = inew->begin(); j != inew->end(); ++j) {
            if (DEBUG_ROTATE) { j->print(); }
        }
        temp_list.insert(i, inew->begin(), inew->end());
    }

    /// Copy the subrealms back from the temporary list to a vector
    _subrealm.resize(temp_list.size());
    std::copy(temp_list.begin(), temp_list.end(), _subrealm.begin());

    _dimension++;

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
 *  \todo Revise this documentation.
 *  \todo Add the caps.
 *  \todo make this work for arbitrary polygons.
 */
Realm Realm::rotatePolygon(unsigned num_segments, unsigned size) {
    if (DEBUG_ROTATE) { cerr << "rotating surface: "; print(); cout << endl; }

    /** Create the sides (parallel to the rotation axis).
     */
    vector<Realm> temp_subrealms;
    for (unsigned j = 0; j < num_segments; ++j) {
        Realm temp_realm = rotateStep(0, j*size, size);
        if (DEBUG_ROTATE) { cerr << "temp realm: "; temp_realm.print(); }
        temp_subrealms.push_back(temp_realm);

        /** We're adding a square for the opposite side too.
         *  \todo Express the above sentence better.
         *  \todo is simply adding 2 correct? how to calculate the correct offset?
         */
        Realm temp_copy = temp_realm;
        temp_copy.add(2);
        if (DEBUG_ROTATE) { cerr << "temp copy: "; temp_copy.print(); }
        temp_subrealms.push_back(temp_copy);

    }

    if (DEBUG_ROTATE) { cout << "new realm: "; Realm(temp_subrealms).print(); cout << endl; }
    if (DEBUG_ROTATE) { cerr << "/Realm::rotate(" << num_segments << ", " << size << ")------------------------\n"; }

#   if false
    rotatePolygonCap(num_segments, size, temp_subrealms);
#   endif
    return temp_subrealms;
}

Realm Realm::rotatePolygonCap(unsigned num_segments, unsigned size, vector<Realm> &temp_subrealms) {
    vector<Realm> edges;
    /** Create the cap (perpendicular to the rotation axis).
     *
     *  Make the first edge the first line in the temporary list of
     *  subrealms (assuming we have a square). To do that remove the
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

//    temp_subrealms.push_back(edges);

}

Realm Realm::rotateRealm(unsigned num_segments, unsigned size) {
    vector<Realm> temp_subrealms;
    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        temp_subrealms.push_back(_subrealm[i].rotate(num_segments, size));
    }
    temp_subrealms.push_back(*this);
    Realm new_realm(temp_subrealms);
    if (DEBUG_ROTATE) { cout << "new realm: "; new_realm.print(); cout << endl; }
    return new_realm;
}

Realm Realm::rotateStep(unsigned index, unsigned base, unsigned delta) {
    if (DEBUG_ROTATE) { cout << "Realm::rotate_step(" << index << ", " << base << ", " << delta << "): "; }
    switch (_dimension) {
    case 0: throw std::logic_error(
            "Realm::rotate_step() can only operate on at least two vertices"
    );

    case 1: return Realm(_subrealm[index]._index+base+delta);
    case 2: return rotateStep2D(index, base, delta);

    default: throw NotYetImplementedException("Realm::rotate_step()");
    }
}

Realm Realm::rotateStep2D(unsigned index, unsigned base, unsigned delta) {
    vector<Realm> new_subrealms;
    if (DEBUG_ROTATE) { cerr << endl << "size: " << _subrealm.size() << endl; }
    /// split procedure: once for points on the positive and once for negative points
    /** what happens and actually seems to be necessary here is this.
     *  when i comment out the second loop in the case of a cylinder only
     *  half is drawn. in the case of a sphere only a quarter sphere is drawn
     *  regardless of whether the second loop runs or not.\n
     *  i suspect that there should be _subrealm.size()/2 loops of length 2.
     *  in the cylinder case, this happens to be the same as what we have here,
     *  because _subrealm.size() == 4.
     */
    for (unsigned i = 0; i < _subrealm.size()/2; ++i) {
        new_subrealms.push_back(generateRectSegment(i, base, delta));
    }
    for (unsigned i = _subrealm.size()/2; i < _subrealm.size(); ++i) {
        new_subrealms.push_back(generateRectSegment(i, base, delta));
    }

    vector<Realm> another_temp;
    for (vector<Realm>::iterator i = new_subrealms[0].begin(); i != new_subrealms[0].end(); ++i)
        another_temp.push_back(*i);
    for (vector<Realm>::reverse_iterator i = new_subrealms[1].rbegin(); i != new_subrealms[1].rend(); ++i)
        another_temp.push_back(*i);

    Realm new_realm(another_temp);
    new_realm._dimension++;
    if (DEBUG_ROTATE) { new_realm.print(); }
    //new_realm.convertToSurface();

    //            return *this;
    return new_realm;
}

Realm Realm::generateRectSegment(unsigned i, unsigned base, unsigned delta) {
    if (DEBUG_ROTATE) { cerr << "rotating "; _subrealm[i].print(); }
    if (_subrealm[i].dimension()) throw new std::logic_error("At this point subrealms should be points");
    Realm new_subrealm;

    new_subrealm.push_back(_subrealm[i]+base);
    new_subrealm.push_back(_subrealm[i]+delta+base);

    if (DEBUG_ROTATE) { new_subrealm.print(); }

    return new_subrealm;
}

void Realm::convertToSurface() {
    if (_dimension != 2) throw std::logic_error("convertToSurface() can only be called on a 2D Realm");
    vector<Realm> temp_vertices;

    for (vector<Realm>::iterator j = _subrealm.begin();
            j != _subrealm.end(); ++j) {
        if (j->dimension() != 1) throw std::logic_error("All subrealms must have dimension 1");
        temp_vertices.push_back(*(j->begin()));
    }

    setSubrealms(temp_vertices);
}
