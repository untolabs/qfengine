add_library(qf_shared STATIC
    "${CMAKE_CURRENT_LIST_DIR}/const.hh"
    "${CMAKE_CURRENT_LIST_DIR}/content.cc"
    "${CMAKE_CURRENT_LIST_DIR}/content.hh"
    "${CMAKE_CURRENT_LIST_DIR}/game.cc"
    "${CMAKE_CURRENT_LIST_DIR}/game.hh"
    "${CMAKE_CURRENT_LIST_DIR}/globals.cc"
    "${CMAKE_CURRENT_LIST_DIR}/globals.hh"
    "${CMAKE_CURRENT_LIST_DIR}/input.hh"
    "${CMAKE_CURRENT_LIST_DIR}/precompiled.hh")
target_compile_features(qf_shared PUBLIC cxx_std_17)
target_include_directories(qf_shared PUBLIC "${DEPS_INCLUDE_DIR}")
target_include_directories(qf_shared PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(qf_shared PUBLIC "${PROJECT_SOURCE_DIR}/src/game")
target_precompile_headers(qf_shared PRIVATE "${CMAKE_CURRENT_LIST_DIR}/precompiled.hh")
target_link_libraries(qf_shared PUBLIC core)
