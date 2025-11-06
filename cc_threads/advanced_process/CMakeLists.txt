add_library(advanced_process SHARED
    advanced_process.cc
)

target_include_directories(advanced_process PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_PROJECT_SOURCE_DIR}/includes
)

target_link_libraries(advanced_process PRIVATE base_thread)

install(TARGETS advanced_process
    LIBRARY DESTINATION lib
)
