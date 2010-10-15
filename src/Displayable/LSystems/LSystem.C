
//      project:      hyperspace explorer
//      module:       LSystem.C
//      contains:     parsing and display of l-systems
//		      currently this module is NOT part of the hyperspace
//		      explorer, but very preliminary code in earliest develop-
//		      ment stage
//      compile with: g++ -I.. LSystem.C LSys_aux.C numclass.C -o LSystem
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)



#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

#include "../Matrix.H"
#include "LSystem.H"


///////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  default LSystem constructor
 */
LSystem::LSystem (unsigned l):
  m_axiom ("X"),  m_level (l),  m_scale (1.0),  m_angle (90.)
{
  m_rules["X"] = "^<XF^<XFX-F^>>XFX&F+>>XFX-F>X->";
  m_object["default"] = "sphere { 0, 0.5 }";
}		

/*******************************************************************************
 *  LSystem constructor taking an axiom and a map of rules
 */
LSystem::LSystem (string axiom, map<string, string> rules, unsigned level):
  m_axiom (axiom), m_rules (rules), m_level (level), m_scale (1.0), m_angle (90.)
{
  m_object["default"] = "sphere { 0, 0.5 }";
/*    
  map<string, string>::iterator i = m_object.begin ();
  while (i != m_object.end ()) {
    cerr << "//           " << i->first << " -> \"" << i->second << "\"" << endl;
    i++;
  }
  exit (0);
  */
}

/*******************************************************************************
 *  generic LSystem destructor
 */
LSystem::~LSystem () {
}


/*******************************************************************************
 *  fill up the object list (doesn't destroy any keys which are not in the input
 *  list)
 */
void LSystem::object (map<string, string> object) {   
  map<string, string>::iterator i = object.begin ();
  while (i != object.end ()) {
    m_object[i->first] = i->second;
    i++;
  } 
}

  
/*******************************************************************************
 *  
 */
string LSystem::Expand (string axiom, unsigned l) {
  if (l > 0) {
    if (m_rules.size () > 0) {
      m_scale /= sqrt (2.0);
     axiom = Expand (str_replace (axiom, m_rules), l-1);
    }
  } 
  return axiom;
}

  
/*******************************************************************************
 *  
 */
string LSystem::Expand () {
  return Expand (m_axiom, m_level);
}


/*******************************************************************************
 *  
 */
