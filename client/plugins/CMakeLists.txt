include_directories (${openSpeak_SOURCE_DIR}/lib/include ${openSpeak_SOURCE_DIR}/clientlib/include)

add_library (test SHARED test.cpp)
target_link_libraries (test openspeakclient openspeaklib)

install (TARGETS test LIBRARY DESTINATION lib/openspeak)
