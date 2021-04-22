//
// Created by piotr233  on 16.04.2021.
//

// example of window with moving points, displayed using SDL create window
// and my genius algorithms

#include "components/graphics/equalizer_window.h"

std::mutex window_data;
int main(int argc, char *argv[]) {
    srand(time(NULL));

    std::vector<int> data;
    for (int i = 0; i < 6; i++) { // generates some starting points for our graph
        data.push_back(rand() % WINDOW_HEIGHT);
    }

    std::vector<double> velocity_and_direction;
    for (int i = 0; i < data.size(); i++) {
        velocity_and_direction.push_back(rand() % 10 - 5); // to make it pretty
                                                        // we generate paths and let points follow them with different speeds

    }

    std::thread window(equalizer_window, &data); // thread containing window


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


    window.join();

    return 0;
}