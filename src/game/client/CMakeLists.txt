add_executable(qf_client
    "${CMAKE_CURRENT_LIST_DIR}/opengl/gl_init.cc"
    "${CMAKE_CURRENT_LIST_DIR}/opengl/gl_level.cc"
    "${CMAKE_CURRENT_LIST_DIR}/opengl/gl_main.cc"
    "${CMAKE_CURRENT_LIST_DIR}/opengl/ref_opengl.hh"
    "${CMAKE_CURRENT_LIST_DIR}/game.cc"
    "${CMAKE_CURRENT_LIST_DIR}/game.hh"
    "${CMAKE_CURRENT_LIST_DIR}/globals.cc"
    "${CMAKE_CURRENT_LIST_DIR}/globals.hh"
    "${CMAKE_CURRENT_LIST_DIR}/main.cc"
    "${CMAKE_CURRENT_LIST_DIR}/precompiled.hh"
    "${CMAKE_CURRENT_LIST_DIR}/refresher.cc"
    "${CMAKE_CURRENT_LIST_DIR}/refresher.hh"
    "${CMAKE_CURRENT_LIST_DIR}/video_mode.hh")
target_compile_features(qf_client PUBLIC cxx_std_17)
target_include_directories(qf_client PUBLIC "${DEPS_INCLUDE_DIR}")
target_include_directories(qf_client PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(qf_client PUBLIC "${PROJECT_SOURCE_DIR}/src/game")
target_precompile_headers(qf_client PRIVATE "${CMAKE_CURRENT_LIST_DIR}/precompiled.hh")
target_link_libraries(qf_client PUBLIC glad SDL3 qf_shared)
