//
// Created by piotr233  on 16.04.2021.
//



#include "components/graphics/equalizer_window.h"
#include <numeric>
#include <numbers>
#include <complex>

std::complex<double_t> get_value_for_freq(double_t freq, std::vector<uint16_t> data) {
    std::complex<double_t> result;
    const double_t delta_t = 2.27E-5;

    for (int itr = 0; itr < data.size() - 1; itr++) {
        double_t avg_value = delta_t * (data[itr] + data[itr + 1]) / 2.0;
        std::complex<double_t> exponent = std::exp(
                std::complex<double_t>(0, static_cast<const double_t>(-2 * PI * 1i * freq * ((itr + itr + 1) / 2.0))));
        result += avg_value * exponent;
    }

    return result;
}


int main(int argc, char *argv[]) {


    std::vector<int> data;
    for (int i = 0; i < 40; i++) { // generates some starting points for our graph
        data.push_back(rand() % WINDOW_HEIGHT);
    }

    std::vector<double> velocity_and_direction;
    for (int i = 0; i < data.size(); i++) {
        velocity_and_direction.push_back(rand() % 36 - 18); // to make it pretty
                                                            // we generate paths and let points follow them with different speeds

    }

    std::thread window(window_with_line, &data); // thread containing window

    double frame = 0;
    while (frame < 36) { // for a minute
        frame += 0.01;
        for (int i = 0; i < data.size(); i++) {
            data[i] += velocity_and_direction[i];
            if (data[i] > WINDOW_HEIGHT || data[i] < 0) velocity_and_direction[i] *= -1; // update position of all points
                                                                                            // o the next position on path
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));

    }

    window.join();
    return 0;
}