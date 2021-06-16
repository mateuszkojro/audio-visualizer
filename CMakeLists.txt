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

#include_directories("${PROJECT_SOURCE_DIR}/SDL_ttf/")
#add_subdirectory(${PROJECT_SOURCE_DIR}/SDL_ttf/)


set(FILE_DIALOG
        tinyfiledialogs/tinyfiledialogs.c tinyfiledialogs/tinyfiledialogs.h)
#        tinyfiledialogs/more_dialogs/tinyfd_moredialogs.c tinyfiledialogs/more_dialogs/tinyfd_moredialogs.h)


add_library(graphics
        components/graphics/drawing_stuff.h components/graphics/drawing_stuff.cc
        components/graphics/equalizer_window.cc components/graphics/equalizer_window.h
        components/graphics/fps_counter.h components/graphics/fps_counter.cc
        components/graphics/rgb_color.h components/graphics/rgb_color.cc
        components/graphics/canvas.h components/graphics/canvas.cc
        components/graphics/coord.h components/graphics/coord.cc
        components/graphics/Buttons/canvas_button.h components/graphics/Buttons/canvas_button.cc
        components/graphics/ppm_loader/file_exception.h)

add_executable(equalizer main.cc ${FILE_DIALOG}
        audio_progress.h audio_progress.cc
        fourier_transform.h fourier_transform.cc
        audio_playback.h audio_playback.cc
        tiny_message.h
        )


target_link_libraries(
        equalizer
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
