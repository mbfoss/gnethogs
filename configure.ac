AC_INIT([gnethogs],[0.1])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.14])

AM_SILENT_RULES([yes])

AC_PROG_CXX
AC_PROG_CC

AC_PATH_PROG([GLIB_COMPILE_RESOURCES], [glib-compile-resources])

PKG_CHECK_MODULES(GNETHOGS, [gtkmm-3.0 ])


# check for pthread
PTHREAD_LIBS=error
AC_CHECK_LIB(pthread, pthread_attr_init, PTHREAD_LIBS="-lpthread")
if test "x$PTHREAD_LIBS" = xerror; then
        AC_CHECK_LIB(pthreads, pthread_attr_init, PTHREAD_LIBS="-lpthreads")
fi
if test "x$PTHREAD_LIBS" = xerror; then
        AC_CHECK_LIB(c_r, pthread_attr_init, PTHREAD_LIBS="-lc_r")
fi
if test "x$PTHREAD_LIBS" = xerror; then
        AC_CHECK_FUNC(pthread_attr_init, PTHREAD_LIBS="")
fi
AC_SUBST(PTHREAD_LIBS)

#check for libnethogs

AC_CHECK_LIB(nethogs, nethogsmonitor_loop, [], [
   echo "Error! You need to have libnethogs-dev installed."
   exit -1
])

AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([libnethogs.h])
AC_LANG_POP

IT_PROG_INTLTOOL([0.35.0]) # Intltool
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.19.3])

AC_CONFIG_FILES([ 
Makefile
src/Makefile
data/Makefile
data/icons/Makefile
po/Makefile.in 
])
AC_OUTPUT

