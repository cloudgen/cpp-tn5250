## Process this file with automake to produce Makefile.in

EXTRA_DIST = CMakeLists.txt

lib_LTLIBRARIES =	lib5250.la

lib5250_la_SOURCES =	buffer.cpp\
			conf.cpp\
			dbuffer.cpp\
			debug.cpp\
			display.cpp\
			field.cpp\
			macro.cpp\
			menu.cpp\
			printsession.cpp\
			record.cpp\
			scrollbar.cpp\
			scs.cpp\
			session.cpp\
			sslstream.cpp\
			stream.cpp\
			telnetstr.cpp\
			terminal.cpp\
			utility.cpp\
			version.cpp\
			window.cpp\
			wtd.cpp

AM_CPPFLAGS = -DSYSCONFDIR=\"$(sysconfdir)\"

pkginclude_HEADERS = 	buffer.h\
		 	codes5250.h\
			conf.h\
			dbuffer.h\
			debug.h\
			display.h\
			field.h\
			macro.h\
			menu.h\
			printsession.h\
			record.h\
			scrollbar.h\
			scs.h\
			session.h\
			stream.h\
			terminal.h\
			utility.h\
			window.h\
			wtd.h

include_HEADERS =	tn5250.h

noinst_HEADERS =	transmaps.h\
			scs-private.h\
			stream-private.h\
			tn5250-private.h
