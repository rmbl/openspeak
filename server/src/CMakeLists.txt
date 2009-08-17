SET (Boost_USE_MULTITHREAD ON)
FIND_PACKAGE (Boost 1.39 COMPONENTS thread)

include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/server/include)

add_executable (openspeakd main.cpp)
set_target_properties (openspeakd PROPERTIES COMPILE_FLAGS -ggdb3)
target_link_libraries (openspeakd openspeaklib ${Boost_THREAD_LIBRARY})

install (PROGRAMS openspeakd DESTINATION bin)
