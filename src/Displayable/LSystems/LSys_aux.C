
//      project:      hyperspace explorer
//      module:       LSystem.C
//      contains:     parsing and display of l-systems
//		      currently this module is NOT part of the hyperspace
//		      explorer, but very preliminary code in earliest develop-
//		      ment stage
//      compile with: g++ -I. LSystem.C LSys_aux.C numclass.C -o LSystem
//	author:	      lene preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)

#include "LSystem_old.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

#include <QString>

#include "Matrix.impl.h"
#include "Vector.impl.h"

////////////////////////////////////////////////////////////////////////////////
double atof(const char *s) {
  return QString(s).toDouble();
}

int atoi(const char *s) {
  return QString(s).toInt();
}

/*******************************************************************************
 * str_replace
 * searches for every occurrence of pattern in instring and substitutes replacement
 * WARNING: crashee if last occurence of pattern is the last letter in instring
*/
string str_replace (string instring, string pattern, string replacement) {
  unsigned pos = 0;

  while (pos < instring.size ()) {
    pos = instring.find (pattern, pos);

    if (pos >= instring.size ()) return instring;

    instring.replace (pos, pattern.size (), replacement);
    pos += replacement.size () - pattern.size ();
  }

  return instring;
}


/*******************************************************************************
 *
 */
 string map_keys_to_string (map<string, string> rules) {
  string keys = "";
  map<string, string>::iterator i = rules.begin ();
  while (i != rules.end ()) {
    keys += i->first;            //  it would be probably more efficient, but certainly less
    i++;
  }
  return keys;
}


/*******************************************************************************
 * str_replace
 * searches for every occurrence of every pattern in the keys of rules in instring
 * and substitutes the corresponding value in rules
 * WARNING: only works for one-letter patterns
*/
string str_replace (string instring, map<string, string> rules) {
  string keys = map_keys_to_string (rules);
  unsigned pos = 0;

  while (pos < instring.size ()) {
    pos = instring.find_first_of (keys, pos);

    if (pos >= instring.size ()) return instring;

    string replacement = rules[instring.substr (pos,1)];
    instring.replace (pos, 1, replacement);
    pos += replacement.size () - 1;
  }

  return instring;
}


///////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *  converts a vector from right-handed to left-handed coordinates
 */
Vector left_handed (const Vector &V) {
  Vector W (V);
  W[2] = -W[2];
  return W;
}


/*******************************************************************************
 *  converts a matrix from right-handed to left-handed coordinates
 */
Matrix<3> left_handed (const Matrix<3> &M) {
  Matrix<3> N (M), T;
  T(2,2) = -1;				//  to POV-ray's #!?*&ing left-handed coordinates:
                                        //  flip z coordinate
  N = T * N;

  return N;
}


/*******************************************************************************
 *
 */
string vector_outstr (const Vector &V) {
  const double eps = 1e-8;

  //  flip z-coordinate because left/right-handedness issue?
  //  V = left_handed (V);
  ostringstream o;
  o << "< ";
  if (fabs (V[0]) > eps) o << V[0];
  else o << 0;
  o << ", ";
  if (fabs (V[1]) > eps) o << V[1];
  else o << 0;
  o << ", ";
  if (fabs (V[2]) > eps) o << V[2];
  else o << 0;
  o << ">";
  return o.str ();
}


/*******************************************************************************
 *
 */
string matrix_outstr (Matrix<3> M) {
  const double eps = 1e-8;
  ostringstream o;

  o << "      matrix <\n"
    << setw (4) << setprecision (2)
    << "              ";
  if (fabs (M (0, 0)) > eps) o << M(0, 0);
  else o << 0;
  o << ", ";
  if (fabs (M (0, 1)) > eps) o << M(0, 1);
  else o << 0;
  o << ", ";
  if (fabs (M (0, 2)) > eps) o << M(0, 2);
  else o << 0;
  o << ",\n";
  o << "              ";
  if (fabs (M (1, 0)) > eps) o << M(1, 0);
  else o << 0;
  o << ", ";
  if (fabs (M (1, 1)) > eps) o << M(1, 1);
  else o << 0;
  o << ", ";
  if (fabs (M (1, 2)) > eps) o << M(1, 2);
  else o << 0;
  o << ",\n";
  o << "              ";
  if (fabs (M (2, 0)) > eps) o << M(2, 0);
  else o << 0;
  o << ", ";
  if (fabs (M (2, 1)) > eps) o << M(2, 1);
  else o << 0;
  o << ", ";
  if (fabs (M (2, 2)) > eps) o << M(2, 2);
  else o << 0;
  o << ",\n";
  o << "              "
    << "0, 0, 0>\n";

  return o.str ();
}


/*******************************************************************************
 *
 */
string dtos (const double &d){
  ostringstream o;
  o << d;
  return o.str ();
}


/*******************************************************************************
 *
 */
void state_push (vector<Matrix<3> >& Rstate, const Matrix<3>& R,
		 vector<Vector>& xstate, const Vector & x,
		 vector<string>& rotatestate, const string & rotate,
		 vector<double>& scalestate, const double & scale) {
  Rstate.push_back (R);
  xstate.push_back (x);
  rotatestate.push_back (rotate);
  scalestate.push_back (scale);
}


/*******************************************************************************
 *
 */
void state_pop (vector<Matrix<3> >& Rstate, Matrix<3>& R,
		vector<Vector>& xstate, Vector & x,
		vector<string>& rotatestate, string & rotate,
		vector<double>& scalestate, double & scale) {
  R = Rstate.back();
  Rstate.pop_back ();
  x = xstate.back();
  xstate.pop_back ();
  rotate = rotatestate.back();
  rotatestate.pop_back ();
  scale = scalestate.back();
  scalestate.pop_back ();
}


