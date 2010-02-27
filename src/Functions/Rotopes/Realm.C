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
#include <sstream>

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
        throw std::invalid_argument(
                "Tried to push_back() "+r.toString()+" to Realm "+toString()+".\n"
                "You can only add realms of dimension this->_dimension-1.");
    _subrealm.push_back(r);
}


void Realm::merge(const Realm &r) {
    if (r._dimension != _dimension)
        throw std::invalid_argument(
                "Tried to merge "+r.toString()+" into Realm "+toString()+".\n"
                "You can only merge realms of equal dimension.");

    for (vector<Realm>::const_iterator i = r.cbegin(); i != r.cend(); ++i)
        _subrealm.push_back(*i);
}

std::string Realm::toString() const {
    std::ostringstream realm_outstream;

    RealmPrinter printer(this);
    printer.print(realm_outstream);
    realm_outstream << std::ends;

    return realm_outstream.str();

}

void Realm::add(unsigned delta) {
    if (_dimension == 0) {
        _index += delta;
    } else {
        for (vector<Realm>::iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            i->add(delta);
        }
    }
}

Realm::operator unsigned() const { 
    if (dimension() == 0) return _index; 
    throw std::invalid_argument(
            "Tried to convert Realm "+toString()+" to unsigned.\n"
            "Only a 0-dimensional Realm can be converted to an unsigned index.");
}


