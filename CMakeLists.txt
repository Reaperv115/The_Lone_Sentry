cmake_minimum_required(VERSION 3.20)
project(Game_Engine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}-$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}-$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}-$<CONFIG>)

# GFLW
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Dependencies/GLFW/glfw3.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include")

#Engine
file(GLOB_RECURSE ENGINE_SOURCES "Engine/src/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "Engine/src/*.h")

set(GLAD_SOURCE "${CMAKE_SOURCE_DIR}/Engine/src/vendor/glad/glad.c")
set_source_files_properties(${GLAD_SOURCE} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

set(IMGUI_IMPL_SOURCES
    "${CMAKE_SOURCE_DIR}/Engine/src/vendor/imgui/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/vendor/imgui/imgui_impl_opengl3.cpp")

set_source_files_properties(${IMGUI_IMPL_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

source_group(TREE "${CMAKE_SOURCE_DIR}/Engine/src/" PREFIX "src" FILES ${ENGINE_SOURCES} ${ENGINE_HEADERS})



add_library(Engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GLAD_SOURCE})

target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/Engine/src)
target_include_directories(Engine PRIVATE
    ${CMAKE_SOURCE_DIR}/Engine/src/vendor
    ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include)

target_link_libraries(Engine PRIVATE glfw opengl32)

#precompiled header
target_precompile_headers(Engine PRIVATE Engine/src/gepch.h)

#Game(executable)
file(GLOB_RECURSE GAME_SOURCES "Game/src/*.cpp")
file(GLOB_RECURSE GAME_HEADERS "Game/src/*.h")

source_group(TREE "${CMAKE_SOURCE_DIR}/Game/src/" PREFIX "src" FILES ${GAME_SOURCES} ${GAME_HEADERS})

add_executable(Game ${GAME_SOURCES} ${GAME_HEADERS})

target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/Engine/src)

target_link_libraries(Game PRIVATE Engine)