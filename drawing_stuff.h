//
// Created by studio25 on 14.04.2021.
//

#ifndef LOL_FALA_DRAWING_STUFF_H
#define LOL_FALA_DRAWING_STUFF_H

#include <SDL.h>
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define PI 3.1415
#include <cmath>

struct rgb_color {
    rgb_color(double r, double g, double b) : r(r), g(g), b(b) {}

    char r;
    char g;
    char b;
};

struct cord {
    cord(int x, int y) : x(x), y(y) {}

    int x;
    int y;

};



void draw_big_point(SDL_Renderer *renderer, cord &point, int r);
rgb_color gen_rainbow(unsigned height, unsigned max_height);
void draw_point(SDL_Renderer *renderer, cord &point);
#endif //LOL_FALA_DRAWING_STUFF_H
