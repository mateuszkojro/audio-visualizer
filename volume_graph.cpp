//
// Created by piotr233  on 16.04.2021.
//


#include <chrono>
#include "components/graphics/equalizer_window.h"
#include "components/graphics/Button.h"


int main(int argc, char *argv[]) {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);


    std::mutex surface_guard;

    auto *surface = new Canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {0, 0, 0});

    std::thread window(equalizer_window, surface, std::ref(surface_guard)); // thread containing window

    surface->fill({0, 0, 0});
    Button play(30, 30, 100, 50);

    int bar_head_position = 0;
    int bar_height = 10;/// how many pixels from the bottom the bar will be displayed
    int line_thickness = 5;

    std::chrono::milliseconds audio_lenght = std::chrono::milliseconds(60000);

    for (int i = 0; i < WINDOW_WIDTH; i++) {

        int j = 0;
        for (; j < line_thickness; j++) {
            surface->draw_point({i, WINDOW_HEIGHT - j - bar_height}, 5, {180, 180, 180});
        }

    }

    int temporary_high = 0;
    double trend = 0;


    while (bar_head_position != WINDOW_WIDTH) {
        /// draw current "volume level" for now it's random generated it wll change in the future
        surface->draw_point({bar_head_position, WINDOW_HEIGHT / 2 - temporary_high}, 4,
                            gen_rainbow(WINDOW_HEIGHT / 2 - temporary_high, WINDOW_HEIGHT));

        /// to make it pretty I draw it emmm like this;
        /// it's only made to make it pretty
        surface->draw_point({bar_head_position, WINDOW_HEIGHT / 2 + temporary_high}, 4,
                            gen_rainbow(WINDOW_HEIGHT / 2 + temporary_high, WINDOW_HEIGHT));

        surface->draw_button(play.getImage(), {(int) play.getPy(), (int) play.getPx()});

        /// generate change in time

        temporary_high += trend;


        temporary_high = (temporary_high / 3);
//        trend /=1.005;

        /// small changes in trend
        if (bar_head_position % 8 == 2) trend += (rand() % 20) - 10;

        /// very small changes in trend (about the size of penis that mati has to work around)
        trend += (rand() % 10) - 5;




        /// update line of progress bar
        for (int i = 0; i < bar_head_position; i++) {
            int j = 0;
            for (; j < line_thickness; j++) {
                surface->draw_point({i, WINDOW_HEIGHT - j - bar_height}, 5, {0, 210, 0});
            }
        }
        std::this_thread::sleep_for(audio_lenght / WINDOW_WIDTH);
        /// move the barr one pixel to the right;
        bar_head_position++;
    }

    window.join();

    return 0;
}

