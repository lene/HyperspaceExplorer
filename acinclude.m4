##    -*- shell-script -*-

##    This file is part of the Hyperspace Explorer distribution
##    Based on bits from KDE:
##    Copyright (C) 1997 Janos Farkas (chexum@shadow.banki.hu)
##              (C) 1997 Stephan Kulow (coolo@kde.org)
##    and autoqt by      Geoffrey Wossum (gwossum@acm.org)

##    This file is free software; you can redistribute it and/or
##    modify it under the terms of the GNU Library General Public
##    License as published by the Free Software Foundation; either
##    version 2 of the License, or (at your option) any later version.

##    This library is distributed in the hope that it will be useful,
##    but WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
##    Library General Public License for more details.

##    You should have received a copy of the GNU Library General Public License
##    along with this library; see the file COPYING.LIB.  If not, write to
##    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
##    Boston, MA 02111-1307, USA.        


#   Provides:
#        
#        AC_HAVE_GL
#        gw_CHECK_QT
#        KDE_CHECK_DLOPEN
#        KDE_CHECK_DYNAMIC_LOADING
#        AC_FIND_PNG
#        AC_CHECK_GETDOMAINNAME
#        AC_CHECK_GETHOSTNAME
#        AC_CHECK_USLEEP
#        AC_FIND_GIF
#        AC_FIND_JPEG
#        AC_FIND_ZLIB
        

AC_DEFUN(AC_HAVE_GL,
     [AC_REQUIRE_CPP() dnl

     test -z "$GL_LDFLAGS" && GL_LDFLAGS=
     test -z "$GL_INCLUDE" && GL_INCLUDE=

     AC_ARG_WITH(gl, [  --without-gl            disable 3D GL modes],
	    gl_test=$withval, gl_test="yes")
     if test "x$gl_test" = xno; then
       ac_cv_have_gl=no
     else
       AC_MSG_CHECKING(for GL)
       AC_CACHE_VAL(ac_cv_have_gl,
       [
	AC_LANG_C
	ac_save_ldflags="$LDFLAGS"
	ac_save_cflags="$CFLAGS"
	LDFLAGS="$LDFLAGS $GL_LDFLAGS $all_libraries -lMesaGL -lMesaGLU -lX11 -lXext -lm $LIBSOCKET"
	CFLAGS="$CFLAGS $X_INCLUDES"
	test ! -z "$GL_INCLUDE" && CFLAGS="-I$GL_INCLUDE $CFLAGS"
	AC_TRY_LINK([
        #include <GL/gl.h>
        ],[
	exit (0);
        ],,
	ac_cv_have_gl="yes",ac_cv_have_gl="no")
	LDFLAGS="$ac_save_ldflags"
	CFLAGS="$ac_save_cflags"
       ])dnl

      if test "$ac_cv_have_gl" = no; then
	AC_MSG_RESULT(no)
	GL_LDFLAGS=""
	GLINC=""
	$2
      else
	AC_DEFINE(HAVE_GL)
	if test "$GL_LDFLAGS" = ""; then
	   GLLIB="-lMesaGL -lMesaGLU"
	else
	   GLLIB="-L$GL_LDFLAGS -lMesaGL -lMesaGLU"
	fi
	if test "$GL_INCLUDE" = ""; then
	   GLINC=""
	else
	   GLINC="-I$GL_INCLUDE"
	fi
	AC_MSG_RESULT(yes)
	$1
      fi
     fi
     AC_SUBST(GLINC)
     AC_SUBST(GLLIB)
    ]) 


 
