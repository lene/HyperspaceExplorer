///
/// C++ Implementation: Realm
///
/// Description:
///
///
/// Author: Lene Preuss <lene.preuss@gmail.com>, (C) 2009
///
/// Copyright: See COPYING file that comes with this distribution
///
///
#include "Realm.h"

#include "Rotope.h"

#include <stdexcept>
#include <list>
#include <ios>

using std::cout;
using std::cerr;
using std::endl;
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

    for (realm_container_type::const_iterator i = r.cbegin(); i != r.cend(); ++i)
        _subrealm.push_back(*i);
}

std::string Realm::toString() const {
    std::ostringstream realm_outstream;

    RealmPrinter(this).print(realm_outstream);
    realm_outstream << std::ends;

    return realm_outstream.str();
}

void Realm::addOffset(unsigned delta) {
    if (_dimension == 0) {
        _index += delta;
    } else {
        for (realm_container_type::iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            i->addOffset(delta);
        }
    }
}

unsigned Realm::toIndex() const { 
    if (dimension() == 0) return _index; 
    throw std::invalid_argument(
            "Tried to convert Realm "+toString()+" to unsigned.\n"
            "Only a 0-dimensional Realm can be converted to an unsigned index.");
}

/** \todo rewrite to make independent of realm_container_type::operator[] */
bool Realm::operator==(const Realm &other) const {

    if (dimension() != other.dimension()) return false;

    if (dimension() == 0) return (toIndex() == other.toIndex());

    if (_subrealm.size() != other._subrealm.size()) return false;

    /* comparing _subrealm to other._subrealm does not always return true, even
     * if the elements are equal. doing it manually. */
    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        if (!(_subrealm[i] == other._subrealm[i])) return false;
    }

    return true;
}
    
