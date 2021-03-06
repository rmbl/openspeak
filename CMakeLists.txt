cmake_minimum_required (VERSION 2.6)
project (openSpeak C CXX)

# Some variables used for .po(t) creation
set (PACKAGE_NAME openSpeak)
set (PACKAGE_VERSION 0.2-git)
set (BUG_EMAIL bugs@openspeak-project.org)

# Also include our custom cmake files in ./cmake
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Check for global dependecies
if (WIN32)
	set (BOOST_ROOT $ENV{BOOST_ROOT})
endif (WIN32)

# Check for boost >= 1.40.0
set (Boost_USE_MULTITHREAD ON)
find_package (Boost 1.40 REQUIRED COMPONENTS thread date_time)

if (NOT Boost_FOUND)
    message (FATAL_ERROR "Boost >= 1.40.0 couldn't be found! Please install it \
            or update your version")
endif (NOT Boost_FOUND)

# Check for gettext
find_package (Gettext REQUIRED)

if (NOT GETTEXT_FOUND)
    message (FATAL_ERROR "Gettext couldn't be found! Please install it!")
endif (NOT GETTEXT_FOUND)

# Check for libdl for plugin support
if (UNIX)
	include (CheckLibraryExists)
	check_library_exists (dl dlopen "" HAVE_LIBDL)
    
    if (NOT HAVE_LIBDL)
        message (FATAL_ERROR "Libdl couldn't be found! Please install it")
    endif (NOT HAVE_LIBDL)
endif (UNIX)

# Add all required subdirectories
add_subdirectory (po)
add_subdirectory (lib)
add_subdirectory (server)
add_subdirectory (clientlib)
add_subdirectory (client)

# Set important CPack variables
set (CPACK_PACKAGE_NAME "openSpeak")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "VoIP tool for gamer")
set (CPACK_PACKAGE_VENDOR "The openSpeak Team")
set (CPACK_PACKAGE_DESCRIPTION_FILE "${openSpeak_SOURCE_DIR}/README")
set (CPACK_RESOURCE_FILE_LICENSE "${openSpeak_SOURCE_DIR}/COPYING")
set (CPACK_PACKAGE_VERSION "0.1-git")
set (CPACK_PACKAGE_VERSION_MAJOR "0")
set (CPACK_PACKAGE_VERSION_MINOR "1")
set (CPACK_PACKAGE_VERSION_PATCH "0")

if (WIN32 AND NOT UNIX)
    set (CPACK_NSIS_DISPLAY_NAME "openSpeak 0.1-git")
    set (CPACK_NSIS_HELP_LINK "http:\\\\\\openspeak-project.org")
    set (CPACK_NSIS_URL_INFO "http:\\\\\\openspeak-project.org")
    set (CPACK_NSIS_CONTACT "rmbl@openspeak-project.org")
    set (CPACK_NSIS_MODIFY_PATH ON)
endif (WIN32 AND NOT UNIX)

set (CPACK_PACKAGE_EXECUTABLES "client/src/openspeak;server/src/openspeakd")
include (CPack)
