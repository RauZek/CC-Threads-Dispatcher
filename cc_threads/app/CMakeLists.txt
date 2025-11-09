add_executable(app
    app.cc
)

target_link_libraries(app PRIVATE
    dispatcher
    Threads::Threads
)

set_target_properties(app PROPERTIES
    INSTALL_RPATH "$ORIGIN/../lib"
    INSTALL_RPATH_USE_LINK_PATH TRUE
)

install(TARGETS app
    RUNTIME DESTINATION bin
)
