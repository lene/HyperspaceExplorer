/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2009-2010  Lene Preuss <lene.preuss@gmail.com>

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

/// @author: Lene Preuss <lene.preuss@gmail.com>, (C) 2009
///
/// Copyright: See COPYING file that comes with this distribution
///
/// \ingroup RotopeGroup
///

#ifndef REALM_H
#define REALM_H

//#include "uintvec.h"
#include "Vector.h"

#include <string>
#include <list>
#include <vector>

class Rotope;

/// \p N - dimensional surface on a vertex array.
/** A Realm stores a N-dimensional surface in the form of indices into the
 *  object's vertex array. The vertex array is not managed by the Realm and must
 *  be independently managed.
 *
 *  Every Realm is made up of subrealms: E.g. a rectangle, as part of the surface
 *  of a three-dimensional object, is made up of lines, and a line is made up of
 *  its endpoints. Thus, a Realm stores its subrealms, except for points, which
 *  are stored as the index of the corresponding \p N - dimensional vertex in
 *  the vertex array of the described object.
 *
 *  Realm emulates the interface of std::vector<Realm>, as far as this interface
 *  is used.
 *
 *  \todo fully understand and document rotating polygons
 *  \todo add caps for polygons
 *  \todo It looks as if it would make sense for Realm to manage the vertex
 *      array too. Look into this.
 *  \todo refactor to have shorter functions.
 *
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
class Realm {

public:

    /// Storage type for the vertices.
    typedef std::vector<VecMath::Vector<4> > vertex_container_type;
    /// Must support push_back, forward iterator, reverse iterator, operator[].
    typedef std::vector<Realm> realm_container_type;

    /// Default constructor: Realm points to the first vertex in the array.
    Realm(): _dimension(0), _subrealm(), _index(0) { }

    /// Construct a Realm pointing to a specified vertex.
    /** \param i The index of the vertex in the vertex array.
     */
    Realm(unsigned i): _dimension(0), _subrealm(), _index(i) { }

    /// Construct a Realm from a number of subrealms.
    /** \param sr The subrealms which together make up the new Realm.
     */
    Realm(const realm_container_type &sr): _subrealm(sr), _index() {
        if(sr.empty()) _dimension = 0;
        else _dimension = sr[0].dimension()+1;
    }

    /// Destructor. Frees managed Realms automatically.
    ~Realm() { }

    /// Returns the number of subrealms the Realm is made of, emulating realm_container_type interface.
    unsigned size() const { return _subrealm.size(); }
    /// Returns the Realm to a completely empty state, emulating realm_container_type interface.
    void clear();
    /// Add a new subrealm to the list, emulating realm_container_type interface.
    void push_back(const Realm &r);
    /// Pointer to first subrealm, emulating realm_container_type interface.
    realm_container_type::iterator begin() { return _subrealm.begin(); }
    /// Const pointer to first subrealm, emulating realm_container_type interface.
    realm_container_type::const_iterator cbegin() const { return _subrealm.begin(); }

    /// Pointer past last subrealm, emulating realm_container_type interface.
    realm_container_type::iterator end() { return _subrealm.end(); }
    /// Const pointer past last subrealm, emulating realm_container_type interface.
    realm_container_type::const_iterator cend() const { return _subrealm.end(); }

    /// Reverse pointer to last subrealm, emulating realm_container_type interface.
    realm_container_type::reverse_iterator rbegin() { return _subrealm.rbegin(); }

    /// Reverse pointer before first subrealm, emulating realm_container_type interface.
    realm_container_type::reverse_iterator rend() { return _subrealm.rend(); }

    /// Returns the dimension of the realm.
    unsigned dimension() const { return _dimension; }
    /// Sets the dimension of the realm.
    void setDimension(unsigned d) { _dimension = d; }

    /// Makes a Realm of dimension 0 usable as index into the vertex array.
    unsigned toIndex() const;

    /// Create a new Realm by extruding the present Realm.
    Realm extruded(unsigned delta) const;

    /// Create a new Realm by tapering the present Realm.
    Realm tapered(unsigned taper_index) const;

    /// Create a new Realm by rotating the present Realm.
    Realm rotated(unsigned num_segments, unsigned size) const;

    /// Merge \p r into the current Realm, keeping the dimension as it is.
    void merge(const Realm &r);

    /// Get the list of subrealms this Realm is made up from.
    const realm_container_type &getSubrealms() const { return _subrealm; }

    /// Manually set the list of subrealms.
    void setSubrealms(realm_container_type sr) { _subrealm = sr; }

    /// Whether all the elements in two Realms are equal
    bool operator==(const Realm &other) const;

    /// Whether a Realm contains another, either directly or in any subrealm
    bool contains(const Realm &other) const;

    /// String representation
    std::string toString() const;

    /// Add an offset to all indices into the vertex array.
    /** public only to satisfy unit tests.
     *  \todo find a better way.
     */
    void addOffset(unsigned delta);

