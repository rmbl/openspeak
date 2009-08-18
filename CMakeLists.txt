cmake_minimum_required (VERSION 2.6)
project (openSpeak C CXX)

# Check for global dependecies
IF (WIN32)
	SET (BOOST_ROOT $ENV{BOOST_ROOT})
ENDIF (WIN32)

SET (Boost_USE_MULTITHREAD ON)
FIND_PACKAGE (Boost 1.39 REQUIRED COMPONENTS thread date_time)

IF (UNIX)
	INCLUDE (CheckLibraryExists)
	CHECK_LIBRARY_EXISTS (dl dlopen "" HAVE_LIBDL) 
ENDIF (UNIX)

add_subdirectory (lib)
add_subdirectory (server)
add_subdirectory (clientlib)
add_subdirectory (client)

SET (CPACK_PACKAGE_NAME "openSpeak")
SET (CPACK_PACKAGE_DESCRIPTION_SUMMARY "VoIP tool for gamer")
SET (CPACK_PACKAGE_VENDOR "The openSpeak Team")
SET (CPACK_PACKAGE_DESCRIPTION_FILE "${openSpeak_SOURCE_DIR}/README")
SET (CPACK_RESOURCE_FILE_LICENSE "${openSpeak_SOURCE_DIR}/COPYING")
SET (CPACK_PACKAGE_VERSION "0.1-git")
SET (CPACK_PACKAGE_VERSION_MAJOR "0")
SET (CPACK_PACKAGE_VERSION_MINOR "1")
SET (CPACK_PACKAGE_VERSION_PATCH "0")

IF (WIN32 AND NOT UNIX)
    SET (CPACK_NSIS_DISPLAY_NAME "openSpeak 0.1-git")
    SET (CPACK_NSIS_HELP_LINK "http:\\\\\\openspeak-project.org")
    SET (CPACK_NSIS_URL_INFO "http:\\\\\\openspeak-project.org")
    SET (CPACK_NSIS_CONTACT "rmbl@openspeak-project.org")
    SET (CPACK_NSIS_MODIFY_PATH ON)
ELSE (WIN32 AND NOT UNIX)

ENDIF (WIN32 AND NOT UNIX)

SET (CPACK_PACKAGE_EXECUTABLES "client/src/openspeak;server/src/openspeakd")
INCLUDE (CPack)
