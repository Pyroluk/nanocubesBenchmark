set(CMAKE_CXX_FLAGS "-fPIC -g -std=c++11")

add_library(jsoncpp jsoncpp.cpp)
target_include_directories (jsoncpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
