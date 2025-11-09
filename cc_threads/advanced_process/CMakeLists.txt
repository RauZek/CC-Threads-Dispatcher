add_library(advanced_process SHARED
    advanced_process.cc
)

target_include_directories(advanced_process PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(advanced_process PRIVATE
    base_thread
)

install(TARGETS advanced_process
    LIBRARY DESTINATION lib
)

set_target_properties(advanced_process PROPERTIES OUTPUT_NAME "advanced_process")