string LSystem::POV_Source () {
  ostringstream out;

  string templ = Expand ();		//  the full expansion of the axiom under the current level

  matrix<3> R,				//  current rotation state
    Rx  (2, 1,  m_angle),			//  positive right angle in x direction
    R_x (2, 1, -m_angle),			//  negative right angle in x direction
    Ry  (0, 2,  m_angle),			//	y
    R_y (0, 2, -m_angle),
    Rz  (1, 0,  m_angle),			//	z
    R_z (1, 0, -m_angle);
  
  Vector x (3, 0., 0., 0.),		//  current translation state
    xmin (3, 0., 0., 0.),		//  minumum xlation ever
    xmax (3, 0., 0., 0.);		//  maximum (used for scaling the image)
  const Vector ux (3, 1., 0., 0.);	//  unity vector in x direction

  string rotate = "";			//  stores the rotation values as a POV-ray readable string

  vector<matrix<3> > Rstate;
  vector<Vector> xstate;
  vector<string> rotatestate;
  vector<double> scalestate;
  
  out << POV_Header (templ);		//  write pov header (coordinate cross, some infos)

  out << "union {\n";

  //  parse the expanded lsystem string
  for (unsigned pos = 0; pos < templ.size (); pos++) {
    if (templ[pos] >= 'G' && templ[pos] <= 'Z') {       //  > 'F', small letters nyi 
      ostringstream o;
      o << "      " << rotate << endl
	<< "      translate " << vector_outstr (x) << endl
	<< "      scale " << m_scale << endl;
      out << POV_Atom (templ.substr (pos, 1), o.str ());
#     ifdef DEBUG
        cerr << "OBJECT" << endl;
#     endif
    }
    else {
      switch (templ[pos]) {
      case 'F': x += R*ux;
#               ifdef DEBUG
                  cerr << "F" << endl;
#	        endif
                break;
      case 'B': x -= R*ux;
#               ifdef DEBUG
                  cerr << "B" << endl;
#	        endif		
                break;
              
      case '+': R =  R*Rx;
                rotate = "rotate "+dtos (m_angle)+"*x "+rotate;
#               ifdef DEBUG
	          cerr << "+" << endl;
#	        endif		
                break;
      case '-': R = R*R_x; 
                rotate = "rotate -"+dtos (m_angle)+"*x "+rotate;
#               ifdef DEBUG
	          cerr << "-" << endl;
#	        endif		
                break;
              
      case '^': R =  R*Ry; 
                rotate = "rotate "+dtos (m_angle)+"*y "+rotate;
#               ifdef DEBUG
	          cerr << "^" << endl;
#	        endif		
                break;
      case '&': R = R*R_y; 
                rotate = "rotate -"+dtos (m_angle)+"*y "+rotate;
#               ifdef DEBUG
	          cerr << "&" << endl;
#	        endif		
                break;
              
      case '<': R =  R*Rz; 
                rotate = "rotate "+dtos (m_angle)+"*z "+rotate;
#               ifdef DEBUG
	          cerr << "<" << endl;
#	        endif		
                break;
      case '>': R = R*R_z; 
                rotate = "rotate -"+dtos (m_angle)+"*z "+rotate;
#               ifdef DEBUG
	          cerr << ">" << endl;
#	        endif		
                break;
              
      case '{': state_push (Rstate, R, xstate, x, rotatestate, rotate,
  			    scalestate, m_scale);
#               ifdef DEBUG
	          cerr << "}" << endl;
#	        endif		
	        break;
      case '}': state_pop (Rstate, R, xstate, x, rotatestate, rotate,
			   scalestate, m_scale);
#               ifdef DEBUG
  	          cerr << "}" << endl;
#	        endif		
	        break;
              
    //        scaling
      case 's': { string num = "";
                  while (isdigit (templ[++pos]) ||
	 	         templ[pos] == '.') {
		    num += templ[pos];
		  }
		  pos--;
		  m_scale *= atof (num.c_str ());

#                 ifdef DEBUG
		    cerr << m_scale << endl;
#	          endif		
                }
                break;

      case '@': { string num = "";
                  while (isdigit (templ[++pos]) ||
	 	         templ[pos] == '.') {
		    num += templ[pos];
		  }
		  pos--;
		  m_angle = atof (num.c_str ());
		  Rx  = matrix<3> (2, 1,  m_angle);
		  R_x = matrix<3> (2, 1, -m_angle);
		  Ry  = matrix<3> (0, 2,  m_angle);
		  R_y = matrix<3> (0, 2, -m_angle);
		  Rz  = matrix<3> (1, 0,  m_angle);
		  R_z = matrix<3> (1, 0, -m_angle);

#                ifdef DEBUG
		   cerr << m_angle << endl;
#	         endif
                }
                break;
      case ' ': break;			//  spaces as delimiters are always allowed
      default:
                out << "//  invalid character: \"" << templ[pos] << "\"" << endl;
#               ifdef DEBUG
                  cerr << templ[pos] << endl;
#	        endif
      }      
#     ifdef DEBUG
        cerr << R.Print () << "R*ux = " << vector_outstr (R*ux)
	     << "\tx = " << vector_outstr (x) << endl;
#     endif
    }
      
    for (int i = 0; i < 3; i++) {
      if (x[i] > xmax[i]) xmax[i] = x[i];
      if (x[i] < xmin[i]) xmin[i] = x[i];
    }
  }

  out << "}\n";
  
  out << POV_Footer (xmin, xmax);
  
  return out.str ();
}


/*******************************************************************************
 *  
 */
