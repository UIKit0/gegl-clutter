AC_PREREQ(2.53)

# clutter package version number, (as distinct from shared library version)
# An odd micro number indicates in-progress development, (eg. from CVS)
# An even micro number indicates a released version.
m4_define(clutter_gegl_version_major, 0)
m4_define(clutter_gegl_version_minor, 0)
m4_define(clutter_gegl_version_micro, 1)

m4_define([clutter_gegl_version],
          [clutter_gegl_version_major.clutter_gegl_version_minor.clutter_gegl_version_micro])

m4_define([clutter_gegl_api_version],
          [clutter_gegl_version_major.clutter_gegl_version_minor])

m4_define([clutter_gegl_interface_age], [0])
m4_define([clutter_gegl_binary_age],
          [m4_eval(100 * clutter_gegl_version_minor + clutter_gegl_version_micro)])

AC_INIT([clutter-gegl], 
       clutter_gegl_version_major.clutter_gegl_version_minor.clutter_gegl_version_micro, 
        [http://bugzilla.o-hand.com/enter_bug.cgi?product=Clutter])
AC_CONFIG_SRCDIR([clutter-gegl.h])
AM_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE([1.7])

CLUTTER_GEGL_MAJORMINOR=clutter_gegl_version_major.clutter_gegl_version_minor
AC_SUBST(CLUTTER_GEGL_MAJORMINOR)

# CURRENT, REVISION, AGE
# - library source changed -> increment REVISION
# - interfaces added/removed/changed -> increment CURRENT, REVISION = 0
# - interfaces added -> increment AGE
# - interfaces removed -> AGE = 0
m4_define([lt_current],
          [m4_eval(100 * clutter_gegl_version_minor + clutter_gegl_version_micro - clutter_gegl_interface_age)])
m4_define([lt_revision], [clutter_gegl_interface_age])
m4_define([lt_age], [m4_eval(clutter_gegl_binary_age - clutter_gegl_interface_age)])
CLUTTER_GEGL_LT_CURRENT=lt_current
CLUTTER_GEGL_LT_REV=lt_revision
CLUTTER_GEGL_LT_AGE=lt_age
CLUTTER_GEGL_LT_VERSION="$CLUTTER_GEGL_LT_CURRENT:$CLUTTER_GEGL_LT_REV:$CLUTTER_GEGL_LT_AGE"
CLUTTER_GEGL_LT_LDFLAGS="-version-info $CLUTTER_GEGL_LT_VERSION"

AC_SUBST(CLUTTER_GEGL_LT_VERSION)
AC_SUBST(CLUTTER_GEGL_LT_LDFLAGS)

dnl ========================================================================

# Checks for programs.
AC_PROG_CC
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_CHECK_FUNCS([memset munmap strcasecmp strdup])


dnl ========================================================================


pkg_modules="clutter-0.5, gegl >= 0.0.14"
PKG_CHECK_MODULES(DEPS, [$pkg_modules])

if test "x$GCC" = "xyes"; then
        GCC_FLAGS="-g -Wall"
fi

AC_SUBST(GCC_FLAGS)
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)

AC_OUTPUT([Makefile
clutter-gegl.pc
examples/Makefile
])

