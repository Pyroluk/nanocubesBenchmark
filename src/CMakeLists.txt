add_executable(nanocubesBenchmark nanocubesBenchmark.cc stopwatch.cc)
target_link_libraries (nanocubesBenchmark
LINK_PUBLIC
tinyprocesslib
jsoncpp
${Boost_LIBRARIES}
${CMAKE_THREAD_LIBS_INIT})