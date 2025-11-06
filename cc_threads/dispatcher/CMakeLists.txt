add_library(dispatcher SHARED
    dispatcher.cc
)

target_include_directories(dispatcher PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_PROJECT_SOURCE_DIR}/includes
)

target_link_libraries(dispatcher PRIVATE
    base_thread
    Threads::Threads
    dl
)

install(TARGETS dispatcher
    LIBRARY DESTINATION lib
)
