add_library(dispatcher SHARED
    dispatcher.cc
)

target_include_directories(dispatcher PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(dispatcher PUBLIC
    base_thread
    Threads::Threads
    dl
)

install(TARGETS dispatcher
    LIBRARY DESTINATION lib
)

set_target_properties(dispatcher PROPERTIES OUTPUT_NAME "dispatcher")
