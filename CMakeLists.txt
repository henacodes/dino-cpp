cmake_minimum_required(VERSION 3.20)
project(DinoGame CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch Raylib automatically
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.0
)
FetchContent_MakeAvailable(raylib)

# Automatically find all .cpp files across src/ and its subdirectories
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(DinoGame ${SOURCES})

# Include header directories (allows #include "components/graphics/...")
target_include_directories(DinoGame PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(DinoGame PRIVATE raylib)