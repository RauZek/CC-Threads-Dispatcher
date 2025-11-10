add_library(base_thread STATIC
    base_thread.cc
)

target_include_directories(base_thread PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(base_thread PUBLIC Threads::Threads)

install(TARGETS base_thread
    ARCHIVE DESTINATION lib
)

set_target_properties(base_thread PROPERTIES OUTPUT_NAME "base_thread")
