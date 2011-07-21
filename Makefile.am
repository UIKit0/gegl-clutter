SUBDIRS = . examples

gegl-clutter-0.10.pc: gegl-clutter.pc
	@cp -f $< $@

pkgconfig_DATA = gegl-clutter-0.10.pc
pkgconfigdir   = $(libdir)/pkgconfig

INCLUDES = @GCC_FLAGS@ @DEPS_CFLAGS@

lib_LTLIBRARIES = libgegl-clutter-@CLUTTER_GEGL_MAJORMINOR@.la

libgegl_clutter_@CLUTTER_GEGL_MAJORMINOR@_la_SOURCES = gegl-clutter.c
libgegl_clutter_@CLUTTER_GEGL_MAJORMINOR@_la_LIBADD  = @DEPS_LIBS@
libgegl_clutter_@CLUTTER_GEGL_MAJORMINOR@_la_LDFLAGS = @CLUTTER_GEGL_LT_LDFLAGS@

gegl_clutterheaders_HEADERS = gegl-clutter.h
gegl_clutterheadersdir = $(includedir)/clutter-0.10/gegl-clutter

EXTRA_DIST = gegl-clutter.pc.in

CLEANFILES = gegl-clutter-0.10.pc
DISTCLEANFILES = gegl-clutter.pc

# Extra clean files so that maintainer-clean removes *everything*
MAINTAINERCLEANFILES = aclocal.m4 compile config.guess config.sub \
                       configure depcomp install-sh ltmain.sh     \
                       Makefile.in missing config.h.in
