//
// Created by piotr233  on 16.04.2021.
//


#include <chrono>
#include "components/graphics/equalizer_window.h"


int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);


    std::mutex surface_guard;

    auto *surface = new canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {0, 0, 0});

    std::thread window(equalizer_window, surface, std::ref(surface_guard)); // thread containing window

    surface->fill({0, 0, 0});


    int bar_head_position = 0;
    int bar_height = 10;/// how many pixels from the bottom the bar will be displayed
    int line_thickness = 5;

    std::chrono::milliseconds audio_lenght = std::chrono::milliseconds (60000);

    for(int i=0;i<WINDOW_WIDTH;i++){

        int  j=0;
        for (;j < line_thickness; j++) {
            surface->draw_point({i,WINDOW_HEIGHT - j - bar_height}, 5, {180, 180, 180});
        }

    }

    while (bar_head_position != WINDOW_WIDTH) {
        /// update line
        for (int i = 0; i < bar_head_position; i++) {
          int  j=0;
            for (;j < line_thickness; j++) {
                surface->draw_point({i,WINDOW_HEIGHT - j - bar_height}, 5, {0, 210, 0});
            }
        }
        std::this_thread::sleep_for(audio_lenght/WINDOW_WIDTH);
        /// move the barr one pixel to the right;
        bar_head_position++;
    }

    window.join();

    return 0;
}

