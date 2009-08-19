include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/clientlib/include ${Boost_INCLUDE_DIRS})

add_library (openspeakclient SHARED EventMgr.cpp PluginMgr.cpp PluginInterfaceProvider.cpp Core.cpp)

IF (CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties (openspeakclient PROPERTIES COMPILE_FLAGS -ggdb3)
ENDIF (CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries (openspeakclient openspeaklib dl)

install (TARGETS openspeakclient LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)