AC_INIT([gnethogs],[0.1])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX
AC_PROG_CC

AC_PATH_PROG([GLIB_COMPILE_RESOURCES], [glib-compile-resources])

PKG_CHECK_MODULES(GNETHOGS, [gtkmm-3.0 ])

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
