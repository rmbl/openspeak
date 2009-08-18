include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/clientlib/include ${openSpeak_SOURCE_DIR}/client/include ${Boost_INCLUDE_DIRS})

add_executable (openspeak main.cpp)
IF (CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties (openspeak PROPERTIES COMPILE_FLAGS -ggdb3)
ENDIF (CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries (openspeak openspeaklib openspeakclient ${Boost_THREAD_LIBRARY} dl)

install (PROGRAMS openspeak DESTINATION bin)
