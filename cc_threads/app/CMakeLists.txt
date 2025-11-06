add_executable(app
    app.cc
)

target_include_directories(app PUBLIC
    ${CMAKE_PROJECT_SOURCE_DIR}/includes
)

target_link_libraries(app PRIVATE
    dispatcher
    Threads::Threads
)

install(TARGETS app
    RUNTIME DESTINATION bin
)
