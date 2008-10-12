## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = garia2

garia2_SOURCES = \
	main.c garia2.h \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	preference.c preference.h

garia2_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

