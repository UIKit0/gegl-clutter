CFILES = $(wildcard $(srcdir)/*.c)
bins   = $(subst $(srcdir)/,,$(CFILES:.c=))
EXTRA_DIST = $(wildcard *.c)

all-local: $(bins)

clean-local:
	rm -f *.lo $(bins)

INCLUDES = -I$(top_srcdir)/ @GCC_FLAGS@ @DEPS_CFLAGS@
LDFLAGS = @DEPS_LIBS@ $(top_builddir)/libgegl-clutter-@CLUTTER_GEGL_MAJORMINOR@.la 

%: %.c $(GEGLHEADERS)
	$(LIBTOOL) --mode=compile $(CC) $< -c -o $@.lo $(INCLUDES) -DHAVE_CONFIG_H
	$(LIBTOOL) --mode=link    $(CC) $@.lo -o $@ $(LDFLAGS)

