//
// Created by piotr233  on 16.04.2021.
//

// example of window with moving points, displayed using SDL create window
// and my genius algorithms

#include <chrono>
#include "components/graphics/equalizer_window.h"

#if true

enum effect {
    classic_function,
    weird_time_play,
    bateria,
    square_head,
    kaszuby

};

int main(int argc, char *argv[]) {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);


    std::vector<int> data;
    for (int i = 0; i < 10; i++) { // generates some starting points for our graph
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

    effect current_effect = kaszuby;


    switch (current_effect) {
        case classic_function: {
            for (int i = 0; i < 10000; i++) {
                {
                    for (int i = 0; i < data.size(); i++) {
                        data[i] += velocity_and_direction[i];
                        if (data[i] >= WINDOW_HEIGHT || data[i] < 0)
                            velocity_and_direction[i] *= -1;
                    }
                    {
                        std::lock_guard<std::mutex> guard(surface_guard);
                        surface->clear();
                        draw_function(*surface, data, true, false, true);

                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
            }
        }
            break;
        case weird_time_play: {
            std::queue<std::vector<int>> history_of_the_points;
            for (int i = 0; i < 10000; i++) {
                {
                    for (int i = 0; i < data.size(); i++) {

                        data[i] += velocity_and_direction[i];
                        if (data[i] >= WINDOW_HEIGHT || data[i] < 0)
                            velocity_and_direction[i] *= -1;
                    }
                    history_of_the_points.push(data);
                    if (history_of_the_points.size() > 50) {
                        surface->set_primary_color({0, 0, 0});
                        draw_function(*surface, history_of_the_points.front(), false, true, true);
                        history_of_the_points.pop();
                    }
                    draw_function(*surface, data, false, false, true);
                    std::lock_guard<std::mutex> guard(surface_guard);
                    //surface->clear();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
            }
        }
            break;
        case bateria: {
            for (int i = 0; i < 10000; i++) {
                {
                    for (int i = 0; i < data.size(); i++) {

                        data[i] += velocity_and_direction[i];
                        if (data[i] >= WINDOW_HEIGHT || data[i] < 0)
                            velocity_and_direction[i] *= -1;
                    }

                    {
                        std::lock_guard<std::mutex> guard(surface_guard);
                        surface->clear();
                        draw_function(*surface, data, true, false, true);
                        auto data2 = data;
                        for(auto &i:data2) i = WINDOW_HEIGHT-i;
                        draw_function(*surface, data2, true, false, true);
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(15));
                }
            }
        }
        break;
        case square_head:{
            for (int i = 0; i < 10000; i++) {
                {
                    for (int i = 0; i < data.size(); i++) {

                        data[i] += velocity_and_direction[i];
                        if (data[i] >= WINDOW_HEIGHT || data[i] < 0)
                            velocity_and_direction[i] *= -1;
                    }

                    {
                        std::lock_guard<std::mutex> guard(surface_guard);
                        surface->clear();
                        draw_levels(*surface, data, true, false );

                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(15));
                }
            }


        }
        break;
        case kaszuby:{

            for (int i = 0; i < 10000; i++) {
                {
                    for (int i = 0; i < data.size(); i++) {

                        data[i] += velocity_and_direction[i];
                        if (data[i] >= WINDOW_HEIGHT || data[i] < 0)
                            velocity_and_direction[i] *= -1;
                    }

                    {
                        std::lock_guard<std::mutex> guard(surface_guard);
                        surface->clear();
                        draw_function_but_fill_it_below(*surface, data, true, false ,true);

                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(15));
                }
            }

        }

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