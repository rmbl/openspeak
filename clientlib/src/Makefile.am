lib_LTLIBRARIES = libopenspeakclient.la
libopenspeakclient_la_SOURCES = \
                    Core.cpp \
					EventMgr.cpp \
					PluginMgr.cpp

libopenspeakclient_la_LDFLAGS = -version-info 1:1:0
libopenspeakclient_la_LIBADD = ../../lib/src/libopenspeak.la -ldl
libopenspeakclient_la_CPPFLAGS = $(BOOST_CPPFLAGS) $(OS_CPPFLAGS)
INCLUDES = -I../include -I../../lib/include
