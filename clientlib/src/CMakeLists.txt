SET (Boost_USE_MULTITHREAD ON)
FIND_PACKAGE (Boost 1.33 COMPONENTS signals)

include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/clientlib/include ${Boost_INCLUDE_DIRS})

add_library (openspeakclient SHARED EventMgr.cpp PluginMgr.cpp)
set_target_properties (openspeakclient PROPERTIES COMPILE_FLAGS -ggdb3)
target_link_libraries (openspeakclient openspeaklib ${Boost_SIGNALS_LIBRARY} dl)
