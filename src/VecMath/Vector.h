/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef VECTOR_H
#define VECTOR_H 1

#include <cstdarg>
#include <cassert>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

# if (!defined __PI)
#   include <cmath>
    const double pi = 4.*atan (1.);
#   define __PI 3_14
# endif

/// \defgroup VecMath Vector and Matrix algebra

/// Vector and Matrix algebra
namespace VecMath {

  ///  Vector<D, N>: a D-dimensional vector of numbers of type N
  /** @tparam D dimension of the vector
   *  @tparam N numerical type of the vector elements
   *  \ingroup VecMath
   *  @author Lene Preuss <lene.preuss@gmail.com>                     */
  template <unsigned D, typename N = double> class Vector {

    public:

      //----------  management  ----------
      /// Default constructor.
      Vector<D, N> ();
      /// Make all elements have the same size.
      Vector<D, N> (const N &x);
      /// Constructor with variable argument list.
      Vector<D, N> (N x0, N x1, ... );

      //----------  access      ----------

      /// Returns a reference to component i
      N &operator[] (unsigned i);
      /// Returns component i by value
      N operator[] (unsigned i) const;

      static unsigned dimension (void);

      //----------  arithmetics ----------

      Vector<D, N> &operator+= (const Vector<D, N> &Y);
      Vector<D, N> &operator-= (const Vector<D, N> &Y);
      Vector<D, N> &operator*= (const N &s);

      /// Direct access to the array storing the components
      const N *data () const;               

      /// Convert the Vector into an array of arbitrary objects
      template <typename T> operator const T * () const;
        
      /// Convert Vector to a std::string.
      std::string toString() const;

      //  move the following functions out of the class!
        
      /** @return the squared norm of the vector, |V|�                      */
      N sqnorm (void) const;

    private:

      N _x[D]; ///< A static array storing the components
        
  };

  /// Unary minus
  template <unsigned D, typename N>    
  Vector<D, N> operator-(const Vector<D, N> &v);
  /// Plus
  template <unsigned D, typename N>    
  Vector<D, N> operator+(const Vector<D, N> &x, const Vector<D, N> &y);
  /// Binary minus
  template <unsigned D, typename N>    
  Vector<D, N> operator-(const Vector<D, N> &x, const Vector<D, N> &y);
        
  template <unsigned D, typename N>    
  Vector<D, N> operator* (const Vector<D, N> &x, const N &s);
  template <unsigned D, typename N>    
  Vector<D, N> operator* (const N &s, const Vector<D, N> &x);
    
  /// scalar multiplication between two Vectors (dot product)
  template <unsigned D, typename N>    
  N operator* (const Vector<D, N> &x, const Vector<D, N> &y);
    
  template <unsigned D, typename N>    
  Vector<D, N> operator/ (const Vector<D, N> &x, const N &s);
    
  /// divide every component of one vector by same component of another
  template <unsigned D, typename N>    
  Vector<D, N> operator/ (const Vector<D, N> &x, const Vector<D, N> &y);
    
  /// Comparison operator: Test for equality
  template <unsigned D, typename N>    
  bool operator==(const Vector<D, N> &one, const Vector<D, N> &other);
    
  /// Comparison operator: Test for inequality
  template <unsigned D, typename N>    
  bool operator!=(const Vector<D, N> &one, const Vector<D, N> &other);
    
  /// Ordering needed to use Vector as key for a std::map
  template <unsigned D, typename N>    
  bool operator<(const Vector<D, N> &one, const Vector<D, N> &other);

  /// Vector output operator
  template <unsigned D, typename N>
  std::ostream &operator << (std::ostream &s, const Vector<D, N> &v);

  /// Vector input operator
  template <unsigned D, typename N>
  std::istringstream &operator >> (std::istringstream &in, Vector<D, N> &v);

  /// Cross product of two 3-Vectors.
  template <typename N>
  Vector<3, N> vcross (Vector<3, N> a, Vector<3, N> b);

  /// Cross product of three 4-Vectors
  template <typename N>
  Vector<4, N> vcross (Vector<4, N> a, Vector<4, N> b, Vector<4, N> c);
     
  /// Normalizes a 3-Vector out-of-place
  template <unsigned D, typename N>
  Vector<D, N> vnormalize( const Vector<D, N> &x );
    
  /// Generator function for a 2-dimensional Vector
  template <typename N> Vector<2, N> makeVector(N const &x0, N const &x1);
    
  /// Generator function for a 3-dimensional Vector
  template <typename N> 
  Vector<3, N> makeVector(N const &x0, N const &x1, N const &x2);
    
  /// Generator function for a 4-dimensional Vector
  template <typename N> 
  Vector<4, N> makeVector(N const &x0, N const &x1, N const &x2, N const &x3);
    
  /// Generator function for a 5-dimensional Vector
  template <typename N> 
  Vector<5, N> makeVector(N const &x0, N const &x1, N const &x2, N const &x3, N const &x4);
    
  /// Generator function for a 6-dimensional Vector
  template <typename N> 
  Vector<6, N> makeVector(N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
                          N const &x5);
     
  /// Generator function for a 7-dimensional Vector
  template <typename N> 
  Vector<7, N> makeVector(N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
                          N const &x5, N const &x6);

  /// Generator function for a 8-dimensional Vector
  template <typename N> 
  Vector<8, N> makeVector(N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
                          N const &x5, N const &x6, N const &x7);
                            
  /// Generator function for a 9-dimensional Vector
  template <typename N> 
  Vector<9, N> makeVector(N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
                          N const &x5, N const &x6, N const &x7, N const &x8);
                            
  /// Generator function for a 10-dimensional Vector
  template <typename N> 
  Vector<10, N> makeVector(N const &x0, N const &x1, N const &x2, N const &x3, N const &x4,
                           N const &x5, N const &x6, N const &x7, N const &x8, N const &x9);

     
}
#endif                                                //  VECTOR_H
