//
// Created by piotr233  on 16.04.2021.
//

// example of window with moving points, displayed using SDL create window
// and my genius algorithms

#include <chrono>  // chrono::system_clock
#include "components/graphics/equalizer_window.h"
#include "components/scheduler/p_scheduler.h"
#if false
int main(int argc, char *argv[]) {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);


    std::vector<int> data;
    for (int i = 0; i < 6; i++) { // generates some starting points for our graph
        data.push_back(rand() % WINDOW_HEIGHT);
    }

    std::vector<double> velocity_and_direction;
    for (int i = 0; i < data.size(); i++) {
        velocity_and_direction.push_back(rand() % 10 - 5); // to make it pretty
        // we generate paths and let points follow them with different speeds

    }


    auto *surface = new canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {255, 0, 0});
    std::thread visualizer_window(equalizer_window, surface); // thread containing window


    for(int i=0;i<10000;i++){
      //  auto *updated_surface = new canvas(WINDOW_WIDTH, WINDOW_HEIGHT, gen_rainbow(i,WINDOW_HEIGHT));

        //std::lock_guard<std::mutex> guard(surface_guard);
        surface->fill(gen_rainbow(i,WINDOW_HEIGHT));
        //std::lock_guard<std::mutex> unlock(surface_guard);

        if(i>=WINDOW_HEIGHT) i = 0;

        std::this_thread::sleep_for(std::chrono::milliseconds(36));

    }


    visualizer_window.join();

    return 0;
}
#else
int main(int argc, char *argv[]) {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);


    std::thread visualizer_window(equalizer_window, surface); // thread containing window

    visualizer_window.join();

    return 0;
}
#endif