include (MacroAddPlugin)

include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/clientlib/include ${Boost_INCLUDE_DIRS})

add_plugin (test test.cpp)
target_link_libraries (test openspeakclient openspeaklib)

add_plugin (portaudio portaudio.cpp)
target_link_libraries (portaudio openspeakclient openspeaklib)

install (TARGETS test LIBRARY DESTINATION lib/openspeak ARCHIVE DESTINATION lib/openspeak)
