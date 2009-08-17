include_directories (${openSpeak_SOURCE_DIR}/lib/include)
add_definitions (-DOS_PREFIX=\"/usr\")

add_library (openspeaklib SHARED dummy.cpp CmdLineParser.cpp Config.cpp 
        FileUtils.cpp Log.cpp LogMgr.cpp StringUtils.cpp Thread.cpp)
set_target_properties (openspeaklib PROPERTIES COMPILE_FLAGS -ggdb3)

install (TARGETS openspeaklib LIBRARY DESTINATION lib)
