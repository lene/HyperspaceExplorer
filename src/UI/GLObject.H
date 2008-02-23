
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


 ////////////////////////////////////////////////////////////////////////////
//  class GLObject:                                                       //
//  abstract base class for 3D objects. provides a glList containing the    //
//  base primitive and a routine to draw it.                                //
//  the Draw () routine must be implemented in the derived classes.         //
 ////////////////////////////////////////////////////////////////////////////

#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <GL/gl.h>
#include <cstdarg>

#include <vector>

class GLObject {
  public:
    GLObject (GLuint objlist = 0): List () {
      if (glIsList (objlist)) List.push_back (objlist); }

    GLObject (unsigned elements, GLuint objlist, ...): List () {
#     ifdef __DEBUG__
        cerr << "    GLObject (" << elements << ", ";
#     endif
      if (glIsList (objlist)) {
#       ifdef __DEBUG__
	  cerr << objlist << ", ";
#       endif
	List.push_back (objlist); }
#     ifdef __DEBUG__
        else cerr << objlist << " not a GL list ";
#     endif
 
      va_list argp;
      va_start (argp, objlist);

      for (unsigned i = 1; i < elements; i++) {
	objlist = va_arg (argp, GLuint); 

	if (glIsList (objlist)) {
#         ifdef __DEBUG__
	    cerr << objlist << ", ";
#         endif
	  List.push_back (objlist); }

#       ifdef __DEBUG__
          else cerr << objlist << " not a GL list ";
#       endif
      }

#     ifdef __DEBUG__
        cerr << ")"<< endl;
#     endif

      va_end (argp); }


    virtual ~GLObject (void) {
      for (unsigned i = 0; i < List.size (); i++) {
	if (glIsList (List[i])) glDeleteLists (List[i], 1); } }

    virtual unsigned Draw (void) {
#     ifdef __DEBUG__
        cerr << "GLObject::Draw (";
#     endif      

      for (unsigned i = 0; i < List.size (); i++) {
#       ifdef __DEBUG__
	  cerr << List[i] << ", ";
#       endif
	glCallList (List[i]); }
#     ifdef __DEBUG__
        cerr << ")" << endl;
#     endif

      return 0; }

    operator bool () { 
      if (List.empty ()) return false;
      for (unsigned i = 0; i < List.size (); i++)
	if (glIsList (List[i])) return true;
      return false; }

  protected:
    std::vector<GLuint> List;
};
#endif
