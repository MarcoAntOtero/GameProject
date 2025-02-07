cmake_minimum_required(VERSION 3.21)  # Use a stable version
project(test)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

# Fetch SFML from GitHub
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)  # C++17 is sufficient

# Define executable
add_executable(test main.cpp
        Game.h
        Game.cpp
        Player.cpp
        Player.h
        Enemy.cpp
        Enemy.h)

# Link SFML libraries correctly
target_link_libraries(test PRIVATE sfml-graphics sfml-window sfml-system)