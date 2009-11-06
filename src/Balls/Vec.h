
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

template <unsigned n> class Vec {
  public:

    //----------  management  ----------

    //  constructor: given a pointer to double, interprets it as n-dimensional vector 
    //  defaults are n = Vec::DefaultDim, A = 0; they are set in the implementation,
    //  because they must be defined after Vec::DefaultDim
    Vec (); 
    Vec (double x0, ... ); //  Vec<n>:: constructor with variable arglist
  //    ~Vec (void);                                   //  destructor

    //----------  access      ----------

    //  operator [] returns a reference to component i (no boundary checking!)
    double &operator[] (unsigned i);

    //  operator [] const returns component i (read-only access, no check)
    double operator[] (unsigned i) const;

    unsigned dimension (void) const;

    //----------  arithmetics ----------

    Vec &operator+= (const Vec &Y);
    Vec &operator-= (const Vec &Y);
    Vec &operator*= (const double &s);

    Vec operator- (void) const;
    Vec operator+ (const Vec &Y);
    Vec operator- (const Vec &Y);
    Vec operator* (const double &s);
    double operator* (const Vec &X);
    Vec operator/ (const double &s);

    bool operator== (const Vec &Y);
    bool operator!= (const Vec &Y);

    double sqnorm (void);
    double norm (void);
    Vec normalize (void);

    double *data () { return x; }

  private:
    double x[n]; };
 
template <unsigned n> ostream &operator << (ostream &, const Vec<n> &);
template <unsigned n> istream &operator >> (istream &, Vec<n> &);

template <unsigned n> Vec<n> cross (const Vec<n> &, const Vec<n> &);




//------------  Vec member functions

    //  ------------  management  ------------

template <unsigned n> inline Vec<n>::Vec<n> () { //  implicitly initialized to zero vector
  for (int i = 0; i < n; x[i++] = 0.);
}
  
// template <unsigned n> inline Vec<n>::~Vec<n> (void) { }
  
    //----------  access      ----------

template <unsigned n> inline double &Vec<n>::operator[] (unsigned i) { 
  return x[i]; }                                                  //  no boundary checking!

template <unsigned n> inline double Vec<n>::operator[] (unsigned i) const { 
  return x[i]; }                                                  //  -''- !

template <unsigned n> inline unsigned Vec<n>::dimension (void) const { return n; }

    //----------  arithmetics ----------

template <unsigned n> inline Vec<n> &Vec<n>::operator+= (const Vec<n> &Y) {
  for (unsigned i = 0; i < n; i++) x[i] += Y.x[i] ; 
  return *this; }

template <unsigned n> inline Vec<n> &Vec<n>::operator-= (const Vec<n> &Y) {
  for (unsigned i = 0; i < n; i++) x[i] -= Y.x[i] ; 
  return *this; }

//  scalar multiplication
template <unsigned n> inline Vec<n> &Vec<n>::operator*= (const double &s) {
  for (unsigned i = 0; i < n; i++) x[i] *= s ;
  return *this; }

template <unsigned n> inline Vec<n> Vec<n>::operator- (void) const {
  static Vec<n> Z;
  for (unsigned i = 0; i < n; i++) Z.x[i] = -x[i] ; 
  return Z; }

template <unsigned n> inline Vec<n> Vec<n>::operator+ (const Vec<n> &Y) {
  static Vec<n> Z;
  for (unsigned i = 0; i < n; i++) Z.x[i] = x[i]+Y.x[i];
  return Z; }

template <unsigned n> inline Vec<n> Vec<n>::operator- (const Vec<n> &Y) {
  static Vec<n> Z;
  for (unsigned i = 0; i < n; i++) Z.x[i] = x[i]-Y.x[i];
  return Z;
}

//  scalar multiplication
template <unsigned n> inline Vec<n> Vec<n>::operator* (const double &s) {
  static Vec<n> Z;
  for (unsigned i = 0; i < n; i++) Z.x[i] = x[i]*s;
  return Z;
}

//  dot product
template <unsigned n> inline double Vec<n>::operator* (const Vec<n> &Y) {
  double dot = 0.;
  for (unsigned i = 0; i < n; i++)
    if (x[i]) dot += x[i]*Y.x[i];
  return dot; }

//  scalar multiplication
template <unsigned n> inline Vec<n> Vec<n>::operator/ (const double &s) {
  return operator* (1./s); }

template <unsigned n> inline bool Vec<n>::operator== (const Vec<n> &Y) {
  for (unsigned i = 0; i < n; i++) 
    if (x[i] != Y.x[i]) return false;
  return true; }

template <unsigned n> inline bool Vec<n>::operator!= (const Vec<n> &Y) {
  return !operator== (Y); }

template <unsigned n> inline double Vec<n>::sqnorm (void) {
  return operator* (*this); }

template <unsigned n> inline double Vec<n>::norm (void) {
    return sqrt (sqnorm ()); }

template <unsigned n> inline Vec<n> Vec<n>::normalize (void) {
  double nrm = sqnorm ();
  if (nrm > 0.) return operator* (1./sqrt (nrm));
  else return *this; }

    //----------  management  ----------

//  Vec<n>:: constructor with variable arglist
template <unsigned n> Vec<n>::Vec<n> (double x0, ... ) {
  x[0] = x0;
  unsigned i = 0;
  va_list argp;
  va_start (argp, x0);
  for (i = 1; i < n; i++) { 
    x[i] = va_arg (argp, double); }
  va_end (argp); }

//------------  important non-member functions for class Vec<n>

template <unsigned n> ostream &operator << (ostream &o, const Vec<n> &v) {	//  Vec<n>: output operator
  o << "<";						//  might want to use other brackets one day
  for (unsigned i = 0; i < v.dimension ()-1; i++)
    o << v[i] << ",";
  o << v[v.dimension ()-1] << ">"; 
  return o; }

template <unsigned n> istream &operator >> (istream &i, Vec<n> &v) {
  for (unsigned j = 0; j < v.dimension (); j++)
    i >> v[j];						//  how about brackets?

  return i; }

template <unsigned n> Vec<n> cross (const Vec<n> &a, const Vec<n> &b) {	//  cross product of two 3D Vec<n>s
  if (n < 3) {
    cerr << "cross product for dimension < 3 is not defined." << endl;
    abort(); }
  if (n > 3) {
    cerr << "cross product for dimension > 3 not yet implemented, sorry." << endl;
    abort(); }

  Vec<n> c;
  
  c[0] = a[1]*b[2]-b[1]*a[2];
  c[1] = a[2]*b[0]-b[2]*a[0];
  c[0] = a[0]*b[1]-b[0]*a[1];
  
  return c; }



#endif                                                //  NUMCLASS_H
