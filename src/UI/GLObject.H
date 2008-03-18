
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <GL/gl.h>
#include <cstdarg>

#include <vector>

#include "Log.H"

/** class GLObject:
 *  abstract base class for 3D objects. provides a glList containing the
 *  base primitive and a routine to draw it. \n
 *  the Draw () routine must be implemented in the derived classes.
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class GLObject {
    public:
        GLObject (GLuint objlist = 0): List () {
            if (glIsList (objlist)) List.push_back (objlist);
        }

        GLObject (unsigned elements, GLuint objlist, ...): List () {
            SingletonLog::Instance() << "    GLObject (" << (long)elements << ", ";
            if (glIsList (objlist)) {
                SingletonLog::Instance() << (long)objlist << ", ";
                List.push_back (objlist);
            } else {
                SingletonLog::Instance() << (long)objlist << " not a GL list ";
            }

            va_list argp;
            va_start (argp, objlist);

            for (unsigned i = 1; i < elements; i++) {
                objlist = va_arg (argp, GLuint);

                if (glIsList (objlist)) {
                    SingletonLog::Instance() << (long)objlist << ", ";
                    List.push_back (objlist);
                }

                else SingletonLog::Instance() << (long)objlist << " not a GL list ";
            }

            SingletonLog::Instance() << ")\n";

            va_end (argp);
        }


        virtual ~GLObject (void) {
            for (unsigned i = 0; i < List.size (); i++)
                if (glIsList (List[i])) glDeleteLists (List[i], 1);
        }

        virtual unsigned Draw (void) {
            SingletonLog::Instance() << "GLObject::Draw (";

            for (unsigned i = 0; i < List.size (); i++) {
                SingletonLog::Instance() << (long)List[i] << ", ";
                glCallList (List[i]);
            }
            SingletonLog::Instance() << ")\n";

            return 0;
        }

        operator bool () {
            if (List.empty ()) return false;
            for (unsigned i = 0; i < List.size (); i++)
                if (glIsList (List[i])) return true;
            return false;
        }

        protected:
            std::vector<GLuint> List;
};
#endif
