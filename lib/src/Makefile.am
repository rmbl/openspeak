lib_LTLIBRARIES = libopenspeak.la
libopenspeak_la_SOURCES = \
	dummy.cpp \
	CmdLineParser.cpp \
	Config.cpp \
	FileUtils.cpp \
	LogMgr.cpp \
	Log.cpp \
	StringUtils.cpp

libopenspeak_la_LDFLAGS = -version-info 1:1:0
INCLUDES = -I../include
AM_CPPFLAGS = -DOS_PREFIX=\"$(OS_PREFIX)\" $(OS_CPPFLAGS)