bool Realm::contains(const Realm &other) const {

    if (std::find(_subrealm.begin(), _subrealm.end(), other) != _subrealm.end()) {
        return true;
    }

    if (other.dimension() < dimension()) {
        for (realm_container_type::const_iterator i = _subrealm.begin();
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
 *    extruded image. Handled by extrudePoint().
 *  - Going from one to two dimensions: make a surface from the two end
 *    points of the line and their extruded images, storing the Realm not
 *    as a set of lines, but as a set of points and manually setting its
 *    dimension to two. Handled by extrudeLine().
 *  - Going from two to three dimensions: The top and bottom caps can be
 *    copies of the current object, as in the default algorithm below, but
 *    the sides must be treated as lines, and thus repeat the algorithm
 *    described above. Handled by extrudePolygon.
 *  - Default: Top and bottom caps are (shifted) copies of the current
 *    Realm, while for the side connections the extrusion algorithm is
 *    called recursively. Handled by extrudeRealm().
 *
 *  \param delta How many elements there were in the original vertex array - IOW,
 *      how much there needs to be added to each index from the original Realm
 *      to be pointing to the corresponding vertex in the extruded vertex array.
 *      (Gee, that's a mouthful.)
 */
Realm Realm::extruded(unsigned delta) const {
    switch(_dimension) {
    case 0: return extrudedPoint(delta);
    case 1: return extrudedLine(delta);
    case 2: return extrudedPolygon(delta);
    default: return extrudedRealm(delta);
    }
}

Realm Realm::extrudedPoint(unsigned delta) const {
    if (_dimension) {
        throw std::logic_error("extrudePoint() called on Realm: "+toString());
    }
    
    realm_container_type new_subrealms;

    new_subrealms.push_back(_index);
    new_subrealms.push_back(_index+delta);

    Realm new_realm(new_subrealms);
    return new_realm;
}

/** Special case: make surfaces so OpenGL can draw them. \c _subrealm.size()
 *  should be 2.
 */
Realm Realm::extrudedLine(unsigned delta) const {
    if (_dimension != 1) {
        throw std::logic_error("extrudeLine() called on Realm: "+toString());
    }
    if (_subrealm.size() != 2) {
        throw std::logic_error(
                "extrudeLine() called on Realm whose size is not exactly 2: "+
                toString());
    }

    realm_container_type new_subrealms;

    new_subrealms.push_back(_subrealm[0]._index);
    new_subrealms.push_back(_subrealm[1]._index);
    new_subrealms.push_back(_subrealm[1]._index+delta);
    new_subrealms.push_back(_subrealm[0]._index+delta);

    Realm new_realm(new_subrealms);
    new_realm._dimension++;

    return new_realm;
}

Realm Realm::extrudedPolygon(unsigned delta) const {
    if (_dimension != 2) {
        throw std::logic_error("extrudePolygon() called on Realm: "+toString());
    }

    realm_container_type new_subrealms;

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

    copied_realm.addOffset(delta);
    new_subrealms.push_back(copied_realm);
    
    return Realm(new_subrealms);
}

Realm Realm::extrudedRealm(unsigned delta) const {
    if (_dimension < 3) {
        throw std::logic_error("extrudeRealm() called on Realm: "+toString());
    }

    realm_container_type new_subrealms;

    Realm copied_realm(*this);
    new_subrealms.push_back(copied_realm);

    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        new_subrealms.push_back(_subrealm[i].extruded(delta));
    }

    copied_realm.addOffset(delta);
    new_subrealms.push_back(copied_realm);

    return Realm(new_subrealms);
}

/** \param taper_index Index in the vertex array of the new vertex, toward which 
 *      the object is tapered.
 */
Realm Realm::tapered(unsigned taper_index) const {
    switch (_dimension) {
    case 0: throw std::logic_error(
            "Tried to taper a point: "+toString()+".\n"
            "Realm::taper() can only operate on at least two vertices."
    );
    case 1: return taperedLine(taper_index);    
    case 2: return taperedPolygon(taper_index);
    default: return taperedRealm(taper_index);
    }
}

Realm Realm::taperedLine(unsigned taper_index) const {
    if (_dimension != 1) {
        throw std::logic_error("taperLine() called on Realm: "+toString());
    }
    if (_subrealm.size() != 2) {
        throw std::logic_error(
                "taperLine() called on Realm whose size is not exactly 2: "+
                toString());
    }

    Realm triangle(*this);
    triangle.push_back(Realm(taper_index));
    triangle._dimension++;
    return triangle;
}

Realm Realm::taperedPolygon(unsigned taper_index) const {
    if (_dimension != 2) {
        throw std::logic_error("taperPolygon() called on Realm: "+toString());
    }

    realm_container_type new_subrealms;

    new_subrealms.push_back(*this);

    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        Realm new_subrealm;
        new_subrealm.push_back(_subrealm[i]._index);
        new_subrealm.push_back(_subrealm[(i+1)%_subrealm.size()]._index);
        new_subrealm.push_back(taper_index);
        new_subrealm._dimension = 2;
        new_subrealms.push_back(new_subrealm);
    }
    
    return Realm(new_subrealms);
}

Realm Realm::taperedRealm(unsigned taper_index) const {
    if (_dimension < 3) {
        throw std::logic_error("extrudeRealm() called on Realm: "+toString());
    }

    realm_container_type new_subrealms;

    new_subrealms.push_back(*this);

    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        new_subrealms.push_back(_subrealm[i].tapered(taper_index));
    }
    
    return Realm(new_subrealms);;
}

/** \todo more documentation
 *  \param num_segments How many segments to use approximating a circle.
 *  \param size Size of the original vertex array. See extrude().
 */
Realm Realm::rotated(unsigned num_segments, unsigned size) const {

    switch (_dimension) {
    case 0: throw std::logic_error(
            "Tried to rotate a point: "+toString()+".\n"
            "Realm::rotate() can only operate on at least two vertices."
    );
    case 1: return rotatedLine(num_segments, size);
    case 2: return rotatedPolygon(num_segments, size);
    default: return rotatedRealm(num_segments, size);
    }
}

/** To rotate a line we must do the following.
 *
 *  Rotate both endpoints of the line \p num_segments times, first the one, then
 *  the other. Connect the last rotated image of the first endpoint to the
 *  original second point and the last rotated image of the second point
 *  to the first point. If we start with the line <tt>[0, 1]</tt> and rotate it
 *  with \p num_segments = 3, we get <tt>[ 0, 2, 3, 1, 4, 5 ]</tt>.
 *
 *  \param num_segments How many segments to use approximating a circle.
 *  \param size Size of the original vertex array. See extrude().
 */
Realm Realm::rotatedLine(unsigned num_segments, unsigned size) const {

    /// Copy the subrealms to a list for easier insertion in the middle.
    list<Realm> temp_list(_subrealm.size());
    std::copy(_subrealm.begin(), _subrealm.end(), temp_list.begin());

    list< realm_container_type > realms_to_add = generateListOfPointsToAdd(temp_list, num_segments, size);
    insertNewPoints(temp_list, realms_to_add);

    /// Copy the subrealms back from the temporary list to a vector
    realm_container_type new_subrealms(temp_list.size());
    std::copy(temp_list.begin(), temp_list.end(), new_subrealms.begin());

    Realm circle(new_subrealms);
    circle._dimension++;
    return circle;
}

list<Realm::realm_container_type> Realm::generateListOfPointsToAdd(
        list<Realm> original_list, unsigned num_segments, unsigned size) const {
    list< realm_container_type > realms_to_add;

    unsigned index = 0;
    for (list<Realm>::iterator i = original_list.begin(); i != original_list.end(); ++i, ++index) {
        realm_container_type to_add;
        for (unsigned j = 0; j < num_segments; ++j) {
            to_add.push_back(rotateStep(index, j*size, size));
        }
        realms_to_add.push_back(to_add);
    }

    return realms_to_add;
}

void Realm::insertNewPoints(list<Realm> &original_list,
                            const list<Realm::realm_container_type> &new_points) const {

    list<Realm>::iterator i = original_list.begin();
    ++i;
    
    for (list< realm_container_type >::const_iterator inew = new_points.begin();
         inew != new_points.end(); ++i, ++inew) {
        original_list.insert(i, inew->begin(), inew->end());
    }
}

/** For a two-dimensional surface we have to do the following.
 *
 *  First, because the surface is not stored as a list of lines, but rather as a list of points
 *  (because drawing the surface from lines in OpenGL would be too tedious) we have to split the
 *  surface corner points into line segments. Say we have a square defined as <tt>[0, 1, 3, 2]</tt>
 *  we must first split it into its edges: <tt>[0, 1], [1, 3], [3, 2], [2, 1]</tt>.
 *
 *  Say we have \p num_segments = 3. What we want in the end is for the sides of the prism:
 *  <tt>[0, 1, 5, 4], [4, 5, 7, 6], [6, 7, 3, 2], [2, 3, 9, 8], [8, 9, 11, 10], [10, 11, 1, 0]</tt>
 *  and for the caps: <tt>[0, 4, 6, 2, 8, 10], [1, 5, 7, 3, 9, 11]</tt>.

 *  Nietzsche said (I paraphrase), "Philosophers are often poor writers because they not only tell 
 *  us what they think, but also how they developed their thoughts." If I were a good writer, my
 *  code would express the solution for the numbering and ordering of indices in a "rotated" Realm
 *  clearly. Because I am not, I include my musings as a reference to whom it may concern.
 *
 *  A polygon's indices are numbered like this:
 *  \code
 *       5 *       * 3
 *
 *
 *  0 * - original-line - * 1
 *
 *
 *       2 *        * 4
 *  \endcode
 *
 *  A rotation step leads to the following situation, unsatisfactorily depicted in ASCII art.
 *  \code
 *               5 *           * 3
 *
 *             11 *           * 9  <- rotated up
 *
 *  0,6,12 *                           * 1,7,13
 *
 *
 *
 *               2 *-----------* 4
 *                  \          \      <- one resulting face
 * rotated down-> 8 *-----------* 10
 *
 *  \endcode
 *  To generate a polygon strip that adds a surface to all these vertices, we connect each
 *  neighboring pair [original vertex, neighboring vertex] and their rotated images.
 *  Naively we would just add \p num_segments (6) to connect to the rotated vertex, then add the
 *  offset 2 to connect to the neighbour in the rotated polygon, then subtract 6 again
 *  to connect to the neighbor in the original polygon.
 *  In traversing the list of vertices we must use each vertex twice, because it is part of two
 *  line segments/resulting faces. The idea is to simply add 2 to each vertex in a face, that would
 *  lead to the next neighboring face. Let's see how that works out.
 *  \code
 *  [0,  6,  8, 2] -> [2,  8, 10, 4]     ok.
 *  [4, 10,  7, 1] -> [6, 12, 13, 3]     wrong face! 12 and 13 lie across the center.
 *  [3,  9, 11, 5] -> [5, 11, 13, 7]     wrong face again! 5 and 11 don't neighbor 13 and 7.
 *  \endcode
 *  Clearly, if an "overflow" occurs, ie. vertices are connected to other vertices that do not
 *  result from the same rotation step, errors creep in.
 *  addKeepingInRange() ensures that the vertices are kept within the same plane:
 *  \code
 *  [0,  6,  8, 2] -> [2,  8, 10, 4]
 *  [4, 10,  7, 1] -> [6, 12, 11, 5]
 *  [3,  9, 11, 5] -> [5, 11,  6, 0]
 *  \endcode
 *
 *  \todo Add the caps.
 */
Realm Realm::rotatedPolygon(unsigned num_segments, unsigned size) const {

    if (DEBUG_ROTATE) { cerr << "rotating surface: " << toString() << endl; }

    Realm rotated_walls = generateEmpty3DRealm();
    for (unsigned j = 0; j < num_segments; ++j) {
        addRotationStrip(rotated_walls, j, size);
    }

    rotatedPolygonCap(rotated_walls.getSubrealms());

    return rotated_walls;
}

Realm Realm::generateEmpty3DRealm() {
    Realm realm;
    realm.setDimension(3);
    return realm;
}

void Realm::addRotationStrip(Realm &all_strips, unsigned rotation_step, unsigned num_segments) const {
    Realm temp_realm = rotateStep(0, rotation_step*num_segments, num_segments);
    if (DEBUG_ROTATE) { 
        cerr << "addRotationStrip(..., " << rotation_step << ", " << num_segments << "): "
                << "temp realm: " << endl << temp_realm.toString(); }
    all_strips.merge(temp_realm);

    Realm temp_copy = temp_realm;
    temp_copy.addStayingWithinSameStrip(num_segments, rotation_step);
    if (DEBUG_ROTATE) { cerr << "temp copy: " << temp_copy.toString() << endl; }
    all_strips.merge(temp_copy);
}

/** Adds an offset to indices in the realm, generating the rectangle that is
 *  generated by rotating the line that is opposite (in the original polygon) of
 *  the line that generated this realm.
 *
 *  in other words, transforms a rectangle on a sphere to the rectangle lying
 *  directly across the sphere.
 *
 * - keep the "+1%num_segments" operation constrained to the two offending indices, but not the
 *   other two.
 * - ensure that both of the transformed indices stay in the target range, which is the vertices in
 *   the original strip for the smaller one and the vertices in the rotated strip for the bigger
 *   one. What is the target range? Well, every quad can be seen as a pair of pairs of indices:
 *   <tt>[ (base1, extruded1), (extruded2, base2)]</tt>. the base points need to remain in the base
 *   range <tt>[j*N, ..., j*(N+1)-1]</tt>, while the extruded points lie in
 *   <tt>[j*(N+1), ..., j*(N+2)-1]</tt>.
 *
 *  \param total_vertices Number of vertices per polygon.
 *  \param rotation_step Between 0 and num_segments-1.
 */
void Realm::addStayingWithinSameStrip(unsigned total_vertices, unsigned rotation_step)   {

    if (_dimension > 2) {
        for (realm_container_type::iterator i = _subrealm.begin(); i != _subrealm.end(); ++i) {
          i->addStayingWithinSameStrip(total_vertices, rotation_step);
        }
        return;
    }
    checkArgumentsForAddStayingWithinSameStrip();
    
    addOffset(OFFSET_BETWEEN_NEIGHBORING_INDICES);

    if (DEBUG_ROTATE) {
        cerr << toString()
            << " num_segments: "<< std::setw(4) << total_vertices << " rotation_step "<< std::setw(4) << rotation_step << endl;
    }

    std::pair<unsigned, unsigned> base_extruded1 = wrapToStayWithinStrip(_subrealm[0].toIndex(), _subrealm[1].toIndex(), total_vertices, rotation_step);
    _subrealm[0] = base_extruded1.first;
    _subrealm[1] = base_extruded1.second;

    std::pair<unsigned, unsigned> base_extruded2 = wrapToStayWithinStrip(_subrealm[3].toIndex(), _subrealm[2].toIndex(), total_vertices, rotation_step);
    _subrealm[3] = base_extruded2.first;
    _subrealm[2] = base_extruded2.second;

}

void Realm::checkArgumentsForAddStayingWithinSameStrip() const {

    if (_dimension < 2) {
        throw std::invalid_argument("generating Realm must be a rectangle: "+toString());
    }

    if (_subrealm.size() != 4) {
        throw std::invalid_argument(
                "generating Realm must consist of exactly 4 vertices: "+toString());
    }
}

std::pair<unsigned, unsigned> Realm::wrapToStayWithinStrip(unsigned base, unsigned extruded,
                                                           unsigned num_segments, unsigned rotation_step
                                                           ) const {
    unsigned min_base_index = rotation_step*num_segments,
             max_base_index = (rotation_step+1)*num_segments-1,
             min_extruded_index = max_base_index+1,
             max_extruded_index = (rotation_step+2)*num_segments-1;

    if (base > max_base_index) {
    
        if (extruded <= max_extruded_index) {
            throw std::logic_error(
                    "If the base index wraps out of the rotation strip, the extruded must too: "
                    +toString());
        }

        //  add and modulo here
        base++;
        extruded++;
        while (base > max_base_index || extruded > max_extruded_index) {
            base -= num_segments;
            extruded -= num_segments;
        }

        if (base < min_base_index || extruded < min_extruded_index) {
            throw new std::logic_error(
                    "While performing modulo operation, "
                    "an index dropped out of the current rotation strip!");
        }
    }
    
    return std::make_pair(base, extruded);
}

/** Create the cap (perpendicular to the rotation axis).
 *
 *  Make the first edge the first line in the temporary list of subrealms (assuming we have a
 *  square). To do that remove the last two vertices from the square.
 *
 *  \todo achieve the desired effect for any polygon
 */
Realm Realm::rotatedPolygonCap(const realm_container_type &rotated_walls) const {
    realm_container_type edges;

    Realm first_edge(*this);
    first_edge._subrealm.pop_back();
    first_edge._subrealm.pop_back();
    edges.push_back(first_edge);

    /// then add the following edges by using only the first point of the edge
    for (unsigned i = 0; i < rotated_walls.size(); ++i) {
        edges.push_back(rotated_walls[i]._subrealm[0]);
    }

    return edges;
}

Realm Realm::rotatedRealm(unsigned num_segments, unsigned size) const {
    realm_container_type temp_subrealms;
    for (unsigned i = 0; i < _subrealm.size(); ++i) {
        temp_subrealms.push_back(_subrealm[i].rotated(num_segments, size));
    }
    temp_subrealms.push_back(*this);
    Realm new_realm(temp_subrealms);
    if (DEBUG_ROTATE) { cout << "new realm: " << endl << new_realm.toString() << endl; }
    return new_realm;
}

/** The edges of the current Realm are rotated about some (clarify!) axis. The resulting image is
 *  connected to the current Realm, resulting in a Realm of the same dimension. The total set of
 *  thusly created Realms, for all degrees from 0 to 360, constitute the surface Realm of the
 *  rotated object. Phoo, another mouthful.
 * 
 *  \todo clarify this documentation.
 *  \param index Currently only used for lines. Do I really need it? What is it for?
 *  \param base
 *  \param delta
 */
Realm Realm::rotateStep(unsigned index, unsigned base, unsigned delta) const {
    if (DEBUG_ROTATE) { cout << "Realm::rotate_step(" << index << ", " << base << ", " << delta << "): "; }
    switch (_dimension) {
    case 0: throw std::logic_error(
            "Realm::rotate_step() can only operate on at least two vertices"
    );

    case 1: return Realm(_subrealm[index]._index+base+delta);
    case 2: return rotateStep2D(base, delta);

    default: throw NotYetImplementedException("Realm::rotate_step()");
    }
}

/** split procedure: once for points on the positive and once for negative points.
 *  what happens and actually seems to be necessary here is this.
 *  when i comment out the second loop in the case of a cylinder only
 *  half is drawn. in the case of a sphere only a quarter sphere is drawn
 *  regardless of whether the second loop runs or not.\n
 *  i suspect that there should be _subrealm.size()/2 loops of length 2.
 *  in the cylinder case, this happens to be the same as what we have here,
 *  because _subrealm.size() == 4.
 *
 *  \todo Split into smaller functions.
 *  \todo Fix for triangles.
 */
Realm Realm::rotateStep2D(unsigned base, unsigned delta) const {
    realm_container_type new_subrealms;
    if (DEBUG_ROTATE) {
        cerr << endl << "rotateStep2D(" << base << ", " << delta <<"): size: " << _subrealm.size() << endl;
    }

    if (size() < 4) {
        throw BadRotopeOperation("Realm::rotateStep2D()",
                                 "Rotating tapered object is not yet supported.");
    }

    for (unsigned i = 0; i < _subrealm.size()/2; ++i) {
        new_subrealms.push_back(generateRectSegment(i, base, delta));
    }
    // generate rectangles for the odd indices
    for (unsigned i = _subrealm.size()/2; i < _subrealm.size(); ++i) {
        new_subrealms.push_back(generateRectSegment(i, base, delta));
    }
    if (DEBUG_ROTATE) { 
        cerr  << "rotateStep2D(" << base << ", " << delta <<"): new subrealms: " << Realm(new_subrealms).toString(); }

    Realm new_realm;
    // here is the assumption that new_subrealms.size() is even.
    for (unsigned index = 0; index < new_subrealms.size(); index += 2) {
        Realm another_temp;

        for (realm_container_type::iterator i = new_subrealms[index].begin();
             i != new_subrealms[index].end(); ++i) {
            another_temp.push_back(*i);
        }

        for (realm_container_type::reverse_iterator i = new_subrealms[index+1].rbegin();
             i != new_subrealms[index+1].rend(); ++i) {
            another_temp.push_back(*i);
        }

        another_temp._dimension++;

        new_realm.push_back(another_temp);
    }

    if (DEBUG_ROTATE) { cerr  << "rotateStep2D(" << base << ", " << delta <<"): new realm: " << new_realm.toString() << endl; }

    return new_realm;
}

Realm Realm::generateRectSegment(unsigned i, unsigned base, unsigned delta) const {

    if (_subrealm[i].dimension()) throw new std::logic_error("At this point subrealms should be points");

    Realm new_subrealm;

    new_subrealm.push_back(_subrealm[i].toIndex()+base);
    new_subrealm.push_back(_subrealm[i].toIndex()+delta+base);

    return new_subrealm;
}
