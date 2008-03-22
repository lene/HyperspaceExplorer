
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
 *  namespace. \n
 *  I plan to advance this class to a full-blown registry though. One day. \n
 *  Members are accessed with the SingletonHolder static function, i.e.
 *  Globals::Instance().
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class Global {
    public:
        Global();

        static bool check_memory;
        /** sqrt (3), stored to save computation time, probably superfluous   */
        static double SR3;
        /** global (YUCK!) alpha value for transparent display                */
        static double ALPHA;
        /** global (YUCK!) shininess value                                    */
        static double SHININESS;
        /** global (YUCK!) fog/depth cue color                                */
        static float fog_color[4];
        /** color definition for White                                        */
        static float White[4];
        /** color definition for Grey                                         */
        static float grey50[4];
        static float background[4];

        static unsigned long MaximumMemory;
        /** why tf did i make that global again? damn, i really should write
         *  comments immediately after writing the code</rant>                */
        QStringList rcdirs;

        QAction *getQuitAction() const { return quitAction; }
        QMainWindow *getMainWindow() const { return mainWindow; }

        int GetGLList();

        void SetColor(float R, float G, float B);
        void SetColor (const VecMath::Vector<4> &RGB);

        float *BackgroundColor() { return background; }
        void setBackground(float r, float g, float b, float a = 1.0) {
            background[0] = r;
            background[1] = g;
            background[2] = b;
            background[3] = a;
        }

        float *FogColor() { return fog_color; }
        void setFogColor(float r, float g, float b, float a = 1.0) {
            fog_color[0] = r;
            fog_color[1] = g;
            fog_color[2] = b;
            fog_color[3] = a;
        }

        double atod (QString);

        std::string itoa (int x);
        std::string ftoa (double x);

        void CheckGLErrors (const char *op = 0);

        void Debug (std::string s, std::string h = "") {
            QMessageBox::information (NULL, h.c_str (), s.c_str ());
        }

        void glVertex (VecMath::Vector<3> &V) {
            if (std::isfinite (V.sqnorm ()))
	       glVertex3dv (V.data ());
        }

        VecMath::Vector<3> vnormalize (double xx, double yy, double zz);

        template <typename T> void Swap (T &a, T &b) {
	    T temp (a);
	    a = b;
	    b = temp;
        }
        static unsigned long check_proc_meminfo ();

    private:
        QAction *quitAction;
        QMainWindow *mainWindow;

};

typedef Loki::SingletonHolder<Global> Globals;

#endif // !defined(GLOBALS_H)
