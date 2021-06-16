//
// Created by piotr233 on 18.04.2021.
//

#ifndef EQUALIZER_COMPONENTS_GRAPHICS_DRAWING_STUFF_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_DRAWING_STUFF_H_

#include <SDL.h>
#include <array>

#include "canvas.h"
#include <cmath>

/// generates rainbow gradient across window
/// \return color derived from gradient at given height
/// \param height drawn pixel height \note height < max_height
/// \pram max_height height of gradient effect
RgbColor GenRainbow(unsigned height, unsigned max_height);

/// draws numbers on the screen in given point
/// \note that numbers will be displayed to the right and down form the given
/// position \param renderer the placement of our pixels \param number value
/// that will be draw, important is that number >=0 and <10 \param scale of
/// displayed object, scale must be >=1 \param color the color that displayed
/// object will have \param position where top left corner of our object will
/// end up
void DrawNumber(Canvas &surface, int number, char scale, RgbColor color,
                Coord position);

#endif // EQUALIZER_COMPONENTS_GRAPHICS_DRAWING_STUFF_H_
