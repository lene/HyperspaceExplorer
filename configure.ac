#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(HyperspaceExplorer, 0.2.0, helge.preuss@gmx.net, hyperspace-expl)
AM_INIT_AUTOMAKE
AC_CONFIG_AUX_DIR([config])
#AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET

AC_LANG([C++])

# Checks for libraries.

AC_HAVE_GL
INCLUDES="$INCLUDES $GLINC"
# i am not certain which one of the following two is relevant...
LIBS="$LIBS $GLLIB"
LDADD="$LDADD $GLLIB"

# check whether to use the Qt library.
# this check does not make sense in this case, as we need it in any case.
# it is included as a practice.
AC_ARG_ENABLE(qt, [[  --enable-qt             Build Qt utils. Default. ]], \
    if test "$enableval" = "no"; then \
	AC_MSG_ERROR([[You cannot disable using the Qt libraries, sorry!]])
fi;)

gw_CHECK_QT

dnl AC_LANG([C++])
dnl # check whether the QGL extension is present
dnl AC_MSG_CHECKING([[for QGL extension]])

dnl AC_TRY_LINK([
dnl          #include <qgl.h>
dnl         ],[
dnl 	  QGLWidget w;
dnl 	  exit (0);
dnl         ],
dnl 	AC_MSG_RESULT([yes]),
dnl         AC_MSG_WARN([[
dnl Your Qt installation does not have the QGL extension!]])
dnl      )

# export the necessary variables
AC_SUBST(INCLUDES)
AC_SUBST(LDFLAGS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt usleep])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
