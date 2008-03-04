
//      project:      hyperspace explorer
//      module:       4DMenu.C
//      contains:     menu definitions unique to this application (functions,
//		      4D manipulations, the like)
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include "4DView.H"
#include "Menu4D.H"

#include "Function.H"
#include "Surface.H"
#include "Object.H"
#include "ComplexFunction.H"

#include <qmessagebox.h>

#include <sstream>
#include <iomanip>

#define TESTFEATURES 1
//#undef TESTFEATURES

using std::ostringstream;
using std::cerr;
using std::endl;
using std::ends;

using VecMath::Vector;

