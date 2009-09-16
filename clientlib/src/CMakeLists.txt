include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/clientlib/include ${Boost_INCLUDE_DIRS})

set (SOURCE
	EventMgr.cpp
	PluginMgr.cpp
	PluginInterfaceProvider.cpp
	AudioInputProvider.cpp
	AudioOutputProvider.cpp
	VoiceCodecProvider.cpp
	Core.cpp
)

file (GLOB HEADERS "../include/*.hpp")

add_library (openspeakclient SHARED ${SOURCE} ${HEADERS})

IF (CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties (openspeakclient PROPERTIES COMPILE_FLAGS -ggdb3)
ENDIF (CMAKE_COMPILER_IS_GNUCXX)

IF (MSVC)
	set (LIBS openspeaklib)
ELSE (MSVC)
	set (LIBS openspeaklib dl)
ENDIF (MSVC)

target_link_libraries (openspeakclient ${LIBS})

install (TARGETS openspeakclient LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
