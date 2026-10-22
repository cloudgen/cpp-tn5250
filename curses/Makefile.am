## Process this file with automake to produce Makefile.in

EXTRA_DIST = CMakeLists.txt

bin_PROGRAMS =		tn5250

LDADD = ../lib5250/lib5250.la

tn5250_SOURCES = 	cursesterm.cpp tn5250.cpp

tn5250_CXXFLAGS = $(AM_CXXFLAGS)

tn5250_LDFLAGS = $(CURSES_LIBS)

pkginclude_HEADERS = 	cursesterm.h

AM_CPPFLAGS = -DSYSCONFDIR=\"$(sysconfdir)\" -I$(top_srcdir)/lib5250
