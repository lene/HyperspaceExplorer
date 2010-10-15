
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with:
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if(!defined LSYSTEM_H)
#define LSYSTEM_H

#include "Vector.h"
#include "Matrix.h"

#include <string>
#include <map>
#include <vector>

using namespace std;

typedef VecMath::Vector<3, double> Vector;
using VecMath::Matrix;

/** An experimental class to display Lindenmayer Systems (LSystems)
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class LSystem {
public:
    /// \todo document me
    LSystem (unsigned = 2);
    /// \todo document me
    LSystem (string, map<string, string>, unsigned = 2);
    /// \todo document me
    virtual ~LSystem ();

    /// \todo document me
    void level (unsigned n) { m_level = n; }
    /// \todo document me
    unsigned level () { return m_level; }

    /// \todo document me
    void axiom (string a) { m_axiom = a; }
    /// \todo document me
    string axiom () { return m_axiom; }

    /// \todo document me
    void set_rule (string key, string rule) { m_rules[key] = rule; }
    /// \todo document me
    void rules (map<string, string> rules) {m_rules = rules; }
    /// \todo document me
    map<string, string> rules (void)  { return m_rules; }

    /// \todo document me
    void angle (double angle) { m_angle = angle; }
    /// \todo document me
    double angle () { return m_angle; }

    /// \todo document me
    void object (string key, string object) { m_object[key] = object; }
    /// \todo document me
    void object (map<string, string> object);
    /// \todo document me
    map<string, string> object () { return m_object; }
    /// \todo document me
    string object (string key) { return m_object[key]; }

    /// \todo document me
    virtual string Expand ();

    /// \todo document me
    virtual string POV_Source ();
    /// \todo document me
    virtual void Draw () { throw "nyi!"; }

protected:
    /// \todo document me
    string POV_Header (const string &);
    /// \todo document me
    string POV_Footer (const Vector &, const Vector &);
    /// \todo document me
    virtual string POV_Atom (const string &, const string &);	//  one element of the l-system, pov-style

    /// \todo document me
    virtual string Expand (string, unsigned);

    string m_axiom;                ///< \todo document me
    map<string, string> m_rules;   ///< \todo document me
    unsigned m_level;              ///< \todo document me
    double m_scale;                ///< \todo document me
    double m_angle;                ///< \todo document me
    map<string, string> m_object;  ///< \todo document me
};

//  functions defined in LSys_aux.C

string str_replace (string, string, string);
string str_replace (string, map<string, string>);
string matrix_outstr (Matrix<3> M);
string vector_outstr (const Vector &V);
string dtos (const double &);
void state_push (vector<Matrix<3> >&, const Matrix<3>&,
                 vector<Vector>&, const Vector &,
                 vector<string>&, const string &,
                 vector<double>&, const double &);
void state_pop (vector<Matrix<3> >&, Matrix<3>&,
                 vector<Vector>&, Vector &,
                 vector<string>&, string &,
                 vector<double>&, double &);
void read_file (const string &, unsigned &, string &, map<string, string> &, map<string, string> &);
void help (const string &);
double atof(const char *);
int atoi(const char *);


#endif
