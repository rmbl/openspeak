IF (WIN32)
	SET (BOOST_ROOT $ENV{BOOST_ROOT})
ENDIF (WIN32)

SET (Boost_USE_MULTITHREAD ON)
FIND_PACKAGE (Boost 1.39)

include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/clientlib/include ${Boost_INCLUDE_DIRS})

add_library (test SHARED test.cpp)
target_link_libraries (test openspeakclient openspeaklib)

install (TARGETS test LIBRARY DESTINATION lib/openspeak ARCHIVE DESTINATION lib/openspeak)
