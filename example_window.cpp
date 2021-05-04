//
// Created by piotr233  on 16.04.2021.
//

// example of window with moving points, displayed using SDL create window
// and my genius algorithms

#include <chrono>
#include "components/graphics/equalizer_window.h"

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

 std::queue<std::vector<int> *> raw_bus;

 std::queue<std::thread *> thread_queue;
 std::queue<frame> analyzed_bus;


int main(int argc, char *argv[]) {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    for(int i=0;i<10;i++)
        raw_bus.push(new std::vector<int>({100,200,300,400,500}));


    std::thread thread_gen_data(main_gen_data);
    std::thread thread_analyze_data(main_analyze_data);

    std::thread thread_visualizer_window(equalizer_window); // thread containing window

    thread_visualizer_window.join();
    thread_analyze_data.join();
    thread_gen_data.join();
    return 0;
}

#endif