#
#
#
#
#
#
#
# Check for Qt compiler flags, linker flags, and binary packages
AC_DEFUN([gw_CHECK_QT],
[
AC_REQUIRE([AC_PROG_CXX])
AC_REQUIRE([AC_PATH_X])

AC_MSG_CHECKING([QTDIR])
AC_ARG_WITH([qtdir], [  --with-qtdir=DIR        Qt installation directory [default=$QTDIR]], QTDIR=$withval)
# Check that QTDIR is defined or that --with-qtdir given
if test x"$QTDIR" = x ; then
    QT_SEARCH="/usr/lib/qt31 /usr/local/qt31 /usr/lib/qt3 /usr/local/qt3 /usr/lib/qt2 /usr/local/qt2 /usr/lib/qt /usr/local/qt"
    for i in $QT_SEARCH; do
	if test -f $i/include/qglobal.h -a x$QTDIR = x; then QTDIR=$i; fi
    done
fi
if test x"$QTDIR" = x ; then
    AC_MSG_ERROR([*** QTDIR must be defined, or --with-qtdir option given])
fi
AC_MSG_RESULT([$QTDIR])

# Change backslashes in QTDIR to forward slashes to prevent escaping
# problems later on in the build process, mainly for Cygwin build
# environment using MSVC as the compiler
# TODO: Use sed instead of perl
QTDIR=`echo $QTDIR | perl -p -e 's/\\\\/\\//g'`

# Figure out which version of Qt we are using
AC_MSG_CHECKING([Qt version])
QT_VER=`grep 'define.*QT_VERSION_STR\W' $QTDIR/include/qglobal.h | perl -p -e 's/\D//g'`
case "${QT_VER}" in
    2*)
	QT_MAJOR="2"
    ;;
    3*)
	QT_MAJOR="3"
    ;;
    *)
	AC_MSG_ERROR([*** Do not know how to handle this Qt major version])
    ;;
esac
AC_MSG_RESULT([$QT_VER ($QT_MAJOR)])

# Check that moc is in path
AC_CHECK_PROG(MOC, moc, moc)
if test x$MOC = x ; then
	AC_MSG_ERROR([*** moc must be in path])
fi

# uic is the Qt user interface compiler
AC_CHECK_PROG(UIC, uic, uic)
if test x$UIC = x ; then
	AC_MSG_ERROR([*** uic must be in path])
fi

# qembed is the Qt data embedding utility.
# It is located in $QTDIR/tools/qembed, and must be compiled and installed
# manually, we'll let it slide if it isn't present
AC_CHECK_PROG(QEMBED, qembed, qembed)


# Calculate Qt include path
QT_CXXFLAGS="-I$QTDIR/include"

QT_IS_EMBEDDED="no"
# On unix, figure out if we are doing a static or dynamic link
case "${host}" in
	*-cygwin)
	    AC_DEFINE_UNQUOTED(WIN32, "", Defined if on Win32 platform)
	    if test -f "$QTDIR/lib/qt.lib" ; then
		QT_LIB="qt.lib"
		QT_IS_STATIC="yes"
		QT_IS_MT="no"
	    elif test -f "$QTDIR/lib/qt-mt.lib" ; then
		QT_LIB="qt-mt.lib" 
		QT_IS_STATIC="yes"
		QT_IS_MT="yes"
	    elif test -f "$QTDIR/lib/qt$QT_VER.lib" ; then
		QT_LIB="qt$QT_VER.lib"
		QT_IS_STATIC="no"
		QT_IS_MT="no"
	    elif test -f "$QTDIR/lib/qt-mt$QT_VER.lib" ; then
		QT_LIB="qt-mt$QT_VER.lib"
		QT_IS_STATIC="no"
		QT_IS_MT="yes"
	    fi
	    ;;

	*)
	    QT_IS_STATIC=`ls $QTDIR/lib/*.a 2> /dev/null`
	    if test "x$QT_IS_STATIC" = x; then
		QT_IS_STATIC="no"
	    else
		QT_IS_STATIC="yes"
	    fi
	    QT_IS_DYNAMIC=`ls $QTDIR/lib/*.so 2> /dev/null` 
	    if test "x$QT_IS_DYNAMIC" = x;  then
		if test x$QT_IS_STATIC = xno ; then
		    AC_MSG_ERROR([*** Could not find any Qt libraries])
		fi
	    else
		QT_IS_DYNAMIC="yes"
		QT_IS_STATIC="no"
	    fi

	    if test "x`ls $QTDIR/lib/libqt.* 2> /dev/null`" != x ; then
		QT_LIB="-lqt"
		QT_IS_MT="no"
	    elif test "x`ls $QTDIR/lib/libqt-mt.* 2> /dev/null`" != x ; then
		QT_LIB="-lqt-mt"
		QT_IS_MT="yes"
	    elif test "x`ls $QTDIR/lib/libqte.* 2> /dev/null`" != x ; then
		QT_LIB="-lqte"
		QT_IS_MT="no"
		QT_IS_EMBEDDED="yes"
	    elif test "x`ls $QTDIR/lib/libqte-mt.* 2> /dev/null`" != x ; then
		QT_LIB="-lqte-mt"
		QT_IS_MT="yes"
		QT_IS_EMBEDDED="yes"
	    fi
	    ;;
