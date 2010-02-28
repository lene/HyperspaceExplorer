///
/// C++ Interface: Realm
///
/// Description:
///
///
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
    operator unsigned() const;

    /// Create a new Realm by extruding the present Realm.
    Realm extrude(unsigned delta);

    /// Create a new Realm by tapering the present Realm.
    Realm taper(unsigned taper_index);

    /// Create a new Realm by rotating the present Realm.
    Realm rotate(unsigned num_segments, unsigned size);

    /// Merge \p r into the current Realm, keeping the dimension as it is.
    void merge(const Realm &r);

    const realm_container_type &getSubrealms() const { return _subrealm; }

    void setSubrealms(realm_container_type sr) { _subrealm = sr; }

    /// Whether all the elements in two Realms are equal
    bool operator==(const Realm &other) const;

    /// Whether a Realm contains another, either directly or in any subrealm
    bool contains(const Realm &other) const;

    std::string toString() const;
    operator std::string() const { return toString(); }

    /// Add an offset to all indices into the vertex array.
    /** public only to satisfy unit tests.
     *  \todo find a better way.
     */
    void add(unsigned delta);

private:

    ///  Extrude a point to a line
    Realm extrudePoint(unsigned delta);
    ///  Extrude a line to a square
    Realm extrudeLine(unsigned delta);
    ///  Extrude a polygon to a prism
    Realm extrudePolygon(unsigned delta);
    ///  Extrude an N-dimensional Realm to a N+1-dimensional one, where N > 2
    Realm extrudeRealm(unsigned delta);

    ///  Taper a line to a triangle
    Realm taperLine(unsigned taper_index);
    ///  Taper a polygon to a pyramid
    Realm taperPolygon(unsigned taper_index);
    ///  Taper an N-dimensional Realm to a N+1-dimensional one, where N > 2
    Realm taperRealm(unsigned taper_index);

    /// Rotate a line into a polygon approximating a circle.
    Realm rotateLine(unsigned num_segments, unsigned size);

    std::list<realm_container_type> generateListOfPointsToAdd(
        std::list<Realm> original_list, unsigned num_segments, unsigned size);
    void insertNewPoints(std::list<Realm> &original_list,
                         const std::list<Realm::realm_container_type> &new_points);

    /// Rotate a polygon into a quasi-sphere, cylinder or cone.
    Realm rotatePolygon(unsigned num_segments, unsigned size);
    /// Upper and lower cap for a rotated polygon.
    Realm rotatePolygonCap(const realm_container_type &temp_subrealms);
    /// Rotate a Realm of at least 3 dimensions.
    Realm rotateRealm(unsigned num_segments, unsigned size);

    /// Create a Realm by extruding edges for one step of a rotation.
    Realm rotateStep(unsigned index, unsigned base, unsigned delta);
    /// Create a three-dimensional Realm from a polygon for one rotation step.
    Realm rotateStep2D(unsigned base, unsigned delta);

    Realm generateRectSegment(unsigned i, unsigned base, unsigned delta);

    /// Accumulate the rectangles generated by connecting the edges of a polygon with the polygon rotated into a new dimension.
    void addRotationStrip(Realm &all_strips, unsigned rotation_step, unsigned num_segments);
    /// Transforms a rectangle on a sphere to the rectangle lying directly across the sphere.
    void addStayingWithinSameStrip(unsigned total_vertices, unsigned rotation_step);
    /// Make sure addStayingWithinSameStrip() is called only on a valid Realm.
    void checkArgumentsForAddStayingWithinSameStrip();
    /// If \p base or \p extruded point beyond the current rotation strip, wrap them around so they remain within it.
    std::pair<unsigned, unsigned> wrapToStayWithinStrip(unsigned base, unsigned extruded,
                                                        unsigned num_segments, unsigned rotation_step);

    /// \return A Realm of dimension 3, with no Realms contained.
    static Realm generateEmpty3DRealm();

    /// Dimension of the realm
    unsigned _dimension;
    /// Subrealms the Realm is made of
    realm_container_type _subrealm;
    /// If _dimension == 0, this is the index into the vertex array
    unsigned _index;

    const static bool DEBUG_ROTATE = true;
    static const unsigned OFFSET_BETWEEN_NEIGHBORING_INDICES = 2;

    /// Auxiliary class encapsulating printing and conversion to std::string.
    class RealmPrinter {

        static const std::string PRINT_DIMENSION_SPACER;

    public:
        RealmPrinter(const Realm *realm): _realm(realm) { }

        /// Prints the elements of the Realm.
        void print(std::ostream &out) const;

    private:
        void printHeader(std::ostream &out) const;
        void printFooter(std::ostream &out) const;
        void printPoint(std::ostream &out) const;
        void printSubrealms(std::ostream &out) const;
        void indentNextLine(std::ostream &out) const;

        const Realm * _realm;
        /** Highest dimension of a Realm encountered during program run; used for
         *  print formatting
         */
        static unsigned _max_dimension;

    };

};

#endif
