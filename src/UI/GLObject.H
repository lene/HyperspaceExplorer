
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <GL/gl.h>
#include <vector>

/** class GLObject:
 *  abstract base class for 3D objects. provides a glList containing the
 *  base primitive and a routine to draw it. \n
 *  the Draw () routine must be implemented in the derived classes.
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
/*
class GLObject {
    public:
        /// initialize a GLObject with a GL List
        GLObject (GLuint objlist = 0);
        /// initialize a GLObject with a variable number of GL Lists
        GLObject (unsigned elements, GLuint objlist, ...);

        /// free all GL Lists managed by this GLObject
        virtual ~GLObject (void);

        /// Template Method to draw all GL Lists managed by this GLObject
        unsigned Draw (void) { return doDraw(); }

        /// true if GLObject contains at least one GL List
        operator bool ();

    private:
        /// implementation for Template Method Draw()
        /** kept virtual and private to separate interface and implementation */
/*        virtual unsigned doDraw();

        std::vector<GLuint> List;
};*/
#endif