esac
AC_MSG_CHECKING([if Qt is static])
AC_MSG_RESULT([$QT_IS_STATIC])
AC_MSG_CHECKING([if Qt is multithreaded])
AC_MSG_RESULT([$QT_IS_MT])
AC_MSG_CHECKING([if Qt is embedded])
AC_MSG_RESULT([$QT_IS_EMBEDDED])

QT_GUILINK=""
QASSISTANTCLIENT_LDADD="-lqassistantclient"


case "${host}" in
    *irix*)
	QT_LIBS="$QT_LIB"
	if test $QT_IS_STATIC = yes ; then
	    QT_LIBS="$QT_LIBS -L$x_libraries -lXext -lX11 -lm -lSM -lICE"
	fi
	;;

    *linux*)
	QT_LIBS="$QT_LIB"
	if test $QT_IS_STATIC = yes && test $QT_IS_EMBEDDED = no; then
	    QT_LIBS="$QT_LIBS -L$x_libraries -lXext -lX11 -lm -lSM -lICE -ldl -ljpeg"
	fi
	;;

    *osf*) 
	# Digital Unix (aka DGUX aka Tru64)
	QT_LIBS="$QT_LIB"
	if test $QT_IS_STATIC = yes ; then
	    QT_LIBS="$QT_LIBS -L$x_libraries -lXext -lX11 -lm -lSM -lICE"
	fi
	;;

    *solaris*)
	QT_LIBS="$QT_LIB"
	if test $QT_IS_STATIC = yes ; then
	    QT_LIBS="$QT_LIBS -L$x_libraries -lXext -lX11 -lm -lSM -lICE -lresolv -lsocket -lnsl"
	fi
	;;

    *win*)
	# linker flag to suppress console when linking a GUI app on Win32
	QT_GUILINK="/subsystem:windows"

	if test $QT_MAJOR = "3" ; then
	    if test $QT_IS_MT = yes ; then
		QT_LIBS="/nodefaultlib:libcmt"
	    else
		QT_LIBS="/nodefaultlib:libc"
	    fi
	fi

	if test $QT_IS_STATIC = yes ; then
	    QT_LIBS="$QT_LIBS $QT_LIB kernel32.lib user32.lib gdi32.lib comdlg32.lib ole32.lib shell32.lib imm32.lib advapi32.lib wsock32.lib winspool.lib winmm.lib netapi32.lib"
	    if test $QT_MAJOR = "3" ; then
		QT_LIBS="$QT_LIBS qtmain.lib"
	    fi
	else
	    QT_LIBS="$QT_LIBS $QT_LIB"        
	    if test $QT_MAJOR = "3" ; then
		QT_CXXFLAGS="$QT_CXXFLAGS -DQT_DLL"
		QT_LIBS="$QT_LIBS qtmain.lib qui.lib user32.lib netapi32.lib"
	    fi
	fi
	QASSISTANTCLIENT_LDADD="qassistantclient.lib"
	;;

