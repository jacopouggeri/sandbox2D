cmake_minimum_required(VERSION 3.31)
project(sandbox2D)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Gather sources
file(GLOB_RECURSE SOURCE_FILES
        src/*.cpp
        src/*.h
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE /opt/homebrew/include)
target_link_directories(${PROJECT_NAME} PRIVATE /opt/homebrew/lib)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

# Assets include directory
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_DST "${CMAKE_CURRENT_BINARY_DIR}/assets")

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETS_DIR}" "${ASSETS_DST}"
        COMMENT "Copying assets to build folder"
)

# Warnings + sanitizers (GCC/Clang); clean MSVC setup too
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Wall;-Wextra;-Wpedantic
        >
        $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Debug>>:
        -fsanitize=address,undefined
        >
        $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Release>>:
        -O3
        >
)
target_link_options(${PROJECT_NAME} PRIVATE
        $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Debug>>:
        -fsanitize=address,undefined
        >
)

# MSVC alternative warnings (optional)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
endif()