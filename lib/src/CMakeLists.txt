IF (WIN32)
	SET (BOOST_ROOT $ENV{BOOST_ROOT})
ENDIF (WIN32)

SET (Boost_USE_MULTITHREAD ON)
FIND_PACKAGE (Boost 1.39 REQUIRED COMPONENTS thread)

include_directories (${openSpeak_SOURCE_DIR}/lib/include ${Boost_INCLUDE_DIRS})
add_definitions (-DOS_PREFIX=\"/usr\")

add_library (openspeaklib SHARED dummy.cpp CmdLineParser.cpp Config.cpp 
        FileUtils.cpp Log.cpp LogMgr.cpp StringUtils.cpp Thread.cpp)
IF (CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties (openspeaklib PROPERTIES COMPILE_FLAGS -ggdb3)
ENDIF (CMAKE_COMPILER_IS_GNUCXX)

install (TARGETS openspeaklib LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