#
# added the following default clause because ${host} is unset in my case
# dont ask me why that is
#
    *)
	QT_LIBS="$QT_LIB"
	if test $QT_IS_STATIC = yes && test $QT_IS_EMBEDDED = no; then
	    QT_LIBS="$QT_LIBS -L$x_libraries -lXext -lX11 -lm -lSM -lICE -ldl -ljpeg"
	fi
	;;

esac


if test x"$QT_IS_EMBEDDED" = "xyes" ; then
	QT_CXXFLAGS="-DQWS $QT_CXXFLAGS"
fi

if test x"$QT_IS_MT" = "xyes" ; then
	QT_CXXFLAGS="$QT_CXXFLAGS -D_REENTRANT -DQT_THREAD_SUPPORT"
fi

QT_LDADD="-L$QTDIR/lib $QT_LIBS"

if test x$QT_IS_STATIC = xyes ; then
    OLDLIBS="$LIBS"
    LIBS="$QT_LDADD"
    AC_CHECK_LIB(Xft, XftFontOpen, QT_LDADD="$QT_LDADD -lXft")
#   LIBS="$LIBS"
# changed this to:
    LIBS="$OLDLIBS"
fi

AC_MSG_CHECKING([QT_CXXFLAGS])
AC_MSG_RESULT([$QT_CXXFLAGS])
AC_MSG_CHECKING([QT_LDADD])
AC_MSG_RESULT([$QT_LDADD])

AC_SUBST(QT_CXXFLAGS)
AC_SUBST(QT_LDADD)
AC_SUBST(QT_GUILINK)
AC_SUBST(QASSISTANTCLIENT_LDADD)

])

AC_DEFUN(KDE_CHECK_DLOPEN,
    [
    KDE_CHECK_LIBDL
    AC_CHECK_HEADERS(dlfcn.h dl.h)
    if test "$ac_cv_header_dlfcn_h" = "no"; then
      ac_cv_have_dlfcn=no
    fi

    if test "$ac_cv_header_dl_h" = "no"; then
      ac_cv_have_shload=no
    fi

    enable_dlopen=no
    AC_ARG_ENABLE(dlopen,
    [  --disable-dlopen        link staticly [default=no]] ,
    [if test "$enableval" = yes; then
      enable_dlopen=yes
    fi],
    enable_dlopen=yes)

    # override the user's opinion, if we know it better ;)
    if test "$ac_cv_have_dlfcn" = "no" && test "$ac_cv_have_shload" = "no"; then
      enable_dlopen=no
    fi

    if test "$ac_cv_have_dlfcn" = "yes"; then
      AC_DEFINE_UNQUOTED(HAVE_DLFCN)
    fi

    if test "$ac_cv_have_shload" = "yes"; then
      AC_DEFINE_UNQUOTED(HAVE_SHLOAD)
    fi

    if test "$enable_dlopen" = no ; then
      test -n "$1" && eval $1
    else
      test -n "$2" && eval $2
    fi

    ])

AC_DEFUN(KDE_CHECK_DYNAMIC_LOADING,
    [
    KDE_CHECK_DLOPEN(libtool_enable_shared=no, libtool_enable_static=no)
    KDE_PROG_LIBTOOL
    AC_MSG_CHECKING([dynamic loading])
    eval "`egrep '^build_libtool_libs=' libtool`"
    if test "$build_libtool_libs" = "yes" && test "$enable_dlopen" = "yes"; then
      dynamic_loading=yes
      AC_DEFINE_UNQUOTED(HAVE_DYNAMIC_LOADING)
    else
      dynamic_loading=no
    fi
    AC_MSG_RESULT($dynamic_loading)
    if test "$dynamic_loading" = "yes"; then
      $1
    else
      $2
fi
])


