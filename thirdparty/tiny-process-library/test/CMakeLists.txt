include_directories(..)

add_executable(open_close_test open_close_test.cpp ${process_source_files})
target_link_libraries(open_close_test ${CMAKE_THREAD_LIBS_INIT})

add_executable(multithread_test multithread_test.cpp ${process_source_files})
target_link_libraries(multithread_test ${CMAKE_THREAD_LIBS_INIT})

add_test(open_close_test open_close_test)
add_test(multithread_test multithread_test)
