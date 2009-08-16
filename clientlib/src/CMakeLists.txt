INCLUDE (CheckLibraryExists)
INCLUDE (CheckIncludeFile)

SET (Boost_USE_MULTITHREAD ON)
FIND_PACKAGE (Boost 1.39)
CHECK_INCLUDE_FILE (boost/signals2.hpp HAVE_SIGNALS2)
CHECK_LIBRARY_EXISTS (dl dlopen "" HAVE_LIBDL) 

include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/clientlib/include ${Boost_INCLUDE_DIRS})

add_library (openspeakclient SHARED EventMgr.cpp PluginMgr.cpp Core.cpp)
set_target_properties (openspeakclient PROPERTIES COMPILE_FLAGS -ggdb3)
target_link_libraries (openspeakclient openspeaklib dl)

install (TARGETS openspeakclient LIBRARY DESTINATION lib)
