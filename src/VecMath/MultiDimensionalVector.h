/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
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

#ifndef MULTIDIMENSIONAL_VECTOR_H
#define MULTIDIMENSIONAL_VECTOR_H

#include <vector>

namespace VecMath {

  /// A \p D -dimensionally nested std::vector of objects of type \p T
  /** As always, an example is more illustrative than a lengthy description:
   *  \code
   *    MultiDimensionalVector<unsigned, 1> v1;
   *    v[i] = 1;
   *    MultiDimensionalVector<double, 2> v2;
   *    v[i][j] = 1.0;
   *    MultiDimensionalVector<std::string, 4> v4;
   *    v[i][j][k][l] = "hello, world!";
   *  \endcode
   *  This class emulates the std::vector interface to the extent that it is used
   *  in HyperspaceExplorer. It does not inherit from std::vector, but it behaves
   *  like one.
   *
   *  \tparam T Type that is eventually stored
   *  \tparam D Dimensionality (nesting depth) of the vector
   *
   *  \ingroup VecMath
   *  \author Lene Preuss <lene.preuss@gmail.com>
   */
  template <typename T, unsigned D> 
  class MultiDimensionalVector: public MultiDimensionalVector<T, D-1> {

    public:
      
      /// Iterator type to loop over elements, read/write - from std::vector
      typedef typename std::vector<MultiDimensionalVector<T, D-1> >::iterator iterator;

      /// Iterator type to loop over elements, read only - from std::vector
      typedef typename std::vector<MultiDimensionalVector<T, D-1> >::const_iterator const_iterator;

      /// Construct an empty MultiDimensionalVector
      MultiDimensionalVector();

      /// Construct an MultiDimensionalVector with \p n empty elements
      MultiDimensionalVector(unsigned n);

      /// Construct a MultiDimensionalVector from an iterator range
      MultiDimensionalVector(typename std::vector<MultiDimensionalVector<T, D-1> >::iterator first,
                             typename std::vector<MultiDimensionalVector<T, D-1> >::iterator last);

      /// Copy construct a MultiDimensionalVector
      MultiDimensionalVector(const MultiDimensionalVector<T, D> &v);

      /// Iterator that points to the first element in the vector
      iterator begin();

      /// Iterator that points one past the last element in the vector
      iterator end();

      /// Read-only iterator that points to the first element in the vector
      const_iterator begin() const;

      /// Read-only iterator that points one past the last element in the vector
      const_iterator end() const;

      /// Add data to the end of the vector
      void push_back(const MultiDimensionalVector<T, D-1> &x);

      /// Remove element at given position
      iterator erase(iterator position);

      /// Remove elements at given range
      iterator erase(iterator first, iterator last);

      /// Subscript access to the data contained in the vector
      MultiDimensionalVector<T, D-1> &operator [] (unsigned i);

      /// Subscript access to the data contained in the vector
      const MultiDimensionalVector<T, D-1> &operator [] (unsigned i) const;

      /// Returns the number of elements in the vector
      unsigned size() const;

      /// Returns true if the vector is empty. (Thus begin() would equal end().)
      unsigned empty() const;

      /// Erases all the elements, and calls clear() on them recursively.
      void clear();

      /// Resizes the vector to the specified number of elements
      void resize(unsigned new_size);

      /// Resizes the vector to the specified number of elements
      void resize(unsigned new_size, MultiDimensionalVector<T, D-1> x);

      /// Returns true if \p other is not equal to \p this
      bool operator == (const MultiDimensionalVector<T, D> &other) const;

      /// Returns true if \p other is not equal to \p this
      bool operator != (const MultiDimensionalVector<T, D> &other) const;

      /// Apply a function or functor on every element of a MultiDimensionalVector
      template <typename Function> Function for_each(Function f);
      /// Apply a function or functor on every element of a MultiDimensionalVector
      template <typename Function> Function for_each(Function f) const;

      /// Convert NestedVector to a std::string.
      std::string toString() const;

      /// Prints the elements of the vector
      void print() const;

    protected:

      /// Access to the stored vector
      std::vector<MultiDimensionalVector<T, D-1> > &data();

      /// Read-only access to the stored vector
      const std::vector<MultiDimensionalVector<T, D-1> > &data() const;

