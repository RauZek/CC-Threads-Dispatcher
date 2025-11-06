add_library(simple_process SHARED
    simple_process.cc
)

target_include_directories(simple_process PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_PROJECT_SOURCE_DIR}/includes
)

target_link_libraries(simple_process PRIVATE base_thread)

install(TARGETS simple_process
    LIBRARY DESTINATION lib
)
