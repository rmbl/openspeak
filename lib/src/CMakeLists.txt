include_directories (${openSpeak_SOURCE_DIR}/lib/include ${Boost_INCLUDE_DIRS})
link_directories (${Boost_LIBRARY_DIRS})
add_definitions (-DOS_PREFIX=\"/usr\" -DOS_BUILD_DLL)

set (SOURCE
	dummy.cpp
	CmdLineParser.cpp
	Config.cpp
	FileUtils.cpp
	Log.cpp
	LogMgr.cpp
	StringUtils.cpp
	Thread.cpp
)

file (GLOB HEADERS "../include/*.hpp")
	

add_library (openspeaklib SHARED ${SOURCE} ${HEADERS})
IF (CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties (openspeaklib PROPERTIES COMPILE_FLAGS -ggdb3)
ENDIF (CMAKE_COMPILER_IS_GNUCXX)
#target_link_libraries (openspeaklib ${Boost_THREAD_LIBRARY})

install (TARGETS openspeaklib LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
