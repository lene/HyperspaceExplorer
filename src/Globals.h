
//      project:      hyperspace explorer
//      module:       Globals.H
//      contains:     declarations for some global auxiliary functions and
//		      variables
//      compile with: make all
//	author:	      helge preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)


#if !defined(GLOBALS_H)
#define GLOBALS_H

#include <string>
#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>

#include <QMessageBox>

#include "Vector.h"
#include "SingletonHolder.h"
#include "Color.h"

class QAction;
class QMainWindow;
class QStringList;
class QString;

/** for an explanation why this two-stage macro expansion generates string
 *  literals from #defines, see
 * http://groups.google.de/group/comp.lang.c/browse_thread/thread/2016d4664fdae3c1/f2873d4f6ef769b9#f2873d4f6ef769b9
 */
#define stringify(X) #X
#define make_str(X) stringify(X)

/** __PRETTY_FUNCTION__ is a gcc extension. For other compilers, redefine it
 *  to print filename and line instead of the function signature.
 */
//#ifndef __PRETTY_FUNCTION__
//#   define __PRETTY_FUNCTION__ (std::string(__FILE__)+std::string(" line //")+Globals::Instance().itoa(__LINE__)).c_str()
//#endif

///  Utility functions
namespace Util {

  /// Print a std::vector on a std::ostream
  /** \param s The ostream to which \p v is sent
  *  \param v The vector to print
  *  \return \p s
  */
  template<typename T> std::ostream& operator<<(std::ostream& s,
                                                std::vector<T> const& v) {
    s << "(";
    copy(v.begin(), v.end(), std::ostream_iterator<T>(s, " "));
    s << ")";
    return s;
  }

  /// Find an element in a vector
  /** \param find_me The element to find in the vector \p v
  *  \param v The vector to search for element \p find_me
  *  \return The \p vector<T>::iterator pointing to the element or \p v.end() if
  *          it is not in \p v
  */
  template <typename T> typename std::vector<T>::iterator find(T find_me, std::vector<T> &v) {
    typename std::vector<T>::iterator i = v.begin();
    while(*i != find_me && i != v.end()) ++i;
    return i;
  }

  int GetGLList();

  void CheckGLErrors (const char *op = 0);

  /** define a GL Vertex from a Vector<3>
  *  @param V the vertex to be defined                                 */
  void glVertex (const VecMath::Vector<3> &V);

  VecMath::Vector<3> vnormalize (double xx, double yy, double zz);

  std::string itoa (int x);
  /// Convert a QString to double
  /** \return The double precision value of the argument */
  double atod (QString);
  /// Convert a string to unsigned
  /** \return The double precision value of the argument */
  double atod (const std::string &);
  /// Convert a string to signed int
  /** \return The integer value of the argument */
  int atoi(const std::string &);
  /// Convert a string to unsigned
  /** \return The unsigned value of the argument */
  unsigned atou(const std::string &);

  std::string ftoa (double x);

  /// A (I hope) Editor-independent repersentation of "²"
  std::string sup2();

  /// A (I hope) Editor-independent repersentation of "³"
  std::string sup3();

}
/// As a workaround to end the embarassing practice of keeping global variables,
/// I have created this class as a singleton. You might also call it a
/// namespace.
/** I plan to advance this class to a full-blown registry though. One day.
 *
 *  Members are accessed with the SingletonHolder static function, i.e.
 *  Globals::Instance().
 *  @author Helge Preuss <lene.preuss@gmail.com>                         */
class Global {
    public:
        Global();

        /** why tf did i make that global again? damn, i really should write
         *  comments immediately after writing the code                       */
        QStringList rcdirs;

        /// \return The QAction associated with quitting the application
        QAction *getQuitAction();
        /// \return The main window of the application
        QMainWindow *getMainWindow();


        /// \return The global fog color
        Color &FogColor() { return fog_color; }
        /// Set the global fog color
        /** \param rgba The new fog color */
        void setFogColor(const Color &rgba) { fog_color = rgba; }

        /** maximum amount of memory available for use                        */
        static unsigned long getMaxMemory() { return MaximumMemory; }

        /** color definition for White                                        */
        static Color& white() { return White; }
        /** color definition for Grey                                         */
        static Color& grey50() { return Grey50; }

        /** sqrt (3), stored to save computation time, probably superfluous   */
        const double SR3;

        /// \return Whether to check for memory usage
        static bool checkMemory() { return check_memory; }

    private:
        /** whether to check for memory usage. this member is set or unset from
        check_proc_meminfo(), depending on the success of that function.  */
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

};

typedef Loki::SingletonHolder<Global> Globals;

#endif // !defined(GLOBALS_H)
