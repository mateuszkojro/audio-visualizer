//
// Created by piotr233  on 16.04.2021.
//


#include <chrono>
#include "components/graphics/equalizer_window.h"


int main(int argc, char *argv[]) {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);


    std::mutex surface_guard;

    auto *surface = new Canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {0, 0, 0});

    std::vector<Button> butt_vec ;
    ///fixmy in button for some reason height and width are flipped

    Button backward(0 , WINDOW_HEIGHT-35, 35, 40);
    backward.set_debug_color({0,255,0});
    Button play(40 , WINDOW_HEIGHT-35, 35, 40);

    Button forward(80 , WINDOW_HEIGHT-35, 35, 40);
    forward.set_debug_color({0,0,255});

    butt_vec.push_back(backward);
    butt_vec.push_back(play);
    butt_vec.push_back(forward);

    std::thread window(equalizer_window, surface, std::ref(surface_guard), butt_vec); // thread containing window

    surface->fill({0, 0, 0});

    int bar_head_position = 0;
    int bar_height = 40;/// how many pixels from the bottom the bar will be displayed
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

        for(auto i:butt_vec)
            surface->draw_button(i.getImage(), {(int) i.getPy(), (int) i.getPx()});

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

