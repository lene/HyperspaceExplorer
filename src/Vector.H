
//      project:      hyperspace explorer
//      module:       Vector.H
//      contains:     class definitions for class Vector
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#ifndef VECTOR_H
#define VECTOR_H 1

#include <iostream>
#include <stdarg.h>
#include <string>

# if (!defined __PI)
#   include <cmath>
    const double pi = 4.*atan (1.);
#   define __PI 3_14
# endif

template <unsigned D> class Vector {
  public:

    //----------  management  ----------

    //  constructor: given a pointer to double, interprets it as n-dimensional vector 
    //  defaults are n = Vector::DefaultDim, A = 0; they are set in the implementation,
    //  because they must be defined after Vector::DefaultDim
    Vector<D> (double *A); 
    Vector<D> (double, ... );

    ~Vector<D> (void);                                   //  destructor

    //  copy constructor: makes a deep copy, if deep == true, else a shallow one
    Vector<D> (const Vector<D> &X, bool deep = true);

    Vector<D> &operator= (const Vector<D> &Y);              // assignment operator
//    Vector<D> operator= (const Vector<D> &Y);              // assignment operator

    //----------  validity    ----------

    operator bool  (void) const;                      // true if valid, false if not
    bool operator! (void) const;                      // false if valid, true if not
      
    //  ownership concept:
    bool owner (void) const;                          // true if object is owner of data

    void invalidate (void);                           //  invalidates an object, destroying data if owner

    //----------  access      ----------

    //  operator [] returns a reference to component i (no boundary checking!)
    double &operator[] (unsigned i);

    //  operator [] const returns component i (read-only access, no check)
    double operator[] (unsigned i) const;

    unsigned dimension (void) const;

    //----------  arithmetics ----------

    Vector<D> &operator+= (const Vector<D> &Y);
    Vector<D> &operator-= (const Vector<D> &Y);
    Vector<D> &operator*= (const double &s);

    Vector<D> operator- (void) const;
    Vector<D> operator+ (const Vector<D> &Y);
    Vector<D> operator- (const Vector<D> &Y);
    Vector<D> operator* (const double &s);
    double operator* (const Vector<D> &X);
    Vector<D> operator/ (const double &s);

    bool operator== (const Vector<D> &Y);
    bool operator!= (const Vector<D> &Y);

    double sqnorm (void);
    double norm (void);
    Vector normalize (void);

    double *data () { return x; }

  private:
    double *x;
    bool own; };
 
template <unsigned D> std::ostream &operator << (std::ostream &, const Vector<D> &);
template <unsigned D> std::istream &operator >> (std::istream &, Vector<D> &);

template <unsigned D> Vector<D> cross (const Vector<D> &, const Vector<D> &);




//------------  Vector member functions

    //  ------------  management  ------------

template <unsigned D> inline Vector<D>::Vector (double *A = 0):
    x (A ? A : new double [D]), own (A? false: true) { } //  implicitly initialized to zero vector
  
template <unsigned D> inline Vector<D>::~Vector (void) { if (own) delete [] x; }
  
//template <unsigned D> Vector<D> Vector<D>::operator= (const Vector<D> &Y) {
//    return operator=(Y);
//}
    
    //----------  validity    ----------     

template <unsigned D> inline Vector<D>::operator bool  (void) const { return  x; }
template <unsigned D> inline bool Vector<D>::operator! (void) const { return !x; }

template <unsigned D> inline void Vector<D>::invalidate (void) {
  if (own) delete [] x;
  x = 0;
  own = false;
}

    //----------  access      ----------

template <unsigned D> inline double &Vector<D>::operator[] (unsigned i) { 
  return x[i];                                                   //  no boundary checking!
}

template <unsigned D> inline double Vector<D>::operator[] (unsigned i) const {
  return x[i];                                                  //  -''- !
}                                                                  //  valgrind: "Use of uninitialised value of size 8"
                                                                  //  at Vector::operator[](unsigned int) const (Vector.H:128)

template <unsigned D> inline unsigned Vector<D>::dimension (void) const { return D; }

    //----------  arithmetics ----------

template <unsigned D> inline Vector<D> &Vector<D>::operator+= (const Vector<D> &Y) {
  for (unsigned i = 0; i < D; i++) x[i] += Y.x[i] ;
  return *this; 
}

template <unsigned D> inline Vector<D> &Vector<D>::operator-= (const Vector<D> &Y) {
  for (unsigned i = 0; i < D; i++) x[i] -= Y.x[i] ;
  return *this; 
}

template <unsigned D> inline Vector<D> &Vector<D>::operator*= (const double &s) {             //  scalar multiplication
  for (unsigned i = 0; i < D; i++) x[i] *= s ;
  return *this;
}

template <unsigned D> inline Vector<D> Vector<D>::operator- (void) const {
  static Vector Z;
  Z = *this;
  for (unsigned i = 0; i < D; i++) Z.x[i] = -x[i] ;
  return Z; 
}

