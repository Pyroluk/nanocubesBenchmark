cmake_minimum_required (VERSION 2.8)

project (nanocubesBenchmark)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(NOT COMPILER_SUPPORTS_CXX11)
       message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(Threads REQUIRED)

#
# Boost
#
find_package(Boost 1.48 REQUIRED COMPONENTS asio)
include_directories(${Boost_INCLUDE_DIRS})
message("---- Boost ----")
message("Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIRS}")
message("Boost_LIBRARIES:     ${Boost_LIBRARIES}")


include_directories(thirdparty/tclap)


if(APPLE)
   set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++" CACHE STRING "compile flags" FORCE)
   set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libc++" CACHE STRING "compile flags" FORCE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Deployment target for OSX" FORCE)
endif(APPLE)

if(UNIX)
   set(CMAKE_CXX_FLAGS "-std=c++11 -O3" CACHE STRING "compile flags" FORCE)
endif(UNIX)

add_subdirectory (thirdparty/tiny-process-library)
add_subdirectory (thirdparty/jsoncpp)
add_subdirectory (src)
