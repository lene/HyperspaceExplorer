
//      project:      hyperspace explorer
//      module:       Globals.C
//      contains:     definitions of global variables and functions
//      compile with: make all
//      author:       helge preuss (scout@hyperspace-travel.de)
//      license:      GPL (see License.txt)

#include <qstring.h>
#include <fstream>
#include <sstream>

#include <QApplication>
#include <QAction>
#include <QMainWindow>

#include "Globals.H"

#include "Vector.H"

using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::ostringstream;
using std::ends;

using VecMath::Vector;


bool Global::check_memory = false;
Color Global::White( 1.0, 1.0, 1.0, 1.0 );
Color Global::Grey50( 0.5, 0.5, 0.5, 1.0 );
Color Global::background(0.1, 0.1, 0.1, 1.0);
Color Global::fog_color(0.2, 0.2, 0.2, 1.0);

Global::Global():
    SR3(sqrt(3.)),
    mainWindow(new QMainWindow),
    quitAction(new QAction(QObject::tr("&Quit"), NULL)) {
    quitAction->setShortcut(QObject::tr("Ctrl+Q"));
    QObject::connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

/** debug function for OpenGL commands; outputs all current GL errors on cerr
 *  @param op optional repetition of last GL command                          */
void Global::CheckGLErrors (const char *
#ifdef DEBUG
    op
#endif
                           ) {
#   ifdef DEBUG
    GLenum error;
    while ((error = glGetError ()) != GL_NO_ERROR)
      cerr << "GL Err: " << op << ": " << gluErrorString (error) << endl;
#   endif
}

/** find the ID of the first free GL list
 *  @return	first freee GL list                                           */
int Global::GetGLList() {
    int MyList = 1;

    //	find a free GL list
    while (glIsList (MyList) == GL_TRUE) MyList++;

    return MyList;
}

/** makes a double precision value from a QString
 *  implemented because I called a function atod () ages ago, for convenience
 *  @param s	string to be converted
 *  @return	its numerical value                                           */
double Global::atod (QString s) {
  return s.toDouble ();
}

/** makes a string  from an integer value
 *  implemented because I called a function itoa () ages ago, for convenience
 *  @param x	number to be converted
 *  @return	its string representation                                     */
string Global::itoa (int x) {
	ostringstream o;
	o << x << ends;
	return o.str ();
}

/** makes a string  from a double value
 *  implemented because I called a function ftoa () ages ago, for convenience
 *  @param x	number to be converted
 *  @return	its string representation                                     */
string Global::ftoa (double x) {
    ostringstream o;
    o << x << ends;
    return o.str ();
}

/** normalizes a Vector made from 3 doubles out-of-place
 *  @param xx	x component of Vector to be normalized
 *  @param yy	y component of Vector to be normalized
 *  @param zz	z component of Vector to be normalized
 *  @return	normalized Vector                                             */
Vector<3> Global::vnormalize (double xx, double yy, double zz) {
    static Vector<3> x;

    x[0] = xx; x[1] = yy; x[2] = zz;
    return VecMath::vnormalize(x);
}

/** get the system memory from /proc/meminfo
 *  of course, this only works on OS's with /proc filesystem and /proc/meminfo
 *  information!
 *  relies on /proc/meminfo of being of the format:
 *  MemTotal:       506912 kB
 *  ...
 *  returns 512 MB as default memory size, when /proc/meminfo is not present
 *  @return	total memory size, or 512 MB                                  */
unsigned long Global::check_proc_meminfo () {
    ifstream in ("/proc/meminfo");
    if (!in) {
        cerr << "no /proc/meminfo - setting Memory limit of 512 MB" << endl;
        check_memory = false;
        return 512*1024*1024;
    }
    string meminfo;
    in >> meminfo;
    in >> meminfo;
    check_memory = true;
    return strtoul (meminfo.c_str (), NULL, 10)*1024;
}

/** maximum memory that should be consumed; calls check_proc_meminfo () above */
unsigned long Global::MaximumMemory = check_proc_meminfo ();
