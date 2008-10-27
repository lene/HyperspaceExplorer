
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


/*
        module: numclass.cc
	compile with: make libnum.so
	memberfunctions for mathematical concepts
*/

#ifndef NUMCLASS_CC
#define NUMCLASS_CC 1

#include "numclass.H"


//------------  Vector member functions and static variable initialization

unsigned Vector::DefaultDim = 4;			//  initialize Vector::DefaultDim

    //----------  management  ----------

Vector::Vector (const unsigned n, double x0, ... ) :	//  Vector:: constructor with variable arglist
    dim (n), x (new double [n]), own (true) {
  x[0] = x0;
  unsigned i = 0;
  va_list argp;
  va_start (argp, x0);
  for (i = 1; i < n; i++) { 
    x[i] = va_arg (argp, double); }
  va_end (argp); }

Vector::Vector (const Vector &X, bool deep) :		//  Vector:: copy constructor
    dim (X.dim), own (deep) {
  if (deep) {						//  deep copy
    x = new double [X.dim]; 
    for (unsigned i = 0; i < dim; i++) x[i] = X[i]; }
  else							//  shallow copy
    x = X.x; }

Vector &Vector::operator= (const Vector &Y) {
  if (dim != Y.dimension ()) {
    invalidate ();					//  free memory 
    dim = Y.dimension ();
    x = new double [dim]; }

  if (Y) {						//  copy only valid source Vectors
    for (unsigned i = 0; i < dim; i++) x[i] = Y[i];	//  copy the elements
    own = true; } 
  return *this; }

//------------  important non-member functions for class Vector

ostream &operator << (ostream &o, const Vector &v) {	//  Vector: output operator
  o << "<";						//  might want to use other brackets one day
  for (unsigned i = 0; i < v.dimension ()-1; i++)
    o << v[i] << ",";
  o << v[v.dimension ()-1] << ">"; 
  return o; }

istream &operator >> (istream &i, Vector &v) {
  for (unsigned j = 0; j < v.dimension (); j++)
    i >> v[j];						//  how about brackets?

  return i; }

Vector cross (const Vector &a, const Vector &b) {	//  cross product of two 3D Vectors
  if (a.dimension () != b.dimension ()) {
    cerr << "dimensions must be equal for cross product!" << endl;
    abort(); }
  if (a.dimension () < 3) {
    cerr << "cross product for dimension < 3 is not defined." << endl;
    abort(); }
  if (a.dimension () > 3) {
    cerr << "cross product for dimension > 3 not yet implemented, sorry." << endl;
    abort(); }

  Vector c (a.dimension ());
  
  c[0] = a[1]*b[2]-b[1]*a[2];
  c[1] = a[2]*b[0]-b[2]*a[0];
  c[0] = a[0]*b[1]-b[0]*a[1];
  
  return c; }


#endif                                                   //  NUMCLASS_CC
