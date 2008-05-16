
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include <cstdarg>

#include "GLObject.H"
#include "Log.H"

GLObject::GLObject (GLuint objlist): List () {
    if (glIsList (objlist)) List.push_back (objlist);
}

GLObject::GLObject (unsigned elements, GLuint objlist, ...): List () {
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
        } else SingletonLog::Instance() << (long)objlist << " not a GL list ";
    }

    SingletonLog::Instance() << ")\n";

    va_end (argp);
}

GLObject::~GLObject (void) {
    for (unsigned i = 0; i < List.size (); i++)
        if (glIsList (List[i])) glDeleteLists (List[i], 1);
}

GLObject::operator bool () {
    if (List.empty ()) return false;
    for (unsigned i = 0; i < List.size (); i++)
        if (glIsList (List[i])) return true;
    return false;
}

unsigned GLObject::doDraw (void) {
    SingletonLog::Instance() << "GLObject::Draw (";

    for (unsigned i = 0; i < List.size (); i++) {
        SingletonLog::Instance() << (long)List[i] << ", ";
        glCallList (List[i]);
    }
    SingletonLog::Instance() << ")\n";

    return 0;
}
