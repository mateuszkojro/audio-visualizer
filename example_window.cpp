//
// Created by piotr233  on 16.04.2021.
//

// example of window with moving points, displayed using SDL create window
// and my genius algorithms

#include <chrono>
#include "components/graphics/equalizer_window.h"

#if true

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

    std::mutex surface_guard;
    auto *surface = new canvas(WINDOW_WIDTH, WINDOW_HEIGHT, {0, 0, 0});
    std::thread window(equalizer_window, surface, std::ref(surface_guard)); // thread containing window


    for (int i = 0; i < 10000; i++) {
        {
            for (int i = 0; i < data.size(); i++) {

                data[i] += velocity_and_direction[i];
                if(data[i]>=WINDOW_HEIGHT || data[i]<0)
                    velocity_and_direction[i]*=-1;
            }
            std::lock_guard<std::mutex> guard(surface_guard);
            surface->clear();
            gen_new_frame(*surface, data);
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(15));

    }


    window.join();

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