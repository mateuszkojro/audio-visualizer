//
// Created by studio25 on 07.04.2021.
//
#include <iostream>
#include <thread>
#include <cmath>
#include <conio.h>
#include <vector>
#include <SDL.h>
#include "drawing_stuff.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define PI 3.1415




// todo 1) make them graphs represent something
// todo 2) make the mouse comprtoller


std::vector<double> gen_function_between_points(cord begin, cord end) {

    std::vector<double> function;
    cord mid_point = {begin.x + end.x / 2, begin.y + end.y / 2};

    // soo
    // polynomial takes form ax^3+bx^2+cx+d
    // but actually we need shape closer to ax^3+bx+d
    // right now we can declare b coz it's always 0
    // d is simply shift up or down for whole function,
    // and since mid_point is in the middle we  can move function up or down to midpoint
    // so d = midpoint.y

    // what's left is a and c
    // and we still have two point's to make system of equations
    // with two equations and two unknowns simple!
    //

    function.push_back(mid_point.y);        // d
    function.push_back(1);                  // c <- for now just to keep vector at bay
    function.push_back(0);                  // b
    function.push_back(1);                  // a <- for now just to keep vector at bay

    // ok call it black box but
    //        xy1 - yx1
    // a = ----------------
    //      xx1(x1^2 - x^2)

    // c = y-(ax)^3 / x

    function[3] = (begin.x*end.y - begin.y*end.x) / (begin.x*end.x)*(end.x*end.x - begin.x*begin.x); // a
    function[1] =( begin.y - pow((function[3]*begin.x),3)) / begin.x; // c


    return function;
}


enum key_pressed {
    up,
    down,
    left,
    right,
    space,
    none


};


std::vector<cord> data;


int window_with_line_a(void *ptr_to_data) {

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


    double amplituda = 150;
    double okres = 0.5;
    int k = 0;
    int middle = WINDOW_HEIGHT / 2;

    key_pressed current_key = none;
    while (true) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (current_key != up) amplituda += 1.1;
                    current_key = up;
                    break;

                case SDLK_DOWN:
                    if (current_key != down) amplituda -= 1.1;
                    current_key = down;
                    break;

                case SDLK_LEFT:
                    if (current_key != left) okres -= 0.01;
                    current_key = left;
                    break;

                case SDLK_RIGHT:
                    if (current_key != right) okres += 0.01;
                    current_key = right;
                    break;
                case SDLK_SPACE:
                    if (current_key != space) {
                        std::cout << "amplituda: " << amplituda << "\t" << "okres: " << okres << "\n";
                    }
                    current_key = space;
                    break;
                default:
                    current_key = none;
                    break;
            }
        }
        {
            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);
            // 1s = 1000 milliseconds
            // 60 frame per second = 1 frame per 16,66  milliseconds

            if (time_dif.count() > 17) {
                k++;
                time_start = std::chrono::steady_clock::now();
                current_key = none;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);


                // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

                for (int i = 0; i < WINDOW_WIDTH * (1 / okres); ++i) {
                    cord current_pixel_position = {
                            (int) (i * okres),
                            (int) (middle + cos(PI * i * 50 * 2) * amplituda)
                    };

                    rgb_color current_pixel_color = gen_rainbow(current_pixel_position.y, WINDOW_HEIGHT);
                    SDL_SetRenderDrawColor(renderer, current_pixel_color.r, current_pixel_color.g,
                                           current_pixel_color.b, 255);


                    //center

                    SDL_RenderDrawPoint(renderer, current_pixel_position.x, current_pixel_position.y);


                    // up
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x, current_pixel_position.y - 2);
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x, current_pixel_position.y - 1);

                    //down
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x, current_pixel_position.y + 1);
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x, current_pixel_position.y + 2);
                    // left
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x - 2, current_pixel_position.y);
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x - 1, current_pixel_position.y);
                    //right
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x + 1, current_pixel_position.y);
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x + 2, current_pixel_position.y);
                    // corners
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x - 1, current_pixel_position.y - 1);
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x - 1, current_pixel_position.y + 1);
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x + 1, current_pixel_position.y + 1);
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x + 1, current_pixel_position.y - 1);


                }
                SDL_RenderPresent(renderer);
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 18;
}

int window_with_line(void *ptr_to_data) {

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


    int k = 0;
    int middle = WINDOW_HEIGHT / 2;

    cord point_on_the_left_margin = {
            0,
            WINDOW_HEIGHT / 2
    };
    cord point_on_the_right_margin = {
            WINDOW_WIDTH-1,
            WINDOW_HEIGHT / 2
    };



    while (true) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;

        {
            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);
            // 1s = 1000 milliseconds
            // 60 frame per second = 1 frame per 16,66  milliseconds

            if (time_dif.count() > 16) {
                time_start = std::chrono::steady_clock::now();


                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer); // clear last frame

                // TODO TEST THE GEN_FUNCTION
                // TODO DRAW IT





                SDL_RenderPresent(renderer);
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 18;
}


int main(int argc, char *argv[]) {

    int *ptr_to_data;
    data.push_back({200, 200});
    data.push_back({200 * 2, 200 * 2});
    data.push_back({200 * 3, 200 * 3});
    data.push_back({200 * 4, 200 * 4});

    SDL_Thread *mainthread;

    mainthread = SDL_CreateThread(window_with_line, "idk", (void *) ptr_to_data);


    int *thread_status;
    SDL_WaitThread(mainthread, thread_status);

    printf("Thread returned value: %d\n", *thread_status);

    return 0;
}