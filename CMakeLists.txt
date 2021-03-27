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

if (WIN32)
    set(SDL_SHARED SDL2d.dll)
endif (WIN32)
if (UNIX)
    set(SDL_SHARED libSDL2d.so)
endif (UNIX)

message(STATUS "Copying shared lib to out folder")
add_custom_command(
        TARGET equalizer POST_BUILD                     # Adds a post-build event to equalizer
        COMMAND ${CMAKE_COMMAND} -E copy_if_different   # which executes "cmake - E copy_if_different..."
        "$<TARGET_FILE_DIR:equalizer>/SDL/${SDL_SHARED}"    # <--this is in-file
        $<TARGET_FILE_DIR:equalizer>                    # <--this is out-file path
)