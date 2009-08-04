lib_LTLIBRARIES = libopenspeakclient.la
libopenspeakclient_la_SOURCES = \
					EventMgr.cpp

libopenspeakclient_la_LDFLAGS = -version-info 1:1:0
libopenspeakclient_la_LIBADD = ../../lib/src/libopenspeak.la $(BOOST_SIGNALS_LIB)
libopenspeakclient_la_CPPFLAGS = $(BOOST_CPPFLAGS)
INCLUDES = -I../include -I../../lib/include
