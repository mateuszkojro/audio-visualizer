//
// Created by piotr233  on 16.04.2021.
//

// example of window with moving points, displayed using SDL create window
// and my genius algorithms

#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time

#include "components/graphics/equalizer_window.h"

std::string return_current_time_and_date() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}


std::mutex window_data;

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



    std::string message = "it's " + return_current_time_and_date() +
                          " sanetra still sucks ass";


    SDL_Surface* surface = new SDL_Surface();

    for (int i = 0; i < 100; i++) {
        Uint32* pixels = (Uint32*)surface -> pixels;

        pixels[(WINDOW_HEIGHT * surface -> w + i) ] = 255<<8;


                                    }



    /// FIXME change whole   equalizer_window function to be based of sdl_surface
    std::thread visualizer_window(equalizer_window,surface, &data); // thread containing window

    double frame = 0;
    while (frame < 36) { // for a minute
        frame += 0.01;
        window_data.lock();
        for (int i = 0; i < data.size(); i++) {
            data[i] += velocity_and_direction[i];
            if (data[i] > WINDOW_HEIGHT || data[i] < 0)
                velocity_and_direction[i] *= -1; // update position of all points
            // o the next position on path
        }
        window_data.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(7));

    }


    visualizer_window.join();

    return 0;
}