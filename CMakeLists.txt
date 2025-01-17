cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(QFengine LANGUAGES C CXX VERSIO 0.0.1)

## Declare feature options present in cmake/feature.hh
option(ENABLE_VULKAN "Enable Vulkan renderer support" OFF)

## If possible, enable solution directories; this allows
## built-in pseudotargets like ALL_BUILD and ZERO_CHECK to
## be moved out of sight into a separate directory
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

## Ensure we are never building dependencies as dynamic
## libraries; we only use dynamic libraries for non-compiled
## third-party dependencies (such as SDL3 and maybe Discord-RPC);
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)

## Microsoft-vendored STL has been permissively licensed for quite
## a while, so it makes all the sense to statically link with it to
## avoid pulling redistributable installers alongside the project
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

## Output binaries into build root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

## Figure out compile-time configuration
configure_file("${CMAKE_CURRENT_LIST_DIR}/cmake/feature.hh.in" "${CMAKE_CURRENT_LIST_DIR}/cmake/feature.hh")
configure_file("${CMAKE_CURRENT_LIST_DIR}/cmake/version.hh.in" "${CMAKE_CURRENT_LIST_DIR}/cmake/version.hh")

add_subdirectory(data)
add_subdirectory(deps)
add_subdirectory(src)

## Copy information and compliance files into the package
install(FILES "${CMAKE_CURRENT_LIST_DIR}/LICENSE.txt" DESTINATION ".")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/README_DEPS.txt" DESTINATION ".")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/README.txt" DESTINATION ".")
