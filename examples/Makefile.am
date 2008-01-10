noinst_PROGRAMS = parsexml 

INCLUDES = -I$(top_srcdir)/ @GCC_FLAGS@ @DEPS_CFLAGS@
LDFLAGS = @DEPS_LIBS@ $(top_builddir)/libclutter-gegl-@CLUTTER_GEGL_MAJORMINOR@.la 

parsexml_SOURCES = parsexml.c
