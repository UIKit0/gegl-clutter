SUBDIRS = . examples

clutter-gegl-0.7.pc: clutter-gegl.pc
	@cp -f $< $@

pkgconfig_DATA = clutter-gegl-0.7.pc
pkgconfigdir   = $(libdir)/pkgconfig

INCLUDES = @GCC_FLAGS@ @DEPS_CFLAGS@ 

lib_LTLIBRARIES = libclutter-gegl-@CLUTTER_GEGL_MAJORMINOR@.la

libclutter_gegl_@CLUTTER_GEGL_MAJORMINOR@_la_SOURCES = clutter-gegl.c
libclutter_gegl_@CLUTTER_GEGL_MAJORMINOR@_la_LIBADD  = @DEPS_LIBS@
libclutter_gegl_@CLUTTER_GEGL_MAJORMINOR@_la_LDFLAGS = @CLUTTER_GEGL_LT_LDFLAGS@

clutter_geglheaders_HEADERS = clutter-gegl.h
clutter_geglheadersdir = $(includedir)/clutter-0.7/clutter-gegl

EXTRA_DIST = clutter-gegl.pc.in

CLEANFILES = clutter-gegl-0.7.pc
DISTCLEANFILES = clutter-gegl.pc

# Extra clean files so that maintainer-clean removes *everything*
MAINTAINERCLEANFILES = aclocal.m4 compile config.guess config.sub \
                       configure depcomp install-sh ltmain.sh     \
                       Makefile.in missing config.h.in
