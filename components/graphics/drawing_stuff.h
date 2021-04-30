//
// Created by piotr233 on 18.04.2021.
//

#ifndef DRAWING_STUFF_H
#define DRAWING_STUFF_H

#include <SDL.h>
#include <array>


#include <cmath>
#include "canvas.h"

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


void draw_point(canvas &surface, Coord point, RGBColor color, unsigned radius);



void draw_circle(canvas &surface, Coord &point, int radius);


/// draws numbers on the screen in given point
/// \note that numbers will be displayed to the right and down form the given position
/// \param renderer the placement of our pixels
/// \param number value that will be draw, important is that number >=0 and <10
/// \param scale of displayed object, scale must be >=1
/// \param color the color that displayed   object will have
/// \param position where top left corner of our object will end up
void draw_number(canvas &surface, int number, char scale, RGBColor color, Coord position) ;

void draw_line_between_points(SDL_Renderer *renderer, Coord first_point, Coord second_point, RGBColor color,
                              unsigned line_thickness);
#endif //DRAWING_STUFF_H
