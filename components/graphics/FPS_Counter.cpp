//
// Created by pc on 22.04.2021.
//

#include "FPS_Counter.h"

FPS_Counter::FPS_Counter(SDL_Renderer *renderer,
                         RGBColor color,
                         Coord counter_position) : time_point(std::chrono::steady_clock::now()), renderer(renderer),
                                                   draw_color(color), counter_position(counter_position) {}

FPS_Counter::FPS_Counter(SDL_Renderer *renderer) : time_point(std::chrono::steady_clock::now()), renderer(renderer),
                                                   draw_color({255, 0, 0}), counter_position({0, 0}) {}

void FPS_Counter::draw() {
    auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - time_point);
    int fps = std::chrono::seconds(1) / time_dif;

    time_point = std::chrono::steady_clock::now();

    draw_number(renderer, fps / 10, 2, draw_color, counter_position);

    draw_number(renderer, fps, 2, draw_color, {counter_position.x + 10, counter_position.y + 10});

}



