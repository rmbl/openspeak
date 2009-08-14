SET (Boost_USE_MULTITHREAD ON)
FIND_PACKAGE (Boost 1.33 COMPONENTS signals)

include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/clientlib/include ${openSpeak_SOURCE_DIR}/client/include ${Boost_INCLUDE_DIRS})

add_executable (openspeak main.cpp)
set_target_properties (openspeak PROPERTIES COMPILE_FLAGS -ggdb3)
target_link_libraries (openspeak openspeaklib openspeakclient ${Boost_SIGNALS_LIBRARY} dl)

install (PROGRAMS openspeak DESTINATION bin)
