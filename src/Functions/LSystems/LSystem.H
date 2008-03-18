
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with:
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if(!defined LSYSTEM_H)
#define LSYSTEM_H

#include <string>
#include <map>

using namespace std;

/** An experimental class to display Lindenmayer Systems (LSystems)
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class LSystem {
public:
  LSystem (unsigned = 2);
  LSystem (string, map<string, string>, unsigned = 2);
  virtual ~LSystem ();

  void level (unsigned n) { m_level = n; }
  unsigned level () { return m_level; }

  void axiom (string a) { m_axiom = a; }
  string axiom () { return m_axiom; }

  void set_rule (string key, string rule) { m_rules[key] = rule; }
  void rules (map<string, string> rules) {m_rules = rules; }
  map<string, string> rules (void)  { return m_rules; }

  void angle (double angle) { m_angle = angle; }
  double angle () { return m_angle; }

  void object (string key, string object) { m_object[key] = object; }
  void object (map<string, string> object);
  map<string, string> object () { return m_object; }
  string object (string key) { return m_object[key]; }

  virtual string Expand ();

  virtual string POV_Source ();
  virtual void Draw () { throw "nyi!"; }

protected:
  string POV_Header (const string &);
  string POV_Footer (const Vector &, const Vector &);
  virtual string POV_Atom (const string &, const string &);	//  one element of the l-system, pov-style

  virtual string Expand (string, unsigned);

  string m_axiom;
  map<string, string> m_rules;
  unsigned m_level;
  double m_scale;
  double m_angle;
  map<string, string> m_object;
};

//  functions defined in LSys_aux.C

string str_replace (string, string, string);
string str_replace (string, map<string, string>);
string matrix_outstr (matrix<3> M);
string vector_outstr (const Vector &V);
string dtos (const double &);
void state_push (vector<matrix<3> >&, const matrix<3>&,
		 vector<Vector>&, const Vector &,
		 vector<string>&, const string &,
		 vector<double>&, const double &);
void state_pop (vector<matrix<3> >&, matrix<3>&,
		 vector<Vector>&, Vector &,
		 vector<string>&, string &,
		 vector<double>&, double &);
void read_file (const string &, unsigned &, string &, map<string, string> &, map<string, string> &);
void help (const string &);



#endif