AC_DEFUN(AC_FIND_PNG,
[
AC_REQUIRE([AC_FIND_ZLIB])
AC_MSG_CHECKING([for libpng])
AC_CACHE_VAL(ac_cv_lib_png,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -lpng $LIBZ -lm -lX11 $LIBSOCKET"
AC_LANG_C
AC_TRY_LINK(dnl
    [
    #include<png.h>
    ],
    [
    png_structp png_ptr = png_create_read_struct(  // image ptr
		PNG_LIBPNG_VER_STRING, 0, 0, 0 );
    return( png_ptr != 0 ); 
    ],
    eval "ac_cv_lib_png='-lpng $LIBZ -lm'",
    eval "ac_cv_lib_png=no")
    LIBS="$ac_save_LIBS"
])dnl
if eval "test ! \"`echo $ac_cv_lib_png`\" = no"; then
  AC_DEFINE_UNQUOTED(HAVE_LIBPNG)
  LIBPNG="$ac_cv_lib_png"
  AC_SUBST(LIBPNG)
  AC_MSG_RESULT($ac_cv_lib_png)
else
  AC_MSG_RESULT(no)
  LIBPNG=""
  AC_SUBST(LIBPNG)
fi
])



AC_DEFUN(AC_CHECK_GETDOMAINNAME,
[
AC_LANG_CPLUSPLUS
save_CXXFLAGS="$CXXFLAGS"
if test "$GCC" = "yes"; then
CXXFLAGS="$CXXFLAGS -pedantic-errors"
fi
AC_MSG_CHECKING(for getdomainname)
AC_CACHE_VAL(ac_cv_func_getdomainname,
[
AC_TRY_COMPILE([
#include <stdlib.h>
#include <unistd.h>
],
[
char buffer[200];
getdomainname(buffer, 200);
],
ac_cv_func_getdomainname=yes,
ac_cv_func_getdomainname=no)
])
AC_MSG_RESULT($ac_cv_func_getdomainname)
if eval "test \"`echo `$ac_cv_func_getdomainname\" = yes"; then
  AC_DEFINE(HAVE_GETDOMAINNAME)
fi
CXXFLAGS="$save_CXXFLAGS"
])

AC_DEFUN(AC_CHECK_GETHOSTNAME,
[
AC_LANG_CPLUSPLUS
save_CXXFLAGS="$CXXFLAGS"
if test "$GCC" = "yes"; then
CXXFLAGS="$CXXFLAGS -pedantic-errors"
fi

AC_MSG_CHECKING([for gethostname])
AC_CACHE_VAL(ac_cv_func_gethostname,
[
AC_TRY_COMPILE([
#include <stdlib.h>
#include <unistd.h>
],
[
char buffer[200];
gethostname(buffer, 200);
],
ac_cv_func_gethostname=yes,
ac_cv_func_gethostname=no)
])
AC_MSG_RESULT($ac_cv_func_gethostname)
if eval "test \"`echo `$ac_cv_func_gethostname\" = yes"; then
  AC_DEFINE(HAVE_GETHOSTNAME)
fi
CXXFLAGS="$save_CXXFLAGS"
])

AC_DEFUN(AC_CHECK_USLEEP,
[
AC_LANG_CPLUSPLUS

AC_MSG_CHECKING([for usleep])
AC_CACHE_VAL(ac_cv_func_usleep,
[
ac_libs_safe="$LIBS"
LIBS="$LIBS $LIBUCB"
AC_TRY_LINK([
#include <stdlib.h>
#include <unistd.h>
],
[
usleep(200);
],
ac_cv_func_usleep=yes,
ac_cv_func_usleep=no)
])
AC_MSG_RESULT($ac_cv_func_usleep)
if eval "test \"`echo `$ac_cv_func_usleep\" = yes"; then
  AC_DEFINE(HAVE_USLEEP)
fi
LIBS="$ac_libs_safe"
])

AC_DEFUN(AC_FIND_GIF,
   [AC_MSG_CHECKING([for giflib])
AC_CACHE_VAL(ac_cv_lib_gif,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -lgif -lX11 $LIBSOCKET"
AC_TRY_LINK(dnl
[
#ifdef __cplusplus
extern "C" {
#endif
int GifLastError(void);
#ifdef __cplusplus
}
#endif
/* We use char because int might match the return type of a gcc2
    builtin and then its argument prototype would still apply.  */
],
            [return GifLastError();],
            eval "ac_cv_lib_gif=yes",
            eval "ac_cv_lib_gif=no")
LIBS="$ac_save_LIBS"
])dnl
if eval "test \"`echo $ac_cv_lib_gif`\" = yes"; then
  AC_MSG_RESULT(yes)
  AC_DEFINE_UNQUOTED(HAVE_LIBGIF)
else
  AC_MSG_ERROR(You need giflib23. Please install the kdesupport package)
fi
])

