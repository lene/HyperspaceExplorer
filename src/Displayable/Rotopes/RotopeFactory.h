/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2008-2010  Lene Preuss <lene.preuss@gmail.com>

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

class RotopeInterface;
template <unsigned D> class VertexData;

#include <string>

/// A class to generate Rotopes
/** Sports a static method generate() which takes a list of extrusion actions as
 *  string and creates a Rotope of the actions, performing them in the order in
 *  which they were specified
 *
 *  \ingroup RotopeGroup
 */
class RotopeFactory {

public:

  /// Generate a Rotope
  static RotopeInterface *generate(const std::string &actions);

private:

  /// Functor class to perform an extrusion on a Rotope or vertex array
  /** \tparam D Dimension of vector space we operate in
   *  \tparam d Dimension we want to extrude into
   */
  template <unsigned D, unsigned d> struct RotopeAction: public RotopeAction<D, d-1> {
    /// Perform the extrusion operations
    VertexData<D> *operator()(std::string actions,
                              VertexData<D> *rotope);
  };

  /// Specialization for extruding into the dimension 0 to end recursion
  /** \tparam D Dimension of vector space we operate in
   */
  template <unsigned D> struct RotopeAction<D, 0> {
    /// Perform the extrusion operations
    VertexData<D> *operator()(std::string actions,
                              VertexData<D> *rotope);
  };
};