    private:
      /// A std::vector of dimensionality \p D - 1
      /** All operations are delegated to this vector. */
      std::vector<MultiDimensionalVector<T, D-1> > _data;
  };

  /// Print a MultiDimensionalVector<T, D> on a std::ostream
  template<typename T, unsigned D> 
  std::ostream& operator<<(std::ostream& s, MultiDimensionalVector<T, D> const& v);

  /// Find an element in a MultiDimensionalVector
  template <typename T, unsigned D>
  typename MultiDimensionalVector<T, D>::iterator find(MultiDimensionalVector<T, D-1> const &find_me,
                                                       MultiDimensionalVector<T, D> &v);

                                                       
  /// Specialization of NestedVector<T, D> for \p D = 1
  template<typename T> 
  class MultiDimensionalVector<T, 1> {
  
    public:
    
      /// See MultiDimensionalVector<T, D>::iterator
      typedef typename std::vector<T>::iterator iterator;
      /// See MultiDimensionalVector<T, D>::const_iterator
      typedef typename std::vector<T>::const_iterator const_iterator;

      /// See MultiDimensionalVector<T, D>::MultiDimensionalVector()
      MultiDimensionalVector();
      /// See MultiDimensionalVector<T, D>::MultiDimensionalVector()
      MultiDimensionalVector(unsigned n);
     
      /// See MultiDimensionalVector<T, D>::begin()
      iterator begin();
      /// See MultiDimensionalVector<T, D>::end()
      iterator end();
      /// See MultiDimensionalVector<T, D>::begin()
      const_iterator begin() const;
      /// See MultiDimensionalVector<T, D>::end()
      const_iterator end() const;

      /// See MultiDimensionalVector<T, D>::push_back()
      void push_back(const T &x);

      /// See MultiDimensionalVector<T, D>::erase()
      iterator erase(iterator position);

      /// Remove elements at given range
      iterator erase(iterator first, iterator last);

      /// See MultiDimensionalVector<T, D>::operator []()
      T &operator [] (unsigned i);
      /// See MultiDimensionalVector<T, D>::operator []()
      const T &operator [] (unsigned i) const;

      /// See MultiDimensionalVector<T, D>::size()
      unsigned size() const;
      /// See MultiDimensionalVector<T, D>::empty()
      unsigned empty() const;

      /// See MultiDimensionalVector<T, D>::clear()
      void clear();

      /// See MultiDimensionalVector<T, D>::resize()
      void resize(unsigned new_size);

      /// Resizes the vector to the specified number of elements
      void resize(unsigned new_size, T x);

      /// See MultiDimensionalVector<T, D>::operator ==()
      bool operator == (const MultiDimensionalVector<T, 1> &other) const;

      /// See MultiDimensionalVector<T, D>::operator !=()
      bool operator != (const MultiDimensionalVector<T, 1> &other) const;

      /// Apply a function or functor on every element of a MultiDimensionalVector
      template <typename Function> Function for_each(Function f);
      /// Apply a function or functor on every element of a MultiDimensionalVector
      template <typename Function> Function for_each(Function f) const;
      
      /// Convert MultiDimensionalVector to a std::string.
      std::string toString() const;

      /// See MultiDimensionalVector<T, D>::print()
      void print() const;

      /// Whether to print the number of elements with operator <<().
      static bool print_num_elements();
      /// How deep to insert maximally with operator <<().
      static unsigned max_dimension();
    
    protected:
      /// See MultiDimensionalVector<T, D>::data()
      std::vector<T> &data();
      /// See MultiDimensionalVector<T, D>::data()
      const std::vector<T> &data() const;
    
    private:
      /// std::vector<T>. All operations are delegated to this vector.
      std::vector<T> _data;

      /// Compile-time configuration: Whether to print the number of elements with operator <<().
      static const bool PRINT_NUM_ELEMENTS = false;
      /// Compile-time configuration: How deep to insert maximally with operator <<().
      static const unsigned MAX_DIMENSION = 4;
    
  };
  
  /// Print a MultiDimensionalVector<T, 1> on a std::ostream
  template<typename T> 
  std::ostream& operator<<(std::ostream& s, MultiDimensionalVector<T, 1> const& v);

}


#endif