AC_DEFUN(AC_FIND_JPEG,
   [AC_MSG_CHECKING([for jpeglib])
AC_CACHE_VAL(ac_cv_lib_jpeg,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -ljpeg -lm"
AC_TRY_LINK(
[/* Override any gcc2 internal prototype to avoid an error.  */
struct jpeg_decompress_struct;
typedef struct jpeg_decompress_struct * j_decompress_ptr;
typedef int size_t;
#ifdef __cplusplus
extern "C" {
#endif
    void jpeg_CreateDecompress(j_decompress_ptr cinfo,
                                    int version, size_t structsize);
#ifdef __cplusplus
}
#endif
/* We use char because int might match the return type of a gcc2
    builtin and then its argument prototype would still apply.  */
],
            [jpeg_CreateDecompress(0L, 0, 0);],
            eval "ac_cv_lib_jpeg=-ljpeg",
            eval "ac_cv_lib_jpeg=no")
LIBS="$ac_save_LIBS"

dnl what to do, if the normal way fails:
if eval "test \"`echo $ac_cv_lib_jpeg`\" = no"; then
	if test -f "$kde_libraries/libjpeg.so"; then
	   test -f ./libjpegkde.so || $LN_S $kde_libraries/libjpeg.so ./libjpegkde.so
	   ac_cv_lib_jpeg="-L\${topdir} -ljpegkde"
	else if test -f "$kde_libraries/libjpeg.sl"; then
	   test -f ./libjpegkde.sl ||$LN_S $kde_libraries/libjpeg.sl ./libjpegkde.sl
	   ac_cv_lib_jpeg="-L\${topdir} -ljpegkde"	
	else if test -f "$kde_libraries/libjpeg.a"; then
	   test -f ./libjpegkde.a || $LN_S $kde_libraries/libjpeg.a ./libjpegkde.a
	   ac_cv_lib_jpeg="-L\${topdir} -ljpegkde"
        else
	  AC_MSG_ERROR([
You need jpeglib6a. Please install the kdesupport package.
If you have already installed kdesupport, you may have an
old libjpeg somewhere. 
In this case copy $KDEDIR/lib/libjpeg* to /usr/lib.
])
	fi
      fi
   fi
fi
])dnl
if eval "test ! \"`echo $ac_cv_lib_jpeg`\" = no"; then
  LIBJPEG="$ac_cv_lib_jpeg"
  AC_SUBST(LIBJPEG)
  AC_MSG_RESULT($ac_cv_lib_jpeg)
  AC_DEFINE_UNQUOTED(HAVE_LIBJPEG)
fi
])

AC_DEFUN(AC_FIND_ZLIB,
[
AC_MSG_CHECKING([for libz])
AC_CACHE_VAL(ac_cv_lib_z,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -lz $LIBSOCKET"
AC_TRY_LINK(dnl
[
#include<zlib.h>
],
            [return (zlibVersion() == ZLIB_VERSION); ],
            eval "ac_cv_lib_z='-lz'",
            eval "ac_cv_lib_z=no")
LIBS="$ac_save_LIBS"
])dnl
if eval "test ! \"`echo $ac_cv_lib_z`\" = no"; then
dnl  AC_DEFINE_UNQUOTED(HAVE_LIBZ)
  LIBZ="$ac_cv_lib_z"
  AC_SUBST(LIBZ)
  AC_MSG_RESULT($ac_cv_lib_z)
else
  AC_MSG_RESULT(no)
  LIBZ=""
  AC_SUBST(LIBZ)
fi
])
