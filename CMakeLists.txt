cmake_minimum_required(VERSION 3.17)
project(equalizer)
# Some settings for release
#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_C_FLAGS /O2)
#set(CMAKE_CXX_FLAGS /O2)

set(CMAKE_CXX_STANDARD 17)

# add SDL lib
add_subdirectory(SDL/)
include_directories("./SDL/include")

# add SDL mixer
add_subdirectory(SDL_mixer/)
include_directories("./SDL_mixer/include")

set(FILE_DIALOG
        tinyfiledialogs/tinyfiledialogs.c tinyfiledialogs/tinyfiledialogs.h)
#        tinyfiledialogs/more_dialogs/tinyfd_moredialogs.c tinyfiledialogs/more_dialogs/tinyfd_moredialogs.h)

set(BUTTONS
        components/graphics/Buttons/Button.h components/graphics/Buttons/Button.cpp
        components/graphics/Buttons/Toggle_Button.h components/graphics/Buttons/Toggle_Button.cpp
        components/graphics/Buttons/PState_Button.h components/graphics/Buttons/PState_Button.cpp)


add_library(graphics STATIC
        components/graphics/drawing_stuff.h components/graphics/drawing_stuff.cpp
        components/graphics/equalizer_window.cpp components/graphics/equalizer_window.h
        components/graphics/FPS_Counter.h components/graphics/FPS_Counter.cpp
        components/graphics/DataInterpreter.h components/graphics/DataInterpreter.cpp
        components/graphics/RGBColor.h components/graphics/RGBColor.cpp
        components/graphics/Canvas.h components/graphics/Canvas.cpp
        components/graphics/Coord.h components/graphics/Coord.cpp
        ${BUTTONS}
        components/graphics/ppm_loader/file_exception.h)

add_executable(equalizer main.cpp ${FILE_DIALOG})

add_executable(window_example example_window.cpp)

add_executable(micro_example micro_example.cpp ${FILE_DIALOG})


add_executable(volume_graph volume_graph.cpp)

target_link_libraries(
        micro_example
        SDL2
        SDL2::SDL2main
        graphics
)

target_link_libraries(
        equalizer
        SDL2
        SDL2::SDL2main
        graphics
)
target_link_libraries(
        window_example
        SDL2
        SDL2::SDL2main
        graphics
)

target_link_libraries(
        volume_graph
        SDL2
        SDL2::SDL2main
        graphics
)


if (WIN32)
    set(SDL_SHARED SDL2d.dll)
endif (WIN32)
if (UNIX)
    set(SDL_SHARED libSDL2d.so)
endif (UNIX)

message(STATUS "Copying shared lib to out folder")

# Copy shared libs to out folder
add_custom_command(
        TARGET equalizer POST_BUILD                     # Adds a post-build event to equalizer
        COMMAND ${CMAKE_COMMAND} -E copy_if_different   # which executes "cmake - E copy_if_different..."
        "$<TARGET_FILE_DIR:equalizer>/SDL/${SDL_SHARED}"    # <--this is in-file
        $<TARGET_FILE_DIR:equalizer>                    # <--this is out-file path
)


# Copy example wav file to out folder
add_custom_command(
        TARGET equalizer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/files/example.wav"
        $<TARGET_FILE_DIR:equalizer>
)
