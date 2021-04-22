//
// Created by pc on 22.04.2021.
//

#ifndef EQUALIZER_FPS_COUNTER_H
#define EQUALIZER_FPS_COUNTER_H

/// class creates, and keeps track of time it takes to generate one frame

#include <chrono>
#include <SDL.h>
#include "drawing_stuff.h"

class FPS_Counter {
    FPS_Counter() = delete;

    FPS_Counter(SDL_Renderer *renderer,
                RGBColor color,
                Coord counter_position);

    FPS_Counter(SDL_Renderer *renderer);


    void draw();

protected:
   std::chrono::time_point<std::chrono::steady_clock> time_point;
    SDL_Renderer *renderer;
    RGBColor draw_color;
    Coord counter_position;
};


#endif //EQUALIZER_FPS_COUNTER_H
