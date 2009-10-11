AUTOMAKE_OPTIONS = gnu

if COND_CLIENT
    BUILD_CLIENT = clientlib client
endif

if COND_SERVER
    BUILD_SERVER = server
endif


SUBDIRS = po lib $(BUILD_SERVER) $(BUILD_CLIENT)
DIST_SUBDIRS = po lib server clientlib client m4

EXTRA_DIST = config.rpath  
	autogen.sh

ACLOCAL_AMFLAGS = -I m4
