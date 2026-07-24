cmake_minimum_required(VERSION 3.20)
project(DinoGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Raylib automatically
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.0
)
FetchContent_MakeAvailable(raylib)

# Include header directories
include_directories(include)

# Gather all .cpp files in src/ and its subdirectories
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(DinoGame ${SOURCES})
target_link_libraries(DinoGame PRIVATE raylib)