string LSystem::POV_Header (const string &expanded) {
  ostringstream out;
  out   << "//    level: " << m_level << endl
        << "//    axiom: " << m_axiom << endl
        << "//    rules: " << endl;
  map<string, string>::iterator i = m_rules.begin ();
  while (i != m_rules.end ()) {
    out << "//           " << i->first << " -> \"" << i->second << "\"" << endl;
    i++;
  }
  out   << "//   result: " << expanded << endl;
  out   << "//  objects: " << endl;
  i = m_object.begin ();
  while (i != m_object.end ()) {
    out << "//           " << i->first << " -> \"" << i->second << "\"" << endl;       
    i++;
  }
       
  out   << endl
         << "#default { pigment { rgb 1 } }\n\n";
         
  return out.str ();         
}


/*******************************************************************************
 *  
 */
string LSystem::POV_Footer (const Vector &xmin, const Vector &xmax) {
  ostringstream out;
  out << "cylinder { -2*x, 2*x, 0.02 pigment { color rgb <1, 0, 0> } }\n"
      << "cone { 2*x, .05, 2.2*x, 0 pigment { color rgb <1, 0, 0> } }\n"
      << "cylinder { -2*y, 2*y, 0.02 pigment { color rgb <0, 1, 0> } }\n"
      << "cone { 2*y, .05, 2.2*y, 0 pigment { color rgb <0, 1, 0> } }\n"
      << "cylinder { -2*z, 2*z, 0.02 pigment { color rgb <0, 0, 1> } }\n"
      << "cone { 2*z, .05, 2.2*z, 0 pigment { color rgb <0, 0, 1> } }\n\n"

      << "camera {\n  location <4,1,2.4> direction <0,1,0> right x*5/4 up y "
//       << "look_at "<< ((xmax+xmin)*(m_scale/2.0))                    //  vector addition no workee! check!
      << "look_at 0"
      <<"\n}\n"
       
      << "light_source { <200,500,100> color rgb 1 }\n"
      << "light_source { <6, 2, 3> color rgb 0.9 }";
      
      return out.str ();
}


/*******************************************************************************
 *  
 */
string LSystem::POV_Atom (const string &key, const string &transform) {
  ostringstream out;
  out << "  object {\n";
  
  if (!m_object[key].empty ())
    out << "    " << m_object[key] << endl;
  else
    out << "    " << m_object["default"] << endl;
//    out << "    " << "sphere { 0, 0.5 }" << endl;
    
  out << "    transform {\n"
      << transform << "\n"
      << "    }\n"
      << "  }\n" << endl;
  
//  cerr << key << endl << out.str () << endl;
  
  return out.str ();
}

////////////////////////////////////////////////////////////////////////////////

void test_rotmat ();

/*******************************************************************************
 *  
 */
int main (unsigned argc, char *argv[]) {
  
  unsigned level = 2;
  string axiom = "X";
  map<string, string> object;
  map<string, string> rules;
  rules["X"] = "{^FX}{&FX}{>FX}{<FX}{+FX}{-FX} ";

  for (unsigned i = 1; i < argc; i++) {
    if (string (argv[i]) == "-l" || string (argv[i]) == "--level")
      level = atoi (argv[++i]);
    else if (string (argv[i]) == "-a" || string (argv[i]) == "--axiom")
      axiom = argv[++i];
    else if (string (argv[i]) == "-r" || string (argv[i]) == "--rule")
      rules["X"] = argv[++i];
    else if (string (argv[i]) == "-o" || string (argv[i]) == "--object")
      object["X"] = argv[++i];
    else if (string (argv[i]) == "-f" || string (argv[i]) == "--file") 
      read_file (argv[++i], level, axiom, rules, object);
    else if (string (argv[i]) == "-t" || string (argv[i]) == "--test") {
      test_rotmat ();
    }
    else {
      help (argv[0]);
      return 0;
    }
	      
  }
    
  LSystem lsys (axiom, rules, level);
  if (!object.empty()) lsys.object (object);

  cout << lsys.POV_Source () << endl;

  return 0;
}

