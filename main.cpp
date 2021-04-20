//
// Created by studio25 on 07.04.2021.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <vector>
#include <SDL.h>
#include "drawing_stuff.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define PI 3.1415


std::vector<cord> gen_function_between_points(cord begin, cord end, bool flip) {

    std::vector<cord> generated_function;
    cord mid_point = {(begin.x + end.x) / 2, (begin.y + end.y) / 2};

    // a sin( bx + c) + d

    double a;
    a = begin.y > end.y ? begin.y - end.y : end.y - begin.y;
    a /= 2;
    int max_value /* distance between two points in x axis*/ = ((1 + end.x) - begin.x);

    double c = PI / 2;;
    double d = mid_point.y;
    if (begin.y > end.y) {

        a *= -1;

    }
    if(flip){
        a *= -1;
    }


    for (double i = begin.x; i <= end.x; i += 1) {

        double radian = i / max_value;
        radian *= PI;
        //  radian /=2;

        generated_function.push_back({(int) i,
                                      (int) (

                                              (a * (sin(radian + c)) + d)

                                      )});


    };
    return generated_function;


}

enum key_pressed {
    up,
    down,
    left,
    right,
    space,
    none

};


/// creates even spaced (on x axis) dot's from given y values
///\param values_to_be_drown vector of values tah will end up as y values in returned coordinates
///\param begin height on witch leftmost point will be, this point is only to make function look nice
///\param end height on witch rightmost point will be, this point is only to make function look nice
///\return vector of point's that will be represented as  "big dots"
std::vector<cord> create_points(int begin, int end, std::vector<int> &values_to_be_drown) {


    // distance between two point's in x axis
    int x_shift = WINDOW_WIDTH / (values_to_be_drown.size() + 1);

    std::vector<cord> dot_coordinates;
    // dot_coordinates.reserve(values_to_be_drown.size() + 2);

    dot_coordinates.emplace_back(0, begin);

    for (int i = 0; i < values_to_be_drown.size(); i++)
        dot_coordinates.emplace_back(x_shift * (i + 1), values_to_be_drown[i]);

    // to make sure that the last point is pixel perfect on the edge
    dot_coordinates.emplace_back(WINDOW_WIDTH - 2, end);


    return dot_coordinates;

}

/// \param values_to_be_drown vector containing y values of the point's tah will be drawn on the screen,
/// important thing all values must be in range <0;WINDOW_HEIGHT)
void window_with_line(std::vector<int> *values_to_be_drown) {

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;


    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, WINDOW_HEIGHT / 2);
    SDL_RenderPresent(renderer); // starting line

    auto time_start = std::chrono::steady_clock::now();


    while (true) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        {
            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);
            // 1s = 1000 milliseconds
            // 60 frame per second = 1 frame per 16,66  milliseconds


            //thread awaits the difference in time
            // in case that window will be generated and shown in time less than 1 frame, we wait the difference to always generate one frame per 60 s
            std::this_thread::sleep_for(std::chrono::milliseconds(
                    16 - std::chrono::duration_cast<std::chrono::milliseconds>(time_dif).count()));
            time_start = std::chrono::steady_clock::now();


            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer); // clear last frame

            //creates new set of point's
            std::vector<cord> p_positions = create_points(WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2, *values_to_be_drown);


            for (unsigned i = 0; i < p_positions.size() - 1; ++i) {

                draw_big_point(renderer, p_positions[i], 6);

                auto function_between_points = gen_function_between_points(p_positions[i], p_positions[i + 1],
                                                                           i % 2 == 0); // i'm giving out money for lucky someone who can tell me why i need this check

                for (auto j:function_between_points) {
                    draw_point(renderer, j);
                }

            }

            // TODO TEST THE GEN_FUNCTION
            // TODO DRAW IT
            SDL_RenderPresent(renderer);

        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

std::mutex mtx;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    std::vector<int> data;
    for (int i = 0; i < 7; i++) {
        data.push_back(rand() % WINDOW_HEIGHT);
    }

    std::thread window(window_with_line, &data);
    int frame = 0;

    while (1) {
        // mtx.lock();
        for (int i = 0; i < data.size(); i++) {
            if (i & 1) data[i] += 1;

            if (data[i] >= WINDOW_HEIGHT) data[i] = 0;

        }
//        for (int i = 0; i < 4; i++) {
//            data[i] += 1
//
//        }
        //  mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));

    }

    window.join();
    return 0;
}