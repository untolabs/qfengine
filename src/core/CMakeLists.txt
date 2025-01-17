add_library(core STATIC
    "${CMAKE_CURRENT_LIST_DIR}/assert.hh"
    "${CMAKE_CURRENT_LIST_DIR}/constexpr.hh"
    "${CMAKE_CURRENT_LIST_DIR}/exception.cc"
    "${CMAKE_CURRENT_LIST_DIR}/exception.hh"
    "${CMAKE_CURRENT_LIST_DIR}/floathacks.hh"
    "${CMAKE_CURRENT_LIST_DIR}/logging.cc"
    "${CMAKE_CURRENT_LIST_DIR}/logging.hh"
    "${CMAKE_CURRENT_LIST_DIR}/matrix4x4base.hh"
    "${CMAKE_CURRENT_LIST_DIR}/matrix4x4f.cc"
    "${CMAKE_CURRENT_LIST_DIR}/matrix4x4f.hh"
    "${CMAKE_CURRENT_LIST_DIR}/precompiled.hh"
    "${CMAKE_CURRENT_LIST_DIR}/vector2base.hh"
    "${CMAKE_CURRENT_LIST_DIR}/vector2f.cc"
    "${CMAKE_CURRENT_LIST_DIR}/vector2f.hh"
    "${CMAKE_CURRENT_LIST_DIR}/vector3angles.cc"
    "${CMAKE_CURRENT_LIST_DIR}/vector3angles.hh"
    "${CMAKE_CURRENT_LIST_DIR}/vector3base.hh"
    "${CMAKE_CURRENT_LIST_DIR}/vector3f.cc"
    "${CMAKE_CURRENT_LIST_DIR}/vector3f.hh"
    "${CMAKE_CURRENT_LIST_DIR}/vector4base.hh"
    "${CMAKE_CURRENT_LIST_DIR}/vector4f.hh")
target_compile_features(core PUBLIC cxx_std_17)
target_include_directories(core PUBLIC "${DEPS_INCLUDE_DIR}")
target_include_directories(core PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_precompile_headers(core PRIVATE "${CMAKE_CURRENT_LIST_DIR}/precompiled.hh")
target_link_libraries(core PUBLIC physfs stb)

if(WIN32)
    target_compile_definitions(core PUBLIC _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(core PUBLIC _USE_MATH_DEFINES)
    target_compile_definitions(core PUBLIC NOMINMAX)
endif()

configure_file("${CMAKE_CURRENT_LIST_DIR}/feature.hh.in" "${CMAKE_CURRENT_LIST_DIR}/feature.hh")
configure_file("${CMAKE_CURRENT_LIST_DIR}/version.hh.in" "${CMAKE_CURRENT_LIST_DIR}/version.hh")
