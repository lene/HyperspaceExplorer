
//      project:      hyperspace explorer
//      module:       numclass.H
//      contains:     class definitions for class Vector
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#ifndef NUMCLASS_H
#define NUMCLASS_H 1

#include <iostream>
#include <stdarg.h>
#include <string>

using namespace std;

# if (!defined __PI)
#   include <cmath>
    const double pi = 4.*atan (1.);
#   define __PI 3_14
# endif

class Vector {
  public:

    //----------  management  ----------

    //  constructor: given a pointer to double, interprets it as n-dimensional vector 
    //  defaults are n = Vector::DefaultDim, A = 0; they are set in the implementation,
    //  because they must be defined after Vector::DefaultDim
    Vector (unsigned n, double *A); 
    Vector (unsigned n, double, ... );         

    ~Vector (void);                                   //  destructor

    //  copy constructor: makes a deep copy, if deep == true, else a shallow one
    Vector (const Vector &X, bool deep = true);

    Vector &operator= (const Vector &Y);              // assignment operator

    static unsigned GetDefaultDim (void);
    static void SetDefaultDim (unsigned d);

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

    Vector &operator+= (const Vector &Y);
    Vector &operator-= (const Vector &Y);
    Vector &operator*= (const double &s);

    Vector operator- (void) const;
    Vector operator+ (const Vector &Y);
    Vector operator- (const Vector &Y);
    Vector operator* (const double &s);
    double operator* (const Vector &X);
    Vector operator/ (const double &s);

    bool operator== (const Vector &Y);
    bool operator!= (const Vector &Y);

    double sqnorm (void);
    double norm (void);
    Vector normalize (void);

    double *data () { return x; }

  private:
    static unsigned DefaultDim; 

    unsigned dim;
    double *x; 
    bool own; };
 
ostream &operator << (ostream &, const Vector &);
istream &operator >> (istream &, Vector &);

Vector cross (const Vector &, const Vector &);




//------------  Vector member functions

    //  ------------  management  ------------

inline Vector::Vector (unsigned n = Vector::DefaultDim, double *A = 0): 
    dim (n), x (A ? A : new double [n]), own (A? false: true) { } //  implicitly initialized to zero vector
  
inline Vector::~Vector (void) { if (own) delete [] x; }
  
    //----------  validity    ----------     

inline Vector::operator bool  (void) const { return  dim; }
inline bool Vector::operator! (void) const { return !dim; }

inline void Vector::invalidate (void) {
  if (own) delete [] x;
  x = 0;
  dim = 0; }

    //----------  access      ----------

inline double &Vector::operator[] (unsigned i) { 
  return x[i]; }                                                  //  no boundary checking!

inline double Vector::operator[] (unsigned i) const { 
  return x[i]; }                                                  //  -''- !
                                                                  //  valgrind: "Use of uninitialised value of size 8"
                                                                  //  at Vector::operator[](unsigned int) const (numclass.H:128)

inline unsigned Vector::dimension (void) const { return dim; }

inline unsigned Vector::GetDefaultDim (void) { return DefaultDim; }
inline void Vector::SetDefaultDim (unsigned d) { DefaultDim = d; }


    //----------  arithmetics ----------

inline Vector &Vector::operator+= (const Vector &Y) {
  for (unsigned i = 0; i < dim; i++) x[i] += Y.x[i] ; 
  return *this; }

inline Vector &Vector::operator-= (const Vector &Y) {
  for (unsigned i = 0; i < dim; i++) x[i] -= Y.x[i] ; 
  return *this; }

inline Vector &Vector::operator*= (const double &s) {             //  scalar multiplication
  for (unsigned i = 0; i < dim; i++) x[i] *= s ;
  return *this; }

inline Vector Vector::operator- (void) const {
  static Vector Z;
  Z = *this;
  for (unsigned i = 0; i < dim; i++) Z.x[i] = -x[i] ; 
  return Z; }

inline Vector Vector::operator+ (const Vector &Y) {
  static Vector Z;
  Z = *this;
  return (Z += Y); }

inline Vector Vector::operator- (const Vector &Y) {
  static Vector Z;
  Z = *this;
  return (Z -= Y); }

inline Vector Vector::operator* (const double &s) {               //  scalar multiplication
  /*static*/ Vector Z;
  Z = *this;
  return Z *= s; }

inline double Vector::operator* (const Vector &Y) {               //  dot product
  double dot = 0.;
  for (unsigned i = 0; i < dim; i++)
    if (x[i]) dot += x[i]*Y.x[i];				  //  valgrind barks "Use of uninitialised value of size 8"
				                                  //  at Vector::operator*(Vector const &) (numclass.H:174)
  return dot; }

inline Vector Vector::operator/ (const double &s) {               //  scalar multiplication
  return operator* (1./s); }

inline bool Vector::operator== (const Vector &Y) {
  for (unsigned i = 0; i < dim; i++) 
    if (x[i] != Y.x[i]) return false;
  return true; }

inline bool Vector::operator!= (const Vector &Y) {
  return !operator== (Y); }

inline double Vector::sqnorm (void) {
  return operator* (*this); }

inline double Vector::norm (void) {
    return sqrt (sqnorm ()); }

inline Vector Vector::normalize (void) {
  double n = norm ();
  if (n > 0.) return operator* (1./sqrt (n));
  else return *this; }


#endif                                                //  NUMCLASS_H
