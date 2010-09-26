
//      project:      hyperspace explorer
//      module:       Globals.C
//      contains:     definitions of global variables and functions
//      compile with: make all
//      author:       lene preuss (lene.preuss@gmail.com)
//      license:      GPL (see License.txt)

#include "Globals.h"

#include <QApplication>
#include <QAction>
#include <QMainWindow>
#include <QString>
#include <QStringList>

#include <fstream>
#include <sstream>

#include "Vector.h"
#include "MultiDimensionalVector.impl.h"
#include "Function.h"
#include "Color.h"

using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::ostringstream;
using std::ends;

using VecMath::Vector;
using VecMath::MultiDimensionalVector;

struct Global::Impl {

  Impl(): mainWindow(NULL), quitAction(NULL), rcdirs() { }
 
  /** whether to check for memory usage. this member is set or unset from
   *  check_proc_meminfo(), depending on the success of that function.  
   */
  static bool check_memory;
  static unsigned long check_proc_meminfo ();

  /** global (YUCK!) background color                                   */
//        static Color background;
  /** global (YUCK!) fog/depth cue color                                */
  static Color fog_color;
  /** color definition for White                                        */
  static Color White;
  /** color definition for Grey                                         */
  static Color Grey50;

  /** maximum amount of memory available for use                        */
  static unsigned long MaximumMemory;

  /** main window of the application                                    */
  QMainWindow *mainWindow;
  /** global QAction that quits the program                             */
  QAction *quitAction;

  QStringList rcdirs;
  
};

bool Global::Impl::check_memory = false;
Color Global::Impl::White( 1.0, 1.0, 1.0, 1.0 );
Color Global::Impl::Grey50( 0.5, 0.5, 0.5, 1.0 );
//Color Global::background(0.1, 0.1, 0.1, 1.0);
Color Global::Impl::fog_color(0.2, 0.2, 0.2, 1.0);

Global::Global(): SR3(sqrt(3.)), pImpl_(new Impl) { }

QStringList& Global::rcdirs() { return pImpl_->rcdirs; }

QAction* Global::getQuitAction() {
    if (!pImpl_->quitAction) {
        pImpl_->quitAction = new QAction(QObject::tr("&Quit"), NULL);
        pImpl_->quitAction->setShortcut(QObject::tr("Ctrl+Q"));
        QObject::connect(pImpl_->quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    }
    return pImpl_->quitAction;
}

QMainWindow* Global::getMainWindow() {
    if (!pImpl_->mainWindow) pImpl_->mainWindow = new QMainWindow;
    return pImpl_->mainWindow;
}

/** get the system memory from /proc/meminfo
 *  of course, this only works on OS's with /proc filesystem and /proc/meminfo
 *  information!
 *  relies on /proc/meminfo of being of the format:
 *  MemTotal:       506912 kB
 *  ...
 *  returns 512 MB as default memory size, when /proc/meminfo is not present
 *  @return	total memory size, or 512 MB                                  */
unsigned long Global::Impl::check_proc_meminfo() {
    ifstream in("/proc/meminfo");
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

MultiDimensionalVector< Vector<4>, 2 > toMultiDimensionalVector(const Function::vec4vec2D &v) {

  MultiDimensionalVector< Vector<4>, 2 > temp2D;
  for (Function::vec4vec2D::const_iterator it = v.begin();
       it != v.end(); ++it) {
    MultiDimensionalVector< Vector<4>, 1> temp1D;
    for (Function::vec4vec1D::const_iterator jt = it->begin();
         jt != it->end(); ++jt) {
      temp1D.push_back(*jt);
    }
    temp2D.push_back(temp1D);
  }
  return temp2D;

}

MultiDimensionalVector< Vector<4>, 3 > toMultiDimensionalVector(const Function::vec4vec3D &v) {

  MultiDimensionalVector< Vector<4>, 3 > temp3D;

  for (Function::vec4vec3D::const_iterator it = v.begin(); it != v.end(); ++it) {

    MultiDimensionalVector< Vector<4>, 2 > temp2D;
    for (Function::vec4vec2D::const_iterator jt = it->begin(); jt != it->end(); ++jt) {

      MultiDimensionalVector< Vector<4>, 1> temp1D;
      for (Function::vec4vec1D::const_iterator kt = jt->begin(); kt != jt->end(); ++kt) {
        temp1D.push_back(*kt);
      }

      temp2D.push_back(temp1D);
    }

    temp3D.push_back(temp2D);
  }

  return temp3D;
}

Color& Global::FogColor() { return pImpl_->fog_color; }

void Global::setFogColor(const Color& rgba) { pImpl_->fog_color = rgba; }

long unsigned int Global::getMaxMemory() { return Impl::MaximumMemory; }

Color& Global::white() { return Impl::White; }

Color& Global::grey50() { return Impl::Grey50; }

bool Global::checkMemory() { return Impl::check_memory; }

/** maximum memory that should be consumed; calls check_proc_meminfo () above */
unsigned long Global::Impl::MaximumMemory = Global::Impl::check_proc_meminfo();
