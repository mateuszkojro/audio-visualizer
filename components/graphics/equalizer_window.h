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

#include "FPS_Counter.h"
#include "drawing_stuff.h"
#include "DataInterpreter.h"
#include "../scheduler/p_scheduler.h"

#include "Buttons/Button.h"
#include "Canvas.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600




// todo bub 0x5jh circles aren't circles they are clocks
// todo fill in spaces between clocks

// todo remove window_width and height and figure something better in place


/// \param values_to_be_drown vector containing y values of the point's tah will be drawn on the screen,
/// \important thing all values must be in range <0;WINDOW_HEIGHT)
/// also vector will be deleted after read
/// \param renderer the renderer what will be used to update window
void equalizer_window(Canvas *surface, std::mutex &surface_guard, std::vector<Button> &button_vector);


void equalizer_window_from_data(std::vector<int> *data);

/// creates even spaced (on x axis) dot's from given y values
///\param values_to_be_drown vector of values tah will end up as y values in returned coordinates
///\param begin height on witch leftmost point will be, this point is only to make function look nice
///\param end height on witch rightmost point will be, this point is only to make function look nice
///\return vector of point's that will be represented as  "big dots"
std::vector<Coord> create_points(int begin, int end, std::vector<int> &values_to_be_drown);

/// generates visual effect based on values passed in local_values
/// \param renderer pointer to our renderer
/// \param local_values array representing positions of drawn points
/// the values given will be processed before placement on screen
/// \return window will be updated with new data
/// the structures already displayed will perish
void draw_function(Canvas &surface,
                   std::vector<int> local_values,
                   bool draw_big_points,
                   bool static_color,
                   bool connect_window_edges);


void draw_levels(Canvas &surface,
                 std::vector<int> local_values,
                 bool draw_big_points,
                 bool static_color);

void draw_function_but_fill_it_below(Canvas &surface,
                                     std::vector<int> local_values,
                                     bool draw_big_points,
                                     bool static_color,
                                     bool connect_window_edges);



/// creates even spaced (on x axis) dot's from given y values
/// the difference is that generated function won't include static points on left and right margin
///\param values_to_be_drown vector of values tah will end up as y values in returned coordinates
///\return vector of point's that will be represented as  "big dots"
std::vector<Coord> create_points(std::vector<int> &values_to_be_drown);


/// creates set of points that fill in space between two given coordinates
/// space is filled uniformly, therefore gaps might be generated
/// function used to generate filler: cos(x)
/// \return set of points that fill the given gap
/// \param begin first point of the output function, also left side of the gap
/// \param end last point to be drowned, also the end of the gap
std::vector<Coord> gen_function_between_points(Coord begin, Coord end);


#endif //EQUALIZER_EQUALIZER_WINDOW_H
