cmake_minimum_required(VERSION 3.14)
project(cc-threads LANGUAGES CXX)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Werror -Wextra -Wpedantic -Wno-non-virtual-dtor)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_subdirectory(base_thread)
add_subdirectory(simple_process)
add_subdirectory(advanced_process)
add_subdirectory(dispatcher)
add_subdirectory(app)
