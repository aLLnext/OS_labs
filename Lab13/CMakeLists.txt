project(Lab13 C)

find_package (Threads)

add_executable(Lab13_queue queue.c utils.c)
add_executable(Lab13_queue_mutex queue_mutex.c utils.c)
add_executable(Lab13_queue_cond queue_cond.c utils.c)

target_link_libraries (Lab13_queue ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab13_queue_mutex ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab13_queue_cond ${CMAKE_THREAD_LIBS_INIT})