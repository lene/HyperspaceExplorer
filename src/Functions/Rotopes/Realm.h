///
/// C++ Interface: Realm
///
/// Description:
///
///
/// @author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2009
///
/// Copyright: See COPYING file that comes with this distribution
///
/// \ingroup RotopeGroup
///

#ifndef REALM_H
#define REALM_H

#include "uintvec.h"
#include "Vector.h"
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
 *  \todo It looks as if it would make sense for Realm to manage the vertex
 *   array too. Look into this.
 *
 *  \ingroup RotopeGroup
 *  \author Lene Preuss <lene.preuss@gmail.com>
 */
class Realm {
    public:

        /// Default constructor: Realm points to the first vertex in the array.
        Realm(): _dimension(0), _subrealm(), _index(1) { }

        /// Construct a Realm pointing to a specified vertex.
        /** \param i The index of the vertex in the vertex array.
         */
        Realm(unsigned i): _dimension(0), _subrealm(), _index(i) { }

        /// Construct a Realm from a number of subrealms.
        /** \param sr The subrealms which together make up the new Realm.
         */
        Realm(const std::vector<Realm> &sr): _subrealm(sr), _index() {
            if(sr.empty()) _dimension = 0;
            else _dimension = sr[0].dimension()+1;
        }

        /// Destructor. Frees managed Realms automatically.
        ~Realm() { }

        /// Returns the number of subrealms the Realm is made of.
        unsigned size() const { return _subrealm.size(); }
        /// Returns the dimension of the realm.
        unsigned dimension() const { return _dimension; }
        /// Sets the dimension of the realm.
        void setDimension(unsigned d) { _dimension = d; }
        /// Prints the elements of the Realm.
        void print() const;

        /// Create a new Realm by extruding the present Realm.
        /** \param delta How many elements there were in the original vertex
         *      array - IOW, how much there needs to be added to each index from
         *      the original Realm to be pointing to the corresponding vertex
         *      in the extruded vertex array. (Gee, that's a mouthful.)
         */
        Realm extrude(unsigned delta);

        /// Create a new Realm by tapering the present Realm.
        /** \param taper_index Index in the vertex array of the new vertex,
         *      toward which the object is tapered.
         */
        Realm taper(unsigned taper_index);

        /// Create a new Realm by rotating the present Realm.
        /** \todo more documentation
         *  \param num_segments How many segments to use approximating a circle.
         *  \param size Size of the original vertex array. See extrude().
         */
        Realm rotate(unsigned num_segments, unsigned size);

        /// Add an offset to all indices into the vertex array.
        void add(unsigned delta);

        /// Add a new subrealm, emulating std::vector<Realm> interface.
        void push_back(const Realm &r);

        /// Pointer to first subrealm, emulating std::vector<Realm> interface.
        std::vector<Realm>::iterator begin() { return _subrealm.begin(); }

        /// Pointer past last subrealm, emulating std::vector<Realm> interface.
        std::vector<Realm>::iterator end() { return _subrealm.end(); }

        /// Pointer to last subrealm, emulating std::vector<Realm> interface.
        std::vector<Realm>::reverse_iterator rbegin() { return _subrealm.rbegin(); }

        /// Pointer before first subrealm, emulating std::vector<Realm> interface.
        std::vector<Realm>::reverse_iterator rend() { return _subrealm.rend(); }

        /// Makes a Realm of dimension 0 usable as index into the vertex array.
        operator unsigned() const { return _index; }

        /// Dimension of the realm.
        unsigned &dimension() { return _dimension; }

        const std::vector<Realm> &getSubrealms() const { return _subrealm; }

        void setSubrealms(std::vector<Realm> sr) { _subrealm = sr; }

    private:

      ///  Extrude a point to a line
      Realm extrudePoint(unsigned delta);
      ///  Extrude a line to a square
      Realm extrudeLine(unsigned delta);
      ///  Extrude a polygon to a prism
      Realm extrudePolygon(unsigned delta);
      Realm extrudeObject(unsigned delta);
      
        /// Create a Realm by extruding edges for one step of a rotation.
        /** The edges of the current Realm are rotated about some (clarify!)
         *  axis. The resulting image is connected to the current Realm,
         *  resulting in a Realm of the same dimension. The total set of thusly
         *  created Realms, for all degrees from 0 to 360, constitute the
         *  surface Realm of the rotated object. Phoo, another mouthful.
         *  \todo clarify this documentation.
         *  \param index Currently only used for lines. Do I really need it?
         *      What is it for?
         *  \param base
         *  \param delta
         */
        Realm rotate_step(unsigned index, unsigned base, unsigned delta);

        /// Convert a set of lines to a surface as a set of points.
        void convertToSurface();

        /// Dimension of the realm
        unsigned _dimension;
        /// Subrealms the Realm is made of
        std::vector<Realm> _subrealm;
        /// If _dimension == 0, this is the index into the vertex array
        unsigned _index;
};

#endif
