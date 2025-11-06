add_library(base_thread STATIC
    base_thread.cc
)

target_include_directories(base_thread PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_PROJECT_SOURCE_DIR}/includes
)

target_link_libraries(base_thread PUBLIC Threads::Threads)
