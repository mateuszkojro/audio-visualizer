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

std::vector<double> interpolate_your_ass_you_bitch(cord begin, cord end, std::vector<cord> data){

    // number of points
    int p_number = 2 + data.size();
    int polynomial_degree = p_number-1;

    // so my polynomial will simply be vector of coresponding things
    std::vector<double> function;

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

            if (time_dif.count() > 17 ) {
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

                cord current_pixel_position = { // draw dot on the left
                        0,
                        WINDOW_HEIGHT / 2
                };
                draw_big_point(renderer, current_pixel_position, 6);

                int temp_x = 0; // used to connect first dot to left margin
                int temp_y = WINDOW_HEIGHT / 2;


                for (int i = 0; i < data.size(); i++) {

                    current_pixel_position = {
                            data[i].x,
                            data[i].y
                    };
                    draw_big_point(renderer, current_pixel_position, 6);






                     temp_x = data[i].x;
                     temp_y =  data[i].y;
                }

                current_pixel_position = {// draw dot on the right
                        0,
                        WINDOW_HEIGHT * WINDOW_WIDTH - WINDOW_HEIGHT / 2

                };
                draw_big_point(renderer, current_pixel_position, 6);

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