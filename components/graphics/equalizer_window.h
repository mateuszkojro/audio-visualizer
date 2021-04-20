//
// Created by piotr233 on 20.04.2021.
//

#ifndef EQUALIZER_EQUALIZER_WINDOW_H
#define EQUALIZER_EQUALIZER_WINDOW_H

#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <vector>
#include <SDL.h>


#include "drawing_stuff.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define PI 3.1415

// todo bub 0x5jh circles aren't circles they are clocks
// todo fill in spaces between clocks
// todo error 0x6ga there seems to be some miscalculation in left top corner
// todo remove window_width and height and figure something better in place

/// \param values_to_be_drown vector containing y values of the point's tah will be drawn on the screen,
/// important thing all values must be in range <0;WINDOW_HEIGHT)
void window_with_line(std::vector<int> *values_to_be_drown);

/// creates even spaced (on x axis) dot's from given y values
///\param values_to_be_drown vector of values tah will end up as y values in returned coordinates
///\param begin height on witch leftmost point will be, this point is only to make function look nice
///\param end height on witch rightmost point will be, this point is only to make function look nice
///\return vector of point's that will be represented as  "big dots"
std::vector<Coord> create_points(int begin, int end, std::vector<int> &values_to_be_drown);

/// creates set of points that fill in space between two given coordinates
/// space is filled uniformly, therefore gaps might be generated
/// function used to generate filler: cos(x)
/// \return set of points that fill the given gap
/// \param begin first point of the output function, also left side of the gap
/// \param end last point to be drowned, also the end of the gap
std::vector<Coord> gen_function_between_points(Coord begin, Coord end);


#endif //EQUALIZER_EQUALIZER_WINDOW_H
