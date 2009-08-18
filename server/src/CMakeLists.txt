include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/server/include ${BOOST_INCLUDE_DIRS})

add_executable (openspeakd main.cpp)
IF (CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties (openspeakd PROPERTIES COMPILE_FLAGS -ggdb3)
ENDIF (CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries (openspeakd openspeaklib ${Boost_THREAD_LIBRARY})

install (PROGRAMS openspeakd DESTINATION bin)
