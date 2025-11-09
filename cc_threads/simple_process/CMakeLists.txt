add_library(simple_process SHARED
    simple_process.cc
)

target_include_directories(simple_process PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(simple_process PRIVATE
    base_thread
)

install(TARGETS simple_process
    LIBRARY DESTINATION lib
)

set_target_properties(simple_process PROPERTIES OUTPUT_NAME "simple_process")
