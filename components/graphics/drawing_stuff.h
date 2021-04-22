//
// Created by piotr233 on 18.04.2021.
//

#ifndef DRAWING_STUFF_H
#define DRAWING_STUFF_H

#include <SDL.h>
#include <array>


#include <cmath>

/// custom struct to represent color
struct RGBColor {

    RGBColor(double r, double g, double b) : r(r), g(g), b(b) {}

    char r;
    char g;
    char b;

};


/// describes duple of numbers
/// used to represent point in 2D space
struct Coord {
    Coord(int x, int y) : x(x), y(y) {}

    int x;
    int y;

};


/// generates rainbow gradient across window
/// \return color derived from gradient at given height
/// \param height drawn pixel height \note height < max_height
/// \pram max_height height of gradient effect
RGBColor gen_rainbow(unsigned height, unsigned max_height);

/// draws filled in circle on SDL canvas
/// \return circle in place of point
/// \param renderer the placement of our pixels
/// \param point position around where pixels will be affected
/// \param color  of the circle
/// \param radius of the circle
void draw_point_SDL(SDL_Renderer *renderer, Coord point, RGBColor color, unsigned radius);


/// draws hollow circle on SDL canvas
/// \return hollow circle in place of point
/// \param renderer the placement of our pixels
/// \param color  of the circle
/// \param radius of the circle
void draw_circle_SDL(SDL_Renderer *renderer, Coord &point, int radius);

void draw_number(SDL_Renderer *renderer, char number, char scale, RGBColor color, Coord position) ;

#endif //DRAWING_STUFF_H