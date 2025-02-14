add_executable(qf_client
    "${CMAKE_CURRENT_LIST_DIR}/opengl/opengl_imgui.cc"
    "${CMAKE_CURRENT_LIST_DIR}/opengl/opengl_level.cc"
    "${CMAKE_CURRENT_LIST_DIR}/opengl/opengl_video.cc"
    "${CMAKE_CURRENT_LIST_DIR}/opengl/opengl.cc"
    "${CMAKE_CURRENT_LIST_DIR}/opengl/opengl.hh"
    "${CMAKE_CURRENT_LIST_DIR}/display.cc"
    "${CMAKE_CURRENT_LIST_DIR}/display.hh"
    "${CMAKE_CURRENT_LIST_DIR}/game.cc"
    "${CMAKE_CURRENT_LIST_DIR}/game.hh"
    "${CMAKE_CURRENT_LIST_DIR}/globals.cc"
    "${CMAKE_CURRENT_LIST_DIR}/globals.hh"
    "${CMAKE_CURRENT_LIST_DIR}/input.cc"
    "${CMAKE_CURRENT_LIST_DIR}/input.hh"
    "${CMAKE_CURRENT_LIST_DIR}/main.cc"
    "${CMAKE_CURRENT_LIST_DIR}/precompiled.hh"
    "${CMAKE_CURRENT_LIST_DIR}/render_api.cc"
    "${CMAKE_CURRENT_LIST_DIR}/render_api.hh")
target_compile_features(qf_client PUBLIC cxx_std_17)
target_include_directories(qf_client PUBLIC "${DEPS_INCLUDE_DIR}")
target_include_directories(qf_client PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(qf_client PUBLIC "${PROJECT_SOURCE_DIR}/src/game")
target_precompile_headers(qf_client PRIVATE "${CMAKE_CURRENT_LIST_DIR}/precompiled.hh")
target_link_libraries(qf_client PUBLIC glad imgui imgui_opengl3 imgui_SDL3 SDL3 qf_shared)
