//
// Created by pc on 23.04.2021.
//


#include  "SDL.h"
#include <chrono>

#include <iostream>
#include <thread>
#include "components/graphics/canvas.h"

#define BYTE *8
// this well be used by time measurement equipment
std::chrono::time_point<std::chrono::system_clock> t1, t2;

#define START_CLOCK t1 = std::chrono::system_clock::now();
#define STOP_CLOCK  t2 = std::chrono::system_clock::now();
#define SHOW_TIME  std::cout << "Elapsed time in microseconds: " \
                             << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() \
                             << " µs" << std::endl; std::cout << "Elapsed time in milliseconds: "\
                             << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() \
                             << " ms" << std::endl;






int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Renderer *renderer;
    SDL_Window *window;

    canvas surface(1280, 720, {255, 0, 0});


    window = SDL_CreateWindow(
            "lele",                  // window title
            0,           // initial x position
            0,           // initial y position
            1280,                               // width, in pixels
            720,                               // height, in pixels
            SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL               // flags - see below
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_TARGET,
                                             1280,
                                             720);


    double counter = 0;
    for (int i = 0; i < 1920; i++) {
        t1 = std::chrono::system_clock::now();

        SDL_UpdateTexture(texture, NULL, surface.get_pixel_ptr(), surface.pitch());

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);

        t2 = std::chrono::system_clock::now();

        counter += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    }

    std::cout << counter / 1920;

    std::this_thread::sleep_for(std::chrono::seconds(2));


    //SDL_FreeSurface(surface);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

