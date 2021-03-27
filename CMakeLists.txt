cmake_minimum_required(VERSION 3.17)
project(equalizer)

set(CMAKE_CXX_STANDARD 17)

# add SDL lib
add_subdirectory(SDL/)
include_directories("./SDL/include")

# add SDL mixer
add_subdirectory(SDL_mixer/)
include_directories("./SDL_mixer/include")

add_executable(equalizer main.cpp)

target_link_libraries(
        equalizer
        SDL2
        SDL2::SDL2main
)
