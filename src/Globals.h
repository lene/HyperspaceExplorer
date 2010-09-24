
//      project:      hyperspace explorer
//      module:       Globals.H
//      contains:     declarations for some global auxiliary functions and
//		      variables
//      compile with: make all
//	author:	      helge preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)


#if !defined(GLOBALS_H)
#define GLOBALS_H

#include "SingletonHolder.h"

class Color;

class QAction;
class QMainWindow;
class QStringList;

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
        QStringList &rcdirs();

        /// \return The QAction associated with quitting the application
        QAction *getQuitAction();
        /// \return The main window of the application
        QMainWindow *getMainWindow();


        /// \return The global fog color
        Color &FogColor();
        /// Set the global fog color
        /** \param rgba The new fog color */
        void setFogColor(const Color &rgba);

        /** maximum amount of memory available for use                        */
        static unsigned long getMaxMemory();

        /** color definition for White                                        */
        static Color& white();
        /** color definition for Grey                                         */
        static Color& grey50();

        /** sqrt (3), stored to save computation time, probably superfluous   */
        const double SR3;

        /// \return Whether to check for memory usage
        static bool checkMemory();

    private:

      class Impl;
      Impl *pImpl_;
      
};

typedef Loki::SingletonHolder<Global> Globals;

#endif // !defined(GLOBALS_H)
