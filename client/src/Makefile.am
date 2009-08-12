bin_PROGRAMS = openspeak
openspeak_SOURCES = \
		main.cpp

openspeak_LDADD = ../../lib/src/libopenspeak.la ../../clientlib/src/libopenspeakclient.la $(BOOST_LDFLAGS) $(BOOST_SIGNALS_LIB) -ldl
openspeak_CPPFLAGS = $(BOOST_CPPFLAGS) $(OS_CPPFLAGS)
INCLUDES = -I../../lib/include -I../include -I../../clientlib/include