bool Realm::operator==(const Realm &other) const {

    if (dimension() != other.dimension()) return false;

    if (dimension() == 0) return ((unsigned)*this == (unsigned)other);

    if (_subrealm.size() != other._subrealm.size()) return false;

    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        if (!(_subrealm[i] == other._subrealm[i])) {
            return false;
        }
    }

    return true;
}

    
bool Realm::contains(const Realm &other) const {

    if (std::find(_subrealm.begin(), _subrealm.end(), other) != _subrealm.end()) {
        return true;
    }

    if (other.dimension() < dimension()) {
        for (vector<Realm>::const_iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            if (i->contains(other)) {
                return true;
            }
        }
    }

    return false;
}

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
Realm Realm::extrude(unsigned delta) {
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
            "Tried to taper a point: "+toString()+".\n"
            "Realm::taper() can only operate on at least two vertices."
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

Realm Realm::rotate(unsigned num_segments, unsigned size) {

    if (DEBUG_ROTATE) { cerr << "Realm::rotate(" << num_segments << ", " << size << ")--------------------------\n"; }
    switch (_dimension) {
    case 0: throw std::logic_error(
            "Tried to rotate a point: "+toString()+".\n"
            "Realm::rotate() can only operate on at least two vertices."
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
            if (DEBUG_ROTATE) { cerr << *j; }
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

    /** the difference between base1 and base2 is usually 2, unless
      * there are overflows, because of the way the polygon is generated from the two endpoints of a line in the
      * first place. */
    static const unsigned MAGIC_OFFSET_ADDED_TO_INDICES = 2;

    if (DEBUG_ROTATE) { cerr << "rotating surface: " << toString() << endl; }

    /** Create the sides (parallel to the rotation axis).
     */
    Realm temp_subrealms;
    temp_subrealms.setDimension(3);
    for (unsigned j = 0; j < num_segments; ++j) {
        Realm temp_realm = rotateStep(0, j*size, size);
        if (DEBUG_ROTATE) { cerr << "temp realm: " << endl << temp_realm.toString(); }
        temp_subrealms.merge(temp_realm);

        /** We're adding a square for the opposite side too.
         *  \todo Express the above sentence better.
         *  \todo Implement the consequences from the following train of thought.
         *
         * Nietzsche said (I paraphrase), "Philosophers are often poor writers because they not only tell us what they
         * think, but also how they developed their thoughts." If I were a good writer, my code would express the
         * solution for the numbering and ordering of indices in a "rotated" Realm clearly. Because I am not, I include
         * my musings as a reference to whom it may concern. 
         * 
         * Here is an observation for a full rotation step.
         * [0, 10, 12, 2] -> [2, 12, 14, 4]     adding 2 is ok.
         * [4, 14, 16, 6] -> [6, 16, 18, 8]     adding 2 is ok.
         * [8, 18, 11, 1] -> [1, 11, 13, 3]     adding 2 leads to overflow (>=20), subtracting 7 instead
         * [3, 13, 15, 5] -> [5, 15, 17, 7]     adding 2 is ok.
         * [7, 17, 19, 9] -> [9, 19, 10, 0]     adding 2 leads to overflow (>=20), subtracting *9* instead
         * problems occur with 8 and 9, these are the doubled vertices (0 == 8, 1 == 9).
         *
         * ok, inconclusive, try again with 6 instead of 4 segments.
                (0 14 16 2 )    (2 16 18 4 )    ok.
                (4 18 20 6 )    (6 20 22 8 )    ok.
                (8 22 24 10 )   (10 24 26 12 )  ok.
                (12 26 15 1 )   (14 28 17 3 )   overflow.
                (3 17 19 5 )    (5 19 21 7 )    ok.
                (7 21 23 9 )    (9 23 25 11 )   ok.
                (11 25 27 13 )  (13 27 29 15 )  overflow.
         * again, troubles with the doubles. :-) 12 == 0, 13 == 1. same with 26 and 27, and so on in 14 increments. the
         * increment is 10 in the first example. it is always 2*(num_segments+1). 
         *
         * these doubles are needed though, at least [1, 11, 13, 3] in the first case. [9, 19, 10, 0] is degenerate and
         * could be dropped.
         *
         * look again at [8, 18, 11, 1]. adding 2 gives [10, 20, 13, 3]. if i do %10+1 on the overflowing vertex 10, and
         * its partner accordingly, i get the desired result. with the second pair though, i'd have to do "+1, %10".
         *
         * of course, +1%10 would work in the first case too. all these AFTER adding 2.
         *
         * for the greater number of segments (case 2), let's see:
         *              +2              +1              %14
         * (12 26 15 1) -> (14 28 17 3) -> (15 29 17 3) -> (1 15 17 3)
         * this surface is not present and appears to be needed, it's triangular.
         *
         * (11 25 27 13) -> (13 27 29 15) -> (13 27 30 16) -> (13 27 16 2)
         * another triangular one, if i'm not mistaken.
         *
         *
         */
        Realm temp_copy = temp_realm;
        temp_copy.setAssociatedVertices(_associated_vertices);

        temp_copy.addKeepingInRange(MAGIC_OFFSET_ADDED_TO_INDICES, size, j);
        if (DEBUG_ROTATE) { cerr << "temp copy: " << temp_copy.toString() << endl; }
        temp_subrealms.merge(temp_copy);

    }

    if (DEBUG_ROTATE) { cout << "new realm: " << Realm(temp_subrealms).toString() << endl; }
    if (DEBUG_ROTATE) { cerr << "/Realm::rotate(" << num_segments << ", " << size << ")------------------------\n"; }

#   if false
    rotatePolygonCap(num_segments, size, temp_subrealms);
#   endif
    return temp_subrealms;
}

/** Adds an offset to indices in the realm, generating the rectangle that is
 *  generated by rotating the line that is opposite (in the original polygon) of
 *  the line that generated this realm.
 *
 *  in other words, transforms a rectangle on a sphere to the rectangle lying
 *  directly across the sphere.
 *
 *  \param delta offset to be added to every index in the Realm.
 *  \param total_vertices number of vertices per polygon, 2*(num_segments+1). aka \c size.
 *  \param rotation_step between 0 and num_segments-1.
 */
void Realm::addKeepingInRange(unsigned delta, unsigned num_segments, unsigned rotation_step) {
    if (_dimension < 2) {
        throw std::invalid_argument(
                "generating Realm must be a rectangle: "+toString());
    } else if (_dimension > 2) {
        for (vector<Realm>::iterator i = _subrealm.begin(); i != _subrealm.end(); ++i) {
            i->addKeepingInRange(delta, num_segments, rotation_step);
        }
        return;
    }
    if (_subrealm.size() != 4) {
        throw std::invalid_argument(
                "generating Realm must consist of exactly 4 vertices: "+toString());
    }
    
    add(delta);

    /** so how do we
     *   1. keep the "+1%num_segments" operation constrained to the two
     *      offending indices, but not the other two?
     *   2. ensure that the larger of the two indices does not get the
     *      operation "+1%N", but rather "-N, +1, %N, +N"? or in fact, this is even more complicated, because for
     *      every rotation step \c j, when we extrude vertices [j*N, ..., j*(N+1)-1] to [j*(N+1), ..., j*(N+2)-1],
     *      we need the indices to stay in the target range.
     * What is the target range? Well, every quad can be seen as a pair of pairs of indices:
     * [ (base1, extruded1), (extruded2, base2)]. the base points need to remain in the base range
     * [j*N, ..., j*(N+1)-1], while the extruded points lie in [j*(N+1), ..., j*(N+2)-1].
     */
    unsigned base1 = _subrealm[0], extruded1 = _subrealm[1],
             base2 = _subrealm[3], extruded2 = _subrealm[2],
             total_vertices = 1? num_segments: 2*(num_segments+1),
             min_base_index = rotation_step*total_vertices,
             max_base_index = (rotation_step+1)*total_vertices-1,
             min_extruded_index = max_base_index+1,
             max_extruded_index = (rotation_step+2)*total_vertices-1;

    if (DEBUG_ROTATE) {
        cerr << toString()
            << " delta: " << std::setw(4) << delta << " total_vertices: "<< std::setw(4) << total_vertices << " rotation_step "<< std::setw(4) << rotation_step << endl
            << " base1: "<< std::setw(4) << base1<< " base2: "<< std::setw(4) << base2
            << " extruded1: "<< std::setw(4) << extruded1 << " extruded2: "<< std::setw(4) << extruded2 << endl
            << " minb: "<< std::setw(4) << min_base_index << " maxb: "<< std::setw(4) << max_base_index
            << " mine "<< std::setw(4) << min_extruded_index << " maxe: "<< std::setw(4) << max_extruded_index
            << endl;
    }

    if (base1 > max_base_index) {
        if (extruded1 <= max_extruded_index) {
            throw std::logic_error("if the base index is out of bounds, the extruded must be too! "+toString());
        }

        //  add and modulo here
        base1++;
        extruded1++;
        while (base1 > max_base_index || extruded1 > max_extruded_index) {
            base1 -= total_vertices;
            extruded1 -= total_vertices;
        }
        if (base1 < min_base_index || extruded1 < min_extruded_index) {
            throw new std::logic_error("dropped below boundary");
        }
        
    } else if (base2 > max_base_index) {
        if (extruded2 <= max_extruded_index) {
            throw std::logic_error("if the base index is out of bounds, the extruded must be too! "+toString());
        }
        //  add and modulo here
        base2++;
        extruded2++;
        while (base2 > max_base_index || extruded2 > max_extruded_index) {
            base2 -= total_vertices;
            extruded2 -= total_vertices;
        }
        if (base2 < min_base_index || extruded2 < min_extruded_index) {
            throw new std::logic_error("dropped below boundary");
        }
    }

    _subrealm[0] = base1;
    _subrealm[1] = extruded1;
    _subrealm[2] = extruded2;
    _subrealm[3] = base2;

}


unsigned Realm::maxIndex() {
    if (_dimension == 0) return (unsigned)*this;

    unsigned max_index = 0;
    for (vector<Realm>::iterator i = _subrealm.begin();
         i != _subrealm.end(); ++i) {
        if (i->maxIndex() > max_index) max_index = i->maxIndex();
    }
    return max_index;
}

void Realm::keepIndicesBelow(unsigned max_index) {
    if (_dimension == 0) {
        if (_index >= max_index) _index = max_index-1;
    } else {
        for (vector<Realm>::iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            i->keepIndicesBelow(max_index);
        }
    }
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
    if (DEBUG_ROTATE) { cout << "new realm: " << endl << new_realm.toString() << endl; }
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
    // generate rectangles for the odd indices
    for (unsigned i = _subrealm.size()/2; i < _subrealm.size(); ++i) {
        new_subrealms.push_back(generateRectSegment(i, base, delta));
    }

    Realm new_realm;
    for (unsigned index = 0; index < new_subrealms.size(); index += 2) {
        Realm another_temp;

        for (vector<Realm>::iterator i = new_subrealms[index].begin(); i != new_subrealms[index].end(); ++i)
            another_temp.push_back(*i);

        for (vector<Realm>::reverse_iterator i = new_subrealms[index+1].rbegin(); i != new_subrealms[index+1].rend(); ++i)
            another_temp.push_back(*i);

        another_temp._dimension++;

        new_realm.push_back(another_temp);
    }

    if (DEBUG_ROTATE) { cerr << "new realm: " << new_realm.toString() << endl; }

    return new_realm;
}

Realm Realm::generateRectSegment(unsigned i, unsigned base, unsigned delta) {
    if (DEBUG_ROTATE) { cerr << "rotating " << _subrealm[i] << ": "; }
    if (_subrealm[i].dimension()) throw new std::logic_error("At this point subrealms should be points");
    Realm new_subrealm;

    new_subrealm.push_back(_subrealm[i]+base);
    new_subrealm.push_back(_subrealm[i]+delta+base);

    if (DEBUG_ROTATE) { cerr << new_subrealm.toString() << endl; }

    return new_subrealm;
}