private:

    ///  Extrude a point to a line
    Realm extrudedPoint(unsigned delta) const;
    ///  Extrude a line to a square
    Realm extrudedLine(unsigned delta) const;
    ///  Extrude a polygon to a prism
    Realm extrudedPolygon(unsigned delta) const;
    ///  Extrude an N-dimensional Realm to a N+1-dimensional one, where N > 2
    Realm extrudedRealm(unsigned delta) const;

    ///  Taper a line to a triangle
    Realm taperedLine(unsigned taper_index) const;
    ///  Taper a polygon to a pyramid
    Realm taperedPolygon(unsigned taper_index) const;
    ///  Taper an N-dimensional Realm to a N+1-dimensional one, where N > 2
    Realm taperedRealm(unsigned taper_index) const;

    /// Rotate a line into a polygon approximating a circle.
    Realm rotatedLine(unsigned num_segments, unsigned size) const;

    /// Which points are generated when rotating a line.
    std::list<realm_container_type> generateListOfPointsToAdd(
        std::list<Realm> original_list,
        unsigned num_segments, unsigned size) const;
    /// Add points generated from rotating a line.
    void insertNewPoints(std::list<Realm> &original_list,
                         const std::list<Realm::realm_container_type> &new_points) const;

    /// Rotate a polygon into a quasi-sphere, cylinder or cone.
    Realm rotatedPolygon(unsigned num_segments, unsigned size) const;
    /// Upper and lower cap for a rotated polygon.
    Realm rotatedPolygonCap(const realm_container_type &temp_subrealms) const;
    /// Rotate a Realm of at least 3 dimensions.
    Realm rotatedRealm(unsigned num_segments, unsigned size) const;

    /// Create a Realm by extruding edges for one step of a rotation.
    Realm rotateStep(unsigned index, unsigned base, unsigned delta) const;
    /// Create a three-dimensional Realm from a polygon for one rotation step.
    Realm generateStripBetweenGreatCircles(unsigned base, unsigned delta) const;

    /// Generates a list of rectangular surface segments which make up a strip between two great circles.
    realm_container_type rectsBetweenGreatCircles(unsigned base, unsigned delta) const;
    /// Makes elements of a strip between great circles have the correct orders.
    Realm reorderRectsBetweenGreatCircles(Realm::realm_container_type subrealms, unsigned int index) const;
    /// Generates a rectangular surface segment of a sphere.
    Realm generateRectSegment(unsigned i, unsigned base, unsigned delta) const;

    /// Accumulate the rectangles generated by connecting the edges of a polygon with the polygon rotated into a new dimension.
    void addRotationStrip(Realm &all_strips, unsigned rotation_step, unsigned num_segments) const;
    /// Transforms a rectangle on a sphere to the rectangle lying directly across the sphere.
    void addStayingWithinSameStrip(unsigned total_vertices, unsigned rotation_step);
    /// Make sure addStayingWithinSameStrip() is called only on a valid Realm.
    void checkArgumentsForAddStayingWithinSameStrip() const;
    /// If \p base or \p extruded point beyond the current rotation strip, wrap them around so they remain within it.
    std::pair<unsigned, unsigned> wrapToStayWithinStrip(unsigned base, unsigned extruded,
                                                        unsigned num_segments, unsigned rotation_step) const;

    /// \return A Realm of dimension 3, with no Realms contained.
    static Realm generateEmpty3DRealm();

    /// Dimension of the realm
    unsigned _dimension;
    /// Subrealms the Realm is made of
    realm_container_type _subrealm;
    /// If _dimension == 0, this is the index into the vertex array
    unsigned _index;

    /// Whether to print debug output in the rotate() function.
    const static bool DEBUG_ROTATE = false;
    /// How far vertices, that are actually neighbors in geometry, are apart in the vertex array.
    static const unsigned OFFSET_BETWEEN_NEIGHBORING_INDICES = 2;

    /// Auxiliary class encapsulating printing and conversion to std::string.
    class RealmPrinter {

        /// Spacer to indent a line depending on the depth of recursion.
        static const std::string PRINT_DIMENSION_SPACER;

    public:

        /// Initializes a RealmPrinter with a Realm.
        RealmPrinter(const Realm *realm): _realm(realm) { }

        /// Prints the elements of the Realm.
        void print(std::ostream &out) const;

    private:
        /// Prints dimension of Realm and opening bracket.
        void printHeader(std::ostream &out) const;
        /// Prints closing bracket.
        void printFooter(std::ostream &out) const;
        /// Prints the index of a single point.
        void printPoint(std::ostream &out) const;
        /// Prints all subrealms of the given Realm.
        void printSubrealms(std::ostream &out) const;
        /// Indents a line before it is printed.
        void indentNextLine(std::ostream &out) const;

        /// Realm to be printed.
        const Realm * _realm;

        /** Highest dimension of a Realm encountered during program run; used for
         *  print formatting
         */
        static unsigned _max_dimension;

    };

};

#endif
