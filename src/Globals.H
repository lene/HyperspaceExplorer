
//      project:      hyperspace explorer
//      module:       Globals.H
//      contains:     declarations for some global auxiliary functions and
//		      variables
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(GLOBALS_H)
#define GLOBALS_H

#include <string>
#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>

#include <QMessageBox>

#include "Vector.H"
#include "SingletonHolder.H"
#include "Color.H"

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

/** As a workaround to end the embarassing practice of keeping global variables,
 *  I have created this class as a singleton. You might also call it a
 *  namespace.
 *
 *  I plan to advance this class to a full-blown registry though. One day.
 *
 *  Members are accessed with the SingletonHolder static function, i.e.
 *  Globals::Instance().
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Global {
    public:
        Global();

        /** why tf did i make that global again? damn, i really should write
         *  comments immediately after writing the code</rant>                */
        QStringList rcdirs;

        QAction *getQuitAction() const { return quitAction; }
        QMainWindow *getMainWindow() const { return mainWindow; }

        int GetGLList();

//        Color &BackgroundColor() { return background; }
//        void setBackground(const Color &rgba) { background = rgba; }

        Color &FogColor() { return fog_color; }
        void setFogColor(const Color &rgba) { fog_color = rgba; }

        double atod (QString);
        double atod (const std::string &);
        int atoi(const std::string &);
        unsigned atou(const std::string &);

        std::string itoa (int x);
        std::string ftoa (double x);

        void CheckGLErrors (const char *op = 0);

        /** define a GL Vertex from a Vector<3>
         *  @param V the vertex to be defined                                 */
        void glVertex (VecMath::Vector<3> &V) {
            if (std::isfinite (V.sqnorm()))
               glVertex3dv (V.data());
        }

        VecMath::Vector<3> vnormalize (double xx, double yy, double zz);

        /** maximum amount of memory available for use                        */
        static unsigned long getMaxMemory() { return MaximumMemory; }

        /** color definition for White                                        */
        static Color& white() { return White; }
        /** color definition for Grey                                         */
        static Color& grey50() { return Grey50; }

        /** sqrt (3), stored to save computation time, probably superfluous   */
        const double SR3;

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
