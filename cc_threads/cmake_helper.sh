#!/bin/bash

PROJECT_ROOT=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

function cc_threads-clean(){
    rm -rf "${PROJECT_ROOT}/build"
    rm -rf "${PROJECT_ROOT}/install"
    rm -rf "${PROJECT_ROOT}/debug"
    echo "Clean Assignment."
}

function cc_threads-configure() {
    mkdir -p "${PROJECT_ROOT}/build"
    (
        cd "${PROJECT_ROOT}/build"

        cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON \
              -DCMAKE_INSTALL_PREFIX:PATH="${PROJECT_ROOT}/install/usr" \
              "${PROJECT_ROOT}" && \
            echo "Assignment Configured!"
    )
}

function cc_threads-compile () {
    (
        cd "${PROJECT_ROOT}/build"

        cmake --build . && \
            echo "Assignment Compiled!"
    )
}

function cc_threads-install() {
    (
        cd "${PROJECT_ROOT}/build"

        cmake --build . --target install && \
            echo "Assignment Installed Successfully!"
    )
}

function cc_threads-install-debug() {
    (
        cd "${PROJECT_ROOT}/build"

        cmake --build . --target install && \
            echo "Assignment Debug Version Installed!"
    )
}


function cc_threads-install-release() {
    (
        cd "${PROJECT_ROOT}/build"

        cmake --build . --target install && \
            echo "Assignment Release Version Installed!"
    )
}

function cc_threads-incremental-build() {
    cc_threads-configure && cc_threads-compile && cc_threads-install-release
    echo "You Choose the Incremental Build Installation of the Assignment!"
}

function cc_threads-clean-build() {
    cc_threads-clean && cc_threads-incremental-build
    echo "You Choose the Clean Build Installation of the Assignment"
}

function cc_threads-test () {
    (
        LD_LIBRARY_PATH="${PROJECT_ROOT}/install/usr/lib" \

        "${PROJECT_ROOT}/install/usr/bin/cc_threads_cmake" "$@"
    )
}

echo "-------------Cmake----------------"
echo "command: cc_threads-incremental-build"
echo    "To build the project's build."
echo "----------------------------------"
echo "command: cc_threads-clean-build"
echo    "To clean the project's build."
echo "----------------------------------"
echo "command: cc_threads-install-debug"
echo    "To install debugging's version."
echo "----------------------------------"
echo "command: cc_threads-test"
echo    "Runs the executable file."
echo "----------------------------------"
