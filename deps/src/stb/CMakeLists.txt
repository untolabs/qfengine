add_library(stb STATIC "${CMAKE_CURRENT_LIST_DIR}/stb.c")
target_compile_definitions(stb PUBLIC STBI_NO_STDIO STBI_WRITE_NO_STDIO)
target_include_directories(stb PUBLIC "${DEPS_INCLUDE_DIR}")
set_target_properties(stb PROPERTIES FOLDER deps)

if(WIN32)
    target_compile_definitions(stb PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
