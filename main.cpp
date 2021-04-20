//
// Created by piotr233  on 16.04.2021.
//



#include "components/graphics/equalizer_window.h"


int main(int argc, char *argv[]) {


    std::vector<int> data;
    for (int i = 0; i < 5; i++) { // generates some starting points for our graph
        data.push_back(WINDOW_HEIGHT/2);
    }

    std::thread window(equalizer_window, &data); // thread containing window



    window.join();
    return 0;
}