openspeak_libdir = $(libdir)/openspeak
openspeak_lib_LTLIBRARIES = test.la portaudio.la
INCLUDES = -I../../clientlib/include -I../../lib/include

test_la_SOURCES = test.cpp
test_la_LDFLAGS = -module -avoid-version

portaudio_la_SOURCES = portaudio.cpp
portaudio_la_LDFLAGS = -module -avoid-version
portaudio_la_LIBADD = $(PORTAUDIO_LIBS)
portaudio_la_CPPFLAGS = $(PORTAUDIO_CFLAGS)


