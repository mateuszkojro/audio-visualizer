//
// Created by pc on 22.04.2021.
//

#include <iostream>
#include "FPS_Counter.h"

FPS_Counter::FPS_Counter(SDL_Renderer *renderer, int scale, RGBColor color, Coord counter_position) :
        time_point(std::chrono::steady_clock::now()),
        renderer(renderer),
        scale(scale),
        draw_color(color),
        counter_position(counter_position) {}


FPS_Counter::FPS_Counter(SDL_Renderer *renderer) :
        time_point(std::chrono::steady_clock::now()),
        renderer(renderer),
        scale(6), // coz it looks good
        draw_color({255, 255, 255}),
        counter_position({0, 0}) {}


FPS_Counter::FPS_Counter(SDL_Renderer *renderer, Coord counter_position) :
        time_point(std::chrono::steady_clock::now()),
        renderer(renderer),
        scale(6), // coz it looks good
        draw_color({255, 255, 255}),
        counter_position(counter_position) {}


void FPS_Counter::draw() {
    static int frames = 0;
    static int fps = 0;


    if (frames % 10 == 9) {

        auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - time_point);

        fps = 10000 / time_dif.count();

        time_point = std::chrono::steady_clock::now();
    }
    draw_number_SDL(renderer, (fps / 100) %10, scale, draw_color, counter_position);
    draw_number_SDL(renderer, (fps / 10)%10, scale, draw_color, {counter_position.x + 5 * scale,counter_position.y});

    draw_number_SDL(renderer, fps % 10, scale, draw_color, {counter_position.x + 10 * scale, counter_position.y});

    ++frames;
}

