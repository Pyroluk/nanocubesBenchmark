set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(WIN32)
	add_library(tinyprocesslib STATIC
	process.cpp
	process_win.cpp
	)
else()
	add_library(tinyprocesslib STATIC
	process.cpp
	process_unix.cpp
	)
endif()