template <unsigned D> inline Vector<D> Vector<D>::operator+ (const Vector<D> &Y) {
  static Vector Z;
  Z = *this;
  return (Z += Y); 
}

template <unsigned D> inline Vector<D> Vector<D>::operator- (const Vector<D> &Y) {
  static Vector Z;
  Z = *this;
  return (Z -= Y); 
}

template <unsigned D> inline Vector<D> Vector<D>::operator* (const double &s) {               //  scalar multiplication
  /*static*/ Vector Z;
  Z = *this;
  return Z *= s; 
}

template <unsigned D> inline double Vector<D>::operator* (const Vector<D> &Y) {               //  dot product
  double dot = 0.;
  for (unsigned i = 0; i < D; i++)
    if (x[i]) dot += x[i]*Y.x[i];				  //  valgrind barks "Use of uninitialised value of size 8"
				                                  //  at Vector::operator*(Vector const &) (Vector.H:174)
  return dot; 
}

template <unsigned D> inline Vector<D> Vector<D>::operator/ (const double &s) {               //  scalar multiplication
  return operator* (1./s); 
}

template <unsigned D> inline bool Vector<D>::operator== (const Vector<D> &Y) {
  for (unsigned i = 0; i < D; i++)
    if (x[i] != Y.x[i]) return false;
  return true; 
}

template <unsigned D> inline bool Vector<D>::operator!= (const Vector<D> &Y) {
  return !operator== (Y); 
}

template <unsigned D> inline double Vector<D>::sqnorm (void) {
  return operator* (*this); 
}

template <unsigned D> inline double Vector<D>::norm (void) {
  return sqrt (sqnorm ()); 
}

template <unsigned D> inline Vector<D> Vector<D>::normalize (void) {
  double n = norm ();
  if (n > 0.) return operator* (1./sqrt (n));
  else return *this; 
}

using std::cerr;
using std::endl;
using std::ostream;
using std::istream;

//------------  Vector member functions and static variable initialization


    //----------  management  ----------

template <unsigned D> Vector<D>::Vector (double x0, ... ) :	//  Vector:: constructor with variable arglist
        x (new double [D]), own (true) {
    x[0] = x0;
    unsigned i = 0;
    va_list argp;
    va_start (argp, x0);
    for (i = 1; i < D; i++) {
        x[i] = va_arg (argp, double); }
        va_end (argp);
        }

        template <unsigned D> Vector<D>::Vector (const Vector<D> &X, bool deep) :		//  Vector:: copy constructor
                own (deep) {
            if (deep) {						//  deep copy
                x = new double [D];
                for (unsigned i = 0; i < D; i++) x[i] = X[i];
            } else							//  shallow copy
                x = X.x;
                }

                template <unsigned D> Vector<D> &Vector<D>::operator= (const Vector<D> &Y) {
                    if (Y) {						//  copy only valid source Vectors
                        for (unsigned i = 0; i < D; i++) x[i] = Y[i];	//  copy the elements
                        own = true; }
                        return *this;
                }

//------------  important non-member functions for class Vector

                template <unsigned D> ostream &operator << (ostream &o, const Vector<D> &v) {	//  Vector: output operator
                    o << "<";						//  might want to use other brackets one day
                    for (unsigned i = 0; i < v.dimension ()-1; i++)
                        o << v[i] << ",";
                    o << v[v.dimension ()-1] << ">";
                    return o;
                }

                template <unsigned D> istream &operator >> (istream &i, Vector<D> &v) {
                    for (unsigned j = 0; j < v.dimension (); j++)
                        i >> v[j];						//  how about brackets?

                    return i;
                }

                template <unsigned D> Vector<D> cross (const Vector<D> &a, const Vector<D> &b) {	//  cross product of two 3D Vectors
                    if (a.dimension () != b.dimension ()) {
                        cerr << "dimensions must be equal for cross product!" << endl;
                        abort(); }
                        if (a.dimension () < 3) {
                            cerr << "cross product for dimension < 3 is not defined." << endl;
                            abort(); }
                            if (a.dimension () > 3) {
                                cerr << "cross product for dimension > 3 not yet implemented, sorry." << endl;
                                abort(); }

                                Vector<D> c ();
  
                                c[0] = a[1]*b[2]-b[1]*a[2];
                                c[1] = a[2]*b[0]-b[2]*a[0];
                                c[0] = a[0]*b[1]-b[0]*a[1];
  
                                return c;
                }


/*******************************************************************************
                *  normalizes a 3-Vector out-of-place
                *  @param x	Vector to be normalized
                *  @return	its normalized value
 */
                template <unsigned D> Vector<D> vnormalize (Vector<D> x) {
                    static Vector<D> n;
                    double norm = 0;
                    for (unsigned i = 0; i < D; i++) norm += x[i]*x[i];

                    if (norm == 0) return x;
    
                    norm = sqrt(norm);
                    for (unsigned i = 0; i < D; i++) n[i] = x[i]/norm;
                    return n;
                }


#endif                                                //  VECTOR_H