/*******************************************************************************
 *
 */
void split_key_and_value (string &value, map<string, string> &store) {
  unsigned delimiter_pos = value.find_first_of (":");
  string key = "X", tmp = value;
  if (delimiter_pos < value.size ()) {
    key = value.substr (0, delimiter_pos),
    tmp = value.substr (value.find_first_not_of (":", key.size ()));
    key = key.substr (0, 1);            //  make sure only first letter is taken as key
  }
  store[key] = tmp.substr (tmp.find_first_not_of (" \t"));
}


/*******************************************************************************
 *  read the (or some) input parameters from a file
 *  the file lines must have the following syntax:
 *    level ...
 *    axiom ...
 *    rule ...
 *    object ...
 *  no leading whitespace, comments only at the beginning of the line,
 *  every value on one line, or it will go wrong
*/
void read_file (const string &filename,
		unsigned &level, string &axiom, map<string, string> &rules, map<string, string> &object) {
  ifstream in (filename.c_str ());
  string line;
  while (getline (in, line)) {
    if (line.size () <1) continue;
    string keyword = line.substr (0, line.find_first_of (" \t")),
           value = line.substr (line.find_first_not_of (" \t", keyword.size ()));

    if (keyword == "level") level = atoi (value.c_str ());
    else if (keyword == "axiom") axiom = value;
    else if (keyword == "rule") split_key_and_value (value, rules);
    else if (keyword == "object") split_key_and_value (value, object);
    else if (keyword == "RULE") rules["X"] = value;             //  keep backward compatibility
    else if (keyword == "OBJECT") object["X"] = value;          //  to obsolete syntax
    else if (keyword.substr (0,1) == "#" || keyword.substr (0,2) == "//") continue;
    else cerr << "line not recognized: " << line << endl;
  }
}


/*******************************************************************************
 *
 */
void help (const string &program) {
  cerr << "usage:\n"
      << program << "[-l|--level <level>]\n"
      << "           [-a|--axiom <axiom>]\n"
      << "           [-r|--rule <rule>]\n"
      << "           [-o|--object <POV-object>]\n"
      << "  rule syntax:\n"
      << "    X	     set an object and expand rule\n"
      << "    F/B    one step forward/back\n"
      << "    +/-    turn +/- 90 degrees around x\n"
      << "    ^/&    turn +/- 90 degrees around y\n"
      << "    </>    turn +/- 90 degrees around z\n"
      << "    {/}    push/pop current transformation\n"
      << "    s<num> scale following transformations by <num>\n";
}

////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 */
void test_str_replace () {
  string teststr = "XXX";

  cout << teststr << ": X -> XYZ: " << str_replace (teststr, "X", "XYZ") << endl;
  teststr = "X";
  cout << teststr << ": X -> XYZ: " << str_replace (teststr, "X", "XYZ") << endl;
}


/*******************************************************************************
 *
 */
void test_rotmat () {
  Matrix<3> R,
    Rx  (2, 1,  90.),
    R_x (2, 1, -90.),
    Ry  (0, 2,  90.),
    R_y (0, 2, -90.),
    Rz  (1, 0,  90.),
    R_z (1, 0, -90.);
  Vector ux (3, 1., 0., 0.),
    uy (3, 0., 1., 0.),
    uz (3, 0., 0., 1.);

    cerr << "unity:\n " << matrix_outstr (R)
	 << "Rx\n" << matrix_outstr (Rx)
	 << "(Rx) * ux " << vector_outstr ((Rx)*ux) << endl
      	 << "R_x\n" << matrix_outstr (R_x)
	 << "(R_x) * ux " << vector_outstr ((R_x)*ux) << endl
	 << "Ry\n" << matrix_outstr (Ry)
	 << "(Ry) * ux " << vector_outstr ((Ry)*ux) << endl
      	 << "R_y\n" << matrix_outstr (R_y)
	 << "(R_y) * ux " << vector_outstr ((R_y)*ux) << endl
	 << "Rz\n" << matrix_outstr (Rz)
	 << "(Rz) * ux " << vector_outstr ((Rz)*ux) << endl
      	 << "R_z\n" << matrix_outstr (R_z)
	 << "(R_z) * ux " << vector_outstr ((R_z)*ux) << endl
	 << "Rx * Ry\n" << matrix_outstr (Rx*Ry)
	 << "Ry * Rx\n" << matrix_outstr ((Ry*Rx))
	 << "(Rx * Ry) * ux " << vector_outstr ((Rx*Ry)*ux) << endl
	 << "(Ry * Rx) * ux " << vector_outstr ((Ry*Rx)*ux) << endl
	 << "Rx * Rz\n" << matrix_outstr ((Rx*Rz))
	 << "Rz * Rx\n" << matrix_outstr ((Rz*Rx))
	 << "(Rz * Rx) * ux " << vector_outstr ((Rz*Rx)*ux) << endl
	 << "(Rx * Rz) * ux " << vector_outstr ((Rx*Rz)*ux) << endl
	 << "Ry * Rz\n" << matrix_outstr ((Ry*Rz))
	 << "Rz * Ry\n" << matrix_outstr ((Rz*Ry))
	 << "(Rz * Ry) * ux " << vector_outstr ((Rz*Ry)*ux) << endl
	 << "(Ry * Rz) * ux " << vector_outstr ((Ry*Rz)*ux) << endl
      ;
}
